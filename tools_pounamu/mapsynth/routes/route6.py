#!/usr/bin/env python3
"""Route 6: Waitohi (north) over to Whakatu (south) - Queen Charlotte Sound runs
on out of Waitohi's harbour, then the road climbs through the bush past Havelock
and the Pelorus river, down the Rai valley's paddocks to Whakatu.

The Sound carries on across the seam from Waitohi's water (same pond tiles, no
edge drawn at the seam) and ends in a sandy cove. Petalburg tileset (every tile
primary)."""
from build import build

SPEC = dict(
    folder='Route6', layout='LAYOUT_ROUTE6', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_WAITOHI': 10, 'MAP_WHAKATU': 8},
    pond_open_top=list(range(24, 30)),
    rows=[
        #0         1         2         3         4
        #01234567890123456789012345678901234567890123
        "TTTTTTTTTTTTTTTT.PP.TTTTWWWWWWTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTT.PP.TTTTWWWWWWTTTTTTTTTTTTTT",
        "TTTTTTTTTT.......PP...TTWWWWWWTTTT..TTTTTTTT",
        "TTTTTTTTTT.....s.PP...TTWWWWWWTTTT..TTTTTTTT",
        "TTTTTTTTTT.......PP...TTWWWWWWTTTT..TTTTTTTT",
        "TTTTTTTTTT.......PP...TTWWWWWWTTTT..TTTTTTTT",  # 5
        "TTTTTTTT.........PP...TTWWWWWWTTTT..TTTTTTTT",
        "TTTTTTTT.........PP...TTWWWWWWTTTT..TTTTTTTT",
        "TTTTTTTT..,,,,,,.PP.a.TTWWWWWWTTTT....TTTTTT",
        "TTTTTTTT..,,,,,,.PP...TTWWWWWWTTTT....TTTTTT",
        "TTTTTTTT..,,,,,,.PP...TTWWWWWWTTTT....TTTTTT",  # 10
        "TTTTTTTT..,,,,,,.PP...TTWWWWWWTTTT....TTTTTT",
        "TTTTTT...........PP...TTWWWWWWTTTT....TTTTTT",
        "TTTTTT...........PP...TTWWWWWWTTTT...2TTTTTT",
        "TTTTTT........b..PP.................TTTTTTTT",
        "TTTTTT...........PP.................TTTTTTTT",  # 15
        "TTTTTT........**.PP.................TTTTTTTT",
        "TTTTTT...........PP...........h.....TTTTTTTT",
        "TTTTTTTT.........PP.................TTTTTTTT",
        "TTTTTTTT.........PP.................TTTTTTTT",
        "TTTTTTTT....TT...PP.**....c.......TTTTTTTTTT",  # 20
        "TTTTTTTT....TT...PP...............TTTTTTTTTT",
        "TTTTTTTT.........PP.........TT....TTTTTTTTTT",
        "TTTTTTTT.........PP.........TT....TTTTTTTTTT",
        "TTTTTT..,,,,,,...PP...............TTTTTTTTTT",
        "TTTTTT..,,,,,,...PP...............TTTTTTTTTT",  # 25
        "TTTTTT..,,,,,,...PP..d....,,,,,,....TTTTTTTT",
        "TTTTTT..,,,,,,...PP.......,,,,,,....TTTTTTTT",
        "TTTTTT...........PP.......,,,,,,....TTTTTTTT",
        "TTTTTT...........PP.......,,,,,,....TTTTTTTT",
        "TTTTTTTT.........PPPPPPPP...........TTTTTTTT",  # 30
        "TTTTTTTT.........PPPPPPPP...........TTTTTTTT",
        "TTTTTTTT....e..........PP.............TTTTTT",
        "TTTTTTTT...............PP.............TTTTTT",
        "TTTTTTTT..TT...........PP.............TTTTTT",
        "TTTTTTTT..TT...........PP.............TTTTTT",  # 35
        "TTTTTT.................PP.WWWWWW......TTTTTT",
        "TTTTTT.................PP.WWWWWW.....1TTTTTT",
        "TTTTTT............g....PP.WWWWWW....TTTTTTTT",
        "TTTTTT.................PP.WWWWWW....TTTTTTTT",
        "TTTTTT......,,,,,,,,...PP.WWWWWW....TTTTTTTT",  # 40
        "TTTTTT......,,,,,,,,...PP.WWWWWW....TTTTTTTT",
        "TTTTTTTT....,,,,,,,,...PP...........TTTTTTTT",
        "TTTTTTTT....,,,,,,,,...PP...........TTTTTTTT",
        "TTTTTTTT.j.............PP...f.....TTTTTTTTTT",
        "TTTTTTTT...............PP.........TTTTTTTTTT",  # 45
        "TTTTTTTT...............PP.....TT..TTTTTTTTTT",
        "TTTTTTTT...............PP.....TT..TTTTTTTTTT",
        "TTTTTTTTTT..i.......**.PP.........TTTTTTTTTT",
        "TTTTTTTTTT.............PP.........TTTTTTTTTT",
        "TTTTTTTTTT.............PP.,,,,,,TTTTTTTTTTTT",  # 50
        "TTTTTTTTTT.............PP.,,,,,,TTTTTTTTTTTT",
        "TTTTTTTTTT....TT.......PP.,,,,,,TTTTTTTTTTTT",
        "TTTTTTTTTT3...TT.......PP.,,,,,,TTTTTTTTTTTT",
        "TTTTTTTTTTTT...........PP.......TTTTTTTTTTTT",
        "TTTTTTTTTTTT...........PP.......TTTTTTTTTTTT",  # 55
        "TTTTTTTTTTTT,,,,.......PP...k.TTTTTTTTTTTTTT",
        "TTTTTTTTTTTT,,,,.......PP.....TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.......PP.s...TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.......PP.....TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.......PP.....TTTTTTTTTTTTTT",  # 60
        "TTTTTTTTTTTTTTTT.......PP.....TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None), '3': ('FindItem#3', None),
        'a': ('Sol', 'LEFT'), 'b': ('Nova', 'RIGHT'), 'c': ('PNina', 'DOWN'), 'd': ('POtis', 'LEFT'),
        'e': ('PPippa', 'RIGHT'), 'f': ('PReid', 'LEFT'), 'g': ('PStella', 'DOWN'), 'i': ('PTroy', 'RIGHT'),
        'k': ('PUna', 'LEFT'),
    },
    hidden={'h': 0, 'j': 1},
    sign_text=[('SignNorth', ['ROUTE 6\\n', 'South to WHAKATU$']),
               ('SignSouth', ['ROUTE 6\\n', 'North to WAITOHI$'])],
)

if __name__ == '__main__':
    build(SPEC)
