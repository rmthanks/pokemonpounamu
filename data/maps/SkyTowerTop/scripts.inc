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
	msgbox SkyTowerTop_Text_FallenFind, MSGBOX_DEFAULT
	msgbox SkyTowerTop_Text_FallenRata, MSGBOX_DEFAULT
	msgbox SkyTowerTop_Text_FallenKauri, MSGBOX_DEFAULT
	msgbox SkyTowerTop_Text_FallenClose, MSGBOX_DEFAULT
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

SkyTowerTop_EventScript_FallenRata::
	msgbox SkyTowerTop_Text_FallenRata, MSGBOX_NPC
	end

SkyTowerTop_EventScript_FallenKauri::
	msgbox SkyTowerTop_Text_FallenKauri, MSGBOX_NPC
	end

SkyTowerTop_Text_FallenFind:
	.string "The last door opens onto wind\n"
	.string "and glass -\p"
	.string "and the first thing you see is\n"
	.string "not your brother.\p"
	.string "It's them.\p"
	.string "Mum. Dad. Propped against the\n"
	.string "rail on opposite sides of the\l"
	.string "deck, beaten.\p"
	.string "They each came alone.\p"
	.string "They each found out.$"

SkyTowerTop_Text_FallenRata:
	.string "Rata: …Hello, love.\p"
	.string "Don't fuss. I've fallen out of\n"
	.string "more trees than this.\p"
	.string "…I came for my boy. The old\n"
	.string "way. On my own two feet, on my\l"
	.string "own stubbornness.\p"
	.string "It wasn't enough. It was never\n"
	.string "going to be.\p"
	.string "…Look at your father, there.\n"
	.string "The fool came alone too.$"

SkyTowerTop_Text_FallenKauri:
	.string "Kauri: …Kid.\p"
	.string "Twenty years I told people\n"
	.string "strength is what you can carry\l"
	.string "by yourself.\p"
	.string "Your mother and I climbed this\n"
	.string "tower one hour apart.\p"
	.string "ONE HOUR. Neither of us called\n"
	.string "the other.\p"
	.string "…We taught him that, you know.\n"
	.string "The alone thing.\p"
	.string "Go. Finish what we couldn't.\n"
	.string "And {PLAYER} -\p"
	.string "don't do it our way.$"

SkyTowerTop_Text_FallenClose:
	.string "They can't stand. They can't\n"
	.string "follow.\p"
	.string "But as you cross the deck, you\n"
	.string "hear it behind you -\p"
	.string "two people who haven't spoken\n"
	.string "in years, talking. Quietly.\p"
	.string "You climb the last stairs with\n"
	.string "their voices at your back.$"
