#!/usr/bin/env python3
"""Rotorua - the land breathes. Drawn with Lavaridge's tileset (Sept 2026).

Lake Rotorua along the north, the main street from Route 36 in the east, the Pokemon
Center, Mart and Whenua's gym between them; south of the street the steaming park with
its hot spring and sand bath among the rock, the Pohutu viewpoint in the south-east, the
Steam House and the Guide House side by side, and the road south to Taupo."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 40, 30
c = Canvas(W, H)
c.border()
# the lake: a deep west bay by Ohinemutu, the open water, the east shore
c.box(4, 2, 11, 6, 'W'); c.box(12, 2, 27, 4, 'W'); c.box(28, 2, 35, 5, 'W')
c.box(36, 2, 37, 9, 'T')
# the main street in from Route 36 (east, rows 14-15), the road south (x 21-22)
c.box(4, 14, 39, 15, 'P')
c.road([(21, 14), (21, 29)])
c.box(20, 28, 20, 29, '.'); c.box(23, 28, 23, 29, '.')
# the lane along the terrace
c.box(23, 22, 34, 23, 'P')
# the park: rock around the hot spring and the sand bath, a boardwalk in
c.box(2, 17, 5, 27, 'R'); c.box(6, 26, 15, 27, 'R'); c.box(2, 20, 3, 25, 'R')
c.box(10, 16, 11, 16, 'P')
# the viewpoint: tiered rock in the south-east, the geyser's pool below it
c.box(30, 25, 37, 27, 'R'); c.box(32, 26, 37, 27, 'R')
c.box(26, 26, 29, 27, 'T')
# trees
for x, y in [(2, 8), (2, 10), (36, 10), (36, 16), (36, 18), (14, 20), (16, 22), (18, 26), (24, 26), (2, 16)]:
    c.tree(x, y)
# flowers
for x, y in [(4, 8), (5, 8), (16, 6), (17, 6), (30, 7), (31, 7), (11, 11), (17, 12), (18, 12), (23, 17),
             (26, 17), (35, 24), (15, 18), (12, 23)]:
    c.at(x, y, '*')

stamps = [('pc', 6, 10, 0), ('mart', 12, 10, 1), ('gym', 22, 7, 2),
          ('house4', 30, 18, 3), ('house4', 26, 18, 4),
          ('lav.spring', 6, 17, None), ('lav.sandbath', 6, 22, None)]
SPEC = dict(
    folder='Rotorua', layout='LAYOUT_ROTORUA', tileset='gTileset_Lavaridge',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    objects={'PoolMan': (12, 20, 'LEFT'), 'StreetWoman': (16, 16, None), 'GymFan': (26, 13, 'UP'),
             'NoseKid': (15, 24, None), 'Kuia': (33, 23, 'DOWN'), 'Awhi': (13, 22, 'LEFT'),
             'PHana3': (14, 17, 'DOWN'), 'PToa': (34, 12, 'LEFT'), 'PIpo': (20, 6, 'UP'), 'RTJOB': (4, 12, 'DOWN')},
    signs=[(28, 24, 'GeyserSign')],
    hidden={0: (19, 24)},
    conns={'MAP_ROUTE36': 2, 'MAP_ROUTE5_POUNAMU': 20 - 20},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
