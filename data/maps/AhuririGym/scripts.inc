AhuririGym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AhuririGym_OnTransition
	.byte 0

@ Tama and his two enforcers stay hidden until the usurpation scene.
AhuririGym_OnTransition:
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	end

@ ------------------------------------------------------------------
@ Kauri - Fairy gym leader, Bay Mob president (concealed until now).
@ Badge 2, immediately followed by Tama's ambush and the exile.
@ ------------------------------------------------------------------
AhuririGym_EventScript_Kauri::
	lock
	faceplayer
	goto_if_set FLAG_BADGE02_GET, AhuririGym_EventScript_KauriRetalk
	goto_if_unset FLAG_BADGE01_GET, AhuririGym_EventScript_KauriNoBadge
	msgbox AhuririGym_Text_KauriPreBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_KAURI, AhuririGym_Text_KauriDefeat
	msgbox AhuririGym_Text_KauriBadgeSpeech, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message AhuririGym_Text_ReceivedReefBadge
	waitfanfare
	waitmessage
	setflag FLAG_BADGE02_GET
	msgbox AhuririGym_Text_KauriConfession, MSGBOX_DEFAULT
	@ --- the doors bang open ---
	playse SE_SLIDING_DOOR
	clearflag FLAG_TEMP_11
	clearflag FLAG_TEMP_12
	clearflag FLAG_TEMP_13
	addobject LOCALID_AHURIRI_GYM_TAMA
	addobject LOCALID_AHURIRI_GYM_GRUNT_A
	addobject LOCALID_AHURIRI_GYM_GRUNT_B
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_AHURIRI_GYM_TAMA, AhuririGym_Movement_TamaEnter
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, AhuririGym_Movement_FaceDown
	applymovement LOCALID_AHURIRI_GYM_KAURI, AhuririGym_Movement_FaceDown
	waitmovement 0
	msgbox AhuririGym_Text_TamaFinishTheSentence, MSGBOX_DEFAULT
	msgbox AhuririGym_Text_KauriNotLikeThis, MSGBOX_DEFAULT
	msgbox AhuririGym_Text_TamaTheVote, MSGBOX_DEFAULT
	msgbox AhuririGym_Text_KauriYouDidnt, MSGBOX_DEFAULT
	msgbox AhuririGym_Text_TamaYouWentSoft, MSGBOX_DEFAULT
	msgbox AhuririGym_Text_TamaAndYou, MSGBOX_DEFAULT
	@ --- the ambush battle: no whiteout, story continues either way ---
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_TAMA_AMBUSH, AhuririGym_Text_TamaDefeat
	clearflag B_FLAG_NO_WHITEOUT
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_WON, AhuririGym_EventScript_TamaBeaten
	call_if_ne VAR_RESULT, B_OUTCOME_WON, AhuririGym_EventScript_TamaWon
	msgbox AhuririGym_Text_KauriLeaveThemOut, MSGBOX_DEFAULT
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, AhuririGym_EventScript_ExileM
	msgbox AhuririGym_Text_TamaTakeSisterNorth, MSGBOX_DEFAULT
	goto AhuririGym_EventScript_ExileCommon
AhuririGym_EventScript_ExileM::
	msgbox AhuririGym_Text_TamaTakeBrotherNorth, MSGBOX_DEFAULT
AhuririGym_EventScript_ExileCommon::
	fadescreen FADE_TO_BLACK
	special HealPlayerParty
	msgbox AhuririGym_Text_ExileNarration, MSGBOX_DEFAULT
	setvar VAR_POUNAMU_INTRO_STATE, 3
	warp MAP_ROUTE2_BAY, 7, 6
	waitstate
	release
	end

AhuririGym_EventScript_TamaBeaten::
	msgbox AhuririGym_Text_TamaBeatenReaction, MSGBOX_DEFAULT
	return

AhuririGym_EventScript_TamaWon::
	msgbox AhuririGym_Text_TamaWonReaction, MSGBOX_DEFAULT
	return

AhuririGym_EventScript_KauriNoBadge::
	msgbox AhuririGym_Text_KauriNoBadge, MSGBOX_DEFAULT
	release
	end

AhuririGym_EventScript_KauriRetalk::
	msgbox AhuririGym_Text_KauriRetalk, MSGBOX_DEFAULT
	release
	end

@ ------------------------------------------------------------------
@ Gym trainer - Nikau, a Kauri devotee.
@ ------------------------------------------------------------------
AhuririGym_EventScript_Prospect::
	trainerbattle_single TRAINER_AHURIRI_PROSPECT, AhuririGym_Text_ProspectIntro, AhuririGym_Text_ProspectDefeat
	msgbox AhuririGym_Text_ProspectPost, MSGBOX_AUTOCLOSE
	end

@ ------------------------- movement -------------------------
AhuririGym_Movement_TamaEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end

AhuririGym_Movement_FaceDown:
	face_down
	step_end

