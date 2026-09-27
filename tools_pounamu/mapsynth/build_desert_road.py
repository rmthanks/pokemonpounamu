#!/usr/bin/env python3
"""Route 1 Desert (the Desert Road, Rangipo) - rebuilt on the ash tileset.

Run from the repo root:  python3 tools_pounamu/mapsynth/build_desert_road.py [--preview]
--preview only renders tools_pounamu/mapsynth/out/desert_road.png.
"""
import json, math, os, random, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
from synth import AutoTiler, ROOT, LAYOUTS
import render_tiles as rt

GROUND = [0x218, 0x229]
TUSSOCK = [0x20A]
TREE = [0x204, 0x205, 0x20C, 0x20D, 0x26D, 0x26E, 0x275, 0x276]
ROCK = [0x06B, 0x06C, 0x06D, 0x071, 0x073, 0x074, 0x075, 0x079, 0x07B, 0x07C, 0x07D, 0x089, 0x091,
        0x093, 0x094, 0x09B, 0x09C, 0x0BE, 0x0BF, 0x0E1, 0x201, 0x202, 0x203, 0x209, 0x20B, 0x211, 0x213]
BOULDER = [0x219]
SIGN = [0x216]
CLASSES = {'.': GROUND, ',': TUSSOCK, 'T': TREE, 'M': ROCK, 'o': BOULDER, 's': SIGN}
TIERS = {'N': 'M'}
SAMPLES = ['LAYOUT_ROUTE113', 'LAYOUT_ROUTE114', 'LAYOUT_FALLARBOR_TOWN']

W, H = 40, 80
SEAM = 8            # rows at each end kept to shared (primary) tiles (view + 1 buffer row)
GAP = (18, 19)          # 2-wide road openings, north and south
rnd = random.Random(1995)   # the year Ruapehu last blew big
g = [['.'] * W for _ in range(H)]

def rect(x0, y0, x1, y1, ch):
    for y in range(max(0, y0), min(H, y1 + 1)):
        for x in range(max(0, x0), min(W, x1 + 1)):
            g[y][x] = ch

def blob(cx, cy, rx, ry, ch, jitter=0.25):
    for y in range(H):
        for x in range(W):
            d = ((x - cx) / rx) ** 2 + ((y - cy) / ry) ** 2
            if d <= 1 + rnd.uniform(-jitter, jitter) and g[y][x] == '.':
                g[y][x] = ch

# --- the road: a gentle S through the plain, kept clear -------------------
def road_x(y):
    return 18.5 + 5.5 * math.sin((y - 6) / 13.0) - 2.0 * math.sin((y - 6) / 5.5) * (0.3 if 20 < y < 64 else 0)
road = set()
for y in range(H):
    c = road_x(y) if 4 < y < H - 5 else 18.5
    for x in range(int(round(c - 1.5)), int(round(c + 1.5)) + 1):
        road.add((x, y))
for x in GAP:
    for y in list(range(0, SEAM + 2)) + list(range(H - SEAM - 2, H)):
        road.add((x, y)); road.add((x - 1, y)); road.add((x + 1, y))

# --- frame: forest at the Taupo end and the Waiouru end, ranges on the sides --
rect(0, 0, W - 1, SEAM - 1, 'T')          # beech forest, north
rect(0, H - SEAM, W - 1, H - 1, 'T')      # forest, south
rect(0, 0, 5, 17, 'T'); rect(W - 6, 0, W - 1, 21, 'T')
rect(0, H - 18, 5, H - 1, 'T'); rect(W - 6, H - 14, W - 1, H - 1, 'T')
# Tongariro flank (west) and Kaimanawa ridge (east): stepped mesa walls
for y0, y1, w in ((19, 30, 7), (31, 41, 5), (42, 55, 8), (56, 61, 6)):
    rect(0, y0, w - 1, y1, 'M')
for y0, y1, w in ((24, 33, 6), (34, 44, 8), (45, 52, 5), (53, 64, 7)):
    rect(W - w, y0, W - 1, y1, 'M')
# keep a strip of bare ash between forest and rock
for y in range(H):
    for x in range(W):
        if g[y][x] == 'M' and any(0 <= y + dy < H and g[y + dy][x] == 'T' for dy in (-1, 1)):
            g[y][x] = '.'

# upper tiers on the ranges (drawn on top of the lower rock)
for x0, y0, x1, y1 in ((0, 21, 3, 28), (0, 44, 4, 53), (W - 4, 36, W - 1, 42), (W - 4, 55, W - 1, 62)):
    rect(x0, y0, x1, y1, 'N')

# --- lahar terraces and volcanic bombs out on the plain ----------------------
for x0, y0, x1, y1 in ((9, 22, 13, 25), (26, 17, 30, 19), (24, 38, 29, 41), (8, 45, 11, 47),
                       (27, 56, 31, 58), (11, 63, 14, 65), (21, 28, 22, 30), (33, 8, 34, 10)):
    rect(x0, y0, x1, y1, 'M')

