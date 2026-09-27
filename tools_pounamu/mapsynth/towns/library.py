#!/usr/bin/env python3
"""The building and decoration stamps the Pounamu towns are made of (Sept 2026).

Every stamp is cut from an Emerald town exactly as Game Freak drew it: the rectangle
(x, y, w, h) of a vanilla map, its doors (relative to the rectangle), and optionally a
mask of the cells to take (the rest stays whatever ground the town has there). A stamp
can only be used in a town drawn with the same secondary tileset as its source, except
the Pokemon Center and Mart, which are General tiles and fit any town.

  python3 tools_pounamu/mapsynth/towns/library.py [prefix]   # sheet of the stamps
"""
import json, os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE)); sys.path.insert(0, os.path.dirname(os.path.dirname(HERE)))
from synth import ROOT, LAYOUTS

# name: (vanilla map folder, x, y, w, h, doors, mask rows or None)
# mask rows: strings over the rectangle, '#' = take the cell, '.' = leave the ground;
# None = take everything but plain ground (grass, paths, sand, trees, water), which the
# town draws itself so it joins up with the rest of its ground
STAMPS = {
    # ---- General (any town)
    'pc':            ('PetalburgCity', 19, 13, 4, 4, [(1, 3)], None),
    'mart':          ('MauvilleCity', 22, 11, 4, 4, [(1, 3)], None),
    # ---- Petalburg (Littleroot, Oldale, Petalburg)
    'gym':           ('PetalburgCity', 12, 4, 6, 7, [(3, 4)], None),      # with its statue
    'house4':        ('PetalburgCity', 9, 16, 4, 4, [(1, 3)], None),      # red roof (General tiles)
    'house5':        ('PetalburgCity', 5, 2, 5, 4, [(2, 3)], None),
    'pet.house_brown': ('OldaleTown', 4, 4, 4, 4, [(1, 3)], None),
    'pet.house_brown2': ('OldaleTown', 14, 13, 4, 4, [(1, 3)], None),
    'pet.house_red':   ('PetalburgCity', 9, 16, 4, 4, [(1, 3)], None),
    'pet.house_wide':  ('PetalburgCity', 5, 2, 5, 4, [(2, 3)], None),
    'pet.house_big':   ('LittlerootTown', 2, 4, 5, 5, [(3, 4)], None),
    'pet.lab':         ('LittlerootTown', 3, 12, 7, 5, [(4, 4)], None),
    'pet.garden_house': ('PetalburgCity', 18, 20, 8, 7, [(2, 4)], None),   # hedged, with planters
    'pet.hedge_house': ('PetalburgCity', 4, 1, 7, 9, [(3, 4)], None),      # Wally's, hedges and flowers
    # ---- Dewford
    'dew.hall':      ('DewfordTown', 1, 0, 5, 4, [(2, 3)], None),
    'dew.house':     ('DewfordTown', 7, 5, 4, 4, [(1, 3)], None),
    'dew.house2':    ('DewfordTown', 16, 11, 4, 4, [(1, 3)], None),
    'dew.dock':      ('DewfordTown', 11, 9, 3, 2, [], None),      # plank jetty over the sea
    # ---- Mossdeep
    'moss.house':    ('MossdeepCity', 27, 6, 4, 4, [(1, 3)], None),
    'moss.house_st': ('MossdeepCity', 18, 7, 4, 4, [(1, 3)], None),     # Steven's, with the aerial
    'moss.hall':     ('MossdeepCity', 35, 20, 5, 5, [(1, 4)], None),    # the game corner's hall
    'moss.dome':     ('MossdeepCity', 60, 8, 9, 8, [(4, 7)], None),     # the space centre, no rocket
    'moss.tree':     ('MossdeepCity', 22, 14, 2, 2, [], None),          # round bushy tree
    # ---- Slateport
    'sl.house':      ('SlateportCity', 4, 16, 4, 4, [(1, 3)], None),     # purple roof (the Name Rater's)
    'sl.clubhouse':  ('SlateportCity', 2, 22, 5, 5, [(2, 4)], None),     # green roof (the Fan Club)
    'sl.dome':       ('SlateportCity', 8, 8, 5, 5, [(2, 4)], None),      # the Battle Tent
    'sl.boat':       ('SlateportCity', 33, 36, 3, 3, [], None),          # moored sailboat (over sea)
    'sl.dinghy':     ('SlateportCity', 36, 37, 3, 2, [], None),          # (over sea)
    # ---- Lavaridge
    'lav.spring':    ('LavaridgeTown', 2, 2, 6, 5, [], None),     # hot spring in its rock rim; way in at (4,0)
    'lav.sandbath':  ('LavaridgeTown', 2, 7, 6, 4, [], None),     # the hot sand bath (against rock on its west)
}


