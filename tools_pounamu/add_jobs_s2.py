#!/usr/bin/env python3
"""Mission batch S2: 24 i-SITE jobs across Aotearoa (Acts 1-3 + Tamaki).

Run once from the repo root on a clean tree:  python3 tools_pounamu/add_jobs_s2.py
Refuses to run twice (checks for its marker). Validates every new NPC /
hidden-item tile against the map's collision grid before writing anything.
"""
import json, os, re, struct, sys, textwrap

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MARK = '@ ---- Mission batch S2'
WRAP = 31

# --------------------------------------------------------------------------
# text helpers
# --------------------------------------------------------------------------
def fmt(s):
    """Plain prose -> .string lines. Blank line = new box (\\p)."""
    s = s.replace('—', '-').replace('–', '-')
    for bad in 'āēīōūĀĒĪŌŪ':
        if bad in s:
            raise SystemExit('macron in text (charmap has none): ' + s[:40])
    paras = [p.strip() for p in s.strip().split('\n\n')]
    paras = [re.sub(r'"([^"]*)"', '“\\1”', p) for p in paras]
    out = []
    for pi, p in enumerate(paras):
        lines = textwrap.wrap(' '.join(p.split()), WRAP)
        for li, ln in enumerate(lines):
            if '"' in ln:
                raise SystemExit('unpaired quote: ' + ln)
            if li == 0:
                sep = ''
            elif li == 1:
                sep = '\\n'
            else:
                sep = '\\l'
            out.append([sep, ln])
        out[-1].append('\\p' if pi < len(paras) - 1 else '$')
    res = []
    for item in out:
        sep, ln = item[0], item[1]
        tail = item[2] if len(item) > 2 else ''
        res.append(f'\t.string "{sep}{ln}{tail}"')
    # merge the leading separator onto the previous line's end (house style)
    fixed = []
    for i, r in enumerate(res):
        m = re.match(r'\t\.string "(\\[nl])(.*)"', r)
        if m and fixed:
            fixed[-1] = fixed[-1][:-1] + m.group(1) + '"'
            r = f'\t.string "{m.group(2)}"'
        fixed.append(r)
    return '\n'.join(fixed)

def text(label, s):
    return f'{label}:\n{fmt(s)}\n'

# --------------------------------------------------------------------------
# map helpers
# --------------------------------------------------------------------------
def mpath(m, f):
    return os.path.join(ROOT, 'data/maps', m, f)

_layouts = json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts']

def walkable(mapname, x, y, mj):
    lay = next(l for l in _layouts if l.get('id') == mj['layout'])
    w, h = lay['width'], lay['height']
    if not (0 <= x < w and 0 <= y < h):
        return False
    blk = open(os.path.join(ROOT, lay['blockdata_filepath']), 'rb').read()
    v = struct.unpack_from('<H', blk, (y * w + x) * 2)[0]
    return ((v >> 10) & 3) == 0

def occupied(mj, x, y):
    for k in ('object_events', 'warp_events', 'coord_events', 'bg_events'):
        for e in mj.get(k, []):
            if e.get('x') == x and e.get('y') == y:
                return True
    return False

MAPS = {}      # name -> json
SCRIPTS = {}   # name -> appended asm
REPLACE = {}   # (map, label) -> new body

def mj(m):
    if m not in MAPS:
        MAPS[m] = json.load(open(mpath(m, 'map.json')))
    return MAPS[m]

def add_obj(m, gfx, x, y, script, face='DOWN', flag='0', trainer=False, sight=0):
    j = mj(m)
    if not walkable(m, x, y, j):
        raise SystemExit(f'{m} ({x},{y}) is not walkable')
    if occupied(j, x, y):
        raise SystemExit(f'{m} ({x},{y}) is occupied')
    elev = j['object_events'][0]['elevation'] if j['object_events'] else 3
    j['object_events'].append({
        'graphics_id': gfx, 'x': x, 'y': y, 'elevation': elev,
        'movement_type': f'MOVEMENT_TYPE_FACE_{face}',
        'movement_range_x': 0, 'movement_range_y': 0,
        'trainer_type': 'TRAINER_TYPE_NORMAL' if trainer else 'TRAINER_TYPE_NONE',
        'trainer_sight_or_berry_tree_id': str(sight),
        'script': script, 'flag': flag})

def add_hidden(m, x, y, item, flag):
    j = mj(m)
    if not walkable(m, x, y, j) or occupied(j, x, y):
        raise SystemExit(f'{m} hidden ({x},{y}) bad tile')
    j['bg_events'].append({'type': 'hidden_item', 'x': x, 'y': y,
                           'elevation': 0, 'item': item, 'flag': flag})

def asm(m, s):
    SCRIPTS[m] = SCRIPTS.get(m, '') + s.rstrip('\n') + '\n\n'

def replace_block(m, label, body):
    """Replace `label::` up to its first `end` with body (which must define label)."""
    REPLACE[(m, label)] = body

def give(item, n=1, full='Common_EventScript_NopReturn'):
    q = f', {n}' if n != 1 else ''
    return f'\tgiveitem {item}{q}\n\tgoto_if_eq VAR_RESULT, FALSE, {full}\n'

# --------------------------------------------------------------------------
# flag / var allocation (verified free on 2026-09-26 against HEAD 29282789)
# --------------------------------------------------------------------------
F = {  # job done-flags
    'DECO': 0x286, 'WHARF': 0x287, 'HOOKS': 0x288, 'EGG': 0x289, 'SLIP': 0x28A,
    'LIGHT': 0x28B, 'DAWN': 0x28C, 'WETA': 0x28D, 'MAUAO': 0x28E, 'GEYSER': 0x28F,
    'ROCK': 0x290, 'CONVOY': 0x291, 'WIND': 0x292, 'MAIL': 0x293, 'DURIE': 0x294,
    'PETITION': 0x295, 'METSERVICE': 0x298, 'TRAMP': 0x299, 'STOWAWAY': 0x29B,
    'CONCERT': 0x29C, 'LUGGAGE': 0x2AE, 'PAUA': 0x2AF, 'TRACK': 0x2B0, 'WHALE': 0x2B1,
}
H = {  # helper flags
    'EGG_GIVEN': 0x4B0, 'MAIL_CARRY': 0x4B1, 'DURIE_GIVEN': 0x4B2,
    'DURIE_1': 0x4B3, 'DURIE_2': 0x4B4, 'DURIE_3': 0x4B5,
    'PET_HAVE': 0x4B6, 'PET_SIGN_1': 0x4B7, 'PET_SIGN_2': 0x4B8, 'PET_SIGN_3': 0x4B9,
    'SUITCASE': 0x4BA,
}
def fl(v):
    return f'FLAG_UNUSED_0x{v:03X}'
DF = {k: fl(v) for k, v in F.items()}
HF = {k: fl(v) for k, v in H.items()}
DECO_VAR = 'VAR_POUNAMU_DECO_STATE'   # 0x40FA (0x40F8/9 belong to DexNav)

# --------------------------------------------------------------------------
# the show-me pattern shared by most jobs
# --------------------------------------------------------------------------
def showme(m, J, done, check, T, reward, pre=''):
    """check: list of species (str) or ('TYPE', TYPE_X). T: text dict with
    Ask, No, Wrong, Thanks, After (+ any extra labels used by pre)."""
    P = m
    if isinstance(check, tuple):
        chk = (f'\tsetvar VAR_0x8005, {check[1]}\n'
               f'\tspecialvar VAR_RESULT, ScriptPartyMonHasType\n'
               f'\tgoto_if_eq VAR_RESULT, TRUE, {P}_{J}_Good\n')
    else:
        chk = '\tspecialvar VAR_RESULT, ScriptGetPartyMonSpecies\n' + ''.join(
            f'\tgoto_if_eq VAR_RESULT, SPECIES_{s}, {P}_{J}_Good\n' for s in check)
    s = f'''{P}_EventScript_{J}::
	lock
	faceplayer
	goto_if_set {done}, {P}_{J}_Done
{pre}	msgbox {P}_Text_{J}Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, {P}_{J}_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, {P}_{J}_No
{chk}	msgbox {P}_Text_{J}Wrong, MSGBOX_DEFAULT
	release
	end

{P}_{J}_Good::
	msgbox {P}_Text_{J}Thanks, MSGBOX_DEFAULT
{reward.replace("Common_EventScript_NopReturn", f"{P}_{J}_Full")}	setflag {done}
	release
	end

{P}_{J}_No::
	msgbox {P}_Text_{J}No, MSGBOX_DEFAULT
	release
	end

{P}_{J}_Full::
	release
	end

{P}_{J}_Done::
	msgbox {P}_Text_{J}After, MSGBOX_DEFAULT
	release
	end
'''
    for k, v in T.items():
        s += '\n' + text(f'{P}_Text_{J}{k}', v)
    return s

def givemon_block(species_const, level, name):
    return (f'\tgivemon {species_const}, {level}\n'
            f'\tgoto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NopReturn\n'
            f'\tplayfanfare MUS_OBTAIN_ITEM\n'
            f'\tmessage gText_Pounamu_Received{name}\n'
            f'\twaitmessage\n\twaitfanfare\n\twaitbuttonpress\n\tclosemessage\n')

# ==========================================================================
#                                ACT 1
# ==========================================================================

