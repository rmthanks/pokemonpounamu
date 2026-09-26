#!/usr/bin/env python3
"""Heretaunga Clock Tower: custom metatiles for the Petalburg tileset (Sept 2026).

PLACEHOLDER ART - drawn in code by Claude, not by an artist. The project rule is
no generative-AI assets in shipped content, so this is logged in
POUNAMU-CREDITS / pounamu-asset-credits as a placeholder to be redrawn.

Reference: the real tower (Sidney Chaplin, 1935) is a square Art Deco tower of
plastered concrete in three tiers - stripped columns, saw-tooth infill panels
and speed stripes - with a louvred turret, four round clock faces, a flat
disc roof and a flagpole; a recessed doorway under a half-round verandah at
street level. Its chimes were salvaged from the Post Office tower that fell in
the 1931 earthquake.

The tower is 2x5 metatiles (32x80 px), appended to the Petalburg secondary
tileset after its original 144 metatiles / 159 tiles, so re-running replaces
rather than duplicates it:
    metatiles 0x290..0x299 (row-major, 2 wide), layer type COVERED
    bottom layer = the sand-path centre (General 0x121), middle = tower art
Run from the repo root:  python3 tools_pounamu/mapsynth/make_clock_tower.py
"""
import os, re, struct
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TS = os.path.join(ROOT, 'data/tilesets/secondary/petalburg')
GFX_H = os.path.join(ROOT, 'src/data/tilesets/graphics.h')
BASE_TILES, BASE_METATILES = 159, 144
FIRST_METATILE = 0x200 + BASE_METATILES          # 0x290
PAL = 6                                          # Petalburg palette 06: creams, greys, blues, yellows, mint
TW, TH = 2, 5                                    # metatiles
PATH_BOTTOM = (0x5108, 0x5118, 0x5118, 0x5108)   # General 0x121's layer, so the square shows round the base

# palette 06 indices
T, WHITE, OFF, CREAM, SAGE, GREY, DGREY, DARK, INK, SKY, TEAL, PALEY, YEL, TAN, BROWN, MINT = range(16)


