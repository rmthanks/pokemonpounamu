Route2BoP_MapScripts::
	.byte 0

Route2BoP_EventScript_Rangi::
	trainerbattle_single TRAINER_BOP_RANGI, Route2BoP_Text_RangiIntro, Route2BoP_Text_RangiDefeat
	msgbox Route2BoP_Text_RangiPost, MSGBOX_AUTOCLOSE
	end

Route2BoP_EventScript_Kiri::
	trainerbattle_single TRAINER_BOP_KIRI, Route2BoP_Text_KiriIntro, Route2BoP_Text_KiriDefeat
	msgbox Route2BoP_Text_KiriPost, MSGBOX_AUTOCLOSE
	end

Route2BoP_Text_RangiIntro:
	.string "My Mightyena's from Bay stock.\n"
	.string "Proper guard-dog lines.\p"
	.string "…We don't talk about the Bay\n"
	.string "much any more. Battle?$"

Route2BoP_Text_RangiDefeat:
	.string "Heel, boy. Heel!$"

Route2BoP_Text_RangiPost:
	.string "Word travels up the coast faster\n"
	.string "than you did.\p"
	.string "The kid who walked out of\n"
	.string "Hawke's Bay… that's you, eh?$"

Route2BoP_Text_KiriIntro:
	.string "Kiwifruit season! Everything\n"
	.string "smells amazing and everyone's\l"
	.string "too busy to battle.\p"
	.string "Except me. Go, Flaaffy!$"

Route2BoP_Text_KiriDefeat:
	.string "Zapped out of season…$"

Route2BoP_Text_KiriPost:
	.string "Tauranga's over the hill.\p"
	.string "Say hi to Mauao for me. The\n"
	.string "mountain, not the gym leader…\l"
	.string "though honestly, both work.$"