# --- Job 09: Deco Deliveries (Ahuriri) ------------------------------------
asm('AhuririCity', f'''@ Job 09: Deco Deliveries - three posies, three addresses, one table
@ state {DECO_VAR}: 0 none, 1 gallery, 2 nurse, 3 socialite, 4 back to Kiri; done {DF['DECO']}
AhuririCity_EventScript_DecoJob::
	lock
	faceplayer
	goto_if_set {DF['DECO']}, AhuririCity_DecoJob_Done
	goto_if_eq {DECO_VAR}, 4, AhuririCity_DecoJob_Finish
	goto_if_ge {DECO_VAR}, 1, AhuririCity_DecoJob_Reminder
	msgbox AhuririCity_Text_DecoLady, MSGBOX_DEFAULT
	msgbox AhuririCity_Text_DecoJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AhuririCity_DecoJob_No
	setvar {DECO_VAR}, 1
	msgbox AhuririCity_Text_DecoJobGo, MSGBOX_DEFAULT
	release
	end

AhuririCity_DecoJob_No::
	msgbox AhuririCity_Text_DecoJobNo, MSGBOX_DEFAULT
	release
	end

AhuririCity_DecoJob_Reminder::
	msgbox AhuririCity_Text_DecoJobReminder, MSGBOX_DEFAULT
	release
	end

AhuririCity_DecoJob_Finish::
	msgbox AhuririCity_Text_DecoJobThanks, MSGBOX_DEFAULT
{give('ITEM_SUN_STONE', full='AhuririCity_DecoJob_Full')}	setflag {DF['DECO']}
	release
	end

AhuririCity_DecoJob_Full::
	release
	end

AhuririCity_DecoJob_Done::
	msgbox AhuririCity_Text_DecoJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('AhuririCity_Text_DecoJobAsk', '''
Kiri: I do the flowers for half
the Deco quarter. Three posies,
three addresses, and my knees
have retired.

Run them round for me, love?''') + text('AhuririCity_Text_DecoJobGo', '''
Kiri: Bless you. First the
gallery painter, then the nurse
by the sea, then the lady in the
Quarter.

In that order. The last one's
fussy about being last.''') + text('AhuririCity_Text_DecoJobNo', '''
Kiri: Fair enough. The flowers
will keep. My knees won't.''') + text('AhuririCity_Text_DecoJobReminder', '''
Kiri: Gallery, then the nurse by
the sea, then the Quarter. Off
you pop.''') + text('AhuririCity_Text_DecoJobThanks', '''
Kiri: All three delivered? And
she didn't send the last lot
back? Well, I never.

Here. It's no sunburst window,
but it's the closest thing I
own. Take it.''') + text('AhuririCity_Text_DecoJobAfter', '''
Kiri: Everything in this town
was rebuilt at once, so it all
matches. People too, if you're
not careful.'''))

for _o in mj('AhuririCity')['object_events']:   # Kiri the deco lady now runs the job
    if _o.get('script') == 'AhuririCity_EventScript_DecoLady':
        _o['script'] = 'AhuririCity_EventScript_DecoJob'

replace_block('AhuririGallery', 'AhuririGallery_EventScript_Painter', f'''AhuririGallery_EventScript_Painter::
	lock
	faceplayer
	goto_if_eq {DECO_VAR}, 1, AhuririGallery_EventScript_PainterPosy
	msgbox AhuririGallery_Text_Painter, MSGBOX_DEFAULT
	release
	end

AhuririGallery_EventScript_PainterPosy::
	msgbox AhuririGallery_Text_PainterPosy, MSGBOX_DEFAULT
	setvar {DECO_VAR}, 2
	release
	end
''')
asm('AhuririGallery', text('AhuririGallery_Text_PainterPosy', '''
Flowers from Kiri? For me?

...She knows I'll paint them
instead of putting them in water.
She always knows.'''))

replace_block('AhuririSeasideHouse3', 'AhuririSeasideHouse3_EventScript_Nurse2', f'''AhuririSeasideHouse3_EventScript_Nurse2::
	lock
	faceplayer
	goto_if_eq {DECO_VAR}, 2, AhuririSeasideHouse3_EventScript_NursePosy
	msgbox AhuririSeasideHouse3_Text_Nurse2, MSGBOX_DEFAULT
	release
	end

AhuririSeasideHouse3_EventScript_NursePosy::
	msgbox AhuririSeasideHouse3_Text_NursePosy, MSGBOX_DEFAULT
	setvar {DECO_VAR}, 3
	release
	end
''')
asm('AhuririSeasideHouse3', text('AhuririSeasideHouse3_Text_NursePosy', '''
Oh, Kiri. She does this every
year on the anniversary. Never
says why. Doesn't need to.

Thank you, love. Mind how you go
at that last address.'''))

replace_block('AhuririQuarterHouse1', 'AhuririQuarterHouse1_EventScript_Socialite', f'''AhuririQuarterHouse1_EventScript_Socialite::
	lock
	faceplayer
	goto_if_eq {DECO_VAR}, 3, AhuririQuarterHouse1_EventScript_SocialitePosy
	msgbox AhuririQuarterHouse1_Text_Socialite, MSGBOX_DEFAULT
	release
	end

AhuririQuarterHouse1_EventScript_SocialitePosy::
	msgbox AhuririQuarterHouse1_Text_SocialitePosy, MSGBOX_DEFAULT
	setvar {DECO_VAR}, 4
	release
	end
''')
asm('AhuririQuarterHouse1', text('AhuririQuarterHouse1_Text_SocialitePosy', '''
Ah, the centrepiece. It's for
the President's table, Saturday.
The club likes a nice table.

...You're his youngest, aren't
you? Then you'll know it's best
not to ask what the club talks
about over the flowers.'''))

# --- Job 11: The Wharf Rats (Ahuriri) -------------------------------------
for tid, x, y, face in (('TRAINER_WHARF_JAYDEN', 36, 19, 'LEFT'),
                        ('TRAINER_WHARF_SKYE', 35, 23, 'LEFT'),
                        ('TRAINER_WHARF_BRAX', 37, 28, 'LEFT')):
    add_obj('AhuririCity', 'OBJ_EVENT_GFX_AQUA_MEMBER_F' if 'SKYE' in tid else 'OBJ_EVENT_GFX_AQUA_MEMBER_M',
            x, y, 'AhuririCity_EventScript_' + tid.split('_')[-1].title(), face, trainer=True, sight=2)
asm('AhuririCity', f'''@ Job 11: The Wharf Rats - the crew hogging the end of the wharf; done {DF['WHARF']}
AhuririCity_EventScript_Jayden::
	trainerbattle_single TRAINER_WHARF_JAYDEN, AhuririCity_Text_JaydenIntro, AhuririCity_Text_JaydenDefeat
	msgbox AhuririCity_Text_JaydenPost, MSGBOX_AUTOCLOSE
	end

AhuririCity_EventScript_Skye::
	trainerbattle_single TRAINER_WHARF_SKYE, AhuririCity_Text_SkyeIntro, AhuririCity_Text_SkyeDefeat
	msgbox AhuririCity_Text_SkyePost, MSGBOX_AUTOCLOSE
	end

AhuririCity_EventScript_Brax::
	trainerbattle_single TRAINER_WHARF_BRAX, AhuririCity_Text_BraxIntro, AhuririCity_Text_BraxDefeat, AhuririCity_EventScript_BraxBeaten
	msgbox AhuririCity_Text_BraxPost, MSGBOX_AUTOCLOSE
	end

AhuririCity_EventScript_BraxBeaten::
	setflag {DF['WHARF']}
	msgbox AhuririCity_Text_BraxPost, MSGBOX_DEFAULT
	release
	end
''' + text('AhuririCity_Text_JaydenIntro', '''
End of the wharf's ours. Toll's
one battle. Pay up.''') + text('AhuririCity_Text_JaydenDefeat', '''
Aw, come on.''') + text('AhuririCity_Text_JaydenPost', '''
Brax says the Mob'll take us on
when we're sixteen. That's
basically a job offer.''') + text('AhuririCity_Text_SkyeIntro', '''
You fishing? Nobody fishes here
without asking the Rats.''') + text('AhuririCity_Text_SkyeDefeat', '''
Okay, okay. You asked.''') + text('AhuririCity_Text_SkyePost', '''
My Rattata came off a container
ship. So did my dad, sort of.''') + text('AhuririCity_Text_BraxIntro', '''
Brax: Wharf Rats run this end,
bro. Fishermen pay in bait,
tourists pay in chips.

You look like you pay in
battles.''') + text('AhuririCity_Text_BraxDefeat', '''
Brax: ...Right. The wharf's
free again. Don't tell anyone
it was a kid who did it.''') + text('AhuririCity_Text_BraxPost', '''
Brax: The old fella with the
rods can have his spot back.
We'll find another end of
something.'''))

# --- Job 12: Hooks and Lines (Ahuriri, the Old Rod fisherman) -------------
replace_block('AhuririCity', 'AhuririCity_EventScript_WharfFisherDone', f'''AhuririCity_EventScript_WharfFisherDone::
	goto_if_set {DF['HOOKS']}, AhuririCity_EventScript_WharfFisherAllDone
	goto_if_unset {DF['WHARF']}, AhuririCity_EventScript_WharfFisherRats
	goto AhuririCity_EventScript_HooksJob
	end

AhuririCity_EventScript_WharfFisherRats::
	msgbox AhuririCity_Text_WharfFisherRats, MSGBOX_DEFAULT
	release
	end

AhuririCity_EventScript_WharfFisherAllDone::
	msgbox AhuririCity_Text_WharfFisherDone, MSGBOX_DEFAULT
	release
	end
''')
asm('AhuririCity', f'''@ Job 12: Hooks and Lines - show the fisherman something off the wharf; done {DF['HOOKS']}
AhuririCity_EventScript_HooksJob::
	msgbox AhuririCity_Text_HooksAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AhuririCity_Hooks_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, AhuririCity_Hooks_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
''' + ''.join(f'\tgoto_if_eq VAR_RESULT, SPECIES_{s}, AhuririCity_Hooks_Good\n' for s in
              ('BARBOACH', 'WHISCASH', 'CORPHISH', 'CRAWDAUNT', 'STUNFISK_GALAR', 'CORSOLA_GALAR',
               'CURSOLA', 'WAILMER', 'WAILORD', 'MAGIKARP', 'GYARADOS')) + f'''	msgbox AhuririCity_Text_HooksWrong, MSGBOX_DEFAULT
	release
	end

AhuririCity_Hooks_Good::
	msgbox AhuririCity_Text_HooksThanks, MSGBOX_DEFAULT
{give('ITEM_DIVE_BALL', 3, 'AhuririCity_Hooks_Full')}	setflag {DF['HOOKS']}
	release
	end

AhuririCity_Hooks_No::
	msgbox AhuririCity_Text_HooksNo, MSGBOX_DEFAULT
	release
	end

AhuririCity_Hooks_Full::
	release
	end
''' + text('AhuririCity_Text_WharfFisherRats', '''
Can't get to the end of the wharf
for those Wharf Rats. Kids with
Rattata and big opinions.

Somebody ought to have a word.
A battling sort of word.''') + text('AhuririCity_Text_HooksAsk', '''
You shifted the Rats! Good on
you. Now, did that rod get
wet yet?

Show us something you hooked off
this harbour.''') + text('AhuririCity_Text_HooksWrong', '''
Nah, that never came out of the
harbour. I know every fish in it
by first name.''') + text('AhuririCity_Text_HooksThanks', '''
Look at that! Proper harbour
stock.

Take these. They're for going
deeper than a rod can.''') + text('AhuririCity_Text_HooksNo', '''
No rush. The fish have been here
longer than both of us.'''))

