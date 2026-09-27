"""Pounamu town map (the Fly map): every town, road and landmark, placed by where it really is.

Towns and landmarks are real coordinates; roads are the real highways as waypoints. geo.py
turns them onto the 28x15 fly grid; here they become cells: a town is one cell, a road the
4-connected cells its highway passes through between two towns. NUDGE moves a town or place
a cell when two would share one. The art (draw.py) and the game data (apply.py) are both
built from what this file exports: TOWNS, PLACES, ROADS, SEA_LANES (cells) and LAKES, PEAKS."""
import math
from geo import proj, cell

# kind: 'city' = red orb (gym towns and the big cities), 'town' = blue orb
TOWN_GEO = {
    'TAMAKI':     ((-36.85, 174.76), 'city', 'MAPSEC_OLDALE_TOWN'),
    'TAURANGA':   ((-37.69, 176.17), 'city', 'MAPSEC_MAUVILLE_CITY'),
    'OPOTIKI':    ((-38.01, 177.29), 'town', 'MAPSEC_SLATEPORT_CITY'),
    'TURANGA':    ((-38.66, 178.02), 'town', 'MAPSEC_DEWFORD_TOWN'),
    'WAIROA':     ((-39.04, 177.42), 'town', 'MAPSEC_RUSTBORO_CITY'),
    'AHURIRI':    ((-39.49, 176.91), 'city', 'MAPSEC_PETALBURG_CITY'),
    'HERETAUNGA': ((-39.64, 176.84), 'city', 'MAPSEC_LITTLEROOT_TOWN'),
    'ROTORUA':    ((-38.14, 176.25), 'city', 'MAPSEC_LAVARIDGE_TOWN'),
    'TAUPO':      ((-38.69, 176.07), 'town', 'MAPSEC_FALLARBOR_TOWN'),
    'NGAMOTU':    ((-39.06, 174.08), 'town', 'MAPSEC_VERDANTURF_TOWN'),
    'WHANGANUI':  ((-39.93, 175.05), 'town', 'MAPSEC_PACIFIDLOG_TOWN'),
    'WELLINGTON': ((-41.29, 174.78), 'city', 'MAPSEC_SOOTOPOLIS_CITY'),
    'WAITOHI':    ((-41.29, 174.00), 'town', 'MAPSEC_EVER_GRANDE_CITY'),
    'WHAKATU':    ((-41.27, 173.28), 'city', 'MAPSEC_FORTREE_CITY'),
    'OTAUTAHI':   ((-43.53, 172.64), 'city', 'MAPSEC_LILYCOVE_CITY'),
    'OTEPOTI':    ((-45.87, 170.50), 'city', 'MAPSEC_MOSSDEEP_CITY'),
}
PLACE_GEO = {
    'TE_MATA':    ((-39.70, 176.90), 'MAPSEC_ROUTE_113'),
    'RUAPEHU':    ((-39.28, 175.57), 'MAPSEC_ROUTE_114'),
    'PIOPIOTAHI': ((-44.67, 167.93), 'MAPSEC_ROUTE_130'),
    'TAUPO_ISLE': ((-38.87, 175.92), None),             # Motutaiko, in Lake Taupo (no cursor name of its own)
}
NUDGE = {}                  # name -> (dx, dy) in cells, when two would share a cell

