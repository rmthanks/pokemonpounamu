SkyTowerTop_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SkyTowerTop_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SkyTowerTop_OnTransition
	.byte 0

SkyTowerTop_OnTransition:
	call_if_set FLAG_UNUSED_0x907, SkyTowerTop_EventScript_NoScene
	end

SkyTowerTop_EventScript_NoScene::
	setvar VAR_TEMP_1, 1
	return

SkyTowerTop_OnFrame:
	map_script_2 VAR_TEMP_1, 0, SkyTowerTop_EventScript_Tama
	.2byte 0

@ The summit. The brother. The bird that never chose him.
SkyTowerTop_EventScript_Tama::
	lockall
	msgbox SkyTowerTop_Text_Tama1, MSGBOX_DEFAULT
	goto_if_set FLAG_UNUSED_0x901, SkyTowerTop_EventScript_TamaHasHoOh
	trainerbattle_no_intro TRAINER_TAMA_TOWER_LUGIA, SkyTowerTop_Text_TamaDefeat
	goto SkyTowerTop_EventScript_Recognition

SkyTowerTop_EventScript_TamaHasHoOh::
	trainerbattle_no_intro TRAINER_TAMA_TOWER_HOOH, SkyTowerTop_Text_TamaDefeat
	goto SkyTowerTop_EventScript_Recognition

SkyTowerTop_EventScript_Recognition::
	msgbox SkyTowerTop_Text_Recognition1, MSGBOX_DEFAULT
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 5
	special ShakeCamera
	waitstate
	msgbox SkyTowerTop_Text_Recognition2, MSGBOX_DEFAULT
	playse SE_PIN
	msgbox SkyTowerTop_Text_Police, MSGBOX_DEFAULT
	msgbox SkyTowerTop_Text_AlmostWave, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_UNUSED_0x907
	setvar VAR_TEMP_1, 1
	removeobject 1
	msgbox SkyTowerTop_Text_Gone, MSGBOX_DEFAULT
	releaseall
	end

SkyTowerTop_Text_Tama1:
	.string "The observation deck. The whole\n"
	.string "motu below, going dark.\p"
	.string "He doesn't turn around.\p"
	.string "Tama: You know what you can see\n"
	.string "from up here?\p"
	.string "Everything. Every road they\n"
	.string "made you walk. Every door they\l"
	.string "shut on me.\p"
	.string "Tama: They kept you and lost\n"
	.string "me, and called it love.\p"
	.string "So I took the one they left\n"
	.string "unguarded. The way they left\l"
	.string "ME unguarded.\p"
	.string "…Show me, then. Show me what\n"
	.string "the chosen one learned.$"

SkyTowerTop_Text_TamaDefeat:
	.string "…No.\p"
	.string "No, stay DOWN, you stupid-\p"
	.string "…Why won't it fight for me?$"

SkyTowerTop_Text_Recognition1:
	.string "The stolen bird hangs above the\n"
	.string "deck, dull-eyed, wrong.\p"
	.string "And then - your own rises to\n"
	.string "meet it.\p"
	.string "No one commands it. It simply\n"
	.string "goes: the other half of an old,\l"
	.string "old whole.$"

SkyTowerTop_Text_Recognition2:
	.string "They regard each other across\n"
	.string "the dark - moon and sun, tide\l"
	.string "and dawn.\p"
	.string "The dull eye clears.\p"
	.string "Whatever Tama held it with -\n"
	.string "it isn't holding any more.\p"
	.string "Tama: …no. No, I EARNED-\p"
	.string "It does not even look at him\n"
	.string "as it leaves.\p"
	.string "Nothing he took ever chose him.\n"
	.string "That was always the wound.$"

SkyTowerTop_Text_AlmostWave:
	.string "At the stairwell door he stops.\p"
	.string "His hand lifts -\n"
	.string "halfway -\p"
	.string "Sirens.\p"
	.string "He's gone.$"

SkyTowerTop_Text_Police:
	.string "Sirens - dozens of them,\n"
	.string "rising from the streets below.\p"
	.string "Boots on the stairs.$"

SkyTowerTop_Text_Gone:
	.string "…When the police reach the\n"
	.string "deck, there is only you, and\l"
	.string "the open sky, and two great\l"
	.string "shapes crossing the harbour -\l"
	.string "side by side, then apart.\p"
	.string "Of Tama, no sign at all.\p"
	.string "Somewhere south, a mountain\n"
	.string "waits to teach a man how to\l"
	.string "find himself.$"

SkyTowerTop_EventScript_TamaIdle::
	msgbox SkyTowerTop_Text_TamaIdle, MSGBOX_NPC
	end

SkyTowerTop_Text_TamaIdle:
	.string "He watches the harbour and\n"
	.string "says nothing at all.$"
