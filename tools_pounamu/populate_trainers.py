#!/usr/bin/env python3
"""Population pass: generate ~189 trainers across Pounamu maps.
Places objects on verified-passable tiles, appends party blocks, scripts, texts, opponent ids."""
import json, struct, re, random, os, sys

random.seed(20260715)
ROOT = '.'

# class archetypes: (Class, Pic, Gender, Music, GFX, intro/defeat/post template pool key)
CL = {
 'kid_m':  ('Youngster','Youngster','Male','Male','OBJ_EVENT_GFX_YOUNGSTER','kid'),
 'kid_f':  ('Lass','Lass','Female','Female','OBJ_EVENT_GFX_LASS','kid'),
 'school': ('School Kid','School Kid M','Male','Male','OBJ_EVENT_GFX_SCHOOL_KID_M','kid'),
 'camper': ('Camper','Camper','Male','Male','OBJ_EVENT_GFX_CAMPER','tramper'),
 'picnic': ('Picnicker','Picnicker','Female','Female','OBJ_EVENT_GFX_PICNICKER','tramper'),
 'hiker':  ('Hiker','Hiker','Male','Male','OBJ_EVENT_GFX_HIKER','tramper'),
 'fisher': ('Fisherman','Fisherman','Male','Male','OBJ_EVENT_GFX_FISHERMAN','fisher'),
 'bugkid': ('Bug Catcher','Bug Catcher','Male','Male','OBJ_EVENT_GFX_BUG_CATCHER','kid'),
 'ranger_m':('Pkmn Ranger','Pkmn Ranger M','Male','Male','OBJ_EVENT_GFX_MAN_5','ranger'),
 'ranger_f':('Pkmn Ranger','Pkmn Ranger F','Female','Female','OBJ_EVENT_GFX_WOMAN_5','ranger'),
 'expert_m':('Expert','Expert M','Male','Male','OBJ_EVENT_GFX_EXPERT_M','expert'),
 'expert_f':('Expert','Expert F','Female','Female','OBJ_EVENT_GFX_EXPERT_F','expert'),
 'farmer': ('Pokefan','Pokefan M','Male','Male','OBJ_EVENT_GFX_POKEFAN_M','farmer'),
 'farmer_f':('Pokefan','Pokefan F','Female','Female','OBJ_EVENT_GFX_POKEFAN_F','farmer'),
 'ace_m':  ('Cooltrainer','Cooltrainer M','Male','Male','OBJ_EVENT_GFX_MAN_3','ace'),
 'ace_f':  ('Cooltrainer','Cooltrainer F','Female','Female','OBJ_EVENT_GFX_WOMAN_3','ace'),
 'sailor': ('Sailor','Sailor','Male','Male','OBJ_EVENT_GFX_SAILOR','fisher'),
 'blackbelt':('Black Belt','Black Belt','Male','Male','OBJ_EVENT_GFX_BLACK_BELT','ace'),
 'scarfie':('Guitarist','Guitarist','Male','Male','OBJ_EVENT_GFX_BOY_2','kid'),
 'gent':   ('Gentleman','Gentleman','Male','Male','OBJ_EVENT_GFX_GENTLEMAN','expert'),
}

TEXTS = {
 'kid': [("Oi! You walked into my line\\nof sight. Them's the rules!","Aw, heck!","Mum says losing builds\\ncharacter. I'm SO strong now."),
         ("Bet you can't beat me.\\nDouble or nothing on my lunch!","You can have the sammie.","Worth it. Rematch at smoko?"),
         ("I've been training out here\\nALL morning!","Okay, MOST of the morning.","Don't tell my nan I lost.")],
 'tramper': [("Kia ora! Great day for it, eh?\\nBattle before the weather turns?","The forecast said nothing\\nabout you.","Southerly's coming. Take care\\nup the track."),
         ("I've tramped every track in\\nthis region. Fight me.","Blisters AND a loss. Ka pai.","The huts are full this weekend.\\nBook ahead, e hoa."),
         ("Shortcut? There's no shortcut.\\nThere's only the long way.","You earned the view.","One more ridge. There's always\\none more ridge.")],
 'fisher': [("Shh! You'll scare the fish!\\n…Too late. Battle.","Snapped my line AND my streak.","They're biting better since\\nyou showed up. Weird."),
         ("The one that got away was\\nTHIS big. Like my Pokemon.","Also got away on me.","Tide's turning. Good luck out\\nthere."),
         ("Patience. That's fishing.\\nAlso that's battling.","I bit too early.","A bad day's fishing beats a\\ngood day's working.")],
 'ranger': [("DOC ranger. Checking traps.\\nAnd checking trainers.","Pest-free AND beaten.","Keep to the track and take\\nyour rubbish out, eh."),
         ("This is protected land.\\nProve you respect it.","You fight like you care.","The birds come back when\\nthe stoats go. Remember that."),
         ("Kaitiaki of this stretch.\\nShow me your manners.","Manners AND muscle. Ka pai.","Leave it better than you\\nfound it.")],
 'expert': [("Sixty years I've watched this\\nland. Show me something new.","…That was new.","The land remembers everyone\\nwho crosses it."),
         ("My mokopuna says I'm out of\\ndate. Let's test that.","Tell no one.","Old tricks are just good\\ntricks that lasted.")],
 'farmer': [("Between milkings. You've got\\nten minutes. Go.","Back to the shed, then.","Rain's coming. Good for the\\ngrass, good for nothing else."),
         ("These paddocks don't run\\nthemselves, but the dog helps.","The dog's still the best\\nworker here.","Gates SHUT behind you,\\nthanks.")],
 'ace': [("You've got badges. I've got\\nstandards. Let's see.","Standards met.","The League's tougher than me.\\nBarely."),
         ("I train where the weather's\\nworst. Makes us honest.","Honestly beaten.","Strength is showing up in\\nthe rain.")],
}

