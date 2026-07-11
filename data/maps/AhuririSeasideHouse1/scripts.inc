AhuririSeasideHouse1_MapScripts::
	.byte 0

AhuririSeasideHouse1_EventScript_ReefMan::
	lock
	faceplayer
	msgbox AhuririSeasideHouse1_Text_ReefMan, MSGBOX_DEFAULT
	release
	end

AhuririSeasideHouse1_Text_ReefMan:
	.string "Pania waits out there on the\n"
	.string "reef, they say. Loved a man,\l"
	.string "went back to the sea.\p"
	.string "Some mornings the swell sings.\n"
	.string "Bring a Pokemon that can sing\l"
	.string "back, show the statue keeper.$"

