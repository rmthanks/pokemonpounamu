OpotikiKiwifruitHouse_MapScripts::
	.byte 0

OpotikiKiwifruitHouse_EventScript_Picker2::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x034, OpotikiKiwifruitHouse_EventScript_Picker2_Done
	msgbox OpotikiKiwifruitHouse_Text_Picker2, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_POTION, 1
	setflag FLAG_UNUSED_0x034
	goto_if_set FLAG_UNUSED_0x28D, OpotikiKiwifruitHouse_EventScript_Picker2_End
	msgbox OpotikiKiwifruitHouse_Text_WetaJob, MSGBOX_DEFAULT
OpotikiKiwifruitHouse_EventScript_Picker2_End::
	release
	end

OpotikiKiwifruitHouse_EventScript_Picker2_Done::
	goto_if_set FLAG_UNUSED_0x28D, OpotikiKiwifruitHouse_EventScript_Picker2_After
	msgbox OpotikiKiwifruitHouse_Text_WetaJob, MSGBOX_DEFAULT
	release
	end

OpotikiKiwifruitHouse_EventScript_Picker2_After::
	msgbox OpotikiKiwifruitHouse_Text_Picker2_After, MSGBOX_DEFAULT
	release
	end

OpotikiKiwifruitHouse_Text_Picker2:
	.string "Kiwifruit season. My arms are\n"
	.string "noodles and my wallet's fat.\p"
	.string "You're doing the Cape road?\n"
	.string "Long and lonely, that one.\l"
	.string "Take this - you'll want it\l"
	.string "around Maraenui.$"

OpotikiKiwifruitHouse_Text_Picker2_After:
	.string "The Cape road doesn't get\n"
	.string "shorter. Kia kaha.$"

@ ---- Mission batch S2 (2026-09-26) ----
@ Opotiki: the weta in the smoko room (scripted wild Pinsir); done FLAG_UNUSED_0x28D
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
	setflag FLAG_UNUSED_0x28D
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox OpotikiKiwifruitHouse_Text_WetaThanks, MSGBOX_DEFAULT
	giveitem ITEM_REVIVE, 2
	goto_if_eq VAR_RESULT, FALSE, OpotikiKiwifruitHouse_Weta_End
OpotikiKiwifruitHouse_Weta_End::
	release
	end
OpotikiKiwifruitHouse_Text_WetaJob:
	.string "Oh, and if you're brave:\n"
	.string "there's a weta the size of my\l"
	.string "forearm in the smoko room.\p"
	.string "Nobody's had a cuppa in three\n"
	.string "days. Morale is low.$"
OpotikiKiwifruitHouse_Text_WetaHiss:
	.string "The giant weta rears up and\n"
	.string "rasps its spiny legs together!$"
OpotikiKiwifruitHouse_Text_WetaStill:
	.string "The weta settles back onto the\n"
	.string "biscuit tin. It considers the\l"
	.string "room its own.$"
OpotikiKiwifruitHouse_Text_WetaThanks:
	.string "Picker: The smoko room is ours\n"
	.string "again! Somebody put the jug on!\p"
	.string "Here, take these. You'd be\n"
	.string "amazed what we need them for in\l"
	.string "picking season.$"

