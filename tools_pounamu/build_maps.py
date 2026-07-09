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

# ---- Petalburg-sampled city kit ----
GYMHALL   = block(lp, LP, 12, 4, 6, 5)    # big civic building, door local (3,4)
PHOUSE5   = block(lp, LP, 5, 2, 5, 4)     # petalburg house 5w, door local (2,3)
PHOUSE4   = block(lp, LP, 9, 16, 4, 4)    # petalburg house 4w, door local (1,3)
LAB       = block(lt, LT, 3, 12, 7, 5)    # littleroot lab (council building), door local (3,4)
POND      = block(lp, LP, 19, 2, 7, 7)    # complete pond with edges
SIGN_L    = cell(lp, LP, 19, 9); SIGN_R = cell(lp, LP, 20, 9)
# paved road kit (full u16 from petalburg streets)
RD_NW=cell(lp,LP,2,12); RD_N=cell(lp,LP,3,12); RD_NE=cell(lp,LP,16,12)
RD_W =cell(lp,LP,2,13); RD_C=cell(lp,LP,3,13); RD_E =cell(lp,LP,16,13)
RD_SW=cell(lp,LP,2,13); RD_S=cell(lp,LP,3,13); RD_SE=cell(lp,LP,16,13)
# white fence kit
F_TL=cell(lp,LP,4,1); F_T=cell(lp,LP,5,1); F_TR=cell(lp,LP,10,1); F_V=cell(lp,LP,10,3)

def paved(g, x0, y0, w, h):
    """Paved road rectangle with edge tiles."""
    for y in range(y0, y0+h):
        for x in range(x0, x0+w):
            top = (y == y0); bot = (y == y0+h-1)
            lef = (x == x0); rig = (x == x0+w-1)
            v = RD_C
            if top and lef: v = RD_NW
            elif top and rig: v = RD_NE
            elif top: v = RD_N
            elif lef: v = RD_W
            elif rig: v = RD_E
            g[y][x] = v

def fence_rect(g, x0, y0, x1, y1, gaps=()):
    for x in range(x0, x1+1):
        if (x, y0) not in gaps: g[y0][x] = F_T
        if (x, y1) not in gaps: g[y1][x] = F_T
    for y in range(y0, y1+1):
        if (x0, y) not in gaps: g[y][x0] = F_V
        if (x1, y) not in gaps: g[y][x1] = F_V
    g[y0][x0] = F_TL; g[y0][x1] = F_TR

# ================= GREATER HERETAUNGA (60 x 40) — Hastings, density build =================
W, H = 60, 40
g = [[GRASS]*W for _ in range(H)]
ring_trees(g, W, H)
# North exit (Route 51) x28-30
fill(g, 28, 0, 3, 2, GRASS)
# SW exit (Route 2 Wairarapa, gated) x0-1 y33-35
fill(g, 0, 33, 2, 3, GRASS)
fill(g, 2, 34, 6, 1, SAND)
# ---- road network ----
paved(g, 27, 2, 4, 11)                 # N-S from Route 51
paved(g, 4, 12, 53, 3)                 # main EW road
paved(g, 27, 15, 4, 10)                # N-S through core to south
fill(g, 8, 15, 1, 15, SAND)            # Flaxmere lane
fill(g, 44, 15, 1, 8, SAND)            # orchard lane
fill(g, 50, 8, 1, 4, SAND)             # Havelock lane
fill(g, 9, 24, 18, 1, SAND)            # SW connector
# ---- CORE ----
put(g, 21, 7, PC_BLOCK)                # door (22,10) -> spur
fill(g, 22, 11, 1, 1, SAND)
put(g, 32, 7, MART_BLOCK)              # door (33,10)
fill(g, 33, 11, 1, 1, SAND)
put(g, 20, 16, LAB)                    # council building, door (23,20)
fill(g, 23, 21, 1, 1, SAND)
put(g, 33, 16, GYMHALL)                # community hall, door (36,20)
fill(g, 36, 21, 1, 1, SAND)
put(g, 21, 24, PHOUSE5)                # door (23,27)
put(g, 34, 24, PHOUSE4)                # door (35,27)
# plaza with flowerbeds + signs (the landmark square)
for (x, y) in [(24,5),(25,5),(33,5),(34,5)]:
    g[y][x] = FLOWER
g[11][24] = SIGN_L; g[11][25] = SIGN_R
fence_rect(g, 19, 6, 26, 11, gaps={(22,11)})
fence_rect(g, 31, 6, 37, 11, gaps={(33,11)})
for (x, y) in [(38,8),(39,9),(18,9),(40,16),(19,23),(39,23),(31,26),(26,17)]:
    g[y][x] = FLOWER
