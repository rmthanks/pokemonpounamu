#!/usr/bin/env python3
"""Route 43: the Forgotten World Highway - down from the Desert Road through the
Tangarakau gorge (a river in its rock walls), over the saddles, past
Whangamomona's paddocks, to Ngamotu. It rains here.

The Desert Road above draws with Fallarbor; its seam band and every tile here are
primary, so neither side garbles the other. Petalburg tileset."""
from build import build

SPEC = dict(
    folder='Route43', layout='LAYOUT_ROUTE43', weather='WEATHER_RAIN',
    tileset='gTileset_Petalburg',
    conns={'MAP_ROUTE1_DESERT': 2, 'MAP_NGAMOTU': 14},
    rows=[
        #0         1         2         3         4
        #01234567890123456789012345678901234567890123
        "TTTTTTTTTTTTTTTTTTTTPPTTTTTTTTTTTTTTTTTTTTTT",  # 0
        "TTTTTTTTTTTTTTTTTTTTPPTTTTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTT........PP........TTTTTTTTTTTTTT",
        "TTTTTTTTTTTT......s.PP........TTTTTTTTTTTTTT",
        "TTTTTTTT,,,,,,......PP..TT........TTTTTTTTTT",
        "TTTTTTTT,,,,,,......PP..TT........TTTTTTTTTT",  # 5
        "TTTTTTTT,,,,,,..**..PP............TTTTTTTTTT",
        "TTTTTTTT,,,,,,......PP............TTTTTTTTTT",
        "TTTTTTTT............PP..a.........TTTTTTTTTT",
        "TTTTTTTT............PP............TTTTTTTTTT",
        "TTTTTT........PPPPPPPP........TTTT..TTTTTTTT",  # 10
        "TTTTTT........PPPPPPPP........TTTT..TTTTTTTT",
        "TTTTTT........PP..........WWWWTTTT..TTTTTTTT",
        "TTTTTT........PP..........WWWWTTTT..TTTTTTTT",
        "TTTTTT....c...PP..RRRRRR..WWWWTTTT..TTTTTTTT",
        "TTTTTT........PP..RRRRRR..WWWWTTTT..TTTTTTTT",  # 15
        "TTTTTTTT......PP..RQQQQR..WWWWTTTTTTTTTTTTTT",
        "TTTTTTTT......PP..RQQQQR..WWWWTTTTTTTTTTTTTT",
        "TTTTTTTT......PP..RQQQQR..WWWWTTTTTTTTTTTTTT",
        "TTTTTTTT......PP..RQQQQR..WWWWTTTTTTTTTTTTTT",
        "TTTTTTTT,,,,,,PP..RRRRRR..WWWWTTTTTTTTTTTTTT",  # 20
        "TTTTTTTT,,,,,,PP..RRRRRR..WWWWTTTTTTTTTTTTTT",
        "TTTTTTTTTT,,,,PP..........WWWW..TTTTTTTTTTTT",
        "TTTTTTTTTT,,,,PP..........WWWW..TTTTTTTTTTTT",
        "TTTTTTTTTT,,,,PP.b........WWWW..TTTTTTTTTTTT",
        "TTTTTTTTTT,,,,PP..........WWWW..TTTTTTTTTTTT",  # 25
        "TTTTTTTTTT....PPTT........WWWW..TTTTTTTTTTTT",
        "TTTTTTTTTT....PPTT........WWWW..TTTTTTTTTTTT",
        "TTTTTTTT......PP...............d..TTTTTTTTTT",
        "TTTTTTTT......PP..................TTTTTTTTTT",
        "TTTTTTTT....h.PPPPPPPPPPPP........TTTTTTTTTT",  # 30
        "TTTTTTTT......PPPPPPPPPPPP........TTTTTTTTTT",
        "TTTTTTTT..........,,,,,,PP........TTTTTTTTTT",
        "TTTTTTTT..........,,,,,,PP........TTTTTTTTTT",
        "TTTTTT..RRRRRRRRRR,,,,,,PP,,,,,,....TTTTTTTT",
        "TTTTTT..RRRRRRRRRR,,,,,,PP,,,,,,....TTTTTTTT",  # 35
        "TTTTTT..RRQQQQQQRR......PP,,,,,,....TTTTTTTT",
        "TTTTTT..RRQQQQQQRR......PP,,,,,,....TTTTTTTT",
        "TTTTTT..RRRRRRRRRR....e.PP..........TTTTTTTT",
        "TTTTTT..RRRRRRRRRR......PP..........TTTTTTTT",
        "TTTTTTTT............**..PP..LLLLLLTTTTTTTTTT",  # 40
        "TTTTTTTT................PP........TTTTTTTTTT",
        "TTTTTTTTf.....TT........PP........TTTTTTTTTT",
        "TTTTTTTT......TT........PP........TTTTTTTTTT",
        "TTTTTTTT..,,,,,,,,......PP..TT....TTTTTTTTTT",
        "TTTTTTTT..,,,,,,,,......PP..TT....TTTTTTTTTT",  # 45
        "TTTTTT....,,,,,,,,...PPPPP..........TTTTTTTT",
        "TTTTTT....,,,,,,,,...PPPPP..........TTTTTTTT",
        "TTTTTT...............PP.......g.....TTTTTTTT",
        "TTTTTT...............PP.............TTTTTTTT",
        "TTTTTT..........**...PP...,,,,,,....TTTTTTTT",  # 50
        "TTTTTT...............PP...,,,,,,....TTTTTTTT",
        "TTTTTTTTTT..,,,,,,.i.PP...,,,,,,TTTTTTTTTTTT",
        "TTTTTTTTTT..,,,,,,...PP...,,,,,,TTTTTTTTTTTT",
        "TTTTTTTTTT..,,,,,,...PP.........TTTTTTTTTTTT",
        "TTTTTTTTTT..,,,,,,...PP.s.......TTTTTTTTTTTT",  # 55
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
        "TTTTTTTTTTTTTTTTTTTT.PP.TTTTTTTTTTTTTTTTTTTT",
    ],
    objects={
        'a': ('Wai', 'DOWN'), 'b': ('PRiley', 'LEFT'), 'c': ('PRuby', 'RIGHT'), 'd': ('PSam', 'LEFT'),
        'e': ('PSophie', 'DOWN'), 'f': ('PThomas', 'RIGHT'), 'g': ('PTyler', 'LEFT'), 'i': ('PWillow', 'RIGHT'),
    },
    hidden={'h': 0},
    sign_text=[('SignNorth', ['ROUTE 43\\n', 'South to NGAMOTU$']),
               ('SignSouth', ['ROUTE 43\\n', 'North to the DESERT ROAD$'])],
)

if __name__ == '__main__':
    build(SPEC)
