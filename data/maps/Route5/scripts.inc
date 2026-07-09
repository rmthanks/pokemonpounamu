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
