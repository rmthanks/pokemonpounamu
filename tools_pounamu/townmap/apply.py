#!/usr/bin/env python3
"""Put the town map's layout (layout.py) into the game data.

  - region_map_sections.json: where each section sits (the fly points, the fallback for
    the player's head) and the names that changed: Tamaki gets a town section of its own
    (MAPSEC_OLDALE_TOWN, so it can be flown to), Piopiotahi gets one (MAPSEC_ROUTE_130)
  - region_map_layout.h: which section the cursor names in every cell
  - src/data/region_map/pounamu_map_cells.h: for every Pounamu outdoor map, the cells it
    covers, in the order the map runs, so the player's head moves along a long road
  - map.json region sections: Tamaki and the Sky Tower -> Tamaki's section, Piopiotahi ->
    its own, the League rooms -> Otepoti (they showed "Waitohi")
  - heal_locations.json: HEAL_LOCATION_HERETAUNGA_TOWN, outside the homestead (Fly lands there)
  - every town's scripts: setflag FLAG_VISITED_<section> on arrival

  python3 tools_pounamu/townmap/apply.py"""
import glob, json, os, re, sys
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
from layout import TOWNS, PLACES, ROADS, SEA_LANES

SECTIONS = os.path.join(ROOT, 'src/data/region_map/region_map_sections.json')
LAYOUT_H = os.path.join(ROOT, 'src/data/region_map/region_map_layout.h')
CELLS_H = os.path.join(ROOT, 'src/data/region_map/pounamu_map_cells.h')
HEAL = os.path.join(ROOT, 'src/data/heal_locations.json')
NAMES = {'MAPSEC_OLDALE_TOWN': 'Tamaki Makaurau', 'MAPSEC_ROUTE_121': 'Route 121',
         'MAPSEC_ROUTE_130': 'Piopiotahi'}
VISITED = {  # a town's section -> the flag its arrival sets (the section's own vanilla flag)
    'MAPSEC_LITTLEROOT_TOWN': 'FLAG_VISITED_LITTLEROOT_TOWN', 'MAPSEC_OLDALE_TOWN': 'FLAG_VISITED_OLDALE_TOWN',
    'MAPSEC_DEWFORD_TOWN': 'FLAG_VISITED_DEWFORD_TOWN', 'MAPSEC_LAVARIDGE_TOWN': 'FLAG_VISITED_LAVARIDGE_TOWN',
    'MAPSEC_FALLARBOR_TOWN': 'FLAG_VISITED_FALLARBOR_TOWN', 'MAPSEC_VERDANTURF_TOWN': 'FLAG_VISITED_VERDANTURF_TOWN',
    'MAPSEC_PACIFIDLOG_TOWN': 'FLAG_VISITED_PACIFIDLOG_TOWN', 'MAPSEC_PETALBURG_CITY': 'FLAG_VISITED_PETALBURG_CITY',
    'MAPSEC_SLATEPORT_CITY': 'FLAG_VISITED_SLATEPORT_CITY', 'MAPSEC_MAUVILLE_CITY': 'FLAG_VISITED_MAUVILLE_CITY',
    'MAPSEC_RUSTBORO_CITY': 'FLAG_VISITED_RUSTBORO_CITY', 'MAPSEC_FORTREE_CITY': 'FLAG_VISITED_FORTREE_CITY',
    'MAPSEC_LILYCOVE_CITY': 'FLAG_VISITED_LILYCOVE_CITY', 'MAPSEC_MOSSDEEP_CITY': 'FLAG_VISITED_MOSSDEEP_CITY',
    'MAPSEC_SOOTOPOLIS_CITY': 'FLAG_VISITED_SOOTOPOLIS_CITY', 'MAPSEC_EVER_GRANDE_CITY': 'FLAG_VISITED_EVER_GRANDE_CITY',
}
# maps that are not a town or a road but sit on the map (the player's head goes to this cell)
EXTRA_CELLS = {'TeMataTrack': PLACES['TE_MATA']['cell'], 'TeMataSummit': PLACES['TE_MATA']['cell'],
               'RuapehuAscent': PLACES['RUAPEHU']['cell'], 'RuapehuSummit': PLACES['RUAPEHU']['cell'],
               'Piopiotahi': PLACES['PIOPIOTAHI']['cell'], 'TaupoLakeIsle': (19, 6)}
TOWN_FOLDERS = {'TAMAKI': 'TamakiMakaurau', 'TAURANGA': 'Tauranga', 'OPOTIKI': 'Opotiki', 'TURANGA': 'Turanga',
                'WAIROA': 'Wairoa', 'AHURIRI': 'AhuririCity', 'HERETAUNGA': 'HeretaungaTown', 'ROTORUA': 'Rotorua',
                'TAUPO': 'Taupo', 'NGAMOTU': 'Ngamotu', 'WHANGANUI': 'Whanganui', 'WELLINGTON': 'Wellington',
                'WAITOHI': 'Waitohi', 'WHAKATU': 'Whakatu', 'OTAUTAHI': 'Otautahi', 'OTEPOTI': 'Otepoti'}
