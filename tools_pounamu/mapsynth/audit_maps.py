#!/usr/bin/env python3
"""Whole-region tile-flaw audit for Pounamu's outdoor maps (towns and routes).

Checks every map for what the gold-standard gates catch on the rebuilt routes:
  - half trees (a tree tile whose 2x2 partners are missing)
  - water touching a map edge where the next map (or the border) isn't water
  - walkable cells on an edge with nothing connected beyond them
  - flaws in view past the edges (context_view.edge_problems: the border beside
    the wrong thing, or a neighbour drawn in the wrong tileset)
  python3 tools_pounamu/mapsynth/audit_maps.py [MapFolder ...]"""
import json, glob, os, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
import routekit as rk, context_view as cv

POUNAMU_SECS = None


def outdoor_maps():
    out = []
    for p in sorted(glob.glob(os.path.join(rk.ROOT, 'data/maps/*/map.json'))):
        j = json.load(open(p))
        if j['name'].endswith('_Frlg') or j.get('map_type') not in ('MAP_TYPE_TOWN', 'MAP_TYPE_CITY', 'MAP_TYPE_ROUTE'):
            continue
        # Pounamu maps only: the vanilla Hoenn maps are unreachable leftovers
        if not (j['id'].endswith('_POUNAMU') or not j['id'].startswith(('MAP_ROUTE1', 'MAP_ROUTE2', 'MAP_ROUTE3'))):
            pass
        out.append(j['name'])
    return out


def is_water(v):
    return rk.BEH.get(v & 0x3FF, 0) in rk.WATER_BEH


def audit(folder):
    m = cv.load_map(folder)
    W, H, cells = m['W'], m['H'], m['cells']
    ids = cv.maps_by_id()
    conns = [(c['direction'], ids[c['map']], c['offset']) for c in (m['json'].get('connections') or []) if c['map'] in ids]
    probs = []
    # half trees
    T = rk.TREE_IDS
    for y in range(H):
        for x in range(W):
            t = cells[y * W + x] & 0x3FF
            if t not in T:
                continue
            top, left = t in rk.TREE_TOP_L | rk.TREE_TOP_R, t in rk.TREE_TOP_L | rk.TREE_BOT_L
            ox, oy = (x if left else x - 1), (y if top else y - 1)
            want = [(ox, oy, rk.TREE_TOP_L), (ox + 1, oy, rk.TREE_TOP_R), (ox, oy + 1, rk.TREE_BOT_L), (ox + 1, oy + 1, rk.TREE_BOT_R)]
            if any(0 <= px < W and 0 <= py < H and (cells[py * W + px] & 0x3FF) not in s for px, py, s in want):
                probs.append(f'half tree at ({x},{y})')
    # the grid the game builds around the map
    grid, src = cv.compose(W, H, cells, m['border'], conns)
    mx, my = 8, 6
    for y in range(H):
        for x in range(W):
            if not (x in (0, W - 1) or y in (0, H - 1)):
                continue
            v = cells[y * W + x]
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nx, ny = x + dx, y + dy
                if 0 <= nx < W and 0 <= ny < H:
                    continue
                beyond = grid[ny + my][nx + mx]
                s = src[ny + my][nx + mx]
                if is_water(v) and not (v >> 10) & 3 and not is_water(beyond):
                    probs.append(f'water at the edge ({x},{y}) meets {"the border" if s == "border" else s} ({beyond & 0x3FF:03x})')
                if rk.cell_walkable(v) and s == 'border':
                    probs.append(f'walkable edge cell ({x},{y}) leads nowhere')
    reach = set()
    walk = lambda x, y: rk.cell_walkable(cells[y * W + x])
    ep, _, _ = cv.edge_problems(W, H, cells, m['border'], conns, m['secondary'], walk, water=is_water)
    probs += [p for side, p in ep]
    # collapse
    out, seen = [], set()
    for p in probs:
        k = p.split(' (')[0]
        if (k, p[:30]) in seen:
            continue
        seen.add((k, p[:30])); out.append(p)
    return out


if __name__ == '__main__':
    names = sys.argv[1:] or outdoor_maps()
    total = 0
    for n in names:
        try:
            ps = audit(n)
        except Exception as e:
            print(f'{n}: audit failed: {e}'); continue
        if ps:
            total += len(ps)
            print(f'{n}: {len(ps)}')
            for p in ps[:12]:
                print('   ', p)
    print('flaws:', total)
