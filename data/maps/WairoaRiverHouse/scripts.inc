WairoaRiverHouse_MapScripts::
	.byte 0

WairoaRiverHouse_EventScript_EelMan::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x032, WairoaRiverHouse_EventScript_EelMan_Done
	msgbox WairoaRiverHouse_Text_EelMan, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 3
	setflag FLAG_UNUSED_0x032
	release
	end

WairoaRiverHouse_EventScript_EelMan_Done::
	msgbox WairoaRiverHouse_Text_EelMan_After, MSGBOX_DEFAULT
	release
	end

WairoaRiverHouse_Text_EelMan:
	.string "The river's the boss in Wairoa.\n"
	.string "Floods when it wants, feeds\l"
	.string "us when it forgives.\p"
	.string "Heading up the coast? Take\n"
	.string "these. Everything worth\l"
	.string "catching is past the bridge.$"

WairoaRiverHouse_Text_EelMan_After:
	.string "Tight lines, kid. Mind the\n"
	.string "river fog at night.$"

