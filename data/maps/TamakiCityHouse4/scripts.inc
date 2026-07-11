TamakiCityHouse4_MapScripts::
	.byte 0

TamakiCityHouse4_EventScript_Volunteer::
	lock
	faceplayer
	msgbox TamakiCityHouse4_Text_Volunteer, MSGBOX_DEFAULT
	release
	end

TamakiCityHouse4_Text_Volunteer:
	.string "Volunteer coastguard. We still\n"
	.string "run drills, tower or no tower.\p"
	.string "Rangitoto hasn't blinked in\n"
	.string "six hundred years. Whatever's\l"
	.string "happening up that tower, the\l"
	.string "volcano isn't impressed.\l"
	.string "I find that very steadying.$"

