Wellington_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Wellington_OnTransition
	.byte 0

Wellington_OnTransition::
	goto_if_set FLAG_UNUSED_0x04A, Wellington_OnTransition_HideStrait
	goto_if_set FLAG_BADGE05_GET, Wellington_OnTransition_ShowStrait
	goto Wellington_OnTransition_HideStrait

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
	msgbox Wellington_Text_BeehiveMan, MSGBOX_NPC
	end
Wellington_EventScript_WindWoman::
	msgbox Wellington_Text_WindWoman, MSGBOX_NPC
	end
Wellington_EventScript_FerryMan::
	msgbox Wellington_Text_FerryMan, MSGBOX_NPC
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
	msgbox Wellington_Text_FerrySign, MSGBOX_SIGN
	end

Wellington_Text_GymKid:
	.string "Leader Manu reads the wind like\n"
	.string "a book.\p"
	.string "In this town, that's not a\n"
	.string "hobby. It's survival.\p"
	.string "…Gym's closed for now, but.$"
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
Wellington_Text_CafeKid:
	.string "Six cafes on one block! I've\n"
	.string "had four hot chocolates.\p"
	.string "I can HEAR colours!$"
Wellington_Text_GymSign:
	.string "TE WHANGANUI-A-TARA GYM\n"
	.string "Leader: MANU - rides the gale.\p"
	.string "“Back when the wind allows.”\p"
	.string "(Gym 5 opens in a later build!)$"
Wellington_Text_BeehiveSign:
	.string "THE BEEHIVE\p"
	.string "“Where the motu makes its\n"
	.string "promises.” Some are even kept.$"
Wellington_Text_FerrySign:
	.string "INTERISLANDER - COOK STRAIT\p"
	.string "SAILINGS SUSPENDED.\p"
	.string "A second notice, newer:\n"
	.string "“By order. Bay business.”\p"
	.string "(The South Island opens in a\n"
	.string "later build - the ferry is your\l"
	.string "door across.)$"

@ ---- Ferry north: Tamaki Makaurau (post-Choice) ----
Wellington_EventScript_TamakiFerry::
	lock
	faceplayer
	goto_if_unset FLAG_UNUSED_0x903, Wellington_EventScript_TamakiFerryClosed
	msgbox Wellington_Text_TamakiFerry, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wellington_EventScript_TamakiFerryNo
	closemessage
	warp MAP_TAMAKI_MAKAURAU, 53, 33
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