# --- Job 13: Eggs in the Shelterbelt (Heretaunga) -------------------------
replace_block('HeretaungaTown', 'HeretaungaTown_EventScript_OrchardWorker', f'''HeretaungaTown_EventScript_OrchardWorker::
	lock
	faceplayer
	goto_if_set {DF['EGG']}, HeretaungaTown_EggJob_Done
	goto_if_set {HF['EGG_GIVEN']}, HeretaungaTown_EggJob_Check
	msgbox HeretaungaTown_Text_OrchardWorker, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_EggJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_EggJob_No
	giveegg SPECIES_HOOTHOOT
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HeretaungaTown_EggJob_NoRoom
	setflag {HF['EGG_GIVEN']}
	playfanfare MUS_OBTAIN_ITEM
	message HeretaungaTown_Text_EggReceived
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	msgbox HeretaungaTown_Text_EggJobGo, MSGBOX_DEFAULT
	release
	end
''')
asm('HeretaungaTown', f'''@ Job 13: Eggs in the Shelterbelt - hatch the ruru and bring it back; done {DF['EGG']}
HeretaungaTown_EggJob_Check::
	msgbox HeretaungaTown_Text_EggJobCheck, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_EggJob_Wait
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, HeretaungaTown_EggJob_Wait
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_HOOTHOOT, HeretaungaTown_EggJob_Good
	goto_if_eq VAR_RESULT, SPECIES_NOCTOWL, HeretaungaTown_EggJob_Good
	goto_if_eq VAR_RESULT, SPECIES_EGG, HeretaungaTown_EggJob_StillEgg
	msgbox HeretaungaTown_Text_EggJobWrong, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EggJob_StillEgg::
	msgbox HeretaungaTown_Text_EggJobStillEgg, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EggJob_Good::
	msgbox HeretaungaTown_Text_EggJobThanks, MSGBOX_DEFAULT
{give('ITEM_SITRUS_BERRY', 3, 'HeretaungaTown_EggJob_Full')}	setflag {DF['EGG']}
	release
	end

HeretaungaTown_EggJob_Full::
HeretaungaTown_EggJob_Wait::
	msgbox HeretaungaTown_Text_EggJobWait, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EggJob_No::
	msgbox HeretaungaTown_Text_EggJobNo, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EggJob_NoRoom::
	msgbox HeretaungaTown_Text_EggJobNoRoom, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EggJob_Done::
	msgbox HeretaungaTown_Text_EggJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('HeretaungaTown_Text_EggJobAsk', '''
Oh, and one more thing. We took
down the old pine in the
shelterbelt, and there was a
ruru nest in it.

Mum and Dad bird never came back.
One egg left. Would you keep it
warm for me?''') + 'HeretaungaTown_Text_EggReceived:\n\t.string "{PLAYER} received an Egg!$"\n\n' + text('HeretaungaTown_Text_EggJobGo', '''
Keep it close and keep walking.
Eggs like a bit of road under
them.

Bring the wee one back to show
me when it hatches, eh?''') + text('HeretaungaTown_Text_EggJobNo', '''
No worries. It's a big ask,
being somebody's mum.''') + text('HeretaungaTown_Text_EggJobNoRoom', '''
Your hands are full, eh? Make
some room and come see me.''') + text('HeretaungaTown_Text_EggJobCheck', '''
How's our ruru getting on?
Hatched yet? Show us!''') + text('HeretaungaTown_Text_EggJobStillEgg', '''
Still an egg! Give it more
road. They hatch in their own
time, same as us.''') + text('HeretaungaTown_Text_EggJobWrong', '''
That's a fine Pokemon, but it's
not our ruru.''') + text('HeretaungaTown_Text_EggJobWait', '''
Whenever you're ready. The
shelterbelt's not going
anywhere.''') + text('HeretaungaTown_Text_EggJobThanks', '''
Look at those eyes! Morepork,
morepork. That's the sound of
the orchard at night, that is.

You did right by it. Here,
something for the road.''') + text('HeretaungaTown_Text_EggJobAfter', '''
We planted a new pine where the
old one was. Every nest deserves
a second go.'''))

# --- Job 14: The Slip Watch (Heretaunga) ----------------------------------
add_obj('HeretaungaTown', 'OBJ_EVENT_GFX_SCIENTIST_1', 55, 17, 'HeretaungaTown_EventScript_SLIPJOB', 'RIGHT')
asm('HeretaungaTown', showme('HeretaungaTown', 'SLIPJOB', DF['SLIP'], ['BUNNELBY', 'DIGGERSBY'], {
    'Ask': '''
Dr Hollis: I monitor slips on the
ridge for the council. The sensors
say Te Mata has been... creaking.

Nobody hears the ground like a
burrower. Would you show me one?''',
    'No': '''
Dr Hollis: Fair. I'll go back to
my sensors. They also don't
listen to me.''',
    'Wrong': '''
Dr Hollis: Lovely, but that one
lives on top of the ground. I
need a digger.''',
    'Thanks': '''
Dr Hollis: See its ears twitch?
It's listening straight down.

...It's not scared. It's
waiting. That's worse, somehow.
Take this, and thank you.''',
    'After': '''
Dr Hollis: The readings are
flat again. Flat like a held
breath. I'll keep watching.''',
}, give('ITEM_SOFT_SAND')))

# ==========================================================================
#                                ACT 2
# ==========================================================================

# --- Wairoa: A Light That Walks (lighthouse keeper) -----------------------
replace_block('WairoaLighthouseKeeper', 'WairoaLighthouseKeeper_EventScript_Keeper',
              showme('WairoaLighthouseKeeper', 'LIGHTJOB', DF['LIGHT'], ['MAREEP', 'FLAAFFY', 'AMPHAROS'], {
    'Ask': '''
Kept the old lighthouse forty
years. Now it sits in town like a
retired soldier.

They say out east there's a sheep
with a light in its tail. A
lighthouse that walks! Show me
one before I go, would you?''',
    'No': '''
A light doesn't choose who it
saves. Worth thinking about, the
company you're headed for.''',
    'Wrong': '''
Handsome, but I can't see a
light on it anywhere.''',
    'Thanks': '''
Would you look at that. A light
that walks, and it chose to walk
with you.

Here. It came off the old lamp
mechanism. It still pulls toward
something.''',
    'After': '''
A light doesn't choose who it
saves. Yours seems to have
chosen anyway.''',
}, give('ITEM_MAGNET')).replace('WairoaLighthouseKeeper_EventScript_LIGHTJOB::',
                                'WairoaLighthouseKeeper_EventScript_Keeper::'))

