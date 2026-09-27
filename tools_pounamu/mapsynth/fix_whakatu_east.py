#!/usr/bin/env python3
"""Whakatu's east edge (Sept 2026): Route 7 connects to Whakatu's right side, but
that side was a solid wall of trees - the Lewis Pass road couldn't be entered from
Whakatu at all. Open a two-row gap (rows 12-13, on the tree lattice) and give the
trees above and below it their open-side tiles. Idempotent."""
import os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
import routekit as rk
from synth import LAYOUTS, read_cells, ROOT

LAYOUT = 'LAYOUT_WHAKATU'
w, h, c = read_cells(LAYOUT)
def put(x, y, m):
    c[y * w + x] = rk.val(m)
for y in (12, 13):
    for x in (30, 31):
        put(x, y, rk.GRASS)
put(30, 11, rk.TREE_BL_OPENSIDE); put(31, 11, rk.TREE_BR_OPENB)     # ground opens below
put(30, 14, rk.TREE_TL_OPEN)                                         # and above, on the town side
lay = LAYOUTS[LAYOUT]
open(os.path.join(ROOT, lay['blockdata_filepath']), 'wb').write(struct.pack(f'<{len(c)}H', *c))
print('Whakatu: east gap opened at rows 12-13')
