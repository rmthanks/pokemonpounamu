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
    c = list(struct.unpack(f'<{len(raw) // 2}H', raw)); w = 44; h = len(c) // w
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

# ---- the Marine Parade (Sept 2026, second pass). The east edge was a column of
# walkable dense-tree tiles beside a strip of sea that ran straight into forest at
# both ends, with half trees at its corners. Now: a two-cell beach below the
# promenade, the sea two cells wider (so nothing past the map's edge is ever in
# view from the sand), whole trees at the corners, and the sea closed at the south
# the vanilla way (shore lip, canopy row, trees; Route 103). Its north end runs on
# into Route 2 Bay.
W2 = 46
out[42 * 44 + 35] = (out[42 * 44 + 35] & 0xFC00) | rk.TREE_TR    # the corner tree now has a neighbour
out[12 * 44 + 35] = out[11 * 44 + 35]           # a stray shore-lip tile sat in the promenade
strip = []
for y in range(44):
    row = '..'                                         # x34-35: the promenade, kept as it is
    row += 'TT' if y < 2 or y >= 40 else 'BB'          # x36-37
    row += 'S' * 8 if y < 40 else '_' * 8 if y < 42 else 'T' * 8   # x38-45: sea, shore grass (solid), bush
    strip.append(row)
sr = rk.from_ascii('AhuririParade', strip)
for y in range(44):
    for x in range(2):
        sr.put(x, y, out[y * 44 + 34 + x] & 0x3FF)
        sr.fix[(x, y)] = out[y * 44 + 34 + x]
cells2 = sr.render(seed=5)
wide = []
for y in range(44):
    base = out[y * 44:(y + 1) * 44][:36]
    extra = [cells2[y * 12 + x] for x in range(2, 12)]
    wide.extend(base + extra)
out, w = wide, W2

lay = LAYOUTS[LAYOUT]
open(os.path.join(ROOT, lay['blockdata_filepath']), 'wb').write(struct.pack(f'<{len(out)}H', *out))
lp = os.path.join(ROOT, 'data/layouts/layouts.json')
txt = open(lp).read()
i = txt.index(f'"id": "{LAYOUT}"')
for key, v in (('width', W2), ('height', 44)):
    j = txt.index(f'"{key}":', i)
    k = txt.index(',', j)
    txt = txt[:j] + f'"{key}": {v}' + txt[k:]
open(lp, 'w').write(txt)
print(f'Ahuriri now {W2}x44: garden strip along the south seam, Marine Parade beach on the east')
