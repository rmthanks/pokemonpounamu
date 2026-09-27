#!/usr/bin/env python3
"""routekit: compose Pounamu routes from Emerald's own terrain, the way Game Freak did.

Every piece is drawn by the rules the vanilla maps follow (read off Routes 101-123):

  trees      2x2 on the even lattice. Tops 1D4 1D5 (1D6/1D7 when the side is open),
             bottoms 1DC 1DD (1E4 1E5 when the ground below is open, 1E6/1E7 at an
             open side). The grass row above a tree shows the canopy: 1CE 1CF
             (1C6 1C7 on tall grass).
  ponds      top edge 0B0 0B1 0B2, sides 0B8 0BA, water 0A1; the grass row under the
             pond carries the shore lip (002).
  ledges     jump-south: 0D5 087... 0D6.
  rock       tiered mounds: tier 1 lip 068 069 06A, sides 070 072, foot 078 079 07A;
             higher tiers 06B 06C 06D / 073 075 / 07B 07C 07D; interior 071;
             concave foot corners 089 (SW) and 074 (SE).
  paths, sand, sea, tall grass, flowers: AutoTiler learned from the same maps.

A Route is a sketch of classes plus fixed cells; render() turns it into metatiles and
check() runs the gold-standard gates (docs_pounamu/gold-standard-principles.md s.4).
All of it is General (primary) tiles, so it is seam-safe against any neighbour.
"""
import json, os, struct, sys
from collections import Counter, defaultdict, deque

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
from synth import AutoTiler, ROOT, LAYOUTS, read_cells

SAMPLES = ['LAYOUT_ROUTE101', 'LAYOUT_ROUTE102', 'LAYOUT_ROUTE103', 'LAYOUT_PETALBURG_CITY', 'LAYOUT_ROUTE104',
           'LAYOUT_ROUTE110', 'LAYOUT_ROUTE117', 'LAYOUT_ROUTE116', 'LAYOUT_ROUTE118', 'LAYOUT_ROUTE120',
           'LAYOUT_ROUTE123', 'LAYOUT_ROUTE119', 'LAYOUT_LITTLEROOT_TOWN', 'LAYOUT_OLDALE_TOWN', 'LAYOUT_ROUTE121',
           'LAYOUT_ROUTE111', 'LAYOUT_ROUTE109', 'LAYOUT_ROUTE134', 'LAYOUT_ROUTE105', 'LAYOUT_ROUTE113',
           'LAYOUT_ROUTE114', 'LAYOUT_ROUTE115']

# ---------------------------------------------------------------- tile ids
TREE_TL, TREE_TR, TREE_BL, TREE_BR = 0x1D4, 0x1D5, 0x1DC, 0x1DD
TREE_TL_OPEN, TREE_TR_OPEN = 0x1D6, 0x1D7
TREE_BL_OPENB, TREE_BR_OPENB, TREE_BL_OPENSIDE, TREE_BR_OPENSIDE = 0x1E4, 0x1E5, 0x1E6, 0x1E7
CANOPY_L, CANOPY_R, CANOPY_TALL_L, CANOPY_TALL_R = 0x1CE, 0x1CF, 0x1C6, 0x1C7
TREE_IDS = {0x1D4, 0x1D5, 0x1DC, 0x1DD, 0x1D6, 0x1D7, 0x1E4, 0x1E5, 0x1E6, 0x1E7}
TREE_TOP_L = {0x1D4, 0x1D6}; TREE_TOP_R = {0x1D5, 0x1D7}
TREE_BOT_L = {0x1DC, 0x1E4, 0x1E6}; TREE_BOT_R = {0x1DD, 0x1E5, 0x1E7}
GRASS, TALL, FLOWER, SHORE_LIP = 0x001, 0x00D, 0x004, 0x002
POND = dict(tl=0x0B0, t=0x0B1, tr=0x0B2, l=0x0B8, r=0x0BA, c=0x0A1)
LEDGE_L, LEDGE, LEDGE_R = 0x0D5, 0x087, 0x0D6
SIGN = 0x003
PATH = [0x113, 0x114, 0x115, 0x118, 0x119, 0x11A, 0x120, 0x121, 0x122, 0x128, 0x129, 0x12A]
BEACH = [0x124, 0x11C, 0x13D, 0x13E]
SEA = [0x170, 0x171, 0x123, 0x125, 0x12B, 0x12C, 0x12D, 0x145, 0x146, 0x11B, 0x11D]
ROCK_IDS = set(range(0x060, 0x0A0)) | {0x0BE, 0x0BF}
# tier 1 (against the ground) and tier 2+ (against a lower tier)
ROCK1 = dict(nw=0x068, n=0x069, ne=0x06A, w=0x070, e=0x072, sw=0x078, s=0x079, se=0x07A, c=0x071)
ROCK2 = dict(nw=0x06B, n=0x06C, ne=0x06D, w=0x073, e=0x075, sw=0x07B, s=0x07C, se=0x07D, c=0x071)
ROCK_CONCAVE_SW, ROCK_CONCAVE_SE = 0x089, 0x074
BOULDER = [0x093, 0x094, 0x09B, 0x09C]     # 2x2 rock on a mountain top

