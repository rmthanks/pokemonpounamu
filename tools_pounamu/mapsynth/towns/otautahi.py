#!/usr/bin/env python3
"""Otautahi / Christchurch - the garden city, rebuilding (Sept 2026).

The road from Arthur's Pass (Route 7) runs south through Cathedral Square to the coast
road (Route 1). West of it the park and the hedged garden flat; east the i-SITE, Pou's
gym among the scaffolds, the rebuild house with the rubble still by its gate, and the
Avon curling through the east of town."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 40, 34
c = Canvas(W, H)
c.border()
c.box(18, 0, 21, 1, '.'); c.box(18, 32, 21, 33, '.')
c.road([(19, 0), (19, 33)])
c.box(4, 14, 35, 15, 'P')                                   # the main street
c.box(14, 16, 25, 22, 'P'); c.box(16, 17, 23, 20, '*')      # Cathedral Square and its beds
c.box(17, 18, 22, 19, '.')
c.box(4, 28, 35, 29, 'P')                                   # the lane south
c.road([(6, 15), (6, 29)]); c.road([(10, 22), (10, 29)])
c.box(15, 13, 16, 13, 'P'); c.box(24, 12, 25, 13, 'P')
# the Avon
c.box(28, 17, 35, 21, 'W'); c.box(32, 22, 35, 23, 'W')
for x, y in [(2, 2), (8, 2), (26, 2), (36, 2), (2, 18), (2, 30), (12, 30), (28, 30), (34, 30)]:
    c.tree(x, y)
for x, y in [(4, 8), (5, 9), (12, 8), (13, 7), (26, 5), (27, 6), (28, 23), (29, 24), (14, 24), (15, 25),
             (36, 22), (37, 23), (3, 22), (4, 23)]:
    c.at(x, y, '*')
fixed = {}
BOULDER = [0x093, 0x094, 0x09B, 0x09C]
for i, (dx, dy) in enumerate([(0, 0), (1, 0), (0, 1), (1, 1)]):
    fixed[(34 + dx, 11 + dy)] = BOULDER[i] | 0x400      # quake rubble by the rebuild house

stamps = [('pc', 4, 10, 0), ('mart', 10, 10, 1), ('gym', 22, 7, 2), ('house5', 14, 9, 3),
          ('house4', 30, 10, 4), ('pet.garden_house', 8, 17, 5), ('pet.house_big', 22, 23, 6)]
SPEC = dict(
    folder='Otautahi', layout='LAYOUT_OTAUTAHI', tileset='gTileset_Petalburg',
    rows=c.rows(), stamps=stamps, pc_warp=0, fixed=fixed,
    objects={'RebuildWoman': (29, 13, 'DOWN'), 'GymKid': (24, 13, 'UP'), 'CathedralMan': (21, 23, 'DOWN'),
             'Kid': (12, 17, None), 'QuakeMan': (34, 13, 'UP'), 'Hori': (13, 26, None),
             'PEru': (4, 25, 'RIGHT'), 'PHemi': (36, 26, 'LEFT'), 'PKiri': (12, 16, 'RIGHT'),
             'PMahina': (3, 16, 'RIGHT'), 'PNiko': (36, 16, 'LEFT'), 'OTJOB': (8, 5, 'DOWN')},
    signs=[(21, 12, 'GymSign'), (15, 23, 'CathedralSign')],
    hidden={},
    conns={'MAP_ROUTE7_POUNAMU': 18 - 20, 'MAP_ROUTE1_SOUTH': 18 - 22},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
