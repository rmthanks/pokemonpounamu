#!/usr/bin/env python3
"""Tile-seam lint: flag every horizontal/vertical neighbour pair in a map that
never occurs in any vanilla map on the same tileset pair.

python3 tools_pounamu/mapsynth/lint.py MapFolder [--png out.png]
"""
import json, os, struct, sys
from collections import Counter, defaultdict
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
from synth import ROOT, LAYOUTS, read_cells

POUNAMU_PREFIX = ('LAYOUT_HERETAUNGA', 'LAYOUT_ORCHARD', 'LAYOUT_AHURIRI', 'LAYOUT_ROUTE2_', 'LAYOUT_WAIROA',
                  'LAYOUT_TURANGA', 'LAYOUT_ROUTE35', 'LAYOUT_OPOTIKI', 'LAYOUT_TAURANGA', 'LAYOUT_ROUTE36',
                  'LAYOUT_ROTORUA', 'LAYOUT_TAUPO', 'LAYOUT_ROUTE5_RANGES', 'LAYOUT_ROUTE1_', 'LAYOUT_ROUTE43',
                  'LAYOUT_NGAMOTU', 'LAYOUT_WHANGANUI', 'LAYOUT_WELLINGTON', 'LAYOUT_WAITOHI', 'LAYOUT_WHAKATU',
                  'LAYOUT_OTAUTAHI', 'LAYOUT_OTEPOTI', 'LAYOUT_TE_MATA', 'LAYOUT_ROUTE3', 'LAYOUT_ROUTE5',
                  'LAYOUT_ROUTE6', 'LAYOUT_ROUTE7')

def vanilla_pairs(prim, sec):
    R, B = defaultdict(Counter), defaultdict(Counter)
    for lid, l in LAYOUTS.items():
        if l.get('primary_tileset') != prim or l.get('secondary_tileset') != sec:
            continue
        if lid.startswith(POUNAMU_PREFIX):
            continue
        try:
            w, h, c = read_cells(lid)
        except Exception:
            continue
        for y in range(h):
            for x in range(w):
                a = c[y*w+x] & 0x3FF
                if x+1 < w: R[a][c[y*w+x+1] & 0x3FF] += 1
                if y+1 < h: B[a][c[(y+1)*w+x] & 0x3FF] += 1
    return R, B

def lint(folder):
    mj = json.load(open(os.path.join(ROOT, 'data/maps', folder, 'map.json')))
    l = LAYOUTS[mj['layout']]
    w, h, c = read_cells(mj['layout'])
    R, B = vanilla_pairs(l['primary_tileset'], l['secondary_tileset'])
    known = set(R) | set(B)
    bad = []
    for y in range(h):
        for x in range(w):
            a = c[y*w+x] & 0x3FF
            if x+1 < w:
                b = c[y*w+x+1] & 0x3FF
                if a in known and b in known and b not in R[a]:
                    bad.append(('H', x, y, a, b))
            if y+1 < h:
                b = c[(y+1)*w+x] & 0x3FF
                if a in known and b in known and b not in B[a]:
                    bad.append(('V', x, y, a, b))
    return bad, (w, h, c, l)

if __name__ == '__main__':
    bad, (w, h, c, l) = lint(sys.argv[1])
    print(f'{sys.argv[1]}: {len(bad)} unseen pairs')
    for d, x, y, a, b in bad[:400]:
        print(f'  {d} ({x},{y}) {a:03x}->{b:03x}')
    if '--png' in sys.argv:
        import render_tiles as rt
        from PIL import ImageDraw
        img = rt.TilesetPair(l['primary_tileset'], l['secondary_tileset']).render_map(list(c), w, scale=2)
        d = ImageDraw.Draw(img)
        for dd, x, y, a, b in bad:
            if dd == 'H': d.line((x*32+31, y*32+2, x*32+31, y*32+29), fill=(255, 0, 0), width=3)
            else: d.line((x*32+2, y*32+31, x*32+29, y*32+31), fill=(255, 0, 0), width=3)
        img.save(sys.argv[sys.argv.index('--png')+1])