# --- tussock fields (wild encounters) ---------------------------------------
for cx, cy, rx, ry in ((11, 11, 4.5, 3), (28, 11, 4, 2.6), (13, 31, 4, 3.5), (30, 28, 3, 3.2),
                       (14, 51, 4.5, 3), (27, 47, 3.5, 3), (24, 66, 5, 3), (10, 71, 3.5, 2.5)):
    blob(cx, cy, rx, ry, ',')

# the road stays bare ash
for (x, y) in road:
    if 0 <= x < W and 0 <= y < H and g[y][x] in ',MN':
        g[y][x] = '.'
# rock fragments too thin to draw (every rock cell must sit in a 3x2 or 2x3 rock block)
def rocky(x, y):
    return 0 <= x < W and 0 <= y < H and g[y][x] in 'MN'
for _ in range(3):
    for y in range(H):
        for x in range(W):
            if g[y][x] in 'MN':
                ok = any(all(rocky(bx + dx, by + dy) for dx in range(bw) for dy in range(bh))
                         for bw, bh in ((3, 2), (2, 3))
                         for bx in range(x - bw + 1, x + 1) for by in range(y - bh + 1, y + 1))
                if not ok:
                    g[y][x] = '.'
# tiers need a rim of lower rock on every side they don't touch the map edge
for y in range(H):
    for x in range(W):
        if g[y][x] == 'N':
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nx, ny = x + dx, y + dy
                if 0 <= nx < W and 0 <= ny < H and g[ny][nx] not in 'MN':
                    g[y][x] = 'M'
for x in GAP:
    for y in list(range(0, SEAM + 1)) + list(range(H - SEAM - 1, H)):
        g[y][x] = '.'

# boulders, never on the road or touching another feature
for _ in range(400):
    x, y = rnd.randrange(7, W - 7), rnd.randrange(7, H - 7)
    if (x, y) in road or any((x + dx, y + dy) in road for dx in (-1, 0, 1) for dy in (-1, 0, 1)):
        continue
    if all(g[y + dy][x + dx] == '.' for dx in (-1, 0, 1) for dy in (-1, 0, 1)) and rnd.random() < 0.06:
        g[y][x] = 'o'

# ash strips that run out to a side edge (there's nothing connected there) end in a
# boulder, so no path leads into the border (audit, Sept 2026)
for y in range(SEAM, H - SEAM):
    for x in (0, W - 1):
        if g[y][x] == '.':
            g[y][x] = 'o'

# --- snap forest to the 2x2 tree lattice ------------------------------------
for by in range(0, H, 2):
    for bx in range(0, W, 2):
        cells = [(bx + dx, by + dy) for dx in (0, 1) for dy in (0, 1) if bx + dx < W and by + dy < H]
        t = sum(g[y][x] == 'T' for x, y in cells)
        if 0 < t < len(cells):
            fill = 'T' if t >= 2 else next(g[y][x] for x, y in cells if g[y][x] != 'T')
            for x, y in cells:
                g[y][x] = fill
# the openings stay open after snapping
for x in GAP:
    for y in list(range(0, SEAM + 1)) + list(range(H - SEAM - 1, H)):
        g[y][x] = '.'

SKETCH = [''.join(r) for r in g]

if __name__ == '__main__':
    at = AutoTiler(SAMPLES, CLASSES, texture='.,o', tiers=TIERS)
    grid = at.render(SKETCH, seed=7)
    os.makedirs(os.path.join(HERE, 'out'), exist_ok=True)
    ts = rt.TilesetPair('gTileset_General', 'gTileset_Fallarbor')
    ts.render_map([m for r in grid for m in r], W, scale=1).save(os.path.join(HERE, 'out', 'desert_road.png'))
    open(os.path.join(HERE, 'out', 'desert_road.txt'), 'w').write('\n'.join(SKETCH) + '\n')
    print('rendered', W, 'x', H)


# ============================================================================
#  integration: python3 tools_pounamu/mapsynth/build_desert_road.py --write
# ============================================================================
import struct

def road_center(y):
    xs = [x for (x, yy) in road if yy == y and 0 <= x < W]
    return sum(xs) / len(xs)

def free(x, y, taken, allow=',.'):
    return (0 <= x < W and 0 <= y < H and SKETCH[y][x] in allow and (x, y) not in taken
            and (x, y) not in road_cells)

road_cells = {(x, y) for (x, y) in road if 0 <= x < W and 0 <= y < H}

def place(y, side, taken, allow='.,'):
    """A tile beside the road at row y (side -1 west, +1 east), searching outward."""
    c = road_center(y)
    for dy in (0, 1, -1, 2, -2, 3, -3):
        for off in (3, 4, 2, 5, 6):
            x = int(round(c + side * off)); yy = y + dy
            if free(x, yy, taken, allow):
                return x, yy
    raise RuntimeError(f'no spot near row {y}')

