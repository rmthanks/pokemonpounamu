Wellington_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Wellington_OnTransition
	.byte 0

Wellington_OnTransition::
	setflag FLAG_VISITED_SOOTOPOLIS_CITY
	call_if_set FLAG_BADGE05_GET, Wellington_EventScript_FerryManAside
	goto_if_set FLAG_UNUSED_0x04A, Wellington_OnTransition_HideStrait
	goto_if_set FLAG_BADGE05_GET, Wellington_OnTransition_ShowStrait
	goto Wellington_OnTransition_HideStrait

@ The ferryman keeps the terminal doors until Manu's badge is won; then he stands aside
@ and the ramp is Tama's until the strait scene resolves.
Wellington_EventScript_FerryManAside::
	setobjectxyperm 4, 24, 29
	return

Wellington_OnTransition_ShowStrait::
	clearflag FLAG_UNUSED_0x04B
	end

Wellington_OnTransition_HideStrait::
	setflag FLAG_UNUSED_0x04B
	end
Wellington_EventScript_GymKid::
	msgbox Wellington_Text_GymKid, MSGBOX_NPC
	end
Wellington_EventScript_BeehiveMan::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x295, Wellington_PetitionJob_Done
	goto_if_set FLAG_UNUSED_0x4B6, Wellington_PetitionJob_Check
	msgbox Wellington_Text_BeehiveMan, MSGBOX_DEFAULT
	msgbox Wellington_Text_PetitionJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wellington_PetitionJob_No
	setflag FLAG_UNUSED_0x4B6
	msgbox Wellington_Text_PetitionJobGo, MSGBOX_DEFAULT
	release
	end
Wellington_EventScript_WindWoman::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x298, Wellington_METJOB_Done
	msgbox Wellington_Text_METJOBAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wellington_METJOB_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Wellington_METJOB_No
	setvar VAR_0x8005, TYPE_FLYING
	specialvar VAR_RESULT, ScriptPartyMonHasType
	goto_if_eq VAR_RESULT, TRUE, Wellington_METJOB_Good
	msgbox Wellington_Text_METJOBWrong, MSGBOX_DEFAULT
	release
	end

Wellington_METJOB_Good::
	msgbox Wellington_Text_METJOBThanks, MSGBOX_DEFAULT
	givemon SPECIES_CASTFORM, 25
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Wellington_METJOB_Full
	playfanfare MUS_OBTAIN_ITEM
	message gText_Pounamu_ReceivedCastform
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	setflag FLAG_UNUSED_0x298
	release
	end

Wellington_METJOB_No::
	msgbox Wellington_Text_METJOBNo, MSGBOX_DEFAULT
	release
	end

Wellington_METJOB_Full::
	release
	end

Wellington_METJOB_Done::
	msgbox Wellington_Text_METJOBAfter, MSGBOX_DEFAULT
	release
	end

Wellington_Text_METJOBAsk:
	.string "You can't lean on the wind\n"
	.string "here, exactly. I forecast it,\l"
	.string "up at MetService on the hill.\p"
	.string "The birds always know before my\n"
	.string "models do. Show me a flier, and\l"
	.string "let me see which way it faces?$"

Wellington_Text_METJOBNo:
	.string "But you can trust the wind to\n"
	.string "catch you. Usually.$"

Wellington_Text_METJOBWrong:
	.string "That one doesn't read the sky.\n"
	.string "I need something with wings.$"

Wellington_Text_METJOBThanks:
	.string "Nose into the southerly. Change\n"
	.string "by tonight, then. Better than\l"
	.string "my model.\p"
	.string "We raise these at MetService.\n"
	.string "This one's been itching to see\l"
	.string "more weather than Wellington.\l"
	.string "Take it.$"

Wellington_Text_METJOBAfter:
	.string "My forecast now has a footnote:\n"
	.string "“consult a bird”. The boss\l"
	.string "thinks I'm joking.$"
Wellington_EventScript_FerryMan::
	goto_if_set FLAG_UNUSED_0x04A, Wellington_EventScript_FerryManOpen
	msgbox Wellington_Text_FerryMan, MSGBOX_NPC
	end

Wellington_EventScript_FerryManOpen::
	msgbox Wellington_Text_FerryManOpen, MSGBOX_NPC
	end
Wellington_EventScript_CafeKid::
	msgbox Wellington_Text_CafeKid, MSGBOX_NPC
	end
Wellington_EventScript_GymSign::
	msgbox Wellington_Text_GymSign, MSGBOX_SIGN
	end
