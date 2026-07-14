TaupoLakeIsle_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TaupoLakeIsle_OnResume
	.byte 0

TaupoLakeIsle_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, TaupoLakeIsle_EventScript_TryRemove
	end

TaupoLakeIsle_EventScript_TryRemove::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

@ The Choice, taken: you came back for the one you love.
TaupoLakeIsle_EventScript_Lugia::
	lock
	faceplayer
	msgbox TaupoLakeIsle_Text_Trial, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_LUGIA, 45
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TaupoLakeIsle_EventScript_Chosen
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TaupoLakeIsle_EventScript_Chosen
	release
	end

TaupoLakeIsle_EventScript_Chosen::
	setflag FLAG_UNUSED_0x905
	setflag FLAG_UNUSED_0x903
	msgbox TaupoLakeIsle_Text_Intercut, MSGBOX_DEFAULT
	release
	end

TaupoLakeIsle_Text_Trial:
	.string "The mist parts on the lake and\n"
	.string "the great diver is there -\l"
	.string "the one who has shadowed every\l"
	.string "threshold of your journey.\p"
	.string "It does not ask why you came.\p"
	.string "It asks it the only way it\n"
	.string "knows how.$"

TaupoLakeIsle_Text_Intercut:
	.string "The lake goes still.\p"
	.string "…And somewhere far south, over\n"
	.string "black water, a bird of fire\l"
	.string "rises into a net of shadows -\p"
	.string "and does not rise again.\p"
	.string "Your brother has what you\n"
	.string "did not protect.$"
