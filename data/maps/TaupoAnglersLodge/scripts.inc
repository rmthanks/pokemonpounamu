TaupoAnglersLodge_MapScripts::
	.byte 0

TaupoAnglersLodge_EventScript_Angler::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x284, TaupoAnglersLodge_EventScript_AnglerRod
	msgbox TaupoAnglersLodge_Text_Angler, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	setflag FLAG_UNUSED_0x284
	msgbox TaupoAnglersLodge_Text_AnglerRod2, MSGBOX_DEFAULT
	release
	end

TaupoAnglersLodge_EventScript_AnglerRod::
	msgbox TaupoAnglersLodge_Text_AnglerAfter, MSGBOX_DEFAULT
	release
	end

TaupoAnglersLodge_EventScript_Angler_Done::
	msgbox TaupoAnglersLodge_Text_Angler_After, MSGBOX_DEFAULT
	release
	end

TaupoAnglersLodge_Text_Angler:
	.string "Forty years fishing this lake.\n"
	.string "Caught trout longer than your\l"
	.string "arm. Caught weirder, too.\p"
	.string "One night something passed\n"
	.string "under the boat. Ten trout\l"
	.string "long. Silver. SINGING.\p"
	.string "Nobody believes an old angler.\n"
	.string "Take this - whatever's down\l"
	.string "there, the lake likes you\l"
	.string "better if you carry it.$"

TaupoAnglersLodge_Text_Angler_After:
	.string "Still out there. Still\n"
	.string "singing. I still don't sleep\l"
	.string "much in a south wind.$"


TaupoAnglersLodge_Text_AnglerRod2:
	.string "That'll pull the deeper ones.\n"
	.string "Trout came here on a boat a\l"
	.string "hundred years back and decided\l"
	.string "they were locals.\p"
	.string "…Don't ask what else is down\n"
	.string "there. The lake keeps its own\l"
	.string "counsel.$"

TaupoAnglersLodge_Text_AnglerAfter:
	.string "The lake was flat as glass this\n"
	.string "morning.\p"
	.string "Those are the days it looks\n"
	.string "back at you.$"
