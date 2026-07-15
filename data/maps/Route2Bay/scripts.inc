Route2Bay_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route2Bay_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route2Bay_OnFrame
	.byte 0

@ Tama only stands at the checkpoint during the exile scene.
Route2Bay_OnTransition:
	goto_if_eq VAR_POUNAMU_INTRO_STATE, 4, Route2Bay_OnTransition_End
	setflag FLAG_TEMP_14
Route2Bay_OnTransition_End:
	end

Route2Bay_OnFrame:
	map_script_2 VAR_POUNAMU_INTRO_STATE, 4, Route2Bay_EventScript_Exile
	.2byte 0

@ ------------------------------------------------------------------
@ The exile. Player has just been dumped north of the Mob checkpoint.
@ ------------------------------------------------------------------
Route2Bay_EventScript_Exile::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Route2Bay_Movement_FaceDown
	applymovement LOCALID_R2_GRUNT1, Route2Bay_Movement_FaceUp
	applymovement LOCALID_R2_GRUNT2, Route2Bay_Movement_FaceUp
	waitmovement 0
	msgbox Route2Bay_Text_TamaExile1, MSGBOX_DEFAULT
	msgbox Route2Bay_Text_TamaExile2, MSGBOX_DEFAULT
	msgbox Route2Bay_Text_TamaExile3, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_R2_TAMA
	fadescreen FADE_FROM_BLACK
	msgbox Route2Bay_Text_ExileClose, MSGBOX_DEFAULT
	delay 40
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox Route2Bay_Text_LugiaSurfaces, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_POUNAMU_INTRO_STATE, 5
	releaseall
	end

@ ------------------------------------------------------------------
@ Checkpoint grunts. Before the exile they seal the road north;
@ after it they seal the road home.
@ ------------------------------------------------------------------
Route2Bay_EventScript_Grunt1::
	lock
	faceplayer
	goto_if_eq VAR_POUNAMU_INTRO_STATE, 5, Route2Bay_EventScript_Grunt1After
	msgbox Route2Bay_Text_Grunt1Before, MSGBOX_DEFAULT
	release
	end
Route2Bay_EventScript_Grunt1After::
	msgbox Route2Bay_Text_Grunt1After, MSGBOX_DEFAULT
	release
	end

Route2Bay_EventScript_Grunt2::
	lock
	faceplayer
	goto_if_eq VAR_POUNAMU_INTRO_STATE, 5, Route2Bay_EventScript_Grunt2After
	msgbox Route2Bay_Text_Grunt2Before, MSGBOX_DEFAULT
	release
	end
Route2Bay_EventScript_Grunt2After::
	msgbox Route2Bay_Text_Grunt2After, MSGBOX_DEFAULT
	release
	end

Route2Bay_EventScript_TamaIdle::
	msgbox Route2Bay_Text_TamaExile3, MSGBOX_NPC
	end

@ ------------------------- movement -------------------------
Route2Bay_Movement_FaceDown:
	face_down
	step_end

Route2Bay_Movement_FaceUp:
	face_up
	step_end

@ ------------------------- text -------------------------
Route2Bay_Text_TamaExile1:
	.string "Tama: Hawke's Bay looks after\n"
	.string "its own now. Properly.\p"
	.string "No more of Dad's soft\n"
	.string "handshakes.$"

Route2Bay_Text_TamaExile2:
	.string "Tama: You want to be somebody?\n"
	.string "Go be somebody out there.\p"
	.string "Every legend in this family\n"
	.string "leaves first.\p"
	.string "…Ask Mum.$"

Route2Bay_Text_TamaExile3:
	.string "Tama: Don't come back until\n"
	.string "it means something.$"

Route2Bay_Text_ExileClose:
	.string "The checkpoint closes.\p"
	.string "Somewhere south, the orchard rows\n"
	.string "are turning over without you.\p"
	.string "ACT 1: HAWKE'S BAY - complete.\p"
	.string "(The road north to Wairoa and\n"
	.string "beyond arrives in the next build.\l"
	.string "Thanks for playing the draft!)$"

Route2Bay_Text_Grunt1Before:
	.string "Checkpoint. Mob business up\n"
	.string "the line.\p"
	.string "Nothing north for you, kid.\n"
	.string "Turn around.$"

