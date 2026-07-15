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

Route3_EventScript_PZoe::
	trainerbattle_single TRAINER_R3P_ZOE, Route3_Text_PZoeIntro, Route3_Text_PZoeDefeat
	msgbox Route3_Text_PZoePost, MSGBOX_AUTOCLOSE
	end

Route3_Text_PZoeIntro:
	.string "Zoe: Between milkings. You've got\nten minutes. Go.$"

Route3_Text_PZoeDefeat:
	.string "Back to the shed, then.$"

Route3_Text_PZoePost:
	.string "Rain's coming. Good for the\ngrass, good for nothing else.$"

Route3_EventScript_PAshley::
	trainerbattle_single TRAINER_R3P_ASHLEY, Route3_Text_PAshleyIntro, Route3_Text_PAshleyDefeat
	msgbox Route3_Text_PAshleyPost, MSGBOX_AUTOCLOSE
	end

Route3_Text_PAshleyIntro:
	.string "Ashley: Between milkings. You've got\nten minutes. Go.$"

Route3_Text_PAshleyDefeat:
	.string "Back to the shed, then.$"

Route3_Text_PAshleyPost:
	.string "Rain's coming. Good for the\ngrass, good for nothing else.$"

Route3_EventScript_PBella::
	trainerbattle_single TRAINER_R3P_BELLA, Route3_Text_PBellaIntro, Route3_Text_PBellaDefeat
	msgbox Route3_Text_PBellaPost, MSGBOX_AUTOCLOSE
	end

Route3_Text_PBellaIntro:
	.string "Bella: I've tramped every track in\nthis region. Fight me.$"

Route3_Text_PBellaDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route3_Text_PBellaPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route3_EventScript_PCody::
	trainerbattle_single TRAINER_R3P_CODY, Route3_Text_PCodyIntro, Route3_Text_PCodyDefeat
	msgbox Route3_Text_PCodyPost, MSGBOX_AUTOCLOSE
	end

Route3_Text_PCodyIntro:
	.string "Cody: I train where the weather's\nworst. Makes us honest.$"

Route3_Text_PCodyDefeat:
	.string "Honestly beaten.$"

Route3_Text_PCodyPost:
	.string "Strength is showing up in\nthe rain.$"

Route3_EventScript_PDaisy::
	trainerbattle_single TRAINER_R3P_DAISY, Route3_Text_PDaisyIntro, Route3_Text_PDaisyDefeat
	msgbox Route3_Text_PDaisyPost, MSGBOX_AUTOCLOSE
	end

Route3_Text_PDaisyIntro:
	.string "Daisy: DOC ranger. Checking traps.\nAnd checking trainers.$"

Route3_Text_PDaisyDefeat:
	.string "Pest-free AND beaten.$"

Route3_Text_PDaisyPost:
	.string "Keep to the track and take\nyour rubbish out, eh.$"

Route3_EventScript_PEmma::
	trainerbattle_single TRAINER_R3P_EMMA, Route3_Text_PEmmaIntro, Route3_Text_PEmmaDefeat
	msgbox Route3_Text_PEmmaPost, MSGBOX_AUTOCLOSE
	end

Route3_Text_PEmmaIntro:
	.string "Emma: I've tramped every track in\nthis region. Fight me.$"

Route3_Text_PEmmaDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route3_Text_PEmmaPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route3_EventScript_PFlora::
	trainerbattle_single TRAINER_R3P_FLORA, Route3_Text_PFloraIntro, Route3_Text_PFloraDefeat
	msgbox Route3_Text_PFloraPost, MSGBOX_AUTOCLOSE
	end

Route3_Text_PFloraIntro:
	.string "Flora: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route3_Text_PFloraDefeat:
	.string "You can have the sammie.$"

Route3_Text_PFloraPost:
	.string "Worth it. Rematch at smoko?$"
