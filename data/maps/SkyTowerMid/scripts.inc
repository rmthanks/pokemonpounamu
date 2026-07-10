SkyTowerMid_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SkyTowerMid_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SkyTowerMid_OnTransition
	.byte 0

SkyTowerMid_OnTransition:
	call_if_set FLAG_UNUSED_0x908, SkyTowerMid_EventScript_NoScene
	end

SkyTowerMid_EventScript_NoScene::
	setvar VAR_TEMP_1, 1
	return

SkyTowerMid_OnFrame:
	map_script_2 VAR_TEMP_1, 0, SkyTowerMid_EventScript_Awhi
	.2byte 0

@ Awhi: Tama's ex, Mob-born, the one who cared for you as a kid.
@ Here she chooses. This is what qualifies her for the Whanau wall.
SkyTowerMid_EventScript_Awhi::
	lockall
	msgbox SkyTowerMid_Text_Awhi1, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TOWER_GRUNT_3, SkyTowerMid_Text_CaptainDefeat
	msgbox SkyTowerMid_Text_Awhi2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_UNUSED_0x908
	setvar VAR_TEMP_1, 1
	removeobject 1
	releaseall
	warp MAP_SKY_TOWER_TOP, 5, 16
	waitstate
	end

SkyTowerMid_Text_Awhi1:
	.string "Awhi stands between you and the\n"
	.string "stairs. She doesn't reach for\l"
	.string "a Poke Ball.\p"
	.string "Awhi: I told him I'd stop you.\p"
	.string "…I told HIM that. I never told\n"
	.string "YOU that.\p"
	.string "The captain behind me heard\n"
	.string "the first version. Sorry, kid.$"

SkyTowerMid_Text_CaptainDefeat:
	.string "“…Awhi. You didn't lift a\n"
	.string "finger.”$"

SkyTowerMid_Text_Awhi2:
	.string "Awhi: No. I didn't.\p"
	.string "She looks at the stairs, then\n"
	.string "at you - the kid she walked to\l"
	.string "kura when the house was loud.\p"
	.string "Awhi: He's not up there, you\n"
	.string "know. Not really. Just the\l"
	.string "thing wearing his hurt.\p"
	.string "Bring back whichever one of\n"
	.string "them is left.\p"
	.string "…I'll be downstairs. With the\n"
	.string "whanau. Where I should've been.$"

SkyTowerMid_EventScript_AwhiIdle::
	msgbox SkyTowerMid_Text_AwhiIdle, MSGBOX_NPC
	end

SkyTowerMid_Text_AwhiIdle:
	.string "Awhi: Go on, kid. Stairs are\n"
	.string "behind me now.$"
