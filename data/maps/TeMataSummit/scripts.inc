TeMataSummit_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TeMataSummit_OnResume
	.byte 0

TeMataSummit_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, TeMataSummit_EventScript_TryRemoveRongokako
	end

TeMataSummit_EventScript_TryRemoveRongokako::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

@ ------------------------------------------------------------------
@ RONGOKAKO. The giant the whole game has been standing on.
@ The ridge above Heretaunga was never a hill. It was a rangatira,
@ lying down, sleeping off a long walk. The quake was him waking.
@ ------------------------------------------------------------------
TeMataSummit_EventScript_Rongokako::
	lock
	faceplayer
	msgbox TeMataSummit_Text_ItIsNotStone, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_REGIGIGAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox TeMataSummit_Text_RongokakoAwake, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_REGIGIGAS, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TeMataSummit_EventScript_DefeatedRongokako
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, TeMataSummit_EventScript_RanFromRongokako
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, TeMataSummit_EventScript_RanFromRongokako
	setflag FLAG_UNUSED_0x026
	release
	end

TeMataSummit_EventScript_DefeatedRongokako::
	setflag FLAG_UNUSED_0x026
	goto Common_EventScript_RemoveStaticPokemon
	end

TeMataSummit_EventScript_RanFromRongokako::
	setvar VAR_0x8004, SPECIES_REGIGIGAS
	goto Common_EventScript_LegendaryFlewAway
	end

@ The split pou at the crown. Readable once Rongokako has moved on.
TeMataSummit_EventScript_Pou::
	msgbox TeMataSummit_Text_Pou, MSGBOX_SIGN
	end

@ ------------------------- text -------------------------
TeMataSummit_Text_ItIsNotStone:
	.string "It is not stone.\p"
	.string "It was never stone.\p"
	.string "The shape the ridge has been\n"
	.string "sleeping in all your life is\l"
	.string "standing at the crown of the\l"
	.string "hill.\p"
	.string "Below it, the whole Bay has\n"
	.string "gone quiet.$"

TeMataSummit_Text_RongokakoAwake:
	.string "RONGOKAKO is awake!$"

TeMataSummit_Text_Pou:
	.string "The pou stands split in two,\n"
	.string "cleanly, like a door.\p"
	.string "The old carving is still\n"
	.string "legible on both halves:\p"
	.string "“TE MATA O RONGOKAKO.\n"
	.string "He is not gone. He is lying\l"
	.string "down. Walk softly on the\l"
	.string "rangatira's back.”$"