Wellington_EventScript_BeehiveSign::
	msgbox Wellington_Text_BeehiveSign, MSGBOX_SIGN
	end
Wellington_EventScript_FerrySign::
	goto_if_set FLAG_UNUSED_0x04A, Wellington_EventScript_FerrySignOpen
	msgbox Wellington_Text_FerrySign, MSGBOX_SIGN
	end

Wellington_EventScript_FerrySignOpen::
	msgbox Wellington_Text_FerrySignOpen, MSGBOX_SIGN
	end

Wellington_Text_GymKid:
	.string "Leader Manu reads the wind like\n"
	.string "a book.\p"
	.string "In this town, that's not a\n"
	.string "hobby. It's survival.$"
Wellington_Text_BeehiveMan:
	.string "That round building's where they\n"
	.string "make the rules for the whole\l"
	.string "motu.\p"
	.string "Shaped like a beehive. Make of\n"
	.string "that what you will.$"
Wellington_Text_WindWoman:
	.string "You can't lean on the wind here,\n"
	.string "exactly.\p"
	.string "But you can trust it to catch\n"
	.string "you. Usually.$"
Wellington_Text_FerryMan:
	.string "Ferry across the strait to the\n"
	.string "South Island.\p"
	.string "…Not running, though. Weather,\n"
	.string "they say. And 'other reasons.'\p"
	.string "The 'other reasons' wear\n"
	.string "matching jackets. You follow?$"

Wellington_Text_FerryManOpen:
	.string "Ferry's running again, e hoa.\n"
	.string "Through the doors behind me.$"
Wellington_Text_CafeKid:
	.string "Six cafes on one block! I've\n"
	.string "had four hot chocolates.\p"
	.string "I can HEAR colours!$"
Wellington_Text_GymSign:
	.string "TE WHANGANUI-A-TARA GYM\n"
	.string "Leader: MANU - rides the gale.\p"
	.string "“Back when the wind allows.”$"
Wellington_Text_BeehiveSign:
	.string "THE BEEHIVE\p"
	.string "“Where the motu makes its\n"
	.string "promises.” Some are even kept.$"
Wellington_Text_FerrySign:
	.string "INTERISLANDER - COOK STRAIT\p"
	.string "SAILINGS SUSPENDED.\p"
	.string "A second notice, newer:\n"
	.string "“By order. Bay business.”$"

Wellington_Text_FerrySignOpen:
	.string "INTERISLANDER - COOK STRAIT\p"
	.string "SAILINGS RESUMED.\p"
	.string "Someone has torn the second\n"
	.string "notice down.$"

@ ---- Ferry north: Tamaki Makaurau (post-Choice) ----
Wellington_EventScript_TamakiFerry::
	lock
	faceplayer
	goto_if_unset FLAG_UNUSED_0x903, Wellington_EventScript_TamakiFerryClosed
	msgbox Wellington_Text_TamakiFerry, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wellington_EventScript_TamakiFerryNo
	closemessage
	warp MAP_TAMAKI_MAKAURAU, 61, 39
	waitstate
	end

Wellington_EventScript_TamakiFerryClosed::
	msgbox Wellington_Text_TamakiFerryClosed, MSGBOX_DEFAULT
	release
	end

Wellington_EventScript_TamakiFerryNo::
	release
	end

Wellington_Text_TamakiFerryClosed:
	.string "Sailor: Tamaki? Nothing sails\n"
	.string "north right now, mate.\p"
	.string "Whole harbour up there answers\n"
	.string "to one tower, and the tower\l"
	.string "isn't taking visitors.$"

Wellington_Text_TamakiFerry:
	.string "Sailor: Tamaki Makaurau.\p"
	.string "…You're really going up there,\n"
	.string "carrying what you carry.\p"
	.string "One tower. One brother.\n"
	.string "…Board her?$"

@ ==================================================================
@ COOK STRAIT - Act 2 climax. "Blessed." Tama stands on the ferry
@ ramp itself: nobody crosses until this scene resolves.
@ ==================================================================
Wellington_EventScript_KauriStrait::
	lock
	faceplayer
	msgbox Wellington_Text_KauriBeside, MSGBOX_DEFAULT
	release
	end

Wellington_EventScript_TamaStrait::
	lock
	faceplayer
	msgbox Wellington_Text_StraitTama1, MSGBOX_DEFAULT
	msgbox Wellington_Text_StraitKauri1, MSGBOX_DEFAULT
	msgbox Wellington_Text_StraitTama2, MSGBOX_DEFAULT
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto_if_ne VAR_RESULT, 0, Wellington_EventScript_StraitBattle
	special LoadPlayerParty
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto Wellington_EventScript_StraitBattle

