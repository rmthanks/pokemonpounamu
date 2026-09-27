#!/usr/bin/env python3
"""Tamaki Makaurau: close the edges Lilycove left open (Sept 2026).

Tamaki is Lilycove's layout, but Lilycove ran on west into Route 121 and north off the
top of its map; Tamaki has no neighbours, so the player walked into the sea border past
the museum, the department store and two dead-end openings in the west. This gives Tamaki
its own copy of the layout, six rows taller and eight columns wider (deep enough that
the sea border never comes into view past the new forest) (the new strips on the
north and west), and fills them the way the map's own edge continues: forest behind the
land, open water beyond the water, the rock shoal carried straight up. Every event moves
with the map (+8, +6), and the ferry from Wellington lands where it did.
  python3 tools_pounamu/mapsynth/fix_tamaki_edges.py"""
import json, os, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.dirname(HERE))
import routekit as rk
from synth import ROOT, LAYOUTS

DX, DY = 8, 6          # deep enough that the border never comes into view
NEW_ID, NEW_NAME = 'LAYOUT_TAMAKI_MAKAURAU', 'TamakiMakaurau_Layout'
SEA, COL = 0x170, 0x400
TL, TR, BL, BR, BLO, BRO = 0x1D4, 0x1D5, 0x1DC, 0x1DD, 0x1E4, 0x1E5
TOPS = {0x1D4: 'L', 0x1D6: 'L', 0x1D5: 'R', 0x1D7: 'R'}
BOTS = {0x1DC: 'L', 0x1E4: 'L', 0x1E6: 'L', 0x1DD: 'R', 0x1E5: 'R', 0x1E7: 'R'}


def v(m, solid=False):
    x = rk.val(m)
    return x | COL if solid else x


