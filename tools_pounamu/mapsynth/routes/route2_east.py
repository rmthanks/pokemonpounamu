#!/usr/bin/env python3
"""Route 2 East: Wairoa (south) up SH2 to Turanga (north) - Nuhaka's paddocks, the
Morere bush with its hot pool, and Poverty Bay under Young Nick's Head.

The bay is closed on the east by the headland's bush, so the sea never meets the
map's edge; the sand runs along under it. Petalburg tileset (every tile here is
primary) so both towns' streets render correctly across the seams."""
from build import build

SPEC = dict(
    folder='Route2East', layout='LAYOUT_ROUTE2_EAST', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_WAIROA': 12, 'MAP_TURANGA': 14},
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
        "TTTTTT...............PP...BBBBBBTTTTTTTTTTTT",
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
        "TTTTTTTTTT...........PP.BBBBBBBBBBBBBBTTTTTT",
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
        "TTTTTTTTTT.....PPPPPP.....TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT.....PPPPPP.....TTTTTTTTTTTTTTTTTT",
        "TTTTTTTT...,,,,,,..PP..,,,,,,...TTTTTTTTTTTT",
        "TTTTTTTT...,,,,,,..PP..,,,,,,e..TTTTTTTTTTTT",
        "TTTTTTTT...........PP.........TTTTTTTTTTTTTT",  # 50
        "TTTTTTTT...........PP.........TTTTTTTTTTTTTT",
        "TTTTTT..,,,,,,.....PP..WWWW.....TTTTTTTTTTTT",
        "TTTTTT..,,,,,,.....PP..WWWW.....TTTTTTTTTTTT",
        "TTTTTT..f..........PP........**.TTTTTTTTTTTT",
        "TTTTTT.............PP..g........TTTTTTTTTTTT",  # 55
        "TTTTTTTTTT....s....PP...........TTTTTTTTTTTT",
        "TTTTTTTTTT.........PP...........TTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTT",
    ],
    objects={
        'a': ('Mihi', 'RIGHT'), 'b': ('Hemi', 'LEFT'), 'c': ('PMatiu', 'LEFT'), 'd': ('PRawiri', 'RIGHT'),
        'e': ('PTimoti', 'LEFT'), 'f': ('PPetera', 'RIGHT'), 'g': ('PHohepa', 'LEFT'),
    },
    sign_text=[('SignNorth', ['ROUTE 2\\n', 'South to WAIROA$']),
               ('SignSouth', ['ROUTE 2\\n', 'North to TURANGA$'])],
)

if __name__ == '__main__':
    build(SPEC)