# --- Job 16: Hikurangi First Light (Route 35A, mornings) ------------------
add_obj('Route35A', 'OBJ_EVENT_GFX_CAMERAMAN', 12, 10, 'Route35A_EventScript_DAWNJOB', 'UP')
asm('Route35A', f'''@ Job 16: Hikurangi First Light - be on the ridge at dawn; done {DF['DAWN']}
Route35A_EventScript_DAWNJOB::
	lock
	faceplayer
	goto_if_set {DF['DAWN']}, Route35A_DawnJob_Done
	gettimeofday
	goto_if_ne VAR_0x8000, 0, Route35A_DawnJob_NotYet
	msgbox Route35A_Text_DawnJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route35A_DawnJob_No
	fadescreen FADE_TO_WHITE
	playse SE_M_REFLECT
	msgbox Route35A_Text_DawnJobShot, MSGBOX_DEFAULT
	fadescreen FADE_FROM_WHITE
	msgbox Route35A_Text_DawnJobThanks, MSGBOX_DEFAULT
{give('ITEM_RARE_CANDY', full='Route35A_DawnJob_Full')}	setflag {DF['DAWN']}
	release
	end

Route35A_DawnJob_NotYet::
	msgbox Route35A_Text_DawnJobNotYet, MSGBOX_DEFAULT
	release
	end

Route35A_DawnJob_No::
	msgbox Route35A_Text_DawnJobNo, MSGBOX_DEFAULT
	release
	end

Route35A_DawnJob_Full::
	release
	end

Route35A_DawnJob_Done::
	msgbox Route35A_Text_DawnJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('Route35A_Text_DawnJobNotYet', '''
Hikurangi is the first maunga in
the world to see the sun each
day. I'm here to photograph it.

Come back at first light, in the
morning. I want you and your
partner in the frame.''') + text('Route35A_Text_DawnJobAsk', '''
Here it comes! First light on
Hikurangi. Quick, stand on the
ridge with your Pokemon!''') + text('Route35A_Text_DawnJobShot', '''
The sun comes up over the sea
and touches the maunga before
anything else in the world.

Click.''') + text('Route35A_Text_DawnJobNo', '''
Suit yourself. The sun will
rise either way. It's generous
like that.''') + text('Route35A_Text_DawnJobThanks', '''
Got it. You'll be the first
people in the world on film
today.

Take this. You earned an early
start.''') + text('Route35A_Text_DawnJobAfter', '''
I'll send the print to the
Turanga museum. First faces of
the day. Has a ring to it.'''))

# --- Opotiki: The Weta in the Smoko Room ----------------------------------
add_obj('OpotikiKiwifruitHouse', 'OBJ_EVENT_GFX_SPECIES(PINSIR)', 8, 3,
        'OpotikiKiwifruitHouse_EventScript_Weta', 'LEFT', flag=DF['WETA'])
replace_block('OpotikiKiwifruitHouse', 'OpotikiKiwifruitHouse_EventScript_Picker2', f'''OpotikiKiwifruitHouse_EventScript_Picker2::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x034, OpotikiKiwifruitHouse_EventScript_Picker2_Done
	msgbox OpotikiKiwifruitHouse_Text_Picker2, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_POTION, 1
	setflag FLAG_UNUSED_0x034
	goto_if_set {DF['WETA']}, OpotikiKiwifruitHouse_EventScript_Picker2_End
	msgbox OpotikiKiwifruitHouse_Text_WetaJob, MSGBOX_DEFAULT
OpotikiKiwifruitHouse_EventScript_Picker2_End::
	release
	end
''')
replace_block('OpotikiKiwifruitHouse', 'OpotikiKiwifruitHouse_EventScript_Picker2_Done', f'''OpotikiKiwifruitHouse_EventScript_Picker2_Done::
	goto_if_set {DF['WETA']}, OpotikiKiwifruitHouse_EventScript_Picker2_After
	msgbox OpotikiKiwifruitHouse_Text_WetaJob, MSGBOX_DEFAULT
	release
	end

OpotikiKiwifruitHouse_EventScript_Picker2_After::
	msgbox OpotikiKiwifruitHouse_Text_Picker2_After, MSGBOX_DEFAULT
	release
	end
''')
asm('OpotikiKiwifruitHouse', f'''@ Opotiki: the weta in the smoko room (scripted wild Pinsir); done {DF['WETA']}
OpotikiKiwifruitHouse_EventScript_Weta::
	lock
	faceplayer
	playmoncry SPECIES_PINSIR, CRY_MODE_ENCOUNTER
	msgbox OpotikiKiwifruitHouse_Text_WetaHiss, MSGBOX_DEFAULT
	waitmoncry
	setwildbattle SPECIES_PINSIR, 17
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, OpotikiKiwifruitHouse_Weta_Gone
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, OpotikiKiwifruitHouse_Weta_Gone
	msgbox OpotikiKiwifruitHouse_Text_WetaStill, MSGBOX_DEFAULT
	release
	end

OpotikiKiwifruitHouse_Weta_Gone::
	setflag {DF['WETA']}
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox OpotikiKiwifruitHouse_Text_WetaThanks, MSGBOX_DEFAULT
{give('ITEM_REVIVE', 2, 'OpotikiKiwifruitHouse_Weta_End')}OpotikiKiwifruitHouse_Weta_End::
	release
	end
''' + text('OpotikiKiwifruitHouse_Text_WetaJob', '''
Oh, and if you're brave: there's
a weta the size of my forearm in
the smoko room.

Nobody's had a cuppa in three
days. Morale is low.''') + text('OpotikiKiwifruitHouse_Text_WetaHiss', '''
The giant weta rears up and
rasps its spiny legs together!''') + text('OpotikiKiwifruitHouse_Text_WetaStill', '''
The weta settles back onto the
biscuit tin. It considers the
room its own.''') + text('OpotikiKiwifruitHouse_Text_WetaThanks', '''
Picker: The smoko room is ours
again! Somebody put the jug on!

Here, take these. You'd be
amazed what we need them for
in picking season.'''))

# --- Job 21: Mauao at Dawn (Tauranga, mornings) ---------------------------
replace_block('Tauranga', 'Tauranga_EventScript_MauaoMan', f'''Tauranga_EventScript_MauaoMan::
	lock
	faceplayer
	goto_if_set {DF['MAUAO']}, Tauranga_MauaoJob_Done
	msgbox Tauranga_Text_MauaoMan, MSGBOX_DEFAULT
	gettimeofday
	goto_if_ne VAR_0x8000, 0, Tauranga_MauaoJob_NotYet
	msgbox Tauranga_Text_MauaoJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Tauranga_MauaoJob_No
	fadescreen FADE_TO_BLACK
	msgbox Tauranga_Text_MauaoJobClimb, MSGBOX_DEFAULT
	fadescreen FADE_FROM_BLACK
	msgbox Tauranga_Text_MauaoJobThanks, MSGBOX_DEFAULT
{give('ITEM_DAWN_STONE', full='Tauranga_MauaoJob_Full')}	setflag {DF['MAUAO']}
Tauranga_MauaoJob_Full::
	release
	end
''')
asm('Tauranga', f'''@ Job 21: Mauao at Dawn - walk the old man up for the sunrise; done {DF['MAUAO']}
Tauranga_MauaoJob_NotYet::
	msgbox Tauranga_Text_MauaoJobNotYet, MSGBOX_DEFAULT
	release
	end

Tauranga_MauaoJob_No::
	msgbox Tauranga_Text_MauaoJobNo, MSGBOX_DEFAULT
	release
	end

Tauranga_MauaoJob_Done::
	msgbox Tauranga_Text_MauaoJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('Tauranga_Text_MauaoJobNotYet', '''
I walk up him every morning to
see the dawn he missed. My legs
aren't what they were.

If you're about at first light,
come find me. I'd like the
company.''') + text('Tauranga_Text_MauaoJobAsk', '''
It's nearly dawn. Walk up with
me? Slowly, mind.''') + text('Tauranga_Text_MauaoJobClimb', '''
You climb together, one slow
switchback at a time.

At the summit the sun lifts out
of the sea, and the whole
harbour turns gold.''') + text('Tauranga_Text_MauaoJobThanks', '''
There. He never got to see it,
so we see it for him.

Take this. It's the colour of
the first light, near enough.''') + text('Tauranga_Text_MauaoJobNo', '''
Another morning, then. He's been
waiting a long while. He can
wait one more.''') + text('Tauranga_Text_MauaoJobAfter', '''
Same sunrise every morning, and
never once the same. Thanks for
the walk.'''))

# --- Job 19: Pohutu at Dusk (Rotorua guide) -------------------------------
replace_block('RotoruaGuideHouse', 'RotoruaGuideHouse_EventScript_Guide', f'''RotoruaGuideHouse_EventScript_Guide::
	lock
	faceplayer
	goto_if_set {DF['GEYSER']}, RotoruaGuideHouse_GeyserJob_Done
	msgbox RotoruaGuideHouse_Text_Guide, MSGBOX_DEFAULT
	gettimeofday
	goto_if_lt VAR_0x8000, 2, RotoruaGuideHouse_GeyserJob_NotYet
	msgbox RotoruaGuideHouse_Text_GeyserJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RotoruaGuideHouse_GeyserJob_No
	fadescreen FADE_TO_BLACK
	playse SE_M_WHIRLPOOL
	msgbox RotoruaGuideHouse_Text_GeyserJobWatch, MSGBOX_DEFAULT
	fadescreen FADE_FROM_BLACK
	msgbox RotoruaGuideHouse_Text_GeyserJobThanks, MSGBOX_DEFAULT
{give('ITEM_MYSTIC_WATER', full='RotoruaGuideHouse_GeyserJob_Full')}	setflag {DF['GEYSER']}
RotoruaGuideHouse_GeyserJob_Full::
	release
	end
''')
asm('RotoruaGuideHouse', f'''@ Job 19: Pohutu at Dusk - the guide's evening walk; done {DF['GEYSER']}
RotoruaGuideHouse_GeyserJob_NotYet::
	msgbox RotoruaGuideHouse_Text_GeyserJobNotYet, MSGBOX_DEFAULT
	release
	end

RotoruaGuideHouse_GeyserJob_No::
	msgbox RotoruaGuideHouse_Text_GeyserJobNo, MSGBOX_DEFAULT
	release
	end

RotoruaGuideHouse_GeyserJob_Done::
	msgbox RotoruaGuideHouse_Text_GeyserJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('RotoruaGuideHouse_Text_GeyserJobNotYet', '''
If you want to see Pohutu at her
best, come back in the evening.
The tourists go home, and the
steam goes pink.''') + text('RotoruaGuideHouse_Text_GeyserJobAsk', '''
It's the right time now. Come on,
I'll walk you out to see her.''') + text('RotoruaGuideHouse_Text_GeyserJobWatch', '''
The ground hums. Then Pohutu
throws her water at the sky,
higher than the trees, pink in
the last of the light.''') + text('RotoruaGuideHouse_Text_GeyserJobThanks', '''
Every guide in my family has
stood right there and said
nothing. Now you have too.

Take this. Water that's been
somewhere, like you.''') + text('RotoruaGuideHouse_Text_GeyserJobNo', '''
She'll go without us. She
always does.''') + text('RotoruaGuideHouse_Text_GeyserJobAfter', '''
There is always somewhere to
lead people, even after the
wonder. You're proof.'''))

