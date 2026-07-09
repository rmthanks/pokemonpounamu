TaurangaPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TaurangaPokemonCenter1F_OnTransition
	.byte 0

TaurangaPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_TAURANGA
	end

TaurangaPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TaurangaPokemonCenter1F_EventScript_Tuber::
	msgbox TaurangaPokemonCenter1F_Text_Tuber, MSGBOX_NPC
	end

TaurangaPokemonCenter1F_Text_Tuber:
	.string "The Rotorua road smells like\n"
	.string "eggs the whole last hour.\p"
	.string "You get used to it!\n"
	.string "…You don't, actually.$"