def write():
    at = AutoTiler(SAMPLES, CLASSES, texture='.,o', tiers=TIERS)
    sk = [list(r) for r in SKETCH]
    # wooden signs beside the road at each end
    signs = []
    for y, side, text in ((9, -1, 'north'), (H - 10, 1, 'south')):
        x, yy = place(y, side, set(), allow='.')
        sk[yy][x] = 's'; signs.append((x, yy, text))
    sketch = [''.join(r) for r in sk]
    grid = at.render(sketch, seed=7)
    cells = [at.cell_value(grid[y][x]) for y in range(H) for x in range(W)]
    # Seam bands: the GBA draws a neighbouring map with the *current* map's
    # tileset, so the rows visible across a connection must use only
    # primary-tileset tiles. Use the same green hedge as Taupo and Route 43.
    HEDGE = ((0x5D4, 0x5D5), (0x5DC, 0x5DD))    # tree tiles, collision 1
    GRASS = 0x3001                              # plain grass, walkable, elevation 3
    for y in list(range(0, SEAM)) + list(range(H - SEAM, H)):
        for x in range(W):
            cells[y*W+x] = HEDGE[y % 2][x % 2] if SKETCH[y][x] == 'T' else GRASS
    lay = LAYOUTS['LAYOUT_ROUTE1_DESERT']
    open(os.path.join(ROOT, lay['blockdata_filepath']), 'wb').write(struct.pack(f'<{len(cells)}H', *cells))
    # border: ash forest, phase-matched to the tree lattice
    border = [at.cell_value(m) for m in (0x26D, 0x26E, 0x275, 0x276)]
    open(os.path.join(ROOT, lay['border_filepath']), 'wb').write(struct.pack('<4H', *border))
    lp = os.path.join(ROOT, 'data/layouts/layouts.json')
    lj = json.load(open(lp))
    for e in lj['layouts']:
        if e.get('id') == 'LAYOUT_ROUTE1_DESERT':
            e['width'], e['height'], e['secondary_tileset'] = W, H, 'gTileset_Fallarbor'
    open(lp, 'w').write(json.dumps(lj, indent=2, ensure_ascii=False) + '\n')

    # ---- events ----
    mp = os.path.join(ROOT, 'data/maps/Route1Desert/map.json')
    mj = json.load(open(mp))
    byname = {o['script'].split('_EventScript_')[-1]: o for o in mj['object_events']}
    taken = set()
    def put(name, x, y, face=None):
        o = byname[name]; o['x'], o['y'] = x, y
        if face: o['movement_type'] = f'MOVEMENT_TYPE_FACE_{face}'
        taken.add((x, y))
    # route trainers, north to south, alternating sides, facing the road
    order = ['PPaige', 'PQuinn', 'Ari', 'PNate', 'Koa', 'POlive', 'POllie', 'PNikki', 'PMia']
    rows = [11, 17, 24, 31, 53, 58, 63, 67, 71]
    for i, (name, y) in enumerate(zip(order, rows)):
        side = -1 if i % 2 == 0 else 1
        x, yy = place(y, side, taken)
        put(name, x, yy, 'RIGHT' if side < 0 else 'LEFT')
    # Taha wanders the open ash
    x, y = place(38, -1, taken); put('Taha', x - 2 if free(x - 2, y, taken) else x, y)
    # the convoy: trucker north of the toll, tollies at the road's edges
    c = road_center(45)
    put('CONVOYJOB', *place(43, -1, taken), 'RIGHT')
    lo, hi = min(x for (x, y) in road_cells if y == 47), max(x for (x, y) in road_cells if y == 47)
    put('TollDean', lo, 47, 'UP'); put('TollKasey', hi, 47, 'UP')
    # the Pounamu shard, hidden by a boulder in the southern tussock
    for b in mj['bg_events']:
        if b.get('type') == 'hidden_item':
            b['x'], b['y'] = place(69, 1, taken, allow=',')
    # signs
    mj['bg_events'] = [b for b in mj['bg_events'] if b.get('type') != 'sign']
    for x, y, which in signs:
        mj['bg_events'].append({'type': 'sign', 'x': x, 'y': y, 'elevation': 0,
                                'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY',
                                'script': f'Route1Desert_EventScript_Sign{which.title()}'})
    for cn in mj['connections']:
        if cn['map'] == 'MAP_TAUPO': cn['offset'] = -6
        if cn['map'] == 'MAP_ROUTE43_POUNAMU': cn['offset'] = -2      # Route 43 rebuilt, Sept 2026
    open(mp, 'w').write(json.dumps(mj, indent=2, ensure_ascii=False) + '\n')
    for other, target, off in (('Taupo', 'MAP_ROUTE1_DESERT', 6), ('Route43', 'MAP_ROUTE1_DESERT', 2)):
        p = os.path.join(ROOT, f'data/maps/{other}/map.json'); j = json.load(open(p))
        for cn in j['connections']:
            if cn['map'] == target: cn['offset'] = off
        open(p, 'w').write(json.dumps(j, indent=2, ensure_ascii=False) + '\n')
    for o in mj['object_events']:
        assert SKETCH[o['y']][o['x']] in '.,', (o['script'], o['x'], o['y'])
    print('wrote layout, events and connections; signs at', signs)

if __name__ == '__main__' and '--write' in sys.argv:
    write()
