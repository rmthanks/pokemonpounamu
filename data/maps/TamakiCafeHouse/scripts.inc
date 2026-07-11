TamakiCafeHouse_MapScripts::
	.byte 0

TamakiCafeHouse_EventScript_CafeOwner::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x03F, TamakiCafeHouse_EventScript_CafeOwner_Done
	msgbox TamakiCafeHouse_Text_CafeOwner, MSGBOX_DEFAULT
	giveitem ITEM_LEFTOVERS, 1
	setflag FLAG_UNUSED_0x03F
	release
	end

TamakiCafeHouse_EventScript_CafeOwner_Done::
	msgbox TamakiCafeHouse_Text_CafeOwner_After, MSGBOX_DEFAULT
	release
	end

TamakiCafeHouse_Text_CafeOwner:
	.string "Cafe's closed. The suits\n"
	.string "'renegotiated' my lease, then\l"
	.string "my nerve.\p"
	.string "Last plate of the old menu.\n"
	.string "Take it. When the tower's got\l"
	.string "lights again, come back and\l"
	.string "I'll cook you the first plate\l"
	.string "of the new one.$"

TamakiCafeHouse_Text_CafeOwner_After:
	.string "Still closed. Still hopeful.\n"
	.string "Still the best table in\l"
	.string "Tamaki, if you're asking.$"

