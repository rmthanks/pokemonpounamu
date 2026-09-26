WairoaLighthouseKeeper_MapScripts::
	.byte 0

WairoaLighthouseKeeper_EventScript_Keeper::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x28B, WairoaLighthouseKeeper_LIGHTJOB_Done
	msgbox WairoaLighthouseKeeper_Text_LIGHTJOBAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, WairoaLighthouseKeeper_LIGHTJOB_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, WairoaLighthouseKeeper_LIGHTJOB_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_MAREEP, WairoaLighthouseKeeper_LIGHTJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_FLAAFFY, WairoaLighthouseKeeper_LIGHTJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_AMPHAROS, WairoaLighthouseKeeper_LIGHTJOB_Good
	msgbox WairoaLighthouseKeeper_Text_LIGHTJOBWrong, MSGBOX_DEFAULT
	release
	end

WairoaLighthouseKeeper_LIGHTJOB_Good::
	msgbox WairoaLighthouseKeeper_Text_LIGHTJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_MAGNET
	goto_if_eq VAR_RESULT, FALSE, WairoaLighthouseKeeper_LIGHTJOB_Full
	setflag FLAG_UNUSED_0x28B
	release
	end

WairoaLighthouseKeeper_LIGHTJOB_No::
	msgbox WairoaLighthouseKeeper_Text_LIGHTJOBNo, MSGBOX_DEFAULT
	release
	end

WairoaLighthouseKeeper_LIGHTJOB_Full::
	release
	end

WairoaLighthouseKeeper_LIGHTJOB_Done::
	msgbox WairoaLighthouseKeeper_Text_LIGHTJOBAfter, MSGBOX_DEFAULT
	release
	end

WairoaLighthouseKeeper_Text_LIGHTJOBAsk:
	.string "Kept the old lighthouse forty\n"
	.string "years. Now it sits in town like\l"
	.string "a retired soldier.\p"
	.string "They say out east there's a\n"
	.string "sheep with a light in its tail.\l"
	.string "A lighthouse that walks! Show\l"
	.string "me one before I go, would you?$"

WairoaLighthouseKeeper_Text_LIGHTJOBNo:
	.string "A light doesn't choose who it\n"
	.string "saves. Worth thinking about,\l"
	.string "the company you're headed for.$"

WairoaLighthouseKeeper_Text_LIGHTJOBWrong:
	.string "Handsome, but I can't see a\n"
	.string "light on it anywhere.$"

WairoaLighthouseKeeper_Text_LIGHTJOBThanks:
	.string "Would you look at that. A light\n"
	.string "that walks, and it chose to\l"
	.string "walk with you.\p"
	.string "Here. It came off the old lamp\n"
	.string "mechanism. It still pulls\l"
	.string "toward something.$"

WairoaLighthouseKeeper_Text_LIGHTJOBAfter:
	.string "A light doesn't choose who it\n"
	.string "saves. Yours seems to have\l"
	.string "chosen anyway.$"

WairoaLighthouseKeeper_Text_Keeper:
	.string "Kept the old lighthouse forty\n"
	.string "years. Now it sits in town\l"
	.string "like a retired soldier.\p"
	.string "A light doesn't choose who it\n"
	.string "saves. Worth thinking about,\l"
	.string "the company you're headed for.$"

