#!/usr/bin/env python3
"""Remove orphan half-trees beside map openings (Sept 2026).

Trees are 2x2 metatiles (0x1D4 0x1D5 over 0x1DC 0x1DD). Most Pounamu maps cut
their 2-wide exits at x7-8, one column off the tree lattice, which leaves half
a tree on each side of every entrance. For each tree 2x2 that is cut by an
opening (a missing quarter that is walkable), the remaining quarters become
grass - i.e. the opening widens to the lattice. Trees cut by anything else are
only reported.

python3 tools_pounamu/mapsynth/fix_orphan_trees.py [--write] Map1 Map2 ...
"""
import json, os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from synth import ROOT, LAYOUTS

TL, TR, BL, BR = 0x1D4, 0x1D5, 0x1DC, 0x1DD
sys.path.insert(0, os.path.dirname(HERE))
from mapgrid import behaviors, WATER
GRASS = 0x3001
# half-trees that are not beside an exit (map edge with no connection, or the
# beach strip along Ahuriri's seafront): leave as they are
EXCLUDE = {'Waitohi': {(6, 0), (7, 0)},
           'AhuririCity': {(36, 0), (36, 1), (36, 34), (36, 35)}}

def fix(folder, write):
    lid = json.load(open(os.path.join(ROOT, 'data/maps', folder, 'map.json')))['layout']
    l = LAYOUTS[lid]; W, H = l['width'], l['height']
    p = os.path.join(ROOT, l['blockdata_filepath'])
    c = list(struct.unpack(f'<{W*H}H', open(p, 'rb').read()))
    get = lambda x, y: c[y*W+x] & 0x3FF
    beh = behaviors(l)
    # land you can walk on: no collision and not water (ponds cut into tree lines are left alone)
    walk = lambda x, y: not (c[y*W+x] >> 10) & 3 and beh.get(get(x, y), 0) not in WATER
    cleared, report = set(), []
    for y in range(H):
        for x in range(W):
            m = get(x, y)
            if m not in (TL, TR, BL, BR):
                continue
            ox = x - (0 if m in (TL, BL) else 1)
            oy = y - (0 if m in (TL, TR) else 1)
            quad = {(ox, oy): TL, (ox+1, oy): TR, (ox, oy+1): BL, (ox+1, oy+1): BR}
            missing = [(px, py) for (px, py), t in quad.items()
                       if 0 <= px < W and 0 <= py < H and get(px, py) != t]
            if not missing:
                continue
            if all(walk(px, py) for px, py in missing):
                for (px, py), t in quad.items():
                    if 0 <= px < W and 0 <= py < H and get(px, py) == t:
                        cleared.add((px, py))
            else:
                report.append((x, y))
    cleared -= EXCLUDE.get(folder, set())
    for (x, y) in cleared:
        c[y*W+x] = GRASS
    if write and cleared:
        open(p, 'wb').write(struct.pack(f'<{W*H}H', *c))
    return sorted(cleared), sorted(set(report))

if __name__ == '__main__':
    write = '--write' in sys.argv
    for f in [a for a in sys.argv[1:] if not a.startswith('--')]:
        cl, rep = fix(f, write)
        print(f'{f:16} cleared {len(cl):2} {cl[:8]}' + (f'  UNFIXED {rep[:6]}' if rep else ''))
