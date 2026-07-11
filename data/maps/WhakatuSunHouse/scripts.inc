WhakatuSunHouse_MapScripts::
	.byte 0

WhakatuSunHouse_EventScript_SunWoman::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x03C, WhakatuSunHouse_EventScript_SunWoman_Done
	msgbox WhakatuSunHouse_Text_SunWoman, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL, 1
	setflag FLAG_UNUSED_0x03C
	release
	end

WhakatuSunHouse_EventScript_SunWoman_Done::
	msgbox WhakatuSunHouse_Text_SunWoman_After, MSGBOX_DEFAULT
	release
	end

WhakatuSunHouse_Text_SunWoman:
	.string "Sunniest town in the country!\n"
	.string "We count the hours like other\l"
	.string "towns count rugby points.\p"
	.string "The Fire gym leader says his\n"
	.string "flame comes from WITHIN.\l"
	.string "Then he laughs like it's a\l"
	.string "joke. It is not a joke.\p"
	.string "Charcoal from the longest,\n"
	.string "brightest bonfire of summer.\l"
	.string "Warm wherever you're headed.$"

WhakatuSunHouse_Text_SunWoman_After:
	.string "2,500 hours of sun and\n"
	.string "counting. Eat that, Otautahi.$"

