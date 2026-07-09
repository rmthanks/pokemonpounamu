Route6_MapScripts::
	.byte 0

Route6_EventScript_Sol::
	trainerbattle_single TRAINER_R6_SOL, Route6_Text_SolIntro, Route6_Text_SolDefeat
	msgbox Route6_Text_SolPost, MSGBOX_AUTOCLOSE
	end

Route6_EventScript_Nova::
	trainerbattle_single TRAINER_R6_NOVA, Route6_Text_NovaIntro, Route6_Text_NovaDefeat
	msgbox Route6_Text_NovaPost, MSGBOX_AUTOCLOSE
	end

Route6_Text_SolIntro:
	.string "Top of the South! Sunniest, artiest, most laid-back corner of the country.\pMy Manectric's the only thing here in a hurry. Battle!$"
Route6_Text_SolDefeat:
	.string "Chur, you got me.$"
Route6_Text_SolPost:
	.string "Whakatu's down the road. Nicest people, worst parking.$"

Route6_Text_NovaIntro:
	.string "Cloud-watching's a sport here! My Altaria IS a cloud. Sort of.\pBattle us and admire the view!$"
Route6_Text_NovaDefeat:
	.string "Clouded over…$"
Route6_Text_NovaPost:
	.string "On a clear day the whole Tasman opens up. Golden sand for miles.$"

