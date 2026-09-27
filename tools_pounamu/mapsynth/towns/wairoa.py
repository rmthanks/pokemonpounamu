#!/usr/bin/env python3
"""Wairoa - "where the river meets the sea". A river town drawn the Oldale way (Sept 2026).

The Wairoa River widens into its mouth in the south-east of town, with the lighthouse
keeper's house across the lane from it; the dairy (the River House) sits behind its hedge
on the cross street where Awhi waits; the road runs north to the East Cape and south to
the Bay's checkpoint."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 24, 22
c = Canvas(W, H)
c.border()
# gaps: north to Route 2 East, south to Route 2 North
c.box(10, 0, 13, 1, '.'); c.box(10, 20, 13, 21, '.')
# the bush steps in at the corners
for x, y in [(2, 2), (2, 18), (20, 18), (20, 10)]:
    c.tree(x, y)
# the main road north to south, the cross street, and the lane to the keeper's house
c.road([(11, 0), (11, 21)])
c.box(4, 9, 19, 10, 'P')
c.box(5, 17, 12, 18, 'P')
# the river mouth, its bank under it
c.box(15, 12, 20, 14, 'W'); c.box(17, 15, 20, 16, 'W')
c.tree(6, 2)
# flowers: the PC's bed, the bank, the corners of the square
for x, y in [(3, 6), (3, 7), (4, 7), (9, 6), (9, 7), (14, 11), (15, 16), (16, 16), (15, 18), (18, 18), (17, 19), (8, 12), (9, 13), (13, 3), (4, 3), (5, 4)]:
    c.at(x, y, '*')

stamps = [('pc', 5, 5, 0),
          ('pet.garden_house', 14, 3, 1),      # the dairy (River House)
          ('pet.house_big', 3, 12, 2)]         # the lighthouse keeper
SPEC = dict(
    folder='Wairoa', layout='LAYOUT_WAIROA', tileset='gTileset_Petalburg',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    objects={'Woman': (8, 16, 'LEFT'), 'Kid': (7, 11, None), 'OldMan': (13, 18, 'DOWN'),
             'Awhi': (13, 7, 'DOWN'), 'PUenuku': (9, 3, 'DOWN'), 'PWero': (14, 14, 'RIGHT')},
    talk_trainers=('PWero',),      # fishing, back to the town: you go and talk to him
    signs=[(10, 7, 'TownSign')],
    hidden={0: (21, 17)},
    conns={'MAP_ROUTE2_NORTH': 10 - 16, 'MAP_ROUTE2_EAST': 10 - 18},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
