Route7_MapScripts::
	.byte 0

Route7_EventScript_Kae::
	trainerbattle_single TRAINER_R7_KAE, Route7_Text_KaeIntro, Route7_Text_KaeDefeat
	msgbox Route7_Text_KaePost, MSGBOX_AUTOCLOSE
	end

Route7_EventScript_Rangi::
	trainerbattle_single TRAINER_R7_RANGI, Route7_Text_RangiIntro, Route7_Text_RangiDefeat
	msgbox Route7_Text_RangiPost, MSGBOX_AUTOCLOSE
	end

Route7_Text_KaeIntro:
	.string "Lewis Pass! Longest, highest, loneliest road in the country.\pIf you make it through, you've earned Otautahi. Onix, go!$"
Route7_Text_KaeDefeat:
	.string "Passed…$"
Route7_Text_KaePost:
	.string "Beech forest the whole way. Robins'll follow you for company. Bit of a laugh.$"

Route7_Text_RangiIntro:
	.string "Snow on the tops even now. My Absol smells the weather turning before I do.\pBattle before the front hits!$"
Route7_Text_RangiDefeat:
	.string "Storm's here…$"
Route7_Text_RangiPost:
	.string "Down out of the pass it flattens right out. Canterbury Plains. Big sky, straight roads.$"

