# Pounamu map rebuild — method, rules, and what was done (started Sat 26 Sept 2026)

## Status (morning of Mon 28 Sept 2026)
Every route and every template town has been rebuilt; the whole-region audit is clean on the
Pounamu outdoor maps (the few flags left are listed at the end, with why). Tonight's commits run
from ae70952a (Orchard Road) to 84a9cab8 on main.

- **Routes (16):** Orchard Road, Route 2 Bay, Route 2 North, Route 2 East, Route 35 A and B,
  Route 2 (BoP), Route 36, Route 5, Route 5 Ranges, Desert Road (Rangipo), Route 43, Route 3,
  Route 1 Kapiti, Route 6, Route 7, Route 1 South. Region-shaped, wider, per-region weather,
  vanilla General tiles only (seam-safe against any neighbour).
- **Towns (13):** each drawn with one vanilla town tileset and that town's own buildings:

  | Town | Tileset | Signature |
  |---|---|---|
  | Wairoa | Slateport | the white lighthouse on the river mouth |
  | Turanga | Dewford | sand streets, blue-roof fishing houses, Kapa Haka Hall, harbour jetty |
  | Opotiki | Petalburg | kiwifruit orchard rows, the river wharf |
  | Tauranga | Slateport | Mauao's tiered rock, yachts moored in the harbour |
  | Rotorua | Lavaridge | the lake, the hot spring and sand bath, Pohutu viewpoint |
  | Taupo | Petalburg | Lake Taupo with bays and a walkable shore |
  | Ngamotu | Slateport | the Wind Gallery (Battle Tent dome), Pukekura Park |
  | Whanganui | Petalburg | the awa the length of town, a riverside walk |
  | Wellington | Mossdeep | the domed Beehive (space centre, no rocket), Oriental Bay, the Interislander terminal |
  | Waitohi | Petalburg | the ferry terminal on the quay, the harbour running on into the Sound |
  | Whakatu | Petalburg | flower gardens, Boulder Bank stones, the hill |
  | Otautahi | Petalburg | Cathedral Square's flower ring, the hedged garden flat, the Avon |
  | Otepoti | Ever Grande | the Pokemon League's own building for the League entrance |

- **Tamaki Makaurau** keeps vanilla Lilycove but on its own layout (LAYOUT_TAMAKI_MAKAURAU,
  88x46): bush and water added north and west so the sea border never shows past the museum and
  department store (fix_tamaki_edges.py).

## Game-breaking things found and fixed tonight
- **The Sky Tower could not be entered** (its lobby warp sat on plain grass in Tamaki). The old
  department store is now the tower's door; the villa that had that door got its own house at the
  end of the old west road.
