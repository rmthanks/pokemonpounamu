#!/usr/bin/env python3
"""Generate Tan and Brown skin-tone palette variants for common trainer classes.
Adds TRAINER_PIC_X_TAN / _BROWN constants, palette files, sprite-table entries, previews."""
import colorsys, os, re
from PIL import Image

CLASSES = {  # pic_const_suffix: (png_stem, CamelName)
 'YOUNGSTER': ('youngster','Youngster'), 'LASS': ('lass','Lass'),
 'SCHOOL_KID_M': ('school_kid_m','SchoolKidM'), 'CAMPER': ('camper','Camper'),
 'PICNICKER': ('picnicker','Picnicker'), 'HIKER': ('hiker','Hiker'),
 'FISHERMAN': ('fisherman','Fisherman'), 'BUG_CATCHER': ('bug_catcher','BugCatcher'),
 'POKEMON_RANGER_M': ('pokemon_ranger_m','PokemonRangerM'), 'POKEMON_RANGER_F': ('pokemon_ranger_f','PokemonRangerF'),
 'EXPERT_M': ('expert_m','ExpertM'), 'EXPERT_F': ('expert_f','ExpertF'),
 'POKEFAN_M': ('pokefan_m','PokefanM'), 'POKEFAN_F': ('pokefan_f','PokefanF'),
 'COOLTRAINER_M': ('cooltrainer_m','CooltrainerM'), 'COOLTRAINER_F': ('cooltrainer_f','CooltrainerF'),
 'SAILOR': ('sailor','Sailor'), 'BLACK_BELT': ('black_belt','BlackBelt'),
 'GUITARIST': ('guitarist','Guitarist'), 'GENTLEMAN': ('gentleman','Gentleman'),
}

def hsv(c): return colorsys.rgb_to_hsv(c[0]/255,c[1]/255,c[2]/255)
def rgb(h,s,v):
    r,g,b = colorsys.hsv_to_rgb(h%1.0,max(0,min(1,s)),max(0,min(1,v)))
    return (int(r*255),int(g*255),int(b*255))

def is_skin(c):
    h,s,v = hsv(c)
    return 0.015 <= h <= 0.105 and 0.15 <= s <= 0.62 and v >= 0.55

def tan(c):
    h,s,v = hsv(c)
    return rgb(h+0.005, min(1, s*1.30), v*0.80)

def brown(c):
    h,s,v = hsv(c)
    return rgb(h+0.012, min(1, s*1.55), v*0.55)

def write_pal(path, cols):
    with open(path,'w') as f:
        f.write('JASC-PAL\r\n0100\r\n16\r\n')
        for c in cols: f.write(f'{c[0]} {c[1]} {c[2]}\r\n')

enum_add=[]; decl_add=[]; table_add=[]
os.makedirs('/home/claude/skin_previews', exist_ok=True)
for const, (stem, camel) in CLASSES.items():
    png = f'graphics/trainers/front_pics/{stem}.png'
    im = Image.open(png)
    pal = im.getpalette()[:48]
    cols = [tuple(pal[i*3:i*3+3]) for i in range(16)]
    skin_idx = [i for i,c in enumerate(cols) if i>0 and is_skin(c)]
    for suffix, fn in (('TAN',tan),('BROWN',brown)):
        newc = list(cols)
        for i in skin_idx: newc[i] = fn(cols[i])
        palpath = f'graphics/trainers/palettes/{stem}_{suffix.lower()}.pal'
        write_pal(palpath, newc)
        enum_add.append(f'    TRAINER_PIC_{const}_{suffix},')
        decl_add.append(f'const u16 gTrainerPalette_{camel}{suffix.title()}[] = INCGFX_U16("graphics/trainers/palettes/{stem}_{suffix.lower()}.pal", ".gbapal");')
        table_add.append(f'    [TRAINER_PIC_{const}_{suffix}] =\n    {{\n        .frontPic = TRAINER_FRONT_PIC(gTrainerFrontPic_{camel}, gTrainerPalette_{camel}{suffix.title()}),\n    }},')
        # preview
        pv = im.copy(); flat=[]
        for c in newc: flat += list(c)
        pv.putpalette(flat + [0,0,0]*(256-16))
        pv.convert('RGB').resize((128,128), Image.NEAREST).save(f'/home/claude/skin_previews/{stem}_{suffix.lower()}.png')
    # base preview
    im.convert('RGB').resize((128,128), Image.NEAREST).save(f'/home/claude/skin_previews/{stem}_base.png')
    print(f'{stem}: skin indices {skin_idx}')

# wire into headers
h = open('include/constants/trainers.h').read()
h = h.replace('    TRAINER_PIC_COUNT,', '\n'.join(enum_add) + '\n    TRAINER_PIC_COUNT,')
open('include/constants/trainers.h','w').write(h)

g = open('src/data/graphics/trainers.h').read()
# palette declarations after the last existing declaration block (before the sprite table comment)
g = g.replace('// The first two parameters invoke a front pic', '\n'.join(decl_add) + '\n\n// The first two parameters invoke a front pic')
# table entries before the final closing brace of the file's last array
idx = g.rstrip().rfind('};')
g = g[:idx] + '\n'.join(table_add) + '\n' + g[idx:]
open('src/data/graphics/trainers.h','w').write(g)
print(f'wired {len(enum_add)} new trainer pics')
