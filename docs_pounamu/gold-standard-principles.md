# Gold Standard: Designing and Developing a Pokémon ROM Hack

*Pokémon Pounamu working reference, 27 September 2026. Drawn from community design guides and from what the best hacks (Unbound, Radical Red, Elite Redux, Emerald Rogue) do well. It also includes lessons learned the hard way on this project. Each section ends with how it applies to Pounamu.*

**The one-line test:** a player who grew up on Emerald should feel at home within ten seconds and surprised within ten minutes. It must look, sound and play like a real GBA Pokémon game, and it must be unmistakably Aotearoa.

---

## 1. Foundations: engine, tools, workflow

- **Build on a maintained base, not a hex-edited ROM.** pokeemerald-expansion gives you the modern battle engine, every generation's Pokémon and moves, and configurable features, all as readable C and scripts. Everything below assumes a decomp base.
- **Use the standard tools.** Porymap for maps and events. Porytiles for turning PNG tile art into Gen 3 tilesets. poryscript for readable scripts, if wanted. Tools other people already use mean their tutorials and fixes also apply to you.
- **Put everything in version control and commit small.** Each map, feature or fix is its own commit with a message saying what and why, so a bad change can be undone without losing a night's work.
- **Configure features, don't hand-roll them.** The expansion's config files turn on the physical/special split, followers, day and night, DexNav and more. Change a config before writing new code.
- **Keep a build you can trust.** Clean builds, a known-good ROM for every release, and an automated emulator harness that can spawn anywhere and take screenshots.

**Pounamu:** expansion 1.16.2 · headless mGBA QA harness · mapsynth tools · project docs as the source of truth.

---

## 2. Vision and scope

- **Know what makes your hack yours, and put it in every screen.** Great hacks have a clear identity: Unbound is a mission-dense open region, Radical Red is competitive difficulty. A region based on a real place should feel like that place, not a reskin of Hoenn.
- **Build a vertical slice first.** Take one town, one route and one gym all the way to finished (layout, art, music, trainers, side content, testing) before scaling up. The slice becomes the template and shows the real cost of everything else.
- **Finishing beats features.** Most hacks die unfinished. Cut scope before cutting quality, and keep a list of things that are "designed but not built".
- **Be consistent.** "Consistency matters more than individual asset quality." One style family for art, one voice for writing, one set of rules for difficulty.

**Pounamu:** identity is Aotearoa plus pūrākau plus the family story. The Heretaunga slice goes first.

---

## 3. World and map design

