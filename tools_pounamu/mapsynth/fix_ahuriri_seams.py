#!/usr/bin/env python3
"""Ahuriri seam repair (Sept 2026).

Ahuriri is drawn with the Mauville tileset; Orchard Road (south) and Route 2 Bay
(north) with Petalburg. The GBA draws a neighbouring map with the current map's
tileset, so Ahuriri's houses near its south edge turned to garbage when seen from
Orchard Road. Fix: eight new rows of Marine Parade gardens (primary tiles only)
along the south edge, so nothing tileset-specific is in view from the road. The
north seam is fixed on the other side: Route 2 Bay is drawn with Mauville too.
Idempotent: run once; it refuses to extend a map that is already 44 tall.
"""
import os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
import routekit as rk
from synth import LAYOUTS, read_cells, ROOT

LAYOUT = 'LAYOUT_AHURIRI_CITY'
import subprocess
w, h, c = read_cells(LAYOUT)
if h != 36:     # already extended: start again from the committed 44x36 original
    raw = subprocess.run(['git', 'show', 'a2046f27:data/layouts/AhuririCity/map.bin'], cwd=ROOT,
                         capture_output=True).stdout
    c = list(struct.unpack(f'<{len(raw) // 2}H', raw)); h = len(c) // w
    assert h == 36

rows = [
    # 0         1         2         3         4
    # 01234567890123456789012345678901234567890123
    "TT.....................................",
    "TT..............**..****..**...........",
    "TT..TT..................TT....TT.......",
    "TT..TT........WWWWWWWW..TT....TT.......",
    "TT............WWWWWWWW.................",
    "TT............WWWWWWWW.................",
    "TT..**........WWWWWWWW....**..**.......",
    "TT.....................................",
    "TTTTTT....TTTTTTTTTTTTTTTTTTTTTTTTTT...",
    "TTTTTT....TTTTTTTTTTTTTTTTTTTTTTTTTT...",
]
rows = [r[:37].ljust(37, '.') for r in rows]      # x0-36 drawn; x37-43 copied (shore, sea)
r = rk.from_ascii('AhuririGardens', [row + '.' * 7 for row in rows])
assert not r.snap_warnings, r.snap_warnings
cells = r.render(seed=3)
new = []
for y in range(10):
    line = []
    for x in range(44):
        if x >= 36:
            src = 34 if y < 8 else 34 + (y - 8)      # the old border rows' x36-43 (half tree, shore, sea)
            v = c[src * w + x] if y >= 8 else (c[33 * w + x] if x >= 37 else cells[y * 44 + x])
            line.append(v)
        elif 7 <= x <= 9 and y < 8:
            line.append(c[33 * w + x])                   # the white promenade carries on south
        else:
            line.append(cells[y * 44 + x])
    new.append(line)
out = list(c[:34 * w])
for line in new:
    out.extend(line)
lay = LAYOUTS[LAYOUT]
open(os.path.join(ROOT, lay['blockdata_filepath']), 'wb').write(struct.pack(f'<{len(out)}H', *out))
lp = os.path.join(ROOT, 'data/layouts/layouts.json')
txt = open(lp).read()
i = txt.index(f'"id": "{LAYOUT}"')
j = txt.index('"height":', i)
k = txt.index(',', j)
txt = txt[:j] + '"height": 44' + txt[k:]
open(lp, 'w').write(txt)
print('Ahuriri extended to 44x44 with a garden strip along the south seam')
