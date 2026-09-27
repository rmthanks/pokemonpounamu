#!/usr/bin/env python3
"""Route 2 East: from the Wairoa end (south) up SH2 to Turanga (north) - Nuhaka's paddocks, the
Morere bush with its hot pool, and Poverty Bay under Young Nick's Head.

The bay is closed on the east by the headland's bush, so the sea never meets the
map's edge; the sand runs along under it. Petalburg tileset (every tile here is
primary) so Turanga's streets render correctly across the seam.

Wairoa is no longer a stop (Sept 2026): the south edge runs straight on from Route 2 North
(the road's last stretch shifted a column west so the two meet), and the Wairoa end of the
road keeps its people - the old lighthouse keeper and his job, the eel man, Panapa - and
its hidden pounamu shard."""
from build import build

SPEC = dict(
    folder='Route2East', layout='LAYOUT_ROUTE2_EAST', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_ROUTE2_NORTH': 2, 'MAP_TURANGA': 8},
    rows=[
        #0         1         2         3         4
        #01234567890123456789012345678901234567890123
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT....s....PP...TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT.........PP...TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT....,,,,,..PP..b..TTTTTTTTTTTTTTTT",
        "TTTTTTTTTT....,,,,,..PP.....TTTTTTTTTTTTTTTT",  # 5
        "TTTTTTTT......,,,,,..PP.......TTTTTTTTTTTTTT",
        "TTTTTTTT.............PP.**....TTTTTTTTTTTTTT",
        "TTTTTTTT..TT.........PP...**....TTTTTTTTTTTT",
        "TTTTTTTT..TT.*.......PP.........TTTTTTTTTTTT",
        "TTTTTT...............PP...BBBBBBTTTTTTTTTTTT",  # 10
        "TTTTTT...............PP...BBBBB3TTTTTTTTTTTT",
        "TTTTTT....,,,,.......PP...BBBBSSSSSSSSTTTTTT",
        "TTTTTT....,,,,.......PP...BBBBSSSSSSSSTTTTTT",
        "TTTTTT...............PP..aBBBBSSSSSSSSTTTTTT",
        "TTTTTT...............PP...BBBBSSSSSSSSTTTTTT",  # 15
        "TTTTTTTT.............PP..BBBBBSSSSSSSSTTTTTT",
        "TTTTTTTT.............PP..BBBBBSSSSSSSSTTTTTT",
        "TTTTTTTT...,,,,,.....PP.BBBBBBSSSSSSSSTTTTTT",
        "TTTTTTTT...,,,,,.....PP.BBBBBBSSSSSSSSTTTTTT",
        "TTTTTTTT...,,,,,.....PP.BBBBBBBSSSSSSSTTTTTT",  # 20
        "TTTTTTTT...,,,,,.....PP.BBBBBBBSSSSSSSTTTTTT",
        "TTTTTTTTTT...........PP.BBBBBBBSSSSSSSTTTTTT",
        "TTTTTTTTTT...........PP.BBBBBBBSSSSSSSTTTTTT",
        "TTTTTTTTTT...........PP.BBBBBBBBSSSSSSTTTTTT",
        "TTTTTTTTTT...........PP.BBBBBBBBSSSSSSTTTTTT",  # 25
        "TTTTTTTTTT...........PP.BBBBBBBBBBBBBBTTTTTT",
        "TTTTTTTTTT...........PP.BBBBBBBBBBBBB1TTTTTT",
        "TTTTTTTTTT...........PP...TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT...........PP...TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT.........PP...TTTTTTTTTTTTTTTTTT",  # 30
        "TTTTTTTTTTTT.........PP...TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT...PPPPPPPP...TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT...PPPPPPPP...TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT...PP.......TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT...PP..c....TTTTTTTTTTTTTTTTTTTT",  # 35
        "TTTTTTTTTT.....PP..WWWWW..TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT.....PP..WWWWW..TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT.....PP..WWWWW..TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT.....PP.........TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT..d..PP,,,,.TT..TTTTTTTTTTTTTTTTTT",  # 40
        "TTTTTTTTTT.....PP,,,,.TT..TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT...PP.........TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT...PP.........TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTT.PP.........TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTT.PP.........TTTTTTTTTTTTTTTTTT",  # 45
        "TTTTTTTTTT.....PPPPP......TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT.....PPPPP......TTTTTTTTTTTTTTTTTT",
        "TTTTTTTT...,,,,,,.PP...,,,,,,...TTTTTTTTTTTT",
        "TTTTTTTT...,,,,,,.PP...,,,,,,e..TTTTTTTTTTTT",
        "TTTTTTTT..........PP..........TTTTTTTTTTTTTT",  # 50
        "TTTTTTTT.......k..PP..........TTTTTTTTTTTTTT",
        "TTTTTT..,,,,,,....PP..mWWWW.....TTTTTTTTTTTT",
        "TTTTTT..,,,,,,....PP...WWWWw....TTTTTTTTTTTT",
        "TTTTTT..f.........PP.........**.TTTTTTTTTTTT",
        "TTTTTT............PP...g........TTTTTTTTTTTT",  # 55
        "TTTTTTTTTT....s...PP............TTTTTTTTTTTT",
        "TTTTTTTTTTh.......PP...........2TTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTPP..TTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTPP..TTTTTTTTTTTTTTTTTTTTTT",
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None), '3': ('FindItem#3', None),
        'a': ('Mihi', 'RIGHT'), 'b': ('Hemi', 'LEFT'), 'c': ('PMatiu', 'LEFT'), 'd': ('PRawiri', 'RIGHT'),
        'e': ('PTimoti', 'LEFT'), 'f': ('PPetera', 'RIGHT'), 'g': ('PHohepa', 'LEFT'),
        'k': ('LightKeeper', 'RIGHT'), 'm': ('EelMan', 'RIGHT'), 'w': ('PWero', 'DOWN'),
    },
    hidden={'h': 0},
    sign_text=[('SignNorth', ['ROUTE 2\\n', 'South to AHURIRI$']),
               ('SignSouth', ['ROUTE 2\\n', 'North to TURANGA$'])],
)

if __name__ == '__main__':
    build(SPEC)
