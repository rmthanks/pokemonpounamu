HeretaungaTwinsHouse_MapScripts::
	.byte 0

HeretaungaTwinsHouse_EventScript_Twins::
	lock
	faceplayer
	msgbox HeretaungaTwinsHouse_Text_Twins, MSGBOX_DEFAULT
	release
	end

HeretaungaTwinsHouse_Text_Twins:
	.string "We're not allowed past the\n"
	.string "orchard fence after dark.\p"
	.string "Mum says the men in the black\n"
	.string "jackets aren't strangers.\l"
	.string "That's what makes it worse.$"