# the highways, town to town, as (lat, lon) waypoints between the two ends
ROAD_GEO = {
    'ORCHARD_ROAD':  ('HERETAUNGA', 'AHURIRI', [], 'MAPSEC_ROUTE_101'),
    'ROUTE2':        ('AHURIRI', 'WAIROA', [(-39.43, 176.87), (-39.33, 176.91), (-39.21, 176.89),
                                            (-39.13, 177.00), (-39.05, 177.18)], 'MAPSEC_ROUTE_102'),
    'ROUTE2_EAST':   ('WAIROA', 'TURANGA', [(-39.04, 177.74), (-38.98, 177.79), (-38.80, 177.90)],
                      'MAPSEC_ROUTE_102'),
    'ROUTE35':       ('TURANGA', 'OPOTIKI', [(-38.37, 178.30), (-38.13, 178.31), (-37.89, 178.32),
                                             (-37.66, 178.35), (-37.58, 178.30), (-37.62, 177.92),
                                             (-37.75, 177.68), (-37.95, 177.49)], 'MAPSEC_ROUTE_103'),
    'ROUTE2_BOP':    ('OPOTIKI', 'TAURANGA', [(-37.95, 176.99), (-37.89, 176.75), (-37.78, 176.33)],
                      'MAPSEC_ROUTE_102'),
    'ROUTE36':       ('TAURANGA', 'ROTORUA', [(-37.79, 176.12), (-38.08, 176.21)], 'MAPSEC_ROUTE_104'),
    'ROUTE5':        ('ROTORUA', 'TAUPO', [(-38.36, 176.36), (-38.62, 176.10)], 'MAPSEC_ROUTE_105'),
    'ROUTE5_RANGES': ('TAUPO', 'AHURIRI', [(-38.89, 176.37), (-39.03, 176.58), (-39.25, 176.68),
                                           (-39.39, 176.83)], 'MAPSEC_ROUTE_105'),
    'ROUTE1_DESERT': ('TAUPO', None, [(-38.99, 175.81), (-39.20, 175.70), (-39.48, 175.67)], 'MAPSEC_ROUTE_106'),
    'ROUTE43':       (None, 'NGAMOTU', [(-39.48, 175.67), (-39.42, 175.40), (-39.18, 175.40), (-38.88, 175.26),
                                        (-39.14, 174.74), (-39.34, 174.28)], 'MAPSEC_ROUTE_107'),
    'ROUTE3':        ('NGAMOTU', 'WHANGANUI', [(-39.12, 173.95), (-39.46, 173.86), (-39.59, 174.28),
                                               (-39.75, 174.48), (-39.76, 174.63)], 'MAPSEC_ROUTE_108'),
    'ROUTE1_KAPITI': ('WHANGANUI', 'WELLINGTON', [(-40.17, 175.38), (-40.47, 175.28), (-40.76, 175.15),
                                                  (-40.99, 174.95), (-41.13, 174.84)], 'MAPSEC_ROUTE_109'),
    'ROUTE6':        ('WAITOHI', 'WHAKATU', [(-41.28, 173.77), (-41.23, 173.58)], 'MAPSEC_ROUTE_110'),
    'ROUTE7':        ('WHAKATU', 'OTAUTAHI', [(-41.80, 172.33), (-42.33, 172.18), (-42.39, 172.40),
                                              (-42.52, 172.83), (-42.77, 172.85), (-43.06, 172.75)],
                      'MAPSEC_ROUTE_111'),
    'ROUTE1_SOUTH':  ('OTAUTAHI', 'OTEPOTI', [(-43.90, 171.75), (-44.40, 171.25), (-45.10, 170.97),
                                              (-45.48, 170.72)], 'MAPSEC_ROUTE_112'),
}
# two in-game maps share one highway: each takes its end of the road
SPLITS = {'ROUTE2': ('ROUTE2_BAY', 'ROUTE2_NORTH'), 'ROUTE35': ('ROUTE35_A', 'ROUTE35_B')}
SEA_GEO = [('WELLINGTON', 'WAITOHI', [(-41.36, 174.60), (-41.30, 174.40), (-41.22, 174.30)])]   # the Interislander

LAKE_GEO = [((-38.80, 175.90), (22, 14), 30),     # Taupo: centre, half-axes in km, tilt
            ((-38.08, 176.27), (6, 5), 0),        # Rotorua
            ((-45.05, 168.75), (38, 3), 65),      # Wakatipu
            ((-45.30, 167.65), (25, 4), 75),      # Te Anau
            ((-44.05, 170.17), (12, 3), 80),      # Pukaki
            ((-43.97, 170.53), (11, 3), 70)]      # Tekapo
