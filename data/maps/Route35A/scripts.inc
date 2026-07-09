Route35A_MapScripts::
	.byte 0

Route35A_EventScript_Tai::
	trainerbattle_single TRAINER_R35_TAI, Route35A_Text_TaiIntro, Route35A_Text_TaiDefeat
	msgbox Route35A_Text_TaiPost, MSGBOX_AUTOCLOSE
	end

Route35A_EventScript_Nikora::
	trainerbattle_single TRAINER_R35_NIKORA, Route35A_Text_NikoraIntro, Route35A_Text_NikoraDefeat
	msgbox Route35A_Text_NikoraPost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_TaiIntro:
	.string "Three hundred k of coast and\n"
	.string "every k is mine.\p"
	.string "Well. Mine and the fish's.$"

Route35A_Text_TaiDefeat:
	.string "Reeled in by a ranger!$"

Route35A_Text_TaiPost:
	.string "You won't see another shop till\n"
	.string "Opotiki, e hoa.\p"
	.string "You'll see everything else\n"
	.string "though. Look up sometimes.$"

Route35A_Text_NikoraIntro:
	.string "I've camped every bay on this\n"
	.string "Cape.\p"
	.string "My Electrike keeps the tent\n"
	.string "warm. Mostly on purpose!$"

Route35A_Text_NikoraDefeat:
	.string "Sparks out!$"

Route35A_Text_NikoraPost:
	.string "At night out here the sky goes\n"
	.string "all the way down to the sea.\p"
	.string "No lights between here and\n"
	.string "forever.$"
