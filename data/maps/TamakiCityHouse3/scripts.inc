TamakiCityHouse3_MapScripts::
	.byte 0

TamakiCityHouse3_EventScript_LeagueFan::
	lock
	faceplayer
	msgbox TamakiCityHouse3_Text_LeagueFan, MSGBOX_DEFAULT
	release
	end

TamakiCityHouse3_Text_LeagueFan:
	.string "I had season tickets to the\n"
	.string "League gallery. Front row for\l"
	.string "every challenge.\p"
	.string "Four walls and the summit,\n"
	.string "they'd say. The whare stands\l"
	.string "when the walls come home.\l"
	.string "...The walls are OUT there\l"
	.string "somewhere, kid. All four.$"

