TaurangaPortHouse_MapScripts::
	.byte 0

TaurangaPortHouse_EventScript_Stevedore::
	lock
	faceplayer
	msgbox TaurangaPortHouse_Text_Stevedore, MSGBOX_DEFAULT
	release
	end

TaurangaPortHouse_Text_Stevedore:
	.string "Biggest port in the country.\n"
	.string "Everything you've ever owned\l"
	.string "came over that wharf.\p"
	.string "Lately there's containers even\n"
	.string "the manifest won't name.\l"
	.string "Bay plates on the trucks, too.$"

