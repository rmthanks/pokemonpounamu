HeretaungaRetiredMobHouse_MapScripts::
	.byte 0

HeretaungaRetiredMobHouse_EventScript_OldPatch::
	lock
	faceplayer
	msgbox HeretaungaRetiredMobHouse_Text_OldPatch, MSGBOX_DEFAULT
	release
	end

HeretaungaRetiredMobHouse_Text_OldPatch:
	.string "Thirty years I wore the patch.\n"
	.string "Drove for the old president\l"
	.string "himself.\p"
	.string "Kauri was hard, but there were\n"
	.string "lines he wouldn't cross.\l"
	.string "His boy doesn't see lines.\p"
	.string "You be careful which whanau\n"
	.string "you let name you, kid.$"