# map plans: (dir, script_prefix, id_prefix, count, (lvmin,lvmax), species pool, class keys, gym_status)
PLANS = [
 ('OrchardRoad','OrchardRoad','ORD',5,(4,7),['Pidgey','Caterpie','Hoppip','Cherubi','Bunnelby','Weedle'],['kid_m','kid_f','bugkid','farmer_f','school'],None),
 ('Route2Bay','Route2Bay','R2B',6,(6,9),['Pidgey','Bunnelby','Hoppip','Wingull','Cherubi','Weedle','Nincada'],['kid_m','kid_f','fisher','picnic','bugkid','school'],None),
 ('Route2North','Route2North','R2N',5,(9,12),['Mareep','Wingull','Combee','Ralts','Bunnelby','Hoppip'],['farmer','farmer_f','camper','kid_f','ranger_m'],None),
 ('Route2East','Route2East','R2E2',5,(11,14),['Mareep','Morelull','Skiploom','Poochyena','Flaaffy','Wingull'],['camper','picnic','ranger_f','farmer','hiker'],None),
 ('Route35A','Route35A','R35A',7,(11,15),['Hoothoot','Pinsir','Taillow','Chatot','Zubat','Salandit','Tranquill'],['camper','picnic','ranger_m','bugkid','hiker','expert_m','kid_m'],None),
 ('Route35B','Route35B','R35B',7,(14,17),['Noctowl','Pinsir','Taillow','Chatot','Salandit','Tranquill','Zubat'],['ranger_f','hiker','camper','expert_f','bugkid','picnic','kid_f'],None),
 ('Route2BoP','Route2BoP','RBOP',7,(16,19),['Wingull','Cramorant','Taillow','Krabby','Shellder','Pyukumuku','Wattrel'],['fisher','sailor','tuberish','picnic','kid_m','fisher','camper'],None),
 ('Route36','Route36','R36',6,(15,18),['Starly','Hoothoot','Fomantis','Morelull','Komala','Shroomish','Staravia'],['bugkid','camper','ranger_m','picnic','school','hiker'],None),
 ('Route5','Route5','R5P',7,(19,23),['Geodude','Slugma','Sizzlipede','Koffing','Togedemaru','Graveler','Magcargo'],['hiker','camper','expert_m','ranger_f','kid_m','hiker','picnic'],None),
 ('Route1Desert','Route1Desert','R1DP',7,(22,25),['Mudbray','Sandygast','Doduo','Dodrio','Mudsdale','Larvitar'],['hiker','ranger_m','camper','expert_f','ace_m','hiker','picnic'],None),
 ('Route43','Route43','R43P',7,(22,25),['Shroomish','Phantump','Pumpkaboo','Misdreavus','Murkrow','Gastly','Hoothoot'],['ranger_f','hiker','camper','expert_m','bugkid','picnic','ace_f'],None),
 ('Route3','Route3','R3P',7,(24,27),['Taillow','Swellow','Flaaffy','Rockruff','Tauros','Miltank','Jumpluff','Kirlia'],['farmer','farmer_f','camper','ace_m','ranger_m','picnic','kid_f'],None),
 ('Route1Kapiti','Route1Kapiti','R1KP',7,(26,29),['Flaaffy','Ampharos','Mantine','Swanna','Stantler','Kirlia','Raticate','Pelipper'],['farmer','sailor','ace_f','ranger_f','camper','expert_m','fisher'],None),
 ('Route6','Route6','R6P',7,(25,28),['Petilil','Cottonee','Venonat','Vespiquen','Whimsicott','Lilligant','Venomoth','Jumpluff'],['bugkid','picnic','camper','ace_f','ranger_m','farmer_f','kid_m'],None),
 ('Route7','Route7','R7P',10,(29,33),['Swinub','Stantler','Murkrow','Sneasel','Aron','Bergmite','Piloswine','Skarmory','Lairon'],['hiker','hiker','camper','expert_m','ace_m','ranger_f','picnic','blackbelt','expert_f','ace_f'],None),
 ('Route1South','Route1South','R1SP',9,(33,36),['Wooloo','Dubwool','Crabrawler','Snorunt','Sneasel','Glalie','Spheal','Sealeo','Eiscue'],['farmer','farmer_f','hiker','ace_m','ace_f','expert_m','fisher','ranger_m','blackbelt'],None),
 ('Route5Ranges','Route5Ranges','R5RP',7,(23,26),['Noctowl','Ferroseed','Sentret','Furret','Stantler','Pinsir','Breloom','Komala'],['ranger_m','ranger_f','hiker','camper','expert_f','bugkid','ace_m'],None),
 ('RuapehuAscent','RuapehuAscent','RUAP',5,(53,57),['Weavile','Mamoswine','Avalugg','Glalie','Skarmory','Centiskorch','Piloswine'],['expert_m','blackbelt','ace_f','hiker','expert_f'],None),
 ('TeMataTrack','TeMataTrack','TMTP',5,(46,50),['Solrock','Lunatone','Skarmory','Trevenant','Lycanroc','Pupitar','Wyrdeer'],['expert_m','expert_f','ace_m','ace_f','ranger_f'],None),
 # towns
 ('HeretaungaTown','HeretaungaTown','HTT',3,(5,8),['Pidgey','Caterpie','Hoppip','Cherubi'],['kid_m','kid_f','school'],None),
 ('AhuririCity','AhuririCity','AHC',3,(12,15),['Wingull','Snubbull','Pidgeotto','Barboach'],['kid_m','gent','fisher'],None),
 ('Wairoa','Wairoa','WRT',2,(13,16),['Mareep','Wingull','Morelull'],['farmer_f','fisher'],None),
 ('Rotorua','Rotorua','RTT',3,(18,21),['Slugma','Sizzlipede','Geodude','Koffing'],['kid_m','hiker','expert_f'],None),
 ('Taupo','Taupo','TPT',4,(20,24),['Psyduck','Poliwag','Poliwhirl','Ducklett','Tynamo'],['fisher','fisher','picnic','sailor'],None),
 ('Tauranga','Tauranga','TGT',3,(18,21),['Krabby','Shellder','Cramorant','Wingull'],['sailor','fisher','tuberish'],None),
 ('Wellington','Wellington','WLT',5,(26,30),['Wattrel','Ducklett','Kirlia','Venonat','Swanna'],['scarfie','ace_f','gent','school','ranger_f'],None),
 ('Whakatu','Whakatu','WKT',3,(28,31),['Petilil','Cottonee','Sizzlipede','Ferroseed'],['picnic','farmer','expert_m'],None),
 ('Otautahi','Otautahi','OTT',5,(31,34),['Timburr','Gurdurr','Aron','Ferroseed','Magnemite'],['blackbelt','hiker','ace_m','school','farmer_f'],None),
 ('Otepoti','Otepoti','OPT',4,(34,37),['Snorunt','Crabrawler','Wooloo','Sneasel','Eiscue'],['scarfie','scarfie','ace_f','expert_m'],None),
 ('TamakiMakaurau','TamakiMakaurau','TMK',5,(45,49),['Raticate','Garbodor','Perrserker','Honchkrow','Malamar','Crawdaunt'],['ace_m','ace_f','gent','blackbelt','scarfie'],None),
 # gym trainers (share the leader's rule)
 ('AhuririGym','AhuririGym','GYM2',2,(12,14),['Snubbull','Ralts','Cottonee'],['kid_f','gent'],'Misty Terrain'),
 ('RotoruaGym','RotoruaGym','GYM3',2,(19,21),['Mudbray','Sandygast','Wooper'],['hiker','ranger_m'],'Sea Of Fire Player / Sea Of Fire Opponent'),
 ('TaurangaGym','TaurangaGym','GYM4',2,(22,24),['Krabby','Shellder','Wingull'],['sailor','fisher'],'Swamp Player'),
 ('WellingtonGym','WellingtonGym','GYM5',2,(25,27),['Wattrel','Ducklett','Taillow'],['ranger_f','ace_m'],'Tailwind Opponent'),
 ('WhakatuGym','WhakatuGym','GYM6',2,(27,29),['Slugma','Sizzlipede','Magcargo'],['expert_m','camper'],None),
 ('OtautahiGym','OtautahiGym','GYM7',2,(31,33),['Ferroseed','Aron','Bronzor'],['blackbelt','ace_f'],'Trick Room'),
 ('OtepotiGym','OtepotiGym','GYM8',2,(34,36),['Snorunt','Snom','Spheal','Bergmite'],['ace_m','expert_f'],None),
 # extras
 ('SkyTowerLobby','SkyTowerLobby','TWEX',2,(42,45),['Mightyena','Raticate','Honchkrow','Gurdurr'],['blackbelt','ace_m'],None),
 ('PounamuLeagueEntrance','PounamuLeagueEntrance','VICT',3,(42,45),['Swellow','Gyarados','Whimsicott','Weavile','Ampharos','Trevenant'],['ace_m','ace_f','expert_m'],None),
]
# Rata's orchard hands live on HeretaungaTown map with her status
PLANS.append(('HeretaungaTown','HeretaungaTown','GYM1',2,(7,9),['Cherubi','Hoppip','Combee'],['farmer_f','kid_m'],'Grassy Terrain'))