Route2Bay_Text_Grunt2Before:
	.string "You deaf?\p"
	.string "Road's closed.\n"
	.string "Boss's orders.$"

Route2Bay_Text_Grunt1After:
	.string "Boss's orders.\p"
	.string "The Bay doesn't know you\n"
	.string "any more.$"

Route2Bay_Text_Grunt2After:
	.string "Nothing personal, kid.\p"
	.string "…Alright. It's a little bit\n"
	.string "personal.$"

Route2Bay_Text_LugiaSurfaces:
	.string "…Out on the grey water of the\n"
	.string "bay, something vast breaks the\l"
	.string "surface.\p"
	.string "Silver. Older than the road.\n"
	.string "Older than the Bay's name.\p"
	.string "It looks at you - LOOKS at\n"
	.string "you -\p"
	.string "and slides back under, going\n"
	.string "north, the way you must.$"

Route2Bay_EventScript_PMarama::
	trainerbattle_single TRAINER_R2B_MARAMA, Route2Bay_Text_PMaramaIntro, Route2Bay_Text_PMaramaDefeat
	msgbox Route2Bay_Text_PMaramaPost, MSGBOX_AUTOCLOSE
	end

Route2Bay_Text_PMaramaIntro:
	.string "Marama: I've been training out here\nALL morning!$"

Route2Bay_Text_PMaramaDefeat:
	.string "Okay, MOST of the morning.$"

Route2Bay_Text_PMaramaPost:
	.string "Don't tell my nan I lost.$"

Route2Bay_EventScript_PMoana::
	trainerbattle_single TRAINER_R2B_MOANA, Route2Bay_Text_PMoanaIntro, Route2Bay_Text_PMoanaDefeat
	msgbox Route2Bay_Text_PMoanaPost, MSGBOX_AUTOCLOSE
	end

Route2Bay_Text_PMoanaIntro:
	.string "Moana: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route2Bay_Text_PMoanaDefeat:
	.string "You can have the sammie.$"

Route2Bay_Text_PMoanaPost:
	.string "Worth it. Rematch at smoko?$"

Route2Bay_EventScript_PKahu::
	trainerbattle_single TRAINER_R2B_KAHU, Route2Bay_Text_PKahuIntro, Route2Bay_Text_PKahuDefeat
	msgbox Route2Bay_Text_PKahuPost, MSGBOX_AUTOCLOSE
	end

Route2Bay_Text_PKahuIntro:
	.string "Kahu: The one that got away was\nTHIS big. Like my Pokemon.$"

Route2Bay_Text_PKahuDefeat:
	.string "Also got away on me.$"

Route2Bay_Text_PKahuPost:
	.string "Tide's turning. Good luck out\nthere.$"

Route2Bay_EventScript_PRewi::
	trainerbattle_single TRAINER_R2B_REWI, Route2Bay_Text_PRewiIntro, Route2Bay_Text_PRewiDefeat
	msgbox Route2Bay_Text_PRewiPost, MSGBOX_AUTOCLOSE
	end

Route2Bay_Text_PRewiIntro:
	.string "Rewi: I've tramped every track in\nthis region. Fight me.$"

Route2Bay_Text_PRewiDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route2Bay_Text_PRewiPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route2Bay_EventScript_PHana::
	trainerbattle_single TRAINER_R2B_HANA, Route2Bay_Text_PHanaIntro, Route2Bay_Text_PHanaDefeat
	msgbox Route2Bay_Text_PHanaPost, MSGBOX_AUTOCLOSE
	end

Route2Bay_Text_PHanaIntro:
	.string "Hana: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route2Bay_Text_PHanaDefeat:
	.string "You can have the sammie.$"

Route2Bay_Text_PHanaPost:
	.string "Worth it. Rematch at smoko?$"

Route2Bay_EventScript_PPiri::
	trainerbattle_single TRAINER_R2B_PIRI, Route2Bay_Text_PPiriIntro, Route2Bay_Text_PPiriDefeat
	msgbox Route2Bay_Text_PPiriPost, MSGBOX_AUTOCLOSE
	end

Route2Bay_Text_PPiriIntro:
	.string "Piri: Oi! You walked into my line\nof sight. Them's the rules!$"

Route2Bay_Text_PPiriDefeat:
	.string "Aw, heck!$"

Route2Bay_Text_PPiriPost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"
