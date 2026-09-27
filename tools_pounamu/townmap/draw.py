#!/usr/bin/env python3
"""Draw Pounamu's town map (the Fly / region map) in Emerald's region-map style.

Emerald's own palette and look: striped sea, a dark-green rim on every coast, hills in
lighter greens, roads as orange bands one cell wide, blue orbs for towns and red orbs for
the cities. The coastline is NZ's real one (geo.py: Natural Earth, turned so Te Rerenga
Wairua is top right and Rakiura bottom left); towns, roads, lakes and peaks sit where they
really are (layout.py), so a fly point always sits on its town.

  python3 tools_pounamu/townmap/draw.py            # preview PNGs into tools_pounamu/townmap/out
  python3 tools_pounamu/townmap/draw.py --write    # also write graphics/pokenav/region_map/map.*"""
import math, os, random, sys
from PIL import Image, ImageDraw
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
from layout import TOWNS, PLACES, ROADS, ROAD_LINES, SEA_LANES, LAKE_GEO, PEAKS
import geo

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


def lake_polys():
    """each lake as an ellipse drawn on the real map (half-axes in km, the long axis at `tilt`
    degrees from east), projected like the coast"""
    out = []
    for (lat, lon), (a, b), tilt in LAKE_GEO:
        t = math.radians(tilt)
        ring = []
        for i in range(24):
            u = 2 * math.pi * i / 24
            dx = a * math.cos(u) * math.cos(t) - b * math.sin(u) * math.sin(t)     # km east
            dy = a * math.cos(u) * math.sin(t) + b * math.sin(u) * math.cos(t)     # km north
            ring.append(px(*geo.proj(lat + dy / 111.3, lon + dx / (111.3 * math.cos(math.radians(lat))))))
        out.append(ring)
    return out


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
    polys = [[px(x, y) for x, y in p] for p in geo.coast_polys()]
    land = [[any(inside(p, x + 0.5, y + 0.5) for p in polys) for x in range(W)] for y in range(H)]
    lakes = [[False] * W for _ in range(H)]
    for lake in lake_polys():
        for y in range(H):
            for x in range(W):
                if land[y][x] and inside(lake, x + 0.5, y + 0.5):
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
    # roads: the real highways, a yellow line with an orange edge; the Interislander dashed
    def stroke(points, radius, colour, dash=None, land_only=False):
        step = 0.25
        dist = 0.0
        for (x0, y0), (x1, y1) in zip(points, points[1:]):
            X0, Y0 = px(x0, y0); X1, Y1 = px(x1, y1)
            n = max(1, int(math.hypot(X1 - X0, Y1 - Y0) / step))
            for i in range(n + 1):
                X, Y = X0 + (X1 - X0) * i / n, Y0 + (Y1 - Y0) * i / n
                dist += step
                if dash and (dist // dash) % 2:
                    continue
                r = int(math.ceil(radius))
                for yy in range(int(Y) - r, int(Y) + r + 1):
                    for xx in range(int(X) - r, int(X) + r + 1):
                        if 0 <= xx < W and 0 <= yy < H and (xx + 0.5 - X) ** 2 + (yy + 0.5 - Y) ** 2 <= radius ** 2:
                            if not land_only or land[yy][xx]:
                                img[yy][xx] = colour(xx, yy) if callable(colour) else colour
    for pts in ROAD_LINES.values():
        stroke(pts, 1.6, 134)
    for pts in ROAD_LINES.values():
        stroke(pts, 0.75, 133)
    for pts in SEA_LANES:
        stroke(pts, 0.6, lambda x, y: 129 if not land[y][x] else 133, dash=2.0)
    # mountains: snow on top, lit from the left
    for ((cx, cy), size) in PEAKS:
        X, Y = px(cx, cy)
        spr = BIG_PEAK if size == 'big' else SMALL_PEAK
        hgt, wid = len(spr), len(spr[0])
        for dy, row in enumerate(spr):
            for dx, ch in enumerate(row):
                x, y = int(X) - wid // 2 + dx, int(Y) - hgt + 1 + dy
                if ch != '.' and 0 <= x < W and 0 <= y < H and land[y][x]:
                    img[y][x] = {'W': SNOW, 'L': ROCK, 'D': ROCK_D}[ch]
    # a compass rose in the Tasman: north is up and to the right on this map
    compass(img, px(2.6, 2.4))
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


N_GLYPH = ['X..X', 'XX.X', 'X.XX', 'X..X', 'X..X']


def compass(img, centre):
    """a small compass rose: the north needle red, pointing where north is on this map"""
    cx, cy = centre
    t = math.radians(geo.TILT)
    n = (math.sin(t), -math.cos(t))            # north, on screen
    e = (math.cos(t), math.sin(t))             # east
    def tri(tip, half, colour, length):
        # a needle from the centre: points within `half` px of the centre line, out to `length`
        for y in range(int(cy) - 14, int(cy) + 15):
            for x in range(int(cx) - 14, int(cx) + 15):
                dx, dy = x + 0.5 - cx, y + 0.5 - cy
                along = dx * tip[0] + dy * tip[1]
                across = abs(-dx * tip[1] + dy * tip[0])
                if 0 <= along <= length and across <= half * (1 - along / length) + 0.35:
                    img[y][x] = colour
    for y in range(int(cy) - 10, int(cy) + 11):          # the ring
        for x in range(int(cx) - 10, int(cx) + 11):
            d = math.hypot(x + 0.5 - cx, y + 0.5 - cy)
            if 6.4 <= d <= 7.4:
                img[y][x] = 118
    tri((e[0], e[1]), 1.6, 139, 6.0)                     # east and west, grey
    tri((-e[0], -e[1]), 1.6, 139, 6.0)
    tri((-n[0], -n[1]), 2.0, 129, 8.0)                   # south, white
    tri(n, 2.0, 137, 10.0)                                # north, red
    img[int(cy)][int(cx)] = 140
    gx, gy = int(cx + n[0] * 13) - 2, int(cy + n[1] * 13) - 2
    for dy, row in enumerate(N_GLYPH):
        for dx, ch in enumerate(row):
            if ch == 'X':
                img[gy + dy][gx + dx] = 129


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
