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


Route6_EventScript_PNina::
	trainerbattle_single TRAINER_R6P_NINA, Route6_Text_PNinaIntro, Route6_Text_PNinaDefeat
	msgbox Route6_Text_PNinaPost, MSGBOX_AUTOCLOSE
	end

Route6_Text_PNinaIntro:
	.string "Nina: I've been training out here\nALL morning!$"

Route6_Text_PNinaDefeat:
	.string "Okay, MOST of the morning.$"

Route6_Text_PNinaPost:
	.string "Don't tell my nan I lost.$"

Route6_EventScript_POtis::
	trainerbattle_single TRAINER_R6P_OTIS, Route6_Text_POtisIntro, Route6_Text_POtisDefeat
	msgbox Route6_Text_POtisPost, MSGBOX_AUTOCLOSE
	end

Route6_Text_POtisIntro:
	.string "Otis: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route6_Text_POtisDefeat:
	.string "The forecast said nothing\nabout you.$"

Route6_Text_POtisPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route6_EventScript_PPippa::
	trainerbattle_single TRAINER_R6P_PIPPA, Route6_Text_PPippaIntro, Route6_Text_PPippaDefeat
	msgbox Route6_Text_PPippaPost, MSGBOX_AUTOCLOSE
	end

Route6_Text_PPippaIntro:
	.string "Pippa: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route6_Text_PPippaDefeat:
	.string "You earned the view.$"

Route6_Text_PPippaPost:
	.string "One more ridge. There's always\none more ridge.$"

Route6_EventScript_PReid::
	trainerbattle_single TRAINER_R6P_REID, Route6_Text_PReidIntro, Route6_Text_PReidDefeat
	msgbox Route6_Text_PReidPost, MSGBOX_AUTOCLOSE
	end

Route6_Text_PReidIntro:
	.string "Reid: You've got badges. I've got\nstandards. Let's see.$"

Route6_Text_PReidDefeat:
	.string "Standards met.$"

Route6_Text_PReidPost:
	.string "The League's tougher than me.\nBarely.$"

Route6_EventScript_PStella::
	trainerbattle_single TRAINER_R6P_STELLA, Route6_Text_PStellaIntro, Route6_Text_PStellaDefeat
	msgbox Route6_Text_PStellaPost, MSGBOX_AUTOCLOSE
	end

Route6_Text_PStellaIntro:
	.string "Stella: Kaitiaki of this stretch.\nShow me your manners.$"

Route6_Text_PStellaDefeat:
	.string "Manners AND muscle. Ka pai.$"

Route6_Text_PStellaPost:
	.string "Leave it better than you\nfound it.$"

Route6_EventScript_PTroy::
	trainerbattle_single TRAINER_R6P_TROY, Route6_Text_PTroyIntro, Route6_Text_PTroyDefeat
	msgbox Route6_Text_PTroyPost, MSGBOX_AUTOCLOSE
	end

Route6_Text_PTroyIntro:
	.string "Troy: Between milkings. You've got\nten minutes. Go.$"

Route6_Text_PTroyDefeat:
	.string "Back to the shed, then.$"

Route6_Text_PTroyPost:
	.string "Rain's coming. Good for the\ngrass, good for nothing else.$"

Route6_EventScript_PUna::
	trainerbattle_single TRAINER_R6P_UNA, Route6_Text_PUnaIntro, Route6_Text_PUnaDefeat
	msgbox Route6_Text_PUnaPost, MSGBOX_AUTOCLOSE
	end

Route6_Text_PUnaIntro:
	.string "Una: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route6_Text_PUnaDefeat:
	.string "You can have the sammie.$"

Route6_Text_PUnaPost:
	.string "Worth it. Rematch at smoko?$"