def main():
    mj = json.load(open(os.path.join(ROOT, 'data/maps/TamakiMakaurau/map.json')))
    if mj['layout'] == NEW_ID:
        print('Tamaki already has its own layout; nothing to do')
        return
    src = LAYOUTS[mj['layout']]
    W, H = src['width'], src['height']
    raw = open(os.path.join(ROOT, src['blockdata_filepath']), 'rb').read()
    old = list(struct.unpack(f'<{W * H}H', raw))
    NW, NH = W + DX, H + DY
    new = [0] * (NW * NH)
    for y in range(H):
        for x in range(W):
            new[(y + DY) * NW + x + DX] = old[y * W + x]
    at = lambda x, y: old[y * W + x] & 0x3FF
    water = lambda t: rk.BEH.get(t, 0) in rk.WATER_BEH
    put = lambda x, y, val: new.__setitem__(y * NW + x, val)

    # ---- the north strip (new rows 0-1) over each old column
    x = 0
    while x < W:
        t = at(x, 0)
        if water(t) or t in (0x1AD, 0x19B, 0x19E, 0x1B7, 0x17C) or (0x060 <= t < 0x0A0):
            # open water, the shoal's edges and the rock: carried straight up; nobody walks the
            # carried-up shoal or rock tops (they would lead to the edge)
            walk = not (old[x] >> 10) & 3 and not water(t)
            for yy in range(DY):
                put(x + DX, yy, old[x] | (COL if walk else 0))
            x += 1
            continue
        # land: a stack of whole trees over this cell and its partner
        pair = 2 if x + 1 < W and not water(at(x + 1, 0)) else 1
        for i in range(pair):
            below = at(x + i, 0)
            for yy in range(DY):
                if yy % 2 == 0:
                    put(x + DX + i, yy, v((TL, TR)[i]))
                elif yy < DY - 1:
                    put(x + DX + i, yy, v((BL, BR)[i]))
                else:
                    put(x + DX + i, yy, v(((BL, BR) if below in TOPS else (BLO, BRO))[i]))
        x += pair

    # ---- the west strip (new columns 0-3) beside each old row
    y = 0
    while y < H:
        t = at(0, y)
        if water(t):
            above_land = y > 0 and not water(at(0, y - 1))
            for xx in range(DX):
                put(xx, y + DY, v(0x189) if above_land else v(SEA))
            y += 1
            continue
        if t in BOTS:                      # the bottom half of a tree that started above
            for xx in range(DX):
                put(xx, y + DY, v((BL, BR)[xx % 2]))
            y += 1
            continue
        if 0x060 <= t < 0x0A0 and y + 1 < H and water(at(0, y + 1)):
            for xx in range(DX):          # the rock ledge over the water runs on west
                put(xx, y + DY, old[y * W])
            y += 1
            continue
        # a new tree here and in the row below, if that row is land too
        if y + 1 < H and not water(at(0, y + 1)) and at(0, y + 1) not in TOPS:
            below2 = at(0, y + 2) if y + 2 < H else None
            for xx in range(DX):
                put(xx, y + DY, v((TL, TR)[xx % 2]))
                put(xx, y + 1 + DY, v(((BL, BR) if below2 in TOPS else (BLO, BRO))[xx % 2]))
            y += 2
        else:
            # a single row: grass under the canopy of the tree below, nobody walks it
            for xx in range(DX):
                put(xx, y + DY, v((rk.CANOPY_L, rk.CANOPY_R)[xx % 2], solid=True))
            y += 1
    # ---- the corner
    for yy in range(DY):
        for xx in range(DX):
            put(xx, yy, v(((TL, TR), (BL, BR))[yy % 2][xx % 2]))
    first = new[DY * NW]                       # what the west strip starts with, under the corner
    if (first & 0x3FF) not in TOPS:
        for xx in range(DX):
            put(xx, DY - 1, v((BLO, BRO)[xx % 2]))

    # ---- the doors. The Sky Tower's lobby warp sat on open grass at the top of the steps (no
    # way in, and it is the climax of Act 3); the tallest building in the city, the old
    # department store, becomes the tower. The villa "this close to the tower" gets its own
    # house in the new bush above the museum, a few steps from it.
    sys.path.insert(0, os.path.join(HERE, 'towns'))
    from library import stamp as get_stamp
    hx, hy = 8, 19
    hs = get_stamp('lily.house')
    for dy, row in enumerate(hs['cells']):
        for dx, val in enumerate(row):
            if val is not None:
                put(hx + dx, hy + dy, val)
    for dx in range(hs['w']):                  # its yard: the canopy row in front, walkable
        put(hx + dx, hy + hs['h'], v((rk.CANOPY_L, rk.CANOPY_R)[(hx + dx) % 2]))
    # tree bottoms in the new strips: closed over another tree, open over anything else
    strip = [(x, y) for y in range(NH) for x in range(NW) if x < DX or y < DY]
    for (x, y) in strip:
        t = new[y * NW + x] & 0x3FF
        if t in BOTS:
            below = new[(y + 1) * NW + x] & 0x3FF if y + 1 < NH else 0x1D4
            side = BOTS[t]
            if below in TOPS:
                put(x, y, v(BL if side == 'L' else BR))
            else:
                put(x, y, v(BLO if side == 'L' else BRO))
    villa_door = (hx + hs['doors'][0][0], hy + hs['doors'][0][1])
    for w in mj['warp_events']:
        if w['dest_map'] == 'MAP_SKY_TOWER_LOBBY':
            sky = w
        if w['dest_map'] == 'MAP_TAMAKI_VILLA_HOUSE':
            villa = w
    store_door = (villa['x'] + DX, villa['y'] + DY)

    # ---- write the new layout
    folder = os.path.join(ROOT, 'data/layouts/TamakiMakaurau')
    os.makedirs(folder, exist_ok=True)
    open(os.path.join(folder, 'map.bin'), 'wb').write(struct.pack(f'<{NW * NH}H', *new))
    braw = open(os.path.join(ROOT, src['border_filepath']), 'rb').read()
    open(os.path.join(folder, 'border.bin'), 'wb').write(braw)
    lp = os.path.join(ROOT, 'data/layouts/layouts.json')
    lj = json.load(open(lp))
    if not any(l.get('id') == NEW_ID for l in lj['layouts']):
        entry = dict(src)
        entry.update(id=NEW_ID, name=NEW_NAME, width=NW, height=NH,
                     border_filepath='data/layouts/TamakiMakaurau/border.bin',
                     blockdata_filepath='data/layouts/TamakiMakaurau/map.bin')
        i = next(i for i, l in enumerate(lj['layouts']) if l.get('id') == mj['layout'])
        txt = open(lp).read()
        # insert textually after the Lilycove entry so the file's formatting stays as it is
        anchor = txt.index(f'"id": "{mj["layout"]}"')
        start = txt.rindex('{', 0, anchor)
        end = txt.index('}', anchor) + 1
        block = txt[start:end]
        nb = block.replace(f'"id": "{mj["layout"]}"', f'"id": "{NEW_ID}"')
        nb = nb.replace(f'"name": "{src["name"]}"', f'"name": "{NEW_NAME}"')
        nb = nb.replace(f'"width": {W}', f'"width": {NW}').replace(f'"height": {H}', f'"height": {NH}')
        nb = nb.replace(src['border_filepath'], 'data/layouts/TamakiMakaurau/border.bin')
        nb = nb.replace(src['blockdata_filepath'], 'data/layouts/TamakiMakaurau/map.bin')
        txt = txt[:end] + ',\n    ' + nb + txt[end:]
        open(lp, 'w').write(txt)

    # ---- move every event with the map
    mj['layout'] = NEW_ID
    for key in ('warp_events', 'object_events', 'coord_events', 'bg_events'):
        for e in mj.get(key) or []:
            e['x'] += DX; e['y'] += DY
    sky['x'], sky['y'] = store_door
    villa['x'], villa['y'] = villa_door
    open(os.path.join(ROOT, 'data/maps/TamakiMakaurau/map.json'), 'w').write(
        json.dumps(mj, indent=2, ensure_ascii=False) + '\n')
    # the ferry from Wellington lands where it did
    sp = os.path.join(ROOT, 'data/maps/Wellington/scripts.inc')
    s = open(sp).read()
    s = s.replace('warp MAP_TAMAKI_MAKAURAU, 53, 33', f'warp MAP_TAMAKI_MAKAURAU, {53 + DX}, {33 + DY}')
    open(sp, 'w').write(s)
    print(f'Tamaki Makaurau: {W}x{H} -> {NW}x{NH} on its own layout')


if __name__ == '__main__':
    main()
