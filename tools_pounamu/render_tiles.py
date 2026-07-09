#!/usr/bin/env python3
"""Render metatile sheets and map images for pokeemerald tilesets/layouts,
so maps can be designed without a GUI editor.

Metatile format (emerald): 8 u16 tile entries per metatile
  (bottom layer 4 quadrants, top layer 4 quadrants)
  entry: tileId(10) | flipX(1<<10) | flipY(1<<11) | palette(4<<12)
map.bin: u16 per cell: metatileId(10) | collision(2) | elevation(4)
"""
import json, os, struct, sys
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

TILESET_DIRS = {
    'gTileset_General': 'data/tilesets/primary/general',
    'gTileset_Petalburg': 'data/tilesets/secondary/petalburg',
    'gTileset_Building': 'data/tilesets/primary/building',
    'gTileset_BrendansMaysHouse': 'data/tilesets/secondary/brendans_mays_house',
    'gTileset_PlayersHouse': 'data/tilesets/secondary/players_house',
    'gTileset_Rustboro': 'data/tilesets/secondary/rustboro',
    'gTileset_Mauville': 'data/tilesets/secondary/mauville',
    'gTileset_Lilycove': 'data/tilesets/secondary/lilycove',
    'gTileset_GenericBuilding': 'data/tilesets/secondary/generic_building',
    'gTileset_Shop': 'data/tilesets/secondary/shop',
    'gTileset_PokemonCenter': 'data/tilesets/secondary/pokemon_center',
    'gTileset_Fortree': 'data/tilesets/secondary/fortree',
    'gTileset_Pacifidlog': 'data/tilesets/secondary/pacifidlog',
    'gTileset_Fallarbor': 'data/tilesets/secondary/fallarbor',
}

NUM_PALS_PRIMARY = 6      # primary tileset owns palettes 0-5
NUM_TILES_PRIMARY = 512
NUM_METATILES_PRIMARY = 512


def load_palettes(tsdir):
    pals = []
    for i in range(16):
        p = os.path.join(ROOT, tsdir, 'palettes', f'{i:02}.pal')
        colors = []
        if os.path.exists(p):
            lines = open(p).read().splitlines()
            for line in lines[3:19]:
                parts = line.split()
                if len(parts) == 3:
                    colors.append(tuple(int(v) for v in parts))
        while len(colors) < 16:
            colors.append((0, 0, 0))
        pals.append(colors)
    return pals


def load_tiles(tsdir):
    """Return list of 8x8 tiles as index arrays."""
    im = Image.open(os.path.join(ROOT, tsdir, 'tiles.png'))
    if im.mode != 'P':
        im = im.convert('P')
    w, h = im.size
    px = im.load()
    tiles = []
    for ty in range(h // 8):
        for tx in range(w // 8):
            tile = [[px[tx*8+x, ty*8+y] & 0xF for x in range(8)] for y in range(8)]
            tiles.append(tile)
    return tiles


def load_metatiles(tsdir):
    raw = open(os.path.join(ROOT, tsdir, 'metatiles.bin'), 'rb').read()
    n = len(raw) // 16
    mts = []
    for i in range(n):
        entries = struct.unpack_from('<8H', raw, i*16)
        mts.append(entries)
    return mts


class TilesetPair:
    def __init__(self, primary, secondary):
        pdir, sdir = TILESET_DIRS[primary], TILESET_DIRS[secondary]
        self.tiles_p = load_tiles(pdir)
        self.tiles_s = load_tiles(sdir)
        self.mts_p = load_metatiles(pdir)
        self.mts_s = load_metatiles(sdir)
        pal_p = load_palettes(pdir)
        pal_s = load_palettes(sdir)
        # palettes 0-5 from primary, 6-12 from secondary (emerald convention)
        self.pals = pal_p[:6] + pal_s[6:13] + pal_p[13:]

    def tile(self, tid):
        if tid < NUM_TILES_PRIMARY:
            return self.tiles_p[tid] if tid < len(self.tiles_p) else None
        sid = tid - NUM_TILES_PRIMARY
        return self.tiles_s[sid] if sid < len(self.tiles_s) else None

    def metatile(self, mid):
        if mid < NUM_METATILES_PRIMARY:
            return self.mts_p[mid] if mid < len(self.mts_p) else None
        sid = mid - NUM_METATILES_PRIMARY
        return self.mts_s[sid] if sid < len(self.mts_s) else None

    def render_metatile(self, mid):
        img = Image.new('RGB', (16, 16), (255, 0, 255))
        mt = self.metatile(mid)
        if mt is None:
            return img
        px = img.load()
        for layer in range(2):
            for quad in range(4):
                e = mt[layer*4 + quad]
                tid, fx, fy, pal = e & 0x3FF, e & 0x400, e & 0x800, (e >> 12) & 0xF
                t = self.tile(tid)
                if t is None:
                    continue
                ox, oy = (quad % 2)*8, (quad//2)*8
                colors = self.pals[pal] if pal < len(self.pals) else self.pals[0]
                for y in range(8):
                    for x in range(8):
                        sx = 7-x if fx else x
                        sy = 7-y if fy else y
                        ci = t[sy][sx]
                        if layer == 1 and ci == 0:
                            continue  # top layer color 0 = transparent
                        px[ox+x, oy+y] = colors[ci]
        return img

    def sheet(self, start, count, cols=16, scale=2, label_every=None):
        rows = (count + cols - 1)//cols
        img = Image.new('RGB', (cols*16, rows*16), (40, 40, 40))
        for i in range(count):
            m = self.render_metatile(start + i)
            img.paste(m, ((i % cols)*16, (i//cols)*16))
        return img.resize((img.width*scale, img.height*scale), Image.NEAREST)

    def render_map(self, cells, width, scale=2):
        """cells: list of u16 map.bin values (or (metatile,) tuples)."""
        height = len(cells)//width
        img = Image.new('RGB', (width*16, height*16))
        for i, c in enumerate(cells):
            mid = c & 0x3FF
            img.paste(self.render_metatile(mid), ((i % width)*16, (i//width)*16))
        return img.resize((img.width*scale, img.height*scale), Image.NEAREST)


def render_layout(layout_id, out, scale=2):
    d = json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))
    l = next(x for x in d['layouts'] if x['id'] == layout_id)
    ts = TilesetPair(l['primary_tileset'], l['secondary_tileset'])
    raw = open(os.path.join(ROOT, l['blockdata_filepath']), 'rb').read()
    cells = struct.unpack(f"<{len(raw)//2}H", raw)
    ts.render_map(cells, l['width'], scale).save(out)
    print(f"{layout_id} {l['width']}x{l['height']} -> {out}")


if __name__ == '__main__':
    cmd = sys.argv[1]
    if cmd == 'sheet':
        prim, sec, start, count, out = sys.argv[2], sys.argv[3], int(sys.argv[4]), int(sys.argv[5]), sys.argv[6]
        TilesetPair(prim, sec).sheet(start, count).save(out)
        print('sheet ->', out)
    elif cmd == 'layout':
        render_layout(sys.argv[2], sys.argv[3])
