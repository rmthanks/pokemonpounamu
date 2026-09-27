#!/usr/bin/env python3
"""Route 7: Lewis Pass - east out of Whakatu, down the Maruia valley through the
beech forest, past the hot springs, and on south to Otautahi. Rain.

The cornering scene keeps its shape: the road runs through a clearing hemmed in by
beech, and the two trigger rows (58 and 63) cover every cell the player can stand
on, with Tawhai and Tama waiting between them. The builder rewrites those rows
across the new clearing (coord_rows). Petalburg tileset (every tile primary)."""
from build import build

SPEC = dict(
    folder='Route7', layout='LAYOUT_ROUTE7', weather='WEATHER_RAIN',
    tileset='gTileset_Petalburg',
    conns={'MAP_WHAKATU': 0, 'MAP_OTAUTAHI': 2},
    rows=[
        #0         1         2         3         4
        #01234567890123456789012345678901234567890123
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTT2.................RRRRRRRRRR......TTTT",
        "TTTTTT..................RRRRRRRRRR......TTTT",
        "TTTTTT..q...............RRQQQQQQRR......TTTT",
        "TTTTTT..................RRQQQQQQRR......TTTT",  # 5
        "TTTTTT,,,,,,............RRQQQQQQRR......TTTT",
        "TTTTTT,,,,,,............RRQQQQQQRR......TTTT",
        "TTTTTT,,,,,,............RRRRRRRRRR....TTTTTT",
        "TTTTTT,,,,,,............RRRRRRRRRR....TTTTTT",
        "TTTT..................................TTTTTT",  # 10
        "TTTT.s................................TTTTTT",
        "PPPPPPPPPPPPPPPPPP...............r....TTTTTT",
        "PPPPPPPPPPPPPPPPPP....................TTTTTT",
        "TT........a.....PP....................TTTTTT",
        "TT..............PP....................TTTTTT",  # 15
        "TTTTTT..........PP**......WWWWWW....TTTTTTTT",
        "TTTTTT..........PP........WWWWWW....TTTTTTTT",
        "TTTTTT..TT......PP........WWWWWW....TTTTTTTT",
        "TTTTTT..TT......PP........WWWWWW....TTTTTTTT",
        "TTTTTT..,,,,,,..PP..c.....WWWWWW....TTTTTTTT",  # 20
        "TTTTTT..,,,,,,..PP........WWWWWW....TTTTTTTT",
        "TTTTTTTT,,,,,,..PP........WWWWWW......TTTTTT",
        "TTTTTTTT,,,,,,..PP........WWWWWW......TTTTTT",
        "TTTTTTTT......b.PP........WWWWWW......TTTTTT",
        "TTTTTTTT........PP........WWWWWW......TTTTTT",  # 25
        "TTTTTTTT........PPPPPPP...WWWWWW......TTTTTT",
        "TTTTTTTT........PPPPPPP...WWWWWW......TTTTTT",
        "TTTTTT....TT.........PP...WWWWWW......TTTTTT",
        "TTTTTT....TT.........PP...WWWWWW......TTTTTT",
        "TTTTTT...............PPh..WWWWWW....TTTTTTTT",  # 30
        "TTTTTT...............PP...WWWWWW....TTTTTTTT",
        "TTTTTT..d............PP.............TTTTTTTT",
        "TTTTTT...............PP.............TTTTTTTT",
        "TTTT..............,,.PP.,,,,,,....o.TTTTTTTT",
        "TTTT..............,,.PP.,,,,,,......TTTTTTTT",  # 35
        "TTTT....WWWWW.....,,.PP.,,,,,,......TTTTTTTT",
        "TTTT....WWWWW.....,,.PP.,,,,,,......TTTTTTTT",
        "TTTT....WWWWW........PP..........e....TTTTTT",
        "TTTT3................PP...............TTTTTT",
        "TTTTTT........**.....PP.TT............TTTTTT",  # 40
        "TTTTTT...............PP.TT............TTTTTT",
        "TTTTTT,,,,,,.........PP...............TTTTTT",
        "TTTTTT,,,,,,.........PP...............TTTTTT",
        "TTTTTT,,,,,,......i..PP.......TT......TTTTTT",
        "TTTTTT,,,,,,.........PP.......TT......TTTTTT",  # 45
        "TTTTTTTT....TT.......PP.............TTTTTTTT",
        "TTTTTTTT....TT.......PP.............TTTTTTTT",
        "TTTTTTTT..f..........PP.,,,,,,......TTTTTTTT",
        "TTTTTTTT.............PP.,,,,,,......TTTTTTTT",
        "TTTTTTTT.............PP.,,,,,,...g..TTTTTTTT",  # 50
        "TTTTTTTT.............PP.,,,,,,.....1TTTTTTTT",
        "TTTTTTTTTT....j......PP...........TTTTTTTTTT",
        "TTTTTTTTTT...........PP...........TTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",  # 55
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....vP.....TTTTTTTTTTTTTTTT",  # 60
        "TTTTTTTTTTTTTTTT.....wP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",  # 65
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTT.....PP.....TTTTTTTTTTTTTTTT",
        "TTTTTTTTTT,,k,,,.....PP.u.,,,,,,TTTTTTTTTTTT",
        "TTTTTTTTTT,,,,,,.....PP...,,l,,,TTTTTTTTTTTT",
        "TTTTTTTTTT,,,,n,.....PP...m,,,,,TTTTTTTTTTTT",  # 70
        "TTTTTTTTTT,,,,,,.....PP...,,,,,,TTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PPsTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",  # 75
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None), '3': ('FindItem#3', None),
        'a': ('Kae', 'LEFT'), 'b': ('Rangi', 'RIGHT'), 'c': ('PVince', 'DOWN'), 'd': ('PWade', 'RIGHT'),
        'e': ('PXimena', 'LEFT'), 'f': ('PYvette', 'DOWN'), 'g': ('PZach', 'LEFT'), 'i': ('PAki', 'DOWN'),
        'k': ('PBex', 'RIGHT'), 'm': ('PCal', 'DOWN'), 'n': ('PDee', 'RIGHT'), 'o': ('PEli', 'LEFT'),
        'q': ('R7JOB', 'DOWN'), 'u': ('TrackMaster', 'LEFT'),
        # the cornering scene (both hidden once it has played)
        'v': ('Cornered', 'DOWN'), 'w': ('Cornered#2', 'UP'),
    },
    hidden={'h': 0, 'j': 1, 'l': 2, 'r': 3},
    coord_rows={58: 58, 63: 63},
    sign_text=[('SignWest', ['ROUTE 7\\n', 'South to OTAUTAHI$']),
               ('SignSouth', ['ROUTE 7\\n', 'North to WHAKATU$'])],
)

if __name__ == '__main__':
    build(SPEC)
