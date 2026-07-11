HeretaungaGardenHouse_MapScripts::
	.byte 0

HeretaungaGardenHouse_EventScript_Gardener::
	lock
	faceplayer
	msgbox HeretaungaGardenHouse_Text_Gardener, MSGBOX_DEFAULT
	release
	end

HeretaungaGardenHouse_Text_Gardener:
	.string "The flower shop by the orchard\n"
	.string "used to be... something else.\l"
	.string "We don't talk about it.\p"
	.string "Rata tore the sign down\n"
	.string "herself. Good on her.\l"
	.string "Best mints in the Bay now.$"

