HeretaungaBerryHouse_MapScripts::
	.byte 0

HeretaungaBerryHouse_EventScript_BerryMum::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x030, HeretaungaBerryHouse_EventScript_BerryMum_Done
	msgbox HeretaungaBerryHouse_Text_BerryMum, MSGBOX_DEFAULT
	giveitem ITEM_PECHA_BERRY, 3
	setflag FLAG_UNUSED_0x030
	release
	end

HeretaungaBerryHouse_EventScript_BerryMum_Done::
	msgbox HeretaungaBerryHouse_Text_BerryMum_After, MSGBOX_DEFAULT
	release
	end

HeretaungaBerryHouse_Text_BerryMum:
	.string "Kia ora, love. You're the\n"
	.string "birthday kid from the\l"
	.string "homestead, eh?\p"
	.string "Take these for the road.\n"
	.string "PECHA sweetens a sour day.$"

HeretaungaBerryHouse_Text_BerryMum_After:
	.string "Plant one, keep two.\n"
	.string "That's the Bay way.$"

