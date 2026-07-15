Route5_MapScripts::
	.byte 0

Route5_EventScript_Pita::
	trainerbattle_single TRAINER_R5_PITA, Route5_Text_PitaIntro, Route5_Text_PitaDefeat
	msgbox Route5_Text_PitaPost, MSGBOX_AUTOCLOSE
	end

Route5_EventScript_Eru::
	trainerbattle_single TRAINER_R5_ERU, Route5_Text_EruIntro, Route5_Text_EruDefeat
	msgbox Route5_Text_EruPost, MSGBOX_AUTOCLOSE
	end

Route5_Text_PitaIntro:
	.string "The ground steams all the way\n"
	.string "to the lake!\p"
	.string "My Slugma's never been happier.\n"
	.string "Warm up, would you?$"

Route5_Text_PitaDefeat:
	.string "Steamed and served…$"

Route5_Text_PitaPost:
	.string "They say the whole plateau is\n"
	.string "one sleeping volcano.\p"
	.string "I sleep great, personally.$"

Route5_Text_EruIntro:
	.string "I walked in from the Desert\n"
	.string "Road. Nothing out there but\l"
	.string "wind and one very fit Onix.\p"
	.string "…This Onix. Battle!$"

Route5_Text_EruDefeat:
	.string "Rocked to sleep!$"

Route5_Text_EruPost:
	.string "Taupo's south of here.\p"
	.string "Nice town. Everyone stands\n"
	.string "around looking at the east road\l"
	.string "like it owes them money.$"

Route5_EventScript_PJake::
	trainerbattle_single TRAINER_R5P_JAKE, Route5_Text_PJakeIntro, Route5_Text_PJakeDefeat
	msgbox Route5_Text_PJakePost, MSGBOX_AUTOCLOSE
	end

Route5_Text_PJakeIntro:
	.string "Jake: I've tramped every track in\nthis region. Fight me.$"

Route5_Text_PJakeDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route5_Text_PJakePost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route5_EventScript_PJess::
	trainerbattle_single TRAINER_R5P_JESS, Route5_Text_PJessIntro, Route5_Text_PJessDefeat
	msgbox Route5_Text_PJessPost, MSGBOX_AUTOCLOSE
	end

Route5_Text_PJessIntro:
	.string "Jess: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route5_Text_PJessDefeat:
	.string "The forecast said nothing\nabout you.$"

Route5_Text_PJessPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route5_EventScript_PKayla::
	trainerbattle_single TRAINER_R5P_KAYLA, Route5_Text_PKaylaIntro, Route5_Text_PKaylaDefeat
	msgbox Route5_Text_PKaylaPost, MSGBOX_AUTOCLOSE
	end

Route5_Text_PKaylaIntro:
	.string "Kayla: Sixty years I've watched this\nland. Show me something new.$"

Route5_Text_PKaylaDefeat:
	.string "…That was new.$"

Route5_Text_PKaylaPost:
	.string "The land remembers everyone\nwho crosses it.$"

Route5_EventScript_PLiam::
	trainerbattle_single TRAINER_R5P_LIAM, Route5_Text_PLiamIntro, Route5_Text_PLiamDefeat
	msgbox Route5_Text_PLiamPost, MSGBOX_AUTOCLOSE
	end

Route5_Text_PLiamIntro:
	.string "Liam: DOC ranger. Checking traps.\nAnd checking trainers.$"

Route5_Text_PLiamDefeat:
	.string "Pest-free AND beaten.$"

Route5_Text_PLiamPost:
	.string "Keep to the track and take\nyour rubbish out, eh.$"

Route5_EventScript_PLucas::
	trainerbattle_single TRAINER_R5P_LUCAS, Route5_Text_PLucasIntro, Route5_Text_PLucasDefeat
	msgbox Route5_Text_PLucasPost, MSGBOX_AUTOCLOSE
	end

Route5_Text_PLucasIntro:
	.string "Lucas: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route5_Text_PLucasDefeat:
	.string "You can have the sammie.$"

Route5_Text_PLucasPost:
	.string "Worth it. Rematch at smoko?$"

Route5_EventScript_PMaddie::
	trainerbattle_single TRAINER_R5P_MADDIE, Route5_Text_PMaddieIntro, Route5_Text_PMaddieDefeat
	msgbox Route5_Text_PMaddiePost, MSGBOX_AUTOCLOSE
	end

Route5_Text_PMaddieIntro:
	.string "Maddie: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route5_Text_PMaddieDefeat:
	.string "The forecast said nothing\nabout you.$"

Route5_Text_PMaddiePost:
	.string "Southerly's coming. Take care\nup the track.$"

Route5_EventScript_PMason::
	trainerbattle_single TRAINER_R5P_MASON, Route5_Text_PMasonIntro, Route5_Text_PMasonDefeat
	msgbox Route5_Text_PMasonPost, MSGBOX_AUTOCLOSE
	end

Route5_Text_PMasonIntro:
	.string "Mason: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route5_Text_PMasonDefeat:
	.string "The forecast said nothing\nabout you.$"

Route5_Text_PMasonPost:
	.string "Southerly's coming. Take care\nup the track.$"