COL = 0x400


def _attrs():
    a = defaultdict(Counter)
    for s in SAMPLES:
        w, h, c = read_cells(s)
        for v in c:
            if (v & 0x3FF) < 0x200:
                a[v & 0x3FF][v & 0xFC00] += 1
    return {m: c.most_common(1)[0][0] for m, c in a.items()}
ATTR = _attrs()
ATTR.update({GRASS: 0x3000, TALL: 0x3000, FLOWER: 0x3000, SHORE_LIP: 0x3000, SIGN: 0x400,
             CANOPY_L: 0x3000, CANOPY_R: 0x3000, CANOPY_TALL_L: 0x3000, CANOPY_TALL_R: 0x3000})
for t in TREE_IDS:
    ATTR[t] = COL
for m in ROCK_IDS:
    ATTR[m] = COL
for m in POND.values():
    ATTR[m] = 0x1000
ATTR[LEDGE] = ATTR[LEDGE_L] = ATTR[LEDGE_R] = 0x3400


def val(m):
    return m | ATTR.get(m, 0x3000)


_AT = None
def autotiler():
    global _AT
    if _AT is None:
        _AT = AutoTiler(SAMPLES, {'.': [GRASS], ',': [TALL], 'P': PATH, 'S': SEA, '*': [FLOWER],
                                  'p': [0x1D0, 0x1D1, 0x1D2, 0x1D8, 0x1D9, 0x1DA, 0x1E0, 0x1E1, 0x1E2]},
                        texture='.,*')
    return _AT


# ---------------------------------------------------------------- behaviours (walkability)
def _behaviours():
    b = {}
    for tsdir, base in (('data/tilesets/primary/general', 0), ('data/tilesets/secondary/petalburg', 0x200)):
        raw = open(os.path.join(ROOT, tsdir, 'metatile_attributes.bin'), 'rb').read()
        for i in range(len(raw) // 2):
            b[base + i] = struct.unpack('<H', raw[i * 2:i * 2 + 2])[0] & 0xFF
    return b
BEH = _behaviours()
MB_JUMP = {0x38: (1, 0), 0x39: (-1, 0), 0x3A: (0, -1), 0x3B: (0, 1)}   # east, west, north, south
WATER_BEH = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x22, 0x23, 0x24, 0x25}


def _jump_codes():
    import re
    src = open(os.path.join(ROOT, 'include/constants/metatile_behaviors.h')).read()
    names, i = {}, 0
    for line in src[src.index('enum'):].split('\n'):
        m = re.match(r'\s*(MB_[A-Z0-9_]+)\s*(=\s*(\w+))?,', line)
        if m:
            if m.group(3):
                i = int(m.group(3), 0)
            names[m.group(1)] = i
            i += 1
    j = {names['MB_JUMP_EAST']: (1, 0), names['MB_JUMP_WEST']: (-1, 0),
         names['MB_JUMP_NORTH']: (0, -1), names['MB_JUMP_SOUTH']: (0, 1)}
    water = {names[k] for k in ('MB_POND_WATER', 'MB_OCEAN_WATER', 'MB_DEEP_WATER', 'MB_SEMI_DEEP_WATER',
                                'MB_INTERIOR_DEEP_WATER', 'MB_SOOTOPOLIS_DEEP_WATER', 'MB_WATERFALL',
                                'MB_EASTWARD_CURRENT', 'MB_WESTWARD_CURRENT', 'MB_NORTHWARD_CURRENT',
                                'MB_SOUTHWARD_CURRENT', 'MB_NO_SURFACING', 'MB_SEAWEED', 'MB_SEAWEED_NO_SURFACING')
             if k in names}
    return j, water, names
