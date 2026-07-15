SkyTowerLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SkyTowerLobby_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SkyTowerLobby_OnTransition
	.byte 0

SkyTowerLobby_OnTransition:
	call_if_set FLAG_UNUSED_0x909, SkyTowerLobby_EventScript_NoScene
	end

SkyTowerLobby_EventScript_NoScene::
	setvar VAR_TEMP_1, 1
	return

SkyTowerLobby_OnFrame:
	map_script_2 VAR_TEMP_1, 0, SkyTowerLobby_EventScript_Gauntlet
	.2byte 0

SkyTowerLobby_EventScript_Gauntlet::
	lockall
	msgbox SkyTowerLobby_Text_Arrive, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TOWER_GRUNT_1, SkyTowerLobby_Text_Grunt1Defeat
	msgbox SkyTowerLobby_Text_Grunt2Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TOWER_GRUNT_2, SkyTowerLobby_Text_Grunt2Defeat
	setflag FLAG_UNUSED_0x909
	setvar VAR_TEMP_1, 1
	msgbox SkyTowerLobby_Text_LiftOpen, MSGBOX_DEFAULT
	closemessage
	releaseall
	warp MAP_SKY_TOWER_MID, 5, 16
	waitstate
	end

SkyTowerLobby_Text_Arrive:
	.string "The lobby is marble and silence.\p"
	.string "Two enforcers peel away from\n"
	.string "the lift doors.\p"
	.string "“The boss's brother. He said\n"
	.string "you'd come. He's been saying it\l"
	.string "for YEARS.”$"

SkyTowerLobby_Text_Grunt1Defeat:
	.string "“…Lift's that way. Like he\n"
	.string "said.”$"

SkyTowerLobby_Text_Grunt2Intro:
	.string "“My turn. Nothing personal -\n"
	.string "actually, no. It's ALL\l"
	.string "personal, with this family.”$"

SkyTowerLobby_Text_Grunt2Defeat:
	.string "“All the way up, then.”$"

SkyTowerLobby_Text_LiftOpen:
	.string "The lift doors stand open.\p"
	.string "Above you: the whole tower,\n"
	.string "and everything it took.$"

SkyTowerLobby_EventScript_PUrsula::
	trainerbattle_single TRAINER_TWEX_URSULA, SkyTowerLobby_Text_PUrsulaIntro, SkyTowerLobby_Text_PUrsulaDefeat
	msgbox SkyTowerLobby_Text_PUrsulaPost, MSGBOX_AUTOCLOSE
	end

SkyTowerLobby_Text_PUrsulaIntro:
	.string "Ursula: You've got badges. I've got\nstandards. Let's see.$"

SkyTowerLobby_Text_PUrsulaDefeat:
	.string "Standards met.$"

SkyTowerLobby_Text_PUrsulaPost:
	.string "The League's tougher than me.\nBarely.$"

SkyTowerLobby_EventScript_PVera::
	trainerbattle_single TRAINER_TWEX_VERA, SkyTowerLobby_Text_PVeraIntro, SkyTowerLobby_Text_PVeraDefeat
	msgbox SkyTowerLobby_Text_PVeraPost, MSGBOX_AUTOCLOSE
	end

SkyTowerLobby_Text_PVeraIntro:
	.string "Vera: You've got badges. I've got\nstandards. Let's see.$"

SkyTowerLobby_Text_PVeraDefeat:
	.string "Standards met.$"

SkyTowerLobby_Text_PVeraPost:
	.string "The League's tougher than me.\nBarely.$"
