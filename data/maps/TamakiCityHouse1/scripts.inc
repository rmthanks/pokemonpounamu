TamakiCityHouse1_MapScripts::
	.byte 0

TamakiCityHouse1_EventScript_Commuter::
	lock
	faceplayer
	msgbox TamakiCityHouse1_Text_Commuter, MSGBOX_DEFAULT
	release
	end

TamakiCityHouse1_Text_Commuter:
	.string "Traffic was already the worst\n"
	.string "thing about this city. Then\l"
	.string "the checkpoints started.\p"
	.string "'Bay business.' On OUR bridge.\n"
	.string "Someone should climb up there\l"
	.string "and sort it. Someone young.\l"
	.string "Someone with nothing to\l"
	.string "repossess.$"