- **One-way rooms:** the six League rooms and three Sky Tower floors (Rustboro Gym's layout) had
  their exits two tiles above the real mats; Te Mata summit's warps were on plain grass. Enter the
  League early and there was no way back. All fixed; check_warps.py now sweeps every warp.
- **Wellington's ferry** warp sat on open sea (never usable) and the gym kid stood in Manu's
  doorway with 'Gym's closed for now' — July's build meant both open. Now: the ferryman keeps the
  terminal until badge 5, Tama holds the ramp until the strait scene, then 'SAILINGS RESUMED'.
- **Names:** Tamaki and its interiors showed 'Waitohi'; Te Mata and Ruapehu showed 'Mt. Pyre'.
  They now have their own region-map sections.
- Heretaunga: the closed Te Mata track trigger covers the grass either side of the path.

## Method (tools_pounamu/mapsynth)
### Routes: routekit.py + routes/<name>.py + routes/build.py
- A route is ASCII rows: `T` tree (2x2 lattice), `.` grass, `,` tall grass, `*` flowers, `P` path,
  `B` beach, `S` sea, `W` pond, `L` ledge, `R`/`Q` rock tiers, `O` sea boulder, `_` grass nobody
  walks (shore lips behind the sea), `s` sign, letters = event markers.
- `render()` draws it by vanilla rules measured off Routes 101-123: tree tops/bottoms and canopy
  rows, pond edges and shore lips, rock tiers, grass coasts (the COAST table) and sand shores,
  beach cells touching land drawn as soft path edges, SURF_MARGIN (outer 7 sea columns solid where
  the sea meets an east/west edge, so the border never shows).
- `build.py` gates: lattice, drawable shapes (lint_shapes), whole trees, seams vs. neighbours,
  exits connect both ways with NPCs standing, no one-way traps, trainers see walkable ground,
  hidden items reachable, story blockers really seal, and what the player sees past each edge
  (context_view.edge_problems). `--write` writes layout, events, connections (both sides).
### Towns: towns/library.py + towns/build_town.py + towns/<town>.py
- **library.py**: every building/decoration is a rectangle of a vanilla map (doors marked);
  plain ground in the rectangle is masked out so the town draws its own. PC, Mart, gym and the
  red-roofed houses are General tiles and fit any town; the rest must match the town's tileset.
- **build_town.py**: ground by routekit, stamps on top, jetties/boat overlays over water,
  warps re-homed in order, heal spot = below the PC door, then gates: stamps don't overlap,
  doors reachable (story blockers allowed), objects/signs/hidden items reachable, trainers see
  something (or are declared talk-to), seams, what we see past our edges, **and what each
  neighbour sees of us** (a route draws our edge with ITS tileset).
- Sweeps: audit_maps.py (whole region), check_connections.py (mirrored), check_warps.py (every
  warp on a warp tile, valid target). QA in the emulator with tools_pounamu/qa (never commit with
  the hooks on: `python3 tools_pounamu/qa/qa_hooks.py off`, `grep -rn POUNAMU_QA src` empty).

## Hard rules learned
1. **Seams:** a connected map is drawn with the *current* map's tileset. Anything within ~8
   columns / 6 rows of a gap, on either side, must be General tiles if the tilesets differ.
2. **Trees are 2x2 on an even lattice**; gaps and offsets even. Tree bottoms over open ground are
   0x1E4/0x1E5, over another tree 0x1DC/0x1DD.
3. **Sea closures:** north end = trees over the sea with beach wrapping the corner (make that sand
   solid if it's a dead end); south end = two solid grass rows (lip + canopy) behind a blocker tree,
   beach beside; P never touches S; two sand cells between land and sea; one shore type per sea cell.
4. **Ponds** need a grass row under every bottom cell (shore lip); inner corners draw fine.
5. **Building roof rows are overlays on grass**: the PC/Mart/houses' top rows show grass behind
   them — on sand, stand them on a grass band (Turanga) or use the tileset's own variants.
6. **Warps fire only on warp tiles** (doors, mats, ladders, stairs). A warp on plain floor is a
   one-way room.
7. Paths 2 thick; rock blocks at least 3x2; tussock never touching tree sides; water has
   collision 0 (walkability must exclude water behaviours).
8. **Petalburg hedge kit** (unchanged): 0x23F/0x24C/0x254 vertical; 0x244/0x245/0x246 box top;
   0x267 0x23D… 0x266 over 0x264 0x245… 0x265 box bottom; 0x24D/0x24E/0x255/0x256 are tree
   bottoms with a hedge rim, only under tree tops.
9. **Grass-country mountains** (primary): tier 1 0x068/0x069/0x06A, 0x070/0x072, 0x071 inside;
   higher tiers 0x06B/0x06C/0x06D, 0x073/0x075; concave feet 0x089/0x074.

## Custom tiles
- Petalburg: the Clock Tower (0x290-0x299, placeholder art, logged in credits).
- Slateport: the lighthouse lantern metatiles 0x246/0x247 now have grass (not paving) in their
  lower layer so the lighthouse can stand in a field (only the lighthouse uses them).

## Left for Ryan / later
- Te Mata o Rongokako sign wording (cultural call).
- The two new functional ferry lines in Wellington (marked for the voice pass).
- Tamaki's Pokemon Center building leads to the Studio Flat (there's no Tamaki PC map);
  its old harbour warp on the shoal is unused.
- Route 5 Ranges ends at the east edge by design (the road home is shut until the post-game).
- Audit flags that are not flaws: Tamaki's vanilla staggered trees and a whole sea boulder at
  its east edge; Taupo Lake Isle (vanilla Southern Island trees); Heretaunga's bottom edge
  (the track trigger stops you first); the Ruapehu/Te Mata maps' vanilla edges.
- Sea encounter tables on the six new seas are placeholders.
