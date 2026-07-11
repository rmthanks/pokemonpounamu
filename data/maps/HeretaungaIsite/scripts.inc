HeretaungaIsite_MapScripts::
	.byte 0

HeretaungaIsite_EventScript_Ranger::
	lock
	faceplayer
	msgbox HeretaungaIsite_Text_Ranger, MSGBOX_DEFAULT
	release
	end

HeretaungaIsite_Text_Ranger:
	.string "Welcome to the Heretaunga\n"
	.string "i-SITE! Jobs, maps, and manu\l"
	.string "sightings, all in one place.\p"
	.string "The Job Board's just outside.\n"
	.string "Locals post work there - the\l"
	.string "Bay looks after its own.\p"
	.string "Keep a page in your notebook\n"
	.string "for native birds. Spot all\l"
	.string "twelve and Rakiura will be\l"
	.string "worth the boat fare someday.$"