MB_JUMP, WATER_BEH, MB = _jump_codes()


# ---------------------------------------------------------------- the route canvas
class Route:
    """cls chars: '.' grass  ',' tall grass  'T' tree  'P' path/sand  'S' sea  'W' pond  'L' ledge
    '*' flowers  'R' rock (see lev)  '#' fixed cell (see fix)"""

    def __init__(self, W, H, name):
        self.W, self.H, self.name = W, H, name
        self.cls = [['.'] * W for _ in range(H)]
        self.lev = [[0] * W for _ in range(H)]
        self.fix = {}
        self.notes = []

    # -- primitives
    def inb(self, x, y):
        return 0 <= x < self.W and 0 <= y < self.H

    def fill(self, x0, y0, x1, y1, ch):
        for y in range(max(0, y0), min(self.H, y1 + 1)):
            for x in range(max(0, x0), min(self.W, x1 + 1)):
                self.cls[y][x] = ch
                self.lev[y][x] = 0
                self.fix.pop((x, y), None)

    def trees(self, x0, y0, x1, y1):
        """forest over the box, snapped outward to whole 2x2 trees on the even lattice"""
        x0, y0 = x0 - x0 % 2, y0 - y0 % 2
        x1, y1 = x1 + (1 - x1 % 2), y1 + (1 - y1 % 2)
        self.fill(x0, y0, x1, y1, 'T')

    def clear(self, x0, y0, x1, y1, ch='.'):
        """open ground; any tree the box cuts is removed whole (no half trees)"""
        x0e, y0e = x0 - x0 % 2, y0 - y0 % 2
        x1e, y1e = x1 + (1 - x1 % 2), y1 + (1 - y1 % 2)
        for y in range(max(0, y0e), min(self.H, y1e + 1)):
            for x in range(max(0, x0e), min(self.W, x1e + 1)):
                if self.cls[y][x] == 'T':
                    self.cls[y][x] = '.'
        self.fill(x0, y0, x1, y1, ch)

    def path(self, pts, w=2):
        """a path through waypoints, drawn with a w x w brush (horizontal then vertical legs)"""
        for (ax, ay), (bx, by) in zip(pts, pts[1:]):
            for x in range(min(ax, bx), max(ax, bx) + 1):
                self.clear(x, ay, x + w - 1, ay + w - 1, 'P')
            for y in range(min(ay, by), max(ay, by) + 1):
                self.clear(bx, y, bx + w - 1, y, 'P')

    def pond(self, x0, y0, x1, y1):
        self.clear(x0, y0, x1, y1 + 1)
        self.fill(x0, y0, x1, y1, 'W')

    def ledge(self, x0, x1, y):
        self.fill(x0, y, x1, y, 'L')

    def rock(self, x0, y0, x1, y1, tier=1):
        if tier == 1:
            self.clear(x0, y0, x1, y1)
        for y in range(max(0, y0), min(self.H, y1 + 1)):
            for x in range(max(0, x0), min(self.W, x1 + 1)):
                self.cls[y][x] = 'R'
                self.lev[y][x] = max(self.lev[y][x], tier)

    def put(self, x, y, m):
        self.cls[y][x] = '#'
        self.fix[(x, y)] = val(m)

    # -- rendering
    def _tree_tile(self, x, y):
        """the vanilla rules (measured over 22 Hoenn maps): a top shows its open side only
        when nothing grows above it; a bottom shows open ground only when the ground below
        is open, and then its open side too"""
        T = lambda xx, yy: (not self.inb(xx, yy)) or self.cls[yy][xx] == 'T'
        top, left = (y % 2 == 0), (x % 2 == 0)
        if top:
            if left:
                return TREE_TL_OPEN if not T(x - 1, y) and not T(x, y - 1) else TREE_TL
            return TREE_TR_OPEN if not T(x + 1, y) and not T(x, y - 1) else TREE_TR
        if T(x, y + 1):
            return TREE_BL if left else TREE_BR
        if left:
            return TREE_BL_OPENB if T(x - 1, y) else TREE_BL_OPENSIDE
        return TREE_BR_OPENB if T(x + 1, y) else TREE_BR_OPENSIDE

    def _rock_tile(self, x, y):
        k = self.lev[y][x]
        L = lambda dx, dy: (self.lev[y + dy][x + dx] if self.inb(x + dx, y + dy) else k)
        n, s, w, e = L(0, -1) < k, L(0, 1) < k, L(-1, 0) < k, L(1, 0) < k
        t = ROCK1 if k == 1 else ROCK2
        if n:
            return t['nw'] if w else t['ne'] if e else t['n']
        if s:
            return t['sw'] if w else t['se'] if e else t['s']
        if w:
            return t['w']
        if e:
            return t['e']
        if L(-1, 1) < k:
            return ROCK_CONCAVE_SW
        if L(1, 1) < k:
            return ROCK_CONCAVE_SE
        return t['c']

    def render(self, seed=1):
        W, H = self.W, self.H
        # the autotiled classes see everything else as a neighbour of another class
        # trees, ponds, ledges and rock look like "something else" (X) to the autotiler
        sk = [''.join(c if c in '.,PS*p' else 'X' for c in self.cls[y]) for y in range(H)]
        at = autotiler()
        grid = [[None] * W for _ in range(H)]
        import random
        rnd = random.Random(seed)
        for y in range(H):
            for x in range(W):
                if sk[y][x] != 'X':
                    try:
                        grid[y][x] = at.tile_at(sk, x, y, rnd)
                    except KeyError:
                        grid[y][x] = GRASS
        cells = [0] * (W * H)
        for y in range(H):
            for x in range(W):
                c = self.cls[y][x]
                if c == 'T':
                    m = self._tree_tile(x, y)
                elif c == 'W':
                    up = y > 0 and self.cls[y - 1][x] == 'W'
                    lw = x > 0 and self.cls[y][x - 1] == 'W'
                    rw = x < W - 1 and self.cls[y][x + 1] == 'W'
                    if not up:
                        m = POND['tl'] if not lw else POND['tr'] if not rw else POND['t']
                    else:
                        m = POND['l'] if not lw else POND['r'] if not rw else POND['c']
                elif c == 'L':
                    lw = x > 0 and self.cls[y][x - 1] == 'L'
                    rw = x < W - 1 and self.cls[y][x + 1] == 'L'
                    m = LEDGE_L if not lw else LEDGE_R if not rw else LEDGE
                elif c == 'R':
                    m = self._rock_tile(x, y)
                elif c == '#':
                    cells[y * W + x] = self.fix[(x, y)]
                    continue
                else:
                    m = grid[y][x]
                    if c == '.' and y > 0 and self.cls[y - 1][x] == 'W':
                        m = SHORE_LIP
                    elif c in '.,' and y + 1 < H and self.cls[y + 1][x] == 'T' and (y + 1) % 2 == 0 and m in (GRASS, TALL):
                        tall = c == ','
                        m = (CANOPY_TALL_L if tall else CANOPY_L) if x % 2 == 0 else (CANOPY_TALL_R if tall else CANOPY_R)
                cells[y * W + x] = val(m)
        self.cells = cells
        return cells

    # -- analysis
    def meta(self, x, y):
        return self.cells[y * self.W + x] & 0x3FF

    def walkable(self, x, y):
        if not self.inb(x, y):
            return False
        v = self.cells[y * self.W + x]
        return not (v >> 10) & 3 and BEH.get(v & 0x3FF, 0) not in WATER_BEH

    def moves(self, x, y):
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if not self.inb(nx, ny):
                continue
            b = BEH.get(self.meta(nx, ny), 0)
            if b in MB_JUMP and MB_JUMP[b] == (dx, dy):
                lx, ly = nx + dx, ny + dy
                if self.walkable(lx, ly):
                    yield lx, ly
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


