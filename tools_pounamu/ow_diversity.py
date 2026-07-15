#!/usr/bin/env python3
"""Overworld + story-cast diversity pass.
1. npc_1..4 tan/brown palettes + tags + registration
2. Tan/Brown OW gfx variants for 25 sheets (20 classes + MOM, WOMAN_2, MAN_3, MANIAC, HEX_MANIAC)
3. Swap map objects: class trainers per their battle-pic tone; Rata/Tama/Awhi -> brown
4. Recolor: player OW pals (brendan/may), player back pics, story battle pics
5. Rename generated civilians that collide with story names
"""
import json, os, re, colorsys
from PIL import Image

def hsv(c): return colorsys.rgb_to_hsv(c[0]/255,c[1]/255,c[2]/255)
def rgb(h,s,v):
    r,g,b = colorsys.hsv_to_rgb(h%1.0,max(0,min(1,s)),max(0,min(1,v)))
    return (int(r*255),int(g*255),int(b*255))
def tan(c):
    h,s,v = hsv(c); return rgb(h+0.005, min(1,s*1.30), v*0.80)
def brown(c):
    h,s,v = hsv(c); return rgb(h+0.012, min(1,s*1.55), v*0.55)
def is_skin(c):
    h,s,v = hsv(c)
    return 0.015 <= h <= 0.105 and 0.15 <= s <= 0.62 and v >= 0.55

# ---------- 1. NPC palettes ----------
def read_pal(p):
    lines = open(p).read().splitlines()
    n = int(lines[2])
    return [tuple(map(int,l.split())) for l in lines[3:3+n]]
def write_pal(p, cols):
    with open(p,'w') as f:
        f.write('JASC-PAL\r\n0100\r\n%d\r\n' % len(cols))
        for c in cols: f.write(f'{c[0]} {c[1]} {c[2]}\r\n')

SKIN_IDX = (1,2,3)  # shared ramp across npc_1..4
pal_decl=[]; pal_reg=[]; tag_defs=[]
tagval = 0x11B0
for n in (1,2,3,4):
    base = read_pal(f'graphics/object_events/palettes/npc_{n}.pal')
    for suf, fn in (('tan',tan),('brown',brown)):
        newc = list(base)
        for i in SKIN_IDX: newc[i] = fn(base[i])
        path = f'graphics/object_events/palettes/npc_{n}_{suf}.pal'
        write_pal(path, newc)
        tag = f'OBJ_EVENT_PAL_TAG_NPC_{n}_{suf.upper()}'
        tag_defs.append(f'#define {tag} 0x{tagval:04X}')
        tagval += 1
        cname = f'gObjectEventPal_Npc{n}{suf.title()}'
        pal_decl.append(f'const u16 {cname}[] = INCGFX_U16("{path}", ".gbapal");')
        pal_reg.append(f'    {{{cname}, {tag}}},')

# tag constants
h = open('include/constants/event_objects.h').read()
anchor = '#define OBJ_EVENT_PAL_TAG_NPC_1                   0x1103'
h = h.replace(anchor, '\n'.join(tag_defs) + '\n' + anchor)

# palette registration
c = open('src/event_object_movement.c').read()
c = c.replace('    {gObjectEventPal_Npc1,                  OBJ_EVENT_PAL_TAG_NPC_1},',
              '\n'.join(pal_reg) + '\n    {gObjectEventPal_Npc1,                  OBJ_EVENT_PAL_TAG_NPC_1},')
open('src/event_object_movement.c','w').write(c)

g = open('src/data/object_events/object_event_graphics.h').read()
g += '\n' + '\n'.join(pal_decl) + '\n'
open('src/data/object_events/object_event_graphics.h','w').write(g)

# ---------- 2. OW gfx variants ----------
SHEETS = ['YOUNGSTER','LASS','SCHOOL_KID_M','CAMPER','PICNICKER','HIKER','FISHERMAN','BUG_CATCHER',
 'MAN_5','WOMAN_5','EXPERT_M','EXPERT_F','POKEFAN_M','POKEFAN_F','MAN_3','WOMAN_3','SAILOR',
 'BLACK_BELT','BOY_2','GENTLEMAN','MOM','WOMAN_2','MANIAC','HEX_MANIAC']
