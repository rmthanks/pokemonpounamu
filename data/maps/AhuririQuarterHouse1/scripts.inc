AhuririQuarterHouse1_MapScripts::
	.byte 0

AhuririQuarterHouse1_EventScript_Socialite::
	lock
	faceplayer
	msgbox AhuririQuarterHouse1_Text_Socialite, MSGBOX_DEFAULT
	release
	end

AhuririQuarterHouse1_Text_Socialite:
	.string "The gym leader? Charming man.\n"
	.string "Beautiful manners. Dreadful\l"
	.string "friends.\p"
	.string "In this town we say the suits\n"
	.string "are tailored and so are the\l"
	.string "stories. Mind both, dear.$"

