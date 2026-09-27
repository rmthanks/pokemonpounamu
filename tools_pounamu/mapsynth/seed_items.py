#!/usr/bin/env python3
"""Item balls on the routes (Sept 2026).

Every mainline route hides a few Poke Balls off the main road - a nook behind the trees,
the far side of the tall grass, the end of a beach - and Pounamu's rebuilt routes had none.
This picks the spots by rule and writes them into the route's spec (markers 1/2/3, so a
rebuild keeps them) and its map.json:
  - off the line between the route's exits, a short detour away
  - in a nook (two or three sides closed), on plain ground, never a path
  - never on the only way through: with the ball standing, every cell of the route that
    could be reached before still can be (so no area is ever cut off)
  - clear of people, signs, hidden items, warps, story triggers and the map's edges
  - spread along the route
The items follow the level curve. Flags come from FLAG_UNUSED_0x4BB.. and 0x493..
(checked free: nothing else in data/, src/, include/ or the tools names them).
The Desert Road is drawn by its own builder, so it gets its balls straight into map.json.
  python3 tools_pounamu/mapsynth/seed_items.py            # show the picks
  python3 tools_pounamu/mapsynth/seed_items.py --write    # write spec rows + map.json"""
import importlib, json, os, re, struct, subprocess, sys
from collections import deque
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path[:0] = [os.path.join(HERE, 'routes'), HERE]
import routekit as rk

ROOT = rk.ROOT
# story order, with what each route's balls hold (the level curve runs 2-4 ... 32-36)
PLAN = [
    ('orchard_road',  ['ITEM_POTION', 'ITEM_POKE_BALL']),
    ('route2_bay',    ['ITEM_ANTIDOTE', 'ITEM_POKE_BALL', 'ITEM_POTION']),
    ('route2_north',  ['ITEM_PARALYZE_HEAL', 'ITEM_REPEL', 'ITEM_POTION']),
    ('route2_east',   ['ITEM_SUPER_POTION', 'ITEM_X_ATTACK', 'ITEM_POKE_BALL']),
    ('route35a',      ['ITEM_GREAT_BALL', 'ITEM_ESCAPE_ROPE', 'ITEM_AWAKENING']),
    ('route35b',      ['ITEM_ETHER', 'ITEM_BURN_HEAL', 'ITEM_SUPER_POTION']),
    ('route2_bop',    ['ITEM_GREAT_BALL', 'ITEM_SUPER_REPEL', 'ITEM_X_DEFENSE']),
    ('route36',       ['ITEM_PP_UP', 'ITEM_ICE_HEAL', 'ITEM_SUPER_POTION']),
    ('route5',        ['ITEM_RARE_CANDY', 'ITEM_FULL_HEAL', 'ITEM_GREAT_BALL']),
    ('route5_ranges', ['ITEM_MAX_ETHER', 'ITEM_REVIVE', 'ITEM_NUGGET']),
    ('DESERT',        ['ITEM_HYPER_POTION', 'ITEM_REVIVE', 'ITEM_SUPER_REPEL']),
    ('route43',       ['ITEM_ULTRA_BALL', 'ITEM_HYPER_POTION', 'ITEM_X_SP_ATK']),
    ('route3',        ['ITEM_FULL_HEAL', 'ITEM_ELIXIR', 'ITEM_ULTRA_BALL']),
    ('route1_kapiti', ['ITEM_MAX_REPEL', 'ITEM_HYPER_POTION', 'ITEM_PROTEIN']),
    ('route6',        ['ITEM_REVIVE', 'ITEM_ULTRA_BALL', 'ITEM_CALCIUM']),
    ('route7',        ['ITEM_RARE_CANDY', 'ITEM_FULL_RESTORE', 'ITEM_MAX_ETHER']),
    ('route1_south',  ['ITEM_MAX_REVIVE', 'ITEM_MAX_POTION', 'ITEM_PP_UP']),
]
FLAG_POOL = list(range(0x4BB, 0x4E0)) + list(range(0x493, 0x4A7))
MARKS = '123'
N4 = ((1, 0), (-1, 0), (0, 1), (0, -1))


