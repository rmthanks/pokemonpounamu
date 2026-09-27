#!/usr/bin/env python3
"""Waitohi's harbour (Sept 2026): the water ran down to the south edge beside a
column of half trees (x21). Widen the water by that column so its east side is a
proper pond edge, and so it lines up with Queen Charlotte Sound on Route 6 (which
carries the same water on across the seam). Idempotent."""
import os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
import routekit as rk
from synth import LAYOUTS, read_cells, ROOT

LAYOUT = 'LAYOUT_WAITOHI'
w, h, c = read_cells(LAYOUT)
P = rk.POND
def put(x, y, m):
    c[y * w + x] = m | 0x1000
put(20, 11, P['t']); put(21, 11, P['tr'])
for y in range(12, h):
    put(20, y, P['c']); put(21, y, P['r'])
lay = LAYOUTS[LAYOUT]
open(os.path.join(ROOT, lay['blockdata_filepath']), 'wb').write(struct.pack(f'<{len(c)}H', *c))
print('Waitohi: harbour widened to the east edge')