Wellington_EventScript_StraitBattle::
	multi_2_vs_1 TRAINER_TAMA_STRAIT, Wellington_Text_StraitTamaBattleEnd, PARTNER_KAURI
	special LoadPlayerParty
	special HealPlayerParty
	msgbox Wellington_Text_StraitDraw, MSGBOX_DEFAULT
	msgbox Wellington_Text_StraitOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Wellington_EventScript_StraitYes
	msgbox Wellington_Text_StraitRefuseNo, MSGBOX_DEFAULT
	goto Wellington_EventScript_StraitOutcome

Wellington_EventScript_StraitYes::
	msgbox Wellington_Text_StraitRefuseYes, MSGBOX_DEFAULT
	goto Wellington_EventScript_StraitOutcome

Wellington_EventScript_StraitOutcome::
	msgbox Wellington_Text_StraitTamaLeaves, MSGBOX_DEFAULT
	msgbox Wellington_Text_StraitWave, MSGBOX_DEFAULT
	msgbox Wellington_Text_StraitBlessing, MSGBOX_DEFAULT
	delay 40
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox Wellington_Text_HoOhCrossing, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x04A
	setflag FLAG_UNUSED_0x04B
	removeobject 7
	removeobject 8
	release
	end

Wellington_Text_KauriBeside:
	.string "Kauri: …Stay close, son.$"

Wellington_Text_StraitTama1:
	.string "Tama: Five badges.\p"
	.string "You've grown teeth, little\n"
	.string "brother.$"

Wellington_Text_StraitKauri1:
	.string "Kauri: …Son.$"

Wellington_Text_StraitTama2:
	.string "Tama: Don't.\p"
	.string "You lost the right to that\n"
	.string "word in Ahuriri.\p"
	.string "…Both of you, then. The old\n"
	.string "man and the runaway.\p"
	.string "Good. I've been wanting to\n"
	.string "count this properly.$"

Wellington_Text_StraitTamaBattleEnd:
	.string "…$"

Wellington_Text_StraitDraw:
	.string "Neither side is standing\n"
	.string "clean.\p"
	.string "For the first time in his\n"
	.string "life, Tama looks at you like\l"
	.string "arithmetic that stopped\l"
	.string "adding up.$"

Wellington_Text_StraitOffer:
	.string "Tama: …New sum, then.\p"
	.string "Come home. Rule the Bay beside\n"
	.string "me. Blood where blood belongs.\p"
	.string "One condition.\p"
	.string "The orchard gets a new tenant.\p"
	.string "Mum goes.\p"
	.string "Well?$"

Wellington_Text_StraitRefuseNo:
	.string "You said no with your whole\n"
	.string "chest.$"

Wellington_Text_StraitRefuseYes:
	.string "Your hand hovers…\p"
	.string "…and drops.\p"
	.string "Some words refuse to be said.\p"
	.string "…No.$"

Wellington_Text_StraitTamaLeaves:
	.string "Tama: …Twice.\p"
	.string "Twice now my family has picked\n"
	.string "the door over me.\p"
	.string "Keep your south, little\n"
	.string "brother. Climb your mountains.\p"
	.string "The tower will be mine.$"

Wellington_Text_StraitWave:
	.string "You raise your hand.\p"
	.string "His fingers curl.\p"
	.string "His hand stays at his side.\p"
	.string "He crosses the terminal\n"
	.string "without looking back.$"

Wellington_Text_StraitBlessing:
	.string "Kauri: …She's still growing\n"
	.string "things? Your mother?\p"
	.string "…Course she is.\p"
	.string "Go on, son. Cross the water.\n"
	.string "Finish becoming whoever it is\l"
	.string "you are.\p"
	.string "I'll hold the strait.$"

@ ------------------------------------------------------------------
@ Hori, the Mob's least effective grunt. He wants your shoes.
@ ------------------------------------------------------------------
Wellington_EventScript_Hori::
	lock
	faceplayer
	trainerbattle_single TRAINER_HORI_4, Wellington_Text_HoriIntro, Wellington_Text_HoriDefeat, Wellington_EventScript_HoriBeaten
	release
	end

Wellington_EventScript_HoriBeaten::
	msgbox Wellington_Text_HoriAfter, MSGBOX_DEFAULT
	closemessage
	playse SE_FLEE
	removeobject 9
	setflag FLAG_UNUSED_0x276
	release
	end