CL['tuberish'] = CL['kid_f']  # beach kids

NAMES = """Wiremu Anahera Mere Aroha Tane Marama Moana Kahu Rewi Hana Piri Tui Miro Ripeka Hine
Ihaia Matiu Petera Rawiri Timoti Hohepa Eruera Hirini Wetini Mihi Ngaio Rima Kawe Huhana Oriwa
Peti Ruta Meri Riria Kuini Pare Anika Beau Blake Caleb Charlie Dylan Ella Finn Harper
Hunter Isla Jack Jake Jess Kayla Liam Lucas Maddie Mason Mia Nate Nikki Olive Ollie
Paige Quinn Riley Ruby Sam Sophie Thomas Tyler Willow Zoe Ashley Bella Cody Daisy Emma
Flora Gus Heath Ivy Jonty Kane Lena Milo Nina Otis Pippa Reid Stella Troy Una
Vince Wade Ximena Yvette Zach Aki Bex Cal Dee Eli Faye Gil Hana2 Ike Joss Kea Levi Mila Ned Orla Pete Rata2 Sid Tila Umi Vada Wes Yaz Zeb Ariki Hori2 Kupe Miriama Rerewa Tainui Waka Whetu2 Hika2 Manaia Ngaire Paikea Rongo Taika Uenuku Wero Hana3 Toa2 Ipo Kiwa Marara Amiria Hakopa Irirangi Kereama Mereana Ngahuia Otene Paora Rangimarie Tamati
Waimarama Whina Aputa Eru2 Hemi2 Kiri2 Mahina Niko Pounamu2 Rangi2 Tia Wiki Aria Bodhi Cleo
Darcy Eddie2 Freya Griff Hollie Indie Jorja Koby Lara Max Nell Oscar Poppy Reuben2 Sadie
Teddy Ursula Vera Wren Xanthe Yusuf Zara Ada Bram Cora Dita Enzo Fern Gwen Hugo
Iris Jude Kip Lola Mack Nova2 Opal Pearl Quill Rex Sage Tess Uma Vik Wynn""".split()
NAMES = [n.replace('2','') for n in NAMES]
seen=set(); POOL=[]
for n in NAMES:
    if n not in seen and len(n)<=10: seen.add(n); POOL.append(n)

