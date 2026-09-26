#!/usr/bin/env python3
"""Reachability check: python3 tools_pounamu/mapsynth/reach.py MapFolder x0 y0 x1 y1
BFS over walkable tiles (NPCs count as obstacles). Prints the path length or FAIL."""
import json, os, struct, sys
from collections import deque
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
m = sys.argv[1]; x0, y0, x1, y1 = map(int, sys.argv[2:6])
mj = json.load(open(f'{ROOT}/data/maps/{m}/map.json'))
L = {l['id']: l for l in json.load(open(f'{ROOT}/data/layouts/layouts.json'))['layouts'] if 'id' in l}
l = L[mj['layout']]; W, H = l['width'], l['height']
c = struct.unpack(f'<{W*H}H', open(f"{ROOT}/{l['blockdata_filepath']}", 'rb').read())
block = {(o['x'], o['y']) for o in mj['object_events']}
ok = lambda x, y: 0 <= x < W and 0 <= y < H and not (c[y*W+x] >> 10) & 3 and (x, y) not in block
prev = {(x0, y0): None}; q = deque([(x0, y0)])
while q:
    p = q.popleft()
    if p == (x1, y1): break
    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        n = (p[0]+dx, p[1]+dy)
        if n not in prev and ok(*n):
            prev[n] = p; q.append(n)
if (x1, y1) in prev:
    n, k = (x1, y1), 0
    while prev[n]: n, k = prev[n], k + 1
    print(f'{m}: reachable, {k} steps')
else:
    print(f'{m}: FAIL - ({x1},{y1}) not reachable from ({x0},{y0})'); sys.exit(1)
