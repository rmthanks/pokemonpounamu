#!/usr/bin/env python3
"""Build a Pounamu town: ground drawn by routekit's vanilla rules, buildings stamped whole
from Emerald's towns, every event re-homed, then the same gates as the routes (Sept 2026).

Each tools_pounamu/mapsynth/towns/<town>.py composes a Canvas and calls build(SPEC).
  python3 tools_pounamu/mapsynth/towns/<town>.py            # check + preview
  python3 tools_pounamu/mapsynth/towns/<town>.py --write    # also write layout, events, heal spot

SPEC keys:
  folder, layout, tileset     map folder, its layout id, the secondary tileset it is drawn with
  rows                        ground classes (routekit.from_ascii legend); stamps go over them
  stamps                      [(stamp name, x, y, warp index | [indices] | None)]  top-left corner
  warps                       {warp index: (x, y)} for warps that are not a stamp's door
  objects                     {script suffix (object_names): (x, y, facing or None)}
  signs                       [(x, y, script label)]  label = existing <Town>_EventScript_<label>,
                              or (label, [lines]) to write a new sign
  hidden                      {index among the old hidden items: (x, y)}
  conns                       {neighbour map id: offset}  (ours; the neighbour gets the negative)
  pc_warp                     the Pokemon Center's warp index (heal spot = the cell below its door)
  allow_unreached             object suffixes that may stand off the walkable town (behind counters...)
"""
import json, os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
MS = os.path.dirname(HERE)
sys.path.insert(0, MS); sys.path.insert(0, os.path.dirname(MS)); sys.path.insert(0, HERE)
import routekit as rk
import context_view as cv
from library import stamp as get_stamp
sys.path.insert(0, os.path.join(MS, 'routes'))
from build import object_names, fail

OUT = os.path.join(MS, 'out')
FACES = {'UP', 'DOWN', 'LEFT', 'RIGHT'}