@ ------------------------- text -------------------------
AhuririGym_Text_KauriNoBadge:
	.string "Kauri: …Ha. Look at you, standing\n"
	.string "in my gym like you own the tide.\p"
	.string "Can't give you this fight yet, kid.\n"
	.string "House rule. Mine, actually.\p"
	.string "Your mother's badge first.\n"
	.string "Earn the Orchard Badge, then walk\l"
	.string "back through that door.$"

AhuririGym_Text_KauriPreBattle:
	.string "Kauri: So. You came.\p"
	.string "I built this gym the way I built\n"
	.string "everything in this town…\l"
	.string "to be looked at.\p"
	.string "Fairy-type, they call it.\n"
	.string "Harmless, they reckon.\p"
	.string "Soft things, eh?\n"
	.string "…Soft things hide the teeth.$"

AhuririGym_Text_KauriDefeat:
	.string "…There it is.\p"
	.string "There's the thing your\n"
	.string "mother saw.$"

AhuririGym_Text_KauriBadgeSpeech:
	.string "Kauri: You fought like the Bay,\n"
	.string "kid. Sunny right up until the\l"
	.string "reef takes the boat.\p"
	.string "I'm proud of you.\n"
	.string "…I don't say that enough.$"

AhuririGym_Text_ReceivedReefBadge:
	.string "{PLAYER} received the Reef Badge\n"
	.string "from Kauri!$"

AhuririGym_Text_KauriConfession:
	.string "Kauri: The Reef Badge.\n"
	.string "Second of eight.\p"
	.string "…Listen, {PLAYER}.\p"
	.string "There's something I should have\n"
	.string "told you a long time ago.\p"
	.string "About this town. About my work.\n"
	.string "About why I couldn't stay.\p"
	.string "The truth is, I'm the president\n"
	.string "of the-$"

AhuririGym_Text_TamaFinishTheSentence:
	.string "Tama: The president of\n"
	.string "the Bay Mob.\p"
	.string "Go on, Dad. Finish the sentence.\p"
	.string "You've had ten years\n"
	.string "to finish it.$"

AhuririGym_Text_KauriNotLikeThis:
	.string "Kauri: Tama.\p"
	.string "Not here. Not like this.$"

AhuririGym_Text_TamaTheVote:
	.string "Tama: The chapter took a vote\n"
	.string "this morning.\p"
	.string "Uncles, captains, the lot.\p"
	.string "…It wasn't close.$"

AhuririGym_Text_KauriYouDidnt:
	.string "Kauri: …You didn't.$"

AhuririGym_Text_TamaYouWentSoft:
	.string "Tama: You went soft the day you\n"
	.string "started keeping two families,\l"
	.string "old man.\p"
	.string "The Bay noticed.\n"
	.string "Even if Mum didn't.\p"
	.string "Consider yourself retired.$"

AhuririGym_Text_TamaAndYou:
	.string "Tama: And you.\p"
	.string "Every road, every gate, every\n"
	.string "boat in this Bay answers to\l"
	.string "me now.\p"
	.string "You wanted your birthday present's\n"
	.string "first real fight?\p"
	.string "Here.$"

AhuririGym_Text_TamaDefeat:
	.string "…Tch.$"

AhuririGym_Text_TamaBeatenReaction:
	.string "Tama: …Heh.\p"
	.string "Better than I was at your age.\p"
	.string "Doesn't matter.\n"
	.string "One good fight doesn't move\l"
	.string "a vote.$"

AhuririGym_Text_TamaWonReaction:
	.string "Tama: That's what I thought.\p"
	.string "Presents don't make a trainer.$"

AhuririGym_Text_KauriLeaveThemOut:
	.string "Kauri: TAMA! Leave the kid out\n"
	.string "of this!\p"
	.string "This is between you and-$"

AhuririGym_Text_TamaTakeBrotherNorth:
	.string "Tama: It's whanau business, Dad.\n"
	.string "He's IN it.\p"
	.string "…Take my little brother to the\n"
	.string "north checkpoint.\p"
	.string "The Bay is closed to favourites.$"

AhuririGym_Text_TamaTakeSisterNorth:
	.string "Tama: It's whanau business, Dad.\n"
	.string "She's IN it.\p"
	.string "…Take my little sister to the\n"
	.string "north checkpoint.\p"
	.string "The Bay is closed to favourites.$"

AhuririGym_Text_ExileNarration:
	.string "Rough hands. A truck bed.\p"
	.string "The smell of salt, and cut grass,\n"
	.string "and someone else's cigarettes.\p"
	.string "Heretaunga rolls past the\n"
	.string "tail-gate… going the wrong way.$"

AhuririGym_Text_KauriRetalk:
	.string "Kauri: …Go, {PLAYER}.\n"
	.string "Please.$"

AhuririGym_Text_ProspectIntro:
	.string "One day I'm going to run this\n"
	.string "gym. Kauri said if I can beat\l"
	.string "one proper trainer, I'm in!$"

AhuririGym_Text_ProspectDefeat:
	.string "Aw, Snubbull! We were so close\n"
	.string "to being legends!$"

AhuririGym_Text_ProspectPost:
	.string "You're not from Ahuriri, eh?\p"
	.string "…Wait. Those eyes.\n"
	.string "You're not… related to the boss,\l"
	.string "are you?$"
