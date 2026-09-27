#!/usr/bin/env python3
"""Te Whanganui-a-Tara / Wellington - the windy capital. Drawn with Mossdeep's tileset (Sept 2026).

The road from the Kapiti coast comes over the hill into town; the Pokemon Center and Mart
on the main street, Manu's gym under the western hills, the domed Beehive in the civic
centre, villas on the slopes, and the harbour in the south-east with Oriental Bay's beach
and the Interislander terminal on the quay (where Tama waits, when the story says so)."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_town import Canvas, build

W, H = 48, 40
c = Canvas(W, H)
c.border()
# the road in from the Kapiti coast (gap x 22-25), down to the main street
c.box(22, 0, 25, 1, '.'); c.road([(23, 0), (23, 15)])
c.box(4, 14, 43, 15, 'P')                       # the main street (Lambton Quay)
c.road([(12, 15), (12, 29)])                    # the hill street
c.box(12, 28, 17, 29, 'P')                      # down to the quay
c.box(26, 22, 29, 35, 'B')                      # Oriental Bay's beach
c.box(18, 21, 25, 29, 'B')                      # the terminal's sand forecourt and quay
# the harbour: open to the east; beach wraps its north-west corner, bush behind;
# at its south end a grass shore behind a blocker tree
c.box(30, 24, 47, 33, 'S')
c.box(30, 18, 47, 23, 'T'); c.box(30, 22, 31, 23, 'B')
c.box(26, 36, 47, 39, 'T'); c.box(28, 34, 29, 35, 'T'); c.box(30, 34, 47, 35, '_')
c.box(44, 2, 47, 17, 'T')
# the western hills: tiered rock with the bush over them
c.box(2, 2, 9, 5, 'T'); c.box(2, 6, 9, 11, 'R')
c.box(2, 18, 7, 33, 'R'); c.box(3, 19, 6, 32, 'Q')
c.box(2, 34, 11, 37, 'T')
# trees and flowers
for x, y in [(18, 2), (28, 2), (14, 18), (20, 18), (22, 34), (18, 36), (20, 36)]:
    c.tree(x, y)
for x, y in [(20, 12), (21, 12), (30, 12), (31, 12), (16, 22), (17, 22), (9, 16), (10, 16), (24, 33), (25, 33),
             (38, 16), (39, 16), (14, 30), (15, 31), (28, 16), (29, 17), (21, 16), (6, 16), (7, 17)]:
    c.at(x, y, '*')

stamps = [('pc', 16, 10, 0), ('mart', 26, 10, 1), ('moss.hall', 20, 23, 2), ('gym', 10, 5, 3),
          ('moss.dome', 34, 5, 4), ('moss.house_st', 8, 21, 5), ('moss.house', 14, 22, 6),
          ('moss.house', 14, 31, 7)]
SPEC = dict(
    folder='Wellington', layout='LAYOUT_WELLINGTON', tileset='gTileset_Mossdeep',
    rows=c.rows(), stamps=stamps, pc_warp=0,
    objects={'GymKid': (13, 10, 'DOWN'), 'BeehiveMan': (36, 13, 'DOWN'), 'WindWoman': (28, 17, None),
             'FerryMan': (24, 29, 'LEFT'), 'CafeKid': (18, 17, None), 'TamakiFerry': (29, 30, 'RIGHT'),
             'TamaStrait': (21, 28, 'UP'), 'KauriStrait': (22, 28, 'UP'), 'Hori': (18, 26, None),
             'PNgahuia': (40, 13, 'LEFT'), 'POtene': (27, 22, 'DOWN'), 'PPaora': (10, 18, 'RIGHT'),
             'PRangimarie': (26, 5, 'LEFT'), 'PTamati': (10, 30, 'RIGHT'), 'WLJOB': (20, 4, 'DOWN'),
             'TRAMPJOB': (10, 13, 'RIGHT')},
    blockers=('GymKid', 'TamaStrait'),
    signs=[(14, 12, 'GymSign'), (31, 12, 'BeehiveSign'), (19, 27, 'FerrySign')],
    hidden={0: (27, 34)},
    conns={'MAP_ROUTE1_KAPITI': 22 - 24},
    script_edits=[('data/maps/TamakiMakaurau/scripts.inc', 'warp MAP_WELLINGTON, 25, 20', 'warp MAP_WELLINGTON, 28, 30')],
)

if __name__ == '__main__':
    c.show(stamps)
    build(SPEC)
