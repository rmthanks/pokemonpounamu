OtepotiPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OtepotiPokemonCenter1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OtepotiPokemonCenter1F_OnFrame
	.byte 0

OtepotiPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_OTEPOTI
	call OtepotiPokemonCenter1F_EventScript_CheckQuakePending
	end

@ The awakening. Fires exactly once: the moment the player wakes up
@ after the Hall of Fame. The whole country feels it. It started
@ under Te Mata.
OtepotiPokemonCenter1F_EventScript_CheckQuakePending::
	goto_if_unset FLAG_SYS_GAME_CLEAR, OtepotiPokemonCenter1F_EventScript_NoQuake
	goto_if_set FLAG_UNUSED_0x025, OtepotiPokemonCenter1F_EventScript_NoQuake
	return

OtepotiPokemonCenter1F_EventScript_NoQuake::
	setvar VAR_TEMP_1, 1
	return

OtepotiPokemonCenter1F_OnFrame:
	map_script_2 VAR_TEMP_1, 0, OtepotiPokemonCenter1F_EventScript_Quake
	.2byte 0

OtepotiPokemonCenter1F_EventScript_Quake::
	lockall
	delay 60
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 12 @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_OTEPOTI_NURSE, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 0  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 6  @ shake delay
	special ShakeCamera
	waitstate
	delay 20
	msgbox OtepotiPokemonCenter1F_Text_QuakeNurse, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_UNUSED_0x025
	setvar VAR_TEMP_1, 1
	releaseall
	end

OtepotiPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OtepotiPokemonCenter1F_EventScript_Student::
	msgbox OtepotiPokemonCenter1F_Text_Student, MSGBOX_NPC
	end

OtepotiPokemonCenter1F_Text_QuakeNurse:
	.string "NURSE: Is everyone alright?!\p"
	.string "That wasn't a local shake.\n"
	.string "The albatross colony went up\l"
	.string "all at once - the whole SKY\l"
	.string "just went up.\p"
	.string "…The radio says it was felt\n"
	.string "from the Cape to the Bluff.\l"
	.string "One quake. Same second.\p"
	.string "Centred up north. Hawke's Bay.\n"
	.string "The TE MATA ridge.\p"
	.string "They're saying the hill MOVED.\p"
	.string "They're saying it like it's\n"
	.string "a weather report. Like hills\l"
	.string "just DO that.\p"
	.string "…{PLAYER}. You're from up that\n"
	.string "way, aren't you?$"

OtepotiPokemonCenter1F_Text_Student:
	.string "Eight badges from here. That's the whole country walked.\pWhatever's waiting back home in the Bay… you're ready for it now.$"
