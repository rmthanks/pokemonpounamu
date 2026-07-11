OtepotiStoneVilla_MapScripts::
	.byte 0

OtepotiStoneVilla_EventScript_Professor::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x03E, OtepotiStoneVilla_EventScript_Professor_Done
	msgbox OtepotiStoneVilla_Text_Professor, MSGBOX_DEFAULT
	giveitem ITEM_NEVER_MELT_ICE, 1
	setflag FLAG_UNUSED_0x03E
	release
	end

OtepotiStoneVilla_EventScript_Professor_Done::
	msgbox OtepotiStoneVilla_Text_Professor_After, MSGBOX_DEFAULT
	release
	end

OtepotiStoneVilla_Text_Professor:
	.string "Edinburgh of the south, this\n"
	.string "city. Stone, scholarship and\l"
	.string "weather with OPINIONS.\p"
	.string "Huka's gym? The whiteout is\n"
	.string "pedagogy, dear. You cannot\l"
	.string "fight what you refuse to\l"
	.string "walk into.\p"
	.string "From my glaciology days.\n"
	.string "It has never once melted.\l"
	.string "Neither, I suspect, will you.$"

OtepotiStoneVilla_Text_Professor_After:
	.string "The harbour was a volcano\n"
	.string "once. Everything cools.\l"
	.string "Everything keeps its shape.$"