def draw():
    img = [[T] * 32 for _ in range(80)]

    def px(x, y, c):
        if 0 <= x < 32 and 0 <= y < 80:
            img[y][x] = c

    def row(y, hw, fill, edge=INK, left=None, right=None):
        x0, x1 = 16 - hw, 15 + hw
        for x in range(x0, x1 + 1):
            px(x, y, fill)
        if left is not None:
            px(x0 + 1, y, left); px(x0 + 2, y, left)
        if right is not None:
            px(x1 - 1, y, GREY if right == SAGE else right); px(x1 - 2, y, right); px(x1 - 3, y, right)
        px(x0, y, edge); px(x1, y, edge)

    # flagpole and the fruit-bowl flag
    for y in range(0, 10):
        px(15, y, DGREY)
    px(15, 0, INK)
    for y in range(1, 5):
        for x in range(16, 21):
            px(x, y, YEL if y < 3 else MINT)
        px(21, y, INK)
    for x in range(16, 22):
        px(x, 0, INK); px(x, 5, INK)
    # flat disc roof
    row(9, 8, INK)
    row(10, 12, CREAM, left=WHITE, right=SAGE)
    row(11, 12, GREY, edge=INK)
    for x in range(4, 28):
        px(x, 9, INK)
    # turret with a round clock face
    for y in range(12, 26):
        row(y, 9, OFF, left=WHITE, right=SAGE)
    cx, cy, r = 15.5, 18.5, 5.6
    for y in range(12, 26):
        for x in range(8, 24):
            d = ((x - cx) ** 2 + (y - cy) ** 2) ** 0.5
            if d <= r - 1.3:
                px(x, y, WHITE)
            elif d <= r - 0.3:
                px(x, y, TEAL)
            elif d <= r + 0.5:
                px(x, y, INK)
    for x, y in ((15, 14), (16, 14), (20, 18), (20, 19), (15, 23), (16, 23), (11, 18), (11, 19)):
        px(x, y, DARK)                               # 12, 3, 6, 9
    for y in (16, 17, 18):
        px(15, y, INK)                               # hour hand
    for x in (16, 17, 18):
        px(x, 18, INK)                               # minute hand
    # louvres
    for y in range(26, 29):
        row(y, 9, SAGE if y % 2 else DGREY, left=WHITE, right=GREY)
    # cornice
    row(29, 11, CREAM, left=WHITE, right=SAGE)
    row(30, 11, GREY)
    # three tiers, each wider, with stripped columns, speed stripes and saw-tooth panels
    def tier(y0, y1, hw, motif):
        for y in range(y0, y1 + 1):
            row(y, hw, OFF, left=WHITE, right=SAGE)
            x0, x1 = 16 - hw, 15 + hw
            px(x0 + 3, y, SKY); px(x1 - 3, y, TEAL)          # speed stripes in the corners
        x0, x1 = 16 - hw + 5, 15 + hw - 5                   # the infill panel
        for y in range(y0 + 1, y1):
            for x in range(x0, x1 + 1):
                px(x, y, CREAM)
        for x in range(x0, x1 + 1):                          # upward saw-tooth
            h = (1, 2, 3, 4, 3, 2)[(x - x0) % 6]
            for y in range(y1 - h, y1):
                px(x, y, motif)
            px(x, y1 - h - 1, SAGE)
        for y in range(y0 + 1, y1 - 5):                      # a flute down the panel
            px((x0 + x1) // 2, y, SAGE); px((x0 + x1) // 2 + 1, y, WHITE)
        for y in range(y0 + 1, y1):
            px(x0 - 1, y, SAGE)
    tier(31, 42, 8, MINT)
    row(43, 9, CREAM, left=WHITE, right=SAGE); row(44, 9, GREY)
    tier(45, 56, 9, YEL)
    row(57, 10, CREAM, left=WHITE, right=SAGE); row(58, 10, GREY)
    for y in range(59, 73):
        row(y, 10, OFF, left=WHITE, right=SAGE)
        px(9, y, SKY); px(22, y, TEAL)
    # street level: half-round verandah over a recessed door, the 1935 crest above
    px(15, 60, YEL); px(16, 60, YEL)
    for y in range(61, 65):
        for x in range(10, 22):
            if ((x - 15.5) ** 2) / 36 + ((y - 64.5) ** 2) / 12 <= 1:
                px(x, y, MINT)
    for x in range(10, 22):
        px(x, 65, INK)
    for y in range(66, 73):
        for x in range(13, 19):
            px(x, y, DARK if x < 18 else INK)
    for y in range(66, 73):
        px(12, y, SAGE); px(19, y, SAGE)
    # plinth and steps
    for y in range(73, 76):
        row(y, 11, CREAM, left=WHITE, right=GREY)
    row(76, 12, SAGE, left=CREAM, right=GREY)
    row(77, 12, SAGE, left=CREAM, right=GREY)
    row(78, 13, GREY, left=SAGE, right=DGREY)
    row(79, 13, DGREY)
    return img


def tiles_of(img):
    out = []
    for ty in range(10):
        for tx in range(4):
            out.append(tuple(img[ty * 8 + y][tx * 8 + x] for y in range(8) for x in range(8)))
    return out


def main():
    img = draw()
    tiles = tiles_of(img)
    uniq, ref = [], []
    for t in tiles:
        if t not in uniq:
            uniq.append(t)
        ref.append(uniq.index(t))

    # tiles.png: keep the original 159 tiles, append the tower's
    png = Image.open(os.path.join(TS, 'tiles.png'))
    pal = png.getpalette()
    w = png.size[0] // 8
    old = []
    for i in range(BASE_TILES):
        tx, ty = i % w, i // w
        old.append(tuple(png.getpixel((tx * 8 + x, ty * 8 + y)) for y in range(8) for x in range(8)))
    allt = old + uniq
    rows = (len(allt) + w - 1) // w
    out = Image.new('P', (w * 8, rows * 8), 0)
    out.putpalette(pal)
    for i, t in enumerate(allt):
        tx, ty = i % w, i // w
        for k, v in enumerate(t):
            out.putpixel((tx * 8 + k % 8, ty * 8 + k // 8), v)
    out.save(os.path.join(TS, 'tiles.png'))

    # metatiles: 2x5, each = 2x2 tiles
    mt = bytearray(open(os.path.join(TS, 'metatiles.bin'), 'rb').read()[:BASE_METATILES * 16])
    at = bytearray(open(os.path.join(TS, 'metatile_attributes.bin'), 'rb').read()[:BASE_METATILES * 2])
    for my in range(TH):
        for mx in range(TW):
            quad = []
            for dy in range(2):
                for dx in range(2):
                    tile = ref[(my * 2 + dy) * 4 + mx * 2 + dx]
                    quad.append((0x200 + BASE_TILES + tile) | (PAL << 12))
            mt += struct.pack('<8H', *PATH_BOTTOM, *quad)
            at += struct.pack('<H', 1 << 12)               # MB_NORMAL, METATILE_LAYER_TYPE_COVERED
    open(os.path.join(TS, 'metatiles.bin'), 'wb').write(mt)
    open(os.path.join(TS, 'metatile_attributes.bin'), 'wb').write(at)

    # the tile count the build embeds
    g = open(GFX_H).read()
    g2 = re.sub(r'(petalburg/tiles\.png", "\.4bpp\.fastSmol", "-num_tiles )\d+', rf'\g<1>{len(allt)}', g)
    open(GFX_H, 'w').write(g2)
    print(f'clock tower: {len(uniq)} new tiles (total {len(allt)}), metatiles '
          f'0x{FIRST_METATILE:03X}-0x{FIRST_METATILE + TW * TH - 1:03X}')


if __name__ == '__main__':
    main()