# ---- FLAXMERE (west) ----
put(g, 3, 15, HOUSE_L)                 # door (6,19)
put(g, 10, 16, OHOUSE)                 # door (11,19)
put(g, 3, 22, PHOUSE4)                 # door (4,25)
put(g, 10, 22, HOUSE_R)                # door (11,26)
fill(g, 6, 20, 1, 1, SAND); fill(g, 11, 20, 1, 1, SAND)
fill(g, 4, 26, 1, 1, SAND); fill(g, 11, 27, 1, 1, SAND)
# Flaxmere park: pond + fence
put(g, 3, 30, POND)
fence_rect(g, 2, 29, 12, 38, gaps={(8,29)})
for (x, y) in [(11,31),(11,34),(4,37),(9,37)]:
    g[y][x] = FLOWER
fill(g, 10, 31, 2, 6, TALL)            # park wild grass
# ---- HAVELOCK NORTH (east, leafy) ----
put(g, 45, 3, OHOUSE)                  # door (46,6)
put(g, 52, 3, HOUSE_L)                 # door (55,7)
put(g, 47, 9, PHOUSE4)                 # door (48,12)
fill(g, 46, 7, 1, 1, SAND); fill(g, 55, 8, 1, 4, SAND); fill(g, 48, 13, 1, 1, SAND)
tree_row(g, 42, 4, 1); tree_row(g, 50, 6, 1); tree_row(g, 57, 9, 1, 0)
for (x, y) in [(44,7),(51,4),(56,7),(45,13),(53,13)]:
    g[y][x] = FLOWER
fence_rect(g, 44, 2, 57, 14, gaps={(50,14),(48,14),(55,14),(50,2)})
# ---- ORCHARD + HOMESTEAD (south-east) ----
put(g, 41, 16, HOUSE_L)                # homestead, door (44,20)
fill(g, 44, 21, 1, 2, SAND)
ox0, oy0, ox1, oy1 = 42, 24, 57, 37
for x in range(ox0, ox1+1):
    g[oy0][x] = HEDGE; g[oy1][x] = HEDGE
for y in range(oy0, oy1+1):
    g[y][ox0] = HEDGE; g[y][ox1] = HEDGE
fill(g, 44, 24, 1, 1, GRASS)           # gate aligned with lane
tree_row(g, 44, 26, 4, gap=1)
for x in range(43, 57):
    if g[29][x] == GRASS: g[29][x] = TALL
tree_row(g, 44, 31, 4, gap=1)
for x in range(45, 52):
    g[34][x] = BERRY_SOIL
for (x, y) in [(55,27),(43,28),(55,33),(53,35)]:
    if g[y][x] == GRASS: g[y][x] = FLOWER
# ---- TE MATA GATE (far east) ----
fill(g, 58, 20, 2, 2, GRASS)
fill(g, 56, 21, 3, 1, SAND)
# sports field (fenced grass, south of core) + street texture
fence_rect(g, 16, 28, 26, 36, gaps={(21,28)})
fill(g, 18, 30, 7, 5, GRASS)
g[29][17] = SIGN_L
tree_row(g, 30, 30, 2, gap=1)
tree_row(g, 34, 34, 2, gap=1)
fill(g, 30, 34, 2, 3, TALL)
for (x, y) in [(16,16),(16,27),(31,30),(15,34),(38,31),(25,32),(29,37),(40,35),(13,17),(41,13),(3,11),(55,16)]:
    if g[y][x] == GRASS: g[y][x] = FLOWER
for (x, y) in [(14,20),(39,28)]:
    g[y][x] = SIGN_L
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


# ---- Mauville-sampled deco kit (Ahuriri uses secondary gTileset_Mauville) ----
LM, lm = load('LAYOUT_MAUVILLE_CITY')
MGYM     = block(lm, LM, 5, 1, 6, 5)      # deco gym, door local (3,4)
THEATRE  = block(lm, LM, 5, 10, 7, 4)     # game-corner deco building, door local (3,3)
MHOUSE4  = block(lm, LM, 18, 11, 4, 4)    # deco house 4w, door local (1,3)
MHOUSE5  = block(lm, LM, 31, 11, 5, 4)    # deco house 5w, door local (1,3)
MWALL_V  = cell(lm, LM, 0, 1)             # deco wall vertical
MWALL_H  = cell(lm, LM, 1, 4)             # deco wall horizontal (291)
ASPH_NW=cell(lm,LM,0,8); ASPH_N=cell(lm,LM,1,8); ASPH_C=cell(lm,LM,1,9)
SEA    = 0x1170
BEACH  = 0x3001 | 0  # plain grass placeholder replaced below
BEACH  = 0x30C6 & 0  # (computed below)
BEACH  = 0x0C6 | 0x3000   # flowery shore shrub strip fallback
SHRUB  = (GRASS & 0xFC00) | 0x0C6

