#!/usr/bin/env python3
"""Route 2 Bay: north out of Ahuriri along Hawke Bay - Westshore, the lagoon, the
Tangoio bluffs, Bay View and the Esk Valley vines.

The sea runs up the whole east side, carrying on from Ahuriri's Marine Parade and
on into Route 2 North. The Mob checkpoint sits where the bluffs come down to the
water and the road squeezes onto the beach: two grunts on two cells of sand, bush
on one side, surf on the other. The exile lands just north of it, with the bay on
screen for Lugia.

Drawn with the Mauville tileset (every tile used here is primary) so Ahuriri's
Mauville buildings render correctly across the southern seam."""
from build import build

SPEC = dict(
    folder='Route2Bay', layout='LAYOUT_ROUTE2_BAY', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Mauville',
    conns={'MAP_AHURIRI_CITY': 2, 'MAP_ROUTE2_NORTH': 0},
    rows=[
        #0         1         2         3         4
        #012345678901234567890123456789012345678901234567
        "TTTTTTTTTTTTTTPP..TTTTTTTTTTBBBBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTPP..TTTTTTTTTTBBBBSSSSSSSSSSSSSSSS",
        "TTTTTTTT......PP.s..TTTTTTBBBBBSSSSSSSSSSSSSSSSS",
        "TTTTTTTT......PP....TTTTTTBBBBBSSSSSSSSSSSSSSSSS",
        "TTTTTT..,,,,,.PP.....2TT..BBBBBSSSSSSSOOSSSSSSSS",
        "TTTTTT........PP......TT..BBBBBSSSSSSSOOSSSSSSSS",
        "TTTT....,,,,,.PP....,,,,..BBBBSSSSSSSSSSSSSSSSSS",
        "TTTT..........PP....WWWW..BBBBSSSSSSSSSSSSSSSSSS",
        "TTTT....,,,,,.PP....WWWW..BBBBSSSSSSOOSSSSSSSSSS",
        "TTTT..........PP....WWWW..BBBBSSSSSSOOSSSSSSSSSS",
        "TTTT....,,,,,.PP.a......**BBBBBSSSSSSSSSSSSSSSSS",
        "TTTT..........PP..........BBBBBSSSSSSSSSSSSOOSSS",
        "TTTTTT..,,,,,.PPPPPPPPPPPPBBBBBSSSSSSSSSSSSOOSSS",
        "TTTTTT........PPPPPPPPPPPPBBBBBBBSSSSSSSSSSSSSSS",
        "TTTTTTTT..**........TT....BBBBBBBSSSSSSSSSSSSSSS",
        "TTTTTTTT...*........TT....BBBBBBBSSSSSSSSSSSSSSS",
        "TTTTTTTTTT......TTTTTTTTTTBBBBBBBSSSSSSSSSSSSSSS",
        "TTTTTTTTTT......TTTTTTTTTTBBBBBBBSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTkBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTBBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTgjSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTBBSSSSSSSSSOOSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTBBSSSSSSSSSOOSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTBBSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTT......BBBBBBSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTT..,,..BBBBBBSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTT......PPPPBBBBBBBSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTT..,,,.PPPPBBBBBBBSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTT....,,,,..PP...BBBBBBBSSSSSSSSSSSS",
        "TTTTTTTTTTTTTT..c.,,,,,.PP....BBBBBBSSSSSSSSSOOS",
        "TTTTTTTTTT......PPPPPPPPPP.....BBBBBBSSSSSSSSOOS",
        "TTTTTTTTTT..,,,,PPPPPPPPPP..d..BBBBBBSSSSSSSSSSS",
        "TTTTTTTT...,,,,,PP..............BBBBBBSSSSSSSSSS",
        "TTTTTTTT..,,,,,.PP..WWWWWWW..e..BBBBBBSSSSSSSSSS",
        "TTTTTT..........PP..WWWWWWW......BBBBB1SSSSSSSSS",
        "TTTTTT..f.......PP..WWWWWWW..**..BBBBBBSSSSSSSSS",
        "TTTTTTTT........PP...............BBBBBBBSSSSSSSS",
        "TTTTTTTT...,,,,.PP...............bBBBBBBSSSSSSSS",
        "TTTTTTTTTT.s,,,.PP....h...TTTT....BBBBBBSSSSSSSS",
        "TTTTTTTTTT......PP........TTTT....BBBBBBSSSSSSSS",
        "TTTTTTTT.PPPPPPPPP..TTTTTTTTTTTTTTTTTTTTSSSSSSSS",
        "TTTTTTTT.PPPPPPPPP..TTTTTTTTTTTTTTTTTTTTSSSSSSSS",
        "TTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTTTTTTTTSSSSSSSS",
        "TTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTTTTTTTTTTSSSSSSSS",
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None),
        'a': ('PRewi', 'RIGHT'), 'b': ('PKahu', 'DOWN'), 'c': ('PMoana', 'RIGHT'), 'd': ('PPiri', 'LEFT'),
        'e': ('PMarama', 'DOWN'), 'f': ('PHana', 'RIGHT'),
        'g': ('Grunt1', 'DOWN'), 'j': ('Grunt2', 'DOWN'), 'k': ('TamaIdle', 'UP'),
    },
    hidden={'h': 0},
    sign_text=[('SignNorth', ['ROUTE 2\\n', 'South to AHURIRI$']),
               ('SignSouth', ['ROUTE 2\\n', 'North to WAIROA$'])],
    script_edits=[('data/maps/AhuririGym/scripts.inc', 'warp MAP_ROUTE2_BAY, 7, 6', 'warp MAP_ROUTE2_BAY, 30, 16'),
                  ('data/maps/AhuririGym/scripts.inc', 'warp MAP_ROUTE2_BAY, 14, 20', 'warp MAP_ROUTE2_BAY, 30, 16')],
    # the checkpoint grunts seal the road by design: each side is walked separately
    split_by=('Grunt1', 'Grunt2'),
)

if __name__ == '__main__':
    build(SPEC)
