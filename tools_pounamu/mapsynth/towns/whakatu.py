#!/usr/bin/env python3
"""Whakatu / Nelson - the sunny city (Sept 2026).

Down from the Sounds (Route 6) the road meets the main street, which runs east into the
Buller valley (Route 7). Pokemon Center, Mart and Roto's gym on the street; the sun house
among its flower gardens, the boulder house by its heap of Boulder Bank stones, and the
hill with the bush over it in the south-east."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 32, 26
c = Canvas(W, H)
c.border()
c.box(14, 0, 17, 1, '.'); c.road([(15, 0), (15, 13)])            # from Route 6
c.box(4, 12, 31, 13, 'P')                                         # the main street, east to Route 7
c.box(4, 11, 5, 11, 'P'); c.box(10, 11, 11, 11, 'P'); c.box(22, 10, 23, 11, 'P')
c.box(4, 21, 23, 22, 'P'); c.road([(8, 13), (8, 22)])             # the lane south
# the hill in the south-east
c.box(24, 16, 29, 23, 'R'); c.box(25, 17, 28, 22, 'Q'); c.box(24, 14, 29, 15, 'T')
for x, y in [(2, 2), (8, 2), (26, 2), (28, 4), (2, 14), (12, 14), (2, 22)]:
    c.tree(x, y)
for x, y in [(3, 17), (4, 17), (5, 18), (3, 19), (4, 19), (15, 17), (16, 18), (9, 6), (10, 5),
             (18, 7), (19, 8), (28, 10), (29, 11), (20, 15), (21, 16)]:
    c.at(x, y, '*')
fixed = {}
BOULDER = [0x093, 0x094, 0x09B, 0x09C]
for i, (dx, dy) in enumerate([(0, 0), (1, 0), (0, 1), (1, 1)]):
    fixed[(22 + dx, 17 + dy)] = BOULDER[i] | 0x400      # Boulder Bank stones

stamps = [('pc', 4, 7, 0), ('mart', 10, 7, 1), ('gym', 19, 4, 2), ('house5', 10, 16, 3), ('house4', 17, 16, 4)]
SPEC = dict(
    folder='Whakatu', layout='LAYOUT_WHAKATU', tileset='gTileset_Petalburg',
    rows=c.rows(), stamps=stamps, pc_warp=0, fixed=fixed,
    objects={'SunWoman': (15, 15, None), 'GymKid': (21, 11, 'UP'), 'ArtWoman': (6, 18, 'DOWN'),
             'Kid': (14, 23, None), 'Awhi': (17, 14, 'DOWN'), 'PWaimarama': (27, 8, 'LEFT'),
             'PWhina': (5, 23, 'RIGHT'), 'PAputa': (18, 9, 'RIGHT'), 'WKJOB': (6, 4, 'DOWN')},
    signs=[(17, 11, 'GymSign')],
    hidden={0: (23, 23)},
    conns={'MAP_ROUTE6_POUNAMU': 14 - 22, 'MAP_ROUTE7_POUNAMU': 0},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
