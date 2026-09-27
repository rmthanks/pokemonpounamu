#!/usr/bin/env python3
"""Building stamps lifted from Emerald's own towns (Sept 2026).

Each Pounamu town is drawn with one vanilla town's tileset (Rotorua with Lavaridge's,
Wellington with Rustboro's, ...), and its buildings are that town's buildings, tile for
tile, collision and all. A building is found from its door: the block of collision
cells joined to the door, plus the roof rows above it that the player walks behind.
Decorations with no door (fences, lamps, pools, stalls) are cut by hand as rectangles.

  python3 tools_pounamu/mapsynth/towns/vanilla_stamps.py <VanillaTown> [--sheet]
  (importable: buildings(folder), cut(folder, x, y, w, h), sheet(stamps, out))"""
import json, os, struct, sys
from collections import Counter
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE)); sys.path.insert(0, os.path.dirname(os.path.dirname(HERE)))
import routekit as rk
from synth import ROOT, LAYOUTS

# primary ground the buildings stand on (never part of a building)
GROUND = ({rk.GRASS, rk.TALL, rk.FLOWER, rk.SHORE_LIP, rk.SIGN, rk.CANOPY_L, rk.CANOPY_R,
           rk.CANOPY_TALL_L, rk.CANOPY_TALL_R} | set(rk.PATH) | set(rk.BEACH) | set(rk.SEA) | rk.TREE_IDS
          | set(rk.POND.values()))


def load(folder):
    j = json.load(open(os.path.join(ROOT, 'data/maps', folder, 'map.json')))
    lay = LAYOUTS[j['layout']]
    raw = open(os.path.join(ROOT, lay['blockdata_filepath']), 'rb').read()
    cells = list(struct.unpack(f'<{len(raw) // 2}H', raw))
    return dict(json=j, layout=lay, W=lay['width'], H=lay['height'], cells=cells,
                secondary=lay['secondary_tileset'])


def _common_ground(m):
    """secondary tiles used as open ground all over the map (paving, ash, sand): walkable
    and common. Roof tops are walkable too (the player passes behind them) but rare."""
    c = Counter(v & 0x3FF for v in m['cells'] if not (v >> 10) & 3)
    return {t for t, n in c.items() if n >= 10} | GROUND


def buildings(folder):
    m = load(folder)
    W, H, cells = m['W'], m['H'], m['cells']
    ground = _common_ground(m)
    col = lambda x, y: 0 <= x < W and 0 <= y < H and (cells[y * W + x] >> 10) & 3
    out, seen_doors = [], set()
    for i, w in enumerate(m['json']['warp_events']):
        sx, sy = w['x'], w['y']
        if (sx, sy) in seen_doors:
            continue
        seen_doors.add((sx, sy))
        blk, todo = {(sx, sy)}, [(sx, sy)]
        while todo:
            x, y = todo.pop()
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nx, ny = x + dx, y + dy
                if (nx, ny) not in blk and col(nx, ny) and sy - 8 <= ny <= sy and abs(nx - sx) <= 7:
                    blk.add((nx, ny)); todo.append((nx, ny))
        # a second door in the same wall (double doors) belongs to the same building
        for w2 in m['json']['warp_events']:
            if (w2['x'], w2['y']) != (sx, sy) and w2['y'] == sy and abs(w2['x'] - sx) == 1:
                blk.add((w2['x'], w2['y'])); seen_doors.add((w2['x'], w2['y']))
        x0 = min(x for x, y in blk); x1 = max(x for x, y in blk)
        y0 = min(y for x, y in blk); y1 = max(y for x, y in blk)
        # roof rows above the collision block (drawn over the player, so no collision)
        while y0 > 0:
            row = [cells[(y0 - 1) * W + x] & 0x3FF for x in range(x0, x1 + 1)]
            if sum(t not in ground for t in row) * 2 >= len(row):
                y0 -= 1
            else:
                break
        st = {'name': w['dest_map'].replace('MAP_', '').lower(), 'src': folder, 'origin': [x0, y0],
              'w': x1 - x0 + 1, 'h': y1 - y0 + 1, 'doors': [[sx - x0, sy - y0]],
              'cells': [[cells[y * W + x] for x in range(x0, x1 + 1)] for y in range(y0, y1 + 1)]}
        for w2 in m['json']['warp_events']:
            if (w2['x'], w2['y']) != (sx, sy) and x0 <= w2['x'] <= x1 and y0 <= w2['y'] <= y1:
                st['doors'].append([w2['x'] - x0, w2['y'] - y0])
        out.append(st)
    return out


def cut(folder, x0, y0, w, h, name, keep=None):
    """a hand-cut decoration: the rectangle as it stands (keep: set of (dx,dy) to take; the
    rest of the rectangle is left to the ground beneath)"""
    m = load(folder)
    W, cells = m['W'], m['cells']
    st = {'name': name, 'src': folder, 'origin': [x0, y0], 'w': w, 'h': h, 'doors': [],
          'cells': [[cells[(y0 + y) * W + x0 + x] for x in range(w)] for y in range(h)]}
    if keep is not None:
        st['mask'] = [[(x, y) in keep for x in range(w)] for y in range(h)]
    return st


def sheet(stamps, secondary, out):
    sys.path.insert(0, os.path.join(ROOT, 'tools_pounamu'))
    from render_tiles import TilesetPair
    from PIL import Image, ImageDraw
    ts = TilesetPair('gTileset_General', secondary)
    pad = 8
    wd = sum(s['w'] * 16 + pad for s in stamps) + pad
    ht = max(s['h'] for s in stamps) * 16 + 24
    img = Image.new('RGB', (wd, ht), (40, 40, 40))
    dr = ImageDraw.Draw(img)
    x = pad
    for s in stamps:
        for yy, row in enumerate(s['cells']):
            for xx, v in enumerate(row):
                img.paste(ts.render_metatile(v & 0x3FF), (x + xx * 16, 16 + yy * 16))
        for dx, dy in s['doors']:
            dr.rectangle([x + dx * 16, 16 + dy * 16, x + dx * 16 + 15, 16 + dy * 16 + 15], outline=(255, 0, 0))
        dr.text((x, 2), s['name'][:18], fill=(255, 255, 0))
        x += s['w'] * 16 + pad
    img.save(out)


if __name__ == '__main__':
    f = sys.argv[1]
    st = buildings(f)
    for s in st:
        print(f"{s['name']:40} {s['w']}x{s['h']} at {s['origin']} doors {s['doors']}")
    if '--sheet' in sys.argv:
        o = os.path.join(os.path.dirname(HERE), 'out', f'stamps_{f}.png')
        sheet(st, load(f)['secondary'], o)
        print('sheet ->', o)
