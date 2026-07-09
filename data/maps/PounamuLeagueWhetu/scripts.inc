PounamuLeagueWhetu_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PounamuLeagueWhetu_OnFrame
	.byte 0

PounamuLeagueWhetu_OnFrame:
	map_script_2 VAR_TEMP_1, 0, PounamuLeagueWhetu_EventScript_Encounter
	.2byte 0

PounamuLeagueWhetu_EventScript_Encounter::
	lockall
	setvar VAR_TEMP_1, 1
	applymovement OBJ_EVENT_ID_PLAYER, PounamuLeagueWhetu_Movement_FaceLeader
	waitmovement 0
	msgbox PounamuLeagueWhetu_Text_Pre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WHETU, PounamuLeagueWhetu_Text_Defeat
	msgbox PounamuLeagueWhetu_Text_AfterBattle, MSGBOX_DEFAULT
	msgbox PounamuLeagueWhetu_Text_Onward, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_POUNAMU_LEAGUE_PO, 5, 16
	waitstate
	releaseall
	end

PounamuLeagueWhetu_Movement_FaceLeader:
	face_up
	step_end

PounamuLeagueWhetu_EventScript_Whetu::
	msgbox PounamuLeagueWhetu_Text_Pre, MSGBOX_NPC
	end

PounamuLeagueWhetu_Text_Pre:
	.string "Whetu: I read the stars for a living, {PLAYER}. Matariki. The whole sky-map.\pI am Hinengaro. The mind. The wall no one sees.\pI've watched your path across the motu like a constellation drawing itself. The exile. The long way round. The badges, one by one.\p…You think clearer now than the frightened child who left the Bay. Prove it.$"

PounamuLeagueWhetu_Text_Defeat:
	.string "…$"

PounamuLeagueWhetu_Text_AfterBattle:
	.string "Whetu: Clear-seeing. Yes. You know who you are now - not who they told you you were.\pThat's the whole of the mind, that.$"

PounamuLeagueWhetu_Text_Onward:
	.string "Whetu: One wall left. Po. The spirit.\pShe keeps the door to those who came before. Be gentle in there. Be brave.$"
