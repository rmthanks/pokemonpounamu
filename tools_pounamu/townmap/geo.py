"""The town map's geography: NZ's real coastline, turned so Te Rerenga Wairua sits in the
top-right corner and Rakiura in the bottom-left, and scaled to fill the 28x15 fly grid.

Turned about 48 degrees clockwise, NZ's length runs along the screen's diagonal: the country
keeps its true shape and comes out about 52 km to a grid cell (north-up it would be about
100 km, with Hastings, Napier and Te Mata in one cell). Coastline: Natural Earth 1:50m
(public domain), data/nz_coast_ne50m.json."""
import json, math, os
HERE = os.path.dirname(os.path.abspath(__file__))

TILT = float(os.environ.get("TOWNMAP_TILT", 48.0))   # degrees clockwise: north points up and to the right
MARGIN = (0.35, 0.25)       # cells of sea kept at the left/right and top/bottom
GRID_W, GRID_H = 28, 15
_K = math.cos(math.radians(41.0))

COAST = json.load(open(os.path.join(HERE, 'data', 'nz_coast_ne50m.json')))   # rings of [lon, lat]


def _km(lat, lon):
    return lon * _K * 111.3, -lat * 111.3         # x east, y south


def _rot(x, y, t=math.radians(TILT)):
    return x * math.cos(t) - y * math.sin(t), x * math.sin(t) + y * math.cos(t)


_all = [_rot(*_km(lat, lon)) for ring in COAST for lon, lat in ring]
_xs, _ys = [p[0] for p in _all], [p[1] for p in _all]
_w, _h = max(_xs) - min(_xs), max(_ys) - min(_ys)
SCALE = min((GRID_W - 2 * MARGIN[0]) / _w, (GRID_H - 2 * MARGIN[1]) / _h)   # cells per km
_OX = (GRID_W - _w * SCALE) / 2 - min(_xs) * SCALE
_OY = (GRID_H - _h * SCALE) / 2 - min(_ys) * SCALE
KM_PER_CELL = 1 / SCALE


def proj(lat, lon):
    """(lat, lon) -> fly-grid units (x right, y down; cell (c, r) covers [c, c+1) x [r, r+1))"""
    x, y = _rot(*_km(lat, lon))
    return x * SCALE + _OX, y * SCALE + _OY


def cell(lat, lon):
    x, y = proj(lat, lon)
    return int(math.floor(x)), int(math.floor(y))


def coast_polys():
    """every island's outline in grid units"""
    return [[proj(lat, lon) for lon, lat in ring] for ring in COAST]
