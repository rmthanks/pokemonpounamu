WaitohiFerryCottage_MapScripts::
	.byte 0

WaitohiFerryCottage_EventScript_FerryWatcher::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x03B, WaitohiFerryCottage_EventScript_FerryWatcher_Done
	msgbox WaitohiFerryCottage_Text_FerryWatcher, MSGBOX_DEFAULT
	giveitem ITEM_FULL_HEAL, 1
	setflag FLAG_UNUSED_0x03B
	release
	end

WaitohiFerryCottage_EventScript_FerryWatcher_Done::
	msgbox WaitohiFerryCottage_Text_FerryWatcher_After, MSGBOX_DEFAULT
	release
	end

WaitohiFerryCottage_Text_FerryWatcher:
	.string "I watch the ferries come in.\n"
	.string "Every soul crossing the strait\l"
	.string "passes my window.\p"
	.string "Saw a young fella cross north\n"
	.string "some months back. Storm face.\l"
	.string "Family jaw. Friend of yours?\p"
	.string "The strait shakes people out.\n"
	.string "Take this - whatever's waiting\l"
	.string "over the water, arrive well.$"

WaitohiFerryCottage_Text_FerryWatcher_After:
	.string "Calm crossing today.\n"
	.string "Doesn't happen twice.$"

