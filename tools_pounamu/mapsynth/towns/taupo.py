#!/usr/bin/env python3
"""Taupo - the town on the great lake (Sept 2026).

The road down from Rotorua (Route 5) meets the main street, which runs east over the
ranges (shut by the Mob) and turns south onto the Desert Road. The Pokemon Center, Mart,
the anglers' lodge and the skydivers' flat line the street; Lake Taupo fills the south-west,
its shore where the boatman waits."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 32, 26
c = Canvas(W, H)
c.border()
c.box(14, 0, 17, 1, '.'); c.road([(15, 0), (15, 12)])          # from Route 5
c.box(4, 12, 31, 13, 'P')                                        # the main street, east to the ranges
c.box(24, 24, 25, 25, 'P'); c.road([(24, 12), (24, 25)])         # south: the Desert Road
c.box(4, 11, 5, 11, 'P'); c.box(10, 11, 11, 11, 'P'); c.box(20, 11, 21, 11, 'P'); c.box(24, 11, 25, 11, 'P')
# Lake Taupo and its shore
c.box(2, 16, 19, 21, 'W'); c.box(2, 22, 19, 23, '.')
c.box(2, 16, 5, 17, '.'); c.box(15, 20, 19, 21, '.')      # the shore bends
c.box(12, 16, 19, 16, '.'); c.box(8, 22, 13, 22, 'W')      # a bay under the town, a cove in the south
c.box(26, 14, 29, 23, 'T'); c.box(28, 2, 31, 9, 'T')
for x, y in [(2, 2), (8, 2), (20, 2), (22, 2), (2, 14)]:
    c.tree(x, y)
for x, y in [(8, 5), (9, 6), (17, 5), (18, 4), (6, 14), (7, 15), (12, 14), (13, 15), (22, 15), (23, 16), (26, 11), (27, 10)]:
    c.at(x, y, '*')

stamps = [('pc', 4, 7, 0), ('mart', 10, 7, 1), ('pet.house_big', 18, 6, 2), ('house4', 24, 7, 3)]
SPEC = dict(
    folder='Taupo', layout='LAYOUT_TAUPO', tileset='gTileset_Petalburg',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    objects={'LakeMan': (12, 15, 'DOWN'), 'StreetWoman': (17, 14, None), 'GateOldMan': (29, 11, 'LEFT'),
             'Kid': (21, 15, None), 'LakeBoatman': (8, 15, 'DOWN'), 'Tawhai': (3, 23, 'RIGHT'),
             'Hori': (18, 23, None), 'PKiwa': (5, 15, 'RIGHT'), 'PMarara': (14, 9, 'RIGHT'),
             'PAmiria': (7, 4, 'RIGHT'), 'PHakopa': (15, 22, 'LEFT'), 'TPJOB': (22, 4, 'DOWN')},
    signs=[(10, 14, 'LakeSign')],
    hidden={0: (4, 22)},
    conns={'MAP_ROUTE5_POUNAMU': 14 - 22, 'MAP_ROUTE5_RANGES': 0, 'MAP_ROUTE1_DESERT': 24 - 18},
    script_edits=[('data/maps/RuapehuAscent/scripts.inc', 'warp MAP_TAUPO, 4, 13', 'warp MAP_TAUPO, 6, 13')],
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
