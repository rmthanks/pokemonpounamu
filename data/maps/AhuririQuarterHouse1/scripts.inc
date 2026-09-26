AhuririQuarterHouse1_MapScripts::
	.byte 0

AhuririQuarterHouse1_EventScript_Socialite::
	lock
	faceplayer
	goto_if_eq VAR_POUNAMU_DECO_STATE, 3, AhuririQuarterHouse1_EventScript_SocialitePosy
	msgbox AhuririQuarterHouse1_Text_Socialite, MSGBOX_DEFAULT
	release
	end

AhuririQuarterHouse1_EventScript_SocialitePosy::
	msgbox AhuririQuarterHouse1_Text_SocialitePosy, MSGBOX_DEFAULT
	setvar VAR_POUNAMU_DECO_STATE, 4
	release
	end

AhuririQuarterHouse1_Text_Socialite:
	.string "The gym leader? Charming man.\n"
	.string "Beautiful manners. Dreadful\l"
	.string "friends.\p"
	.string "In this town we say the suits\n"
	.string "are tailored and so are the\l"
	.string "stories. Mind both, dear.$"

@ ---- Mission batch S2 (2026-09-26) ----
AhuririQuarterHouse1_Text_SocialitePosy:
	.string "Ah, the centrepiece. It's for\n"
	.string "the President's table,\l"
	.string "Saturday. The club likes a nice\l"
	.string "table.\p"
	.string "...You're his youngest, aren't\n"
	.string "you? Then you'll know it's best\l"
	.string "not to ask what the club talks\l"
	.string "about over the flowers.$"

