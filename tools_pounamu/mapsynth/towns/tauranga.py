#!/usr/bin/env python3
"""Tauranga - the port under Mauao. Drawn with Slateport's tileset (Sept 2026).

The road from Rotorua (Route 36) comes in from the west along the main street: Pokemon
Center, Mart and Mua's gym on its north side, the port house, the bach and the house
under the mountain on the south. East of town the beach runs round the harbour to Mauao
itself, yachts on their moorings. South, the coast road to Opotiki (Route 2)."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 40, 34
c = Canvas(W, H)
c.border()
# the main street in from Route 36 (west, rows 16-17) to the beach; the road south (x 7-8)
c.box(0, 16, 23, 17, 'P')
c.box(6, 32, 9, 33, '.'); c.road([(7, 17), (7, 33)])
c.box(3, 25, 22, 26, 'P')                          # the lane past the houses
# the beach round the harbour, the sea open to the east
c.box(22, 8, 31, 29, 'B')
c.box(32, 8, 39, 27, 'S')
# Mauao: the mountain at the harbour mouth, tiered rock, beach at its foot
c.box(32, 2, 39, 7, 'T'); c.box(32, 6, 33, 7, 'B')
c.box(24, 2, 31, 7, 'R'); c.box(25, 3, 30, 6, 'Q')
# the south end of the harbour: grass shore nobody walks, behind a blocker tree
c.box(22, 30, 39, 33, 'T'); c.box(30, 28, 31, 29, 'T'); c.box(32, 28, 39, 29, '_')
# trees and flowers
for x, y in [(2, 2), (8, 2), (14, 2), (20, 2), (2, 28), (12, 28), (18, 28)]:
    c.tree(x, y)
for x, y in [(4, 10), (5, 11), (10, 10), (11, 11), (22, 10), (23, 11), (14, 19), (15, 20), (10, 29), (11, 30),
             (20, 22), (21, 23), (4, 5), (5, 6)]:
    c.at(x, y, '*')

stamps = [('pc', 6, 12, 0), ('mart', 12, 12, 1), ('gym', 16, 7, 2),
          ('house4', 2, 21, 5), ('sl.house', 11, 21, 4), ('sl.clubhouse', 16, 20, 3)]
SPEC = dict(
    folder='Tauranga', layout='LAYOUT_TAURANGA', tileset='gTileset_Slateport',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    overlays=[('sl.boat', 34, 11), ('sl.dinghy', 33, 21), ('sl.boat', 37, 17)],
    objects={'GymKid': (20, 13, 'UP'), 'MauaoMan': (27, 8, 'UP'), 'StreetWoman': (14, 18, None),
             'PondMan': (31, 20, 'RIGHT'), 'SurfKid': (24, 24, None), 'PIrirangi': (11, 27, 'LEFT'),
             'PKereama': (30, 15, 'LEFT'), 'PMereana': (13, 5, 'DOWN'), 'TGJOB': (4, 14, 'DOWN')},
    signs=[(17, 14, 'GymSign'), (23, 9, 'MauaoSign')],
    solid=[(32, 6), (33, 6), (32, 7), (33, 7)],     # the sand where the beach wraps the harbour's corner
    hidden={},
    conns={'MAP_ROUTE2_BOP': 6 - 18, 'MAP_ROUTE36': 4},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
