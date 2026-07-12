Taupo_MapScripts::
	.byte 0

Taupo_EventScript_LakeMan::
	msgbox Taupo_Text_LakeMan, MSGBOX_NPC
	end

Taupo_EventScript_StreetWoman::
	msgbox Taupo_Text_StreetWoman, MSGBOX_NPC
	end

Taupo_EventScript_GateOldMan::
	msgbox Taupo_Text_GateOldMan, MSGBOX_NPC
	end

Taupo_EventScript_Kid::
	msgbox Taupo_Text_Kid, MSGBOX_NPC
	end

Taupo_EventScript_LakeSign::
	msgbox Taupo_Text_LakeSign, MSGBOX_SIGN
	end

Taupo_Text_LakeMan:
	.string "The lake is the crater of\n"
	.string "something enormous and asleep.\p"
	.string "Best fishing in the world,\n"
	.string "right on top of it.\p"
	.string "…We don't think about it much.$"

Taupo_Text_StreetWoman:
	.string "Everything south of here is\n"
	.string "mountains and weather.\p"
	.string "Everything east is home for\n"
	.string "somebody.\p"
	.string "…You looked east just then.$"

Taupo_Text_GateOldMan:
	.string "That road east goes over the\n"
	.string "ranges to Ahuriri. Three days,\l"
	.string "beautiful the whole way.\p"
	.string "The Mob shut it overnight. No\n"
	.string "notice, no reason given.\p"
	.string "…Some folk out there just want\n"
	.string "to keep a door shut, eh.$"

Taupo_Text_Kid:
	.string "I skimmed a stone THIRTEEN times\n"
	.string "on the lake!\p"
	.string "Then something skimmed it back.$"

Taupo_Text_LakeSign:
	.string "LAKE TAUPO\p"
	.string "“The heart of the fish.”$"

@ ---- The Choice: north fork (Lugia) ----
Taupo_EventScript_LakeBoatman::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x903, Taupo_EventScript_BoatmanAfter
	goto_if_set FLAG_UNUSED_0x902, Taupo_EventScript_BoatmanTooLate
	goto_if_unset FLAG_UNUSED_0x900, Taupo_EventScript_BoatmanClosed
	msgbox Taupo_Text_BoatmanWarn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Taupo_EventScript_BoatmanNo
	setflag FLAG_UNUSED_0x901
	closemessage
	warp MAP_TAUPO_LAKE_ISLE, 13, 17
	waitstate
	end

Taupo_EventScript_BoatmanClosed::
	msgbox Taupo_Text_BoatmanClosed, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_BoatmanNo::
	msgbox Taupo_Text_BoatmanNo, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_BoatmanTooLate::
	msgbox Taupo_Text_BoatmanTooLate, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_BoatmanAfter::
	msgbox Taupo_Text_BoatmanAfter, MSGBOX_DEFAULT
	release
	end

Taupo_Text_BoatmanClosed:
	.string "Boatman: The isle? Nobody lands\n"
	.string "there, e hoa. That water\l"
	.string "belongs to what's under it.$"

Taupo_Text_BoatmanWarn:
	.string "Boatman: …So it's true, then.\n"
	.string "What your old man said.\p"
	.string "Listen once: if I row you out,\n"
	.string "there's no rowing to the OTHER\l"
	.string "one after. There isn't time.\l"
	.string "There was never time for both.\p"
	.string "You choose with your feet.\n"
	.string "…Get in?$"

Taupo_Text_BoatmanNo:
	.string "Boatman: Aye. Think on it.\p"
	.string "But don't think long. Your\n"
	.string "brother isn't.$"

Taupo_Text_BoatmanTooLate:
	.string "Boatman: You went south.\p"
	.string "…The lake's been dark two days\n"
	.string "now. Whatever came for the\l"
	.string "diver, it didn't row.$"

Taupo_Text_BoatmanAfter:
	.string "Boatman: Done is done, e hoa.\p"
	.string "Whatever you carry now, carry\n"
	.string "it all the way to that tower.$"

@ ------------------------------------------------------------------
@ Tawhai - the road mentor, keeper of the Tongariro gate. He barred
@ this road all game; post-tower, with Awhi's pointer, he opens it.
@ ------------------------------------------------------------------
Taupo_EventScript_Tawhai::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x90C, Taupo_EventScript_TawhaiOpen
	goto_if_unset FLAG_UNUSED_0x907, Taupo_EventScript_TawhaiBarred
	goto_if_unset FLAG_UNUSED_0x90B, Taupo_EventScript_TawhaiWaiting
	msgbox Taupo_Text_TawhaiOpens, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x90C
	goto Taupo_EventScript_TawhaiAsk

Taupo_EventScript_TawhaiOpen::
	msgbox Taupo_Text_TawhaiRoadOpen, MSGBOX_DEFAULT
	goto Taupo_EventScript_TawhaiAsk

Taupo_EventScript_TawhaiAsk::
	msgbox Taupo_Text_TawhaiHeadUp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Taupo_EventScript_TawhaiStay
	msgbox Taupo_Text_TawhaiGoSlow, MSGBOX_DEFAULT
	closemessage
	warp MAP_RUAPEHU_ASCENT, 28, 40
	waitstate
	release
	end

Taupo_EventScript_TawhaiStay::
	msgbox Taupo_Text_TawhaiStay, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_TawhaiBarred::
	msgbox Taupo_Text_TawhaiBarred, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_TawhaiWaiting::
	msgbox Taupo_Text_TawhaiWaiting, MSGBOX_DEFAULT
	release
	end

Taupo_Text_TawhaiBarred:
	.string "Tawhai: The mountain-family is\n"
	.string "grieving, e tama. That road\l"
	.string "stays shut while the Bay burns.\p"
	.string "Not for you. Not for anyone.$"

Taupo_Text_TawhaiWaiting:
	.string "Tawhai: The tower is quiet.\n"
	.string "Good. You did that.\p"
	.string "…You're looking for something\n"
	.string "now. When you know WHAT, come\l"
	.string "back and ask me properly.$"

Taupo_Text_TawhaiOpens:
	.string "Tawhai: …Ruapehu. I know.\p"
	.string "I've seen the smoke of his\n"
	.string "campfire from the tea tree\l"
	.string "line, most evenings.\p"
	.string "I barred this road to everyone\n"
	.string "for years. Today I open it.\p"
	.string "He asked me the same thing\n"
	.string "you're about to.$"

Taupo_Text_TawhaiRoadOpen:
	.string "Tawhai: The maunga waits.\n"
	.string "So does he.$"

Taupo_Text_TawhaiHeadUp:
	.string "Head up the mountain now?$"

Taupo_Text_TawhaiGoSlow:
	.string "Tawhai: Go up slow.\n"
	.string "Come down whole.$"

Taupo_Text_TawhaiStay:
	.string "Tawhai: The mountain has\n"
	.string "waited this long. It can wait\l"
	.string "for you to be ready.$"
