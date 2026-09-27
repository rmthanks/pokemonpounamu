#!/usr/bin/env python3
"""Route 2 (Bay of Plenty): Opotiki (south) along the coast to Tauranga (north) -
the long Bay of Plenty beach, Mataata's lagoon, and Te Puke's kiwifruit blocks on
the way into Tauranga.

The sea closes at both ends (the vanilla shore at the Opotiki end, bush over it
at the Tauranga end) so it never meets the map's edge in view. Petalburg tileset
(every tile primary)."""
from build import build

SPEC = dict(
    folder='Route2BoP', layout='LAYOUT_ROUTE2_BOP', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_OPOTIKI': 14, 'MAP_TAURANGA': 12},
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTT...............PP.TTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTT.............s.PP.TTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTT..TT..TT..TT...PP,TTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTT..TT..TT..TT...PP,TTTTTTTTTTTTTTTTTTTTTTTTTT",  # 5
        "TTTT...............PP.......TTTTTTTTTTTTTTTTTTTT",
        "TTTT...............PP.......TTTTTTTTTTTTTTTTTTTT",
        "TTTT..TT..TT..TT...PP............BBBBBBBTTTTTTTT",
        "TTTT..TT..TT..TT...PP...a........BBBBBBBTTTTTTTT",
        "TTTT...............PP............BBBBBSSSSSSSSSS",  # 10
        "TTTT...............PP............BBBBBSSSSSSSSSS",
        "TTTT**.............PP............BBBBBSSSSSSSSSS",
        "TTTT...............PP............BBBBBSSSSSSSSSS",
        "TT.................PPPPPPPPPPPPBBBBBBSSSSSSSSSSS",
        "TT......b..........PPPPPPPPPPPPBBBBBBSSSSSSSSSSS",  # 15
        "TT......................,,,,.PPBBBBBBSSSSSSSSSSS",
        "TT......................,,,,.PPBBiBBBSSSSSSSSSSS",
        "TTTT..,,,,,,,,..........,,,,.PPBBBBBBBBSSSSSSSSS",
        "TTTT..,,,,,,,,..........,,,,.PPBBBBBBBBSSSSSSSSS",
        "TTTT..,,,,,,,,...............PPBBBBBBBBSSSOOSSSS",  # 20
        "TTTT..,,,,,,,,...............PPBBBBBBBBSSSOOSSSS",
        "TTTT......................e..PPBBBBBSSSSSSSSSSSS",
        "TTTT.........................PPBBBBBSSSSSSSSSSSS",
        "TTTTTT..............,,,,,,...PPBBBBBSSSSSSSSSSSS",
        "TTTTTT..............,,,,,,...PPBBBBBSSSSSSSSSSSS",  # 25
        "TTTTTT....WWWWWWWW...........PPBBBBBcSSSSSSSSSSS",
        "TTTTTT....WWWWWWWW...........PPBBBBBBSSSSSSSSSSS",
        "TTTTTT....WWWWWWWW......TT...PPBBBBBBSSSSSSSSSSS",
        "TTTTTT....WWWWWWWW......TT...PPBBBBBBSSSSSSSSSSS",
        "TTTT.....f...................PPBBBBBBBSSSSSSSSSS",  # 30
        "TTTT.........................PPBBBBBBBSSSSSSSSSS",
        "TTTT................,,,,,,,..PPBBBBBBBSSSSSSSSSS",
        "TTTT................,,,,,,,..PPBBBBBBBSSSSSSSSSS",
        "TTTT..,,,,,,,,......,,,,,,,..PPBBBBBSSSSSSSSOOSS",
        "TTTT..,,,,,,,,......,,,,,,,..PPBBBBBSSSSSSSSOOSS",  # 35
        "TTTTTT,,,,,,,,...............PPBBBBBSSSSSSSSSSSS",
        "TTTTTT,,,,,,,,...............PPBBBBBSSSSSSSSSSSS",
        "TTTTTT................**.....PPBBBBBBSSSSSSSSSSS",
        "TTTTTT.......................PPBBBBBBSSSSSSSSSSS",
        "TTTTTT.........g.............PPBBBBBBSSSSSSSSSSS",  # 40
        "TTTTTT.......................PPBBBBBBSSSSSSSSSSS",
        "TTTTTTTTTT...................PPBBBBBBBBSSSSSSSSS",
        "TTTTTTTTTT...................PPBBBdBBBBSSSSSSSSS",
        "TTTTTTTT.............PPPPPPPPPPBBBBBBBBSSSSSSSSS",
        "TTTTTTTT.............PPPPPPPPPPBBBBBBBBSSSSSSSSS",  # 45
        "TTTTTTTT.............PP...........BBBBBBSSSSSSSS",
        "TTTTTTTT.............PP...........BBBBBBSSSSSSSS",
        "TTTTTTTTTT....,,,,,,.PP...TT......BBBBBBSSSSSSSS",
        "TTTTTTTTTT....,,,,,,.PP...TT......BBBBBBSSSSSSSS",
        "TTTTTTTTTT....,,,,,,.PP...........BBBBTT........",  # 50
        "TTTTTTTTTT....,,,,,,.PP....k......BBBBTT........",
        "TTTTTTTTTT..**.......PP...........BBBBTTTTTTTTTT",
        "TTTTTTTTTT...........PP...........BBBBTTTTTTTTTT",
        "TTTTTTTTTTTTTT.......PP.,,,,,,....TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTT.......PP.,,,,,,....TTTTTTTTTTTTTT",  # 55
        "TTTTTTTTTTTTTT..TT...PP.,,,,,,....TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTT..TT...PP.,,,,,,....TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP...........TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT...s.PP...........TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP...........TTTTTTTTTTTTTT",  # 60
        "TTTTTTTTTTTTTTTT.....PP...........TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTTTT",
    ],
    objects={
        'a': ('Rangi', 'LEFT'), 'b': ('Kiri', 'RIGHT'), 'c': ('PPare', 'DOWN'), 'd': ('PAnika', 'UP'),
        'e': ('PBeau', 'LEFT'), 'f': ('PBlake', 'RIGHT'), 'g': ('PCaleb', 'RIGHT'), 'i': ('PCharlie', 'DOWN'),
        'k': ('PDylan', 'LEFT'),
    },
    sign_text=[('SignNorth', ['ROUTE 2\\n', 'South to OPOTIKI$']),
               ('SignSouth', ['ROUTE 2\\n', 'North to TAURANGA$'])],
)

if __name__ == '__main__':
    build(SPEC)