def _load(folder):
    j = json.load(open(os.path.join(ROOT, 'data/maps', folder, 'map.json')))
    lay = LAYOUTS[j['layout']]
    raw = open(os.path.join(ROOT, lay['blockdata_filepath']), 'rb').read()
    return lay, list(struct.unpack(f'<{len(raw) // 2}H', raw))


def _plain():
    import routekit as rk
    return ({rk.GRASS, rk.TALL, rk.SHORE_LIP, rk.CANOPY_L, rk.CANOPY_R, rk.CANOPY_TALL_L, rk.CANOPY_TALL_R}
            | set(rk.PATH) | set(rk.BEACH) | set(rk.SEA) | rk.TREE_IDS | set(rk.POND.values()) | set(rk.PALE) | {rk.SIGN})
PLAIN = _plain()


_CACHE = {}
def stamp(name):
    """-> dict(w, h, doors, cells[y][x] (value or None where masked out), secondary)"""
    if name in _CACHE:
        return _CACHE[name]
    folder, x0, y0, w, h, doors, mask = STAMPS[name]
    lay, cells = _load(folder)
    W = lay['width']
    grid = []
    for y in range(h):
        row = []
        for x in range(w):
            v = cells[(y0 + y) * W + x0 + x]
            take = (v & 0x3FF) not in PLAIN if mask is None else mask[y][x] == '#'
            row.append(v if take else None)
        grid.append(row)
    st = dict(name=name, w=w, h=h, doors=list(doors), cells=grid, secondary=lay['secondary_tileset'],
              general=all(v is None or (v & 0x3FF) < 0x200 for r in grid for v in r))
    _CACHE[name] = st
    return st


def sheet(names, secondary, out):
    sys.path.insert(0, os.path.join(ROOT, 'tools_pounamu'))
    from render_tiles import TilesetPair
    from PIL import Image, ImageDraw
    ts = TilesetPair('gTileset_General', secondary)
    sts = [stamp(n) for n in names]
    pad = 10
    wd = sum(max(s['w'] * 16, 60) + pad for s in sts) + pad
    ht = max(s['h'] for s in sts) * 16 + 20
    img = Image.new('RGB', (wd, ht), (40, 40, 40))
    dr = ImageDraw.Draw(img)
    x = pad
    for s in sts:
        for yy, row in enumerate(s['cells']):
            for xx, v in enumerate(row):
                if v is not None:
                    img.paste(ts.render_metatile(v & 0x3FF), (x + xx * 16, 16 + yy * 16))
        for dx, dy in s['doors']:
            dr.rectangle([x + dx * 16, 16 + dy * 16, x + dx * 16 + 15, 16 + dy * 16 + 15], outline=(255, 0, 0))
        dr.text((x, 2), s['name'][:14], fill=(255, 255, 0))
        x += max(s['w'] * 16, 60) + pad
    img.save(out)


if __name__ == '__main__':
    pre = sys.argv[1] if len(sys.argv) > 1 else ''
    names = [n for n in STAMPS if n.startswith(pre)]
    sec = next((stamp(n)['secondary'] for n in names if not stamp(n)['general']), 'gTileset_Petalburg')
    out = os.path.join(os.path.dirname(HERE), 'out', f'library_{pre or "all"}.png')
    sheet(names, sec, out)
    print(out)