def asphalt(g, x0, y0, w, h):
    for y in range(y0, y0+h):
        for x in range(x0, x0+w):
            g[y][x] = ASPH_N if y == y0 else ASPH_C

# ================= AHURIRI (44 x 36) — Napier, Art Deco =================
WA, HA = 44, 36
a = [[GRASS]*WA for _ in range(HA)]
ring_trees(a, WA, HA)
# sea on the east (Marine Parade)
for y in range(0, HA):
    for x in range(38, WA):
        a[y][x] = SEA
for y in range(1, HA-1):
    a[y][37] = SHRUB          # shore strip
# south exit (Route 51) x7-9 / north exit (Route 2) x7-9
fill(a, 7, 34, 3, 2, GRASS)
fill(a, 7, 0, 3, 2, GRASS)
# asphalt roads: N-S spine + two E-W avenues
asphalt(a, 7, 2, 3, 32)
asphalt(a, 4, 16, 32, 2)
asphalt(a, 4, 26, 32, 2)
asphalt(a, 34, 4, 2, 24)      # Marine Parade promenade
# GYM (Kauri's — Deco showpiece) north of first avenue
put(a, 12, 4, MGYM)           # door (15,8)
for y in range(9,16): a[y][15]=ASPH_C
# PC + MART on the first avenue
put(a, 20, 10, PC_BLOCK)      # door (21,13)
for y in range(14,16): a[y][21]=ASPH_C
put(a, 27, 10, MART_BLOCK)    # door (28,13)
for y in range(14,16): a[y][28]=ASPH_C
# Deco Theatre (function: move tutor venue) south-west
put(a, 4, 20, THEATRE)        # door (7,23)
# deco houses
put(a, 13, 20, MHOUSE4)       # door (14,23)
put(a, 19, 20, MHOUSE5)       # door (20,23)
put(a, 26, 20, MHOUSE4)       # door (27,23)
put(a, 13, 29, MHOUSE5)       # door (14,32)
put(a, 21, 29, MHOUSE4)       # door (22,32)
put(a, 28, 29, MHOUSE4)       # door (29,32)
put(a, 24, 4, MHOUSE5)        # door (25,7)
for y in range(8,16): a[y][25]=ASPH_C
# deco walls + plaza flavour
for x in range(12, 33):
    a[3][x] = MWALL_H
for (x, y) in [(11,12),(18,12),(31,8),(5,18),(11,18),(24,18),(31,18),(5,30),(11,34),(26,34),(33,22)]:
    if a[y][x] == GRASS: a[y][x] = FLOWER
# Pania of the Reef — statue nod on the promenade (sign + flowers)
a[12][35] = SIGN_L
for (x, y) in [(34,11),(36,12),(34,13)]:
    if a[y][x] == GRASS: a[y][x] = FLOWER
ahuriri = a

# ================= ROUTE 2 (BAY STRETCH STUB, 16 x 26) — north out of Ahuriri =================
WB, HB = 16, 26
b = [[GRASS]*WB for _ in range(HB)]
ring_trees(b, WB, HB)
fill(b, 7, 24, 3, 2, GRASS)     # south opening from Ahuriri
# road north
fill(b, 7, 14, 2, 10, SAND)
fill(b, 5, 13, 6, 2, SAND)
fill(b, 5, 6, 2, 8, SAND)
fill(b, 5, 4, 8, 2, SAND)
# THE CHECKPOINT — Mob barricade across the road (exile threshold set-piece)
for x in range(2, 14):
    if x not in (7, 8):
        b[10][x] = HEDGE
# grass fields
fill(b, 10, 16, 4, 5, TALL)
fill(b, 2, 15, 3, 6, TALL)
fill(b, 10, 5, 4, 4, TALL)
fill(b, 2, 4, 2, 5, TALL)
tree_row(b, 11, 12, 1)
for (x, y) in [(4,22),(12,14),(3,12),(13,3),(9,3)]:
    if b[y][x] == GRASS: b[y][x] = FLOWER
