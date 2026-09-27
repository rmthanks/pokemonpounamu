"""Pounamu town map (the Fly map): every town, road and landmark on the 28x15 fly grid.

Cells are (column, row) on the region map grid, (0, 0) the top-left cell. A town is one cell;
a road is a list of 4-connected cells running from one town toward the next. The art
(draw.py) and the game data (apply.py) are both built from this file, so moving a town here
moves it everywhere: its orb, its fly point, the name the cursor shows, the player's head."""

# kind: 'city' = red orb (gym towns and the cities), 'town' = blue orb
TOWNS = {
    'TAMAKI':     dict(cell=(16, 2), kind='city', mapsec='MAPSEC_OLDALE_TOWN'),
    'TAURANGA':   dict(cell=(20, 2), kind='city', mapsec='MAPSEC_MAUVILLE_CITY'),
    'OPOTIKI':    dict(cell=(23, 2), kind='town', mapsec='MAPSEC_SLATEPORT_CITY'),
    'TURANGA':    dict(cell=(25, 4), kind='town', mapsec='MAPSEC_DEWFORD_TOWN'),
    'WAIROA':     dict(cell=(24, 5), kind='town', mapsec='MAPSEC_RUSTBORO_CITY'),
    'AHURIRI':    dict(cell=(23, 6), kind='city', mapsec='MAPSEC_PETALBURG_CITY'),
    'HERETAUNGA': dict(cell=(22, 7), kind='city', mapsec='MAPSEC_LITTLEROOT_TOWN'),
    'ROTORUA':    dict(cell=(20, 4), kind='city', mapsec='MAPSEC_LAVARIDGE_TOWN'),
    'TAUPO':      dict(cell=(20, 6), kind='town', mapsec='MAPSEC_FALLARBOR_TOWN'),
    'NGAMOTU':    dict(cell=(16, 7), kind='town', mapsec='MAPSEC_VERDANTURF_TOWN'),
    'WHANGANUI':  dict(cell=(17, 8), kind='town', mapsec='MAPSEC_PACIFIDLOG_TOWN'),
    'WELLINGTON': dict(cell=(17, 10), kind='city', mapsec='MAPSEC_SOOTOPOLIS_CITY'),
    'WAITOHI':    dict(cell=(14, 10), kind='town', mapsec='MAPSEC_EVER_GRANDE_CITY'),
    'WHAKATU':    dict(cell=(12, 10), kind='city', mapsec='MAPSEC_FORTREE_CITY'),
    'OTAUTAHI':   dict(cell=(14, 11), kind='city', mapsec='MAPSEC_LILYCOVE_CITY'),
    'OTEPOTI':    dict(cell=(11, 13), kind='city', mapsec='MAPSEC_MOSSDEEP_CITY'),
}
# landmarks without an orb (the cursor still names them)
PLACES = {
    'TE_MATA':    dict(cell=(23, 8), mapsec='MAPSEC_ROUTE_113'),
    'RUAPEHU':    dict(cell=(19, 8), mapsec='MAPSEC_ROUTE_114'),
    'PIOPIOTAHI': dict(cell=(4, 12), mapsec='MAPSEC_ROUTE_130'),
}
# roads: cells from one end to the other; mapsec = the section the cursor names
ROADS = {
    'ORCHARD_ROAD':  dict(cells=[(23, 7)], mapsec='MAPSEC_ROUTE_101'),            # Heretaunga - Ahuriri
    'ROUTE2_BAY':    dict(cells=[(24, 6)], mapsec='MAPSEC_ROUTE_102'),            # Ahuriri - Wairoa
    'ROUTE2_NORTH':  dict(cells=[(24, 6)], mapsec='MAPSEC_ROUTE_102'),
    'ROUTE2_EAST':   dict(cells=[(24, 4)], mapsec='MAPSEC_ROUTE_102'),            # Wairoa - Turanga
    'ROUTE35_A':     dict(cells=[(25, 3)], mapsec='MAPSEC_ROUTE_103'),            # Turanga - East Cape
    'ROUTE35_B':     dict(cells=[(25, 2), (24, 2)], mapsec='MAPSEC_ROUTE_103'),   # East Cape - Opotiki
    'ROUTE2_BOP':    dict(cells=[(22, 2), (21, 2)], mapsec='MAPSEC_ROUTE_102'),   # Opotiki - Tauranga
    'ROUTE36':       dict(cells=[(20, 3)], mapsec='MAPSEC_ROUTE_104'),            # Tauranga - Rotorua
    'ROUTE5':        dict(cells=[(20, 5)], mapsec='MAPSEC_ROUTE_105'),            # Rotorua - Taupo
    'ROUTE5_RANGES': dict(cells=[(21, 6), (22, 6)], mapsec='MAPSEC_ROUTE_105'),   # Taupo - Ahuriri (sealed)
    'ROUTE1_DESERT': dict(cells=[(20, 7)], mapsec='MAPSEC_ROUTE_106'),            # Taupo - Route 43
    'ROUTE43':       dict(cells=[(19, 7), (18, 7), (17, 7)], mapsec='MAPSEC_ROUTE_107'),  # - Ngamotu
    'ROUTE3':        dict(cells=[(16, 8)], mapsec='MAPSEC_ROUTE_108'),            # Ngamotu - Whanganui
    'ROUTE1_KAPITI': dict(cells=[(17, 9)], mapsec='MAPSEC_ROUTE_109'),            # Whanganui - Wellington
    'ROUTE6':        dict(cells=[(13, 10)], mapsec='MAPSEC_ROUTE_110'),           # Waitohi - Whakatu
    'ROUTE7':        dict(cells=[(12, 11), (13, 11)], mapsec='MAPSEC_ROUTE_111'),           # Whakatu - Otautahi
    'ROUTE1_SOUTH':  dict(cells=[(14, 12), (14, 13), (13, 13), (12, 13)], mapsec='MAPSEC_ROUTE_112'),  # Otautahi - Otepoti
}
# the Interislander across Cook Strait (drawn as a sea lane, named by neither end)
SEA_LANES = [[(15, 10), (16, 10)]]
