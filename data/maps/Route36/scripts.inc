Route36_MapScripts::
	.byte 0

Route36_EventScript_Roadworks::
	msgbox Route36_Text_Roadworks, MSGBOX_NPC
	end

Route36_Text_Roadworks:
	.string "Kia ora! Slip's cleared.\n"
	.string "Rotorua's just over the hill.\p"
	.string "You'll smell it before you\n"
	.string "see it. That's normal.\p"
	.string "That's VERY normal.$"

Route36_EventScript_PElla::
	trainerbattle_single TRAINER_R36_ELLA, Route36_Text_PEllaIntro, Route36_Text_PEllaDefeat
	msgbox Route36_Text_PEllaPost, MSGBOX_AUTOCLOSE
	end

Route36_Text_PEllaIntro:
	.string "Ella: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route36_Text_PEllaDefeat:
	.string "You can have the sammie.$"

Route36_Text_PEllaPost:
	.string "Worth it. Rematch at smoko?$"

Route36_EventScript_PFinn::
	trainerbattle_single TRAINER_R36_FINN, Route36_Text_PFinnIntro, Route36_Text_PFinnDefeat
	msgbox Route36_Text_PFinnPost, MSGBOX_AUTOCLOSE
	end

Route36_Text_PFinnIntro:
	.string "Finn: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route36_Text_PFinnDefeat:
	.string "The forecast said nothing\nabout you.$"

Route36_Text_PFinnPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route36_EventScript_PHarper::
	trainerbattle_single TRAINER_R36_HARPER, Route36_Text_PHarperIntro, Route36_Text_PHarperDefeat
	msgbox Route36_Text_PHarperPost, MSGBOX_AUTOCLOSE
	end

Route36_Text_PHarperIntro:
	.string "Harper: DOC ranger. Checking traps.\nAnd checking trainers.$"

Route36_Text_PHarperDefeat:
	.string "Pest-free AND beaten.$"

Route36_Text_PHarperPost:
	.string "Keep to the track and take\nyour rubbish out, eh.$"

Route36_EventScript_PHunter::
	trainerbattle_single TRAINER_R36_HUNTER, Route36_Text_PHunterIntro, Route36_Text_PHunterDefeat
	msgbox Route36_Text_PHunterPost, MSGBOX_AUTOCLOSE
	end

Route36_Text_PHunterIntro:
	.string "Hunter: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route36_Text_PHunterDefeat:
	.string "You earned the view.$"

Route36_Text_PHunterPost:
	.string "One more ridge. There's always\none more ridge.$"

Route36_EventScript_PIsla::
	trainerbattle_single TRAINER_R36_ISLA, Route36_Text_PIslaIntro, Route36_Text_PIslaDefeat
	msgbox Route36_Text_PIslaPost, MSGBOX_AUTOCLOSE
	end

Route36_Text_PIslaIntro:
	.string "Isla: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route36_Text_PIslaDefeat:
	.string "You can have the sammie.$"

Route36_Text_PIslaPost:
	.string "Worth it. Rematch at smoko?$"

Route36_EventScript_PJack::
	trainerbattle_single TRAINER_R36_JACK, Route36_Text_PJackIntro, Route36_Text_PJackDefeat
	msgbox Route36_Text_PJackPost, MSGBOX_AUTOCLOSE
	end

Route36_Text_PJackIntro:
	.string "Jack: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route36_Text_PJackDefeat:
	.string "The forecast said nothing\nabout you.$"

Route36_Text_PJackPost:
	.string "Southerly's coming. Take care\nup the track.$"
