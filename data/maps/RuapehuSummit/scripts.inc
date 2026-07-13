RuapehuSummit_MapScripts::
	.byte 0

RuapehuSummit_EventScript_Descend::
	lockall
	warp MAP_RUAPEHU_ASCENT, 19, 12
	waitstate
	releaseall
	end

@ ------------------------------------------------------------------
@ Red, the Pounamu way. Strongest single fight in the game.
@ Minimal dialogue by design (endgame canon).
@ ------------------------------------------------------------------
RuapehuSummit_EventScript_Tama::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x90E, RuapehuSummit_EventScript_TamaAtPeace
	goto_if_set FLAG_UNUSED_0x90D, RuapehuSummit_EventScript_TamaRelease
	msgbox RuapehuSummit_Text_TamaPre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TAMA_RUAPEHU, RuapehuSummit_Text_TamaDefeat
	setflag FLAG_UNUSED_0x90D
	msgbox RuapehuSummit_Text_TamaAfter, MSGBOX_DEFAULT
	release
	end

RuapehuSummit_EventScript_TamaRelease::
	msgbox RuapehuSummit_Text_TamaReleaseA, MSGBOX_DEFAULT
	goto_if_set FLAG_UNUSED_0x901, RuapehuSummit_EventScript_GiveHoOh
	givemon SPECIES_LUGIA, 70
	goto RuapehuSummit_EventScript_ReleaseDone

RuapehuSummit_EventScript_GiveHoOh::
	givemon SPECIES_HO_OH, 70
	goto RuapehuSummit_EventScript_ReleaseDone

RuapehuSummit_EventScript_ReleaseDone::
	setflag FLAG_UNUSED_0x90E
	msgbox RuapehuSummit_Text_TamaReleaseB, MSGBOX_DEFAULT
	release
	end

RuapehuSummit_EventScript_TamaAtPeace::
	msgbox RuapehuSummit_Text_TamaAtPeace, MSGBOX_DEFAULT
	release
	end

RuapehuSummit_Text_TamaPre:
	.string "…\p"
	.string "Tama: …You climbed.$"

RuapehuSummit_Text_TamaDefeat:
	.string "…$"

RuapehuSummit_Text_TamaAfter:
	.string "The wind holds its breath.\p"
	.string "Tama looks past you - out over\n"
	.string "the whole island, to where the\l"
	.string "Bay lies beyond the ranges.\p"
	.string "You raise your hand.\p"
	.string "He looks at it for a long,\n"
	.string "long time.\p"
	.string "Tama: …Same time next climb,\n"
	.string "little brother.$"

RuapehuSummit_Text_TamaReleaseA:
	.string "Tama: This was never mine.\p"
	.string "I took it.\n"
	.string "Here.$"

RuapehuSummit_Text_TamaReleaseB:
	.string "He almost smiles. Almost.$"

RuapehuSummit_Text_TamaAtPeace:
	.string "Tama stands at the crater's\n"
	.string "edge, watching the clouds\l"
	.string "cross the summit.\p"
	.string "You raise a hand.\p"
	.string "…He waved back this time.$"