ROAD_FOLDERS = {'ORCHARD_ROAD': 'OrchardRoad', 'ROUTE2_BAY': 'Route2Bay', 'ROUTE2_NORTH': 'Route2North',
                'ROUTE2_EAST': 'Route2East', 'ROUTE35_A': 'Route35A', 'ROUTE35_B': 'Route35B',
                'ROUTE2_BOP': 'Route2BoP', 'ROUTE36': 'Route36', 'ROUTE5': 'Route5', 'ROUTE5_RANGES': 'Route5Ranges',
                'ROUTE1_DESERT': 'Route1Desert', 'ROUTE43': 'Route43', 'ROUTE3': 'Route3',
                'ROUTE1_KAPITI': 'Route1Kapiti', 'ROUTE6': 'Route6', 'ROUTE7': 'Route7', 'ROUTE1_SOUTH': 'Route1South'}


def mj(folder):
    return json.load(open(os.path.join(ROOT, 'data/maps', folder, 'map.json')))


def save_mj(folder, j):
    open(os.path.join(ROOT, 'data/maps', folder, 'map.json'), 'w').write(json.dumps(j, indent=2, ensure_ascii=False) + '\n')


def all_cells():
    """cell -> section, for the cursor"""
    grid = {}
    for t in TOWNS.values():
        grid[t['cell']] = t['mapsec']
    for p in PLACES.values():
        grid[p['cell']] = p['mapsec']
    for r in ROADS.values():
        for c in r['cells']:
            grid.setdefault(c, r['mapsec'])
    return grid


def sections():
    t = open(SECTIONS).read()
    j = json.loads(t)
    home = {}
    for t_ in TOWNS.values():
        home[t_['mapsec']] = t_['cell']
    for p in PLACES.values():
        home[p['mapsec']] = p['cell']
    for r in ROADS.values():
        home.setdefault(r['mapsec'], r['cells'][0])
    for s in j['map_sections']:
        if s['id'] in home:
            s['x'], s['y'] = home[s['id']]
            s['width'] = s['height'] = 1
        if s['id'] in NAMES:
            s['name'] = NAMES[s['id']]
    open(SECTIONS, 'w').write(json.dumps(j, indent=2) + ('\n' if t.endswith('\n') else ''))


def layout_h():
    grid = all_cells()
    rows = []
    for r in range(15):
        rows.append('    {' + ', '.join(grid.get((c, r), 'MAPSEC_NONE') for c in range(28)) + '},')
    open(LAYOUT_H, 'w').write('static const mapsec_u8_t sRegionMap_MapSectionLayout[MAP_HEIGHT][MAP_WIDTH] = {\n'
                              + '\n'.join(rows) + '\n};\n')


def neighbour_cells(map_id):
    """the cells of whatever lies across a connection"""
    for k, t in TOWNS.items():
        if mj(TOWN_FOLDERS[k])['id'] == map_id:
            return [t['cell']]
    for k, r in ROADS.items():
        if mj(ROAD_FOLDERS[k])['id'] == map_id:
            return r['cells']
    return []


def road_order(key):
    """the road's cells in the order its map runs (top to bottom, or left to right)"""
    j = mj(ROAD_FOLDERS[key])
    cells = ROADS[key]['cells']
    conns = j.get('connections') or []
    axis = 'y' if any(c['direction'] in ('up', 'down') for c in conns) else 'x'
    if len(cells) == 1:
        return axis, cells
    first = [c for c in conns if c['direction'] in ('up', 'left')]
    last = [c for c in conns if c['direction'] in ('down', 'right')]
    adj = lambda a, b: abs(a[0] - b[0]) + abs(a[1] - b[1]) == 1
    if first:
        nb = neighbour_cells(first[0]['map'])
        if any(adj(cells[-1], n) for n in nb) and not any(adj(cells[0], n) for n in nb):
            cells = cells[::-1]
    elif last:
        nb = neighbour_cells(last[0]['map'])
        if any(adj(cells[0], n) for n in nb) and not any(adj(cells[-1], n) for n in nb):
            cells = cells[::-1]
    return axis, cells