Wellington_Text_HoriIntro:
	.string "Windy, eh? Good weather for\n"
	.string "TAKING SHOES.\p"
	.string "No more mister one-on-one.\p"
	.string "I'll step you and ALL your\n"
	.string "Pokémon out for your shoes.$"

Wellington_Text_HoriDefeat:
	.string "Stepped out… by meself…$"

Wellington_Text_HoriAfter:
	.string "Every time. EVERY time.\p"
	.string "…You're headed south, aren't ya.\n"
	.string "Across the strait.\p"
	.string "I'll be there. With a plan.\n"
	.string "And a beanie.$"

Wellington_Text_HoOhCrossing:
	.string "Far out over the strait, colour\n"
	.string "flares through the spray -\p"
	.string "a bird like a bonfire, riding\n"
	.string "the southerly down the world.\p"
	.string "Gone before you can name it.\p"
	.string "The water it crossed keeps\n"
	.string "glittering a while.$"

Wellington_EventScript_PNgahuia::
	trainerbattle_single TRAINER_WLT_NGAHUIA, Wellington_Text_PNgahuiaIntro, Wellington_Text_PNgahuiaDefeat
	msgbox Wellington_Text_PNgahuiaPost, MSGBOX_AUTOCLOSE
	end

Wellington_Text_PNgahuiaIntro:
	.string "Ngahuia: Oi! You walked into my line\nof sight. Them's the rules!$"

Wellington_Text_PNgahuiaDefeat:
	.string "Aw, heck!$"

Wellington_Text_PNgahuiaPost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"

Wellington_EventScript_POtene::
	trainerbattle_single TRAINER_WLT_OTENE, Wellington_Text_POteneIntro, Wellington_Text_POteneDefeat
	msgbox Wellington_Text_POtenePost, MSGBOX_AUTOCLOSE
	end

Wellington_Text_POteneIntro:
	.string "Otene: I train where the weather's\nworst. Makes us honest.$"

Wellington_Text_POteneDefeat:
	.string "Honestly beaten.$"

Wellington_Text_POtenePost:
	.string "Strength is showing up in\nthe rain.$"

Wellington_EventScript_PPaora::
	trainerbattle_single TRAINER_WLT_PAORA, Wellington_Text_PPaoraIntro, Wellington_Text_PPaoraDefeat
	msgbox Wellington_Text_PPaoraPost, MSGBOX_AUTOCLOSE
	end

Wellington_Text_PPaoraIntro:
	.string "Paora: My mokopuna says I'm out of\ndate. Let's test that.$"

Wellington_Text_PPaoraDefeat:
	.string "Tell no one.$"

Wellington_Text_PPaoraPost:
	.string "Old tricks are just good\ntricks that lasted.$"

Wellington_EventScript_PRangimarie::
	trainerbattle_single TRAINER_WLT_RANGIMARIE, Wellington_Text_PRangimarieIntro, Wellington_Text_PRangimarieDefeat
	msgbox Wellington_Text_PRangimariePost, MSGBOX_AUTOCLOSE
	end

Wellington_Text_PRangimarieIntro:
	.string "Rangimarie: Oi! You walked into my line\nof sight. Them's the rules!$"

Wellington_Text_PRangimarieDefeat:
	.string "Aw, heck!$"

Wellington_Text_PRangimariePost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"

Wellington_EventScript_PTamati::
	trainerbattle_single TRAINER_WLT_TAMATI, Wellington_Text_PTamatiIntro, Wellington_Text_PTamatiDefeat
	msgbox Wellington_Text_PTamatiPost, MSGBOX_AUTOCLOSE
	end

Wellington_Text_PTamatiIntro:
	.string "Tamati: This is protected land.\nProve you respect it.$"

Wellington_Text_PTamatiDefeat:
	.string "You fight like you care.$"

Wellington_Text_PTamatiPost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Wellington_EventScript_WLJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x2A4, Wellington_EventScript_WLJOB_Done
	msgbox Wellington_Text_WLJOBAsk, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Wellington_EventScript_WLJOB_Cancel
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_HOOTHOOT, Wellington_EventScript_WLJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_NOCTOWL, Wellington_EventScript_WLJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_ZUBAT, Wellington_EventScript_WLJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_GOLBAT, Wellington_EventScript_WLJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_CROBAT, Wellington_EventScript_WLJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_MURKROW, Wellington_EventScript_WLJOB_Good
	msgbox Wellington_Text_WLJOBWrong, MSGBOX_DEFAULT
	release
	end

Wellington_EventScript_WLJOB_Good::
	msgbox Wellington_Text_WLJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_MOON_STONE
	setflag FLAG_UNUSED_0x2A4
	release
	end

