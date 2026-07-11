TaupoAnglersLodge_MapScripts::
	.byte 0

TaupoAnglersLodge_EventScript_Angler::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x037, TaupoAnglersLodge_EventScript_Angler_Done
	msgbox TaupoAnglersLodge_Text_Angler, MSGBOX_DEFAULT
	giveitem ITEM_MYSTIC_WATER, 1
	setflag FLAG_UNUSED_0x037
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