### Routes
- **Every route needs its own identity.** "Make sure each route has something that sets it apart from the others": a river crossing, a ridge, a beach, a forest pocket, a landmark on the horizon.
- **Plan before placing tiles.** Sketch the terrain and the player's path first. Improvised maps look improvised.
- **Direction should be clear, but not straight.** Players always know which way is forward, and the path still bends. Classic first routes use S-bends and zig-zag grass patches to feel longer than they are (Hoenn's Route 101 fits three S-bends into a square).
- **Force engagement.** "Routes should either force the player through tall grass, or force them into Trainer battles." A route you can walk through without engaging wastes the player's time.
- **Keep the walkable width consistent.** Avoid squeezing a wide section into a one-tile gap unless it's a deliberate chokepoint.
- **Use ledges.** They create one-way loops, so backtracking doesn't mean re-walking, and they naturally corral trainers so battles never start off-screen.
- **Place trainers deliberately.** Put them in corridors and at corners where their line of sight crosses the path. Each has a reason to be there and a line that fits the place.
- **Reward optional exploration.** Side pockets, items behind ledges, Cut trees or water, hidden items in plausible spots. The main path never requires an HM the player can't have yet.
- **Everything should be plausible.** Ask whether a tree could really grow there, and whether a person would have a reason to build this here.
- **Vary with elevation and small details:** hills, smaller trees, offshoot paths, flower patches. Don't clutter.
- **Mind the border.** The player sees about 7 tiles either side and 5 up and down. Fill the border with believable terrain (forest, sea, mountains), never a void.

### Towns and cities
- **Every town has a purpose and an identity** that shows in its buildings, NPCs and one signature landmark.
- **Make them walkable at a glance.** A clear main street, the Pokémon Centre and Mart where the player expects them, and doors facing paths.
- **They're lived in.** NPCs doing things, with dialogue that varies in tone and content, and no generic filler.
- **Keep scale honest.** A capital shouldn't be smaller than a village. Give cities multiple districts or maps.

### Region structure
- **Show the lock before the key.** Players should see the road they can't take yet. That's a promise, and it pays off later.
- **Pace intensity with rest:** a route, then a town (safety), then a dungeon (tension), then a gym (payoff), then a story beat.
- **Progress must never be blocked.** A player should never be stuck without the item or ability they need, with no way to get it.

**Pounamu:** the town-design-principles doc. Routes are being rebuilt from 16-wide corridors to region-shaped routes on vanilla tiles.

---

## 4. Tile craft: slick and smooth

These are the technical rules behind "no strange tile flaws". Treat each one as a hard gate.

1. **Trees tessellate on a 2×2 grid.** Cut exits and gaps on that grid, or you leave half trees and stray treetops.
2. **Use each tile for what it is.** Some tiles look like one thing but are part of another; Petalburg's "hedge tops" are really tree bottoms. Verify every piece by rendering it before using it.
3. **Edges must connect.** Every path, water, ledge and cliff edge closes with the correct corner and end pieces. There are no orphan edge tiles.
4. **Seams between maps.** The GBA draws a neighbouring map with the *current* map's tileset and doesn't redraw it when you cross. Where two connected maps use different secondary tilesets, the rows near the seam must use shared primary tiles only.
5. **Respect the tileset budget.** A secondary tileset allows 512 tiles and 512 metatiles, and each 8×8 tile uses one of 13 palettes of 15 colours each. Design art to repeat cleanly.
6. **Keep one style family.** Don't mix Game Freak's row-planted trees with scattered naturalistic trees on the same map. Don't mix art styles across a region.
7. **Collision matches the art.** Water isn't walkable, roofs aren't walkable, doors behave like doors. Use the correct layer types so sprites pass in front of and behind things properly.
8. **Automate the checks,** then confirm by eye in the emulator:
   - broken or partial trees
   - misused tiles
   - tile neighbours never seen in vanilla maps
   - every door, NPC, item and trigger reachable
   - seam walks in both directions

---

## 5. Art and audio

- **Never rip.** Use only released-for-use resources, open licences, or your own work. Credit per artist, per asset, from the day it's imported.
- **Consistency over brilliance.** A cohesive set of modest tiles beats a patchwork of beautiful ones.
- **Stock tiles used creatively are respectable; custom tiles are better.** Signature local landmarks deserve custom art from a real pixel artist.
- **Palette discipline.** Regional palette variation (golden Bay, wet-green East Cape, silver South) adds identity cheaply. Day and night multiplies it.
- **Use atmosphere with restraint.** Weather such as rain, fog, snow and ash sets mood, but heavy effects that hurt readability are worse than none.
- **Music drives emotion.** Cue changes on story beats matter as much as the tracks themselves. Clear the rights for anything that isn't original.
- **AI-generated assets:** PokéCommunity prohibits AI content in showcased fan games. Keep AI art to private reference or placeholders, and replace it before a public release.

**Pounamu:** POUNAMU-CREDITS rules 1–4. The Grok title art, Clock Tower and star sprite are logged as placeholders.

---

## 6. Story, writing and culture

- **Events move the plot; the plot doesn't move events.** Every scene changes something.
- **Show, then tell.** Let players witness the villain's plan in hour one (as Unbound does), rather than hearing about it.
- **Avoid a hollow "save the world" story.** Personal stakes and nuance age better than spectacle.
- **NPCs have voices.** Vary tone, avoid external references that date quickly, and fit the text to the box: about 32 characters per line, and supported characters only.
- **Hand over the tools diegetically.** Systems like the Job Board, DexNav or the Mission Log come from characters in the world.
- **Cultural material is held with care.** The people it belongs to lead. Consult on the highest-care sites and stories, and never play the sacred for spectacle.

**Pounamu:** the dialogue bible is Ryan's editing surface. Pūrākau and rohe-specific content is Ryan's call.

---

## 7. Gameplay and balance

- **Don't fake difficulty with levels.** Challenge should come from trainer AI, team design, double battles, held items, EVs and IVs, restrictions and puzzles, not just higher numbers.
- **Plan a smooth curve.** Set a level target per milestone, check it against wild levels and the XP available along the path, and adjust. Optional level caps and a hard mode serve both casual players and Nuzlockers.
- **Give gyms a gimmick** that changes how the battle plays (field effects, terrain, forced doubles, Trick Room), not just a type.
- **Trainers have purpose.** Themed teams, sensible movesets, and the occasional memorable fight on every route.
- **Encounters should vary.** Each route offers something new or rare, placed by habitat, including by time of day and fishing tier.
- **Features must not break.** An unintended softlock does more damage than a missing feature.

**Pounamu:** the level curve and eight gym gimmicks in the walkthrough doc.

---

## 8. Quality of life (modern comfort, GBA feel)

These features are expected in modern hacks and are available in the expansion:

- running indoors and a faster bike
- reusable TMs, a move relearner and deleter, nature mints, and IV/EV tools reachable in-game
- an Exp. Share toggle, repels that ask to be reused, and a HM-free or low-HM traversal option
- DexNav or similar, followers, a PC reachable from anywhere (optional), and quick-save prompts
- faster text and battle animation options, and a clear objective hint or mission log

Keep the look and feel Gen 3. QoL is invisible comfort, not a UI overhaul.

---

## 9. Side content and density

- **Never more than two screens without a thing.** An item, a trainer, a side quest hook, a view, a character.
- **Missions have shape.** Hook, errand or puzzle, payoff, and ideally a callback later. Seed game-long collections early (Unbound's tablets and Zygarde cells; our Pounamu Trail and Manu Log).
- **The post-game is a second act.** Legendaries woken, the region opened, new challenges. It isn't a checklist.

---

## 10. Testing and QA

- **Test every build, in the emulator.** Walk the maps, especially seams in both directions. Trigger every scene, battle every scripted trainer.
- **Keep a softlock checklist:**
  - Can the player get stuck with no way forward?
  - Can a trainer's sight line trap them?
  - Is there a one-way ledge into a dead end?
  - Is every required item obtainable?
- **Save compatibility.** Flag and var changes can break existing saves. Note breaking releases.
- **Use several emulators.** mGBA is the reference. Check at least one other (OpenEmu or VBA) and real hardware, or a flash cart, if possible.
- **Playtesters who didn't build it.** Fresh eyes find the confusing bits. Collect reports with screenshots and map coordinates.
- **Keep a known-issues list** in the release notes. Honesty earns patience.

---

## 11. Release and community

- **Distribute patches (BPS/UPS), not ROMs.** Players patch their own legally obtained copy.
- **Stay non-commercial.** No selling and no paid access. Donations are a grey area. Nintendo has taken down high-profile projects (Pokémon Prism) regardless of patch format, so a low profile until release is wise.
- **Showcase-ready means** a playable build, screenshots, a feature list, full credits, and compliance with the forum's rules, including the AI-content ban.
- **Version sensibly.** Use alpha, beta and release versions with changelogs. Don't break saves without warning.

---

## 12. Pounamu house rules (summary)

1. Authentic GBA Pokémon first. Beautiful second. Never one without the other.
2. Vanilla Emerald/FRLG art is the floor. Released-for-use packs and commissioned artists raise it. No rips. No AI art in shipped content.
3. Every map passes the Section 4 gates before commit.
4. Story and cultural calls are Ryan's. Claude builds, tests, commits and reports.
5. Finish the Heretaunga slice to release quality, then roll the template out.

---

## Sources

- [PokéCommunity Daily: How To Make Your Maps Stand Out](https://daily.pokecommunity.com/2016/12/04/make-maps-stand/)
- [PokéCommunity Daily: Fangame Tutorials, Mapping Routes](https://daily.pokecommunity.com/2017/09/14/fangame-tutorials-mapping-routes/)
- [PokéCommunity: A comprehensive list of things that make great ROM hacks](https://www.pokecommunity.com/threads/a-comprehensive-list-of-things-that-make-a-great-rom-hacks.387493/)
- [PokéCommunity: What makes a ROM hack 'good'?](https://www.pokecommunity.com/threads/what-makes-a-rom-hack-good.319747/)
- [PokéCommunity: DJTiKi's guide to planning your ROM hack](https://www.pokecommunity.com/threads/djtikis-mega-huge-guide-to-planning-your-awesome-rom-hack-the-guide-for-everything-pokemon.329825/)
- [PokéCommunity: ROM Hacks Showcase Guidelines](https://www.pokecommunity.com/threads/rom-hacks-showcase-guidelines.467328/)
- [PokéCommunity: ROM hacking, patches and the legal consequences](https://www.pokecommunity.com/threads/rom-hacking-patches-and-the-legal-consequences.385958/)
- [PokéCommunity: QoL things you want most in hacks](https://www.pokecommunity.com/threads/qol-quality-of-life-things-you-want-most-in-hacks.430613/)
- [Pokémon Workshop: Good practices in level design](https://pokemonworkshop.com/en/learn/good-practices-in-level-design)
- [Fantendo: Analysis of the first routes in Pokémon games (Gen I–IV)](https://fantendo.fandom.com/wiki/User_blog:Shadow_Inferno/A_short_analysis_of_the_first_Routes_in_Pokemon_Games_(Gen_I-IV))
- [rh-hideout/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion)
- [Porymap](https://github.com/huderlem/porymap) · [Porytiles](https://github.com/grunt-lucas/porytiles)
- [Unbound Wiki walkthrough](https://unboundwiki.com/walkthrough/) (via the project's Unbound archetype doc)
