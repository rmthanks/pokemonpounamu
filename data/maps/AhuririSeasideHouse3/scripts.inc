AhuririSeasideHouse3_MapScripts::
	.byte 0

AhuririSeasideHouse3_EventScript_Nurse2::
	lock
	faceplayer
	goto_if_eq VAR_POUNAMU_DECO_STATE, 2, AhuririSeasideHouse3_EventScript_NursePosy
	msgbox AhuririSeasideHouse3_Text_Nurse2, MSGBOX_DEFAULT
	release
	end

AhuririSeasideHouse3_EventScript_NursePosy::
	msgbox AhuririSeasideHouse3_Text_NursePosy, MSGBOX_DEFAULT
	setvar VAR_POUNAMU_DECO_STATE, 3
	release
	end

AhuririSeasideHouse3_Text_Nurse2:
	.string "I nursed through the quake\n"
	.string "centennial. You know what got\l"
	.string "us through? Neighbours.\p"
	.string "Whatever's rotten in this\n"
	.string "town, the people aren't.\l"
	.string "Remember that when you leave.$"

@ ---- Mission batch S2 (2026-09-26) ----
AhuririSeasideHouse3_Text_NursePosy:
	.string "Oh, Kiri. She does this every\n"
	.string "year on the anniversary. Never\l"
	.string "says why. Doesn't need to.\p"
	.string "Thank you, love. Mind how you\n"
	.string "go at that last address.$"