# ---------------------------------------------------------------- neighbours and seams
def map_json(folder):
    return json.load(open(os.path.join(ROOT, 'data/maps', folder, 'map.json')))


def folder_of(map_id):
    import glob
    for p in glob.glob(os.path.join(ROOT, 'data/maps/*/map.json')):
        j = json.load(open(p))
        if j['id'] == map_id:
            return j['name']
    raise KeyError(map_id)


def neighbour_edge(folder, side):
    """the neighbour's cells along the edge that faces us: list of metatile values.
    side = the neighbour's own edge ('top', 'bottom', 'left', 'right'), outermost first (2 rows)."""
    j = map_json(folder)
    w, h, c = read_cells(j['layout'])
    if side == 'top':
        return [[c[y * w + x] for x in range(w)] for y in (0, 1)], w, h
    if side == 'bottom':
        return [[c[y * w + x] for x in range(w)] for y in (h - 1, h - 2)], w, h
    if side == 'left':
        return [[c[y * w + x] for y in range(h)] for x in (0, 1)], w, h
    return [[c[y * w + x] for y in range(h)] for x in (w - 1, w - 2)], w, h


def cell_walkable(v):
    return not (v >> 10) & 3 and BEH.get(v & 0x3FF, 0) not in WATER_BEH


def check_seam(route, direction, folder, offset):
    """walkable gaps and tree lattice must line up across the seam. direction = the route's side."""
    W, H = route.W, route.H
    side = {'up': 'bottom', 'down': 'top', 'left': 'right', 'right': 'left'}[direction]
    edge, nw, nh = neighbour_edge(folder, side)
    problems = []
    if direction in ('up', 'down'):
        ry = 0 if direction == 'up' else H - 1
        for x in range(W):
            nx = x - offset
            if not (0 <= nx < nw):
                if route.walkable(x, ry):
                    problems.append(f'walkable edge cell ({x},{ry}) has no neighbour beyond it')
                continue
            a, b = route.walkable(x, ry), cell_walkable(edge[0][nx])
            if a != b:
                problems.append(f'seam mismatch at x={x}: route {"open" if a else "blocked"}, {folder} {"open" if b else "blocked"}')
            rm, nm = route.meta(x, ry), edge[0][nx] & 0x3FF
            # tree phase: across a horizontal seam a top must meet a bottom
            if rm in TREE_IDS and nm in TREE_IDS:
                if direction == 'up' and not (rm in TREE_TOP_L | TREE_TOP_R and nm in TREE_BOT_L | TREE_BOT_R):
                    problems.append(f'tree phase broken across seam at x={x}')
                if direction == 'down' and not (rm in TREE_BOT_L | TREE_BOT_R and nm in TREE_TOP_L | TREE_TOP_R):
                    problems.append(f'tree phase broken across seam at x={x}')
                if (rm in TREE_TOP_L | TREE_BOT_L) != (nm in TREE_TOP_L | TREE_BOT_L):
                    problems.append(f'tree left/right phase broken across seam at x={x}')
    else:
        rx = 0 if direction == 'left' else W - 1
        for y in range(H):
            ny = y - offset
            if not (0 <= ny < nh):
                if route.walkable(rx, y):
                    problems.append(f'walkable edge cell ({rx},{y}) has no neighbour beyond it')
                continue
            a, b = route.walkable(rx, y), cell_walkable(edge[0][ny])
            if a != b:
                problems.append(f'seam mismatch at y={y}: route {"open" if a else "blocked"}, {folder} {"open" if b else "blocked"}')
            rm, nm = route.meta(rx, y), edge[0][ny] & 0x3FF
            if rm in TREE_IDS and nm in TREE_IDS:
                if (rm in TREE_TOP_L | TREE_TOP_R) != (nm in TREE_TOP_L | TREE_TOP_R):
                    problems.append(f'tree top/bottom phase broken across seam at y={y}')
                if direction == 'left' and not (rm in TREE_TOP_L | TREE_BOT_L and nm in TREE_TOP_R | TREE_BOT_R):
                    problems.append(f'tree phase broken across seam at y={y}')
                if direction == 'right' and not (rm in TREE_TOP_R | TREE_BOT_R and nm in TREE_TOP_L | TREE_BOT_L):
                    problems.append(f'tree phase broken across seam at y={y}')
    return problems


