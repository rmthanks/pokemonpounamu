TurangaVineyardHouse_MapScripts::
	.byte 0

TurangaVineyardHouse_EventScript_Grower::
	lock
	faceplayer
	msgbox TurangaVineyardHouse_Text_Grower, MSGBOX_DEFAULT
	release
	end

TurangaVineyardHouse_Text_Grower:
	.string "Chardonnay country, this.\n"
	.string "The Bay does apples, we do\l"
	.string "grapes. Old family rivalry.\p"
	.string "Same sun, different fruit.\n"
	.string "Bit like families, eh?$"

