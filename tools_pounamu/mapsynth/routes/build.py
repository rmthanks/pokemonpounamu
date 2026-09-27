#!/usr/bin/env python3
"""Build a hand-drawn Pounamu route: check it against the gold-standard gates, preview, write.

Each tools_pounamu/mapsynth/routes/<name>.py defines SPEC and calls build(SPEC).
  python3 tools_pounamu/mapsynth/routes/<name>.py            # check + preview only
  python3 tools_pounamu/mapsynth/routes/<name>.py --write    # also write map + events

SPEC keys:
  folder, layout, weather     the map folder, its layout id, and its weather
  rows                        the hand-drawn map (see routekit.from_ascii)
  objects                     marker -> (script suffix, facing or None) for every object on the map
  hidden                      marker -> hidden item index (order in the old bg_events)
  signs                       marker 's' spots become signs; SPEC['sign_text'] = [(label, text lines)]
  conns                       neighbour map id -> offset (ours; the neighbour gets the negative)
  allow_unreached             markers allowed to be HM-gated or otherwise off the main line
"""
import json, os, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE)); sys.path.insert(0, os.path.dirname(os.path.dirname(HERE)))
import routekit as rk

OUT = os.path.join(os.path.dirname(HERE), 'out')
FACES = {'UP', 'DOWN', 'LEFT', 'RIGHT'}


def fail(msg, problems):
    print(f'  FAIL {msg}:')
    for p in problems[:25]:
        print('     ', p)
    return 1


