#!/usr/bin/env python3
"""Convert a source image into the Pounamu title screen backdrop.
Replaces graphics/title_screen/{rayquaza.png,rayquaza.bin,rayquaza_and_clouds.pal}
and blanks the clouds layer. Budget: <=512 unique tiles, 14 colors (slots 1-14
of palette 14; slot 15 is animated by UpdateLegendaryMarkingColor, slot 0 transparent).
"""
import sys, struct
from PIL import Image
import numpy as np

SRC = sys.argv[1]
GFXDIR = 'graphics/title_screen'
NCOLORS = 14
MAXTILES = 512

im = Image.open(SRC).convert('RGB').resize((240,160), Image.LANCZOS)
q = im.quantize(colors=NCOLORS, method=Image.MEDIANCUT, dither=Image.Dither.NONE)
pal = q.getpalette()[:NCOLORS*3]
px = np.asarray(q, dtype=np.uint8) + 1      # shift to indices 1..14 (0 = transparent)

# compose into 256x256 map (32x32 tiles); pad with the sky color (top-left pixel)
full = np.full((256,256), px[0,0], dtype=np.uint8)
full[:160,:240] = px

# cut into tiles, dedup with flips
tiles = {}
order = []
tilemap = np.zeros((32,32), dtype=np.uint16)
def key(t): return t.tobytes()
for ty in range(32):
    for tx in range(32):
        t = full[ty*8:(ty+1)*8, tx*8:(tx+1)*8]
        cands = [(t,0,0),(t[:, ::-1],1,0),(t[::-1,:],0,1),(t[::-1,::-1],1,1)]
        hit=None
        for c,hf,vf in cands:
            k=key(c)
            if k in tiles: hit=(tiles[k],hf,vf); break
        if hit is None:
            idx=len(order)
            tiles[key(t)]=idx
            order.append(t.copy())
            hit=(idx,0,0)
        idx,hf,vf=hit
        tilemap[ty,tx] = idx | (hf<<10) | (vf<<11) | (14<<12)
n=len(order)
print('unique tiles:',n)
if n>MAXTILES:
    print('over budget; increasing posterization', file=sys.stderr); sys.exit(2)

# tilesheet png: 16 tiles wide
rows=(n+15)//16
sheet=np.zeros((rows*8,128),dtype=np.uint8)
for i,t in enumerate(order):
    r,c=divmod(i,16)
    sheet[r*8:(r+1)*8, c*8:(c+1)*8]=t
out=Image.fromarray(sheet, mode='P')
palette=[0,0,0]+pal+[0,0,0]*(16-1-NCOLORS)
out.putpalette(palette+[0,0,0]*(256-16))
out.save(f'{GFXDIR}/rayquaza.png')

# tilemap bin
open(f'{GFXDIR}/rayquaza.bin','wb').write(tilemap.astype('<u2').tobytes())

# JASC palette (16 entries)
with open(f'{GFXDIR}/rayquaza_and_clouds.pal','w') as f:
    f.write('JASC-PAL\r\n0100\r\n16\r\n')
    f.write('0 0 0\r\n')
    for i in range(NCOLORS):
        f.write(f'{pal[i*3]} {pal[i*3+1]} {pal[i*3+2]}\r\n')
    f.write('0 0 0\r\n')

# recolor the vanilla cloud wisps into our palette (keeps the misty drift effect)
van=Image.open(f'{GFXDIR}/clouds_vanilla.png')
vpal=van.getpalette()
vpx=np.asarray(van,dtype=np.uint8)
# our palette as array (slots 1..NCOLORS)
ours=np.array(pal,dtype=np.int32).reshape(-1,3)
lum=ours.sum(axis=1)
# the two palest of our colors, weighted toward them for cloud pixels
pale=np.argsort(lum)[::-1][:3]+1
def nearest_pale(rgb):
    d=((ours[pale-1]-np.array(rgb))**2).sum(axis=1)
    return int(pale[int(np.argmin(d))])
lut=np.zeros(256,dtype=np.uint8)
for vi in np.unique(vpx):
    if vi==0: continue
    rgb=vpal[vi*3:vi*3+3]
    lut[vi]=nearest_pale(rgb)
cpx=lut[vpx]
cl=Image.fromarray(cpx,mode='P')
cl.putpalette(palette+[0,0,0]*(256-16))
cl.save(f'{GFXDIR}/clouds.png')
print('title backdrop + mist written')