ptr = open('src/data/object_events/object_event_graphics_info_pointers.h').read()
gi  = open('src/data/object_events/object_event_graphics_info.h').read()

gfx_enum=[]; new_structs=[]; new_ptrs=[]; new_externs=[]
for t in SHEETS:
    m = re.search(rf'\[OBJ_EVENT_GFX_{t}\]\s*=\s*&(\w+)', ptr)
    struct = m.group(1)
    body = re.search(rf'const struct ObjectEventGraphicsInfo {struct} = \{{.*?\}};', gi, re.S).group(0)
    base_tag = re.search(r'\.paletteTag = (OBJ_EVENT_PAL_TAG_\w+),', body).group(1)
    npc_n = re.search(r'NPC_(\d)', base_tag)
    if not npc_n:
        print(f'skip {t}: tag {base_tag}'); continue
    n = npc_n.group(1)
    for suf in ('TAN','BROWN'):
        ns = struct + suf.title()
        nb = body.replace(f'{struct} =', f'{ns} =').replace(
            f'.paletteTag = {base_tag},', f'.paletteTag = OBJ_EVENT_PAL_TAG_NPC_{n}_{suf},')
        new_structs.append(nb)
        gfx_enum.append(f'    OBJ_EVENT_GFX_{t}_{suf},')
        new_externs.append(f'extern const struct ObjectEventGraphicsInfo {ns};')
        new_ptrs.append(f'    [OBJ_EVENT_GFX_{t}_{suf}] = &{ns},')

h = h.replace('    NUM_OBJ_EVENT_GFX,', '\n'.join(gfx_enum) + '\n    NUM_OBJ_EVENT_GFX,')
open('include/constants/event_objects.h','w').write(h)
gi += '\n' + '\n\n'.join(new_structs) + '\n'
open('src/data/object_events/object_event_graphics_info.h','w').write(gi)
# pointers: externs at top, entries before closing };
lines = ptr.rstrip()
idx = lines.rfind('};')
ptr2 = '\n'.join(new_externs) + '\n' + lines[:idx] + '\n'.join(new_ptrs) + '\n' + lines[idx:] + '\n'
open('src/data/object_events/object_event_graphics_info_pointers.h','w').write(ptr2)
print(f'created {len(gfx_enum)} OW gfx variants')

# ---------- 3. map object swaps ----------
# trainer tone from party file
party = open('src/data/trainers.party').read()
tone = {}
for m in re.finditer(r'=== (TRAINER_[A-Z0-9_]+) ===\n(?:.*?\n)*?Pic: (.+?)\n', party):
    p = m.group(2)
    if p.endswith(' Tan'): tone[m.group(1)] = 'TAN'
    elif p.endswith(' Brown'): tone[m.group(1)] = 'BROWN'

VARIANT_GFX = {f'OBJ_EVENT_GFX_{t}' for t in SHEETS}
CAST_BROWN_SCRIPTS = re.compile(
 r'(RataIdle|FlowerShop_EventScript_Mum$|Homestead_EventScript_Rata$|MumOrchardIdle|HeretaungaTown_EventScript_Rata$|FallenRata'
 r'|Homestead_EventScript_Tama$|TamaOrchardIdle|TamaIdle|TamaBreak|TamaStrait|RuapehuSummit_EventScript_Tama$|Tama2'
 r'|EventScript_Awhi$|AwhiIdle|AwhiHome|AwhiPostgame)')

swapped = {'class':0,'cast':0}
for d in os.listdir('data/maps'):
    mp = f'data/maps/{d}/map.json'
    sp = f'data/maps/{d}/scripts.inc'
    if not os.path.exists(mp): continue
    mj = json.load(open(mp))
    scr = open(sp).read() if os.path.exists(sp) else ''
    # script label -> trainer id
    lbl2tid = dict(re.findall(r'(\w+)::\s*\n\ttrainerbattle_single (TRAINER_[A-Z0-9_]+)', scr))
    changed = False
    for o in mj.get('object_events', []):
        gid = o.get('graphics_id','')
        sc = str(o.get('script',''))
        if CAST_BROWN_SCRIPTS.search(sc) and gid in VARIANT_GFX:
            o['graphics_id'] = gid + '_BROWN'; swapped['cast'] += 1; changed = True
            continue
        tid = lbl2tid.get(sc)
        if tid and tid in tone and gid in VARIANT_GFX:
            o['graphics_id'] = gid + '_' + tone[tid]; swapped['class'] += 1; changed = True
    if changed: json.dump(mj, open(mp,'w'), indent=2)
