TamakiHarbourWatch_MapScripts::
	.byte 0

TamakiHarbourWatch_EventScript_HarbourMaster::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x2B1, TamakiHarbourWatch_WHALEJOB_Done
	msgbox TamakiHarbourWatch_Text_WHALEJOBAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TamakiHarbourWatch_WHALEJOB_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, TamakiHarbourWatch_WHALEJOB_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_WAILMER, TamakiHarbourWatch_WHALEJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_WAILORD, TamakiHarbourWatch_WHALEJOB_Good
	msgbox TamakiHarbourWatch_Text_WHALEJOBWrong, MSGBOX_DEFAULT
	release
	end

TamakiHarbourWatch_WHALEJOB_Good::
	msgbox TamakiHarbourWatch_Text_WHALEJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_WAVE_INCENSE
	goto_if_eq VAR_RESULT, FALSE, TamakiHarbourWatch_WHALEJOB_Full
	setflag FLAG_UNUSED_0x2B1
	release
	end

TamakiHarbourWatch_WHALEJOB_No::
	msgbox TamakiHarbourWatch_Text_WHALEJOBNo, MSGBOX_DEFAULT
	release
	end

TamakiHarbourWatch_WHALEJOB_Full::
	release
	end

TamakiHarbourWatch_WHALEJOB_Done::
	msgbox TamakiHarbourWatch_Text_WHALEJOBAfter, MSGBOX_DEFAULT
	release
	end

TamakiHarbourWatch_Text_WHALEJOBAsk:
	.string "Harbour watch. Twenty berths,\n"
	.string "two hundred stories.\p"
	.string "Some nights a shape crosses the\n"
	.string "harbour mouth. Too big for a\l"
	.string "boat. The log says “seal”. The\l"
	.string "log is a coward.\p"
	.string "Show me a whale, and I'll\n"
	.string "finally write the truth in it.$"

TamakiHarbourWatch_Text_WHALEJOBNo:
	.string "Then the log stays a coward\n"
	.string "another night.$"

TamakiHarbourWatch_Text_WHALEJOBWrong:
	.string "Not big enough to be my shape.\n"
	.string "Not by a long way.$"

TamakiHarbourWatch_Text_WHALEJOBThanks:
	.string "That's it. That's the shape.\n"
	.string "Whales in the gulf, right under\l"
	.string "the Harbour Bridge.\p"
	.string "The log now says “whale”. Here,\n"
	.string "with the harbour's thanks.$"

TamakiHarbourWatch_Text_WHALEJOBAfter:
	.string "The log says “whale” now. Best\n"
	.string "entry I've ever written.$"

TamakiHarbourWatch_Text_HarbourMaster:
	.string "Harbour watch. Twenty berths,\n"
	.string "two hundred stories.\p"
	.string "Some nights a shape crosses\n"
	.string "the harbour mouth. Too big\l"
	.string "for a boat, too quiet for a\l"
	.string "bird. The log says 'seal'.\l"
	.string "The log is a coward.$"