def use_secondary(tileset):
    """walkability of a secondary tileset's own tiles"""
    sys.path.insert(0, os.path.join(ROOT, 'tools_pounamu'))
    from render_tiles import TILESET_DIRS
    raw = open(os.path.join(ROOT, TILESET_DIRS[tileset], 'metatile_attributes.bin'), 'rb').read()
    for k in [k for k in rk.BEH if k >= 0x200]:
        del rk.BEH[k]
    for i in range(len(raw) // 2):
        rk.BEH[0x200 + i] = struct.unpack('<H', raw[i * 2:i * 2 + 2])[0] & 0xFF


def free_flags():
    """FLAG_UNUSED_0x... defines that nothing else in the repo names"""
    txt = open(os.path.join(ROOT, 'include/constants/flags.h')).read()
    defined = set(int(h, 16) for h in re.findall(r'#define FLAG_UNUSED_0x([0-9A-Fa-f]+)\s', txt))
    out = subprocess.run(['grep', '-rhoE', 'FLAG_UNUSED_0x[0-9A-Fa-f]+', 'data', 'src', 'include',
                          '--include=*.json', '--include=*.inc', '--include=*.c', '--include=*.h',
                          '--include=*.s', '--include=*.pory'], cwd=ROOT, capture_output=True, text=True).stdout.split()
    count = {}
    for n in out:
        v = int(n[len('FLAG_UNUSED_0x'):], 16)
        count[v] = count.get(v, 0) + 1
    return [v for v in FLAG_POOL if v in defined and count.get(v, 0) <= 1]


class Grid:
    """what the seeding needs to know about a map, from a route spec or from map.bin"""

    def __init__(self, folder):
        self.folder = folder
        self.mj = rk.map_json(folder)
        lay = rk.LAYOUTS[self.mj['layout']]
        self.W, self.H = lay['width'], lay['height']
        raw = open(os.path.join(ROOT, lay['blockdata_filepath']), 'rb').read()
        self.cells = list(struct.unpack(f'<{self.W * self.H}H', raw))

    def v(self, x, y):
        return self.cells[y * self.W + x]

    def walkable(self, x, y):
        if not (0 <= x < self.W and 0 <= y < self.H):
            return False
        v = self.v(x, y)
        b = rk.BEH.get(v & 0x3FF, 0)
        return not (v >> 10) & 3 and b not in rk.WATER_BEH and b not in rk.MB_JUMP

    def moves(self, x, y):
        for dx, dy in N4:
            nx, ny = x + dx, y + dy
            if not (0 <= nx < self.W and 0 <= ny < self.H):
                continue
            b = rk.BEH.get(self.v(nx, ny) & 0x3FF, 0)
            if b in rk.MB_JUMP and rk.MB_JUMP[b] == (dx, dy):
                if self.walkable(nx + dx, ny + dy):
                    yield nx + dx, ny + dy
            elif self.walkable(nx, ny):
                yield nx, ny

    def reach(self, starts, blocked=()):
        seen, q = set(starts), deque(starts)
        blocked = set(blocked)
        while q:
            p = q.popleft()
            for n in self.moves(*p):
                if n not in seen and n not in blocked:
                    seen.add(n); q.append(n)
        return seen


def exits_of(g):
    out = {}
    for cn in g.mj['connections']:
        d = cn['direction']
        if d == 'up':
            cells = [(x, 0) for x in range(g.W) if g.walkable(x, 0)]
        elif d == 'down':
            cells = [(x, g.H - 1) for x in range(g.W) if g.walkable(x, g.H - 1)]
        elif d == 'left':
            cells = [(0, y) for y in range(g.H) if g.walkable(0, y)]
        else:
            cells = [(g.W - 1, y) for y in range(g.H) if g.walkable(g.W - 1, y)]
        if cells:
            out[cn['map']] = cells
    for w in g.mj['warp_events']:
        out.setdefault('warps', []).append((w['x'], w['y']))
    return out


def adjacency(g, main):
    """who can step to whom, both ways (a ledge jump joins the cells either side of it)"""
    adj = {c: set() for c in main}
    for p in main:
        for n in g.moves(*p):
            if n in main:
                adj[p].add(n); adj[n].add(p)
    return adj


def main_line(g, main, adj, exits, road=()):
    """the cells on the shortest walks between the route's exits (a dead-end route: its road)"""
    line = set()
    groups = [set(c for c in cs if c in main) for k, cs in exits.items() if k != 'warps']
    groups = [s for s in groups if s]
    if len(groups) < 2:
        return {c for c in road if c in main}
    road_line = {c for c in road if c in main}
    for i in range(len(groups)):
        for j in range(i + 1, len(groups)):
            prev = {c: None for c in groups[i]}
            q = deque(groups[i])
            end = None
            while q:
                p = q.popleft()
                if p in groups[j]:
                    end = p; break
                for n in adj[p]:
                    if n not in prev:
                        prev[n] = p; q.append(n)
            while end is not None:
                line.add(end); end = prev[end]
    return line or road_line


def dist_from(cells, adj):
    d = {c: 0 for c in cells}
    q = deque(cells)
    while q:
        p = q.popleft()
        for n in adj[p]:
            if n not in d:
                d[n] = d[p] + 1; q.append(n)
    return d


def pick(g, k, ground_ok, avoid, blocked, label, road=()):
    exits = exits_of(g)
    starts = [c for cs in exits.values() for c in cs if g.walkable(*c)]
    main = g.reach(starts, blocked)
    adj = adjacency(g, main)
    line = main_line(g, main, adj, exits, road)
    off = dist_from(line, adj)
    cands = []
    for (x, y) in main:
        if (x, y) in line or not ground_ok(x, y):
            continue
        if x < 2 or y < 2 or x >= g.W - 2 or y >= g.H - 2:
            continue
        if any(abs(x - ax) + abs(y - ay) < 3 for ax, ay in avoid):
            continue
        o = off.get((x, y), 99)
        if not 2 <= o <= 18:
            continue
        closed = sum(1 for dx, dy in N4 if not g.walkable(x + dx, y + dy))
        if closed < 2:
            continue
        cands.append((closed * 3 + min(o, 10), (x, y)))
    cands.sort(reverse=True)
    chosen = []
    sep = max(10, (g.W + g.H) // (k + 2))
    for score, c in cands:
        if len(chosen) == k:
            break
        if any(abs(c[0] - a[0]) + abs(c[1] - a[1]) < sep for a in chosen):
            continue
        # never the only way through: everything reachable before still is
        after = g.reach(starts, blocked | set(chosen) | {c})
        if after != main - set(chosen) - {c}:
            continue
        chosen.append(c)
    if len(chosen) < k:
        print(f'  {label}: only {len(chosen)} of {k} spots found')
    return chosen


def spec_route(modname):
    mod = importlib.import_module(modname)
    S = mod.SPEC
    markers = ''.join(S.get('objects', {}).keys()) + ''.join(S.get('hidden', {}).keys())
    if S.get('seal'):
        markers += S['seal']['beyond']
    r = rk.from_ascii(S['folder'], S['rows'], markers)
    r.pond_open_top = set(S.get('pond_open_top', ()))
    r.render(seed=S.get('seed', 1))
    return mod, S, r, markers


def ground_votes(rows, x, y):
    votes = {}
    for dx, dy in N4:
        nx, ny = x + dx, y + dy
        if 0 <= ny < len(rows) and 0 <= nx < len(rows[0]):
            c = rows[ny][nx]
            if c in '.,BPp*':
                votes[c] = votes.get(c, 0) + 1
    if sum(votes.values()) < 2:
        return None
    best = max(votes.values())
    for c in '.BP,p*':
        if votes.get(c) == best:
            return c


def item_object(item, x, y, elev, flag):
    return {'graphics_id': 'OBJ_EVENT_GFX_ITEM_BALL', 'x': x, 'y': y, 'elevation': elev,
            'movement_type': 'MOVEMENT_TYPE_FACE_DOWN', 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': 'TRAINER_TYPE_NONE', 'trainer_sight_or_berry_tree_id': item,
            'script': 'Common_EventScript_FindItem', 'flag': f'FLAG_UNUSED_0x{flag:03X}'}


def edit_spec(modname, S, picks):
    """markers into the spec's rows, and the balls into its objects"""
    path = os.path.join(HERE, 'routes', modname + '.py')
    lines = open(path).read().split('\n')
    start = next(i for i, l in enumerate(lines) if l.strip().startswith('rows=['))
    rowlines = []
    for i in range(start + 1, len(lines)):
        s = lines[i].strip()
        if s.startswith(']'):
            break
        if s.startswith('"'):
            rowlines.append(i)
    assert len(rowlines) == len(S['rows']), (modname, len(rowlines), len(S['rows']))
    for y, i in enumerate(rowlines):
        q = lines[i].index('"') + 1
        assert lines[i][q:q + len(S['rows'][y])] == S['rows'][y], (modname, y)
    for mk, (x, y) in picks:
        i = rowlines[y]
        q = lines[i].index('"') + 1
        lines[i] = lines[i][:q + x] + mk + lines[i][q + x + 1:]
    txt = '\n'.join(lines)
    names = ['FindItem'] + [f'FindItem#{i}' for i in range(2, 10)]
    add = ''.join(f"'{mk}': ('{names[i]}', None), " for i, (mk, _) in enumerate(picks))
    j = txt.index('objects={') + len('objects={')
    txt = txt[:j] + '\n        ' + add.rstrip() + txt[j:]
    open(path, 'w').write(txt)


def main():
    write = '--write' in sys.argv
    flags = free_flags()
    print(f'free flags in the pool: {len(flags)}')
    fi = 0
    for modname, items in PLAN:
        if modname == 'DESERT':
            use_secondary('gTileset_Fallarbor')
            g = Grid('Route1Desert')
            if any(o['script'] == 'Common_EventScript_FindItem' for o in g.mj['object_events']):
                print('Route1Desert: already has its balls'); continue
            objs = g.mj['object_events']
            blocked = {(o['x'], o['y']) for o in objs}
            avoid = blocked | {(b['x'], b['y']) for b in g.mj['bg_events']} | \
                    {(w['x'], w['y']) for w in g.mj['warp_events']} | {(c['x'], c['y']) for c in g.mj['coord_events']}
            plain = lambda x, y: (g.v(x, y) & 0x3FF) in (0x218, 0x229)     # the ash ground
            spots = pick(g, len(items), plain, avoid, blocked, 'Route1Desert')
            print(f'Route1Desert: {spots}')
            if write:
                for item, (x, y) in zip(items, spots):
                    objs.append(item_object(item, x, y, (g.v(x, y) >> 12) & 0xF or 3, flags[fi])); fi += 1
                rk.save_map_json('Route1Desert', g.mj)
            else:
                fi += len(spots)
            use_secondary('gTileset_Petalburg')
            continue
        mod, S, r, markers = spec_route(modname)
        if any(m in markers for m in MARKS):
            print(f'{S["folder"]}: already has its balls'); continue
        g = Grid(S['folder'])                    # walk what the game walks (map.bin)
        objs = g.mj['object_events']
        split = {mk for mk, (suffix, face) in S.get('objects', {}).items() if suffix in S.get('split_by', ())}
        placed = [r.marks[mk][0] for mk in S.get('objects', {}) if len(r.marks.get(mk, [])) == 1 and mk not in split]
        story = [r.marks[mk][0] for mk in split if len(r.marks.get(mk, [])) == 1]
        hidden = [r.marks[mk][0] for mk in S.get('hidden', {}) if len(r.marks.get(mk, [])) == 1]
        blocked = set(placed)
        avoid = blocked | set(story) | set(hidden) | set(r.marks.get('s', [])) | \
                {(w['x'], w['y']) for w in g.mj['warp_events']} | {(c['x'], c['y']) for c in g.mj['coord_events']}
        # plain ground whose marker would draw the same ground (so the layout is unchanged)
        ok = lambda x, y: S['rows'][y][x] in '.B' and ground_votes(S['rows'], x, y) == S['rows'][y][x] \
            and (x, y) not in r.solid
        k = len(items) if len(r.reach([c for cs in exits_of(g).values() for c in cs], blocked)) > 900 else 2
        road = [(x, y) for y, row in enumerate(S['rows']) for x, ch in enumerate(row) if ch == 'P']
        spots = pick(g, k, ok, avoid, blocked, S['folder'], road)
        print(f'{S["folder"]}: {spots}')
        picks = list(zip(MARKS, spots))
        if write and spots:
            edit_spec(modname, S, picks)
            for item, (x, y) in zip(items, spots):
                objs.append(item_object(item, x, y, (r.cells[y * r.W + x] >> 12) & 0xF or 3, flags[fi])); fi += 1
            rk.save_map_json(S['folder'], g.mj)
        else:
            fi += len(spots)
    print(f'flags used: {fi}')


if __name__ == '__main__':
    main()
