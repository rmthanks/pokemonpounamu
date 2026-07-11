OpotikiKiwifruitHouse_MapScripts::
	.byte 0

OpotikiKiwifruitHouse_EventScript_Picker2::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x034, OpotikiKiwifruitHouse_EventScript_Picker2_Done
	msgbox OpotikiKiwifruitHouse_Text_Picker2, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_POTION, 1
	setflag FLAG_UNUSED_0x034
	release
	end

OpotikiKiwifruitHouse_EventScript_Picker2_Done::
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

