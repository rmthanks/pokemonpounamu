AhuririQuarterHouse2_MapScripts::
	.byte 0

AhuririQuarterHouse2_EventScript_Waiter::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x031, AhuririQuarterHouse2_EventScript_Waiter_Done
	msgbox AhuririQuarterHouse2_Text_Waiter, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_POTION, 1
	setflag FLAG_UNUSED_0x031
	release
	end

AhuririQuarterHouse2_EventScript_Waiter_Done::
	msgbox AhuririQuarterHouse2_Text_Waiter_After, MSGBOX_DEFAULT
	release
	end

AhuririQuarterHouse2_Text_Waiter:
	.string "I wait tables at the social\n"
	.string "club on the parade. The tips\l"
	.string "are... complicated.\p"
	.string "Here. A gentleman left this\n"
	.string "and said 'for the kid with\l"
	.string "the apples'. Take it, quick.$"

AhuririQuarterHouse2_Text_Waiter_After:
	.string "No more packages, promise.\n"
	.string "Just don't sit at the corner\l"
	.string "table. Ever.$"

