#!/usr/bin/env python3
"""Route 35 (A): Turanga (south) up the East Coast to the Cape - Tolaga Bay,
Tokomaru Bay, Tawhai's driftwood camp on the sand, and the lookout where the
first light in the world lands on Hikurangi.

The Pacific runs up the whole east side and on into Route 35 (B); it closes above
Turanga the vanilla way (shore lip, canopy row, trees) behind a tree that keeps the
sand from leading round the corner, so nothing past the map's edge is in view."""
from build import build

SPEC = dict(
    folder='Route35A', layout='LAYOUT_ROUTE35_A', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_TURANGA': 20, 'MAP_ROUTE35_B': 0},
    defer_seams=['MAP_ROUTE35_B'],
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTT..PP..BBBBBBSSSSSSSS",  # 0
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTT..PP..BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTT....s.....PP..BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTT..........PP..BBBBBBSSSSSSSS",
        "TTTTTTTTRRRRRRRR.n............PPBBBBBBBBSSSSSSSS",
        "TTTTTTTTRRRRRRRR..............PPBBBBBBBBSSSSSSSS",  # 5
        "TTTTTTTTRRQQQQRR......**......PPBBBBBBBBSSSSSSSS",
        "TTTTTTTTRRQQQQRR..............PPBBBBBBBBSSSSSSSS",
        "TTTTTTTTRRRRRRRR..,,,,,,......PP..BBBBSSSSSSSSSS",
        "TTTTTTTTRRRRRRRR..,,,,,,......PPk.BBBBSSSSSSSSSS",
        "TTTTTT....,,,,...,,,,,,.......PP..BBBBSSSSSSSSSS",  # 10
        "TTTTTT....,,,,...,,,,,,.......PP..BBBBSSSSSSSSSS",
        "TTTTTT........................PPBBBBBSSSSSSSSSSS",
        "TTTTTT...i....................PPBBBBBSSSSSSSSSSS",
        "TTTTTTTT......................PPBcBBBSSSSSSSSSSS",
        "TTTTTTTT......................PPBBBBBSSSSSSSSSSS",  # 15
        "TTTTTTTTTT....,,,,,,..........PPBBBBSSSSSSSSSSSS",
        "TTTTTTTTTT....,,,,,,..........PPBBBBSSSSSSSSSSSS",
        "TTTTTTTTTT....,,f,,,..........PPBBBBSSSSSSSSSSSS",
        "TTTTTTTTTT....,,,,,,..........PPBBBBSSSSSSSSSSSS",
        "TTTTTTTTTTTT........TT........PPBBBBBSSSSSSSSSSS",  # 20
        "TTTTTTTTTTTT........TT........PPBBBBBSSSSSSSSSSS",
        "TTTTTTTTTTTT..................PPBBaBBSSSSSSSSSSS",
        "TTTTTTTTTTTT..................PPBBBBBSSSSSSSSSSS",
        "TTTTTTTTTT....WWWWWW........TTPPBBBBBBBSSSSSSSSS",
        "TTTTTTTTTT....WWWWWW........TTPPBBBBBBBSSSSSSSSS",  # 25
        "TTTTTTTTTT....WWWWWW..........PPBBBBBBBSSSSSSSSS",
        "TTTTTTTTTT....................PPBBBBBBBSSSSSSSSS",
        "TTTTTTTT....d.................PPBBBBBSSSSSSSSSSS",
        "TTTTTTTT......................PPBBBBBSSSSSSSSSSS",
        "TTTTTTTT..,,,,,,,,......PPPPPPPPBBBSSSSSSSSSSSSS",  # 30
        "TTTTTTTT..,,,,,,,,......PPPPPPPPBBBSSSSSSSSSSSSS",
        "TTTTTTTTTT,,,,,,,,......PP......BBBSSSSSSSSSSSSS",
        "TTTTTTTTTT,,,,,,,,......PP...e..BBBSSSSSSSSSSSSS",
        "TTTTTTTTTT..............PP......BBBBSSSSSSSSSSSS",
        "TTTTTTTTTT..............PP......BBBBSSSSSSSSSSSS",  # 35
        "TTTTTTTT....TT..........PP....TTBBBBSSSSSSSSSSSS",
        "TTTTTTTT....TT..........PP....TTBBBBSSSSSSSSSSSS",
        "TTTTTTTT..g.............PP.......BBBBBSSSSSSSSSS",
        "TTTTTTTT................PP.,,,,..BBBBBSSSSSSSSSS",
        "TTTTTTTTTT........TT....PP.,,,,..BBBBBSSSSSSSSSS",  # 40
        "TTTTTTTTTT........TT....PP.,,,,..BBBBBSSSSSSSSSS",
        "TTTTTTTTTTTT....h.......PP.m.....BBBBBBSSSSSSSSS",
        "TTTTTTTTTTTT............PP.......BBBBBBSSSSSSSSS",
        "TTTTTTTTTTTTTT..........PP**.....BBBBBBSSSSSSSSS",
        "TTTTTTTTTTTTTT..........PP.......BBBBBBSSSSSSSSS",  # 45
        "TTTTTTTTTTTTTT..,,,,,,..PP........BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTT..,,,,,,..PP........BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTT,,,,,,..PP..b.....BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTT,,,,,,..PP........BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTT........PP..........BBTT........",  # 50
        "TTTTTTTTTTTTTTTT........PP..........BBTT........",
        "TTTTTTTTTTTTTTTT........PPPPPPPPPP..BBTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT........PPPPPPPPPP..BBTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT................PPTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT................PPTTTTTTTTTTTTTT",  # 55
        "TTTTTTTTTTTTTTTTTT..,,,,........PPTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTT..,,,,........PPTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTT..........s...PPTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTT..............PPTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTT..........PPTTTTTTTTTTTTTT",  # 60
        "TTTTTTTTTTTTTTTTTTTTTT..........PPTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTPPTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTPPTTTTTTTTTTTTTT",
    ],
    objects={
        'a': ('Tai', 'UP'), 'b': ('Nikora', 'LEFT'), 'c': ('Tawhai', 'RIGHT'), 'd': ('PEruera', 'RIGHT'),
        'e': ('PHirini', 'DOWN'), 'f': ('PWetini', 'LEFT'), 'g': ('PMihi', 'RIGHT'), 'i': ('PNgaio', 'RIGHT'),
        'k': ('PRima', 'DOWN'), 'm': ('PKawe', 'LEFT'), 'n': ('DAWNJOB', 'RIGHT'),
    },
    hidden={'h': 0},
    sign_text=[('SignNorth', ['ROUTE 35\\n', 'South to TURANGA$']),
               ('SignSouth', ['ROUTE 35\\n', 'North to EAST CAPE$'])],
)

if __name__ == '__main__':
    build(SPEC)