PEAK_GEO = [((-39.28, 175.57), 'big'),            # Ruapehu
            ((-39.30, 174.06), 'big'),            # Taranaki
            ((-41.95, 172.25), 'small'), ((-42.55, 171.85), 'small'), ((-43.00, 171.40), 'small'),
            ((-43.595, 170.14), 'big'),           # Aoraki
            ((-44.10, 169.45), 'small'), ((-44.60, 168.75), 'small'), ((-45.10, 168.10), 'small')]


def _town_cells():
    out = {}
    for name, ((lat, lon), kind, sec) in TOWN_GEO.items():
        c = cell(lat, lon)
        dx, dy = NUDGE.get(name, (0, 0))
        out[name] = dict(cell=(c[0] + dx, c[1] + dy), kind=kind, mapsec=sec)
    return out


def _place_cells(towns):
    taken = {t['cell'] for t in towns.values()}
    out = {}
    for name, ((lat, lon), sec) in PLACE_GEO.items():
        c = cell(lat, lon)
        dx, dy = NUDGE.get(name, (0, 0))
        out[name] = dict(cell=(c[0] + dx, c[1] + dy), mapsec=sec)
    return out


def _trace(points):
    """the cells a polyline passes through, 4-connected (a diagonal step goes round by the
    side the line is nearer)"""
    cells = []
    for (x0, y0), (x1, y1) in zip(points, points[1:]):
        n = max(2, int(math.hypot(x1 - x0, y1 - y0) * 12))
        for i in range(n + 1):
            x, y = x0 + (x1 - x0) * i / n, y0 + (y1 - y0) * i / n
            c = (int(math.floor(x)), int(math.floor(y)))
            if not cells or cells[-1] != c:
                if cells and abs(cells[-1][0] - c[0]) + abs(cells[-1][1] - c[1]) == 2:
                    a, b = (cells[-1][0], c[1]), (c[0], cells[-1][1])
                    da = math.hypot(a[0] + 0.5 - x, a[1] + 0.5 - y)
                    db = math.hypot(b[0] + 0.5 - x, b[1] + 0.5 - y)
                    cells.append(a if da <= db else b)
                cells.append(c)
    return cells


def _road_points(towns, a, b, way):
    """a road as a line: from the first town's orb, through the real waypoints, to the last's"""
    pts = [proj(*w) for w in way]
    if a:
        pts = [(towns[a]['cell'][0] + 0.5, towns[a]['cell'][1] + 0.5)] + pts
    if b:
        pts = pts + [(towns[b]['cell'][0] + 0.5, towns[b]['cell'][1] + 0.5)]
    return pts


def _roads(towns):
    town_at = {t['cell']: k for k, t in towns.items()}
    out, lines = {}, {}
    for name, (a, b, way, sec) in ROAD_GEO.items():
        pts = _road_points(towns, a, b, way)
        lines[name] = pts
        cells = [c for c in _trace(pts) if c not in town_at]      # never a town's own cell
        # a road too short to have a cell of its own is found at its towns' cells
        ends = [towns[t]['cell'] for t in (a, b) if t]
        out[name] = dict(cells=cells, ends=ends, mapsec=sec)
    for whole, (first, second) in SPLITS.items():
        r = out.pop(whole)
        half = (len(r['cells']) + 1) // 2
        out[first] = dict(cells=r['cells'][:half], ends=r['ends'][:1] + r['cells'][half:half + 1], mapsec=r['mapsec'])
        out[second] = dict(cells=r['cells'][half:], ends=r['cells'][half - 1:half] + r['ends'][1:], mapsec=r['mapsec'])
    return out, lines


def _sea(towns):
    """sea routes as lines (the Interislander)"""
    return [_road_points(towns, a, b, way) for a, b, way in SEA_GEO]


TOWNS = _town_cells()
PLACES = _place_cells(TOWNS)
ROADS, ROAD_LINES = _roads(TOWNS)
SEA_LANES = _sea(TOWNS)
LAKES = [(proj(*c), ax, tilt) for c, ax, tilt in LAKE_GEO]
PEAKS = [(proj(*c), size) for c, size in PEAK_GEO]
