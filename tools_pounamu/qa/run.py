#!/usr/bin/env python3
"""QA driver: python3 qa/run.py TESTNAME  (tests defined in TESTS below).

Each test writes include/qa_spawn.h, rebuilds the POUNAMU_QA ROM, runs the
headless harness and converts screenshots to PNG in qa/out/TESTNAME.
Party: the listed test species first, then a Lv100 Surf-only Kyogre last
(an empty list makes Kyogre the lead, for battle tests).
"""
import os, subprocess, sys
from PIL import Image

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
QA = os.path.dirname(os.path.abspath(__file__))

BOOT = 'run 120\nmash START 8 40\nrun 60\ntap A\nrun 360\nshot 00_spawn\n'

def T(map, x, y, script, hour=12, flags=(), party=('PIDGEY',), deco=None):
    return dict(map=map, x=x, y=y, hour=hour, flags=list(flags), party=list(party), script=BOOT + script, deco=deco)

TESTS = {
    'wellington': T('MAP_WELLINGTON', 20, 14, 'tap UP\nsteps A 18 s\nrun 120\nsteps A 3 t\n'),
    'tramper': T('MAP_WELLINGTON', 10, 4, 'tap UP\nsteps A 6 s\n'),
    'hooks': T('MAP_AHURIRI_CITY', 31, 17, 'tap UP\nsteps A 14 s\nrun 60\nsteps A 3 t\n',
               flags=['FLAG_UNUSED_0x283', 'FLAG_UNUSED_0x287'], party=['BARBOACH']),
    'weta': T('MAP_OPOTIKI_KIWIFRUIT_HOUSE', 7, 3,
              'tap RIGHT\nsteps A 3 s\nmash A 40 25\nrun 200\nsteps A 8 r\n'
              'tap LEFT\nrun 10\ntap LEFT\nrun 30\ntap DOWN\nsteps A 3 p\n',
              flags=['FLAG_UNUSED_0x034'], party=[]),
    'wharf': T('MAP_AHURIRI_CITY', 37, 29, 'tap UP\nsteps A 4 s\nmash A 120 25\nrun 200\nsteps A 6 r\n', party=[]),
    'mauao': T('MAP_TAURANGA', 6, 6, 'tap UP\nsteps A 16 s\nrun 60\nsteps A 3 t\n', hour=7),
    'mauao_noon': T('MAP_TAURANGA', 6, 6, 'tap UP\nsteps A 7 s\n', hour=13),
    'dawn': T('MAP_ROUTE35_A', 12, 11, 'tap UP\nsteps A 12 s\n', hour=7),
    'convoy': T('MAP_ROUTE1_DESERT', 6, 46, 'tap DOWN\nsteps A 3 d\nmash A 40 25\nrun 200\nsteps B 3 dd\n', party=[]),
    'trucker_blocked': T('MAP_ROUTE1_DESERT', 4, 44, 'tap LEFT\nsteps A 8 s\n'),
    'trucker_done': T('MAP_ROUTE1_DESERT', 4, 44, 'tap LEFT\nsteps A 10 s\nrun 60\nsteps A 3 t\n',
                      flags=['TRAINER_FLAGS_START + TRAINER_DESERT_TOLL_DEAN',
                             'TRAINER_FLAGS_START + TRAINER_DESERT_TOLL_KASEY']),
    'student': T('MAP_WELLINGTON_STUDENT_FLAT', 6, 5,
                 'tap UP\nsteps A 10 a\nrun 60\nsteps A 5 b\nrun 60\nsteps A 5 c\n',
                 flags=['FLAG_UNUSED_0x4B1', 'FLAG_UNUSED_0x4B6']),
    'egg': T('MAP_HERETAUNGA_TOWN', 46, 29, 'tap DOWN\nsteps A 16 s\nrun 60\nsteps A 4 t\n'),
    'deco_start': T('MAP_AHURIRI_CITY', 18, 18, 'tap UP\nsteps A 14 s\nrun 60\nsteps A 3 t\n'),
    'deco_painter': T('MAP_AHURIRI_GALLERY', 12, 5, 'tap UP\nsteps A 5 s\nrun 60\nsteps A 3 t\n', deco=1),
    'deco_finish': T('MAP_AHURIRI_CITY', 18, 18, 'tap UP\nsteps A 12 s\nrun 60\nsteps A 3 t\n', deco=4),
    'taupo_south': T('MAP_TAUPO', 13, 21, 'shot a0\nhold RIGHT 20\nrun 20\nshot a1\nhold DOWN 60\nrun 30\nshot a2\nhold DOWN 60\nrun 90\nshot a3\nhold DOWN 120\nrun 60\nshot a4\n'),
    'desert_enter': T('MAP_TAUPO', 23, 20, 'shot a0\nhold DOWN 16\nrun 10\nshot a1\nhold DOWN 16\nrun 10\nshot a2\nhold DOWN 32\nrun 60\nshot a3\nhold DOWN 48\nrun 20\nshot a4\nhold DOWN 64\nrun 20\nshot a5\n'),
    'desert_exit': T('MAP_ROUTE1_DESERT', 18, 72, 'shot b0\nhold DOWN 48\nrun 20\nshot b1\nhold DOWN 48\nrun 60\nshot b2\nhold DOWN 32\nrun 20\nshot b3\n'),
    'desert_mid': T('MAP_ROUTE1_DESERT', 20, 44, 'shot c0\nhold UP 40\nrun 30\nshot c1\n'),
    'life_desert': T('MAP_ROUTE1_DESERT', 14, 29, 'run 240\nshot d0\nhold LEFT 24\nrun 200\nshot d1\nhold DOWN 24\nrun 200\nshot d2\nrun 300\nshot d3\n', party=['MUDBRAY']),
    'life_heretaunga': T('MAP_HERETAUNGA_TOWN', 44, 29, 'run 200\nshot h0\nhold UP 40\nrun 120\nshot h1\nhold LEFT 40\nrun 120\nshot h2\n', party=['COMBEE']),
    'life_bush': T('MAP_ROUTE35_B', 8, 20, 'run 240\nshot e0\nhold DOWN 32\nrun 200\nshot e1\n', party=['HOOTHOOT']),
    'life_rotorua': T('MAP_ROTORUA', 20, 20, 'run 240\nshot r0\nhold LEFT 32\nrun 120\nshot r1\n', party=['SLUGMA']),
    'life_south': T('MAP_ROUTE1_SOUTH', 8, 30, 'run 240\nshot s0\nhold DOWN 32\nrun 200\nshot s1\n', party=['SNORUNT']),
    'life_route5': T('MAP_ROUTE5_POUNAMU', 8, 30, 'run 240\nshot f0\nhold DOWN 32\nrun 200\nshot f1\n', party=['SLUGMA']),
    'ht_pc': T('MAP_HERETAUNGA_TOWN', 22, 13, 'run 200\nshot a\n'),
    'ht_ne': T('MAP_HERETAUNGA_TOWN', 50, 15, 'run 200\nshot a\n'),
    'ht_pond': T('MAP_HERETAUNGA_TOWN', 9, 27, 'run 200\nshot a\n'),
    'ht_garden': T('MAP_HERETAUNGA_TOWN', 21, 26, 'run 200\nshot a\n'),
    'ht_orchard': T('MAP_HERETAUNGA_TOWN', 44, 23, 'run 200\nshot a\n'),
    'ht_north': T('MAP_HERETAUNGA_TOWN', 29, 3, 'run 200\nshot a\n'),
    'ex_r35a': T('MAP_ROUTE35_A', 7, 3, 'run 200\nshot a\n'),
    'ex_ahuriri': T('MAP_AHURIRI_CITY', 8, 33, 'run 200\nshot a\n'),
    'ex_route36': T('MAP_ROUTE36', 2, 8, 'run 200\nshot a\n'),
    'ex_wellington': T('MAP_WELLINGTON', 7, 3, 'run 200\nshot a\n'),
    'ex_taupo_s': T('MAP_TAUPO', 24, 20, 'run 120\nshot a\nhold DOWN 48\nrun 60\nshot b\nhold DOWN 64\nrun 60\nshot c\n'),
    'durie': T('MAP_WHANGANUI', 16, 3, 'tap UP\nsteps A 12 s\nrun 60\nsteps A 4 t\n'),
}

