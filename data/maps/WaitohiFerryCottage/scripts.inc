WaitohiFerryCottage_MapScripts::
	.byte 0

WaitohiFerryCottage_EventScript_FerryWatcher::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x03B, WaitohiFerryCottage_FerryWatcher_Gifted
	msgbox WaitohiFerryCottage_Text_FerryWatcher, MSGBOX_DEFAULT
	giveitem ITEM_FULL_HEAL, 1
	setflag FLAG_UNUSED_0x03B
WaitohiFerryCottage_FerryWatcher_Gifted::
	goto_if_set FLAG_UNUSED_0x29B, WaitohiFerryCottage_EventScript_FerryWatcher_Done
	msgbox WaitohiFerryCottage_Text_StowawayJob, MSGBOX_DEFAULT
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

@ ---- Mission batch S2 (2026-09-26) ----
@ Job 30: The Picton Stowaway - the iron-clawed ship's cat; done FLAG_UNUSED_0x29B
WaitohiFerryCottage_EventScript_Stowaway::
	lock
	faceplayer
	playmoncry SPECIES_MEOWTH_GALAR, CRY_MODE_ENCOUNTER
	msgbox WaitohiFerryCottage_Text_StowawayHiss, MSGBOX_DEFAULT
	waitmoncry
	setwildbattle SPECIES_MEOWTH_GALAR, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, WaitohiFerryCottage_Stowaway_Gone
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, WaitohiFerryCottage_Stowaway_Gone
	msgbox WaitohiFerryCottage_Text_StowawayStill, MSGBOX_DEFAULT
	release
	end

WaitohiFerryCottage_Stowaway_Gone::
	setflag FLAG_UNUSED_0x29B
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox WaitohiFerryCottage_Text_StowawayThanks, MSGBOX_DEFAULT
	giveitem ITEM_METAL_COAT
	goto_if_eq VAR_RESULT, FALSE, WaitohiFerryCottage_Stowaway_End
WaitohiFerryCottage_Stowaway_End::
	release
	end
WaitohiFerryCottage_Text_StowawayJob:
	.string "Oh, and there's a stowaway in\n"
	.string "here. Came off the last ferry\l"
	.string "in a crate of spanners.\p"
	.string "Iron claws. Won't leave. Eats\n"
	.string "my toast. If you could have a\l"
	.string "word with it...$"
WaitohiFerryCottage_Text_StowawayHiss:
	.string "The stowaway Meowth arches its\n"
	.string "iron back and hisses!$"
WaitohiFerryCottage_Text_StowawayStill:
	.string "The Meowth goes back to\n"
	.string "guarding the toast rack.$"
WaitohiFerryCottage_Text_StowawayThanks:
	.string "Ferry Watcher: My toast is\n"
	.string "safe! The strait provides, and\l"
	.string "the strait takes away.\p"
	.string "It left this behind in the\n"
	.string "spanner crate. Take it, it's no\l"
	.string "use to a man with no spanners.$"

