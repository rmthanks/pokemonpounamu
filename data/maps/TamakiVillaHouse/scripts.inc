TamakiVillaHouse_MapScripts::
	.byte 0

TamakiVillaHouse_EventScript_VillaOwner::
	lock
	faceplayer
	msgbox TamakiVillaHouse_Text_VillaOwner, MSGBOX_DEFAULT
	release
	end

TamakiVillaHouse_Text_VillaOwner:
	.string "A villa this close to the\n"
	.string "tower cost everything we had.\l"
	.string "Then the tower went dark.\p"
	.string "Now we keep the curtains\n"
	.string "closed on that side. You can\l"
	.string "feel it looking, I swear.$"

