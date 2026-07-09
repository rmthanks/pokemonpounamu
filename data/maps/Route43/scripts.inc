Route43_MapScripts::
	.byte 0

Route43_EventScript_Wai::
	trainerbattle_single TRAINER_R43_WAI, Route43_Text_WaiIntro, Route43_Text_WaiDefeat
	msgbox Route43_Text_WaiPost, MSGBOX_AUTOCLOSE
	end

Route43_Text_WaiIntro:
	.string "They call this the Forgotten\n"
	.string "World Highway.\p"
	.string "One lane, one tunnel, one very\n"
	.string "confused Swablu. Battle!$"

Route43_Text_WaiDefeat:
	.string "Lost in the fog…$"

Route43_Text_WaiPost:
	.string "Ngamotu's at the end of the\n"
	.string "road, under the mountain.\p"
	.string "You can't miss the mountain.\n"
	.string "Believe me.$"
