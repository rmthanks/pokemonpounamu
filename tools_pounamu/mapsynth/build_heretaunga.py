#!/usr/bin/env python3
"""Heretaunga rebuild (Sept 2026): Clock Tower square, Rongokako, orchards,
Flaxmere and Havelock North.

  python3 tools_pounamu/mapsynth/build_heretaunga.py            # preview only
  python3 tools_pounamu/mapsynth/build_heretaunga.py --write    # write map + events

Buildings are lifted as stamps from the pre-rebuild map (commit 73d78844) so
every door keeps its warp index; NPCs keep their object index and move with
their anchor (homestead, orchard, pen, Te Mata gate).
"""
import json, os, struct, subprocess, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
from synth import AutoTiler, ROOT, LAYOUTS, read_cells
import render_tiles as rt

W, H = 60, 50
SRC_COMMIT = '73d78844'

def old_cells(path, w):
    raw = subprocess.run(['git', 'show', f'{SRC_COMMIT}:{path}'], cwd=ROOT, capture_output=True).stdout
    c = struct.unpack(f'<{len(raw)//2}H', raw)
    return [c[i:i+w] for i in range(0, len(c), w)]

OLD = old_cells('data/layouts/HeretaungaTown/map.bin', 60)
OLDMAP = json.loads(subprocess.run(['git', 'show', f'{SRC_COMMIT}:data/maps/HeretaungaTown/map.json'],
                                   cwd=ROOT, capture_output=True, text=True).stdout)

GRASS, FLOWER = 0x3001, 0x3004
BLOCK = 0x400
TL, TR, BL, BR = 0x1D4, 0x1D5, 0x1DC, 0x1DD

# ---------------------------------------------------------------- canvas
cls = [['.'] * W for _ in range(H)]      # terrain class for the autotiler
fix = {}                                 # (x, y) -> fixed full cell value

def rect(x0, y0, x1, y1, ch):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            cls[y][x] = ch
            fix.pop((x, y), None)

def put(x, y, v):
    fix[(x, y)] = v
    cls[y][x] = '#'

def tree(x, y):
    for dx, dy, t in ((0, 0, TL), (1, 0, TR), (0, 1, BL), (1, 1, BR)):
        put(x + dx, y + dy, t | BLOCK)

def trees(x0, y0, x1, y1):
    for y in range(y0, y1 + 1, 2):
        for x in range(x0, x1 + 1, 2):
            tree(x, y)

def stamp_old(x0, y0, x1, y1, nx, ny):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            put(nx + x - x0, ny + y - y0, OLD[y][x])

# ---------------------------------------------------------------- buildings
# warp index -> (old box x0, y0, x1, y1), new top-left
OLD_BOX = {0: (41, 16, 45, 20), 1: (21, 7, 24, 10), 2: (32, 7, 35, 10), 4: (50, 18, 54, 22),
           5: (45, 3, 48, 6), 6: (52, 3, 56, 7), 7: (47, 9, 50, 12), 8: (3, 15, 7, 19),
           9: (10, 16, 13, 19), 10: (20, 16, 26, 20), 11: (33, 16, 38, 20), 12: (3, 22, 6, 25),
           13: (10, 22, 14, 26), 14: (21, 24, 25, 27), 15: (34, 24, 37, 27)}
NEW_AT = {
    10: (21, 4),   # i-SITE, north side of the square
    1: (30, 5),    # Pokemon Centre
    2: (34, 5),    # Mart
    8: (13, 11),   # Watchers' house, just west of the square
    15: (38, 11),  # the retired Mob driver, just east of the square
    11: (50, 11),  # Matariki Hall, east end of Heretaunga St
    0: (42, 11),   # the homestead, facing the street, orchard behind
    5: (40, 3),    # orchard cottage
    6: (46, 3),    # shearers' quarters
    7: (53, 3),    # berry house
    13: (3, 19),   # Flaxmere: the twins, on the lane down to the paddocks
    9: (4, 5),     # Flaxmere: the flax weaver
    12: (4, 11),   # Flaxmere: Koro (Te Mata in the window)
    4: (45, 32),   # Havelock North: flower shop (door onto the village lane)
    14: (51, 33),  # Havelock North: garden house
}
DOOR = {}
for wi, (x0, y0, x1, y1) in OLD_BOX.items():
    wv = OLDMAP['warp_events'][wi]
    DOOR[wi] = (wv['x'] - x0, wv['y'] - y0, x1 - x0 + 1, y1 - y0 + 1)

