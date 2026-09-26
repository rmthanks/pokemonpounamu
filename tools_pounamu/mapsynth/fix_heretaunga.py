#!/usr/bin/env python3
"""Heretaunga hedge + tree repair (Sept 2026).

The Petalburg tileset's leafy 'hedge top' tiles (0x24D/0x24E/0x255/0x256) are
really TREE BOTTOMS with a hedge rim painted beneath; they only work directly
under a row of tree tops. Heretaunga used them as free-standing hedge tops,
which showed as floating half-trees. This rebuilds every enclosure from the
free-standing hedge kit (verified by render in mapsynth/hedge notes):

  vertical run      0x23F top cap, 0x24C middle, 0x254 bottom end
  box top edge      0x244 left corner, 0x245 run, 0x246 right corner
  closed box bottom 0x267 0x23D.. 0x266  over  0x264 0x245.. 0x265
  free horizontal   0x23C 0x23D.. 0x23E  over  0x264 0x245.. 0x265

and repairs the forest lattice (trees are 2x2: 0x1D4 0x1D5 over 0x1DC 0x1DD,
x even = left half, y even = top half on this map).
Run once from the repo root: python3 tools_pounamu/mapsynth/fix_heretaunga.py
"""
import json, os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from synth import ROOT, LAYOUTS

lay = LAYOUTS['LAYOUT_HERETAUNGA_TOWN']
W, H = lay['width'], lay['height']
path = os.path.join(ROOT, lay['blockdata_filepath'])
c = list(struct.unpack(f'<{W*H}H', open(path, 'rb').read()))

BLOCK = 0x400          # collision 1, elevation 0 (as the existing hedges/trees)
GRASS, FLOWER, SAND = 0x3001, 0x3004, 0x3129
def hedge(m): return m | BLOCK
def put(x, y, v): c[y*W + x] = v
def get(x, y): return c[y*W + x] & 0x3FF

TL, TR, BL, BR = 0x1D4, 0x1D5, 0x1DC, 0x1DD
def tree_cell(x, y):
    return hedge((TL if x % 2 == 0 else TR) if y % 2 == 0 else (BL if x % 2 == 0 else BR))

def open_front_box(x0, x1, ytop, ybot, gaps=(), front=None):
    """Hedge on top + both sides, open at the bottom (sides end with 0x254 at ybot).
    front: {x: value} for the cells between the side ends on row ybot."""
    put(x0, ytop, hedge(0x244)); put(x1, ytop, hedge(0x246))
    for x in range(x0 + 1, x1):
        if x not in gaps:
            put(x, ytop, hedge(0x245))
    for y in range(ytop + 1, ybot):
        put(x0, y, hedge(0x24C)); put(x1, y, hedge(0x24C))
    put(x0, ybot, hedge(0x254)); put(x1, ybot, hedge(0x254))
    for x, v in (front or {}).items():
        put(x, ybot, v)

# ---- Pokemon Centre (x19-26, y6-11): open front, door path at x22 ----
open_front_box(19, 26, 6, 11, front={20: FLOWER, 21: GRASS, 23: GRASS, 24: GRASS, 25: FLOWER})
# ---- Mart (x31-37, y6-11): door path at x33 ----
open_front_box(31, 37, 6, 11, front={32: FLOWER, 34: GRASS, 35: GRASS, 36: FLOWER})
# ---- north-east homes (x44-57, y2-14): top edge under the tree line, front opens onto the road ----
open_front_box(44, 57, 2, 14, front={x: SAND for x in range(45, 57)})
# ---- pond (x2-12, y29-37): opening x8-11 (stepping stones + the job-06 pen gate); tree line closes the bottom ----
open_front_box(2, 12, 29, 37, gaps=(8, 9, 10, 11), front={x: get(x, 37) | 0 for x in range(3, 12)})
put(9, 29, GRASS)         # the opening: stones at x8 stay, the rest is grass
for x in range(3, 12):   # keep the pond's own row-37 tiles (grass/flowers), walkable
    v = c[37*W + x]
    if (v >> 10) & 3:
        put(x, 37, GRASS)
# ---- garden (x16-26, y28-37): closed box, entrance gap at x21 on top ----
put(16, 28, hedge(0x244)); put(26, 28, hedge(0x246))
for x in range(17, 26):
    put(x, 28, GRASS if x == 21 else hedge(0x245))
for y in range(29, 36):
    put(16, y, hedge(0x24C)); put(26, y, hedge(0x24C))
put(16, 36, hedge(0x267)); put(26, 36, hedge(0x266))
put(16, 37, hedge(0x264)); put(26, 37, hedge(0x265))
for x in range(17, 26):
    put(x, 36, hedge(0x23D)); put(x, 37, hedge(0x245))
# ---- orchard (x42-57, y24-37): entrance gap at x44; the tree line closes the bottom ----
open_front_box(42, 57, 24, 37, gaps=(44,), front={x: GRASS for x in range(43, 57)})
put(44, 24, GRASS)

# ---- forest lattice repairs ----
for y in (0, 1):                       # north exit is x28-29 only; x30-31 is a whole tree
    put(30, y, tree_cell(30, y))
for x in (58, 59):                     # east column rows 9-10 were out of phase
    for y in (9, 10):
        put(x, y, tree_cell(x, y))
for x in (0, 1):                       # west opening is rows 32-35: no orphan tree top above it
    put(x, 32, GRASS)
for x in range(2, 14):                 # south tree line restored under the pond
    put(x, 38, tree_cell(x, 38))

# ---- verify: every tree tile sits in a complete 2x2 tree ----
bad = []
for y in range(H):
    for x in range(W):
        m = get(x, y)
        if m in (TL, TR, BL, BR):
            dx = 0 if m in (TL, BL) else -1
            dy = 0 if m in (TL, TR) else -1
            ox, oy = x + dx, y + dy
            want = {(ox, oy): TL, (ox + 1, oy): TR, (ox, oy + 1): BL, (ox + 1, oy + 1): BR}
            for (px, py), t in want.items():
                if 0 <= px < W and 0 <= py < H and get(px, py) != t:
                    bad.append((x, y))
                    break
# the map's top/bottom rows may show half trees that continue past the edge; allow those
bad = [(x, y) for x, y in bad if 0 < y < H - 1]
leftover_rims = [(x, y) for y in range(H) for x in range(W) if get(x, y) in (0x24D, 0x24E, 0x255, 0x256)]
if bad or leftover_rims:
    raise SystemExit(f'incomplete trees at {bad}; stray rim tiles at {leftover_rims}')
open(path, 'wb').write(struct.pack(f'<{W*H}H', *c))
print('Heretaunga repaired: 0 broken trees, 0 floating rim tiles')
