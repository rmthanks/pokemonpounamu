#!/usr/bin/env python3
"""Route 1 (Kapiti Coast): Whanganui (north) down the west coast to Wellington
(south) - dairy paddocks, the long Kapiti beach, and Kapiti Island out in the
haze (a bush-covered island ringed by its own shore), with the ranges inland.

The Tasman runs down the west side and closes at both ends the vanilla way, so
it never meets the map's edge in view. Petalburg tileset (every tile primary)."""
from build import build

SPEC = dict(
    folder='Route1Kapiti', layout='LAYOUT_ROUTE1_KAPITI', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_WHANGANUI': 18, 'MAP_WELLINGTON': 18},
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.,,,,,,..TTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PPs,,,,,,..TTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.,,,,,,..TTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.,,,,,,..TTTTTTTTTTTT",  # 5
        "TTTTTTTTTTBBBBBBB...PPPPPPP.........TTTTTTTTTTTT",
        "TTTTTTTTTTBBBBBBB...PPPPPPP...**....TTTTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PP................TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PP................TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PP......RRRRRRRR..TTTTTTTTTT",  # 10
        "SSSSSSSSSSSSBBBBB...PP......RRRRRRRR..TTTTTTTTTT",
        "SSSSSSSSSSSSBBBaB...PP..TT..RRQQQQRR..TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PP..TT..RRQQQQRR..TTTTTTTTTT",
        "SSSSSSSSSSSSSBBBBB..PP......RRQQQQRRTTTTTTTTTTTT",
        "SSSSSSSSSSSSSBBBBB..PP......RRQQQQRRTTTTTTTTTTTT",  # 15
        "SSSSSSSSSSSSSBBBBB..PPb.....RRRRRRRRTTTTTTTTTTTT",
        "SSSSSSSSSSSSSBBBBB..PP......RRRRRRRRTTTTTTTTTTTT",
        "SSSSSSSSSSSSSBBBBB..PP..............TTTTTTTTTTTT",
        "SSSSSSSSSSSSSBBBBB..PP..............TTTTTTTTTTTT",
        "SSSSSSSSSSSSSSBkBBB.PP,,,,,,..c.......TTTTTTTTTT",  # 20
        "SSSSSSSSSSSSSSBBBBB.PP,,,,,,..........TTTTTTTTTT",
        "SS......SSSSSSBBBBB.PP,,,,,,..........TTTTTTTTTT",
        "SS......SSSSSSBBBBB.PP,,,,,,..........TTTTTTTTTT",
        "SSTTTTTTSSSSSSBBBBB.PP............e...TTTTTTTTTT",
        "SSTTTTTTSSSSSSBBBBB.PP................TTTTTTTTTT",  # 25
        "SSTTTTTTSSSSBBBBB...PP....,,,,,,,,......TTTTTTTT",
        "SSTTTTTTSSSSBBBBB...PP....,,,,,,,,......TTTTTTTT",
        "SSTTTTTTSSSSBBBBB...PP....,,,,,,,,......TTTTTTTT",
        "SSTTTTTTSSSSBBBBB...PP....,,,,,,,,......TTTTTTTT",
        "SSTTTTTTSSSSBBBBB...PPf.................TTTTTTTT",  # 30
        "SSTTTTTTSSSSBBBBB...PP..................TTTTTTTT",
        "SSTTTTTTSSSSSBBBBB..PP........TT......TTTTTTTTTT",
        "SSTTTTTTSSSSSBBBBB..PP........TT......TTTTTTTTTT",
        "SSSSSSSSSSSSSBdBBB..PP..**............TTTTTTTTTT",
        "SSSSSSSSSSSSSBBBBB..PP................TTTTTTTTTT",  # 35
        "SSSSSSSSSSSSSBBBBB..PP....LLLLLLLL....TTTTTTTTTT",
        "SSSSSSSSSSSSSBBBBB..PP................TTTTTTTTTT",
        "SSSSSSSSSSSBBBBB....PP..............TTTTTTTTTTTT",
        "SSSSSSSSSSSBBBBB....PP..............TTTTTTTTTTTT",
        "SSSSSSSSSSSBBBBB....PP,,,,,,........TTTTTTTTTTTT",  # 40
        "SSSSSSSSSSSBBBBB....PP,,,,,,........TTTTTTTTTTTT",
        "SSSSSSSSSSSBBBBB....PP,,,,,,..i.....TTTTTTTTTTTT",
        "SSSSSSSSSSSBBBBB....PP,,,,,,........TTTTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PP................TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PP................TTTTTTTTTT",  # 45
        "SSSSSSSSSSSSBBBBg...PP......,,,,,,....TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PP......,,,,,,....TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PPTT....,,,,,,....TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB...PPTT....,,,,,,....TTTTTTTTTT",
        "SSSSSSSSSSBBBBBB....PP..............TTTTTTTTTTTT",  # 50
        "SSSSSSSSSSBBBBBB....PP..............TTTTTTTTTTTT",
        "SSSSSSSSSSBBBBBB....PPPPPPP...**....TTTTTTTTTTTT",
        "SSSSSSSSSSBBBBBB....PPPPPPP.........TTTTTTTTTTTT",
        "SSSSSSSSSSBBBBBB.........PP.........TTTTTTTTTTTT",
        "SSSSSSSSSSBBBBBB.........PP.........TTTTTTTTTTTT",  # 55
        "..........TTBBBB.........PP.,,,,..TTTTTTTTTTTTTT",
        "..........TTBBBB.........PP.,,,,..TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTBBBB.......s.PP.,,,,..TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTBBBB.........PP.,,,,..TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",  # 60
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
    ],
    objects={
        'a': ('Tama2', 'LEFT'), 'b': ('Rae', 'RIGHT'), 'c': ('PGus', 'DOWN'), 'd': ('PHeath', 'UP'),
        'e': ('PIvy', 'LEFT'), 'f': ('PJonty', 'RIGHT'), 'g': ('PKane', 'LEFT'), 'i': ('PLena', 'DOWN'),
        'k': ('PMilo', 'DOWN'),
    },
    sign_text=[('SignNorth', ['ROUTE 1\\n', 'South to WELLINGTON$']),
               ('SignSouth', ['ROUTE 1\\n', 'North to WHANGANUI$'])],
)

if __name__ == '__main__':
    build(SPEC)
