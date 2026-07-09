PounamuLeagueMaui_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PounamuLeagueMaui_OnFrame
	.byte 0

PounamuLeagueMaui_OnFrame:
	map_script_2 VAR_TEMP_1, 0, PounamuLeagueMaui_EventScript_Encounter
	.2byte 0

PounamuLeagueMaui_EventScript_Encounter::
	lockall
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_SYS_GAME_CLEAR, LeagueMaui_EventScript_Rematch
	applymovement OBJ_EVENT_ID_PLAYER, PounamuLeagueMaui_Movement_FaceLeader
	waitmovement 0
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox LeagueMaui_Text_Reveal, MSGBOX_DEFAULT
	msgbox LeagueMaui_Text_Reveal2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAUI, LeagueMaui_Text_Defeat
	msgbox LeagueMaui_Text_PostBattle, MSGBOX_DEFAULT
	msgbox LeagueMaui_Text_Coronation, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD
	delay 20
	setrespawn HEAL_LOCATION_OTEPOTI
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	releaseall
	end

LeagueMaui_EventScript_Rematch::
	applymovement OBJ_EVENT_ID_PLAYER, PounamuLeagueMaui_Movement_FaceLeader
	waitmovement 0
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox LeagueMaui_Text_RematchIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAUI, LeagueMaui_Text_Defeat
	msgbox LeagueMaui_Text_RematchAfter, MSGBOX_DEFAULT
	releaseall
	end

PounamuLeagueMaui_Movement_FaceLeader:
	face_up
	step_end

LeagueMaui_EventScript_Maui::
	msgbox LeagueMaui_Text_RematchIntro, MSGBOX_NPC
	end

LeagueMaui_Text_Reveal:
	.string "Maui: Haere mai, e hoa.\p"
	.string "…You remember that greeting,\n"
	.string "don't you.\p"
	.string "A void. A slow old sun-Pokemon.\n"
	.string "A voice that kept you waiting,\l"
	.string "but was patient.\p"
	.string "I told you we would meet again.$"

LeagueMaui_Text_Reveal2:
	.string "Maui: I am Maui. I slowed the sun.\n"
	.string "I fished up this land. And yes -\l"
	.string "I have watched you the whole way.\p"
	.string "Your mother's orchard. Your\n"
	.string "father's reef. Your brother's\l"
	.string "long, sad anger.\p"
	.string "And you - the one they sent away.\n"
	.string "The one who came back the long\l"
	.string "way, badge by badge, and grew\l"
	.string "into something none of them\l"
	.string "expected.\p"
	.string "I hold the roof of this whare.\n"
	.string "Come and see if you can lift it.$"

LeagueMaui_Text_Defeat:
	.string "…Ah.\p"
	.string "There it is.$"

LeagueMaui_Text_PostBattle:
	.string "Maui: I once snared the sun\n"
	.string "itself, and it still fought me\l"
	.string "for an hour every spring.\p"
	.string "You? You didn't fight me at all,\n"
	.string "in the end.\p"
	.string "You just… rose. The way the sun\n"
	.string "does. Whether anyone allows it\l"
	.string "or not.$"

LeagueMaui_Text_Coronation:
	.string "Maui: The child who was told they\n"
	.string "didn't belong is now the one this\l"
	.string "whole land answers to.\p"
	.string "That's not revenge, {PLAYER}.\n"
	.string "It's something bigger. It's\l"
	.string "coming home to yourself.\p"
	.string "Champion of Aotearoa.\p"
	.string "…Now. About your brother.\n"
	.string "And a certain tower.\p"
	.string "But that - that is a story for\n"
	.string "when you're ready.\p"
	.string "Rest first, e hoa. You've earned\n"
	.string "the light."

LeagueMaui_Text_RematchIntro:
	.string "Maui: Back for the sun, Champion?\p"
	.string "Come on then. Show me you still\n"
	.string "burn.$"

LeagueMaui_Text_RematchAfter:
	.string "Maui: Ha! Still rising.\p"
	.string "The tower will keep. Your\n"
	.string "brother isn't going anywhere he\l"
	.string "can't be followed.$"