# ================================================================ layout
TALL = 0x300D                             # tall grass (wild encounters), walkable

def hedge_box(x0, y0, x1, y1, gaps=()):
    """Closed hedge box: top row y0, sides, two-row closed bottom (y1-1, y1).
    gaps: x positions left open in the top row."""
    put(x0, y0, 0x244 | BLOCK); put(x1, y0, 0x246 | BLOCK)
    for x in range(x0 + 1, x1):
        if x in gaps:
            cls[y0][x] = '.'; fix.pop((x, y0), None)
        else:
            put(x, y0, 0x245 | BLOCK)
    for y in range(y0 + 1, y1 - 1):
        put(x0, y, 0x24C | BLOCK); put(x1, y, 0x24C | BLOCK)
    put(x0, y1 - 1, 0x267 | BLOCK); put(x1, y1 - 1, 0x266 | BLOCK)
    put(x0, y1, 0x264 | BLOCK); put(x1, y1, 0x265 | BLOCK)
    for x in range(x0 + 1, x1):
        put(x, y1 - 1, 0x23D | BLOCK); put(x, y1, 0x245 | BLOCK)

# --- border forest (2x2 lattice: x even, y even = top-left) ---
trees(0, 0, 58, 0)                        # north
for x in (28,):                           # north exit x28-29 (Orchard Road)
    for y in (0, 1):
        fix.pop((x, y)); fix.pop((x + 1, y)); cls[y][x] = cls[y][x + 1] = 'P'
trees(0, 2, 0, H - 2)                     # west
trees(58, 2, 58, 38)                      # east, down to where Rongokako takes over
trees(2, 44, 16, H - 2)                   # south-west corner

# --- Heretaunga Street and the north road ---
rect(28, 0, 29, 8, 'P')
rect(2, 16, 57, 17, 'P')
# --- the Clock Tower square: the north road ends at the tower ---
rect(20, 9, 37, 15, 'P')
TOWER = (28, 9)                           # 2x5 custom metatiles, see make_clock_tower.py
for my in range(5):
    for mx in range(2):
        fix[(28 + mx, 9 + my)] = (0x290 + my * 2 + mx) | BLOCK
        cls[9 + my][28 + mx] = 'Z'            # the square's paving runs round it
for x, y in ((20, 10), (21, 10), (36, 10), (37, 10), (20, 14), (21, 14), (36, 14), (37, 14)):
    cls[y][x] = '*'                       # flowerbeds at the square's corners
trees(20, 2, 26, 2)                       # behind the i-SITE
trees(30, 2, 36, 2)                       # behind the PC and Mart

# --- Flaxmere (west): a crescent off Heretaunga St, a reserve, the road out ---
rect(2, 9, 17, 10, 'P')                   # top of the crescent
rect(16, 9, 17, 15, 'P')                  # east arm back down to the street
rect(9, 18, 10, 27, 'P')                  # south lane to the Remutaka road stub
rect(2, 26, 10, 27, 'P')                  # the road out west (closed by slips)
rect(4, 24, 8, 25, 'P')                   # front path of the twins' house
trees(10, 2, 16, 2); trees(2, 2, 2, 2)
for x, y in ((8, 4), (9, 4), (8, 5), (9, 5), (3, 13), (3, 14)):
    cls[y][x] = '*'
trees(12, 20, 16, 22)                     # Flaxmere reserve
for x, y in ((12, 24), (13, 24), (14, 25), (15, 25), (16, 24)):
    cls[y][x] = '*'
