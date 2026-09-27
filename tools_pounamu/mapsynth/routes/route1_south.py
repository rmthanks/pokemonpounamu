#!/usr/bin/env python3
"""Route 1 (South): Otautahi (north) down SH1 to Otepoti (south) in the snow - the
Canterbury paddocks behind their shelterbelts, a braided river, the coast at
Moeraki with its boulders sitting out in the shallows, and the hills into Otepoti.

The sea runs down the east side between bush at both ends, so it never meets the
map's edge in view. Petalburg tileset (every tile primary)."""
from build import build

SPEC = dict(
    folder='Route1South', layout='LAYOUT_ROUTE1_SOUTH', weather='WEATHER_SNOW',
    tileset='gTileset_Petalburg',
    conns={'MAP_OTAUTAHI': 4, 'MAP_OTEPOTI': 12},
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTT...............PP...............TTTTTTTT",
        "TTTTTTTT.............s.PP...............TTTTTTTT",
        "TTTTTTTT...............PP...............TTTTTTTT",
        "TTTTTTTT...............PP..............3TTTTTTTT",  # 5
        "TTTTTTTT..TTTTTTTTTTTT.PP.....TTTTTTTTTTTTTTTTTT",
        "TTTTTTTT..TTTTTTTTTTTT.PP.....TTTTTTTTTTTTTTTTTT",
        "TTTTTT....,,,,,,,,,,...PP.....,,,,,,,,TTTTTTTTTT",
        "TTTTTT....,,,,,,,,,,...PP.....,,,,,,,,TTTTTTTTTT",
        "TTTTTT....,,,,,,,,,,...PP*....,,,,,,,,TTTTTTTTTT",  # 10
        "TTTTTT....,,,,,,,,,,...PP.....,,,,b,,,TTTTTTTTTT",
        "TTTTTT....,,,,,,,,,,a..PP.....,,,,,,,,TTTTTTTTTT",
        "TTTTTT....,,,,,,,,,,...PP.....,,,,,,,,TTTTTTTTTT",
        "TTTT......TTTTTTTTTTTT.PP.............TTTTTTTTTT",
        "TTTT......TTTTTTTTTTTT.PP.............TTTTTTTTTT",  # 15
        "TTTT...................PP...............TTTTTTTT",
        "TTTT...................PP...............TTTTTTTT",
        "TTTT........d..........PP...............TTTTTTTT",
        "TTTT...................PP...............TTTTTTTT",
        "TTTTTT.................PPPPPPP..........TTTTTTTT",  # 20
        "TTTTTT.................PPPPPPP..........TTTTTTTT",
        "TTTTTT..WWWWWWWWWWWW........PP........TTTTTTTTTT",
        "TTTTTT..WWWWWWWWWWWW........PP........TTTTTTTTTT",
        "TTTTTT..WWWWWWWWWWWW........PP........TTTTTTTTTT",
        "TTTTTT..WWWWWWWWWWWW........PP........TTTTTTTTTT",  # 25
        "TTTTTT..................c...PP........TTTTTTTTTT",
        "TTTTTT......................PP........TTTTTTTTTT",
        "TTTTTTTT....................PP....BBBBBBTTTTTTTT",
        "TTTTTTTT....................PP....BBBBB2TTTTTTTT",
        "TTTTTTTT,,,,,,,,,,....e.....PP....BBBBSSSSSSSSSS",  # 30
        "TTTTTTTT,,,,,,,,,,..........PP....BBBBSSSSSSSSSS",
        "TTTTTTTT,,,,,,,,,,..........PP....BBBBSSSSSSSSSS",
        "TTTTTTTT,,,,,,,,,,..........PP....BBBBSSSSSSSSSS",
        "TTTTTTTTTT..........TT......PP...BBBBBBSSSSSSSSS",
        "TTTTTTTTTT..........TT......PP...BBBBBBSSSSSSSSS",  # 35
        "TTTTTTTTTT......q...........PP...BBBBBBSSSOOSSSS",
        "TTTTTTTTTT..................PP...BBBBBBSSSOOSSSS",
        "TTTTTTTTTTf.................PP....BBBBBBSSSSSSSS",
        "TTTTTTTTTT..................PP....BBBBBBSSSSSSSS",
        "TTTTTTTTTTTT,,,,,,,,,,....g.PP....BBhBBBSSSSSSSS",  # 40
        "TTTTTTTTTTTT,,,,,,,,,,......PP....BBBBBBSSSSSSSS",
        "TTTTTTTTTTTT,,,,,,,,,,......PP...BBBBBSSSSSSSSSS",
        "TTTTTTTTTTTT,,,,,,,,,,......PP...BBBBBSSSSSSSSSS",
        "TTTTTTTTTTTT................PP...BBBBBSSSSSSSSSS",
        "TTTTTTTTTTTT................PP...BBBBBSSSSSSSSSS",  # 45
        "TTTTTTTTTT........i.........PP....BBBBBSSSSSSSSS",
        "TTTTTTTTTT..................PP....BBBBBSSSSSSSSS",
        "TTTTTTTTTT....TT............PP....BBBBBSSSSSOOSS",
        "TTTTTTTTTT....TT............PP....BBBBBSSSSSOOSS",
        "TTTTTTTTTTj.................PP...BBBBBBBSSSSSSSS",  # 50
        "TTTTTTTTTT..................PP...BBBBBBBSSSSSSSS",
        "TTTTTTTTTTTT....**.........PPP...BBmBBBBSSSSSSSS",
        "TTTTTTTTTTTT...............PPP...BBBBBBBSSSSSSSS",
        "TTTTTTTTTTTT............k..PP.....BBBBBBSSSSSSSS",
        "TTTTTTTTTTTT...............PP.....BBBBBBSSSSSSSS",  # 55
        "TTTTTTTTTTTT..,,,,,,,,.....PP.....BBBBBBSSSSSSSS",
        "TTTTTTTTTTTT..,,,,,,,,.....PP.....BBBBB1SSSSSSSS",
        "TTTTTTTTTTTTTT,,,,,,,,.....PP.....BBBBTT________",
        "TTTTTTTTTTTTTT,,,,,,,,.....PP.....BBBBTT________",
        "TTTTTTTTTTTTTT..n..........PP.....BBBBTTTTTTTTTT",  # 60
        "TTTTTTTTTTTTTT.............PP.....BBBBTTTTTTTTTT",
        "TTTTTTTTTTTTTT........TT...PP.,,TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTT........TT...PP.,,TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTT.........PPo,,TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTT.........PP.,,TTTTTTTTTTTTTTTT",  # 65
        "TTTTTTTTTTTTTTTTTT.......s.PP.TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTT.........PP.TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",  # 70
        "TTTTTTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None), '3': ('FindItem#3', None),
        'a': ('Frost', 'LEFT'), 'b': ('Kaia', 'RIGHT'), 'c': ('Pae', None), 'd': ('PFaye', 'DOWN'),
        'e': ('PGil', 'LEFT'), 'f': ('PIke', 'RIGHT'), 'g': ('PJoss', 'LEFT'), 'i': ('PKea', 'DOWN'),
        'k': ('PLevi', 'LEFT'), 'm': ('PMila', 'UP'), 'n': ('PNed', 'RIGHT'), 'o': ('POrla', 'LEFT'),
        'q': ('Suitcase', None),
    },
    hidden={'h': 0, 'j': 1},
    sign_text=[('SignNorth', ['ROUTE 1\\n', 'South to OTEPOTI$']),
               ('SignSouth', ['ROUTE 1\\n', 'North to OTAUTAHI$'])],
)

if __name__ == '__main__':
    build(SPEC)
