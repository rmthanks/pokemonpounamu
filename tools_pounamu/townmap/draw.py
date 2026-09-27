#!/usr/bin/env python3
"""Draw Pounamu's town map (the Fly / region map) in Emerald's region-map style.

Emerald's own palette and look: striped sea, a dark-green rim on every coast, hills in
lighter greens, roads as orange bands one cell wide, blue orbs for towns and red orbs for
the cities. The coastlines are NZ's, drawn by hand on the fly grid around the towns and
roads in layout.py (so a fly point always sits on its town).

  python3 tools_pounamu/townmap/draw.py            # preview PNGs into tools_pounamu/townmap/out
  python3 tools_pounamu/townmap/draw.py --write    # also write graphics/pokenav/region_map/map.*"""
import math, os, random, sys
from PIL import Image, ImageDraw
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
from layout import TOWNS, PLACES, ROADS, SEA_LANES

# Emerald's region map palette (BG palettes 7-8: colour index 112 + n)
PAL = [(0, 0, 0), (156, 213, 255), (164, 180, 255), (123, 180, 213), (74, 156, 230), (41, 131, 230),
       (65, 106, 205), (0, 115, 172), (32, 74, 197), (0, 57, 139), (213, 255, 123), (172, 238, 49),
       (98, 213, 0), (57, 172, 8), (0, 115, 0), (205, 205, 148), (0, 0, 0), (255, 255, 255),
       (238, 230, 172), (238, 230, 115), (238, 189, 57), (246, 213, 82), (230, 164, 0), (255, 172, 16),
       (255, 57, 16), (246, 0, 0), (148, 0, 0), (205, 205, 205), (98, 98, 98), (0, 0, 0), (0, 0, 0),
       (0, 0, 0)]
SEA_A, SEA_B = 113, 114            # the open sea, in alternating rows
LANE_A, LANE_B = 116, 117          # a sea route
LAKE_A, LAKE_B = 116, 117
G1, G2, G3, G4, G5 = 126, 125, 124, 123, 122   # darkest (the coast) to lightest (the hills)
ROAD = {G1: 134, G2: 135, G3: 132, G4: 133, G5: 131}
SNOW, ROCK, ROCK_D = 129, 139, 140
BLUE_ORB = ["C D W W W W D C", "D W 115 115 119 119 L D", "W 115 W W 115 119 121 L",
            "W 115 W W 115 119 121 L", "W 119 115 115 119 119 121 L", "W 119 119 119 119 121 121 L",
            "D W 121 121 121 121 L D", "C D L L L L D C"]
RED_ORB = [r.replace('115', 'r1').replace('119', 'r2').replace('121', 'r3') for r in BLUE_ORB]
ORB_CODES = {'W': 129, 'D': 140, 'L': 139, 'r1': 135, 'r2': 136, 'r3': 138}

# coastlines in grid-cell units (x right, y down; cell (c, r) covers [c, c+1) x [r, r+1))
NORTH = [(12.0, 0.25), (12.6, 0.05), (13.0, 0.05), (13.4, 0.5), (14.1, 0.75), (14.6, 1.1), (15.0, 1.45),
         (15.4, 1.55), (15.7, 1.75), (16.3, 1.7), (16.8, 1.2), (17.1, 0.5), (17.45, 0.3), (17.7, 0.6),
         (17.8, 1.2), (18.2, 1.55), (19.2, 1.6), (20.1, 1.55), (21.0, 1.75), (22.0, 1.85), (22.9, 1.75),
         (23.8, 1.5), (24.8, 1.25), (25.8, 1.1), (26.55, 1.25), (26.9, 1.75), (26.75, 2.5), (26.45, 3.3),
         (26.3, 4.1), (26.7, 4.55), (26.6, 4.95), (26.0, 5.05), (25.5, 5.35), (25.3, 5.9), (25.2, 6.5),
         (25.4, 7.0), (25.85, 7.35), (25.4, 7.8), (25.0, 8.5), (24.5, 9.2), (23.5, 9.8), (22.4, 10.3),
         (21.3, 10.75), (20.5, 11.15), (19.9, 11.0), (19.3, 10.85), (18.7, 11.2), (18.2, 11.35),
         (17.6, 11.3), (17.1, 11.05), (17.0, 10.3), (17.05, 9.9), (16.8, 9.35), (16.3, 9.1), (15.6, 8.95),
         (15.0, 8.65), (14.4, 8.2), (14.35, 7.6), (14.6, 7.0), (15.0, 6.6), (15.4, 6.15), (15.5, 5.5),
         (15.25, 4.9), (15.2, 4.2), (15.15, 3.5), (15.0, 3.0), (14.6, 2.6), (14.0, 2.1), (13.5, 1.6),
         (13.0, 1.1), (12.5, 0.7), (12.1, 0.45)]
