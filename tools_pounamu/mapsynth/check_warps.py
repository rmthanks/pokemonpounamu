#!/usr/bin/env python3
"""Every warp on every Pounamu map must stand on a tile that can warp (a door, a mat, a
ladder, stairs...) and point at a map and warp id that exist (Sept 2026). Warps on plain
floor never fire: that is how the Sky Tower, the League rooms and Te Mata summit ended up
one-way. Vanilla maps (the ones in the initial import) are skipped.
  python3 tools_pounamu/mapsynth/check_warps.py"""
import sys, json, os, glob, struct
HERE=os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0,HERE); sys.path.insert(0,os.path.dirname(HERE))
import routekit as rk
from render_tiles import TILESET_DIRS
ROOT=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
lays={l['id']:l for l in json.load(open(f'{ROOT}/data/layouts/layouts.json'))['layouts'] if 'id' in l}
names={v:k for k,v in rk.MB.items()}
def tsdir(name):
    if name in TILESET_DIRS: return TILESET_DIRS[name]
    # guess: gTileset_FooBar -> secondary/foo_bar or primary/...
    import re
    base=re.sub(r'(?<!^)(?=[A-Z])','_',name.replace('gTileset_','')).lower()
    for kind in ('secondary','primary'):
        p=f'data/tilesets/{kind}/{base}'
        if os.path.exists(f'{ROOT}/{p}'): return p
    return None
beh_cache={}
def behs(prim, sec):
    key=(prim,sec)
    if key in beh_cache: return beh_cache[key]
    b={}
    for ts, base in ((prim,0),(sec,0x200)):
        d=tsdir(ts)
        if not d: continue
        raw=open(f'{ROOT}/{d}/metatile_attributes.bin','rb').read()
        for i in range(len(raw)//2):
            b[base+i]=struct.unpack('<H',raw[i*2:i*2+2])[0]&0xFF
    beh_cache[key]=b
    return b
ids={}
maps={}
for p in glob.glob(f'{ROOT}/data/maps/*/map.json'):
    j=json.load(open(p)); ids[j['id']]=j['name']; maps[j['name']]=j
WARPY=('DOOR','WARP','LADDER','ESCALATOR','STAIRS','HOLE','CAVE','SPIN')
import subprocess
vanilla={l.split('/')[2] for l in subprocess.run(['git','show','7e6f8c47','--name-only','--format='],cwd=ROOT,capture_output=True,text=True).stdout.split() if l.startswith('data/maps/') and l.endswith('/map.json')}
bad=0
for name,j in sorted(maps.items()):
    if name in vanilla: continue
    L=lays.get(j['layout'])
    if not L: print('NO LAYOUT', name); continue
    W,H=L['width'],L['height']
    raw=open(f"{ROOT}/{L['blockdata_filepath']}",'rb').read()
    cells=struct.unpack(f'<{len(raw)//2}H',raw)
    b=behs(L['primary_tileset'],L['secondary_tileset'])
    for i,w in enumerate(j.get('warp_events') or []):
        x,y=w['x'],w['y']
        if not (0<=x<W and 0<=y<H):
            print(f'{name}: warp {i} off the map ({x},{y})'); bad+=1; continue
        t=cells[y*W+x]&0x3ff
        bn=names.get(b.get(t,0),'?')
        dest=ids.get(w['dest_map'])
        problems=[]
        if not any(k in bn for k in WARPY):
            problems.append(f'tile {t:03x} is {bn}')
        if w['dest_map']!='MAP_DYNAMIC' and not dest:
            problems.append(f"dest {w['dest_map']} missing")
        elif dest:
            dw=maps[dest].get('warp_events') or []
            did=int(w['dest_warp_id'])
            if did>=len(dw): problems.append(f"dest warp id {did} >= {len(dw)}")
        if problems:
            bad+=1
            print(f"{name}: warp {i} ({x},{y}) -> {w['dest_map']}: "+'; '.join(problems))
print('problems', bad)
