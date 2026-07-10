Piopiotahi_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Piopiotahi_OnResume
	.byte 0

Piopiotahi_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Piopiotahi_EventScript_TryRemove
	end

Piopiotahi_EventScript_TryRemove::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

@ The Choice, taken: you left the one you love for the one you'd never met.
Piopiotahi_EventScript_HoOh::
	lock
	faceplayer
	msgbox Piopiotahi_Text_Trial, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_HO_OH, 55
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Piopiotahi_EventScript_Chosen
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Piopiotahi_EventScript_Chosen
	release
	end

Piopiotahi_EventScript_Chosen::
	setflag FLAG_UNUSED_0x906
	setflag FLAG_UNUSED_0x903
	msgbox Piopiotahi_Text_Intercut, MSGBOX_DEFAULT
	release
	end

Piopiotahi_Text_Trial:
	.string "At the head of the sound, above\n"
	.string "the falls, it burns without\l"
	.string "burning anything.\p"
	.string "You have never met. It has\n"
	.string "never shadowed your road.\p"
	.string "You left everything you love\n"
	.string "unguarded to stand here.\p"
	.string "It finds that… interesting.$"

Piopiotahi_Text_Intercut:
	.string "The fire settles on your\n"
	.string "shoulder like a setting sun.\p"
	.string "…And far to the north, a lake\n"
	.string "erupts - a silver wing beats\l"
	.string "once against a net of shadows -\p"
	.string "and the lake goes dark.\p"
	.string "Your brother has what you\n"
	.string "did not protect.$"
