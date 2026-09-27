#!/usr/bin/env python3
"""Will saves from an older build still load? (Sept 2026)

A save stores the player's map as (group, number) and the map's layout as an index into
layouts.json. So new maps must go at the END of their map group and new layouts at the END
of layouts.json: anything inserted mid-list shifts the numbers after it, and a continued
save wakes up in the wrong map, or in the right map drawn with the wrong layout.

  python3 tools_pounamu/mapsynth/check_save_compat.py [GIT_REF]   (default: origin/main)
Exit 1 if the working tree reorders anything the ref already had."""
import json, os, subprocess, sys
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def at(ref, path):
    out = subprocess.run(['git', 'show', f'{ref}:{path}'], cwd=ROOT, capture_output=True, text=True)
    if out.returncode:
        sys.exit(f'cannot read {path} at {ref}: {out.stderr.strip()}')
    return json.loads(out.stdout)


def main():
    ref = sys.argv[1] if len(sys.argv) > 1 else 'origin/main'
    bad = []
    old = [l.get('id') for l in at(ref, 'data/layouts/layouts.json')['layouts']]
    new = [l.get('id') for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts']]
    if new[:len(old)] != old:
        i = next(i for i, (a, b) in enumerate(zip(old, new)) if a != b)
        bad.append(f'layouts.json: index {i} was {old[i]}, now {new[i]} (new layouts go at the end)')
    og = at(ref, 'data/maps/map_groups.json')
    ng = json.load(open(os.path.join(ROOT, 'data/maps/map_groups.json')))
    if ng['group_order'][:len(og['group_order'])] != og['group_order']:
        bad.append('map_groups.json: the group order changed')
    for g in og['group_order']:
        o, n = og.get(g, []), ng.get(g, [])
        if n[:len(o)] != o:
            i = next((i for i, (a, b) in enumerate(zip(o, n)) if a != b), min(len(o), len(n)))
            bad.append(f'{g}: map {i} was {o[i] if i < len(o) else "-"}, now {n[i] if i < len(n) else "-"} '
                       f'(new maps go at the end of the group)')
    if bad:
        print('Saves from', ref, 'would load the wrong map:')
        for b in bad:
            print('  ', b)
        sys.exit(1)
    print(f'save-compatible with {ref}: {len(new) - len(old)} new layout(s) and '
          f'{sum(len(ng.get(g, [])) - len(og.get(g, [])) for g in og["group_order"])} new map(s), all appended')


if __name__ == '__main__':
    main()