def neighbour_gap(folder, side):
    """columns (or rows) where the neighbour's facing edge is walkable"""
    edge, nw, nh = neighbour_edge(folder, side)
    return [i for i, v in enumerate(edge[0]) if cell_walkable(v)], nw, nh


# ---------------------------------------------------------------- gates
def check_trees(route):
    bad = []
    W, H = route.W, route.H
    for y in range(H):
        for x in range(W):
            m = route.meta(x, y)
            if m not in TREE_IDS:
                continue
            top, left = m in TREE_TOP_L | TREE_TOP_R, m in TREE_TOP_L | TREE_BOT_L
            ox, oy = (x if left else x - 1), (y if top else y - 1)
            want = [(ox, oy, TREE_TOP_L), (ox + 1, oy, TREE_TOP_R), (ox, oy + 1, TREE_BOT_L), (ox + 1, oy + 1, TREE_BOT_R)]
            for px, py, s in want:
                if route.inb(px, py) and route.meta(px, py) not in s:
                    bad.append((x, y)); break
    return bad


def check_pairs(route):
    """tile neighbour pairs never seen in any vanilla sample (a pointer, not a verdict)"""
    seen = set()
    for s in SAMPLES + ['LAYOUT_ROUTE101']:
        w, h, c = read_cells(s)
        for y in range(h):
            for x in range(w):
                a = c[y * w + x] & 0x3FF
                if x + 1 < w:
                    seen.add(('h', a, c[y * w + x + 1] & 0x3FF))
                if y + 1 < h:
                    seen.add(('v', a, c[(y + 1) * w + x] & 0x3FF))
    odd = []
    for y in range(route.H):
        for x in range(route.W):
            a = route.meta(x, y)
            if x + 1 < route.W and ('h', a, route.meta(x + 1, y)) not in seen:
                odd.append(('h', x, y, hex(a), hex(route.meta(x + 1, y))))
            if y + 1 < route.H and ('v', a, route.meta(x, y + 1)) not in seen:
                odd.append(('v', x, y, hex(a), hex(route.meta(x, y + 1))))
    return odd


