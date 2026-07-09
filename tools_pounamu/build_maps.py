#!/usr/bin/env python3
"""Compose Pounamu's from-scratch maps by sampling full map.bin cells
(metatile+collision+elevation) from vanilla reference layouts."""
import json, struct, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LAYOUTS = json.load(open(f'{ROOT}/data/layouts/layouts.json'))

def load(lid):
    l = next(x for x in LAYOUTS['layouts'] if x['id'] == lid)
    raw = open(f"{ROOT}/{l['blockdata_filepath']}", 'rb').read()
    return l, list(struct.unpack(f"<{len(raw)//2}H", raw))

LT, lt = load('LAYOUT_LITTLEROOT_TOWN')
R101, r101 = load('LAYOUT_ROUTE101')
LH1, h1 = load('LAYOUT_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F')
LH2, h2 = load('LAYOUT_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F')

def cell(src, l, x, y):
    return src[y*l['width']+x]

def block(src, l, x0, y0, w, h):
    return [[cell(src, l, x0+dx, y0+dy) for dx in range(w)] for dy in range(h)]

# ---- exterior palette (full u16 values) ----
GRASS   = cell(lt, LT, 11, 11)   # 001 plain
SAND    = cell(lt, LT, 5, 9)     # 201 sandy patch/path
FLOWER  = (GRASS & 0xFC00) | 0x004  # red flowers
TALL    = (GRASS & 0xFC00) | 0x00D  # tall grass (encounters)
TUFT_A  = FLOWER
TUFT_B  = FLOWER
TREE_TL = cell(lt, LT, 0, 0); TREE_TR = cell(lt, LT, 1, 0)
TREE_BL = cell(lt, LT, 0, 19); TREE_BR = cell(lt, LT, 1, 19)
HOUSE_L = block(lt, LT, 2, 4, 5, 5)    # small house, door at local col 3 bottom
HOUSE_R = block(lt, LT, 13, 4, 5, 5)   # mirrored house, door at local col 1 bottom

def tree_row(g, x0, y, n, gap=0):
    """Row of 2x2 trees starting at x0, top row y."""
    x = x0
    for i in range(n):
        put(g, x, y,   [[TREE_TL, TREE_TR]])
        put(g, x, y+1, [[TREE_BL, TREE_BR]])
        x += 2 + gap

def put(g, x0, y0, rows):
    for dy, row in enumerate(rows):
        for dx, v in enumerate(row):
            g[y0+dy][x0+dx] = v

def fill(g, x0, y0, w, h, v):
    for y in range(y0, y0+h):
        for x in range(x0, x0+w):
            g[y][x] = v

def ring_trees(g, W, H):
    for x in range(0, W, 2):
        put(g, x, 0, [[TREE_TL, TREE_TR], [TREE_BL, TREE_BR]])
        put(g, x, H-2, [[TREE_TL, TREE_TR], [TREE_BL, TREE_BR]])
    for y in range(0, H, 2):
        put(g, 0, y, [[TREE_TL, TREE_TR], [TREE_BL, TREE_BR]])
        put(g, W-2, y, [[TREE_TL, TREE_TR], [TREE_BL, TREE_BR]])

# ---- extra sampled blocks (Oldale/Petalburg) ----
LO, lo = load('LAYOUT_OLDALE_TOWN')
PC_BLOCK   = block(lo, LO, 5, 13, 4, 4)   # door local (1,3)
MART_BLOCK = block(lo, LO, 13, 3, 4, 4)   # door local (1,3)
MART_BLOCK[0][3] = (MART_BLOCK[0][3] & 0xFC00) | 0x02A  # clean roof corner (Oldale's had tree overlap)
OHOUSE     = block(lo, LO, 4, 4, 4, 4)    # oldale-style house, door local (1,3)
HEDGE      = 0x0644                        # shelterbelt hedge (collision 1, from Petalburg)
LP, lp = load('LAYOUT_PETALBURG_CITY')
BERRY_SOIL = 0x368D                        # soft soil under berry trees (Route 102 sample)

