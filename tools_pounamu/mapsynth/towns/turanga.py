#!/usr/bin/env python3
"""Turanga - first to see the sun. Drawn with Dewford's tileset (Sept 2026).

A beach town on Poverty Bay: sand streets, the blue-roofed houses of a fishing town,
the Kapa Haka Hall on the square, the harbour on the east with its jetty, and the
Hikurangi track leaving town past the kaitiaki (who isn't letting anyone up yet).
North to the East Cape (Route 35), south to Wairoa (Route 2)."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 40, 26
c = Canvas(W, H, fill='B')
c.border()
# roads: north to the Cape (x 12-13), south to Wairoa (gap x 12-15, road 13-14)
# grass along the back of town and in the corners
c.box(2, 2, 27, 4, '.'); c.box(2, 22, 23, 23, '.'); c.box(2, 2, 3, 23, '.')
c.road([(12, 0), (12, 5)])
c.box(12, 24, 15, 25, '.'); c.road([(13, 19), (13, 25)])
# the harbour: sea on the east; beach wraps its north-west corner, bush beyond;
# at its south end a grass shore nobody walks, behind a blocker tree
c.box(28, 8, 39, 19, 'S')
c.box(28, 2, 39, 7, 'T'); c.box(28, 6, 29, 7, 'B')
c.box(24, 20, 39, 25, 'T'); c.box(24, 20, 25, 21, 'B'); c.box(28, 20, 39, 21, '_')
c.box(26, 2, 27, 5, 'T')
# the Hikurangi track: a path west into the bush, the kaitiaki standing on it
c.box(2, 12, 5, 13, 'P'); c.box(2, 10, 3, 11, 'T'); c.box(2, 14, 3, 15, 'T')
# trees in town
for x, y in [(8, 2), (22, 2), (2, 4), (2, 20), (18, 22), (8, 22), (4, 22), (20, 22)]:
    c.tree(x, y)
# flowers on the grass verges
for x, y in [(4, 2), (5, 3), (16, 2), (17, 3), (10, 22), (11, 23), (16, 22), (17, 23), (24, 3), (25, 2)]:
    c.at(x, y, '*')

stamps = [('pc', 4, 3, 0), ('mart', 16, 3, 1), ('dew.house', 22, 12, 2),
          ('dew.house2', 6, 15, 3), ('dew.hall', 15, 12, 4), ('house4', 17, 17, 5)]
SPEC = dict(
    folder='Turanga', layout='LAYOUT_TURANGA', tileset='gTileset_Dewford',
    rows=c.rows(), stamps=stamps, pc_warp=0, fixed_class='B',
    jetties=[(28, 13, 4)],
    objects={'Kaitiaki': (4, 12, 'RIGHT'), 'Roadworks': (14, 5, 'LEFT'), 'MainStreetWoman': (10, 11, None),
             'HarbourMan': (31, 13, 'RIGHT'), 'SunKid': (24, 17, None)},
    signs=[(25, 10, 'Museum'), (6, 11, 'TrackSign'), (10, 7, 'TownSign')],
    hidden={0: (23, 21)},
    conns={'MAP_ROUTE2_EAST': 12 - 20, 'MAP_ROUTE35_A': 12 - 32},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