route2bay = b


# ================= ROUTE 2 NORTH (16 x 70) — checkpoint to Wairoa =================
W5, H5 = 16, 70
r2n = [[GRASS]*W5 for _ in range(H5)]
ring_trees(r2n, W5, H5)
fill(r2n, 7, 0, 2, 2, GRASS)    # north opening (Wairoa)
fill(r2n, 7, 68, 2, 2, GRASS)   # south opening (Route 2 Bay)
fill(r2n, 7, 2, 2, 66, SAND)    # the highway
# lay-bys / widenings
fill(r2n, 5, 60, 2, 3, SAND)
fill(r2n, 9, 40, 2, 3, SAND)
fill(r2n, 5, 18, 2, 3, SAND)
# tall grass fields flanking (path kept clear)
fill(r2n, 2, 62, 4, 4, TALL)
fill(r2n, 10, 55, 4, 5, TALL)
fill(r2n, 2, 46, 3, 6, TALL)
fill(r2n, 11, 33, 3, 5, TALL)
fill(r2n, 2, 28, 4, 4, TALL)
fill(r2n, 10, 14, 4, 4, TALL)
fill(r2n, 2, 8, 3, 5, TALL)
# hedgerows with gaps at the road
for x in list(range(2,7))+list(range(9,14)):
    r2n[52][x] = HEDGE
for x in list(range(2,7))+list(range(9,14)):
    r2n[24][x] = HEDGE
# tree clusters
tree_row(r2n, 3, 36, 2)
tree_row(r2n, 11, 20, 2)
tree_row(r2n, 3, 5, 1)
for (x,y) in [(4,58),(11,45),(3,31),(12,27),(5,12),(10,7),(13,63),(2,41)]:
    if r2n[y][x] == GRASS: r2n[y][x] = FLOWER
route2_north = r2n

# ================= WAIROA (20 x 16) — hamlet at the river mouth =================
W6, H6 = 20, 16
wr = [[GRASS]*W6 for _ in range(H6)]
ring_trees(wr, W6, H6)
fill(wr, 7, 0, 2, 2, GRASS)     # north opening (Route 2 east leg)
fill(wr, 7, 14, 2, 2, GRASS)    # south opening (Route 2 north leg)
fill(wr, 7, 2, 2, 12, SAND)     # through-road
put(wr, 2, 3, PC_BLOCK)         # Pokemon Center, door (3,6)
fill(wr, 3, 7, 4, 1, SAND)
put(wr, 11, 3, OHOUSE)          # cottage, door (12,6)
fill(wr, 9, 7, 4, 1, SAND)
put(wr, 13, 9, PHOUSE4)         # cottage, door (14,12)
fill(wr, 9, 12, 5, 1, SAND)
wr[8][4] = SIGN_L; wr[8][5] = SIGN_R   # town sign west of road
for (x,y) in [(4,10),(16,4),(11,13),(3,12)]:
    if wr[y][x] == GRASS: wr[y][x] = FLOWER
wairoa = wr

# ================= ROUTE 2 EAST (16 x 85) — Wairoa to Turanga =================
W7, H7 = 16, 84
r2e = [[GRASS]*W7 for _ in range(H7)]
ring_trees(r2e, W7, H7)
fill(r2e, 7, 0, 2, 2, GRASS)
fill(r2e, 7, 82, 2, 2, GRASS)
fill(r2e, 7, 2, 2, 80, SAND)
fill(r2e, 9, 70, 2, 3, SAND)
fill(r2e, 5, 50, 2, 3, SAND)
fill(r2e, 9, 25, 2, 3, SAND)
fill(r2e, 2, 76, 4, 5, TALL)
fill(r2e, 10, 64, 4, 5, TALL)
fill(r2e, 2, 57, 3, 5, TALL)
fill(r2e, 11, 44, 3, 6, TALL)
fill(r2e, 2, 37, 4, 5, TALL)
fill(r2e, 10, 30, 4, 4, TALL)
fill(r2e, 2, 17, 3, 6, TALL)
fill(r2e, 11, 9, 3, 5, TALL)
for x in list(range(2,7))+list(range(9,14)):
    r2e[73][x] = HEDGE
for x in list(range(2,7))+list(range(9,14)):
    r2e[41][x] = HEDGE
for x in list(range(2,7))+list(range(9,14)):
    r2e[14][x] = HEDGE
