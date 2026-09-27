#!/usr/bin/env python3
"""Whanganui - "ko au te awa, ko te awa ko au" (Sept 2026).

The awa runs the length of town on the east, a riverside walk along its west bank; the
road from Route 3 in the north to the Kapiti coast in the south; the Pokemon Center on
the cross street and the glass studio on the lane."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 24, 22
c = Canvas(W, H)
c.border()
c.box(6, 0, 9, 1, '.'); c.box(6, 20, 9, 21, '.')
c.road([(7, 0), (7, 21)])
c.box(2, 8, 13, 9, 'P')                 # the cross street
c.road([(12, 8), (12, 17)])             # the riverside walk
c.box(3, 16, 13, 17, 'P')               # the lane
# the awa
c.box(14, 2, 19, 17, 'W')
c.box(14, 2, 15, 5, '.'); c.box(18, 12, 19, 17, '.')     # the awa bends
c.box(20, 2, 21, 19, 'T')
for x, y in [(10, 2), (2, 18), (10, 18), (16, 20), (18, 14), (18, 16)]:
    c.tree(x, y)
for x, y in [(4, 10), (5, 11), (10, 11), (11, 12), (9, 4), (10, 5), (5, 19), (15, 19)]:
    c.at(x, y, '*')

stamps = [('pc', 2, 4, 0), ('house5', 2, 12, 1)]
SPEC = dict(
    folder='Whanganui', layout='LAYOUT_WHANGANUI', tileset='gTileset_Petalburg',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    objects={'RiverMan': (13, 11, 'RIGHT'), 'Kid': (10, 14, None), 'DURIEJOB': (13, 4, 'RIGHT')},
    signs=[(9, 7, 'RiverSign')],
    hidden={0: (13, 18), 1: (2, 3), 2: (12, 4), 3: (6, 18)},
    conns={'MAP_ROUTE3_POUNAMU': 6 - 24, 'MAP_ROUTE1_KAPITI': 6 - 24},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
