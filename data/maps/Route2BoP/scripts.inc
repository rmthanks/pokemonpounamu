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

Route2BoP_EventScript_PPare::
	trainerbattle_single TRAINER_RBOP_PARE, Route2BoP_Text_PPareIntro, Route2BoP_Text_PPareDefeat
	msgbox Route2BoP_Text_PParePost, MSGBOX_AUTOCLOSE
	end

Route2BoP_Text_PPareIntro:
	.string "Pare: Shh! You'll scare the fish!\n…Too late. Battle.$"

Route2BoP_Text_PPareDefeat:
	.string "Snapped my line AND my streak.$"

Route2BoP_Text_PParePost:
	.string "They're biting better since\nyou showed up. Weird.$"

Route2BoP_EventScript_PAnika::
	trainerbattle_single TRAINER_RBOP_ANIKA, Route2BoP_Text_PAnikaIntro, Route2BoP_Text_PAnikaDefeat
	msgbox Route2BoP_Text_PAnikaPost, MSGBOX_AUTOCLOSE
	end

Route2BoP_Text_PAnikaIntro:
	.string "Anika: Shh! You'll scare the fish!\n…Too late. Battle.$"

Route2BoP_Text_PAnikaDefeat:
	.string "Snapped my line AND my streak.$"

Route2BoP_Text_PAnikaPost:
	.string "They're biting better since\nyou showed up. Weird.$"

Route2BoP_EventScript_PBeau::
	trainerbattle_single TRAINER_RBOP_BEAU, Route2BoP_Text_PBeauIntro, Route2BoP_Text_PBeauDefeat
	msgbox Route2BoP_Text_PBeauPost, MSGBOX_AUTOCLOSE
	end

Route2BoP_Text_PBeauIntro:
	.string "Beau: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route2BoP_Text_PBeauDefeat:
	.string "You can have the sammie.$"

Route2BoP_Text_PBeauPost:
	.string "Worth it. Rematch at smoko?$"

Route2BoP_EventScript_PBlake::
	trainerbattle_single TRAINER_RBOP_BLAKE, Route2BoP_Text_PBlakeIntro, Route2BoP_Text_PBlakeDefeat
	msgbox Route2BoP_Text_PBlakePost, MSGBOX_AUTOCLOSE
	end

Route2BoP_Text_PBlakeIntro:
	.string "Blake: I've tramped every track in\nthis region. Fight me.$"

Route2BoP_Text_PBlakeDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route2BoP_Text_PBlakePost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route2BoP_EventScript_PCaleb::
	trainerbattle_single TRAINER_RBOP_CALEB, Route2BoP_Text_PCalebIntro, Route2BoP_Text_PCalebDefeat
	msgbox Route2BoP_Text_PCalebPost, MSGBOX_AUTOCLOSE
	end

Route2BoP_Text_PCalebIntro:
	.string "Caleb: I've been training out here\nALL morning!$"

Route2BoP_Text_PCalebDefeat:
	.string "Okay, MOST of the morning.$"

Route2BoP_Text_PCalebPost:
	.string "Don't tell my nan I lost.$"

Route2BoP_EventScript_PCharlie::
	trainerbattle_single TRAINER_RBOP_CHARLIE, Route2BoP_Text_PCharlieIntro, Route2BoP_Text_PCharlieDefeat
	msgbox Route2BoP_Text_PCharliePost, MSGBOX_AUTOCLOSE
	end

Route2BoP_Text_PCharlieIntro:
	.string "Charlie: The one that got away was\nTHIS big. Like my Pokemon.$"

Route2BoP_Text_PCharlieDefeat:
	.string "Also got away on me.$"

Route2BoP_Text_PCharliePost:
	.string "Tide's turning. Good luck out\nthere.$"

Route2BoP_EventScript_PDylan::
	trainerbattle_single TRAINER_RBOP_DYLAN, Route2BoP_Text_PDylanIntro, Route2BoP_Text_PDylanDefeat
	msgbox Route2BoP_Text_PDylanPost, MSGBOX_AUTOCLOSE
	end

Route2BoP_Text_PDylanIntro:
	.string "Dylan: I've tramped every track in\nthis region. Fight me.$"

Route2BoP_Text_PDylanDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route2BoP_Text_PDylanPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"