def sight_cells(route, x, y, face, rng):
    d = {'UP': (0, -1), 'DOWN': (0, 1), 'LEFT': (-1, 0), 'RIGHT': (1, 0)}[face]
    out = []
    for i in range(1, rng + 1):
        cx, cy = x + d[0] * i, y + d[1] * i
        if not route.walkable(cx, cy):
            break
        out.append((cx, cy))
    return out


# ---------------------------------------------------------------- output
def write_layout(route, layout_id, border=(TREE_TL, TREE_TR, TREE_BL, TREE_BR)):
    lay = LAYOUTS[layout_id]
    open(os.path.join(ROOT, lay['blockdata_filepath']), 'wb').write(struct.pack(f'<{len(route.cells)}H', *route.cells))
    open(os.path.join(ROOT, lay['border_filepath']), 'wb').write(struct.pack('<4H', *[val(m) for m in border]))
    lp = os.path.join(ROOT, 'data/layouts/layouts.json')
    txt = open(lp).read()
    i = txt.index(f'"id": "{layout_id}"')
    for key, v in (('width', route.W), ('height', route.H)):
        j = txt.index(f'"{key}":', i)
        k = min(txt.index(',', j), txt.index('\n', j))
        txt = txt[:j] + f'"{key}": {v}' + txt[k:]
    open(lp, 'w').write(txt)


def save_map_json(folder, j):
    open(os.path.join(ROOT, 'data/maps', folder, 'map.json'), 'w').write(json.dumps(j, indent=2, ensure_ascii=False) + '\n')


def set_connection(folder, target_id, offset, reverse_folder=None):
    """set our connection to target_id and the target's reverse connection to us"""
    j = map_json(folder)
    for cn in j['connections']:
        if cn['map'] == target_id:
            cn['offset'] = offset
    save_map_json(folder, j)
    rf = reverse_folder or folder_of(target_id)
    rj = map_json(rf)
    for cn in rj['connections']:
        if cn['map'] == j['id']:
            cn['offset'] = -offset
    save_map_json(rf, rj)


def preview(route, path, scale=1, events=None):
    import render_tiles as rt
    from PIL import ImageDraw
    img = rt.TilesetPair('gTileset_General', 'gTileset_Petalburg').render_map(route.cells, route.W, scale=scale)
    if events:
        d = ImageDraw.Draw(img)
        for (x, y, colour) in events:
            d.rectangle([x * 16 * scale + 3 * scale, y * 16 * scale + 3 * scale,
                         x * 16 * scale + 12 * scale, y * 16 * scale + 12 * scale], outline=colour, width=scale)
    img.save(path)


