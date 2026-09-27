# Pokémon Pounamu — Asset Credits

Pounamu only uses assets that are free to use with credit (or built by us). This file is the
running ledger — **every imported asset gets a line here the moment it enters the repo.**
(Separate from CREDITS.md, which is pokeemerald-expansion's own contributor list.)

## Base

- **pokeemerald-expansion 1.16.2** — RHH (Rom Hacking Hideout) and all pokeemerald/pret contributors (see CREDITS.md).

## Graphics packs in use / queued

### ROM Hacking Sprites Pack — LibertyTwins (PokéCommunity, updated 2026)
Free to use with credit. Modification allowed with credit. The pack is organised by folder so each
asset's artist can be credited individually — **when an asset from this pack is imported, add the
specific artist + folder to "Imported so far" below.**

Known contributing artists (per the thread; confirm per-folder on import):
- Battle backgrounds: princess-phoenix, carchagui, aveontrainer, WesleyFG, kWharever, worldslayer608, LibertyTwins
- Other folders (badges, bag backgrounds, battle UI, HP bars, item sprites, opening, overworld
  sprites, Pokémon sprites, text boxes, tilesets, town map, trainer sprites, type icons): credit
  per the pack's own Credits folder when imported. Tileset folder includes work from Adventure
  Red / Ikarus' Lost Property lineages — verify per-tile credits before shipping.

**Imported so far: (none yet — assets pending upload to the repo)**

### Magiscarf tilesets (planned)
- Magiscarf — public tilesets, **CC BY-NC-SA 3.0** (non-commercial, share-alike, credit required).
- Not yet imported.

## Rules we follow

1. **No assets lifted from other ROM hacks** — only released-for-use packs, open licences, or our own work.
2. **Credit per artist, per asset**, not just per pack.
3. **No generative-AI assets in shipped content** (PokéCommunity prohibits AI content in fan games;
   AI stays private-reference/concept only).
4. When in doubt about a licence, don't import it.

## Title & credits backdrops (14 July 2026)
- Title screen backdrop: pixel-art render of Ryan's own photo of Te Mata Peak at dawn
  (photo by Ryan; pixel-art conversion generated with Grok).
- Credits "THE END" backdrop: pixel-art render of Te Mata o Rongokako from the west at
  sunset (source painting supplied by Ryan; pixel-art conversion generated with Grok).
- NOTE: both conversions are AI-generated images. Fine for personal/playtest builds, but
  PokeCommunity prohibits AI-generated assets in released fan games - replace with
  hand-made art (or hand-pixel the photos) before any public release there.

## Heretaunga Clock Tower (26 Sept 2026)
- Metatiles 0x290-0x299 in the Petalburg tileset (2x5, the tower in Heretaunga's square):
  PLACEHOLDER pixel art drawn in code by Claude (tools_pounamu/mapsynth/make_clock_tower.py),
  after the real 1935 Sidney Chaplin tower. It is AI-made, so rule 3 applies: replace with
  hand-drawn art before any public release. Everything else on the rebuilt map is vanilla
  Emerald tiles (Rongokako's terraces use the Route 119 ridge tiles).

## Opening intro (27 Sept 2026)
- Reuses the title screen's Te Mata dawn backdrop and mist, and the game's own Lugia and Ho-Oh
  front sprites (drawn as translucent silhouettes). The only new art is an 8x8 twinkling star
  (graphics/intro/pounamu_star.png), drawn in code by Claude: placeholder under rule 3.

## Rule 3 update from Ryan (27 Sept 2026)
- Ryan, 27 Sept 2026: "I don't care about the AI generated bans." So AI-made art may now ship in
  Pounamu builds. The entries above that say "replace before public release" are still worth
  keeping as a list: PokéCommunity's own rule hasn't changed, so anything AI-made needs replacing
  before a public release there. The quality bar stays the same either way: vanilla Emerald
  tiles are kept wherever Claude-drawn art isn't clearly better.

## Route rebuild (28 Sept 2026)
- Route 2 Bay, Route 2 North and Ahuriri's Marine Parade are drawn entirely from vanilla Emerald
  General-tileset metatiles (trees, sand, surf, grass coast, sea rocks), placed by rule by
  tools_pounamu/mapsynth/routekit.py. No new art.
- All fifteen template routes and Orchard Road were rebuilt the same way (vanilla General
  metatiles only). No new art.

## Town rebuild (28 Sept 2026)
- The thirteen template towns (Wairoa, Turanga, Opotiki, Tauranga, Rotorua, Taupo, Ngamotu,
  Whanganui, Wellington, Waitohi, Whakatu, Otautahi, Otepoti) are drawn with vanilla Emerald
  town tilesets and buildings, stamped whole from Game Freak's own maps by
  tools_pounamu/mapsynth/towns (library.py lists every source rectangle): Petalburg/Littleroot/
  Oldale (Wairoa, Opotiki, Whanganui, Waitohi, Taupo, Whakatu, Otautahi), Dewford (Turanga),
  Slateport (Tauranga, Ngamotu; its boats and Battle Tent), Lavaridge (Rotorua; the hot spring
  and sand bath), Mossdeep (Wellington; the space centre without its rocket stands in for the
  Beehive), Ever Grande (Otepoti; the Pokemon League building). Pokemon Center, Mart, gym and
  red-roofed houses are General-tileset buildings. No new art.
- Tamaki Makaurau keeps vanilla Lilycove, extended north and west with vanilla General trees,
  water and rock (tools_pounamu/mapsynth/fix_tamaki_edges.py); its villa is a Lilycove house.
