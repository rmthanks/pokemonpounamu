Route3_MapScripts::
	.byte 0

Route3_EventScript_Rico::
	trainerbattle_single TRAINER_R3_RICO, Route3_Text_RicoIntro, Route3_Text_RicoDefeat
	msgbox Route3_Text_RicoPost, MSGBOX_AUTOCLOSE
	end
Route3_EventScript_Ana::
	trainerbattle_single TRAINER_R3_ANA, Route3_Text_AnaIntro, Route3_Text_AnaDefeat
	msgbox Route3_Text_AnaPost, MSGBOX_AUTOCLOSE
	end

Route3_Text_RicoIntro:
	.string "Surf coast! Best waves in the\n"
	.string "country and nobody around.\p"
	.string "Well. Me. And now you.$"
Route3_Text_RicoDefeat:
	.string "Wiped out.$"
Route3_Text_RicoPost:
	.string "Word from up north is the\n"
	.string "Hawke's Bay Mob's spreading.\p"
	.string "Checkpoints on roads that never\n"
	.string "had them. Even down here.$"
Route3_Text_AnaIntro:
	.string "My Swablu's a cloud with a\n"
	.string "face! Isn't she perfect?\p"
	.string "Battle us and say she's perfect!$"
Route3_Text_AnaDefeat:
	.string "She's still perfect.$"
Route3_Text_AnaPost:
	.string "Whanganui's just south, on the\n"
	.string "big river.\p"
	.string "The river has a legal person,\n"
	.string "you know. A whole person!$"
