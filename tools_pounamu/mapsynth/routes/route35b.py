#!/usr/bin/env python3
"""Route 35 (B): round the East Cape to Opotiki - Hicks Bay and Te Kaha under the
pohutukawa, then inland through the bush to the Opotiki road. Rain comes in off
the sea here.

The Pacific carries on from Route 35 (A) (same columns, offset 0) and closes under
the bush at the top of the coast, so the sea never meets the map's edge where the
player can see it. Petalburg tileset (every tile primary)."""
from build import build

SPEC = dict(
    folder='Route35B', layout='LAYOUT_ROUTE35_B', weather='WEATHER_RAIN',
    tileset='gTileset_Petalburg',
    conns={'MAP_ROUTE35_A': 0, 'MAP_OPOTIKI': 10},
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT.........PP.......TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT.......s.PP.......TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT..,,,,,,.PP.,,,,..TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT..,,,,,,.PP.,,,,..TTTTTTTTTTTTTTTTTT",  # 5
        "TTTTTTTTTT....,,,,,,.PP.,,,,..TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT....,,,,,,.PP.,,,,..TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT......**...PP.......TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTT..d........PP.......TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT.........PP.....TTTTBBBBBBBBTTTTTTTT",  # 10
        "TTTTTTTTTTTT.........PP.....TTTTBBBBBBB2TTTTTTTT",
        "TTTTTTTTTTTT.,,,,,,..PP.........BBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTT.,,,,,,..PP.........BBBBBBSSSSSSSSSS",
        "TTTTTTTTTT...,,,,,,..PP.TT......BBBBBBSSSSSSSSSS",
        "TTTTTTTTTT...,,,,,,..PP.TT......BBBBBBSSSSSSSSSS",  # 15
        "TTTTTTTTTT..........ePP.......BBBBBBSSSSSSSSSSSS",
        "TTTTTTTTTT...........PP.......BBBBBBSSSSSSSSSSSS",
        "TTTTTTTTTTTT.........PP.....TTBBBBBBSSSSSSSSSSSS",
        "TTTTTTTTTTTT.........PP.....TTBBBBBBSSSSSSSSSSSS",
        "TTTTTTTTTTTT..RRRRRR.PP.......BBBBBBSSSSSSSSSSSS",  # 20
        "TTTTTTTTTTTT..RRRRRR.PP......cBBBBBBSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTRRRRRR.PP........BBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTTTTRRRRRR.PP........BBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTTTT.......PP,,,,,...BBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTTTT.......PP,,,,,...BBBBBBBSSSSSSSSSS",  # 25
        "TTTTTTTTTTTT.........PP,,,,,...BBBaBBBSSSSSSSSSS",
        "TTTTTTTTTTTT.g.......PP,,,,,...BBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTT.........PP......BBBBBBSSSSSSSSSSSSS",
        "TTTTTTTTTTTT.........PP......BBBBBBSSSSSSSSSSSSS",
        "TTTTTTTTTT...WWWWWW..PP......BBBBBBSSSSSSSSSSSSS",  # 30
        "TTTTTTTTTT...WWWWWW..PP......BBBBBBSSSSSSSSSSSSS",
        "TTTTTTTTTT...WWWWWW..PP......BBBBBBSSSSSSSSSSSSS",
        "TTTTTTTTTT...........Pb......BBBBBBSSSSSSSSSSSSS",
        "TTTTTTTTTTTT.........PP...TT...BBBBB3SSSSSSSSSSS",
        "TTTTTTTTTTTT.........PP...TT...BBBBBBSSSSSSSSSSS",  # 35
        "TTTTTTTTTTTT,,,,,,,,.PP........BBBBBBSSSSSSSSSSS",
        "TTTTTTTTTTTT,,,,,,,,.PP........BBBBBBSSSSSSSSSSS",
        "TTTTTTTTTTTTTT,,,,,,.PP...**i..BBBBBBSSSSSSSSSSS",
        "TTTTTTTTTTTTTT,,,,,,.PP........BBBBBBSSSSSSSSSSS",
        "TTTTTTTTTTTTTT.......PP.........BBBBBBBSSSSSSSSS",  # 40
        "TTTTTTTTTTTTTT.......PP.........BBBBBBBSSSSSSSSS",
        "TTTTTTTTTTTTTTTT.....PPPPPPPPPPPBBBBBBBSSSSSSSSS",
        "TTTTTTTTTTTTTTTT.....PPPPPPPPPPPBBBBBBBSSSSSSSSS",
        "TTTTTTTTTTTTTTTT..............PPBBBBBBBSSSSSSSSS",
        "TTTTTTTTTTTTTTTT..............PPBBBBBBBSSSSSSSSS",  # 45
        "TTTTTTTTTTTTTTTT..............PPBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTTTTTT..............PPBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTTTT..........,,,,,.PfBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTTTT..........,,,,,.PPBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTTTTTT....**..,,,,,.PPBBBBBBSSSSSSSSSS",  # 50
        "TTTTTTTTTTTTTTTT........,,,,,.PPBBBBBBSSSSSSSSSS",
        "TTTTTTTTTTTTTTTT........k.....PPBBBBBBB1SSSSSSSS",
        "TTTTTTTTTTTTTTTT..............PPBBBBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTT,,,,......PPBBBBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTT,,,,....s.PPBBBBBBBBSSSSSSSS",  # 55
        "TTTTTTTTTTTTTTTTTTTT......TT..PP..BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTT......TT..PP..BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTT..PP..BBBBBBSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTT..PP..BBBBBBSSSSSSSS",
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None), '3': ('FindItem#3', None),
        'a': ('Manaia', 'DOWN'), 'b': ('Aroha', 'LEFT'), 'c': ('PHuhana', 'RIGHT'), 'd': ('POriwa', 'RIGHT'),
        'e': ('PPeti', 'LEFT'), 'f': ('PRuta', 'RIGHT'), 'g': ('PMeri', 'RIGHT'), 'i': ('PRiria', 'LEFT'),
        'k': ('PKuini', 'DOWN'),
    },
    sign_text=[('SignNorth', ['ROUTE 35\\n', 'South to EAST CAPE$']),
               ('SignSouth', ['ROUTE 35\\n', 'North to OPOTIKI$'])],
)

if __name__ == '__main__':
    build(SPEC)
