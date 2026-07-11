TaurangaMauaoHouse_MapScripts::
	.byte 0

TaurangaMauaoHouse_EventScript_Runner::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x035, TaurangaMauaoHouse_EventScript_Runner_Done
	msgbox TaurangaMauaoHouse_Text_Runner, MSGBOX_DEFAULT
	giveitem ITEM_NET_BALL, 3
	setflag FLAG_UNUSED_0x035
	release
	end

TaurangaMauaoHouse_EventScript_Runner_Done::
	msgbox TaurangaMauaoHouse_Text_Runner_After, MSGBOX_DEFAULT
	release
	end

TaurangaMauaoHouse_Text_Runner:
	.string "I run Mauao before work.\n"
	.string "The maunga was a lovesick\l"
	.string "hill once, you know the story?\p"
	.string "Dragged himself to the sea in\n"
	.string "grief. Now he's the sunrise.\l"
	.string "Even sad endings keep going.\p"
	.string "Here - NET BALLS. The harbour\n"
	.string "is generous to early risers.$"

TaurangaMauaoHouse_Text_Runner_After:
	.string "Race you up Mauao sometime.\n"
	.string "Loser buys the juice.$"

