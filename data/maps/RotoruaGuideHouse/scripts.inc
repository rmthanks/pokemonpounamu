RotoruaGuideHouse_MapScripts::
	.byte 0

RotoruaGuideHouse_EventScript_Guide::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x28F, RotoruaGuideHouse_GeyserJob_Done
	msgbox RotoruaGuideHouse_Text_Guide, MSGBOX_DEFAULT
	gettimeofday
	goto_if_lt VAR_0x8000, 2, RotoruaGuideHouse_GeyserJob_NotYet
	msgbox RotoruaGuideHouse_Text_GeyserJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RotoruaGuideHouse_GeyserJob_No
	fadescreen FADE_TO_BLACK
	playse SE_M_WHIRLPOOL
	msgbox RotoruaGuideHouse_Text_GeyserJobWatch, MSGBOX_DEFAULT
	fadescreen FADE_FROM_BLACK
	msgbox RotoruaGuideHouse_Text_GeyserJobThanks, MSGBOX_DEFAULT
	giveitem ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, FALSE, RotoruaGuideHouse_GeyserJob_Full
	setflag FLAG_UNUSED_0x28F
RotoruaGuideHouse_GeyserJob_Full::
	release
	end

RotoruaGuideHouse_Text_Guide:
	.string "My great-great-nana guided\n"
	.string "people across the lake to the\l"
	.string "Pink and White Terraces.\p"
	.string "The mountain took the terraces\n"
	.string "back. Guides stayed. There is\l"
	.string "always somewhere to lead\l"
	.string "people, even after the wonder.\p"
	.string "The gym leader, Whenua? Solid\n"
	.string "as the ground and twice as\l"
	.string "patient. You'll like him.$"

@ ---- Mission batch S2 (2026-09-26) ----
@ Job 19: Pohutu at Dusk - the guide's evening walk; done FLAG_UNUSED_0x28F
RotoruaGuideHouse_GeyserJob_NotYet::
	msgbox RotoruaGuideHouse_Text_GeyserJobNotYet, MSGBOX_DEFAULT
	release
	end

RotoruaGuideHouse_GeyserJob_No::
	msgbox RotoruaGuideHouse_Text_GeyserJobNo, MSGBOX_DEFAULT
	release
	end

RotoruaGuideHouse_GeyserJob_Done::
	msgbox RotoruaGuideHouse_Text_GeyserJobAfter, MSGBOX_DEFAULT
	release
	end
RotoruaGuideHouse_Text_GeyserJobNotYet:
	.string "If you want to see Pohutu at\n"
	.string "her best, come back in the\l"
	.string "evening. The tourists go home,\l"
	.string "and the steam goes pink.$"
RotoruaGuideHouse_Text_GeyserJobAsk:
	.string "It's the right time now. Come\n"
	.string "on, I'll walk you out to see\l"
	.string "her.$"
RotoruaGuideHouse_Text_GeyserJobWatch:
	.string "The ground hums. Then Pohutu\n"
	.string "throws her water at the sky,\l"
	.string "higher than the trees, pink in\l"
	.string "the last of the light.$"
RotoruaGuideHouse_Text_GeyserJobThanks:
	.string "Every guide in my family has\n"
	.string "stood right there and said\l"
	.string "nothing. Now you have too.\p"
	.string "Take this. Water that's been\n"
	.string "somewhere, like you.$"
RotoruaGuideHouse_Text_GeyserJobNo:
	.string "She'll go without us. She\n"
	.string "always does.$"
RotoruaGuideHouse_Text_GeyserJobAfter:
	.string "There is always somewhere to\n"
	.string "lead people, even after the\l"
	.string "wonder. You're proof.$"