def cells_h():
    rows = []
    for k, folder in TOWN_FOLDERS.items():
        rows.append((mj(folder)['id'], 'y', [TOWNS[k]['cell']]))
    for k, folder in ROAD_FOLDERS.items():
        axis, cells = road_order(k)
        rows.append((mj(folder)['id'], axis, cells))
    for folder, cell in EXTRA_CELLS.items():
        rows.append((mj(folder)['id'], 'y', [cell]))
    out = ['// Generated by tools_pounamu/townmap/apply.py from layout.py - edit there, not here.',
           '// Where each Pounamu outdoor map sits on the town map: its cells in the order the map',
           '// runs (top to bottom, or left to right), so the player\'s head moves along a long road.',
           '#define POUNAMU_MAP_CELLS_MAX 4', '',
           'struct PounamuMapCells', '{', '    u16 map;   // (group << 8) | num', '    u8 alongX;',
           '    u8 count;', '    u8 x[POUNAMU_MAP_CELLS_MAX];', '    u8 y[POUNAMU_MAP_CELLS_MAX];', '};', '',
           'static const struct PounamuMapCells sPounamuMapCells[] =', '{']
    for mid, axis, cells in rows:
        assert len(cells) <= 4, mid
        xs = ', '.join(str(c[0]) for c in cells)
        ys = ', '.join(str(c[1]) for c in cells)
        out.append(f'    {{(MAP_GROUP({mid}) << 8) | MAP_NUM({mid}), {int(axis == "x")}, {len(cells)}, {{{xs}}}, {{{ys}}}}},')
    out += ['};', '']
    open(CELLS_H, 'w').write('\n'.join(out))


def map_sections():
    changed = []
    for p in sorted(glob.glob(os.path.join(ROOT, 'data/maps/*/map.json'))):
        folder = os.path.basename(os.path.dirname(p))
        j = json.load(open(p))
        sec = j.get('region_map_section')
        new = None
        if sec == 'MAPSEC_ROUTE_121' and (folder.startswith('Tamaki') or folder.startswith('SkyTower')):
            new = 'MAPSEC_OLDALE_TOWN'
        elif folder == 'Piopiotahi':
            new = 'MAPSEC_ROUTE_130'
        elif folder.startswith('PounamuLeague'):
            new = 'MAPSEC_MOSSDEEP_CITY'
        if new and new != sec:
            j['region_map_section'] = new
            save_mj(folder, j)
            changed.append(folder)
    return changed


def heal_location():
    t = open(HEAL).read()
    j = json.loads(t)
    hl = j['heal_locations']
    if not any(h['id'] == 'HEAL_LOCATION_HERETAUNGA_TOWN' for h in hl):
        home = next(h for h in hl if h['id'] == 'HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F')
        door = next(w for w in mj('HeretaungaTown')['warp_events'] if w['dest_map'] == 'MAP_HERETAUNGA_HOMESTEAD_1F')
        hl.append({'id': 'HEAL_LOCATION_HERETAUNGA_TOWN', 'map': 'MAP_HERETAUNGA_TOWN', 'x': door['x'],
                   'y': door['y'] + 1, 'respawn_map': home['respawn_map'], 'respawn_npc': home['respawn_npc']})
        open(HEAL, 'w').write(json.dumps(j, indent=2, ensure_ascii=False) + ('\n' if t.endswith('\n') else ''))


FLY = {  # a town's section -> (the map, the heal location Fly lands at)
    t['mapsec']: (mj(TOWN_FOLDERS[k])['id'], 'HEAL_LOCATION_' + mj(TOWN_FOLDERS[k])['id'][4:]) for k, t in TOWNS.items()}
FLY['MAPSEC_PETALBURG_CITY'] = ('MAP_AHURIRI_CITY', 'HEAL_LOCATION_AHURIRI_CITY')


def fly_table():
    """region_map.c: each town section flies to its Pounamu town (they pointed at Hoenn's)"""
    p = os.path.join(ROOT, 'src/region_map.c')
    s = open(p).read()
    for sec, (mid, heal) in FLY.items():
        s, n = re.subn(r'(\n    \[' + sec + r'\] = )\{[^}]*\},',
                       rf'\g<1>{{MAP_GROUP({mid}), MAP_NUM({mid}), {heal}}},', s, count=1)
        assert n == 1, sec
    open(p, 'w').write(s)


def visited_flags():
    done = []
    for k, folder in TOWN_FOLDERS.items():
        flag = VISITED[TOWNS[k]['mapsec']]
        p = os.path.join(ROOT, 'data/maps', folder, 'scripts.inc')
        s = open(p).read()
        if f'setflag {flag}' in s:
            continue
        head = f'{folder}_MapScripts::\n'
        assert s.startswith(head), folder
        m = re.search(r'map_script MAP_SCRIPT_ON_TRANSITION, (\w+)', s.split('.byte 0', 1)[0])
        if m:
            label = m.group(1)
            i = s.index(f'\n{label}:') + 1
            j = s.index('\n', i) + 1
            s = s[:j] + f'\tsetflag {flag}\n' + s[j:]
        else:
            label = f'{folder}_OnTransition_Visited'
            s = (head + f'\tmap_script MAP_SCRIPT_ON_TRANSITION, {label}\n' + s[len(head):])
            s = s.replace('\t.byte 0\n', f'\t.byte 0\n\n{label}:\n\tsetflag {flag}\n\tend\n', 1)
        open(p, 'w').write(s)
        done.append(folder)
    return done


if __name__ == '__main__':
    sections()
    layout_h()
    cells_h()
    print('sections moved to:', map_sections())
    heal_location()
    fly_table()
    print('visited flags added:', visited_flags())
