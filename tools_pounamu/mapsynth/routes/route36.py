#!/usr/bin/env python3
"""Route 36: Tauranga (east) over the hills to Rotorua (west) - the kiwifruit
blocks outside Tauranga, the slip the road crew has just cleared, the pine
forest on the ridge, and Lake Rotoiti on the way down. Petalburg tileset (every
tile primary)."""
from build import build

SPEC = dict(
    folder='Route36', layout='LAYOUT_ROUTE36', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_TAURANGA': -4, 'MAP_ROTORUA': -2},
    rows=[
        #0         1         2         3         4         5
        #012345678901234567890123456789012345678901234567890123456789
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTT........,,,,,.TTTTTTTTTT....RRRRRR..................TT",
        "TTTTTT........,,,,,.TTTTTTTTTT....RQQQQR..................TT",
        "TTTTTT........,,,,,.TTTTTTTTTT**..RQQQQR..TT......TT..TT..TT",
        "TTTTTT........,,,,,.TTTTTTTTTT....RRRRRR..TT......TT..TT..TT",  # 5
        "TT..............b................a........................TT",
        "TT........PPPPPPPPPPPPPPPPPPPPPPPP........................TT",
        "TT..,,,,,.PPPPPPPPPPPPPPPPPPPPPPPP................TT..TT..TT",
        "TT..,,,,,.PP....................PP..,,,,,,,,......TT..TT..TT",
        "TT..,,,,,.PP..........,,,,TTTT..PP..,,,,,,,,**............TT",  # 10
        "TT..s,,,,.PP..........,,,,TTTT..PP..,,,,,,,,.....e.....s..TT",
        "PPPPPPPPPPPP..........,,,,TTTT..PP..,,,,,,,,..PPPPPPPPPPPPPP",
        "PPPPPPPPPPPP..........,,,,TTTT..PP............PPPPPPPPPPPPPP",
        "TT........................TTTT..PP............PP..........TT",
        "TT.d......................TTTT..PP............PP,,,,,,,,..TT",  # 15
        "TT....TT,,,.WWWWWWWWWWWW........PP............PP,,,,,,,,g.TT",
        "TT....TT,,,.WWWWWWWWWWWW........PPPPPPPPPPPPPPPP..........TT",
        "TT......,,,.WWWWWWWWWWWW,,,,,,,,PPPPPPPPPPPPPPPP..........TT",
        "TT......,,,.WWWWWWWWWWWW,,,,,,,,......c...................TT",
        "TTTTTTTT....WWWWWWWWWWWW,,,,,,,,..TTTTTTTT..TT..TT........TT",  # 20
        "TTTTTTTT....WWWWWWWWWWWW,,,,,,,,..TTTTTTTT..TT..TT........TT",
        "TTTTTTTT..........................TTTTTTTT..........TTTTTTTT",
        "TTTTTTTT..................f.......TTTTTTTT..........TTTTTTTT",
        "TTTTTTTT....**....TTTTTTTTTTTTTTTTTTTTTTTT..........TTTTTTTT",
        "TTTTTTTT..........TTTTTTTTTTTTTTTTTTTTTTTT..........TTTTTTTT",  # 25
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
    ],
    objects={
        'a': ('Roadworks', 'DOWN'), 'b': ('PElla', 'DOWN'), 'c': ('PFinn', 'UP'), 'd': ('PHarper', 'RIGHT'),
        'e': ('PHunter', 'LEFT'), 'f': ('PIsla', 'UP'), 'g': ('PJack', 'LEFT'),
    },
    sign_text=[('SignWest', ['ROUTE 36\\n', 'West to ROTORUA$']),
               ('SignEast', ['ROUTE 36\\n', 'East to TAURANGA$'])],
)

if __name__ == '__main__':
    build(SPEC)