SOUTH = [(9.4, 8.35), (10.4, 8.3), (10.0, 8.55), (10.6, 8.75), (11.2, 8.7), (11.6, 9.1), (12.1, 9.45),
         (12.6, 9.25), (13.1, 9.1), (13.6, 9.3), (14.2, 9.35), (14.8, 9.5), (15.3, 9.9), (15.3, 10.6),
         (15.05, 11.2), (15.1, 11.7), (15.5, 11.95), (15.45, 12.4), (15.1, 12.6), (15.05, 13.2),
         (14.8, 13.8), (14.2, 14.1), (13.2, 14.15), (12.0, 14.25), (10.8, 14.35), (9.6, 14.1), (8.6, 13.95),
         (7.4, 13.9), (6.3, 13.75), (5.1, 13.5), (4.2, 13.1), (3.7, 12.5), (3.9, 11.8), (4.6, 11.25),
         (5.6, 10.8), (6.8, 10.35), (7.8, 9.95), (8.6, 9.45), (9.0, 9.0), (9.3, 8.6)]
ISLANDS = [
    [(7.0, 14.45), (7.6, 14.35), (8.2, 14.45), (8.45, 14.7), (8.1, 14.97), (7.3, 14.97), (6.9, 14.75)],  # Rakiura
    [(16.65, 0.75), (17.0, 0.6), (17.15, 0.95), (16.85, 1.15)],                  # Aotea (Great Barrier)
    [(23.5, 0.85), (23.8, 0.85), (23.8, 1.1), (23.5, 1.1)],                      # Whakaari
    [(16.45, 9.55), (16.7, 9.45), (16.75, 9.85), (16.5, 9.9)],                   # Kapiti
]
LAKES = [((19.5, 6.45), (0.42, 0.4)),       # Taupo
         ((19.55, 4.35), (0.22, 0.2)),      # Rotorua
         ((7.4, 12.6), (0.18, 0.3)),        # Wakatipu
         ((9.1, 11.9), (0.16, 0.26))]       # Pukaki
PEAKS = [(19.5, 8.6, 'big'),                # Ruapehu
         (15.35, 7.7, 'big'),               # Taranaki
         (10.2, 9.9, 'small'), (9.4, 10.45, 'small'), (8.5, 11.05, 'big'),      # the Southern Alps,
         (7.5, 11.5, 'small'), (6.6, 12.0, 'small')]                           # Aoraki in the middle
W, H = 240, 160
BIG_PEAK = ['...W...', '..WWL..', '.WWLLD.', '.LLLDDD', 'LLLLDDD']
SMALL_PEAK = ['..W..', '.WLL.', 'LLLDD']


def px(x, y):
    """grid-cell units -> screen pixels (the fly grid starts one tile in and two tiles down)"""
    return (x + 1) * 8, (y + 2) * 8


def inside(poly, x, y):
    c = False
    for i in range(len(poly)):
        x1, y1 = poly[i]; x2, y2 = poly[(i + 1) % len(poly)]
        if (y1 > y) != (y2 > y) and x < x1 + (y - y1) * (x2 - x1) / (y2 - y1):
            c = not c
    return c


def noise_field(seed=1998):
    """smooth value noise for the hills, sampled per pixel"""
    rnd = random.Random(seed)
    grids = []
    for step in (24, 12, 6):
        gw, gh = W // step + 2, H // step + 2
        grids.append((step, [[rnd.random() for _ in range(gw)] for _ in range(gh)]))

    def f(x, y):
        v, tot = 0.0, 0.0
        for amp, (step, g) in zip((1.0, 0.5, 0.25), grids):
            gx, gy = x / step, y / step
            i, j = int(gx), int(gy)
            fx, fy = gx - i, gy - j
            fx, fy = fx * fx * (3 - 2 * fx), fy * fy * (3 - 2 * fy)
            a = g[j][i] * (1 - fx) + g[j][i + 1] * fx
            b = g[j + 1][i] * (1 - fx) + g[j + 1][i + 1] * fx
            v += amp * (a * (1 - fy) + b * fy); tot += amp
        return v / tot
    return f


