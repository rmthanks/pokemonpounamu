#!/usr/bin/env python3
"""Orchard Road: Heretaunga (south) to Ahuriri (north) across the plains.
Napier's edge in the north, a terrace with an irrigation pond, then orchard rows
and vineyard lines down into Heretaunga."""
from build import build

SPEC = dict(
    folder='OrchardRoad', layout='LAYOUT_ORCHARD_ROAD', weather='WEATHER_SUNNY_CLOUDS',
    conns={'MAP_AHURIRI_CITY': 8, 'MAP_HERETAUNGA_TOWN': -14},
    # the two path cells on the south edge match Heretaunga's path across the seam
    fixed={(14, 47): 0x3120, (15, 47): 0x3122},
    rows=[
        #0         1         2         3
        #01234567890123456789012345678901
        "TTTTTTTTTTTTTT....TTTTTTTTTTTTTT",  # 0  to Ahuriri
        "TTTTTTTTTTTTTT....TTTTTTTTTTTTTT",
        "TTTTTTTTTTTT...PP...TTTTTTTTTTTT",
        "TTTTTTTTTTTT.s.PP...TTTTTTTTTTTT",
        "TTTTTTTT.......PP.......TTTTTTTT",
        "TTTTTTTT..*....PP.a..**.TTTTTTTT",  # 5
        "TTTTTT...,,,,..PP.....*...TTTTTT",
        "TTTTTT..,,,,,,.PP.........TTTTTT",
        "TTTT....,,,,,,.PP...TT....TTTTTT",
        "TTTT.....,,,,..PP...TT....TTTTTT",
        "TTTT..TT.......PPPPPPP.b..TTTTTT",  # 10
        "TTTT..TT.......PPPPPPP....TTTTTT",
        "TTTT....ppppp.......PP......TTTT",
        "TTTT..*.ppppp......cPP.WWWWWTTTT",
        "TTTT................PP.WWWWWTTTT",
        "TTTTLLLLLLLLLLLLL...PP.WWWWWTTTT",  # 15
        "TTTT................PP.WWWWWTTTT",
        "TTTT.,,,,,,,,,,.....PP.....2TTTT",
        "TTTT..,,,,,,,,,.....PP..TT..TTTT",
        "TTTT..,,,,,,,,....d.PP..TT..TTTT",
        "TTTT...,,,,,........PP..,,,,TTTT",  # 20
        "TTTT................PP..,,,.TTTT",
        "TTTT........PPPPPPPPPP..TT..TTTT",
        "TTTT........PPPPPPPPPP..TT..TTTT",
        "TTTTTT..TT..PP..,,,,,,,,,,..TTTT",
        "TTTTTT..TTe.PP..............TTTT",  # 25
        "TTTT........PP..,,,,,,,,,,..TTTT",
        "TTTT........PP.f............TTTT",
        "TTTTTT..TT..PP..,,,,,,,,,,..TTTT",
        "TTTTTT..TT..PP..............TTTT",
        "TTTT........PP..,,,,,,,,,,..TTTT",  # 30
        "TTTT......g.PP..............TTTT",
        "TTTTTT..TT..PP..,,,,,,,,,,..TTTT",
        "TTTTTT..TT..PP..............TTTT",
        "TTTT........PPPP............TTTT",
        "TTTT........PPPP............TTTT",  # 35
        "TTTT..**......PP..,,,,,,....TTTT",
        "TTTT...*......PP.h,,,,,,,...TTTT",
        "TTTTTT..TT....PP...,,,,,,...TTTT",
        "TTTTTT..TT....PP....,,,,...1TTTT",
        "TTTTTTTT......PP........TTTTTTTT",  # 40
        "TTTTTTTT......PP........TTTTTTTT",
        "TTTTTTTTTT....PP....TTTTTTTTTTTT",
        "TTTTTTTTTT....PP....TTTTTTTTTTTT",
        "TTTTTTTTTTTT.sPP..TTTTTTTTTTTTTT",
        "TTTTTTTTTTTT..PP..TTTTTTTTTTTTTT",  # 45
        "TTTTTTTTTTTTTTPPTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTPPTTTTTTTTTTTTTTTT",  # 47 to Heretaunga
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None),
        'a': ('Anaru', 'LEFT'), 'b': ('Mereana', 'LEFT'), 'c': ('Wiremu', 'RIGHT'),
        'd': ('PWiremu', 'RIGHT'), 'e': ('PAnahera', 'RIGHT'), 'f': ('PMere', 'LEFT'),
        'g': ('PAroha', 'RIGHT'), 'h': ('PTane', 'LEFT'),
    },
    sign_text=[('SignNorth', ['ORCHARD ROAD\\n', 'South to HERETAUNGA$']),
               ('SignSouth', ['ORCHARD ROAD\\n', 'North to AHURIRI$'])],
)

if __name__ == '__main__':
    build(SPEC)
