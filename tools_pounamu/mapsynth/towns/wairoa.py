#!/usr/bin/env python3
"""Wairoa - "where the river meets the sea". Drawn with Slateport's tileset (Sept 2026).

The Wairoa River widens into its mouth in the south-east of town with the white
lighthouse on its bank (Slateport's, its lantern set on grass), the keeper's house across
the road; the dairy (the River House) on the cross street where Awhi waits; the road runs
north to the East Cape and south to the Bay's checkpoint."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 24, 22
c = Canvas(W, H)
c.border()
# gaps: north to Route 2 East, south to Route 2 North
c.box(10, 0, 13, 1, '.'); c.box(10, 20, 13, 21, '.')
# the bush steps in at the corners
for x, y in [(2, 2), (2, 18), (20, 18), (20, 12)]:
    c.tree(x, y)
# the main road north to south, the cross street, and the lane to the keeper's house
c.road([(11, 0), (11, 21)])
c.box(4, 10, 19, 11, 'P')
c.box(5, 17, 12, 18, 'P')
# the river mouth, its bank under it
c.box(15, 13, 19, 15, 'W'); c.box(17, 16, 19, 16, 'W')
c.tree(6, 2)
# flowers: the PC's bed, the bank, the corners of the square
for x, y in [(3, 7), (3, 8), (4, 8), (9, 7), (9, 8), (14, 12), (15, 17), (16, 17), (15, 19), (18, 18), (17, 19), (8, 13), (9, 14), (13, 3), (4, 3), (5, 4)]:
    c.at(x, y, '*')

# (the Slateport buildings keep six rows clear of both roads: the routes beyond draw what
# they can see of Wairoa with their own tileset)
stamps = [('pc', 5, 6, 0),
          ('sl.house', 15, 6, 1),              # the dairy (River House)
          ('house5', 3, 12, 2),                # the lighthouse keeper
          ('sl.lighthouse', 13, 12, None)]
SPEC = dict(
    folder='Wairoa', layout='LAYOUT_WAIROA', tileset='gTileset_Slateport',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    objects={'Woman': (8, 16, 'LEFT'), 'Kid': (9, 12, None), 'OldMan': (13, 18, 'DOWN'),
             'Awhi': (19, 8, 'DOWN'), 'PUenuku': (9, 3, 'DOWN'), 'PWero': (20, 14, 'LEFT')},
    talk_trainers=('PWero',),      # fishing, back to the town: you go and talk to him
    signs=[(10, 9, 'TownSign')],
    hidden={0: (21, 17)},
    conns={'MAP_ROUTE2_NORTH': 10 - 16, 'MAP_ROUTE2_EAST': 10 - 18},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
