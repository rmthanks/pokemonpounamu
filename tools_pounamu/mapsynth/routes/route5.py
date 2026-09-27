#!/usr/bin/env python3
"""Route 5: Rotorua (north) down SH5 to Taupo (south) - steaming ground in the
Whakarewarewa forest, the Kaingaroa pine rows, Hatupatu's rock by the road (the
kuia's sprig job), and the Waikato running down toward Huka Falls. Petalburg
tileset (every tile primary)."""
from build import build

SPEC = dict(
    folder='Route5', layout='LAYOUT_ROUTE5', weather='WEATHER_SUNNY_CLOUDS',
    tileset='gTileset_Petalburg',
    conns={'MAP_ROTORUA': 0, 'MAP_TAUPO': 8},
    rows=[
        #0         1         2         3         4
        #01234567890123456789012345678901234567890123
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTT...............PP.....TT....TTTTTTTTTT",
        "TTTTTT.............s.PP.....TT....TTTTTTTTTT",
        "TTTTTT..WWWWW........PP.....TT....TTTTTTTTTT",
        "TTTTTT..WWWWW........PP.....TT....TTTTTTTTTT",  # 5
        "TTTT....WWWWW........PP.a...........TTTTTTTT",
        "TTTT.................PP.............TTTTTTTT",
        "TTTT......,,,,,,,,,,.PP...WWWWWW....TTTTTTTT",
        "TTTT......,,,,,,,,,,.PP...WWWWWW....TTTTTTTT",
        "TTTT....TT...........PP...WWWWWW....TTTTTTTT",  # 10
        "TTTT....TT...........PP............2TTTTTTTT",
        "TTTTTT..TT...........PP,,,,,,,,,..TTTTTTTTTT",
        "TTTTTT..TT...........PP,,,,,,,,,..TTTTTTTTTT",
        "TTTTTT...............PP.**........TTTTTTTTTT",
        "TTTTTT.b.............PP......g....TTTTTTTTTT",  # 15
        "TTTTTT.........PPPPPPPP...........TTTTTTTTTT",
        "TTTTTT.........PPPPPPPP...........TTTTTTTTTT",
        "TTTTTTTT.......PP.........TT..TT....TTTTTTTT",
        "TTTTTTTT.......PP.........TT..TT....TTTTTTTT",
        "TTTTTTTT,,,,,,.PP.........TT..TT....TTTTTTTT",  # 20
        "TTTTTTTT,,,,,,.PP.........TT..TT....TTTTTTTT",
        "TTTTTTTT,,,,,,.PP.........TT..TT....TTTTTTTT",
        "TTTTTTTT,,,,,,.PP.........TT..TT....TTTTTTTT",
        "TTTTTT.........PP.RRRRRR..TT..TT......TTTTTT",
        "TTTTTT.........PP.RQQQQR..TT..TT......TTTTTT",  # 25
        "TTTTTT....TT...PP.RQQQQR..TTd.TT......TTTTTT",
        "TTTTTT....TT...PPmRRRRRR..TT..TT......TTTTTT",
        "TTTTTT......c..PP.RRRRRR..TT..TT......TTTTTT",
        "TTTTTT.........PP.........TT..TT......TTTTTT",
        "TTTT..,,,,,,...PP.........TT..TT....TTTTTTTT",  # 30
        "TTTT..,,,,,,...PP.........TT..TT....TTTTTTTT",
        "TTTT..,,,,,,...PP.........TT..TT....TTTTTTTT",
        "TTTT..,,,,,,...PP.........TT..TT....TTTTTTTT",
        "TTTT...........PP.**......TT..TT....TTTTTTTT",
        "TTTT...........PP.........TT..TT...1TTTTTTTT",  # 35
        "TTTTTT..f......PP.................TTTTTTTTTT",
        "TTTTTT.........PP.................TTTTTTTTTT",
        "TTTTTT.........PPPPPPPPPP.........TTTTTTTTTT",
        "TTTTTT.........PPPPPPPPPP.........TTTTTTTTTT",
        "TTTTTT......TT....,,,,.PP.**....k.TTTTTTTTTT",  # 40
        "TTTTTT......TT....,,,,.PP.........TTTTTTTTTT",
        "TTTTTTTT...............PP...WWWWWW..TTTTTTTT",
        "TTTTTTTT...............PP...WWWWWW..TTTTTTTT",
        "TTTTTTTT..,,,,,,,,,,e..PP...WWWWWW..TTTTTTTT",
        "TTTTTTTT..,,,,,,,,,,...PP...WWWWWW..TTTTTTTT",  # 45
        "TTTTTTTT..,,,,,,,,,,...PP...WWWWWW..TTTTTTTT",
        "TTTTTTTT..,,,,,,,,,,...PP...WWWWWW..TTTTTTTT",
        "TTTTTT..............TT.PP...WWWWWWTTTTTTTTTT",
        "TTTTTT..............TT.PP...WWWWWWTTTTTTTTTT",
        "TTTTTT.................PP...WWWWWWTTTTTTTTTT",  # 50
        "TTTTTT.................PP...WWWWWWTTTTTTTTTT",
        "TTTTTT..,,,,,,.........PP...WWWWWWTTTTTTTTTT",
        "TTTTTT..,,,,,,....i....PP.........TTTTTTTTTT",
        "TTTTTTTTTT.............PP.,,,,TTTTTTTTTTTTTT",
        "TTTTTTTTTT.............PP.,,,,TTTTTTTTTTTTTT",  # 55
        "TTTTTTTTTT......**.....PP.s...TTTTTTTTTTTTTT",
        "TTTTTTTTTT3............PP.....TTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTT",
    ],
    objects={
        '1': ('FindItem', None), '2': ('FindItem#2', None), '3': ('FindItem#3', None),
        'a': ('Pita', 'LEFT'), 'b': ('Eru', 'RIGHT'), 'c': ('PJake', 'RIGHT'), 'd': ('PJess', 'DOWN'),
        'e': ('PKayla', 'LEFT'), 'f': ('PLiam', 'RIGHT'), 'g': ('PLucas', 'LEFT'), 'i': ('PMaddie', 'DOWN'),
        'k': ('PMason', 'LEFT'), 'm': ('ROCKJOB', 'RIGHT'),
    },
    sign_text=[('SignNorth', ['ROUTE 5\\n', 'South to TAUPO$']),
               ('SignSouth', ['ROUTE 5\\n', 'North to ROTORUA$'])],
)

if __name__ == '__main__':
    build(SPEC)
