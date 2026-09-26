#!/usr/bin/env python3
"""mapsynth: turn a terrain sketch into a real Emerald map.bin.

A sketch is ASCII, one character per tile; each character names a terrain
class (ash ground, tussock, forest, mesa rock...). AutoTiler learns, from
vanilla Hoenn maps, which metatile the original artists used for a class in
each local situation (its 8 neighbours' membership + position parity, since
trees tessellate on a 2x2 lattice), and renders a sketch the same way.

Design rules the sketches must follow (learned the hard way, Sept 2026):
- Forest shapes snap to the 2x2 tree lattice (even x, even y blocks).
- Rock needs at least 3x2 / 2x3 blocks; thinner slivers can't be drawn.
- Keep bare ground between tussock and the *side* of trees (vanilla never
  lets them touch).
- Seams: the GBA draws a connected map with the CURRENT map's tileset and
  doesn't redraw on crossing, so the ~8 rows either side of a connection
  must use primary-tileset tiles only (green trees 0x1D4/5/C/D, grass 0x001)
  whenever the two maps' secondary tilesets differ.

Used as a library by the per-map build scripts in this folder.
"""
import json, os, random, struct, sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LAYOUTS = {l['id']: l for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts'] if 'id' in l}


def read_cells(layout_id):
    l = LAYOUTS[layout_id]
    raw = open(os.path.join(ROOT, l['blockdata_filepath']), 'rb').read()
    return l['width'], l['height'], list(struct.unpack(f'<{len(raw)//2}H', raw))


class AutoTiler:
    """Local-context autotiling learned from vanilla maps.

    classes: {char: [metatiles]}. For every sample cell whose tile belongs to a
    class, record the tile under key (char, x%2, y%2, 8-neighbour same-class
    mask). Rendering a sketch looks up the most specific key seen.
    texture: chars whose tiles are chosen by weighted random (ground, tussock)."""

    def __init__(self, samples, classes, texture='', tiers=None, interior_texture=''):
        self.classes = classes
        self.texture = set(texture)
        # tiers: {'N': 'M'} means N is a higher tier of M: drawn with M's tiles,
        # M treats N as part of itself, N only treats N as itself.
        self.tiers = tiers or {}
        self.interior_texture = set(interior_texture)
        owner = {}
        for ch, ms in classes.items():
            for m in ms:
                owner.setdefault(m, ch)
        self.tables = [defaultdict(Counter) for _ in range(5)]
        self.freq = defaultdict(Counter)
        self.attr = defaultdict(Counter)
        for s in samples:
            w, h, c = read_cells(s)
            cls = [owner.get(v & 0x3FF) for v in c]
            for y in range(h):
                for x in range(w):
                    k = cls[y*w+x]
                    if k is None:
                        continue
                    m = c[y*w+x] & 0x3FF
                    self.freq[k][m] += 1
                    self.attr[m][((c[y*w+x] >> 10) & 3, c[y*w+x] >> 12)] += 1
                    def same(dx, dy):
                        nx, ny = x+dx, y+dy
                        if not (0 <= nx < w and 0 <= ny < h):
                            return 1          # off-map counts as same (maps run off-edge)
                        return int(cls[ny*w+nx] == k)
                    m4 = (same(0, -1), same(1, 0), same(0, 1), same(-1, 0))
                    m8 = m4 + (same(1, -1), same(1, 1), same(-1, 1), same(-1, -1))
                    for t, key in zip(self.tables, ((k, x % 2, y % 2, m8), (k, x % 2, y % 2, m4),
                                                    (k, m8), (k, m4), (k,))):
                        t[key][m] += 1

    def tile_at(self, sketch, x, y, rnd):
        H, W = len(sketch), len(sketch[0])
        k = sketch[y][x]
        base = k
        while base in self.tiers:          # a tier draws with its root class's tiles
            base = self.tiers[base]
        if base in self.texture:
            opts = self.freq[base]
            return rnd.choices(list(opts), weights=list(opts.values()))[0]
        def above(t):                      # every tier stacked on top of t
            out = set()
            for u, b in self.tiers.items():
                if b == t:
                    out |= {u} | above(u)
            return out
        higher = above(k)
        def same(dx, dy):
            nx, ny = x+dx, y+dy
            if not (0 <= nx < W and 0 <= ny < H):
                return 1
            n = sketch[ny][nx]
            return int(n == k or n in higher)
        m4 = (same(0, -1), same(1, 0), same(0, 1), same(-1, 0))
        m8 = m4 + (same(1, -1), same(1, 1), same(-1, 1), same(-1, -1))
        for t, key in zip(self.tables, ((base, x % 2, y % 2, m8), (base, x % 2, y % 2, m4),
                                        (base, m8), (base, m4), (base,))):
            if key in t:
                c = t[key]
                if base in self.interior_texture and all(m8):
                    return rnd.choices(list(c), weights=list(c.values()))[0]
                return c.most_common(1)[0][0]
        raise KeyError(k)

    def render(self, sketch, seed=0):
        rnd = random.Random(seed)
        return [[self.tile_at(sketch, x, y, rnd) for x in range(len(sketch[0]))] for y in range(len(sketch))]

    def cell_value(self, m):
        col, elev = self.attr[m].most_common(1)[0][0]
        return m | (col << 10) | (elev << 12)
