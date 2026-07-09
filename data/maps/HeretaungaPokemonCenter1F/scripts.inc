HeretaungaPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HeretaungaPokemonCenter1F_OnTransition
	.byte 0

HeretaungaPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	end

HeretaungaPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

HeretaungaPokemonCenter1F_EventScript_Girl::
	msgbox HeretaungaPokemonCenter1F_Text_Girl, MSGBOX_NPC
	end

HeretaungaPokemonCenter1F_Text_Girl:
	.string "It's a long walk north to Ahuriri.\p"
	.string "Rest that team of yours before\n"
	.string "you set out, eh?$"