# back paddocks behind Flaxmere: a hedged paddock of long grass (wild encounters)
trees(2, 30, 16, 30)                      # shelterbelt
hedge_box(4, 33, 15, 41, gaps=(9, 10))
for y in range(34, 39):
    for x in range(5, 15):
        put(x, y, TALL)
rect(9, 28, 10, 29, 'P'); rect(9, 32, 10, 32, 'P')   # lane from the road stub to the paddock gate
for x in (9, 10):                                     # through the shelterbelt
    for y in (30, 31):
        fix.pop((x, y), None); cls[y][x] = 'P'
for x in (8, 11):                                     # the belt tree cut by the lane goes
    for y in (30, 31):
        fix.pop((x, y), None); cls[y][x] = '.'

# --- Cornwall Park: the pond pen (job 06), rebuilt with the hedge kit ---
PEN = (19, 20)                            # old pen interior x3..11, y30..37 -> here
stamp_old(3, 30, 11, 37, PEN[0] + 1, PEN[1] + 1)          # water, reeds, flowers
put(PEN[0], PEN[1], 0x244 | BLOCK); put(PEN[0] + 10, PEN[1], 0x246 | BLOCK)
for x in range(PEN[0] + 1, PEN[0] + 10):
    if x - PEN[0] in (6, 7, 8, 9):
        cls[PEN[1]][x] = 'P' if x - PEN[0] == 6 else '.'
        fix.pop((x, PEN[1]), None)
    else:
        put(x, PEN[1], 0x245 | BLOCK)
for y in range(PEN[1] + 1, PEN[1] + 9):
    put(PEN[0], y, 0x24C | BLOCK); put(PEN[0] + 10, y, 0x24C | BLOCK)
put(PEN[0], PEN[1] + 9, 0x267 | BLOCK); put(PEN[0] + 10, PEN[1] + 9, 0x266 | BLOCK)
put(PEN[0], PEN[1] + 10, 0x264 | BLOCK); put(PEN[0] + 10, PEN[1] + 10, 0x265 | BLOCK)
for x in range(PEN[0] + 1, PEN[0] + 10):
    put(x, PEN[1] + 9, 0x23D | BLOCK); put(x, PEN[1] + 10, 0x245 | BLOCK)
rect(25, 18, 25, 19, 'P')                 # stepping path from the street to the pen gate
trees(32, 20, 36, 22)                     # park trees east of the pen
for x, y in ((31, 25), (32, 25), (33, 26), (34, 26), (37, 21), (37, 22)):
    cls[y][x] = '*'

# --- the second orchard (south-centre): fruit trees in rows, a lane ---
rect(19, 31, 37, 32, 'P')                 # orchard lane off Te Mata Rd
for y in (34, 38):
    for x in (20, 23, 26, 29, 32):
        tree(x, y)

# --- the family orchard (Rata's gym): the old block, bottom closed ---
ORCH = (42, 19)                           # old x42..57, y24..34 -> here
for y in range(24, 35):
    for x in range(42, 58):
        put(ORCH[0] + x - 42, ORCH[1] + y - 24, OLD[y][x])
by = ORCH[1] + 11                         # closed two-row bottom
put(42, by, 0x267 | BLOCK); put(57, by, 0x266 | BLOCK)
put(42, by + 1, 0x264 | BLOCK); put(57, by + 1, 0x265 | BLOCK)
for x in range(43, 57):
    put(x, by, 0x23D | BLOCK); put(x, by + 1, 0x245 | BLOCK)

# --- north-east: workers' lane, and the path down past the homestead ---
rect(38, 8, 57, 9, 'P')
rect(47, 10, 48, 15, 'P')
for x, y in ((56, 12), (57, 12), (56, 13), (57, 13)):
    cls[y][x] = '*'

