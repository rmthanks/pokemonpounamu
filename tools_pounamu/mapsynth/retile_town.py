#!/usr/bin/env python3
"""Re-tile a town's ground with the route toolkit, keeping every building, sign and
street tile exactly where it is (Sept 2026).

The template towns had ponds running off their edges into the next map, half
trees where those ponds cut the tree border, and a dead-end gap or two. Each town
here is read back into classes (trees, grass, flowers, tall grass, pond, path),
given a few edits, and rendered again by the same rules as the routes, so trees,
pond edges, shore lips and canopy rows all come out the vanilla way. Anything
that isn't ground is kept as it was.
  python3 tools_pounamu/mapsynth/retile_town.py [Town ...]   (default: all below)"""
import os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
import routekit as rk
import context_view as cv
from synth import LAYOUTS, ROOT

GRASSY = {0x001, 0x002, rk.CANOPY_L, rk.CANOPY_R, rk.CANOPY_TALL_L, rk.CANOPY_TALL_R}
POND_IDS = set(rk.POND.values()) | {0x0C0, 0x0C1, 0x0C2, 0x0C3, 0x0C4}


def classify(m):
    W, H = m['W'], m['H']
    r = rk.Route(W, H, m['json']['name'])
    for y in range(H):
        for x in range(W):
            v = m['cells'][y * W + x]
            t = v & 0x3FF
            if t in rk.TREE_IDS:
                c = 'T'
            elif t in GRASSY:
                c = '.'
            elif t == rk.FLOWER:
                c = '*'
            elif t == rk.TALL:
                c = ','
            elif t in POND_IDS:
                c = 'W'
            elif t in rk.PATH:
                c = 'P'
            else:
                r.fix[(x, y)] = v
                c = '#'
            r.cls[y][x] = c
    return r


def box(r, x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            r.cls[y][x] = c
            r.fix.pop((x, y), None)


# per-town edits (x0, y0, x1, y1, class), applied in order
EDITS = {
    # the harbour ran off the south-east corner through the tree border, and a
    # gap on the east edge led nowhere
    'Turanga': [(24, 8, 25, 11, 'T'), (19, 14, 25, 21, 'T'), (19, 14, 23, 18, 'W'), (19, 19, 23, 19, '.'),
                (24, 12, 25, 19, 'T'), (21, 8, 21, 8, '.'), (21, 10, 21, 10, '.'),   # the main street ends square
                (23, 8, 23, 8, '.'), (23, 11, 23, 11, '.')],                            # the old exit's gateposts
    # Lake Taupo ran through the south border; the border's trees were off the lattice
    'Taupo': [(14, 21, 20, 21, '.'), (0, 22, 23, 23, 'T')],
    'Ngamotu': [(20, 21, 26, 21, '.'), (10, 22, 29, 23, 'T')],
    # the Whanganui ran out through the east and south edges
    'Whanganui': [(10, 14, 19, 15, 'T'), (18, 8, 19, 13, 'T'), (13, 9, 17, 12, 'W'), (13, 13, 17, 13, '.'),
                  (12, 9, 12, 13, '.')],
    # a notch in the north border, and the tree the harbour's widening cut in half
    # and the harbour's east side (a column of half trees, then pond water on the map edge):
    # whole trees down the east edge; the harbour carries on south into Queen Charlotte Sound
    'Waitohi': [(0, 0, 21, 1, 'T'), (20, 10, 21, 17, 'T')],
}


def retile(town):
    m = cv.load_map(town)
    r = classify(m)
    for x0, y0, x1, y1, c in EDITS.get(town, []):
        box(r, x0, y0, x1, y1, c)
    if town == 'Waitohi':
        r.pond_open_top = set()
    cells = r.render(seed=11)
    # a pond that runs on off the bottom edge into the next map (Waitohi's harbour into
    # Queen Charlotte Sound) keeps its water to the edge: nothing below needs a lip
    lay = LAYOUTS[m['json']['layout']]
    open(os.path.join(ROOT, lay['blockdata_filepath']), 'wb').write(struct.pack(f'<{len(cells)}H', *cells))
    return r


if __name__ == '__main__':
    for t in sys.argv[1:] or list(EDITS):
        retile(t)
        print('retiled', t)
