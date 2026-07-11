WellingtonWindFlat_MapScripts::
	.byte 0

WellingtonWindFlat_EventScript_Barista::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x03A, WellingtonWindFlat_EventScript_Barista_Done
	msgbox WellingtonWindFlat_Text_Barista, MSGBOX_DEFAULT
	giveitem ITEM_ULTRA_BALL, 2
	setflag FLAG_UNUSED_0x03A
	release
	end

WellingtonWindFlat_EventScript_Barista_Done::
	msgbox WellingtonWindFlat_Text_Barista_After, MSGBOX_DEFAULT
	release
	end

WellingtonWindFlat_Text_Barista:
	.string "Wind ate my umbrella, my hat,\n"
	.string "and one very good scarf. You\l"
	.string "learn to carry less.\p"
	.string "Flat white? Best in the world,\n"
	.string "don't argue. And take these -\l"
	.string "anything that flies in THIS\l"
	.string "town has earned respect.$"

WellingtonWindFlat_Text_Barista_After:
	.string "Southerly tomorrow. You'll\n"
	.string "hear it before you feel it.$"

