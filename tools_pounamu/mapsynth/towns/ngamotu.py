#!/usr/bin/env python3
"""Ngamotu / New Plymouth - under the mountain. Drawn with Slateport's tileset (Sept 2026).

The road from the Forgotten World Highway (Route 43) runs down through town to the coast
road south (Route 3). The Pokemon Center and Mart on the main street, the Wind Gallery
(Slateport's dome) across from them, the surf house and the gardener's house by the park
with its lake."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 32, 26
c = Canvas(W, H)
c.border()
c.box(6, 0, 9, 1, '.'); c.box(6, 24, 9, 25, '.')
c.road([(7, 0), (7, 25)])
c.box(2, 12, 27, 13, 'P')                                        # the main street
c.box(4, 11, 5, 11, 'P'); c.box(12, 11, 13, 11, 'P'); c.box(20, 10, 21, 11, 'P')
c.box(9, 20, 27, 21, 'P')                                        # the lane by the park
# Pukekura Park: the lake among the trees
c.box(14, 15, 23, 18, 'W')
c.box(14, 17, 15, 18, '.'); c.box(22, 15, 23, 16, '.')   # its shore wanders
for x, y in [(2, 2), (24, 2), (26, 4), (2, 18), (26, 22), (12, 22), (20, 22), (12, 14), (24, 16)]:
    c.tree(x, y)
for x, y in [(10, 5), (11, 6), (3, 15), (4, 16), (24, 14), (25, 15), (14, 22), (15, 23), (23, 9), (24, 8)]:
    c.at(x, y, '*')

stamps = [('pc', 3, 7, 0), ('mart', 11, 7, 1), ('sl.dome', 18, 6, 2), ('sl.house', 9, 16, 3), ('house4', 26, 16, 4)]
SPEC = dict(
    folder='Ngamotu', layout='LAYOUT_NGAMOTU', tileset='gTileset_Slateport',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    objects={'MountainMan': (16, 10, 'DOWN'), 'StreetWoman': (14, 14, None), 'GymKid': (23, 11, 'LEFT'),
             'SurfKid': (5, 21, None)},
    signs=[(9, 11, 'TaranakiSign')],
    hidden={},
    conns={'MAP_ROUTE43_POUNAMU': 6 - 20, 'MAP_ROUTE3_POUNAMU': 6 - 26},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
