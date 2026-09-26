#!/usr/bin/env python3
"""Print a map's collision grid with events overlaid, for placing NPCs safely.

Usage: python3 tools_pounamu/mapgrid.py MapFolder [x0 y0 x1 y1]

Legend: . walkable   # blocked   ~ water (walkable-surf)   W warp   O object
        C coord event   S sign/bg event   H hidden item
Rows/cols are labelled so coordinates can be read straight off.
"""
import json, os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def load_layout(layout_id):
    layouts = json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts']
    for l in layouts:
        if l.get('id') == layout_id:
            return l
    raise SystemExit('layout not found: ' + layout_id)

def behaviors(layout):
    """Return {metatile_id: behavior} for primary+secondary tilesets (water detection)."""
    import re
    out = {}
    hdr = open(os.path.join(ROOT, 'src/data/tilesets/headers.h')).read()
    def attrs_path(ts):
        m = re.search(r'const struct Tileset %s\s*=\s*\{(.*?)\};' % ts, hdr, re.S)
        if not m:
            return None
        a = re.search(r'\.metatileAttributes\s*=\s*(\w+)', m.group(1)).group(1)
        inc = open(os.path.join(ROOT, 'src/data/tilesets/metatiles.h')).read()
        p = re.search(r'%s\[\]\s*=\s*INCBIN_U16\("([^"]+)"\)' % a, inc)
        return os.path.join(ROOT, p.group(1)) if p else None
    for ts, base in ((layout['primary_tileset'], 0), (layout['secondary_tileset'], 0x200)):
        p = attrs_path(ts)
        if not p or not os.path.exists(p):
            continue
        data = open(p, 'rb').read()
        for i in range(len(data) // 2):
            out[base + i] = struct.unpack_from('<H', data, i * 2)[0] & 0xFF
    return out

WATER = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B}

def main():
    folder = sys.argv[1]
    m = json.load(open(os.path.join(ROOT, 'data/maps', folder, 'map.json')))
    lay = load_layout(m['layout'])
    w, h = lay['width'], lay['height']
    blk = open(os.path.join(ROOT, lay['blockdata_filepath']), 'rb').read()
    beh = behaviors(lay)
    x0, y0, x1, y1 = (0, 0, w - 1, h - 1)
    if len(sys.argv) == 6:
        x0, y0, x1, y1 = map(int, sys.argv[2:6])
    grid = {}
    for y in range(h):
        for x in range(w):
            v = struct.unpack_from('<H', blk, (y * w + x) * 2)[0]
            mid, col = v & 0x3FF, (v >> 10) & 3
            ch = '#' if col else '.'
            if beh.get(mid) in WATER:
                ch = '~'
            grid[(x, y)] = ch
    for o in m.get('object_events', []):
        grid[(o['x'], o['y'])] = 'O'
    for wv in m.get('warp_events', []):
        grid[(wv['x'], wv['y'])] = 'W'
    for c in m.get('coord_events', []):
        grid[(c['x'], c['y'])] = 'C'
    for b in m.get('bg_events', []):
        grid[(b['x'], b['y'])] = 'H' if b.get('type') == 'hidden_item' else 'S'
    print(f"{folder}: {w}x{h} layout={m['layout']}")
    print('    ' + ''.join(str((x // 10) % 10) for x in range(x0, x1 + 1)))
    print('    ' + ''.join(str(x % 10) for x in range(x0, x1 + 1)))
    for y in range(y0, y1 + 1):
        print(f'{y:3d} ' + ''.join(grid.get((x, y), ' ') for x in range(x0, x1 + 1)))
    for o in m.get('object_events', []):
        print(f"  O ({o['x']},{o['y']}) {o['graphics_id'].replace('OBJ_EVENT_GFX_','')} {o['script']}")

if __name__ == '__main__':
    main()