# --- Te Mata Rd: from Heretaunga St down between the orchards to Havelock ---
rect(38, 18, 39, 38, 'P')
# --- Havelock North, the village at Rongokako's feet ---
rect(38, 37, 57, 38, 'P')                 # village lane along the foot of the ridge
for x, y in ((42, 35), (43, 35), (42, 36), (43, 36), (56, 35), (57, 35), (56, 36), (57, 36)):
    cls[y][x] = '*'

# --- Rongokako: the sleeping giant, Te Mata's ridge along the southern edge ---
# Terraces drawn from the vanilla Route 119 ridge tiles; each tier runs off the
# bottom edge, so only its lip and sides show (the faces are on the far side).
RIDGE_Y0 = 40
TIERS = [  # (x0, x1, top row) per tier level; the track gap is x36-40
    [(18, 35, 41), (41, 59, 40)],                              # tier 1
    [(21, 33, 43), (43, 59, 42)],                              # tier 2
    [(25, 30, 45), (47, 59, 44)],                              # tier 3: knees, chest
    [(50, 55, 46)],                                            # tier 4: the peak
]
lev = [[0] * W for _ in range(H)]
for k, spans in enumerate(TIERS, 1):
    for x0, x1, top in spans:
        for y in range(top, H):
            for x in range(x0, x1 + 1):
                lev[y][x] = k
RIDGE = {}
def ridge_tile(x, y):
    k = lev[y][x]
    L = lambda dx, dy: lev[y + dy][x + dx] if 0 <= x + dx < W and 0 <= y + dy < H else (k if y + dy >= H or x + dx >= W else 0)
    top, left, right = L(0, -1) < k, L(-1, 0) < k, L(1, 0) < k
    if k == 1:
        t = {(1, 1, 0): 0x068, (1, 0, 1): 0x06A, (1, 0, 0): 0x069, (1, 1, 1): 0x069,
             (0, 1, 0): 0x070, (0, 0, 1): 0x072, (0, 1, 1): 0x070, (0, 0, 0): 0x071}[(top, left, right)]
    else:
        t = {(1, 1, 0): 0x06B, (1, 0, 1): 0x06D, (1, 0, 0): 0x06C, (1, 1, 1): 0x06C,
             (0, 1, 0): 0x073, (0, 0, 1): 0x075, (0, 1, 1): 0x073, (0, 0, 0): 0x071}[(top, left, right)]
    return t | BLOCK
for y in range(H):
    for x in range(W):
        if lev[y][x]:
            put(x, y, ridge_tile(x, y))
TRACK_X = (37, 38, 39)                    # Te Mata Track: the path up through the gap
rect(37, 39, 39, H - 1, 'P')
put(40, 39, 0x003 | BLOCK)                # sign: Te Mata o Rongokako
# --- buildings (stamped last; their door front becomes path) ---
for wi, (nx, ny) in NEW_AT.items():
    x0, y0, x1, y1 = OLD_BOX[wi]
    stamp_old(x0, y0, x1, y1, nx, ny)
    dx, dy, bw, bh = DOOR[wi]
    fx, fy = nx + dx, ny + dy + 1
    if cls[fy][fx] not in 'P#':
        cls[fy][fx] = 'P'

SKETCH = [''.join(r) for r in cls]

def render(write=False):
    PATH = [0x113, 0x114, 0x115, 0x118, 0x119, 0x11A, 0x120, 0x121, 0x122, 0x128, 0x129, 0x12A]
    at = AutoTiler(['LAYOUT_PETALBURG_CITY', 'LAYOUT_OLDALE_TOWN', 'LAYOUT_LITTLEROOT_TOWN',
                    'LAYOUT_ROUTE101', 'LAYOUT_ROUTE102', 'LAYOUT_ROUTE103'],
                   {'.': [0x001], 'P': PATH}, texture='.')
    sk = [r.replace('#', '.').replace('*', '.').replace('Z', 'P') for r in SKETCH]
    grid = at.render(sk)
    cells = []
    for y in range(H):
        for x in range(W):
            if (x, y) in fix:
                cells.append(fix[(x, y)])
            elif SKETCH[y][x] == '*':
                cells.append(FLOWER)
            elif SKETCH[y][x] == 'P':
                cells.append(at.cell_value(grid[y][x]) if grid[y][x] in PATH else GRASS)
            else:
                cells.append(GRASS)
    return cells

