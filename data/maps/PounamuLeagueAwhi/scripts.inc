PounamuLeagueAwhi_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PounamuLeagueAwhi_OnFrame
	.byte 0

PounamuLeagueAwhi_OnFrame:
	map_script_2 VAR_TEMP_1, 0, PounamuLeagueAwhi_EventScript_Encounter
	.2byte 0

PounamuLeagueAwhi_EventScript_Encounter::
	lockall
	setvar VAR_TEMP_1, 1
	applymovement OBJ_EVENT_ID_PLAYER, PounamuLeagueAwhi_Movement_FaceLeader
	waitmovement 0
	msgbox PounamuLeagueAwhi_Text_Pre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_AWHI, PounamuLeagueAwhi_Text_Defeat
	msgbox PounamuLeagueAwhi_Text_AfterBattle, MSGBOX_DEFAULT
	msgbox PounamuLeagueAwhi_Text_Onward, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_POUNAMU_LEAGUE_TOA, 5, 16
	waitstate
	releaseall
	end

PounamuLeagueAwhi_Movement_FaceLeader:
	face_up
	step_end

PounamuLeagueAwhi_EventScript_Awhi::
	goto_if_unset FLAG_UNUSED_0x2A0, PounamuLeagueAwhi_MaybeStone
PounamuLeagueAwhi_AfterStoneCheck::
	msgbox PounamuLeagueAwhi_Text_Pre, MSGBOX_NPC
	end

PounamuLeagueAwhi_Text_Pre:
	.string "Awhi: Kia ora, {PLAYER}. …Yes. I know your name.\pI walked you to kura when the house was loud. I loved your brother before the armour. Nearly whanau twice over - and now, at last, properly.\pI'm the first wall - Whanau. Family. The foundation the other three stand on.\pThe Mob turned this Dark type into a weapon. I turned it back into what it was: a way of holding your own close.\pShow me you've found people to hold. Show me you're not still alone out there.$"

PounamuLeagueAwhi_Text_Defeat:
	.string "…$"

PounamuLeagueAwhi_Text_AfterBattle:
	.string "Awhi: …There. THAT'S whanau. You've gathered a family of your own on the road, haven't you. I can see them in how you fight.$"

PounamuLeagueAwhi_Text_Onward:
	.string "Awhi: Go on. Toa's next - the body. He hits harder than me. They all do, up the line.\p…It's good to finally meet you properly, love. She'd be proud. She IS proud.$"

PounamuLeagueAwhi_MaybeStone::
	goto_if_unset FLAG_UNUSED_0x296, PounamuLeagueAwhi_AfterStoneCheck
	msgbox PounamuLeagueAwhi_Text_StoneKnown, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x2A0
	goto PounamuLeagueAwhi_AfterStoneCheck

PounamuLeagueAwhi_Text_StoneKnown:
	.string "Awhi: That stone at your neck.\p"
	.string "…He has one too, you know.\n"
	.string "Your brother.\p"
	.string "Keeps it in the inside pocket.\n"
	.string "Left side. Over the heart.\p"
	.string "He thinks nobody knows.\p"
	.string "…I loved him. I know where he\n"
	.string "keeps everything he pretends\l"
	.string "he threw away.$"
