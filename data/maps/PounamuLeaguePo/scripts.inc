PounamuLeaguePo_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PounamuLeaguePo_OnFrame
	.byte 0

PounamuLeaguePo_OnFrame:
	map_script_2 VAR_TEMP_1, 0, PounamuLeaguePo_EventScript_Encounter
	.2byte 0

PounamuLeaguePo_EventScript_Encounter::
	lockall
	setvar VAR_TEMP_1, 1
	applymovement OBJ_EVENT_ID_PLAYER, PounamuLeaguePo_Movement_FaceLeader
	waitmovement 0
	msgbox PounamuLeaguePo_Text_Pre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PO, PounamuLeaguePo_Text_Defeat
	msgbox PounamuLeaguePo_Text_AfterBattle, MSGBOX_DEFAULT
	msgbox PounamuLeaguePo_Text_Onward, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_POUNAMU_LEAGUE_MAUI, 5, 16
	waitstate
	releaseall
	end

PounamuLeaguePo_Movement_FaceLeader:
	face_up
	step_end

PounamuLeaguePo_EventScript_Po::
	msgbox PounamuLeaguePo_Text_Pre, MSGBOX_NPC
	end

PounamuLeaguePo_Text_Pre:
	.string "Po: Welcome to the last wall, e hoa.\pI am Wairua. The spirit. I keep the connection to the tipuna - the ones who walked before you and walk with you still.\pDo not fear my team. They are not ghosts to frighten children. They are the ones who never truly leave.\pYour whakapapa is standing right behind you, {PLAYER}. It always was. Fight like you know it.$"

PounamuLeaguePo_Text_Defeat:
	.string "…$"

PounamuLeaguePo_Text_AfterBattle:
	.string "Po: …Ae. You feel them now. The whole line of them, at your back.\pYou were never as alone as they made you believe.$"

PounamuLeaguePo_Text_Onward:
	.string "Po: Go through, mokopuna. The roof of the whare waits.\p…You may find you already know the one who holds it up.$"