# ================================================================ events
def door(wi):
    nx, ny = NEW_AT[wi]
    dx, dy, _, _ = DOOR[wi]
    return nx + dx, ny + dy

HOME = door(0)                                   # the homestead door
PEN_D = (PEN[0] - 2, PEN[1] - 29)                # old pen -> new pen offset
ORCH_D = (ORCH[0] - 42, ORCH[1] - 24)            # old orchard -> new orchard offset
TRACK_WARP = (38, 47)
ISITE = door(10)

# object local id -> (x, y[, movement_type])
OBJ = {
    1: (52 + ORCH_D[0], 26 + ORCH_D[1]),               # Girl, between the fruit trees
    2: (33, 12),                                       # Neighbour, in the square
    3: (10, 13),                                       # Woman, Flaxmere
    4: (42, 39, 'MOVEMENT_TYPE_FACE_DOWN'),            # Te Mata boy, looking up at the ridge
    5: (46 + ORCH_D[0], 30 + ORCH_D[1]),               # Orchard worker
    6: (40, 46),                                       # Te Mata gate keeper (faces the track)
    7: (13, 26),                                       # Flax kid, Flaxmere reserve
    8: (44, 37),                                       # Havelock lady, on the village lane
    9: (3, 26),                                        # Route 2 gate camper, at the slip-closed road
    16: (49 + ORCH_D[0], 28 + ORCH_D[1]),              # Rata, the gym leader, in her orchard
    17: (41, 20),                                      # the Queen (Vespiquen), by the orchard
    18: (52, 10),                                      # Kuia, on the workers' lane
    19: (ISITE[0] + 2, ISITE[1] + 1, 'MOVEMENT_TYPE_FACE_LEFT'),   # the Watchers, by the job board
    20: (49 + ORCH_D[0], 23 + ORCH_D[1]),              # Awhi (postgame), at the orchard fence
    21: (48 + ORCH_D[0], 28 + ORCH_D[1]),              # Tama (retired object)
    22: (37, 46),                                      # Rata at the track (postgame)
    23: (39, 46),                                      # Kauri at the track (postgame)
    24: (HOME[0], HOME[1] + 3),                        # Tama, intro
    25: (HOME[0] + 1, HOME[1] + 2),                    # Mum, intro
    32: (35, 12),                                      # Hori, in town
    33: (40, 10, 'MOVEMENT_TYPE_FACE_RIGHT'),          # PHika
    34: (12, 8, 'MOVEMENT_TYPE_FACE_DOWN'),            # PManaia, Flaxmere crescent
    35: (49, 13),                                      # PNgaire, beside the homestead path
    36: (42, 18, 'MOVEMENT_TYPE_FACE_RIGHT'),          # PZara, at the orchard gate
    37: (47, 18),                                      # PAda, at the orchard gate
    38: (43 + ORCH_D[0], 26 + ORCH_D[1]),              # Stall aunty
    39: (46 + ORCH_D[0], 26 + ORCH_D[1]),              # Training koro
    40: (49 + ORCH_D[0], 26 + ORCH_D[1]),              # Share kid
    41: (56, 39, 'MOVEMENT_TYPE_FACE_DOWN'),           # the slip-job scientist, under the ridge
}
for i in range(10, 16):                                # berry trees
    OBJ[i] = (45 + i - 10 + ORCH_D[0], 34 + ORCH_D[1])
for i in range(26, 32):                                # pond pen job (kid, pups, leader, friend)
    ox, oy = {26: (10, 30), 27: (10, 32), 28: (11, 35), 29: (4, 37), 30: (8, 37), 31: (6, 37)}[i]
    OBJ[i] = (ox + PEN_D[0], oy + PEN_D[1])

