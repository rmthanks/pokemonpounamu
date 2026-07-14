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