# --- Job 18: The Sprig at the Rock (Route 5, between Rotorua and Taupo) ---
add_obj('Route5', 'OBJ_EVENT_GFX_OLD_WOMAN', 12, 46, 'Route5_EventScript_ROCKJOB', 'LEFT')
asm('Route5', f'''@ Job 18: The Sprig at the Rock - leave green for safe passage; done {DF['ROCK']}
@ Rohe-specific (Te Arawa) - kept deliberately light; flagged for Ryan's review.
Route5_EventScript_ROCKJOB::
	lock
	faceplayer
	goto_if_set {DF['ROCK']}, Route5_RockJob_Done
	msgbox Route5_Text_RockJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route5_RockJob_No
	msgbox Route5_Text_RockJobLeave, MSGBOX_DEFAULT
	msgbox Route5_Text_RockJobThanks, MSGBOX_DEFAULT
{give('ITEM_BIG_ROOT', full='Route5_RockJob_Full')}	setflag {DF['ROCK']}
Route5_RockJob_Full::
	release
	end

Route5_RockJob_No::
	msgbox Route5_Text_RockJobNo, MSGBOX_DEFAULT
	release
	end

Route5_RockJob_Done::
	msgbox Route5_Text_RockJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('Route5_Text_RockJobAsk', '''
This is Hatupatu's rock. He hid
inside it once, and it kept him
safe.

Travellers leave a sprig of green
here as they pass. For him, and
for a safe road. Will you?''') + text('Route5_Text_RockJobLeave', '''
You pick a sprig of manuka from
the roadside and lay it at the
foot of the rock.''') + text('Route5_Text_RockJobThanks', '''
Ka pai. The road will remember
you did that, even if you
forget.

My moko found this by the rock.
I think it was meant for someone
travelling.''') + text('Route5_Text_RockJobNo', '''
No pressure, dear. The rock has
kept people safe a long time
without asking.''') + text('Route5_Text_RockJobAfter', '''
Haere ra. Safe road ahead.'''))

# --- Job 23: The Desert Road Convoy (Route 1 Desert) -----------------------
add_obj('Route1Desert', 'OBJ_EVENT_GFX_MAN_1', 3, 44, 'Route1Desert_EventScript_CONVOYJOB', 'RIGHT')
add_obj('Route1Desert', 'OBJ_EVENT_GFX_AQUA_MEMBER_M', 6, 47, 'Route1Desert_EventScript_TollDean', 'UP', trainer=True, sight=2)
add_obj('Route1Desert', 'OBJ_EVENT_GFX_AQUA_MEMBER_F', 9, 47, 'Route1Desert_EventScript_TollKasey', 'UP', trainer=True, sight=2)
asm('Route1Desert', f'''@ Job 23: The Desert Road Convoy - clear the Mob toll so the stock truck can pass; done {DF['CONVOY']}
Route1Desert_EventScript_CONVOYJOB::
	lock
	faceplayer
	goto_if_set {DF['CONVOY']}, Route1Desert_ConvoyJob_Done
	goto_if_not_defeated TRAINER_DESERT_TOLL_DEAN, Route1Desert_ConvoyJob_Blocked
	goto_if_not_defeated TRAINER_DESERT_TOLL_KASEY, Route1Desert_ConvoyJob_Blocked
	msgbox Route1Desert_Text_ConvoyJobThanks, MSGBOX_DEFAULT
{give('ITEM_MAX_POTION', 2, 'Route1Desert_ConvoyJob_Full')}	setflag {DF['CONVOY']}
Route1Desert_ConvoyJob_Full::
	release
	end

Route1Desert_ConvoyJob_Blocked::
	msgbox Route1Desert_Text_ConvoyJobBlocked, MSGBOX_DEFAULT
	release
	end

Route1Desert_ConvoyJob_Done::
	msgbox Route1Desert_Text_ConvoyJobAfter, MSGBOX_DEFAULT
	release
	end

Route1Desert_EventScript_TollDean::
	trainerbattle_single TRAINER_DESERT_TOLL_DEAN, Route1Desert_Text_DeanIntro, Route1Desert_Text_DeanDefeat
	msgbox Route1Desert_Text_DeanPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_EventScript_TollKasey::
	trainerbattle_single TRAINER_DESERT_TOLL_KASEY, Route1Desert_Text_KaseyIntro, Route1Desert_Text_KaseyDefeat
	msgbox Route1Desert_Text_KaseyPost, MSGBOX_AUTOCLOSE
	end
''' + text('Route1Desert_Text_ConvoyJobBlocked', '''
Trucker: Got a truck of stock
bound for Waiouru and two Mob
tollies wanting a cut to let me
through.

Some road. Some tax. If you can
talk to them in a language they
understand, I'd be grateful.''') + text('Route1Desert_Text_ConvoyJobThanks', '''
Trucker: Road's clear! The sheep
thank you. Well, they don't, but
I do.

Take these. The Desert Road eats
people who don't carry spares.''') + text('Route1Desert_Text_ConvoyJobAfter', '''
Trucker: Forty years on this
road. Snow in summer, sun in
winter, Mob in between.''') + text('Route1Desert_Text_DeanIntro', '''
Road toll. Not the government
kind. Ours is quicker.''') + text('Route1Desert_Text_DeanDefeat', '''
Fine. Waived. This once.''') + text('Route1Desert_Text_DeanPost', '''
The President doesn't know we
run this one. Keep it that way,
eh?''') + text('Route1Desert_Text_KaseyIntro', '''
Everyone pays on the Desert
Road. Pay in battles, pay in
bruises.''') + text('Route1Desert_Text_KaseyDefeat', '''
Okay, you've paid.''') + text('Route1Desert_Text_KaseyPost', '''
Wild horses out here don't pay
anyone. I'm starting to see the
appeal.'''))

# --- Job 24: The Wind Wand (Ngamotu) --------------------------------------
replace_block('NgamotuWindGallery', 'NgamotuWindGallery_EventScript_Kinetic',
              showme('NgamotuWindGallery', 'WINDJOB', DF['WIND'],
                     ['HOPPIP', 'SKIPLOOM', 'JUMPLUFF', 'COTTONEE', 'WHIMSICOTT'], {
    'Ask': '''
The Wind Wand out front bends but
never breaks. Kinetic art, they
call it.

I'm making a new piece. I want
to watch something that rides the
wind like the Wand does. Show me
one?''',
    'No': '''
The whole coast is kinetic art
if you ask me. Nothing here stands
still, not even the mountain.''',
    'Wrong': '''
Lovely, but that one fights the
wind. I need one that lets it
carry them.''',
    'Thanks': '''
Yes! Look how it gives in and
still gets where it's going.
That's the whole piece, right
there.

Here. A bit of the wind, kept
in a balloon. Don't ask how.''',
    'After': '''
The new piece is called "Letting
Go, Arriving Anyway". The council
hates the title. Perfect.''',
}, give('ITEM_AIR_BALLOON')).replace('NgamotuWindGallery_EventScript_WINDJOB::',
                                     'NgamotuWindGallery_EventScript_Kinetic::'))

# --- Job 25: The River Mail (Whanganui -> Wellington student flat) --------
replace_block('Whanganui', 'Whanganui_EventScript_RiverMan', f'''Whanganui_EventScript_RiverMan::
	lock
	faceplayer
	goto_if_set {DF['MAIL']}, Whanganui_MailJob_Done
	goto_if_set {HF['MAIL_CARRY']}, Whanganui_MailJob_Carrying
	msgbox Whanganui_Text_RiverMan, MSGBOX_DEFAULT
	msgbox Whanganui_Text_MailJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Whanganui_MailJob_No
	setflag {HF['MAIL_CARRY']}
	msgbox Whanganui_Text_MailJobGo, MSGBOX_DEFAULT
	release
	end
''')
asm('Whanganui', f'''@ Job 25: The River Mail - carry the letter to his moko in Wellington; done {DF['MAIL']}
Whanganui_MailJob_No::
	msgbox Whanganui_Text_MailJobNo, MSGBOX_DEFAULT
	release
	end

Whanganui_MailJob_Carrying::
	msgbox Whanganui_Text_MailJobCarrying, MSGBOX_DEFAULT
	release
	end

Whanganui_MailJob_Done::
	msgbox Whanganui_Text_MailJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('Whanganui_Text_MailJobAsk', '''
For a hundred years the
riverboats carried the mail up
and down this awa.

My moko is at university in
Wellington. Would you carry a
letter downriver for me?''') + text('Whanganui_Text_MailJobGo', '''
Tell him his koro says eat
properly and ring his mother.
He lives in a student flat, the
cold kind.''') + text('Whanganui_Text_MailJobNo', '''
All good. The awa is patient.''') + text('Whanganui_Text_MailJobCarrying', '''
My moko's in a student flat in
Wellington. The cold kind. You
can't miss it.''') + text('Whanganui_Text_MailJobAfter', '''
He rang his mother! Three whole
minutes. The river mail still
works miracles.'''))

