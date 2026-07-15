RuapehuAscent_MapScripts::
	.byte 0

RuapehuAscent_EventScript_Descend::
	lockall
	warp MAP_TAUPO, 4, 13
	waitstate
	releaseall
	end

RuapehuAscent_EventScript_ToSummit::
	lockall
	warp MAP_RUAPEHU_SUMMIT, 23, 30
	waitstate
	releaseall
	end

RuapehuAscent_EventScript_PYaz::
	trainerbattle_single TRAINER_RUAP_YAZ, RuapehuAscent_Text_PYazIntro, RuapehuAscent_Text_PYazDefeat
	msgbox RuapehuAscent_Text_PYazPost, MSGBOX_AUTOCLOSE
	end

RuapehuAscent_Text_PYazIntro:
	.string "Yaz: Sixty years I've watched this\nland. Show me something new.$"

RuapehuAscent_Text_PYazDefeat:
	.string "…That was new.$"

RuapehuAscent_Text_PYazPost:
	.string "The land remembers everyone\nwho crosses it.$"

RuapehuAscent_EventScript_PZeb::
	trainerbattle_single TRAINER_RUAP_ZEB, RuapehuAscent_Text_PZebIntro, RuapehuAscent_Text_PZebDefeat
	msgbox RuapehuAscent_Text_PZebPost, MSGBOX_AUTOCLOSE
	end

RuapehuAscent_Text_PZebIntro:
	.string "Zeb: I train where the weather's\nworst. Makes us honest.$"

RuapehuAscent_Text_PZebDefeat:
	.string "Honestly beaten.$"

RuapehuAscent_Text_PZebPost:
	.string "Strength is showing up in\nthe rain.$"

RuapehuAscent_EventScript_PAriki::
	trainerbattle_single TRAINER_RUAP_ARIKI, RuapehuAscent_Text_PArikiIntro, RuapehuAscent_Text_PArikiDefeat
	msgbox RuapehuAscent_Text_PArikiPost, MSGBOX_AUTOCLOSE
	end

RuapehuAscent_Text_PArikiIntro:
	.string "Ariki: I train where the weather's\nworst. Makes us honest.$"

RuapehuAscent_Text_PArikiDefeat:
	.string "Honestly beaten.$"

RuapehuAscent_Text_PArikiPost:
	.string "Strength is showing up in\nthe rain.$"

RuapehuAscent_EventScript_PHori::
	trainerbattle_single TRAINER_RUAP_HORI, RuapehuAscent_Text_PHoriIntro, RuapehuAscent_Text_PHoriDefeat
	msgbox RuapehuAscent_Text_PHoriPost, MSGBOX_AUTOCLOSE
	end

RuapehuAscent_Text_PHoriIntro:
	.string "Heta: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

RuapehuAscent_Text_PHoriDefeat:
	.string "The forecast said nothing\nabout you.$"

RuapehuAscent_Text_PHoriPost:
	.string "Southerly's coming. Take care\nup the track.$"

RuapehuAscent_EventScript_PKupe::
	trainerbattle_single TRAINER_RUAP_KUPE, RuapehuAscent_Text_PKupeIntro, RuapehuAscent_Text_PKupeDefeat
	msgbox RuapehuAscent_Text_PKupePost, MSGBOX_AUTOCLOSE
	end

RuapehuAscent_Text_PKupeIntro:
	.string "Makareta: Sixty years I've watched this\nland. Show me something new.$"

RuapehuAscent_Text_PKupeDefeat:
	.string "…That was new.$"

RuapehuAscent_Text_PKupePost:
	.string "The land remembers everyone\nwho crosses it.$"
