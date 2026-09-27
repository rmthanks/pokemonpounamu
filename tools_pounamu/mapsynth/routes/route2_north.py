#!/usr/bin/env python3
"""Route 2 North: from the top of Hawke Bay up SH2 toward Wairoa - the Tangoio beach
where the bay ends, the climb inland over the Devil's Elbow, Lake Tūtira, and the
sheep paddocks on the Wairoa side.

The sea at the bottom carries on from Route 2 Bay (same columns, offset 0) and
closes under a line of bush along its north shore; nothing past the map's east
edge is ever in view from the sand. Drawn with Petalburg (all tiles here are
primary). Wairoa is no longer a stop (Sept 2026): the north edge runs straight on into
Route 2 East, and Akenehi, Wairoa's farmer, works the paddocks here."""
from build import build

SPEC = dict(
    folder='Route2North', layout='LAYOUT_ROUTE2_NORTH', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_ROUTE2_BAY': 0, 'MAP_ROUTE2_EAST': -2},
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTTTPP..TTTTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTPP..TTTTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT...s..PP....TTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT......PP....TTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTT..,,,,,.PP..g..,,,,,..TTTTTTTTTTTTTTTTTT",
        "TTTTTTTT..,,,,,.PP.....,,,,,..TTTTTTTTTTTTTTTTTT",
        "TTTTTT....,,,,,.PP.....,,,,,....TTTTTTTTTTTTTTTT",
        "TTTTTT..........PP..............TTTTTTTTTTTTTTTT",
        "TTTTTT..TT..u...PP...f..........TTTTTTTTTTTTTTTT",
        "TTTTTT..TT......PP..............TTTTTTTTTTTTTTTT",
        "TTTT............PP..,,,,....TT..TTTTTTTTTTTTTTTT",
        "TTTT..**........PP..,,,,....TT..TTTTTTTTTTTTTTTT",
        "TTTT............PP............TTTTTTTTTTTTTTTTTT",
        "TTTT............PP....e.......TTTTTTTTTTTTTTTTTT",
        "TTTTTT..........PP....WWWWWWWWWW....TTTTTTTTTTTT",
        "TTTTTT..,,,,....PP..WWWWWWWWWWWW....TTTTTTTTTTTT",
        "TTTTTT..,,,,....PP..WWWWWWWWWWWW..d.TTTTTTTTTTTT",
        "TTTTTT..........PP..WWWWWWWWWWWW....TTTTTTTTTTTT",
        "TTTTTT..........PPa.WWWWWWWWWWWW....TTTTTTTTTTTT",
        "TTTTTT..........PP..WWWWWWWWWWWW....TTTTTTTTTTTT",
        "TTTTTTTT....TT..PP..WWWWWWWWWWW2..TTTTTTTTTTTTTT",
        "TTTTTTTT....TT..PP................TTTTTTTTTTTTTT",
        "TTTTTTTT..TT....PP....**..TT......TTTTTTTTTTTTTT",
        "TTTTTTTT..TT....PP........TT......TTTTTTTTTTTTTT",
        "TTTTTT........PPPP................TTTTTTTTTTTTTT",
        "TTTTTT........PPPP....,,,,,,......TTTTTTTTTTTTTT",
        "TTTTTT..,,,,..PP......,,,,,,......TTTTTTTTTTTTTT",
        "TTTTTT..,,,,..PP..c...,,,,,,......TTTTTTTTTTTTTT",
        "TTTT..........PP............RRRRRR..TTTTTTTTTTTT",
        "TTTT..........PP............RQQQQR..TTTTTTTTTTTT",
        "TTTT....LLLLLLPPLLLLLLLL....RQQQQR..TTTTTTTTTTTT",
        "TTTT..........PP............RRRRRR..TTTTTTTTTTTT",
        "TTTT..b.......PP......,,,,,,........TTTTTTTTTTTT",
        "TTTT..........PP......,,,,,,........TTTTTTTTTTTT",
        "TTTTTT....TT..PP............**TT..TTTTTTTTTTTTTT",
        "TTTTTT3...TT..PP..............TT..TTTTTTTTTTTTTT",
        "TTTTTTTT......PP..........BBBBBB..TTTTTTTTTTTTTT",
        "TTTTTTTT......PP........BBBBBBBBBBTTTTTTTTTTTTTT",
        "TTTTTTTTTT....PP......BBBBBBBBBBBBBBTTTTTTTTTTTT",
        "TTTTTTTTTT....PP....BBBBBBBBBBBBBBBBTTTTTTTTTTTT",
        "TTTTTTTTTTTT..PP....BBBBBBBBBBBBBBSSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP....BBBBBBBBBBBBB1SSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP..s..BBBBBBBBBBBBSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP......BBBBBBBBBBBSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP......BBBBBBBBBBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP......BBBBBBBBBBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP..TTTTBBBBBBBBBBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP..TTTTBBBBBBBBBBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP..TTTTTTTTBBBBBSSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTT..PP..TTTTTTTTBBBBBSSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTPP..TTTTTTTTTTBBBBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTPP..TTTTTTTTTTBBBBSSSSSSSSSSSSSSSS",
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None), '3': ('FindItem#3', None),
        'a': ('Rewi', 'RIGHT'), 'b': ('PIhaia', 'RIGHT'), 'c': ('PHine', 'LEFT'), 'd': ('PRipeka', 'LEFT'),
        'e': ('PMiro', 'LEFT'), 'f': ('Piri', 'LEFT'), 'g': ('PTui', 'DOWN'), 'u': ('PUenuku', 'RIGHT'),
    },
    sign_text=[('SignNorth', ['ROUTE 2\\n', 'South to AHURIRI$']),
               ('SignSouth', ['ROUTE 2\\n', 'North to TURANGA$'])],
)

if __name__ == '__main__':
    build(SPEC)
