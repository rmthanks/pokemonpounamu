#!/usr/bin/env python3
"""Convert a source image into the Pounamu THE END backdrop (BG1 behind the letters).
Writes graphics/credits/pounamu_end.{png,bin,pal}. 15 colors (palette 14 slots 1-15)."""
import sys, struct
from PIL import Image
import numpy as np

SRC = sys.argv[1]
GFXDIR = 'graphics/credits'
NCOLORS = 15
MAXTILES = 512
SKY_SPLIT = 56

im = Image.open(SRC).convert('RGB').resize((240,160), Image.LANCZOS)
a = np.asarray(im)
lum = a.astype(int).sum(axis=2)
sun_px = a[lum >= np.percentile(lum, 99.7)]
r_, g_, b_ = a[...,0].astype(int), a[...,1].astype(int), a[...,2].astype(int)
green_px = a[(g_ > r_*0.95) & (g_ > b_*1.1) & (lum > 150) & (lum < 620)]
boost = np.vstack([a.reshape(-1,3)] + [sun_px]*40 + ([green_px]*6 if len(green_px) else []))
side = int(len(boost)**0.5)
boost_img = Image.fromarray(boost[:side*side].reshape(side,side,3))
pal_src = boost_img.quantize(colors=NCOLORS, method=Image.MEDIANCUT, kmeans=25, dither=Image.Dither.NONE)
q = im.quantize(palette=pal_src, dither=Image.Dither.NONE)
qd = im.quantize(palette=pal_src, dither=Image.Dither.FLOYDSTEINBERG)
q.paste(qd.crop((0,SKY_SPLIT,240,160)), (0,SKY_SPLIT))
pal = pal_src.getpalette()[:NCOLORS*3]
px = np.asarray(q, dtype=np.uint8) + 1

full = np.full((256,256), px[0,0], dtype=np.uint8)
full[:160,:240] = px

tiles = {}; order = []
tilemap = np.zeros((32,32), dtype=np.uint16)
for ty in range(32):
    for tx in range(32):
        t = full[ty*8:(ty+1)*8, tx*8:(tx+1)*8]
        cands = [(t,0,0),(t[:, ::-1],1,0),(t[::-1,:],0,1),(t[::-1,::-1],1,1)]
        hit=None
        for c,hf,vf in cands:
            k=c.tobytes()
            if k in tiles: hit=(tiles[k],hf,vf); break
        if hit is None:
            idx=len(order); tiles[t.tobytes()]=idx; order.append(t.copy()); hit=(idx,0,0)
        idx,hf,vf=hit
        tilemap[ty,tx] = idx | (hf<<10) | (vf<<11) | (14<<12)
n=len(order)
print('unique tiles (exact):',n)
T=0
while n>MAXTILES and T<6:
    T+=1
    arr=np.stack(order)
    keep=[]; remap={}
    for i in range(len(arr)):
        merged=False; ti=arr[i]
        for j in keep:
            for cand in (arr[j],arr[j][:, ::-1],arr[j][::-1,:],arr[j][::-1,::-1]):
                if int((ti!=cand).sum())<=T: remap[i]=j; merged=True; break
            if merged: break
        if not merged: remap[i]=i; keep.append(i)
    newindex={}; neworder=[]
    for j in keep: newindex[j]=len(neworder); neworder.append(order[j])
    flat=tilemap.flatten()
    for k in range(len(flat)):
        e=int(flat[k]); idx=e&0x3FF
        flat[k]=(e & ~0x3FF)|newindex[remap[idx]]
    tilemap=flat.reshape(32,32); order=neworder; n=len(order)
    print(f'approx merge T={T}: {n} tiles')
if n>MAXTILES:
    print('over budget', file=sys.stderr); sys.exit(2)

rows=(n+15)//16
sheet=np.zeros((rows*8,128),dtype=np.uint8)
for i,t in enumerate(order):
    r,c=divmod(i,16)
    sheet[r*8:(r+1)*8, c*8:(c+1)*8]=t
out=Image.fromarray(sheet, mode='P')
palette=[0,0,0]+pal
out.putpalette(palette+[0,0,0]*(256-16))
out.save(f'{GFXDIR}/pounamu_end.png')
open(f'{GFXDIR}/pounamu_end.bin','wb').write(tilemap.astype('<u2').tobytes())
with open(f'{GFXDIR}/pounamu_end.pal','w') as f:
    f.write('JASC-PAL\r\n0100\r\n16\r\n0 0 0\r\n')
    for i in range(NCOLORS):
        f.write(f'{pal[i*3]} {pal[i*3+1]} {pal[i*3+2]}\r\n')
print('credits backdrop written')
