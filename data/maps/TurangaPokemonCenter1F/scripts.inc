TurangaPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TurangaPokemonCenter1F_OnTransition
	.byte 0

TurangaPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_TURANGA
	end

TurangaPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TurangaPokemonCenter1F_EventScript_Girl::
	msgbox TurangaPokemonCenter1F_Text_Girl, MSGBOX_NPC
	end

TurangaPokemonCenter1F_Text_Girl:
	.string "Everyone who walks the Cape road\n"
	.string "starts bragging about it forever.\p"
	.string "“Three hundred k of coast, one\n"
	.string "shop.” Yes, Uncle. We know.$"