print('map swaps:', swapped)

# ---------- 4. player + story battle pic recolors ----------
def recolor_png_palette(path, fn, only_idx=None):
    im = Image.open(path)
    pal = im.getpalette()
    ncol = len(pal)//3
    cols = [tuple(pal[i*3:i*3+3]) for i in range(ncol)]
    idxs = only_idx if only_idx else [i for i,cc in enumerate(cols) if i>0 and is_skin(cc)]
    for i in idxs:
        if i < ncol: cols[i] = fn(cols[i])
    flat=[]
    for cc in cols: flat += list(cc)
    im.putpalette(flat)
    im.save(path)
    return idxs

# player OW palettes (brendan/may .pal files)
for stem in ('brendan','may'):
    p = f'graphics/object_events/palettes/{stem}.pal'
    base = read_pal(p)
    idxs = [i for i,cc in enumerate(base) if i>0 and is_skin(cc)]
    for i in idxs: base[i] = brown(base[i])
    write_pal(p, base)
    print(f'player OW {stem}: skin idx {idxs}')

# player battle pics (front + back), story cast battle pics
for path in ('graphics/trainers/back_pics/brendan.png','graphics/trainers/back_pics/may.png',
             'graphics/trainers/front_pics/brendan.png','graphics/trainers/front_pics/may.png',
             'graphics/trainers/front_pics/aroma_lady.png','graphics/trainers/front_pics/leaf.png',
             'graphics/trainers/front_pics/champion_wallace.png','graphics/trainers/front_pics/elite_four_sidney.png'):
    idxs = recolor_png_palette(path, brown)
    print(os.path.basename(path), 'skin idx', idxs)

# ---------- 5. rename colliding civilians ----------
RENAME = {'Hori':'Heta','Rata':'Reka','Tama':'Turi','Awhi':'Amai','Whetu':'Waru','Toa':'Tuku',
          'Eru':'Epa','Hemi':'Huri','Kiri':'Kura','Nova':'Nia','Rangi':'Rewa','Hika':'Hui','Pounamu':'Puna'}
GEN_PREFIX = ('ORD_','R2B_','R2N_','R2E2_','R35A_','R35B_','RBOP_','R36_','R5P_','R1DP_','R43P_','R3P_','R1KP_',
 'R6P_','R7P_','R1SP_','R5RP_','RUAP_','TMTP_','HTT_','AHC_','WRT_','RTT_','TPT_','TGT_','WLT_','WKT_','OTT_',
 'OPT_','TMK_','GYM1_','GYM2_','GYM3_','GYM4_','GYM5_','GYM6_','GYM7_','GYM8_','TWEX_','VICT_')
blocks = re.split(r'(?=^=== TRAINER_[A-Z0-9_]+ ===$)', party, flags=re.M)
renamed=[]
for i,b in enumerate(blocks):
    m = re.match(r'^=== TRAINER_([A-Z0-9_]+) ===', b)
    if not m or not m.group(1).startswith(GEN_PREFIX): continue
    nm = re.search(r'^Name: (\w+)$', b, re.M)
    if nm and nm.group(1) in RENAME:
        old, new = nm.group(1), RENAME[nm.group(1)]
        blocks[i] = b.replace(f'Name: {old}\n', f'Name: {new}\n')
        renamed.append((m.group(1), old, new))
party2 = ''.join(blocks)
open('src/data/trainers.party','w').write(party2)
# also fix their intro text prefixes in scripts ("Rata: ...")
for tid, old, new in renamed:
    pass  # intro texts use "{name}: intro" - patch scripts
import glob
for f in glob.glob('data/maps/*/scripts.inc'):
    s = open(f).read(); orig = s
    for tid, old, new in renamed:
        s = s.replace(f'_Text_P{old}Intro:\n\t.string "{old}:', f'_Text_P{old}Intro:\n\t.string "{new}:')
    if s != orig: open(f,'w').write(s)
print('renamed civilians:', [(o,n) for _,o,n in renamed])