def draw():
    polys = [[px(x, y) for x, y in p] for p in [NORTH, SOUTH] + ISLANDS]
    land = [[any(inside(p, x + 0.5, y + 0.5) for p in polys) for x in range(W)] for y in range(H)]
    lakes = [[False] * W for _ in range(H)]
    for (cx, cy), (rx, ry) in LAKES:
        X, Y = px(cx, cy)
        for y in range(H):
            for x in range(W):
                if ((x + 0.5 - X) / (rx * 8)) ** 2 + ((y + 0.5 - Y) / (ry * 8)) ** 2 <= 1:
                    lakes[y][x] = True
    # distance from the sea (the rim, then the lowlands, then the hills)
    INF = 99
    dist = [[0 if not land[y][x] else INF for x in range(W)] for y in range(H)]
    for _ in range(6):
        for y in range(H):
            for x in range(W):
                if dist[y][x]:
                    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        nx, ny = x + dx, y + dy
                        if 0 <= nx < W and 0 <= ny < H:
                            dist[y][x] = min(dist[y][x], dist[ny][nx] + 1)
    nf = noise_field()
    # elevation: the noise, lifted a little away from the coast; the greens by share of the land
    elev = {}
    for y in range(H):
        for x in range(W):
            if land[y][x]:
                elev[(x, y)] = nf(x, y) + min(dist[y][x], 6) * 0.02
    vals = sorted(elev.values())
    q = lambda f: vals[int(f * (len(vals) - 1))]
    t1, t2, t3, t4 = q(0.18), q(0.55), q(0.84), q(0.95)
    img = [[0] * W for _ in range(H)]
    for y in range(H):
        for x in range(W):
            if not land[y][x]:
                img[y][x] = SEA_A if y % 2 == 0 else SEA_B
                continue
            if lakes[y][x]:
                img[y][x] = LAKE_A if y % 2 == 0 else LAKE_B
                continue
            d, e = dist[y][x], elev[(x, y)]
            if d <= 1 or e < t1:
                c = G1
            elif d == 2 or e < t2:
                c = G2
            elif e < t3:
                c = G3
            elif e < t4:
                c = G4
            else:
                c = G5
            img[y][x] = c
    # lake shores: the dark rim round the water
    for y in range(H):
        for x in range(W):
            if land[y][x] and not lakes[y][x] and any(
                    0 <= y + dy < H and 0 <= x + dx < W and lakes[y + dy][x + dx]
                    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
                img[y][x] = G1
    # mountains: snow on top, lit from the left
    for (cx, cy, size) in PEAKS:
        X, Y = px(cx, cy)
        spr = BIG_PEAK if size == 'big' else SMALL_PEAK
        hgt, wid = len(spr), len(spr[0])
        for dy, row in enumerate(spr):
            for dx, ch in enumerate(row):
                x, y = int(X) - wid // 2 + dx, int(Y) - hgt + 1 + dy
                if ch != '.' and 0 <= x < W and 0 <= y < H and land[y][x]:
                    img[y][x] = {'W': SNOW, 'L': ROCK, 'D': ROCK_D}[ch]
    # roads: an orange band over the land's own shading, one cell wide
    for rd in ROADS.values():
        for (c, r) in rd['cells']:
            X0, Y0 = px(c, r)
            for y in range(Y0, Y0 + 8):
                for x in range(X0, X0 + 8):
                    v = img[y][x]
                    img[y][x] = ROAD.get(v, 135 if v not in (SEA_A, SEA_B) else ROAD[G2])
    for lane in SEA_LANES:
        for (c, r) in lane:
            X0, Y0 = px(c, r)
            for y in range(Y0, Y0 + 8):
                for x in range(X0, X0 + 8):
                    img[y][x] = LANE_A if y % 2 == 0 else LANE_B
    # the orbs
    for t in TOWNS.values():
        c, r = t['cell']
        X0, Y0 = px(c, r)
        rows = RED_ORB if t['kind'] == 'city' else BLUE_ORB
        for dy, row in enumerate(rows):
            for dx, code in enumerate(row.split()):
                if code == 'C':
                    continue
                img[Y0 + dy][X0 + dx] = ORB_CODES.get(code) or int(code)
    return img, land


def to_png(img, path, scale=1, grid=False):
    im = Image.new('RGB', (W, H))
    p = im.load()
    for y in range(H):
        for x in range(W):
            p[x, y] = PAL[img[y][x] - 112]
    if scale > 1:
        im = im.resize((W * scale, H * scale), Image.NEAREST)
    if grid:
        d = ImageDraw.Draw(im)
        for c in range(29):
            X = (c + 1) * 8 * scale
            d.line([(X, 16 * scale), (X, 17 * 8 * scale)], fill=(0, 0, 0))
        for r in range(16):
            Y = (r + 2) * 8 * scale
            d.line([(8 * scale, Y), (29 * 8 * scale, Y)], fill=(0, 0, 0))
        for c in range(0, 28, 2):
            d.text(((c + 1) * 8 * scale + 2, 16 * scale - 11), str(c), fill=(0, 0, 0))
        for r in range(15):
            d.text((8 * scale - 16, (r + 2) * 8 * scale + 2), str(r), fill=(0, 0, 0))
    im.save(path)
    return im


def pack(img):
    """8x8 tiles, deduplicated; the tilemap is 64x64 bytes (an affine background)"""
    sea = tuple(SEA_A if y % 2 == 0 else SEA_B for y in range(8) for x in range(8))
    tiles, index, tmap = [sea], {sea: 0}, [0] * (64 * 64)
    for ty in range(H // 8):
        for tx in range(W // 8):
            t = tuple(img[ty * 8 + y][tx * 8 + x] for y in range(8) for x in range(8))
            if t not in index:
                index[t] = len(tiles); tiles.append(t)
            tmap[ty * 64 + tx] = index[t]
    return tiles, tmap


def write(tiles, tmap):
    out = os.path.join(ROOT, 'graphics/pokenav/region_map')
    n = len(tiles)
    assert n <= 256, f'{n} tiles: an affine background holds 256'
    cols, rows = 16, (n + 15) // 16
    im = Image.new('P', (cols * 8, rows * 8), 0)
    pal = [0] * 768
    for i, c in enumerate(PAL):
        pal[(112 + i) * 3:(112 + i) * 3 + 3] = c
    im.putpalette(pal)
    p = im.load()
    for i, t in enumerate(tiles):
        ox, oy = (i % cols) * 8, (i // cols) * 8
        for k, v in enumerate(t):
            p[ox + k % 8, oy + k // 8] = v
    im.save(os.path.join(out, 'map.png'))
    open(os.path.join(out, 'map.bin'), 'wb').write(bytes(tmap))
    lines = ['JASC-PAL', '0100', '48'] + [f'{r} {g} {b}' for r, g, b in PAL] + ['0 0 0'] * (48 - len(PAL))
    open(os.path.join(out, 'map.pal'), 'w').write('\n'.join(lines) + '\n')
    # the tile count lives in the INCGFX line
    rc = os.path.join(ROOT, 'src/region_map.c')
    s = open(rc).read()
    import re
    s2 = re.sub(r'(graphics/pokenav/region_map/map\.png", "\.8bpp\.smol", "-num_tiles )\d+', rf'\g<1>{n}', s)
    open(rc, 'w').write(s2)
    return n


def write_dex(img):
    """the Pokedex area map: the same picture on a regular 32x32 background (16-bit tilemap)"""
    import struct, re
    out = os.path.join(ROOT, 'graphics/pokedex')
    sea = tuple(SEA_A if y % 2 == 0 else SEA_B for y in range(8) for x in range(8))
    tiles, index, tmap = [sea], {sea: 0}, [0] * (32 * 32)
    for ty in range(H // 8):
        for tx in range(W // 8):
            t = tuple(img[ty * 8 + y][tx * 8 + x] for y in range(8) for x in range(8))
            if t not in index:
                index[t] = len(tiles); tiles.append(t)
            tmap[ty * 32 + tx] = index[t]
    n = len(tiles)
    cols, rows = 16, (n + 15) // 16
    im = Image.new('P', (cols * 8, rows * 8), 0)
    pal = [0] * 768
    for i, c in enumerate(PAL):
        pal[(112 + i) * 3:(112 + i) * 3 + 3] = c
    im.putpalette(pal)
    p = im.load()
    for i, t in enumerate(tiles):
        ox, oy = (i % cols) * 8, (i // cols) * 8
        for k, v in enumerate(t):
            p[ox + k % 8, oy + k // 8] = v
    im.save(os.path.join(out, 'region_map.png'))
    open(os.path.join(out, 'region_map.bin'), 'wb').write(struct.pack('<1024H', *tmap))
    lines = ['JASC-PAL', '0100', '48'] + [f'{r} {g} {b}' for r, g, b in PAL] + ['0 0 0'] * (48 - len(PAL))
    open(os.path.join(out, 'region_map.pal'), 'w').write('\n'.join(lines) + '\n')
    rc = os.path.join(ROOT, 'src/region_map.c')
    s = open(rc).read()
    s2 = re.sub(r'(graphics/pokedex/region_map\.png", "\.8bpp\.smol", "-num_tiles )\d+', rf'\g<1>{n}', s)
    open(rc, 'w').write(s2)
    return n


if __name__ == '__main__':
    os.makedirs(os.path.join(HERE, 'out'), exist_ok=True)
    img, land = draw()
    to_png(img, os.path.join(HERE, 'out/townmap.png'))
    to_png(img, os.path.join(HERE, 'out/townmap_4x_grid.png'), scale=4, grid=True)
    tiles, tmap = pack(img)
    print(f'{len(tiles)} unique tiles')
    if '--write' in sys.argv:
        print('wrote', write(tiles, tmap), 'tiles (Fly map);', write_dex(img), 'tiles (Pokedex area map)')
