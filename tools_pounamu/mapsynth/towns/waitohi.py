#!/usr/bin/env python3
"""Waitohi / Picton - gateway to Te Waipounamu (Sept 2026).

Off the Interislander at the head of Queen Charlotte Sound: the ferry terminal on the
quay (Littleroot's long hall), the harbour basin that runs on south into the Sound
(Route 6), the Pokemon Center and the ferry cottage on the road south to Whakatu."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 24, 22
c = Canvas(W, H)
c.border()
# the road south (gap x 6-9), the quay in front of the terminal, the lane to the houses
c.box(6, 20, 9, 21, '.'); c.road([(7, 9), (7, 21)])
c.box(2, 10, 11, 11, 'P')
c.box(2, 17, 11, 18, 'P')
# the harbour basin and the channel south into Queen Charlotte Sound (Route 6)
c.box(13, 2, 21, 9, 'W'); c.box(14, 10, 19, 21, 'W')
c.box(20, 12, 21, 21, 'T'); c.box(12, 18, 13, 21, 'T')
# bush and flowers
for x, y in [(2, 2), (10, 2)]:
    c.tree(x, y)
for x, y in [(4, 12), (5, 12), (12, 12), (12, 13), (6, 15), (2, 19), (3, 19), (10, 19), (11, 19)]:
    c.at(x, y, '*')

stamps = [('pc', 9, 13, 0), ('pet.lab', 3, 4, 1), ('pet.house_brown', 2, 13, 2)]
SPEC = dict(
    folder='Waitohi', layout='LAYOUT_WAITOHI', tileset='gTileset_Petalburg',
    rows=c.rows(), stamps=stamps, pc_warp=0, pond_open_bottom=True,
    objects={'Ferryman': (9, 9, 'LEFT'), 'Woman': (13, 14, 'RIGHT'), 'Kid': (4, 19, None)},
    signs=[(11, 9, 'Sign')],
    hidden={},
    conns={'MAP_ROUTE6_POUNAMU': 6 - 16},
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
