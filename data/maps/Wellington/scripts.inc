Wellington_MapScripts::
	.byte 0
Wellington_EventScript_GymKid::
	msgbox Wellington_Text_GymKid, MSGBOX_NPC
	end
Wellington_EventScript_BeehiveMan::
	msgbox Wellington_Text_BeehiveMan, MSGBOX_NPC
	end
Wellington_EventScript_WindWoman::
	msgbox Wellington_Text_WindWoman, MSGBOX_NPC
	end
Wellington_EventScript_FerryMan::
	msgbox Wellington_Text_FerryMan, MSGBOX_NPC
	end
Wellington_EventScript_CafeKid::
	msgbox Wellington_Text_CafeKid, MSGBOX_NPC
	end
Wellington_EventScript_GymSign::
	msgbox Wellington_Text_GymSign, MSGBOX_SIGN
	end
Wellington_EventScript_BeehiveSign::
	msgbox Wellington_Text_BeehiveSign, MSGBOX_SIGN
	end
Wellington_EventScript_FerrySign::
	msgbox Wellington_Text_FerrySign, MSGBOX_SIGN
	end

Wellington_Text_GymKid:
	.string "Leader Manu reads the wind like\n"
	.string "a book.\p"
	.string "In this town, that's not a\n"
	.string "hobby. It's survival.\p"
	.string "…Gym's closed for now, but.$"
Wellington_Text_BeehiveMan:
	.string "That round building's where they\n"
	.string "make the rules for the whole\l"
	.string "motu.\p"
	.string "Shaped like a beehive. Make of\n"
	.string "that what you will.$"
Wellington_Text_WindWoman:
	.string "You can't lean on the wind here,\n"
	.string "exactly.\p"
	.string "But you can trust it to catch\n"
	.string "you. Usually.$"
Wellington_Text_FerryMan:
	.string "Ferry across the strait to the\n"
	.string "South Island.\p"
	.string "…Not running, though. Weather,\n"
	.string "they say. And 'other reasons.'\p"
	.string "The 'other reasons' wear\n"
	.string "matching jackets. You follow?$"
Wellington_Text_CafeKid:
	.string "Six cafes on one block! I've\n"
	.string "had four hot chocolates.\p"
	.string "I can HEAR colours!$"
Wellington_Text_GymSign:
	.string "TE WHANGANUI-A-TARA GYM\n"
	.string "Leader: MANU - rides the gale.\p"
	.string "“Back when the wind allows.”\p"
	.string "(Gym 5 opens in a later build!)$"
Wellington_Text_BeehiveSign:
	.string "THE BEEHIVE\p"
	.string "“Where the motu makes its\n"
	.string "promises.” Some are even kept.$"
Wellington_Text_FerrySign:
	.string "INTERISLANDER - COOK STRAIT\p"
	.string "SAILINGS SUSPENDED.\p"
	.string "A second notice, newer:\n"
	.string "“By order. Bay business.”\p"
	.string "(The South Island opens in a\n"
	.string "later build - the ferry is your\l"
	.string "door across.)$"

@ ---- Ferry north: Tamaki Makaurau (post-Choice) ----
Wellington_EventScript_TamakiFerry::
	lock
	faceplayer
	goto_if_unset FLAG_UNUSED_0x903, Wellington_EventScript_TamakiFerryClosed
	msgbox Wellington_Text_TamakiFerry, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Wellington_EventScript_TamakiFerryNo
	closemessage
	warp MAP_TAMAKI_MAKAURAU, 53, 33
	waitstate
	end

Wellington_EventScript_TamakiFerryClosed::
	msgbox Wellington_Text_TamakiFerryClosed, MSGBOX_DEFAULT
	release
	end

Wellington_EventScript_TamakiFerryNo::
	release
	end

Wellington_Text_TamakiFerryClosed:
	.string "Sailor: Tamaki? Nothing sails\n"
	.string "north right now, mate.\p"
	.string "Whole harbour up there answers\n"
	.string "to one tower, and the tower\l"
	.string "isn't taking visitors.$"

Wellington_Text_TamakiFerry:
	.string "Sailor: Tamaki Makaurau.\p"
	.string "…You're really going up there,\n"
	.string "carrying what you carry.\p"
	.string "One tower. One brother.\n"
	.string "…Board her?$"
