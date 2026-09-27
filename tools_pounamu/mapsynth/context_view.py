#!/usr/bin/env python3
"""What the player actually sees at a map's edges.

The GBA draws the ground past a map's edge from two sources: the connected maps
(drawn with THIS map's tilesets, which is how seam garbage happens) and, where no
map is connected, the layout's 2x2 border block. This renders a map with a margin
of both, exactly as the game would, so seam and border flaws show up before the
emulator does.

  python3 tools_pounamu/mapsynth/context_view.py <MapFolder> [out.png]
  (importable: compose(), render_context(folder), edge_problems())

The screen is 15x10 metatiles with the player at column 7, row 4 or 5, so from a
cell the player sees 7 columns either side and 5 rows up and down; one more while
a step scrolls. edge_problems() lists what the player can see past the edges that
doesn't belong: a border that doesn't continue the map's edge (sea border beside a
forest, forest border past the surf) and a neighbour drawn with the wrong tileset.
"""
import json, os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
import render_tiles as rt

ROOT = rt.ROOT
LAYOUTS = {l['id']: l for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts'] if 'id' in l}
_MAPS = None
VIEW_X, VIEW_UP, VIEW_DOWN = 7, 5, 5


def maps_by_id():
    global _MAPS
    if _MAPS is None:
        _MAPS = {}
        base = os.path.join(ROOT, 'data/maps')
        for f in os.listdir(base):
            p = os.path.join(base, f, 'map.json')
            if os.path.exists(p):
                j = json.load(open(p))
                _MAPS[j['id']] = f
    return _MAPS


def load_map(folder):
    j = json.load(open(os.path.join(ROOT, 'data/maps', folder, 'map.json')))
    lays = {l['id']: l for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts'] if 'id' in l}
    lay = lays[j['layout']]
    raw = open(os.path.join(ROOT, lay['blockdata_filepath']), 'rb').read()
    cells = list(struct.unpack(f'<{len(raw) // 2}H', raw))
    braw = open(os.path.join(ROOT, lay['border_filepath']), 'rb').read()
    border = list(struct.unpack(f'<{len(braw) // 2}H', braw))
    return dict(json=j, layout=lay, W=lay['width'], H=lay['height'], cells=cells, border=border,
                secondary=lay['secondary_tileset'], primary=lay['primary_tileset'])


def compose(W, H, cells, border, connections, mx=8, my=6):
    """connections: [(direction, neighbour folder, offset)]. returns grid of values and src labels"""
    GW, GH = W + 2 * mx, H + 2 * my
    grid = [[None] * GW for _ in range(GH)]
    src = [[None] * GW for _ in range(GH)]
    for y in range(H):
        for x in range(W):
            grid[y + my][x + mx] = cells[y * W + x]
            src[y + my][x + mx] = 'map'
    for d, nf, o in connections:
        n = load_map(nf)
        for gy in range(GH):
            for gx in range(GW):
                x, y = gx - mx, gy - my
                if d == 'up' and y < 0:
                    nx, ny = x - o, n['H'] + y
                elif d == 'down' and y >= H:
                    nx, ny = x - o, y - H
                elif d == 'left' and x < 0:
                    nx, ny = n['W'] + x, y - o
                elif d == 'right' and x >= W:
                    nx, ny = x - W, y - o
                else:
                    continue
                if 0 <= nx < n['W'] and 0 <= ny < n['H'] and src[gy][gx] is None:
                    grid[gy][gx] = n['cells'][ny * n['W'] + nx]
                    src[gy][gx] = nf
    for gy in range(GH):
        for gx in range(GW):
            if grid[gy][gx] is None:
                x, y = gx - mx, gy - my
                grid[gy][gx] = border[(x & 1) + 2 * (y & 1)]
                src[gy][gx] = 'border'
    return grid, src


def context_of(folder, mx=8, my=6):
    m = load_map(folder)
    ids = maps_by_id()
    conns = [(c['direction'], ids[c['map']], c['offset']) for c in (m['json'].get('connections') or [])
             if c['map'] in ids]
    grid, src = compose(m['W'], m['H'], m['cells'], m['border'], conns, mx, my)
    return m, conns, grid, src


def render_grid(grid, primary, secondary, frame=None, scale=1):
    from PIL import ImageDraw
    ts = rt.TilesetPair(primary, secondary)
    GW = len(grid[0])
    img = ts.render_map([v & 0x3FF for row in grid for v in row], GW, scale=1)
    if frame:
        mx, my, W, H = frame
        ImageDraw.Draw(img).rectangle([mx * 16 - 1, my * 16 - 1, (mx + W) * 16, (my + H) * 16], outline=(255, 0, 0))
    if scale != 1:
        img = img.resize((img.width * scale, img.height * scale), 0)
    return img


def render_context(folder, mx=8, my=6, scale=1):
    m, conns, grid, src = context_of(folder, mx, my)
    return render_grid(grid, m['primary'], m['secondary'], (mx, my, m['W'], m['H']), scale), m


def _is_tree(v):
    m = v & 0x3FF
    return m in (0x1D4, 0x1D5, 0x1DC, 0x1DD, 0x1D6, 0x1D7, 0x1E4, 0x1E5, 0x1E6, 0x1E7, 0x0C6, 0x0C7, 0x0CE)


def edge_problems(W, H, cells, border, connections, secondary, walkable, mx=8, my=6, water=None):
    """what the player can see past the edges that doesn't belong there.
    walkable(x, y) -> bool for map cells; water(v) -> bool for a cell value"""
    grid, src = compose(W, H, cells, border, connections, mx, my)
    seen = set()
    for y in range(H):
        for x in range(W):
            if not walkable(x, y):
                continue
            for gy in range(y + my - VIEW_UP - 1, y + my + VIEW_DOWN + 2):
                for gx in range(x + mx - VIEW_X - 1, x + mx + VIEW_X + 2):
                    if 0 <= gy < len(grid) and 0 <= gx < len(grid[0]) and src[gy][gx] != 'map':
                        seen.add((gx, gy))
    probs = []
    border_is_tree = _is_tree(border[0])
    folders = {nf: load_map(nf) for d, nf, o in connections}
    for gx, gy in sorted(seen):
        s = src[gy][gx]
        x, y = gx - mx, gy - my
        if s == 'border':
            # compare with the nearest cell that isn't border
            cx, cy = min(max(x, 0), W - 1), min(max(y, 0), H - 1)
            v = cells[cy * W + cx]
            near = src[min(max(gy, my), my + H - 1)][min(max(gx, mx), mx + W - 1)]
            side = 'up' if y < 0 else 'down' if y >= H else 'left' if x < 0 else 'right'
            if border_is_tree and not _is_tree(v):
                probs.append((side, f'forest border seen past ({cx},{cy}) which is not forest ({v & 0x3FF:03x})'))
            elif water and water(border[0]) and not water(v):
                probs.append((side, f'sea border seen past ({cx},{cy}) which is not sea ({v & 0x3FF:03x})'))
        else:
            n = folders[s]
            if (grid[gy][gx] & 0x3FF) >= 0x200 and n['secondary'] != secondary:
                side = [d for d, nf, o in connections if nf == s][0]
                probs.append((side, f'{s} cell seen at ({x},{y}) uses its own tileset ({n["secondary"]}); '
                                    f'drawn with ours ({secondary}) it is garbage'))
    # collapse repeats; each entry is (side, text)
    out, last = [], None
    for side, p in probs:
        key = p.split(' (')[0][:40]
        if key != last:
            out.append((side, p))
        last = key
    return out, grid, src


if __name__ == '__main__':
    folder = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else os.path.join(HERE, 'out', f'{folder}_context.png')
    img, m = render_context(folder)
    img.save(out)
    print(f'{folder} {m["W"]}x{m["H"]} -> {out}')