def use_secondary(tileset):
    """walkability of the secondary's own tiles (doors, docks, hot springs...)"""
    sys.path.insert(0, os.path.join(rk.ROOT, 'tools_pounamu'))
    from render_tiles import TILESET_DIRS
    raw = open(os.path.join(rk.ROOT, TILESET_DIRS[tileset], 'metatile_attributes.bin'), 'rb').read()
    for k in [k for k in rk.BEH if k >= 0x200]:
        del rk.BEH[k]
    for i in range(len(raw) // 2):
        rk.BEH[0x200 + i] = struct.unpack('<H', raw[i * 2:i * 2 + 2])[0] & 0xFF


class Canvas:
    """compose a town's ground by rectangles (inclusive corners)"""
    def __init__(self, W, H, fill='.'):
        self.W, self.H = W, H
        self.g = [[fill] * W for _ in range(H)]

    def box(self, x0, y0, x1, y1, ch, only=None):
        for y in range(max(0, y0), min(self.H, y1 + 1)):
            for x in range(max(0, x0), min(self.W, x1 + 1)):
                if only is None or self.g[y][x] in only:
                    self.g[y][x] = ch

    def at(self, x, y, ch):
        self.g[y][x] = ch

    def tree(self, x, y):
        assert x % 2 == 0 and y % 2 == 0, ('tree off the lattice', x, y)
        self.box(x, y, x + 1, y + 1, 'T')

    def border(self, t=2):
        self.box(0, 0, self.W - 1, t - 1, 'T'); self.box(0, self.H - t, self.W - 1, self.H - 1, 'T')
        self.box(0, 0, t - 1, self.H - 1, 'T'); self.box(self.W - t, 0, self.W - 1, self.H - 1, 'T')

    def road(self, pts, w=2, ch='P'):
        for (ax, ay), (bx, by) in zip(pts, pts[1:]):
            if ay == by:
                self.box(min(ax, bx), ay, max(ax, bx) + w - 1, ay + w - 1, ch)
            else:
                self.box(ax, min(ay, by), ax + w - 1, max(ay, by), ch)

    def rows(self):
        return [''.join(r) for r in self.g]

    def show(self, stamps=()):
        g = [r[:] for r in self.g]
        for name, x, y, *_ in stamps:
            st = get_stamp(name)
            for dy, row in enumerate(st['cells']):
                for dx, v in enumerate(row):
                    if v is not None and 0 <= y + dy < self.H and 0 <= x + dx < self.W:
                        g[y + dy][x + dx] = '#'
            for dx, dy in st['doors']:
                g[y + dy][x + dx] = 'D'
        tens = ''.join(str(i // 10) if i % 10 == 0 else ' ' for i in range(self.W))
        print('    ' + tens); print('    ' + ''.join(str(i % 10) for i in range(self.W)))
        for i, r in enumerate(g):
            print(f'{i:3} ' + ''.join(r))


def render_png(cells, W, secondary, path, events=()):
    sys.path.insert(0, os.path.join(rk.ROOT, 'tools_pounamu'))
    from render_tiles import TilesetPair
    from PIL import ImageDraw
    img = TilesetPair('gTileset_General', secondary).render_map(cells, W, scale=1)
    d = ImageDraw.Draw(img)
    for (x, y, colour) in events:
        d.rectangle([x * 16 + 3, y * 16 + 3, x * 16 + 12, y * 16 + 12], outline=colour, width=1)
    img.save(path)


def build(spec):
    write = '--write' in sys.argv
    name, tileset = spec['folder'], spec['tileset']
    use_secondary(tileset)
    r = rk.from_ascii(name, spec['rows'], '')
    r.pond_open_top = set(spec.get('pond_open_top', ()))
    r.fixed_class = spec.get('fixed_class', 'X')
    errors = 0
    print(f'{name}: {r.W}x{r.H} drawn with {tileset}')
    if r.snap_warnings:
        errors += fail('trees off the 2x2 lattice', r.snap_warnings)

    # ---- stamps
    warps, fronts = {}, {}
    for name_s, x, y, warp in spec['stamps']:
        st = get_stamp(name_s)
        if not st['general'] and st['secondary'] != tileset:
            errors += fail('stamp from another tileset', [(name_s, st['secondary'])])
        for dy, row in enumerate(st['cells']):
            for dx, v in enumerate(row):
                if v is None:
                    continue
                if not r.inb(x + dx, y + dy):
                    errors += fail('stamp off the map', [(name_s, x + dx, y + dy)])
                    continue
                r.cls[y + dy][x + dx] = '#'
                r.fix[(x + dx, y + dy)] = v
        ws = warp if isinstance(warp, (list, tuple)) else ([] if warp is None else [warp])
        for i, (dx, dy) in enumerate(st['doors']):
            if i < len(ws):
                warps[ws[i]] = (x + dx, y + dy)
                fronts[ws[i]] = (x + dx, y + dy + 1)
    for i, xy in spec.get('warps', {}).items():
        warps[i] = tuple(xy)
    # signs are fixed sign posts
    for sx, sy, _ in spec.get('signs', []):
        r.cls[sy][sx] = '#'; r.fix[(sx, sy)] = rk.val(rk.SIGN)
    # jetties: plank walks out over the sea (Dewford's dock, stretched). The sea is drawn
    # as if the jetty weren't there (open water all round it), then the planks go on top.
    jet = {}
    if spec.get('jetties'):
        dock = get_stamp('dew.dock')['cells']
        for jx, jy, n in spec['jetties']:
            for i in range(n):
                jet[(jx + i, jy)] = dock[0][0 if i == 0 else 1]
                jet[(jx + i, jy + 1)] = dock[1][0 if i == 0 else 1]
        for (x, y) in jet:
            r.cls[y][x] = 'S'

    shapes = rk.lint_shapes(r)
    if shapes:
        errors += fail('shapes the tiles cannot draw', shapes)
    r.render(seed=spec.get('seed', 1))
    for (x, y), v in jet.items():
        r.cells[y * r.W + x] = v
    bad = rk.check_trees(r)
    if bad:
        errors += fail('broken trees', bad)

    # ---- connections and seams
    mj = rk.map_json(name)
    exits = {}
    for cn in mj['connections']:
        off = spec['conns'].get(cn['map'], cn['offset'])
        probs = rk.check_seam(r, cn['direction'], rk.folder_of(cn['map']), off)
        if probs:
            errors += fail(f'seam with {cn["map"]} (offset {off})', probs)
        d = cn['direction']
        cells = {'up': [(x, 0) for x in range(r.W)], 'down': [(x, r.H - 1) for x in range(r.W)],
                 'left': [(0, y) for y in range(r.H)], 'right': [(r.W - 1, y) for y in range(r.H)]}[d]
        cells = [c for c in cells if r.walkable(*c)]
        if not cells:
            errors += fail(f'no open edge toward {cn["map"]}', [d])
        exits[cn['map']] = cells

    # ---- warps
    if len(warps) != len(mj['warp_events']) or set(warps) != set(range(len(mj['warp_events']))):
        errors += fail('warps not all placed', [f'have {sorted(warps)}, need 0..{len(mj["warp_events"]) - 1}'])

    # ---- objects
    objs = mj['object_events']
    names = object_names(objs)
    placed = {}
    for suffix in names:
        if suffix not in spec['objects']:
            errors += fail('object not placed', [suffix])
            continue
        x, y, face = spec['objects'][suffix]
        placed[suffix] = ((x, y), face)
        if not r.walkable(x, y):
            errors += fail('object on a blocked tile', [(suffix, x, y)])
        if (x, y) in fronts.values() or (x, y) in warps.values():
            errors += fail('object in a doorway', [(suffix, x, y)])
    for suffix in spec['objects']:
        if suffix not in names:
            errors += fail('placed an object the map does not have', [suffix])
    standing = {xy for xy, f in placed.values()}

    # ---- reachability: every exit and every door, with everyone standing still
    allexits = [c for cs in exits.values() for c in cs]
    main = r.reach(allexits, standing)
    for a, acells in exits.items():
        seen = r.reach(acells, standing)
        for b, bcells in exits.items():
            if b != a and not any(c in seen for c in bcells):
                errors += fail('town cannot be crossed', [f'{a} -> {b}'])
    for i, (x, y) in sorted(warps.items()):
        if i in fronts:
            fx, fy = fronts[i]
            if (fx, fy) not in main:
                errors += fail('door cannot be reached', [(i, mj['warp_events'][i]['dest_map'], fx, fy)])
        elif not any((x + dx, y + dy) in main for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))) and (x, y) not in main:
            errors += fail('warp cannot be reached', [(i, x, y)])
    for suffix, ((x, y), face) in placed.items():
        near = any((x + dx, y + dy) in main for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)))
        if not near and suffix not in spec.get('allow_unreached', ()):
            errors += fail('object cannot be reached', [(suffix, x, y)])
    for sx, sy, _ in spec.get('signs', []):
        if (sx, sy + 1) not in main:
            errors += fail('sign cannot be read from below', [(sx, sy)])
    hid = [b for b in mj['bg_events'] if b.get('type') == 'hidden_item']
    for idx, (x, y) in spec.get('hidden', {}).items():
        if (x, y) not in main:
            errors += fail('hidden item unreachable', [(idx, x, y)])
    if len(spec.get('hidden', {})) != len(hid):
        errors += fail('hidden items not all placed', [f'{len(spec.get("hidden", {}))} of {len(hid)}'])
    pc = warps.get(spec.get('pc_warp', 0))
    heal = (pc[0], pc[1] + 1) if pc else None
    if heal and heal not in main:
        errors += fail('heal spot unreachable', [heal])

    # ---- what the player sees past the edges
    border = [rk.val(m) for m in (rk.TREE_TL, rk.TREE_TR, rk.TREE_BL, rk.TREE_BR)]
    conns = [(cn['direction'], rk.folder_of(cn['map']), spec['conns'].get(cn['map'], cn['offset']))
             for cn in mj['connections']]
    water = lambda v: rk.BEH.get(v & 0x3FF, 0) in rk.WATER_BEH
    probs, grid, src = cv.edge_problems(r.W, r.H, r.cells, border, conns, tileset,
                                        lambda x, y: (x, y) in main, water=water)
    probs = [p for side, p in probs]
    if probs:
        errors += fail('flaws the player can see past the edges', probs)

    # ---- preview
    os.makedirs(OUT, exist_ok=True)
    ev = [(x, y, 'red') for (x, y), f in placed.values()] + \
         [(x, y, 'yellow') for x, y in spec.get('hidden', {}).values()] + \
         [(x, y, 'cyan') for x, y in warps.values()]
    render_png(r.cells, r.W, tileset, os.path.join(OUT, f'{name}.png'), ev)
    cv.render_grid(grid, 'gTileset_General', tileset, (8, 6, r.W, r.H)).save(os.path.join(OUT, f'{name}_context.png'))
    print(f'  preview: out/{name}.png (+ _context.png)')
    if errors:
        print(f'  {errors} gate(s) failed - not writing')
        return r, False
    print('  all gates passed')
    if not write:
        return r, True

    # ---- write
    rk.write_layout(r, spec['layout'], secondary=tileset)
    mj = rk.map_json(name)
    for i, w in enumerate(mj['warp_events']):
        w['x'], w['y'] = warps[i]
    for o, suffix in zip(mj['object_events'], object_names(mj['object_events'])):
        (x, y), face = placed[suffix]
        o['x'], o['y'] = x, y
        if face:
            o['movement_type'] = f'MOVEMENT_TYPE_FACE_{face}'
    hid = [b for b in mj['bg_events'] if b.get('type') == 'hidden_item']
    for idx, (x, y) in spec.get('hidden', {}).items():
        hid[idx]['x'], hid[idx]['y'] = x, y
    others = [b for b in mj['bg_events'] if b.get('type') not in ('hidden_item', 'sign')]
    signs, new_text = [], []
    for sx, sy, label in spec.get('signs', []):
        if isinstance(label, tuple):
            new_text.append(label)
            label = label[0]
        signs.append({'type': 'sign', 'x': sx, 'y': sy, 'elevation': 0,
                      'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY', 'script': f'{name}_EventScript_{label}'})
    mj['bg_events'] = others + hid + signs
    for cn in mj['connections']:
        if cn['map'] in spec['conns']:
            cn['offset'] = spec['conns'][cn['map']]
    rk.save_map_json(name, mj)
    for tgt, off in spec['conns'].items():
        rf = rk.folder_of(tgt)
        rj = rk.map_json(rf)
        for cn in rj['connections']:
            if cn['map'] == mj['id']:
                cn['offset'] = -off
        rk.save_map_json(rf, rj)
    sp = os.path.join(rk.ROOT, 'data/maps', name, 'scripts.inc')
    s = open(sp).read()
    for label, lines in new_text:
        lab = f'{name}_EventScript_{label}::'
        if lab in s:
            continue
        body = '\n'.join(f'\t.string "{t}"' for t in lines)
        s += (f'\n{lab}\n\tmsgbox {name}_Text_{label}, MSGBOX_SIGN\n\tend\n\n'
              f'{name}_Text_{label}:\n{body}\n')
    open(sp, 'w').write(s)
    for label in [l for x, y, l in spec.get('signs', []) if not isinstance(l, tuple)]:
        if f'{name}_EventScript_{label}::' not in s:
            print(f'  WARNING: sign script {name}_EventScript_{label} not found')
    if heal:
        hp = os.path.join(rk.ROOT, 'src/data/heal_locations.json')
        hj = json.load(open(hp))
        for h in hj['heal_locations']:
            if h['map'] == mj['id']:
                h['x'], h['y'] = heal
        open(hp, 'w').write(json.dumps(hj, indent=2) + '\n')
    for path, old, new in spec.get('script_edits', []):
        fp = os.path.join(rk.ROOT, path)
        t = open(fp).read()
        if old in t:
            open(fp, 'w').write(t.replace(old, new))
        elif new not in t:
            print(f'  WARNING: could not apply script edit in {path}: {old!r}')
    print('  written')
    return r, True