# --- Job 26: Durie Hill (Whanganui) ---------------------------------------
add_obj('Whanganui', 'OBJ_EVENT_GFX_MAN_1', 16, 2, 'Whanganui_EventScript_DURIEJOB', 'DOWN')
add_hidden('Whanganui', 3, 3, 'ITEM_PEARL', HF['DURIE_1'])
add_hidden('Whanganui', 17, 8, 'ITEM_STARDUST', HF['DURIE_2'])
add_hidden('Whanganui', 8, 13, 'ITEM_HONEY', HF['DURIE_3'])
asm('Whanganui', f'''@ Job 26: Durie Hill - the lift operator's lost-and-found, and the Dowsing Machine; done {DF['DURIE']}
Whanganui_EventScript_DURIEJOB::
	lock
	faceplayer
	goto_if_set {DF['DURIE']}, Whanganui_DurieJob_Done
	goto_if_set {HF['DURIE_GIVEN']}, Whanganui_DurieJob_Check
	msgbox Whanganui_Text_DurieJobIntro, MSGBOX_DEFAULT
{give('ITEM_DOWSING_MACHINE', full='Whanganui_DurieJob_Full')}	setflag {HF['DURIE_GIVEN']}
	msgbox Whanganui_Text_DurieJobGo, MSGBOX_DEFAULT
	release
	end

Whanganui_DurieJob_Check::
	goto_if_unset {HF['DURIE_1']}, Whanganui_DurieJob_NotYet
	goto_if_unset {HF['DURIE_2']}, Whanganui_DurieJob_NotYet
	goto_if_unset {HF['DURIE_3']}, Whanganui_DurieJob_NotYet
	msgbox Whanganui_Text_DurieJobThanks, MSGBOX_DEFAULT
{give('ITEM_NUGGET', full='Whanganui_DurieJob_Full')}	setflag {DF['DURIE']}
Whanganui_DurieJob_Full::
	release
	end

Whanganui_DurieJob_NotYet::
	msgbox Whanganui_Text_DurieJobNotYet, MSGBOX_DEFAULT
	release
	end

Whanganui_DurieJob_Done::
	msgbox Whanganui_Text_DurieJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('Whanganui_Text_DurieJobIntro', '''
I run the Durie Hill lift. It
goes up through the inside of
the hill. Only one in the
country!

People drop things on the way
up. Three things this week alone.
Here, this beeps near buried
bits and bobs.''') + text('Whanganui_Text_DurieJobGo', '''
Have a poke around town. Bring
me word when you've found all
three.''') + text('Whanganui_Text_DurieJobNotYet', '''
Still some beeping to do, I
reckon. Three lost things.
Check round the edges of town.''') + text('Whanganui_Text_DurieJobThanks', '''
All three! You've got a nose
for it.

Keep that gadget. And take this.
Somebody left it in the lift in
1983 and never came back.''') + text('Whanganui_Text_DurieJobAfter', '''
Up through the hill and out the
top. Best view on the river.'''))

# --- Job 27: The Beehive Petition (Wellington, three signatures) ----------
replace_block('Wellington', 'Wellington_EventScript_BeehiveMan', f'''Wellington_EventScript_BeehiveMan::
	lock
	faceplayer
	goto_if_set {DF['PETITION']}, Wellington_PetitionJob_Done
	goto_if_set {HF['PET_HAVE']}, Wellington_PetitionJob_Check
	msgbox Wellington_Text_BeehiveMan, MSGBOX_DEFAULT
	msgbox Wellington_Text_PetitionJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wellington_PetitionJob_No
	setflag {HF['PET_HAVE']}
	msgbox Wellington_Text_PetitionJobGo, MSGBOX_DEFAULT
	release
	end
''')
asm('Wellington', f'''@ Job 27: The Beehive Petition - three signatures for a crossing; done {DF['PETITION']}
Wellington_PetitionJob_Check::
	goto_if_unset {HF['PET_SIGN_1']}, Wellington_PetitionJob_NotYet
	goto_if_unset {HF['PET_SIGN_2']}, Wellington_PetitionJob_NotYet
	goto_if_unset {HF['PET_SIGN_3']}, Wellington_PetitionJob_NotYet
	msgbox Wellington_Text_PetitionJobThanks, MSGBOX_DEFAULT
{give('ITEM_PP_UP', full='Wellington_PetitionJob_Full')}	setflag {DF['PETITION']}
Wellington_PetitionJob_Full::
	release
	end

Wellington_PetitionJob_No::
	msgbox Wellington_Text_PetitionJobNo, MSGBOX_DEFAULT
	release
	end

Wellington_PetitionJob_NotYet::
	msgbox Wellington_Text_PetitionJobNotYet, MSGBOX_DEFAULT
	release
	end

Wellington_PetitionJob_Done::
	msgbox Wellington_Text_PetitionJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('Wellington_Text_PetitionJobAsk', '''
I'm petitioning for a pedestrian
crossing outside the Beehive.
The people who make the rules
keep jaywalking.

I need three signatures from real
Wellingtonians. Will you collect
them?''') + text('Wellington_Text_PetitionJobGo', '''
Try the house by the cable car,
the cafe flat, and the students.
Wellingtonians love a petition
almost as much as a complaint.''') + text('Wellington_Text_PetitionJobNo', '''
Fair. Democracy is exhausting.
That's how you know it works.''') + text('Wellington_Text_PetitionJobNotYet', '''
Still short a signature or two.
Cable car house, cafe flat,
students. Go on.''') + text('Wellington_Text_PetitionJobThanks', '''
Three signatures! That's more
than the last three petitions
put together.

It'll go in the pile. The pile is
very important. Here, for your
trouble.''') + text('Wellington_Text_PetitionJobAfter', '''
They've agreed to "consider a
review of the crossing process".
In Wellington that's basically
a yes.'''))

replace_block('WellingtonCableHouse', 'WellingtonCableHouse_EventScript_Bureaucrat', f'''WellingtonCableHouse_EventScript_Bureaucrat::
	lock
	faceplayer
	goto_if_unset {HF['PET_HAVE']}, WellingtonCableHouse_Bureaucrat_Normal
	goto_if_set {HF['PET_SIGN_1']}, WellingtonCableHouse_Bureaucrat_Normal
	msgbox WellingtonCableHouse_Text_BureaucratSign, MSGBOX_DEFAULT
	setflag {HF['PET_SIGN_1']}
	release
	end

WellingtonCableHouse_Bureaucrat_Normal::
	msgbox WellingtonCableHouse_Text_Bureaucrat, MSGBOX_DEFAULT
	release
	end
''')
asm('WellingtonCableHouse', text('WellingtonCableHouse_Text_BureaucratSign', '''
A petition? For a crossing?

...I drafted the policy that
removed the last one. Give it
here. I'll sign it. Footnote
and all.'''))

replace_block('WellingtonWindFlat', 'WellingtonWindFlat_EventScript_Barista', f'''WellingtonWindFlat_EventScript_Barista::
	lock
	faceplayer
	goto_if_unset {HF['PET_HAVE']}, WellingtonWindFlat_Barista_Normal
	goto_if_set {HF['PET_SIGN_2']}, WellingtonWindFlat_Barista_Normal
	msgbox WellingtonWindFlat_Text_BaristaSign, MSGBOX_DEFAULT
	setflag {HF['PET_SIGN_2']}
	release
	end

WellingtonWindFlat_Barista_Normal::
	goto_if_set FLAG_UNUSED_0x03A, WellingtonWindFlat_EventScript_Barista_Done
	msgbox WellingtonWindFlat_Text_Barista, MSGBOX_DEFAULT
	giveitem ITEM_ULTRA_BALL, 2
	setflag FLAG_UNUSED_0x03A
	release
	end
''')
asm('WellingtonWindFlat', text('WellingtonWindFlat_Text_BaristaSign', '''
A crossing outside the Beehive?
I'd sign that twice.

Half my customers are MPs and
none of them look before they
step off a kerb.'''))

# The student gets the river mail first, then the petition, then his usual line.
replace_block('WellingtonStudentFlat', 'WellingtonStudentFlat_EventScript_Student', f'''WellingtonStudentFlat_EventScript_Student::
	lock
	faceplayer
	goto_if_set {DF['MAIL']}, WellingtonStudentFlat_Student_Petition
	goto_if_unset {HF['MAIL_CARRY']}, WellingtonStudentFlat_Student_Petition
	msgbox WellingtonStudentFlat_Text_StudentMail, MSGBOX_DEFAULT
{give('ITEM_EXP_CANDY_M', 3, 'WellingtonStudentFlat_Student_End')}	setflag {DF['MAIL']}
	release
	end

WellingtonStudentFlat_Student_Petition::
	goto_if_unset {HF['PET_HAVE']}, WellingtonStudentFlat_Student_Normal
	goto_if_set {HF['PET_SIGN_3']}, WellingtonStudentFlat_Student_Normal
	msgbox WellingtonStudentFlat_Text_StudentSign, MSGBOX_DEFAULT
	setflag {HF['PET_SIGN_3']}
	release
	end

WellingtonStudentFlat_Student_Normal::
	msgbox WellingtonStudentFlat_Text_Student, MSGBOX_DEFAULT
WellingtonStudentFlat_Student_End::
	release
	end
''')
asm('WellingtonStudentFlat', text('WellingtonStudentFlat_Text_StudentMail', '''
A letter? From Koro? Up the
river?

"Eat properly and ring your
mother." ...Yeah. Yeah, fair.

Here, have these. They're my
study snacks. Koro would want
you fed too.''') + text('WellingtonStudentFlat_Text_StudentSign', '''
A petition! I have never not
signed a petition. Gerald the
mould would sign too if he had
hands.'''))

# --- Job 31: The MetService Forecaster (Wellington) - gives Castform ------
replace_block('Wellington', 'Wellington_EventScript_WindWoman',
              showme('Wellington', 'METJOB', DF['METSERVICE'], ('TYPE', 'TYPE_FLYING'), {
    'Ask': '''
You can't lean on the wind here,
exactly. I forecast it, up at
MetService on the hill.

The birds always know before my
models do. Show me a flier, and
let me see which way it faces?''',
    'No': '''
But you can trust the wind to
catch you. Usually.''',
    'Wrong': '''
That one doesn't read the sky.
I need something with wings.''',
    'Thanks': '''
Nose into the southerly. Change
by tonight, then. Better than my
model.

We raise these at MetService.
This one's been itching to see
more weather than Wellington.
Take it.''',
    'After': '''
My forecast now has a footnote:
"consult a bird". The boss
thinks I'm joking.''',
}, givemon_block('SPECIES_CASTFORM', 25, 'Castform')).replace(
    'Wellington_EventScript_METJOB::', 'Wellington_EventScript_WindWoman::'))
asm('Wellington', 'gText_Pounamu_ReceivedCastform:\n\t.string "{PLAYER} received Castform!$"\n')

