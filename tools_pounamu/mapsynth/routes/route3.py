#!/usr/bin/env python3
"""Route 3: Ngamotu (north) round the Taranaki coast to Whanganui (south) - surf
beaches under the maunga, the dairy flats, and the long South Taranaki Bight.
Taranaki itself stands inland as a tiered rock mass east of the road.

The Tasman runs down the west side, closed under bush at the north and by the
vanilla shore (lip, canopy, trees, behind a tree) at the south, so it never meets
the map's edge in view. Petalburg tileset (every tile primary)."""
from build import build

SPEC = dict(
    folder='Route3', layout='LAYOUT_ROUTE3', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_NGAMOTU': 20, 'MAP_WHANGANUI': 18},
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTT.PP...........TTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTT.PPs..........TTTTTTTT",
        "TTTTTTTTBBBBBBBB....,,,,,,.PP...........TTTTTTTT",
        "TTTTTTTTBBBBBBBB....,,,,,,.PP...........TTTTTTTT",  # 5
        "SSSSSSSSSSBBBBBB...........PP...........TTTTTTTT",
        "SSSSSSSSSSBBBBBB...........PP..........2TTTTTTTT",
        "SSSSSSSSSSBBBBBB..PPPPPPPPPPP.........TTTTTTTTTT",
        "SSSSSSSSSSBBBBBB..PPPPPPPPPPP.........TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB.PP........**........TTTTTTTTTT",  # 10
        "SSSSSSSSSSSSBBBBB.PP..................TTTTTTTTTT",
        "SSSSSSSSSSSSBaBBB.PP..,,,,,,..........TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB.PP..,,,,,,..........TTTTTTTTTT",
        "SSSSSSSSSSSSBBBBB.PP..,,,,,,..RRRRRRRRRRTTTTTTTT",
        "SSSSSSSSSSSSBBBBB.PP..,,,,,,..RRRRRRRRRRTTTTTTTT",  # 15
        "SSSSSSSSSSBBBBB...PP..........RRQQQQQQRRTTTTTTTT",
        "SSSSSSSSSSBBBBB...PP....c.....RRQQQQQQRRTTTTTTTT",
        "SSSSSSSSSSBBBBB...PP..........RRQQQQQQRRTTTTTTTT",
        "SSSSSSSSSSBBBBB...PP..........RRQQQQQQRRTTTTTTTT",
        "SSSSSSSSSSBBBBB...PP..TT......RRQQQQQQRR..TTTTTT",  # 20
        "SSSSSSSSSSBBBBB...PP..TT......RRQQQQQQRR..TTTTTT",
        "SSSSSSSSSBBBBB....PP..........RRQQQQQQRR..TTTTTT",
        "SSSSSSSSSBBBBB....PP..........RRQQQQQQRR..TTTTTT",
        "SSSSSSSSSBBBbB....PP..........RRQQQQQQRR..TTTTTT",
        "SSSSSSSSSBBBBB....PP..........RRQQQQQQRR..TTTTTT",  # 25
        "SSSSSSSSSBBBBB....PP..**......RRRRRRRRRR..TTTTTT",
        "SSSSSSSSSBBBBB....PP..........RRRRRRRRRR..TTTTTT",
        "SSSSSSSSSSSBBBBB..PP......................TTTTTT",
        "SSSSSSSSSSSBBBBB..PP.....................1TTTTTT",
        "SSSSSSSSSSSBBBBB..PP,,,,,,,,......d.....TTTTTTTT",  # 30
        "SSSSSSSSSSSBBBBB..PP,,,,,,,,............TTTTTTTT",
        "SSSSSSSSSSSBBBBB..PP,,,,,,,,............TTTTTTTT",
        "SSSSSSSSSSSBBBBB..PP,,,,,,,,............TTTTTTTT",
        "SSSSSSSSSBBBBBB...PP....................TTTTTTTT",
        "SSSSSSSSSBBBBBB...PP....................TTTTTTTT",  # 35
        "SSSSSSSSSBBBBeB...PP....TT............TTTTTTTTTT",
        "SSSSSSSSSBBBBBB...PP....TT............TTTTTTTTTT",
        "SSSSSSSSSBBBBBB...PP........,,,,,,,,..TTTTTTTTTT",
        "SSSSSSSSSBBBBBB...PP........,,,,,,,,..TTTTTTTTTT",
        "SSSSSSSSSSBBBBBB..PPi.......,,,,,,,,..TTTTTTTTTT",  # 40
        "SSSSSSSSSSBBBBBB..PP........,,,,,,,,..TTTTTTTTTT",
        "SSSSSSSSSSBBBBBB..PP......f.............TTTTTTTT",
        "SSSSSSSSSSBBBBBB..PP....................TTTTTTTT",
        "SSSSSSSSSSBBBBgB..PP..,,,,,,............TTTTTTTT",
        "SSSSSSSSSSBBBBBB..PP..,,,,,,............TTTTTTTT",  # 45
        "SSSSSSSSSSBBBBB...PP..,,,,,,............TTTTTTTT",
        "SSSSSSSSSSBBBBB...PP..,,,,,,............TTTTTTTT",
        "SSSSSSSSSSBBBBB...PP............TT..TTTTTTTTTTTT",
        "SSSSSSSSSSBBBBB...PP............TT..TTTTTTTTTTTT",
        "SSSSSSSSSSBBBBB...PPPPPPPPP.........TTTTTTTTTTTT",  # 50
        "SSSSSSSSSSBBBBB...PPPPPPPPP.........TTTTTTTTTTTT",
        "SSSSSSSSSSBBBBB.......s..PP...**....TTTTTTTTTTTT",
        "SSSSSSSSSSBBBBB..........PP...k.....TTTTTTTTTTTT",
        "__________TTBBB.....TT...PP.,,,,TTTTTTTTTTTTTTTT",
        "__________TTBBB.....TT...PP.,,,,TTTTTTTTTTTTTTTT",  # 55
        "TTTTTTTTTTTTBBB..........PP.,,,,TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT3BB..........PP.,,,,TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",  # 60
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None), '3': ('FindItem#3', None),
        'a': ('Rico', 'LEFT'), 'b': ('Ana', 'RIGHT'), 'c': ('PZoe', 'DOWN'), 'd': ('PAshley', 'LEFT'),
        'e': ('PBella', 'RIGHT'), 'f': ('PCody', 'UP'), 'g': ('PDaisy', 'LEFT'), 'i': ('PEmma', 'RIGHT'),
        'k': ('PFlora', 'DOWN'),
    },
    sign_text=[('SignNorth', ['ROUTE 3\\n', 'South to WHANGANUI$']),
               ('SignSouth', ['ROUTE 3\\n', 'North to NGAMOTU$'])],
)

if __name__ == '__main__':
    build(SPEC)