def main(name):
    t = TESTS[name]
    party = ', '.join('SPECIES_' + p for p in t['party']) or 'SPECIES_NONE'
    flags = ', '.join(t['flags']) or '0'
    open(f'{REPO}/include/qa_spawn.h', 'w').write(
        f'#define QA_MAP {t["map"]}\n#define QA_X {t["x"]}\n#define QA_Y {t["y"]}\n'
        f'#define QA_HOUR {t["hour"]}\n#define QA_PARTY {{ {party} }}\n#define QA_FLAGS {{ {flags} }}\n'
        + (f'#define QA_DECO {t["deco"]}\n' if t.get('deco') is not None else ''))
    r = subprocess.run('make modern -j2', shell=True, cwd=REPO, capture_output=True, text=True)
    if r.returncode:
        print(r.stdout[-3000:], r.stderr[-3000:]); sys.exit(1)
    out = f'{QA}/out/{name}'
    os.makedirs(out, exist_ok=True)
    for f in os.listdir(out):
        os.remove(os.path.join(out, f))
    open(f'{QA}/{name}.cmd', 'w').write(t['script'])
    subprocess.run([f'{QA}/harness', f'{REPO}/pokeemerald.gba', f'{QA}/{name}.cmd', out, '1790000000'], check=True)
    for f in sorted(os.listdir(out)):
        if f.endswith('.ppm'):
            im = Image.open(os.path.join(out, f))
            im.resize((im.width * 2, im.height * 2), Image.NEAREST).save(os.path.join(out, f[:-4] + '.png'))
            os.remove(os.path.join(out, f))
    print('\n'.join(sorted(os.listdir(out))))

if __name__ == '__main__':
    main(sys.argv[1])