layouts = {l['id']: l for l in json.load(open('data/layouts/layouts.json'))['layouts'] if isinstance(l, dict)}

def passable_positions(mapdir):
    mj = json.load(open(f'data/maps/{mapdir}/map.json'))
    l = layouts[mj['layout']]
    w,h = l['width'], l['height']
    data = open(l['blockdata_filepath'],'rb').read()
    def ok(x,y):
        if not (2<=x<w-2 and 2<=y<h-2): return False
        v = struct.unpack_from('<H', data, (y*w+x)*2)[0]
        return ((v>>10)&3)==0
    occupied = set()
    for o in mj.get('object_events',[]): occupied.add((o['x'],o['y']))
    for wp in mj.get('warp_events',[]): occupied.add((wp['x'],wp['y']))
    for ce in mj.get('coord_events',[]): occupied.add((ce['x'],ce['y']))
    spots=[]
    for y in range(2,h-2):
        for x in range(2,w-2):
            if not ok(x,y): continue
            if any(abs(x-ox)<=2 and abs(y-oy)<=2 for ox,oy in occupied): continue
            # need at least one passable neighbor to face
            faces=[]
            if ok(x,y+1): faces.append('MOVEMENT_TYPE_FACE_DOWN')
            if ok(x-1,y): faces.append('MOVEMENT_TYPE_FACE_LEFT')
            if ok(x+1,y): faces.append('MOVEMENT_TYPE_FACE_RIGHT')
            if faces: spots.append((x,y,faces))
    return mj, spots