# ---------------------------------------------------------------- hand-drawn routes
PALE = [0x1D0, 0x1D1, 0x1D2, 0x1D8, 0x1D9, 0x1DA, 0x1E0, 0x1E1, 0x1E2]
TERRAIN = set('.,PWLRQ*TpSs')


def from_ascii(name, rows, markers=''):
    """build a Route from a hand-drawn map. Legend:
    T tree (2x2 on the even lattice)  . grass  , tall grass  P path/sand  W pond  L ledge (jump south)
    R rock  Q upper rock tier  * flowers  p worn pale ground  S sea  s sign
    any character in `markers` = an event spot on grass (returned in route.marks)"""
    H, W = len(rows), len(rows[0])
    for i, row in enumerate(rows):
        if len(row) != W:
            raise ValueError(f'{name}: row {i} is {len(row)} wide, expected {W}')
    r = Route(W, H, name)
    r.marks = {}
    r.snap_warnings = []
    for y, row in enumerate(rows):
        for x, ch in enumerate(row):
            if ch in markers:
                r.marks.setdefault(ch, []).append((x, y))
                ch = '.'
            if ch == 'Q':
                r.cls[y][x] = 'R'; r.lev[y][x] = 2
            elif ch == 'R':
                r.cls[y][x] = 'R'; r.lev[y][x] = 1
            elif ch == 's':
                r.cls[y][x] = '#'; r.fix[(x, y)] = val(SIGN)
                r.marks.setdefault('s', []).append((x, y))
            elif ch in TERRAIN:
                r.cls[y][x] = ch
            else:
                raise ValueError(f'{name}: unknown map character {ch!r} at ({x},{y})')
    # snap trees to whole 2x2 trees; report anything that had to move
    for by in range(0, H, 2):
        for bx in range(0, W, 2):
            cells = [(bx + dx, by + dy) for dy in (0, 1) for dx in (0, 1) if bx + dx < W and by + dy < H]
            t = sum(r.cls[y][x] == 'T' for x, y in cells)
            if 0 < t < len(cells):
                r.snap_warnings.append((bx, by, t))
                for x, y in cells:
                    if r.cls[y][x] == 'T':
                        r.cls[y][x] = '.'
    return r


def lint_shapes(r):
    """shapes the tiles cannot draw: 1-thick paths, lone ledge cells, thin rock, bad tier insets"""
    out = []
    W, H = r.W, r.H
    C = lambda x, y: r.cls[y][x] if r.inb(x, y) else None
    for y in range(H):
        for x in range(W):
            c = r.cls[y][x]
            if c == 'P':
                ok = any(all(C(x + dx + i, y + dy + j) == 'P' for i in (0, 1) for j in (0, 1))
                         for dx in (-1, 0) for dy in (-1, 0))
                if not ok:
                    out.append(f'thin path at ({x},{y})')
            if c == 'L' and C(x - 1, y) != 'L' and C(x + 1, y) != 'L':
                out.append(f'lone ledge at ({x},{y})')
            if c == 'L' and C(x, y + 1) not in ('.', ',', 'P', '*', 'p'):
                out.append(f'ledge at ({x},{y}) lands on {C(x, y + 1)!r}')
            if c == 'W':
                if C(x, y + 1) not in ('W', '.'):
                    out.append(f'pond at ({x},{y}) needs grass below it for the shore')
            if c == 'R':
                k = r.lev[y][x]
                ok = any(all(r.inb(x + dx + i, y + dy + j) and r.lev[y + dy + j][x + dx + i] >= k
                             for i in range(3) for j in range(2))
                         for dx in (-2, -1, 0) for dy in (-1, 0)) or \
                     any(all(r.inb(x + dx + i, y + dy + j) and r.lev[y + dy + j][x + dx + i] >= k
                             for i in range(2) for j in range(3))
                         for dx in (-1, 0) for dy in (-2, -1, 0))
                if not ok:
                    out.append(f'rock too thin at ({x},{y})')
                if k >= 2:
                    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        nx, ny = x + dx, y + dy
                        if r.inb(nx, ny) and r.lev[ny][nx] < k - 1:
                            out.append(f'upper rock tier touches the ground at ({x},{y})')
                            break
    return out
