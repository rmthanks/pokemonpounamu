#!/usr/bin/env python3
"""Every map connection must have its mirror: if A connects up to B at offset o,
B connects down to A at offset -o. Also flags links into the unused FRLG maps.
Retired maps keep one-way exits so a save made inside one can still walk out (LEGACY).
  python3 tools_pounamu/mapsynth/check_connections.py"""
import json, glob, os, sys
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
maps = {}
for p in glob.glob(os.path.join(ROOT, 'data/maps/*/map.json')):
    j = json.load(open(p)); maps[j['id']] = j
opp = {'up': 'down', 'down': 'up', 'left': 'right', 'right': 'left'}
# Wairoa stopped being a stop in Sept 2026 (Route 2 North runs straight into Route 2 East);
# its map stays, unreachable, with its old exits so an old save standing in it can leave
LEGACY = {'MAP_WAIROA'}
bad = []
for mid, j in maps.items():
    if j['name'].endswith('_Frlg'):
        continue
    for c in j.get('connections') or []:
        if c['direction'] not in opp:
            continue
        t = maps.get(c['map'])
        if t is None:
            bad.append(f"{j['name']}: connects to {c['map']}, which doesn't exist"); continue
        if t['name'].endswith('_Frlg'):
            bad.append(f"{j['name']}: connects to {c['map']}, an unused FRLG map")
        back = [b for b in (t.get('connections') or []) if b['map'] == mid]
        if not back and mid in LEGACY:
            continue
        if not back:
            bad.append(f"{j['name']} -> {t['name']}: no connection back")
        elif back[0]['direction'] != opp[c['direction']] or back[0]['offset'] != -c['offset']:
            bad.append(f"{j['name']} -> {t['name']}: back is {back[0]['direction']} {back[0]['offset']}, "
                       f"should be {opp[c['direction']]} {-c['offset']}")
print('\n'.join(bad) or 'all connections mirror each other')
sys.exit(1 if bad else 0)