# ================= HERETAUNGA TOWN (40 x 28) — Hastings =================
W, H = 40, 28
g = [[GRASS]*W for _ in range(H)]
ring_trees(g, W, H)
# North exit toward Ahuriri (x19-21)
fill(g, 19, 0, 3, 2, GRASS)
# Main roads
fill(g, 19, 2, 2, 12, SAND)          # vertical from north exit
fill(g, 4, 13, 31, 1, SAND)          # main east-west road
fill(g, 31, 14, 1, 2, SAND)          # spur to orchard gate
fill(g, 31, 9, 1, 4, SAND)           # spur up to homestead door
fill(g, 8, 8, 1, 5, SAND)            # spur to west houses
fill(g, 8, 8, 4, 1, SAND)
# West side — Flaxmere rows
put(g, 3, 3, HOUSE_L)                # door (6,7)
fill(g, 6, 8, 1, 1, SAND)
put(g, 3, 9, OHOUSE)                 # door (4,12)
fill(g, 4, 13, 1, 1, SAND)
put(g, 3, 16, HOUSE_R)               # door (4,20)
fill(g, 4, 21, 1, 1, SAND)
put(g, 3, 22, OHOUSE)                # door (4,25)
# Town square: Pokemon Center + Mart flank the crossroads
put(g, 13, 9, PC_BLOCK)              # door (14,12)
fill(g, 14, 13, 1, 1, SAND)
put(g, 22, 9, MART_BLOCK)            # door (23,12)
fill(g, 23, 13, 1, 1, SAND)
for (x, y) in [(12,14),(26,14),(18,15),(22,15)]:
    g[y][x] = FLOWER
# Homestead — NE, above the orchard
put(g, 28, 4, HOUSE_L)               # door (31,8)
# The orchard — fenced with shelterbelt hedges, SE outskirts
ox0, oy0, ox1, oy1 = 26, 16, 38, 26  # perimeter
for x in range(ox0, ox1+1):
    g[oy0][x] = HEDGE
    g[oy1][x] = HEDGE
for y in range(oy0, oy1+1):
    g[y][ox0] = HEDGE
    g[y][ox1] = HEDGE
fill(g, 31, 16, 1, 1, GRASS)         # orchard gate (aligned with spur)
# inside: tree rows + tall-grass alleys + berry soil
tree_row(g, 28, 18, 3, gap=1)        # trees x28,31,34 (2 wide)
for x in range(27, 38):
    if g[21][x] == GRASS: g[21][x] = TALL
tree_row(g, 28, 22, 3, gap=1)
for x in range(28, 34):
    g[24][x] = BERRY_SOIL
for (x, y) in [(36,18),(36,22),(27,19),(37,24)]:
    if g[y][x] == GRASS: g[y][x] = FLOWER
# SE — the Te Mata track (sealed until the story allows)
fill(g, 24, 26, 2, 2, GRASS)
fill(g, 24, 26, 1, 2, SAND)
g[26][25] = HEDGE
g[27][25] = HEDGE

heretaunga = g

# ================= ROUTE 51 (16 x 44) — the coastal road north to Ahuriri =================
W2, H2 = 16, 44
r = [[GRASS]*W2 for _ in range(H2)]
ring_trees(r, W2, H2)
# south opening (from Heretaunga) x7-8; north opening (to Ahuriri, blocked) x7-8
fill(r, 7, 42, 2, 2, GRASS)
fill(r, 7, 0, 2, 2, GRASS)
# winding road (south to north)
fill(r, 7, 36, 2, 8, SAND)
fill(r, 4, 35, 5, 2, SAND)
fill(r, 4, 28, 2, 8, SAND)
fill(r, 4, 27, 8, 2, SAND)
fill(r, 10, 20, 2, 8, SAND)
fill(r, 7, 19, 5, 2, SAND)
fill(r, 7, 12, 2, 8, SAND)
fill(r, 7, 11, 5, 2, SAND)
fill(r, 10, 4, 2, 8, SAND)
fill(r, 8, 3, 4, 2, SAND)
fill(r, 7, 2, 2, 2, SAND)
# tall grass fields
fill(r, 10, 37, 4, 4, TALL)
fill(r, 2, 30, 2, 5, TALL)
fill(r, 7, 30, 3, 4, TALL)
fill(r, 2, 22, 4, 3, TALL)
fill(r, 12, 24, 3, 4, TALL)
fill(r, 2, 12, 3, 4, TALL)
fill(r, 4, 6, 3, 3, TALL)
fill(r, 12, 12, 3, 4, TALL)
# hedgerow orchard edges & trees
tree_row(r, 11, 32, 1)
tree_row(r, 3, 17, 1)
tree_row(r, 12, 8, 1)
for x in range(2, 7):
    r[10][x] = HEDGE
for x in range(9, 14):
    r[29][x] = HEDGE
for (x, y) in [(3,28),(12,25),(6,33),(13,41),(2,25),(5,13),(13,17),(3,5)]:
    if r[y][x] == GRASS: r[y][x] = FLOWER
orchard_road = r

# ================= HOMESTEAD 1F (15 x 11, fills the screen) =================
W3, H3 = 15, 11
FLOOR = cell(h1, LH1, 8, 5)     # 201 wood floor
WALL_TOP = cell(h1, LH1, 1, 0)  # 26E wall top
LEDGE_L = cell(h1, LH1, 0, 4)   # 204 left wall edge
f1 = [[FLOOR]*W3 for _ in range(H3)]
for x in range(W3):
    f1[0][x] = WALL_TOP