# --- Job 33: Te Araroa (Wellington) - steps walked -------------------------
add_obj('Wellington', 'OBJ_EVENT_GFX_HIKER', 10, 3, 'Wellington_EventScript_TRAMPJOB', 'DOWN')
asm('Wellington', f'''@ Job 33: Te Araroa - 15,000 steps on the motu; done {DF['TRAMP']}
Wellington_EventScript_TRAMPJOB::
	lock
	faceplayer
	goto_if_set {DF['TRAMP']}, Wellington_TrampJob_Done
	setvar VAR_0x8005, 150
	specialvar VAR_RESULT, ScriptCheckStepsWalked
	goto_if_eq VAR_RESULT, FALSE, Wellington_TrampJob_NotYet
	msgbox Wellington_Text_TrampJobThanks, MSGBOX_DEFAULT
{give('ITEM_EXP_CANDY_L', 2, 'Wellington_TrampJob_Full')}	setflag {DF['TRAMP']}
Wellington_TrampJob_Full::
	release
	end

Wellington_TrampJob_NotYet::
	msgbox Wellington_Text_TrampJobNotYet, MSGBOX_DEFAULT
	release
	end

Wellington_TrampJob_Done::
	msgbox Wellington_Text_TrampJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('Wellington_Text_TrampJobNotYet', '''
Walking Te Araroa. Cape Reinga to
Bluff, one foot at a time. I'm
about halfway.

Let's see your boots. Hmm, not
enough road in them yet. Come
back when you've walked 15,000
steps across the motu.''') + text('Wellington_Text_TrampJobThanks', '''
Let's see your boots. Oh, now
THOSE have some road in them.
15,000 steps at least.

You're a tramper, whether you
meant to be or not. Here, trail
food. Well, trail candy.''') + text('Wellington_Text_TrampJobAfter', '''
See you in Bluff, maybe. Or
maybe I'll just keep walking.'''))

# --- Job 30: The Picton Stowaway (Waitohi ferry cottage) ------------------
add_obj('WaitohiFerryCottage', 'OBJ_EVENT_GFX_SPECIES(MEOWTH_GALAR)', 8, 6,
        'WaitohiFerryCottage_EventScript_Stowaway', 'LEFT', flag=DF['STOWAWAY'])
replace_block('WaitohiFerryCottage', 'WaitohiFerryCottage_EventScript_FerryWatcher', f'''WaitohiFerryCottage_EventScript_FerryWatcher::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x03B, WaitohiFerryCottage_FerryWatcher_Gifted
	msgbox WaitohiFerryCottage_Text_FerryWatcher, MSGBOX_DEFAULT
	giveitem ITEM_FULL_HEAL, 1
	setflag FLAG_UNUSED_0x03B
WaitohiFerryCottage_FerryWatcher_Gifted::
	goto_if_set {DF['STOWAWAY']}, WaitohiFerryCottage_EventScript_FerryWatcher_Done
	msgbox WaitohiFerryCottage_Text_StowawayJob, MSGBOX_DEFAULT
	release
	end
''')
asm('WaitohiFerryCottage', f'''@ Job 30: The Picton Stowaway - the iron-clawed ship's cat; done {DF['STOWAWAY']}
WaitohiFerryCottage_EventScript_Stowaway::
	lock
	faceplayer
	playmoncry SPECIES_MEOWTH_GALAR, CRY_MODE_ENCOUNTER
	msgbox WaitohiFerryCottage_Text_StowawayHiss, MSGBOX_DEFAULT
	waitmoncry
	setwildbattle SPECIES_MEOWTH_GALAR, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, WaitohiFerryCottage_Stowaway_Gone
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, WaitohiFerryCottage_Stowaway_Gone
	msgbox WaitohiFerryCottage_Text_StowawayStill, MSGBOX_DEFAULT
	release
	end

WaitohiFerryCottage_Stowaway_Gone::
	setflag {DF['STOWAWAY']}
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox WaitohiFerryCottage_Text_StowawayThanks, MSGBOX_DEFAULT
{give('ITEM_METAL_COAT', full='WaitohiFerryCottage_Stowaway_End')}WaitohiFerryCottage_Stowaway_End::
	release
	end
''' + text('WaitohiFerryCottage_Text_StowawayJob', '''
Oh, and there's a stowaway in
here. Came off the last ferry
in a crate of spanners.

Iron claws. Won't leave. Eats
my toast. If you could have a
word with it...''') + text('WaitohiFerryCottage_Text_StowawayHiss', '''
The stowaway Meowth arches its
iron back and hisses!''') + text('WaitohiFerryCottage_Text_StowawayStill', '''
The Meowth goes back to guarding
the toast rack.''') + text('WaitohiFerryCottage_Text_StowawayThanks', '''
Ferry Watcher: My toast is
safe! The strait provides, and
the strait takes away.

It left this behind in the
spanner crate. Take it, it's
no use to a man with no
spanners.'''))

# ==========================================================================
#                                ACT 3
# ==========================================================================

# --- Job 36: The Cardboard Cathedral Concert (Otautahi) -------------------
replace_block('OtautahiCathedralFlat', 'OtautahiCathedralFlat_EventScript_ChoirKid',
              showme('OtautahiCathedralFlat', 'CONCERTJOB', DF['CONCERT'],
                     ['CHATOT', 'POPPLIO', 'BRIONNE', 'PRIMARINA'], {
    'Ask': '''
We sang in the cardboard
cathedral! It's REAL cardboard
and it's REALLY a cathedral!

Our soloist has a cold. Do you
have a Pokemon that can SING?
Show me!''',
    'No': '''
Dad says buildings are just songs
you can stand in. Ours needs a
new song!''',
    'Wrong': '''
Hmm, that one hums. We need a
singer!''',
    'Thanks': '''
It can sing! It can REALLY sing!
The choir will lose their minds.

Here, the choir leader gave me
this for our soloist. You have
it. Your Pokemon earned it!''',
    'After': '''
We sang it at the service. Dad
cried again. He's a very
reliable crier.''',
}, give('ITEM_THROAT_SPRAY')).replace('OtautahiCathedralFlat_EventScript_CONCERTJOB::',
                                      'OtautahiCathedralFlat_EventScript_ChoirKid::'))

# --- Job 41: The Lost Luggage (Route 1 South -> Otepoti porter) -----------
add_obj('Route1South', 'OBJ_EVENT_GFX_ITEM_BALL', 11, 33, 'Route1South_EventScript_Suitcase',
        'DOWN', flag=HF['SUITCASE'])
asm('Route1South', f'''@ Job 41: The Lost Luggage - the suitcase that fell off the train
Route1South_EventScript_Suitcase::
	lock
	msgbox Route1South_Text_Suitcase, MSGBOX_DEFAULT
	setflag {HF['SUITCASE']}
	removeobject VAR_LAST_TALKED
	release
	end
''' + text('Route1South_Text_Suitcase', '''
A battered suitcase, tagged for
the Dunedin railway station.

{PLAYER} picked it up to hand in
at Otepoti.'''))
add_obj('Otepoti', 'OBJ_EVENT_GFX_MAN_1', 30, 6, 'Otepoti_EventScript_LUGGAGEJOB', 'DOWN')
asm('Otepoti', f'''@ Job 41: The Lost Luggage - hand the suitcase to the station porter; done {DF['LUGGAGE']}
Otepoti_EventScript_LUGGAGEJOB::
	lock
	faceplayer
	goto_if_set {DF['LUGGAGE']}, Otepoti_LuggageJob_Done
	goto_if_unset {HF['SUITCASE']}, Otepoti_LuggageJob_Lost
	msgbox Otepoti_Text_LuggageJobThanks, MSGBOX_DEFAULT
{give('ITEM_BIG_NUGGET', full='Otepoti_LuggageJob_Full')}	setflag {DF['LUGGAGE']}
Otepoti_LuggageJob_Full::
	release
	end

Otepoti_LuggageJob_Lost::
	msgbox Otepoti_Text_LuggageJobLost, MSGBOX_DEFAULT
	release
	end

Otepoti_LuggageJob_Done::
	msgbox Otepoti_Text_LuggageJobAfter, MSGBOX_DEFAULT
	release
	end
''' + text('Otepoti_Text_LuggageJobLost', '''
Porter at the old railway
station. Fanciest station in the
country, and we still lose
things.

A suitcase bounced off the
excursion train up the line. If
you're walking the road north,
keep an eye out.''') + text('Otepoti_Text_LuggageJobThanks', '''
That's the one! Mrs Galbraith
will be thrilled. It's her
good cardigans.

She said to give the finder
this. She's very generous about
cardigans.''') + text('Otepoti_Text_LuggageJobAfter', '''
The station's over a hundred
years old. Everything else here
is students. It's a balance.'''))

# --- Job 42: The Paua Count (Otepoti) -------------------------------------
add_obj('Otepoti', 'OBJ_EVENT_GFX_FISHERMAN', 35, 17, 'Otepoti_EventScript_PAUAJOB', 'LEFT')
asm('Otepoti', showme('Otepoti', 'PAUAJOB', DF['PAUA'], ['SHELLDER', 'CLOYSTER'], {
    'Ask': '''
Diver: I count paua for the
fisheries lot. Numbers are down
round here.

Seen a healthy one on your
travels? Show me and cheer an
old diver up.''',
    'No': '''
Diver: No worries. I'll keep
counting. Somebody has to.''',
    'Wrong': '''
Diver: That's no paua, mate.
Paua shine blue and green
inside, like the sea at night.''',
    'Thanks': '''
Diver: Now THAT is a healthy
paua. Good shell, good colour.

Found this one in a rock pool
last winter. You have it. Give
my count a bit of hope.''',
    'After': '''
Diver: One healthy paua. It's
a start. Everything is, down
here.''',
}, give('ITEM_BIG_PEARL')))

# --- Job 43: The Track Master (Route 7, Lewis Pass) -----------------------
add_obj('Route7', 'OBJ_EVENT_GFX_EXPERT_F', 12, 88, 'Route7_EventScript_TrackMaster', 'LEFT', trainer=True, sight=0)
asm('Route7', f'''@ Job 43: The Track Master - the ranger who has walked every Great Walk; done {DF['TRACK']}
Route7_EventScript_TrackMaster::
	trainerbattle_single TRAINER_TRACK_MASTER_HEATHER, Route7_Text_HeatherIntro, Route7_Text_HeatherDefeat, Route7_EventScript_HeatherBeaten
	msgbox Route7_Text_HeatherPost, MSGBOX_AUTOCLOSE
	end

Route7_EventScript_HeatherBeaten::
	msgbox Route7_Text_HeatherReward, MSGBOX_DEFAULT
{give('ITEM_ABILITY_CAPSULE', full='Route7_Heather_Full')}	setflag {DF['TRACK']}
Route7_Heather_Full::
	release
	end
''' + text('Route7_Text_HeatherIntro', '''
Heather: DOC ranger. I've walked
every Great Walk in the motu,
twice, and the Milford Track
three times.

I only battle people who've
walked further than their gym
badges. Let's find out.''') + text('Route7_Text_HeatherDefeat', '''
Heather: Well walked.''') + text('Route7_Text_HeatherReward', '''
Heather: You've got legs and a
head. Rare combination on the
passes.

Take this. It changes how a
Pokemon carries itself. So do
long roads.''') + text('Route7_Text_HeatherPost', '''
Heather: The kea stole my lunch
again. Twice this week. They're
smarter than the walkers.'''))