def build(spec):
    write = '--write' in sys.argv
    name = spec['folder']
    markers = ''.join(spec.get('objects', {}).keys()) + ''.join(spec.get('hidden', {}).keys())
    if spec.get('seal'):
        markers += spec['seal']['beyond']
    r = rk.from_ascii(name, spec['rows'], markers)
    errors = 0
    print(f'{name}: {r.W}x{r.H}')
    if r.snap_warnings:
        errors += fail('trees off the 2x2 lattice (block x,y,count)', r.snap_warnings)
    shapes = rk.lint_shapes(r)
    if shapes:
        errors += fail('shapes the tiles cannot draw', shapes)
    r.render(seed=spec.get('seed', 1))
    bad = rk.check_trees(r)
    if bad:
        errors += fail('broken trees', bad)

    # ---- connections and seams
    mj = rk.map_json(name)
    exits = {}
    deferred = set(spec.get('defer_seams', ()))
    for cn in mj['connections']:
        off = spec['conns'].get(cn['map'], cn['offset'])
        probs = rk.check_seam(r, cn['direction'], rk.folder_of(cn['map']), off)
        if cn['map'] in deferred:
            print(f'  (seam with {cn["map"]} is checked when that map is rebuilt: {len(probs)} open now)')
        elif probs:
            errors += fail(f'seam with {cn["map"]} (offset {off})', probs)
        d = cn['direction']
        if d == 'up':
            cells = [(x, 0) for x in range(r.W) if r.walkable(x, 0)]
        elif d == 'down':
            cells = [(x, r.H - 1) for x in range(r.W) if r.walkable(x, r.H - 1)]
        elif d == 'left':
            cells = [(0, y) for y in range(r.H) if r.walkable(0, y)]
        else:
            cells = [(r.W - 1, y) for y in range(r.H) if r.walkable(r.W - 1, y)]
        if not cells:
            errors += fail(f'no open edge toward {cn["map"]}', [d])
        exits[cn['map']] = cells

    # ---- objects
    objs = mj['object_events']
    placed = {}
    for mk, (suffix, face) in spec.get('objects', {}).items():
        spots = r.marks.get(mk, [])
        if len(spots) != 1:
            errors += fail(f'marker {mk!r} for {suffix}', [f'found {len(spots)} spots'])
            continue
        placed[suffix] = (spots[0], face)
    blocked = set()
    for o in objs:
        suffix = o['script'].split('_EventScript_')[-1]
        if suffix not in placed:
            errors += fail('object not placed', [suffix])
            continue
        (x, y), face = placed[suffix]
        if not r.walkable(x, y):
            errors += fail('object on a blocked tile', [(suffix, x, y)])
        blocked.add((x, y))

    # ---- reachability: every exit reaches every other, both ways, with objects standing still
    allexits = [c for cs in exits.values() for c in cs]
    split = {placed[s][0] for s in spec.get('split_by', ()) if s in placed}
    if split:
        # story blockers (a checkpoint) must really seal the road...
        seen = r.reach(list(exits.values())[0], blocked)
        if any(c in seen for c in list(exits.values())[1]):
            errors += fail('the checkpoint does not seal the road', sorted(split))
        blocked = blocked - split     # ...and the road must be whole without them
    for a, acells in exits.items():
        seen = r.reach(acells, blocked)
        for b, bcells in exits.items():
            if b != a and not any(c in seen for c in bcells):
                errors += fail('route cannot be walked', [f'{a} -> {b}'])
        # softlock: from anywhere you can get to, you can still get out
        for cell in list(seen)[::7]:
            back = r.reach([cell], blocked)
            if not any(c in back for c in allexits):
                errors += fail('one-way trap (ledges?)', [cell])
                break
    if spec.get('seal'):
        # story blockers on a dead end: what lies beyond them is out of reach while they stand,
        # and the road really does carry on past them
        seal = spec['seal']
        beyond = r.marks.get(seal['beyond'], [])
        stand = blocked | {placed[s][0] for s in seal['by'] if s in placed}
        if any(c in r.reach(allexits, stand) for c in beyond):
            errors += fail('the blockers do not seal the road', [seal['by']])
        free = blocked - {placed[s][0] for s in seal['by'] if s in placed}
        if not all(c in r.reach(allexits, free) for c in beyond):
            errors += fail('the road does not carry on past the blockers', [seal['by']])
    main = r.reach(allexits, blocked)
    for suffix, ((x, y), face) in placed.items():
        near = any((x + dx, y + dy) in main for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)))
        if not near and suffix not in spec.get('allow_unreached', ()):
            errors += fail('object cannot be reached', [(suffix, x, y)])
    # trainers must see onto ground the player walks
    for o in objs:
        suffix = o['script'].split('_EventScript_')[-1]
        if suffix not in placed or o.get('trainer_type', 'TRAINER_TYPE_NONE') == 'TRAINER_TYPE_NONE':
            continue
        (x, y), face = placed[suffix]
        f = face or o['movement_type'].replace('MOVEMENT_TYPE_FACE_', '')
        if f not in FACES:
            continue
        sight = rk.sight_cells(r, x, y, f, int(o.get('trainer_sight_or_berry_tree_id', 2) or 2))
        if not any(c in main for c in sight):
            errors += fail('trainer looks at nothing', [(suffix, x, y, f)])
    hidden_spots = {}
    for mk, idx in spec.get('hidden', {}).items():
        spots = r.marks.get(mk, [])
        if len(spots) == 1:
            hidden_spots[idx] = spots[0]
            if spots[0] not in main and mk not in spec.get('allow_unreached', ()):
                errors += fail('hidden item unreachable', [mk])
    odd = rk.check_pairs(r)
    print(f'  tile pairs not seen in vanilla: {len(odd)} (review the render)')

    # ---- what the player sees past the edges (neighbours drawn with our tileset, and the border)
    import context_view as cv
    lay = rk.LAYOUTS[spec['layout']]
    secondary = spec.get('tileset') or lay['secondary_tileset']
    border = [rk.val(m) for m in spec.get('border', (rk.TREE_TL, rk.TREE_TR, rk.TREE_BL, rk.TREE_BR))]
    conns = [(cn['direction'], rk.folder_of(cn['map']), spec['conns'].get(cn['map'], cn['offset']))
             for cn in mj['connections']]
    water = lambda v: rk.BEH.get(v & 0x3FF, 0) in rk.WATER_BEH
    standing = {placed[s][0] for s in placed}
    reachable = r.reach(allexits, standing)  # where the player can actually stand, everyone in place
    probs, grid, src = cv.edge_problems(r.W, r.H, r.cells, border, conns, secondary,
                                        lambda x, y: (x, y) in reachable, water=water)
    skip_sides = {cn['direction'] for cn in mj['connections'] if cn['map'] in deferred}
    probs = [p for side, p in probs if side not in skip_sides]
    if probs:
        errors += fail('flaws the player can see past the edges', probs)

    # ---- preview
    os.makedirs(OUT, exist_ok=True)
    ev = [(x, y, 'red') for (x, y), f in placed.values()] + [(x, y, 'yellow') for x, y in hidden_spots.values()]
    rk.preview(r, os.path.join(OUT, f'{name}.png'), scale=1, events=ev)
    cv.render_grid(grid, 'gTileset_General', secondary, (8, 6, r.W, r.H)).save(os.path.join(OUT, f'{name}_context.png'))
    print(f'  preview: {os.path.join(OUT, name + ".png")} (+ _context.png: as the game draws the edges)')
    if errors:
        print(f'  {errors} gate(s) failed - not writing')
        return r, False
    print('  all gates passed')
    if not write:
        return r, True

    # ---- write
    rk.write_layout(r, spec['layout'], border=spec.get('border', (rk.TREE_TL, rk.TREE_TR, rk.TREE_BL, rk.TREE_BR)),
                    secondary=spec.get('tileset'))
    for path, old, new in spec.get('script_edits', []):
        fp = os.path.join(rk.ROOT, path)
        t = open(fp).read()
        if old in t:
            open(fp, 'w').write(t.replace(old, new))
        elif new not in t:
            print(f'  WARNING: could not apply script edit in {path}: {old!r}')
    mj = rk.map_json(name)
    for o in mj['object_events']:
        suffix = o['script'].split('_EventScript_')[-1]
        (x, y), face = placed[suffix]
        o['x'], o['y'] = x, y
        if face:
            o['movement_type'] = f'MOVEMENT_TYPE_FACE_{face}'
    hid = [b for b in mj['bg_events'] if b.get('type') == 'hidden_item']
    for idx, (x, y) in hidden_spots.items():
        hid[idx]['x'], hid[idx]['y'] = x, y
    others = [b for b in mj['bg_events'] if b.get('type') not in ('hidden_item', 'sign')]
    signs = []
    for i, (x, y) in enumerate(r.marks.get('s', [])):
        label = spec['sign_text'][i][0]
        signs.append({'type': 'sign', 'x': x, 'y': y, 'elevation': 0,
                      'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY', 'script': f'{name}_EventScript_{label}'})
    mj['bg_events'] = others + hid + signs
    mj['weather'] = spec.get('weather', mj['weather'])
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
    # sign scripts
    sp = os.path.join(rk.ROOT, 'data/maps', name, 'scripts.inc')
    s = open(sp).read()
    for label, lines in spec.get('sign_text', []):
        lab = f'{name}_EventScript_{label}::'
        if lab in s:
            continue
        body = '\n'.join(f'\t.string "{t}"' for t in lines)
        s += (f'\n{lab}\n\tmsgbox {name}_Text_{label}, MSGBOX_SIGN\n\tend\n\n'
              f'{name}_Text_{label}:\n{body}\n')
    open(sp, 'w').write(s)
    print('  written')
    return r, True
