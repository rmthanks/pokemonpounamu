Route5Ranges_MapScripts::
	.byte 0

@ ------------------------------------------------------------------
@ The exemplar gate. You can SEE the road home. You cannot take it.
@ ------------------------------------------------------------------
Route5Ranges_EventScript_Grunt1::
	lock
	faceplayer
	msgbox Route5Ranges_Text_Grunt1, MSGBOX_DEFAULT
	release
	end

Route5Ranges_EventScript_Grunt2::
	lock
	faceplayer
	msgbox Route5Ranges_Text_Grunt2, MSGBOX_DEFAULT
	release
	end

Route5Ranges_EventScript_Sign::
	msgbox Route5Ranges_Text_Sign, MSGBOX_SIGN
	end

Route5Ranges_Text_Grunt1:
	.string "…You.\p"
	.string "We know your face. You're ON\n"
	.string "the list. THE list.\p"
	.string "The Bay doesn't know you any\n"
	.string "more, remember?$"

Route5Ranges_Text_Grunt2:
	.string "Road's right there, eh.\p"
	.string "Ahuriri. Three days over the\n"
	.string "ranges. Prettiest walk in the\l"
	.string "North Island.\p"
	.string "…For everyone except you.\p"
	.string "Boss's little sibling walks the\n"
	.string "LONG way. Boss was very clear.$"

Route5Ranges_Text_Sign:
	.string "ROUTE 5 EAST\n"
	.string "AHURIRI via the Titiokura ranges.\p"
	.string "A handwritten note is nailed\n"
	.string "underneath:\p"
	.string "“CLOSED. Bay business.\n"
	.string "Don't ask.”$"

Route5Ranges_EventScript_PPete::
	trainerbattle_single TRAINER_R5RP_PETE, Route5Ranges_Text_PPeteIntro, Route5Ranges_Text_PPeteDefeat
	msgbox Route5Ranges_Text_PPetePost, MSGBOX_AUTOCLOSE
	end

Route5Ranges_Text_PPeteIntro:
	.string "Pete: This is protected land.\nProve you respect it.$"

Route5Ranges_Text_PPeteDefeat:
	.string "You fight like you care.$"

Route5Ranges_Text_PPetePost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Route5Ranges_EventScript_PRata::
	trainerbattle_single TRAINER_R5RP_RATA, Route5Ranges_Text_PRataIntro, Route5Ranges_Text_PRataDefeat
	msgbox Route5Ranges_Text_PRataPost, MSGBOX_AUTOCLOSE
	end

Route5Ranges_Text_PRataIntro:
	.string "Reka: This is protected land.\nProve you respect it.$"

Route5Ranges_Text_PRataDefeat:
	.string "You fight like you care.$"

Route5Ranges_Text_PRataPost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Route5Ranges_EventScript_PSid::
	trainerbattle_single TRAINER_R5RP_SID, Route5Ranges_Text_PSidIntro, Route5Ranges_Text_PSidDefeat
	msgbox Route5Ranges_Text_PSidPost, MSGBOX_AUTOCLOSE
	end

Route5Ranges_Text_PSidIntro:
	.string "Sid: I've tramped every track in\nthis region. Fight me.$"

Route5Ranges_Text_PSidDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route5Ranges_Text_PSidPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route5Ranges_EventScript_PTila::
	trainerbattle_single TRAINER_R5RP_TILA, Route5Ranges_Text_PTilaIntro, Route5Ranges_Text_PTilaDefeat
	msgbox Route5Ranges_Text_PTilaPost, MSGBOX_AUTOCLOSE
	end

Route5Ranges_Text_PTilaIntro:
	.string "Tila: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route5Ranges_Text_PTilaDefeat:
	.string "You earned the view.$"

Route5Ranges_Text_PTilaPost:
	.string "One more ridge. There's always\none more ridge.$"

Route5Ranges_EventScript_PUmi::
	trainerbattle_single TRAINER_R5RP_UMI, Route5Ranges_Text_PUmiIntro, Route5Ranges_Text_PUmiDefeat
	msgbox Route5Ranges_Text_PUmiPost, MSGBOX_AUTOCLOSE
	end

Route5Ranges_Text_PUmiIntro:
	.string "Umi: Sixty years I've watched this\nland. Show me something new.$"

Route5Ranges_Text_PUmiDefeat:
	.string "…That was new.$"

Route5Ranges_Text_PUmiPost:
	.string "The land remembers everyone\nwho crosses it.$"

Route5Ranges_EventScript_PVada::
	trainerbattle_single TRAINER_R5RP_VADA, Route5Ranges_Text_PVadaIntro, Route5Ranges_Text_PVadaDefeat
	msgbox Route5Ranges_Text_PVadaPost, MSGBOX_AUTOCLOSE
	end

Route5Ranges_Text_PVadaIntro:
	.string "Vada: I've been training out here\nALL morning!$"

Route5Ranges_Text_PVadaDefeat:
	.string "Okay, MOST of the morning.$"

Route5Ranges_Text_PVadaPost:
	.string "Don't tell my nan I lost.$"

Route5Ranges_EventScript_PWes::
	trainerbattle_single TRAINER_R5RP_WES, Route5Ranges_Text_PWesIntro, Route5Ranges_Text_PWesDefeat
	msgbox Route5Ranges_Text_PWesPost, MSGBOX_AUTOCLOSE
	end

Route5Ranges_Text_PWesIntro:
	.string "Wes: I train where the weather's\nworst. Makes us honest.$"

Route5Ranges_Text_PWesDefeat:
	.string "Honestly beaten.$"

Route5Ranges_Text_PWesPost:
	.string "Strength is showing up in\nthe rain.$"
