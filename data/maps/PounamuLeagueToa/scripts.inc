PounamuLeagueToa_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PounamuLeagueToa_OnFrame
	.byte 0

PounamuLeagueToa_OnFrame:
	map_script_2 VAR_TEMP_1, 0, PounamuLeagueToa_EventScript_Encounter
	.2byte 0

PounamuLeagueToa_EventScript_Encounter::
	lockall
	setvar VAR_TEMP_1, 1
	applymovement OBJ_EVENT_ID_PLAYER, PounamuLeagueToa_Movement_FaceLeader
	waitmovement 0
	msgbox PounamuLeagueToa_Text_Pre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TOA, PounamuLeagueToa_Text_Defeat
	msgbox PounamuLeagueToa_Text_AfterBattle, MSGBOX_DEFAULT
	msgbox PounamuLeagueToa_Text_Onward, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_POUNAMU_LEAGUE_WHETU, 5, 16
	waitstate
	releaseall
	end

PounamuLeagueToa_Movement_FaceLeader:
	face_up
	step_end

PounamuLeagueToa_EventScript_Toa::
	msgbox PounamuLeagueToa_Text_Pre, MSGBOX_NPC
	end

PounamuLeagueToa_Text_Pre:
	.string "Toa: You've come far on tired legs, challenger.\pI am Tinana. The body. The wall you can touch.\pStrength isn't fury - any fool can swing hard. Strength is precision. Discipline. Knowing exactly what you can carry and carrying it without complaint.\pYou've carried a lot. Let's see how you set it down.$"

PounamuLeagueToa_Text_Defeat:
	.string "…$"

PounamuLeagueToa_Text_AfterBattle:
	.string "Toa: …Controlled. Measured. You've learned to fight without wasting a thing. The mountains taught you that, I think.$"

PounamuLeagueToa_Text_Onward:
	.string "Toa: Whetu waits beyond - the mind. She'll read you before you move.\pRest your body a moment first. You've earned the breath.$"
