Otepoti_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Otepoti_OnTransition
	.byte 0

Otepoti_OnTransition:
	call_if_unset FLAG_BADGE08_GET, Otepoti_EventScript_HideKauri
	call_if_set FLAG_UNUSED_0x900, Otepoti_EventScript_HideKauri
	end

Otepoti_EventScript_HideKauri::
	setflag FLAG_UNUSED_0x904
	return
Otepoti_EventScript_ColdWoman::
	msgbox Otepoti_Text_ColdWoman, MSGBOX_NPC
	end
Otepoti_EventScript_GymKid::
	msgbox Otepoti_Text_GymKid, MSGBOX_NPC
	end
Otepoti_EventScript_StudentMan::
	msgbox Otepoti_Text_StudentMan, MSGBOX_NPC
	end
Otepoti_EventScript_Kid::
	msgbox Otepoti_Text_Kid, MSGBOX_NPC
	end
Otepoti_EventScript_GymSign::
	msgbox Otepoti_Text_GymSign, MSGBOX_SIGN
	end
Otepoti_Text_ColdWoman:
	.string "Coldest, southernmost city with\na gym. End of the line, love.\pFrom here it's albatross country.\nThen ice. Then nothing.$"
Otepoti_Text_GymKid:
	.string "Leader Huka is the STRONGEST of\nall eight! Badge 8's the real one!\pShe came from up north, like you.\nShe stayed. Made it hers.$"
Otepoti_Text_StudentMan:
	.string "Student town. Cheapest flats,\ncoldest flats, best nights out.\pWe heat the rooms with pure\nstubbornness.$"
Otepoti_Text_Kid:
	.string "Steepest street in the WORLD is\nright here! I rolled a marble down\lit and never saw it again!$"
Otepoti_Text_GymSign:
	.string "OTEPOTI GYM\nLeader: HUKA - the honest cold.\p“Eight badges. You walked the\nwhole motu to reach me.”$"

@ ---- Kauri's warning: the first fatherly act ----
Otepoti_EventScript_Kauri::
	lock
	faceplayer
	msgbox Otepoti_Text_KauriWarning, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_UNUSED_0x900
	setflag FLAG_UNUSED_0x904
	removeobject VAR_LAST_TALKED
	release
	end

Otepoti_Text_KauriWarning:
	.string "…Don't say my name.\p"
	.string "Eight badges. Your mother will\n"
	.string "be insufferable about it.\l"
	.string "Good.\p"
	.string "Listen. I have one thing to\n"
	.string "give you and it isn't an\l"
	.string "apology, so take it.\p"
	.string "Your brother moves on BOTH the\n"
	.string "great birds. Tonight. The lake\l"
	.string "in the north. The sound in the\l"
	.string "south.\p"
	.string "His crews can take one while\n"
	.string "you save the other. You cannot\l"
	.string "reach both. Nobody can.\p"
	.string "The boatmen know. Taupo, or\n"
	.string "the sound. Choose with your\l"
	.string "feet, kid.\p"
	.string "…They saw me come here. That's\n"
	.string "the last door I'll ever be able\l"
	.string "to open for you.\p"
	.string "Make it count.$"

@ ---- The Choice: south fork (Ho-Oh) ----
Otepoti_EventScript_SoundBoatman::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x903, Otepoti_EventScript_SBoatAfter
	goto_if_set FLAG_UNUSED_0x901, Otepoti_EventScript_SBoatTooLate
	goto_if_unset FLAG_UNUSED_0x900, Otepoti_EventScript_SBoatClosed
	msgbox Otepoti_Text_SBoatWarn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Otepoti_EventScript_SBoatNo
	setflag FLAG_UNUSED_0x902
	closemessage
	warp MAP_PIOPIOTAHI, 13, 19
	waitstate
	end

Otepoti_EventScript_SBoatClosed::
	msgbox Otepoti_Text_SBoatClosed, MSGBOX_DEFAULT
	release
	end

Otepoti_EventScript_SBoatNo::
	msgbox Otepoti_Text_SBoatNo, MSGBOX_DEFAULT
	release
	end

Otepoti_EventScript_SBoatTooLate::
	msgbox Otepoti_Text_SBoatTooLate, MSGBOX_DEFAULT
	release
	end

Otepoti_EventScript_SBoatAfter::
	msgbox Otepoti_Text_SBoatAfter, MSGBOX_DEFAULT
	release
	end

Otepoti_Text_SBoatClosed:
	.string "Sailor: Piopiotahi? In THIS\n"
	.string "season? Not for love nor money,\l"
	.string "mate.$"

Otepoti_Text_SBoatWarn:
	.string "Sailor: The sound, is it.\p"
	.string "Straight talk: if we sail,\n"
	.string "there's no reaching the lake\l"
	.string "up north after. No time. There\l"
	.string "was never time for both.\p"
	.string "The one you already know sits\n"
	.string "unguarded the moment we cast\l"
	.string "off.\p"
	.string "…Board her?$"

Otepoti_Text_SBoatNo:
	.string "Sailor: Wise to weigh it.\p"
	.string "Unwise to weigh it long.$"

Otepoti_Text_SBoatTooLate:
	.string "Sailor: You went north, mate.\p"
	.string "…Word is something took the\n"
	.string "firebird out of the sound the\l"
	.string "same night. Nets in the sky.$"

Otepoti_Text_SBoatAfter:
	.string "Sailor: Done is done.\p"
	.string "Sail's yours whenever you want\n"
	.string "the water, champ. But the\l"
	.string "choosing's finished.$"