opp = open('include/constants/opponents.h').read()
party = open('src/data/trainers.party').read()
next_id = 920
new_defs=[]; new_party=[]; total=0; report=[]

for mapdir, prefix, idp, count, band, pool, classes, gymstatus in PLANS:
    mj, spots = passable_positions(mapdir)
    if len(spots) < count:
        print(f"!! {mapdir}: only {len(spots)} spots for {count}"); count=len(spots)
    random.shuffle(spots)
    # spread: greedy min-distance pick
    chosen=[]
    for s in spots:
        if all(abs(s[0]-c[0])+abs(s[1]-c[1])>=6 for c in chosen): chosen.append(s)
        if len(chosen)==count: break
    if len(chosen)<count: chosen = spots[:count]
    scr = open(f'data/maps/{mapdir}/scripts.inc').read()
    add_scr=[]
    for i,(x,y,faces) in enumerate(chosen):
        name = POOL.pop(0)
        ck = classes[i%len(classes)]
        cls,pic,gender,music,gfx,tk = CL[ck]
        tid = f'TRAINER_{idp}_{name.upper()}'
        new_defs.append(f'#define {tid:<35} {next_id}')
        next_id+=1; total+=1
        # team: 1-3 mons
        nmons = 1 if band[1]<10 else (2 if band[1]<30 else random.choice([2,3]))
        mons=[]
        for k in range(nmons):
            sp = random.choice(pool)
            lv = random.randint(*band)
            mons.append(f"\n{sp}\nLevel: {lv}")
        status = f"\nStarting Status: {gymstatus}" if gymstatus else ""
        new_party.append(f"=== {tid} ===\nName: {name}\nClass: {cls}\nPic: {pic}\nGender: {gender}\nMusic: {music}\nDouble Battle: No{status}\nAI: Check Bad Move\n" + "".join(mons) + "\n")
        intro,defeat,post = random.choice(TEXTS[tk])
        lbl = f'{prefix}_EventScript_P{name}'
        add_scr.append(f"""
{lbl}::
\ttrainerbattle_single {tid}, {prefix}_Text_P{name}Intro, {prefix}_Text_P{name}Defeat
\tmsgbox {prefix}_Text_P{name}Post, MSGBOX_AUTOCLOSE
\tend

{prefix}_Text_P{name}Intro:
\t.string "{name}: {intro}$"

{prefix}_Text_P{name}Defeat:
\t.string "{defeat}$"

{prefix}_Text_P{name}Post:
\t.string "{post}$"
""")
        mj['object_events'].append({
            "graphics_id": gfx, "x": x, "y": y, "elevation": 3,
            "movement_type": random.choice(faces),
            "movement_range_x": 0, "movement_range_y": 0,
            "trainer_type": "TRAINER_TYPE_NORMAL",
            "trainer_sight_or_berry_tree_id": "2",
            "script": lbl, "flag": "0"})
    open(f'data/maps/{mapdir}/scripts.inc','w').write(scr + "".join(add_scr))
    json.dump(mj, open(f'data/maps/{mapdir}/map.json','w'), indent=2)
    report.append(f"{mapdir}: +{len(chosen)}")

# opponents.h: insert defines + bump count
opp = opp.replace('#define TRAINERS_COUNT_EMERALD     920',
                  '\n'.join(new_defs) + f'\n\n#define TRAINERS_COUNT_EMERALD     {next_id}')
open('include/constants/opponents.h','w').write(opp)
open('src/data/trainers.party','w').write(party.rstrip('\n') + '\n\n' + '\n'.join(new_party))
print('\n'.join(report))
print(f"TOTAL NEW: {total}  (ids up to {next_id-1}, ceiling 1119)")
