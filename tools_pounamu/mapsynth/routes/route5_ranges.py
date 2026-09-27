#!/usr/bin/env python3
"""Route 5 East (the Titiokura ranges): out of Taupo toward Ahuriri - the short
road home, over the ranges, and the Mob's two grunts standing across it. The road
carries on past them to the east edge; it's the player who can't.

A dead end by design: the builder checks that the grunts seal the road and that
the road really does go on beyond them. Petalburg tileset (every tile primary)."""
from build import build

SPEC = dict(
    folder='Route5Ranges', layout='LAYOUT_ROUTE5_RANGES', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_TAUPO': 2},
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTT......TT......TT......RRRRRRRRRRTTTTTTTTTT",
        "TTTTTT......TT......TT......RRRRRRRRRRTTTTTTTTTT",
        "TTTTTTm.......d.............RRQQQQQQRRTTTTTTTTTT",
        "TTTTTT......................RRQQQQQQRRTTTTTTTTTT",  # 5
        "TT......PPPPPPPPPPPPPPPPPP..RRQQQQQQRRTTTTTTTTTT",
        "TT......PPPPPPPPPPPPPPPPPP..RRQQQQQQRRTTTTTTTTTT",
        "TT......PP,,,,,,,,......PP..RRRRRRRRRRTTTTTTTTTT",
        "TT......PP,,,,,,,,....f.PP.hRRRRRRRRRRTTTTTTTTTT",
        "TT..TT..PP,,,,,,,,......PP,,,,,,......TTTTTTTTTT",  # 10
        "TT..TT..PP,,,,,,,,......Pj,,,,,,.....sTTTTTTTTTT",
        "PPPcPPPPPP..............PP,,,,,,..PPPPPPaPPPPzPP",
        "PPPPPPPPPP..............PP,,,,,,..PPPPPPbPPPPPPP",
        "TT,,,,,,..RRRRRRRRRRRR..PP.....e..PP..TTTTTTTTTT",
        "TT,,,,,,..RRRRRRRRRRRR..PP........PPg.TTTTTTTTTT",  # 15
        "TT,,,,,,..RRQQQQQQQQRR..PPPPPPPPPPPP..TTTTTTTTTT",
        "TT,,,,,,..RRQQQQQQQQRR..PPPPPPPPPPPP..TTTTTTTTTT",
        "TT.k......RRQQQQQQQQRR................TTTTTTTTTT",
        "TT........RRQQQQQQQQRR................TTTTTTTTTT",
        "TTTTTTTT..RRRRRRRRRRRR....LLLLLLLLLL,,TTTTTTTTTT",  # 20
        "TTTTTTTT..RRRRRRRRRRRR..............,,TTTTTTTTTT",
        "TTTTTTTT..........,,,,,,.i..WWWWWW..,,TTTTTTTTTT",
        "TTTTTTTT..........,,,,,,....WWWWWW..,,TTTTTTTTTT",
        "TTTTTTTT..........,,,,,,**............TTTTTTTTTT",
        "TTTTTTTT..........,,,,,,..............TTTTTTTTTT",  # 25
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
    ],
    objects={
        'a': ('Grunt1', 'LEFT'), 'b': ('Grunt2', 'LEFT'), 'c': ('PPete', 'RIGHT'), 'd': ('PRata', 'DOWN'),
        'e': ('PSid', 'LEFT'), 'f': ('PTila', 'DOWN'), 'g': ('PUmi', 'LEFT'), 'i': ('PVada', 'UP'),
        'k': ('PWes', 'RIGHT'),
    },
    hidden={'h': 0, 'j': 1, 'm': 2},
    sign_text=[('Sign', None)],
    seal=dict(by=('Grunt1', 'Grunt2'), beyond='z'),
)

if __name__ == '__main__':
    build(SPEC)
