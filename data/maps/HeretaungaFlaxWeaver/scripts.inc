HeretaungaFlaxWeaver_MapScripts::
	.byte 0

HeretaungaFlaxWeaver_EventScript_Weaver::
	lock
	faceplayer
	msgbox HeretaungaFlaxWeaver_Text_Weaver, MSGBOX_DEFAULT
	release
	end

HeretaungaFlaxWeaver_Text_Weaver:
	.string "Harakeke, love. Flax.\n"
	.string "You cut it right, thank it\l"
	.string "right, and it gives forever.\p"
	.string "Same with people. Cut them\n"
	.string "wrong and something unravels\l"
	.string "that no one can plait back.$"

HeretaungaFlaxWeaver_EventScript_FlaxKid::
	lock
	faceplayer
	msgbox HeretaungaFlaxWeaver_Text_FlaxKid, MSGBOX_DEFAULT
	release
	end

HeretaungaFlaxWeaver_Text_FlaxKid:
	.string "Nana can make ANYTHING out of\n"
	.string "flax! Kete, whariki, even a\l"
	.string "tiny Wooloo!$"

