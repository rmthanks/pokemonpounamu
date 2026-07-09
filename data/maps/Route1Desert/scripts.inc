Route1Desert_MapScripts::
	.byte 0

Route1Desert_EventScript_Koa::
	trainerbattle_single TRAINER_R1D_KOA, Route1Desert_Text_KoaIntro, Route1Desert_Text_KoaDefeat
	msgbox Route1Desert_Text_KoaPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_EventScript_Ari::
	trainerbattle_single TRAINER_R1D_ARI, Route1Desert_Text_AriIntro, Route1Desert_Text_AriDefeat
	msgbox Route1Desert_Text_AriPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_KoaIntro:
	.string "The Desert Road! Nothing but\n"
	.string "tussock and three volcanoes\l"
	.string "watching you.\p"
	.string "They won't battle. I will!$"

Route1Desert_Text_KoaDefeat:
	.string "Blown flat.$"

Route1Desert_Text_KoaPost:
	.string "Those mountains south are tapu.\n"
	.string "Tongariro. You'll want to bow,\l"
	.string "even from here.$"

Route1Desert_Text_AriIntro:
	.string "Coldest, highest, emptiest road\n"
	.string "in the North Island.\p"
	.string "I love it. My Numel keeps me\n"
	.string "warm. Come on!$"

Route1Desert_Text_AriDefeat:
	.string "Out cold on the plateau…$"

Route1Desert_Text_AriPost:
	.string "West from here the road forgets\n"
	.string "itself for a while.\p"
	.string "Route 43. The Forgotten World.\n"
	.string "Beautiful and a bit spooky.$"