Wellington_EventScript_WLJOB_Cancel::
	release
	end

Wellington_EventScript_WLJOB_Done::
	msgbox Wellington_Text_WLJOBAfter, MSGBOX_DEFAULT
	release
	end

Wellington_Text_WLJOBAsk:
	.string "Warden: Night survey for the\nsanctuary - we count what flies\lafter dark.\pShow me a night-flier and\lyou're on the count.$"

Wellington_Text_WLJOBThanks:
	.string "Warden: Logged! The night shift\nthanks you.\pFound this on a survey. Moths\nlove it. You have it.$"

Wellington_Text_WLJOBWrong:
	.string "Warden: That one sleeps at\nnight, surely.$"

Wellington_Text_WLJOBAfter:
	.string "Ka pai. The board's been told.$"

@ ---- Mission batch S2 (2026-09-26) ----
@ Job 27: The Beehive Petition - three signatures for a crossing; done FLAG_UNUSED_0x295
Wellington_PetitionJob_Check::
	goto_if_unset FLAG_UNUSED_0x4B7, Wellington_PetitionJob_NotYet
	goto_if_unset FLAG_UNUSED_0x4B8, Wellington_PetitionJob_NotYet
	goto_if_unset FLAG_UNUSED_0x4B9, Wellington_PetitionJob_NotYet
	msgbox Wellington_Text_PetitionJobThanks, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP
	goto_if_eq VAR_RESULT, FALSE, Wellington_PetitionJob_Full
	setflag FLAG_UNUSED_0x295
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
Wellington_Text_PetitionJobAsk:
	.string "I'm petitioning for a\n"
	.string "pedestrian crossing outside the\l"
	.string "Beehive. The people who make\l"
	.string "the rules keep jaywalking.\p"
	.string "I need three signatures from\n"
	.string "real Wellingtonians. Will you\l"
	.string "collect them?$"
Wellington_Text_PetitionJobGo:
	.string "Try the house by the cable car,\n"
	.string "the cafe flat, and the\l"
	.string "students. Wellingtonians love a\l"
	.string "petition almost as much as a\l"
	.string "complaint.$"
Wellington_Text_PetitionJobNo:
	.string "Fair. Democracy is exhausting.\n"
	.string "That's how you know it works.$"
Wellington_Text_PetitionJobNotYet:
	.string "Still short a signature or two.\n"
	.string "Cable car house, cafe flat,\l"
	.string "students. Go on.$"
Wellington_Text_PetitionJobThanks:
	.string "Three signatures! That's more\n"
	.string "than the last three petitions\l"
	.string "put together.\p"
	.string "It'll go in the pile. The pile\n"
	.string "is very important. Here, for\l"
	.string "your trouble.$"
Wellington_Text_PetitionJobAfter:
	.string "They've agreed to “consider a\n"
	.string "review of the crossing\l"
	.string "process”. In Wellington that's\l"
	.string "basically a yes.$"

gText_Pounamu_ReceivedCastform:
	.string "{PLAYER} received Castform!$"

@ Job 33: Te Araroa - 15,000 steps on the motu; done FLAG_UNUSED_0x299
Wellington_EventScript_TRAMPJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x299, Wellington_TrampJob_Done
	setvar VAR_0x8005, 150
	specialvar VAR_RESULT, ScriptCheckStepsWalked
	goto_if_eq VAR_RESULT, FALSE, Wellington_TrampJob_NotYet
	msgbox Wellington_Text_TrampJobThanks, MSGBOX_DEFAULT
	giveitem ITEM_EXP_CANDY_L, 2
	goto_if_eq VAR_RESULT, FALSE, Wellington_TrampJob_Full
	setflag FLAG_UNUSED_0x299
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
Wellington_Text_TrampJobNotYet:
	.string "Walking Te Araroa. Cape Reinga\n"
	.string "to Bluff, one foot at a time.\l"
	.string "I'm about halfway.\p"
	.string "Let's see your boots. Hmm, not\n"
	.string "enough road in them yet. Come\l"
	.string "back when you've walked 15,000\l"
	.string "steps across the motu.$"
Wellington_Text_TrampJobThanks:
	.string "Let's see your boots. Oh, now\n"
	.string "THOSE have some road in them.\l"
	.string "15,000 steps at least.\p"
	.string "You're a tramper, whether you\n"
	.string "meant to be or not. Here, trail\l"
	.string "food. Well, trail candy.$"
Wellington_Text_TrampJobAfter:
	.string "See you in Bluff, maybe. Or\n"
	.string "maybe I'll just keep walking.$"