def events(m):
    for wi, w in enumerate(m['warp_events']):
        if wi == 3:
            w['x'], w['y'] = TRACK_WARP
        else:
            w['x'], w['y'] = door(wi)
    for i, o in enumerate(m['object_events'], 1):
        v = OBJ[i]
        o['x'], o['y'] = v[0], v[1]
        if len(v) > 2:
            o['movement_type'] = v[2]
    trig = lambda x, y, var, val, scr: {'type': 'trigger', 'x': x, 'y': y, 'elevation': 3,
                                        'var': var, 'var_value': val, 'script': scr}
    m['coord_events'] = [trig(HOME[0], HOME[1] + 1, 'VAR_POUNAMU_INTRO_STATE', '1', 'HeretaungaTown_EventScript_Shadows')]
    m['coord_events'] += [trig(x, 48, 'VAR_TEMP_0', '0', 'HeretaungaTown_EventScript_TeMataTrackEntry') for x in TRACK_X]
    m['coord_events'] += [trig(x, y, 'VAR_TEMP_0', '0', 'HeretaungaTown_EventScript_Watchers')
                          for x, y in ((ISITE[0] - 1, ISITE[1] + 1), (ISITE[0] + 1, ISITE[1] + 1), (ISITE[0], ISITE[1] + 2))]
    sign = lambda x, y, scr, face='BG_EVENT_PLAYER_FACING_ANY': {'type': 'sign', 'x': x, 'y': y, 'elevation': 0,
                                                                 'player_facing_dir': face, 'script': scr}
    hall = door(11)
    m['bg_events'] = [sign(ISITE[0] - 1, ISITE[1], 'HeretaungaTown_EventScript_ISite'),
                      sign(hall[0], hall[1], 'HeretaungaTown_EventScript_MatarikiHall'),
                      sign(ISITE[0], ISITE[1], 'HeretaungaTown_EventScript_JobBoard'),
                      sign(28, 13, 'HeretaungaTown_EventScript_ClockTower', 'BG_EVENT_PLAYER_FACING_NORTH'),
                      sign(29, 13, 'HeretaungaTown_EventScript_ClockTower', 'BG_EVENT_PLAYER_FACING_NORTH'),
                      sign(40, 39, 'HeretaungaTown_EventScript_TeMataSign'),
                      {'type': 'hidden_item', 'x': 3 + PEN_D[0], 'y': 37 + PEN_D[1], 'elevation': 3,
                       'item': 'ITEM_STAR_PIECE', 'flag': 'FLAG_UNUSED_0x264'}]
    return m

def write(cells):
    lay = LAYOUTS['LAYOUT_HERETAUNGA_TOWN']
    open(os.path.join(ROOT, lay['blockdata_filepath']), 'wb').write(struct.pack(f'<{W*H}H', *cells))
    lp = os.path.join(ROOT, 'data/layouts/layouts.json')
    txt = open(lp).read()
    i = txt.index('"id": "LAYOUT_HERETAUNGA_TOWN"')
    j = txt.index('"height":', i)
    k = txt.index(',', j)
    txt = txt[:j] + f'"height": {H}' + txt[k:]
    open(lp, 'w').write(txt)
    mp = os.path.join(ROOT, 'data/maps/HeretaungaTown/map.json')
    m = events(OLDMAP)
    open(mp, 'w').write(json.dumps(m, indent=2) + '\n')

if __name__ == '__main__':
    cells = render()
    if '--write' in sys.argv:
        write(cells)
        print('map + events written')
    ts = rt.TilesetPair('gTileset_General', 'gTileset_Petalburg')
    img = ts.render_map(cells, W, scale=1)
    os.makedirs(os.path.join(HERE, 'out'), exist_ok=True)
    img.save(os.path.join(HERE, 'out', 'heretaunga_draft.png'))
    open(os.path.join(HERE, 'out', 'heretaunga_sketch.txt'), 'w').write('\n'.join(SKETCH) + '\n')
    print('draft rendered')
