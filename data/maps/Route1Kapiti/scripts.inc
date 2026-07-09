Route1Kapiti_MapScripts::
	.byte 0
Route1Kapiti_EventScript_Tama2::
	trainerbattle_single TRAINER_R1K_TAMA2, Route1Kapiti_Text_Tama2Intro, Route1Kapiti_Text_Tama2Defeat
	msgbox Route1Kapiti_Text_Tama2Post, MSGBOX_AUTOCLOSE
	end
Route1Kapiti_EventScript_Rae::
	trainerbattle_single TRAINER_R1K_RAE, Route1Kapiti_Text_RaeIntro, Route1Kapiti_Text_RaeDefeat
	msgbox Route1Kapiti_Text_RaePost, MSGBOX_AUTOCLOSE
	end
Route1Kapiti_Text_Tama2Intro:
	.string "Kapiti Island's out there in the\n"
	.string "haze. Sanctuary. No predators.\p"
	.string "Bit like a checkpoint, really.\n"
	.string "Keeps things OUT.$"
Route1Kapiti_Text_Tama2Defeat:
	.string "Grounded.$"
Route1Kapiti_Text_Tama2Post:
	.string "You've got that look. Somebody\n"
	.string "back home shut a door on you.\p"
	.string "…Yeah. I know the look.$"
Route1Kapiti_Text_RaeIntro:
	.string "Wind farm country! Every ridge\n"
	.string "has a turbine and every turbine\l"
	.string "has a name.\p"
	.string "That one's Kevin. Battle!$"
Route1Kapiti_Text_RaeDefeat:
	.string "Kevin is disappointed.$"
Route1Kapiti_Text_RaePost:
	.string "The capital's just south now.\p"
	.string "Te Whanganui-a-Tara. End of the\n"
	.string "island. You'll feel it.$"