tree_row(r2e, 3, 68, 2)
tree_row(r2e, 11, 53, 2)
tree_row(r2e, 3, 27, 2)
tree_row(r2e, 11, 18, 1)
for (x,y) in [(4,74),(11,60),(3,48),(12,35),(5,21),(10,11),(13,79),(2,66)]:
    if r2e[y][x] == GRASS: r2e[y][x] = FLOWER
route2_east = r2e

# ================= TURANGA (26 x 22) — first light city =================
W8, H8 = 26, 22
tg = [[GRASS]*W8 for _ in range(H8)]
ring_trees(tg, W8, H8)
fill(tg, 7, 20, 2, 2, GRASS)    # south opening (Route 2)
fill(tg, 12, 0, 2, 2, GRASS)    # north opening (Route 35, gated)
# streets
paved(tg, 6, 8, 16, 3)          # main street EW
fill(tg, 7, 11, 2, 9, SAND)     # south road to opening
fill(tg, 12, 2, 2, 6, SAND)     # north road to Route 35 gate
# civic row (north side of main street)
put(tg, 3, 3, PC_BLOCK)         # door (4,6)
fill(tg, 4, 7, 1, 1, SAND)
put(tg, 8, 3, MART_BLOCK)       # door (9,6)
fill(tg, 9, 7, 1, 1, SAND)
put(tg, 16, 2, LAB)             # Tairawhiti museum, door (19,6)
fill(tg, 19, 7, 1, 1, SAND)
# houses (south side)
put(tg, 2, 13, PHOUSE5)         # door (4,16)
fill(tg, 4, 17, 1, 1, SAND)
put(tg, 10, 13, OHOUSE)         # door (11,16)
fill(tg, 11, 17, 1, 1, SAND)
put(tg, 15, 13, PHOUSE4)        # door (16,16)
fill(tg, 16, 17, 1, 1, SAND)
# harbour basin (pond block) SE corner
put(tg, 19, 14, POND)
# waharoa gate to Hikurangi Track: east edge opening + hedge frame
fill(tg, 24, 9, 2, 2, GRASS)    # east opening in the ring
tg[8][23] = HEDGE; tg[11][23] = HEDGE
tg[9][21] = SIGN_L; tg[9][22] = SIGN_R  # track sign
tg[12][10] = SIGN_L; tg[12][11] = SIGN_R  # town sign near south road
for (x,y) in [(5,12),(14,12),(21,3),(2,18),(17,11)]:
    if tg[y][x] == GRASS: tg[y][x] = FLOWER
turanga = tg

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
write_layout('AhuririCity', ahuriri, 'AhuririCity')
write_layout('Route2Bay', route2bay, 'Route2Bay')
write_layout('Route2North', route2_north, 'Route2North')
write_layout('Wairoa', wairoa, 'Wairoa')
write_layout('Route2East', route2_east, 'Route2East')
write_layout('Turanga', turanga, 'Turanga')
write_layout('OrchardRoad', orchard_road, 'OrchardRoad')
write_layout('HomesteadF1', homestead1f, 'HeretaungaHomestead1F')
write_layout('MaramaRoom', marama_room, 'HeretaungaHomestead2F')

specs = [
    ('LAYOUT_HERETAUNGA_TOWN', 'HeretaungaTown_Layout', 60, 40, 'gTileset_General', 'gTileset_Petalburg', 'HeretaungaTown'),
    ('LAYOUT_AHURIRI_CITY', 'AhuririCity_Layout', 44, 36, 'gTileset_General', 'gTileset_Mauville', 'AhuririCity'),
    ('LAYOUT_ROUTE2_BAY', 'Route2Bay_Layout', 16, 26, 'gTileset_General', 'gTileset_Petalburg', 'Route2Bay'),
    ('LAYOUT_ORCHARD_ROAD', 'OrchardRoad_Layout', 16, 44, 'gTileset_General', 'gTileset_Petalburg', 'OrchardRoad'),
    ('LAYOUT_ROUTE2_NORTH', 'Route2North_Layout', 16, 70, 'gTileset_General', 'gTileset_Petalburg', 'Route2North'),
    ('LAYOUT_WAIROA', 'Wairoa_Layout', 20, 16, 'gTileset_General', 'gTileset_Petalburg', 'Wairoa'),
    ('LAYOUT_ROUTE2_EAST', 'Route2East_Layout', 16, 84, 'gTileset_General', 'gTileset_Petalburg', 'Route2East'),
    ('LAYOUT_TURANGA', 'Turanga_Layout', 26, 22, 'gTileset_General', 'gTileset_Petalburg', 'Turanga'),
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
