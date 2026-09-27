#!/usr/bin/env python3
"""Opotiki - kiwifruit and the river wharf (Sept 2026).

The coast road runs straight through: north to Tauranga (Route 2), south round the East
Cape (Route 35). West of it the kiwifruit orchard in its rows (the General tileset's
planters) and the orchard family's house; east the Pokemon Center and the wharf on the
river where the old man watches the water."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 24, 20
c = Canvas(W, H)
c.border()
c.box(10, 0, 13, 1, '.'); c.box(10, 18, 13, 19, '.')
c.road([(11, 0), (11, 19)])
c.box(4, 8, 19, 9, 'P')                 # the cross street
c.box(4, 15, 10, 16, 'P')               # the lane to the orchard house
# the river at the wharf
c.box(16, 11, 21, 15, 'W')
for x, y in [(2, 2), (18, 2), (20, 2), (2, 16), (20, 18)]:
    c.tree(x, y)
for x, y in [(13, 3), (13, 4), (9, 11), (9, 12), (14, 17), (15, 16), (4, 12), (6, 17), (7, 17)]:
    c.at(x, y, '*')
PLANTER = 0x407
fixed = {(x, y): PLANTER for y in (3, 5) for x in range(4, 10)}

stamps = [('pc', 14, 4, 0), ('pet.house_brown', 3, 11, 1)]
SPEC = dict(
    folder='Opotiki', layout='LAYOUT_OPOTIKI', tileset='gTileset_Petalburg',
    rows=c.rows(), stamps=stamps, pc_warp=0, fixed=fixed,
    objects={'WharfOldMan': (15, 13, 'RIGHT'), 'Woman': (8, 11, None), 'Kid': (6, 6, None)},
    signs=[(14, 10, 'WharfSign')],
    hidden={},
    conns={'MAP_ROUTE35_B': 10 - 20, 'MAP_ROUTE2_BOP': 10 - 20},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