# kitchen strip (fridge/sink/counters) sampled verbatim
put(f1, 0, 1, block(h1, LH1, 0, 1, 5, 2))
# stair block to 2F at top-right (4 wide x 3 tall incl. wall)
put(f1, 11, 0, block(h1, LH1, 7, 0, 4, 3))
# family table + chairs + rug set (6 wide x 4 tall)
put(f1, 4, 5, block(h1, LH1, 1, 5, 6, 4))
# left wall edge
for y in range(3, H3):
    f1[y][0] = LEDGE_L
# exit mats at bottom center
put(f1, 7, H3-1, [[cell(h1, LH1, 8, 8), cell(h1, LH1, 9, 8)]])
homestead1f = f1

# ================= HOMESTEAD 2F — Marama's room (15 x 10, fills the screen) =================
W4, H4 = 15, 10
FLOOR2 = cell(h2, LH2, 8, 7)
WALL2_TOP  = cell(h2, LH2, 1, 0)   # plain wall top strip
WALL2_FACE = cell(h2, LH2, 1, 1)   # plain wall face strip
f2 = [[FLOOR2]*W4 for _ in range(H4)]
for x in range(W4):
    f2[0][x] = WALL2_TOP
    f2[1][x] = WALL2_FACE
# desk/console corner (includes its own wall) top-left
put(f2, 0, 0, block(h2, LH2, 0, 0, 4, 3))
# stairs down block (3 wide x 2 tall) top-right
put(f2, 12, 0, block(h2, LH2, 6, 0, 3, 2))
# bed block left
put(f2, 1, 4, block(h2, LH2, 0, 3, 3, 3))
# rug center-right
put(f2, 7, 4, block(h2, LH2, 4, 3, 4, 4))
marama_room = f2

# ---- write out ----
def write_layout(name, grid, folder):
    os.makedirs(f'{ROOT}/data/layouts/{folder}', exist_ok=True)
    with open(f'{ROOT}/data/layouts/{folder}/map.bin', 'wb') as f:
        for row in grid:
            for v in row:
                f.write(struct.pack('<H', v))
    # border: 2x2 trees for exteriors, black (wall top) for interiors
    with open(f'{ROOT}/data/layouts/{folder}/border.bin', 'wb') as f:
        if '2F' in folder:
            for v in (WALL2_TOP, WALL2_TOP, WALL2_FACE, WALL2_FACE):
                f.write(struct.pack('<H', v))
        elif 'Homestead' in folder:
            for v in (WALL_TOP, WALL_TOP, WALL_TOP, WALL_TOP):
                f.write(struct.pack('<H', v))
        else:
            for v in (TREE_TL, TREE_TR, TREE_BL, TREE_BR):
                f.write(struct.pack('<H', v))

write_layout('HeretaungaTown', heretaunga, 'HeretaungaTown')
write_layout('OrchardRoad', orchard_road, 'OrchardRoad')
write_layout('HomesteadF1', homestead1f, 'HeretaungaHomestead1F')
write_layout('MaramaRoom', marama_room, 'HeretaungaHomestead2F')

specs = [
    ('LAYOUT_HERETAUNGA_TOWN', 'HeretaungaTown_Layout', 40, 28, 'gTileset_General', 'gTileset_Petalburg', 'HeretaungaTown'),
    ('LAYOUT_ORCHARD_ROAD', 'OrchardRoad_Layout', 16, 44, 'gTileset_General', 'gTileset_Petalburg', 'OrchardRoad'),
    ('LAYOUT_HERETAUNGA_HOMESTEAD_1F', 'HeretaungaHomestead1F_Layout', 15, 11, 'gTileset_Building', 'gTileset_BrendansMaysHouse', 'HeretaungaHomestead1F'),
    ('LAYOUT_HERETAUNGA_HOMESTEAD_2F', 'HeretaungaHomestead2F_Layout', 15, 10, 'gTileset_Building', 'gTileset_BrendansMaysHouse', 'HeretaungaHomestead2F'),
]
ids = {l['id'] for l in LAYOUTS['layouts']}
for lid, name, w, h, p, s, folder in specs:
    entry = {
        'id': lid, 'name': name, 'width': w, 'height': h,
        'primary_tileset': p, 'secondary_tileset': s,
        'border_filepath': f'data/layouts/{folder}/border.bin',
        'blockdata_filepath': f'data/layouts/{folder}/map.bin',
        'layout_version': 'emerald',
    }
    if lid not in ids:
        LAYOUTS['layouts'].append(entry)
    else:
        i = next(i for i, l in enumerate(LAYOUTS['layouts']) if l['id'] == lid)
        LAYOUTS['layouts'][i] = entry
json.dump(LAYOUTS, open(f'{ROOT}/data/layouts/layouts.json', 'w'), indent=2)
print('layouts written & registered')