# --- Tamaki: The Harbour Watch Log ----------------------------------------
replace_block('TamakiHarbourWatch', 'TamakiHarbourWatch_EventScript_HarbourMaster',
              showme('TamakiHarbourWatch', 'WHALEJOB', DF['WHALE'], ['WAILMER', 'WAILORD'], {
    'Ask': '''
Harbour watch. Twenty berths, two
hundred stories.

Some nights a shape crosses the
harbour mouth. Too big for a
boat. The log says "seal". The log
is a coward.

Show me a whale, and I'll finally
write the truth in it.''',
    'No': '''
Then the log stays a coward
another night.''',
    'Wrong': '''
Not big enough to be my shape.
Not by a long way.''',
    'Thanks': '''
That's it. That's the shape.
Whales in the gulf, right under
the Harbour Bridge.

The log now says "whale". Here,
with the harbour's thanks.''',
    'After': '''
The log says "whale" now. Best
entry I've ever written.''',
}, give('ITEM_WAVE_INCENSE')).replace('TamakiHarbourWatch_EventScript_WHALEJOB::',
                                      'TamakiHarbourWatch_EventScript_HarbourMaster::'))

# ==========================================================================
#                                trainers
# ==========================================================================
TRAINERS = [
    ('TRAINER_WHARF_JAYDEN', 'Jayden', 'Team Aqua', 'Aqua Grunt M', 'Male', 'Aqua',
     [('Rattata-Alola', 10), ('Wingull', 10)]),
    ('TRAINER_WHARF_SKYE', 'Skye', 'Team Aqua', 'Aqua Grunt F', 'Female', 'Aqua',
     [('Rattata-Alola', 11), ('Corphish', 11)]),
    ('TRAINER_WHARF_BRAX', 'Brax', 'Team Aqua', 'Aqua Grunt M', 'Male', 'Aqua',
     [('Rattata-Alola', 12), ('Poochyena', 12), ('Corphish', 13)]),
    ('TRAINER_DESERT_TOLL_DEAN', 'Dean', 'Team Aqua', 'Aqua Grunt M', 'Male', 'Aqua',
     [('Koffing', 23), ('Mightyena', 24)]),
    ('TRAINER_DESERT_TOLL_KASEY', 'Kasey', 'Team Aqua', 'Aqua Grunt F', 'Female', 'Aqua',
     [('Mudbray', 24), ('Sandygast', 25)]),
    ('TRAINER_TRACK_MASTER_HEATHER', 'Heather', 'Expert', 'Expert F', 'Female', 'Female',
     [('Stantler', 35), ('Skarmory', 36), ('Sliggoo', 36), ('Weavile', 37)]),
]

# ==========================================================================
#                                apply
# ==========================================================================
def main():
    for m in set(list(SCRIPTS) + [k[0] for k in REPLACE]):
        s = open(mpath(m, 'scripts.inc')).read()
        if MARK in s:
            raise SystemExit(f'{m}: batch already applied')

    # 1. replace blocks
    for (m, label), body in REPLACE.items():
        p = mpath(m, 'scripts.inc')
        s = open(p).read()
        pat = re.compile(r'^' + re.escape(label) + r'::\n.*?^\tend\n', re.S | re.M)
        if not pat.search(s):
            raise SystemExit(f'{m}: label {label} not found')
        s = pat.sub(lambda _: body.rstrip('\n') + '\n', s, count=1)
        open(p, 'w').write(s)

    # 2. append new scripts
    for m, body in SCRIPTS.items():
        p = mpath(m, 'scripts.inc')
        s = open(p).read().rstrip('\n')
        open(p, 'w').write(s + '\n\n' + MARK + ' (2026-09-26) ----\n' + body)

    # 3. maps
    for m, j in MAPS.items():
        open(mpath(m, 'map.json'), 'w').write(json.dumps(j, indent=2, ensure_ascii=False) + '\n')

    # 4. trainers
    opp = os.path.join(ROOT, 'include/constants/opponents.h')
    o = open(opp).read()
    base = int(re.search(r'#define TRAINERS_COUNT_EMERALD\s+(\d+)', o).group(1))
    defs = ''.join(f'#define {t[0]:<36}{base + i}\n' for i, t in enumerate(TRAINERS))
    o = re.sub(r'(\n)(\n#define TRAINERS_COUNT_EMERALD\s+)\d+',
               lambda mm: '\n' + defs + mm.group(2) + str(base + len(TRAINERS)), o, count=1)
    open(opp, 'w').write(o)
    party = os.path.join(ROOT, 'src/data/trainers.party')
    blocks = []
    for tid, name, cls, pic, gender, music, mons in TRAINERS:
        b = [f'=== {tid} ===', f'Name: {name}', f'Class: {cls}', f'Pic: {pic}',
             f'Gender: {gender}', f'Music: {music}', 'Double Battle: No', 'AI: Check Bad Move', '']
        for sp, lv in mons:
            b += [sp, f'Level: {lv}', '']
        blocks.append('\n'.join(b))
    s = open(party).read().rstrip('\n')
    open(party, 'w').write(s + '\n\n' + '\n'.join(blocks).rstrip('\n') + '\n')

    # 5. deco var name
    vp = os.path.join(ROOT, 'include/constants/vars.h')
    v = open(vp).read()
    v = v.replace('#define VAR_UNUSED_0x40FA                                0x40FA // Unused Var',
                  '#define VAR_POUNAMU_DECO_STATE                           0x40FA // Pounamu Job 09: deco deliveries (0 none, 1-3 stops, 4 back to Kiri)')
    if 'VAR_POUNAMU_DECO_STATE' not in v:
        raise SystemExit('could not claim 0x40F8')
    open(vp, 'w').write(v)

    # 6. job counter
    fs = os.path.join(ROOT, 'src/field_specials.c')
    c = open(fs).read()
    names = {'DECO': 'Deco Deliveries (Ahuriri)', 'WHARF': 'The Wharf Rats (Ahuriri)',
             'HOOKS': 'Hooks and Lines (Ahuriri)', 'EGG': 'Eggs in the Shelterbelt (Heretaunga)',
             'SLIP': 'The Slip Watch (Heretaunga)', 'LIGHT': 'A Light That Walks (Wairoa)',
             'DAWN': 'Hikurangi First Light (Route 35A)', 'WETA': 'The Weta in the Smoko Room (Opotiki)',
             'MAUAO': 'Mauao at Dawn (Tauranga)', 'GEYSER': 'Pohutu at Dusk (Rotorua)',
             'ROCK': "The Sprig at Hatupatu's Rock (Route 5)", 'CONVOY': 'The Desert Road Convoy',
             'WIND': 'The Wind Wand (Ngamotu)', 'MAIL': 'The River Mail (Whanganui)',
             'DURIE': 'Durie Hill (Whanganui)', 'PETITION': 'The Beehive Petition (Wellington)',
             'METSERVICE': 'The MetService Forecaster (Wellington)', 'TRAMP': 'Te Araroa (Wellington)',
             'STOWAWAY': 'The Picton Stowaway (Waitohi)', 'CONCERT': 'The Cathedral Concert (Otautahi)',
             'LUGGAGE': 'The Lost Luggage (Otepoti)', 'PAUA': 'The Paua Count (Otepoti)',
             'TRACK': 'The Track Master (Lewis Pass)', 'WHALE': 'The Harbour Watch Log (Tamaki)'}
    add = '    FLAG_UNUSED_0x272, // The Pounamu Trail: all 12 shards carved (job 08)\n' + ''.join(
        f'    {DF[k]}, // {names[k]}\n' for k in F)
    c = c.replace('    FLAG_UNUSED_0x29E, // The Parcel (Ahuriri)\n};',
                  '    FLAG_UNUSED_0x29E, // The Parcel (Ahuriri)\n' + add + '};')
    if names['WHALE'] not in c:
        raise SystemExit('counter table not found')
    c = c.replace('for (i = 1; i < 1107; i++)', 'for (i = 1; i < TRAINERS_COUNT; i++)')
    open(fs, 'w').write(c)

    # 7. wild: ship rats on the port road (dex: Rattata, "everywhere, introduced")
    wp = os.path.join(ROOT, 'src/data/wild_encounters.json')
    w = open(wp).read()
    old = '{"min_level": 4, "max_level": 6, "species": "SPECIES_WEEDLE"}'
    wj = json.loads(w)
    done = False
    for grp in wj['wild_encounter_groups']:
        for e in grp['encounters']:
            if e.get('map') == 'MAP_ROUTE2_BAY':
                for mon in e['land_mons']['mons']:
                    if mon['species'] == 'SPECIES_WEEDLE':
                        mon['species'] = 'SPECIES_RATTATA_ALOLA'
                        done = True
    if not done:
        raise SystemExit('Route2Bay Weedle slot not found')
    open(wp, 'w').write(json.dumps(wj, indent=2, ensure_ascii=False) + '\n')
    print('applied: %d jobs, %d trainers, maps touched: %s' % (len(F), len(TRAINERS),
          ', '.join(sorted(set(list(SCRIPTS) + [k[0] for k in REPLACE])))))

if __name__ == '__main__':
    main()
