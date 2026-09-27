#!/usr/bin/env python3
"""Otepoti / Dunedin - end of the line. Drawn with Ever Grande's tileset (Sept 2026).

The road down from Route 1 comes into the Octagon at the heart of town: the Pokemon
Center, Mart and Huka's gym round it, the student flats and the stone villa on the lane
by the harbour, and in the north-east, under the bush, the doors of the Pounamu League."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 40, 32
c = Canvas(W, H)
c.border()
c.box(14, 0, 17, 1, '.'); c.road([(15, 0), (15, 15)])            # from Route 1
c.box(4, 14, 35, 15, 'P')                                         # the main street
c.road([(22, 12), (22, 13)])                                      # to the gym
c.road([(31, 8), (31, 13)])                                       # the League approach
c.road([(6, 15), (6, 25)]); c.box(6, 24, 21, 25, 'P')             # the lane by the harbour
# Otago Harbour's inlet in the south-east
c.box(26, 19, 37, 25, 'W'); c.box(24, 28, 37, 29, 'T')
for x, y in [(2, 2), (8, 2), (20, 2), (2, 16), (10, 28), (16, 28), (22, 18), (18, 8)]:
    c.tree(x, y)
for x, y in [(4, 8), (5, 9), (10, 8), (11, 9), (24, 4), (25, 5), (34, 10), (35, 11), (8, 19), (9, 18),
             (17, 17), (18, 18), (26, 16), (27, 17), (12, 4), (13, 5)]:
    c.at(x, y, '*')

stamps = [('pc', 4, 10, 0), ('mart', 10, 10, 1), ('gym', 20, 7, 2), ('eg.league', 27, 2, 3),
          ('house4', 8, 20, 4), ('house5', 14, 20, 5)]
SPEC = dict(
    folder='Otepoti', layout='LAYOUT_OTEPOTI', tileset='gTileset_EverGrande',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    objects={'ColdWoman': (12, 17, None), 'GymKid': (24, 13, 'LEFT'), 'StudentMan': (12, 23, 'DOWN'),
             'Kid': (30, 17, None), 'SoundBoatman': (25, 21, 'RIGHT'), 'Kauri': (33, 9, 'DOWN'),
             'Awhi': (8, 16, 'DOWN'), 'PPounamu': (10, 5, 'RIGHT'), 'PRangi': (4, 17, 'RIGHT'),
             'PTia': (36, 16, 'LEFT'), 'PWiki': (23, 26, 'LEFT'), 'OPJOB': (3, 12, 'DOWN'),
             'LUGGAGEJOB': (17, 5, 'DOWN'), 'PAUAJOB': (25, 23, 'RIGHT')},
    signs=[(19, 12, 'GymSign')],
    hidden={},
    conns={'MAP_ROUTE1_SOUTH': 14 - 26},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
