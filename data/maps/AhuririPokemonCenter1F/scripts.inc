AhuririPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AhuririPokemonCenter1F_OnTransition
	.byte 0

AhuririPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_AHURIRI_CITY
	end

AhuririPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

AhuririPokemonCenter1F_EventScript_Sailor::
	msgbox AhuririPokemonCenter1F_Text_Sailor, MSGBOX_NPC
	end

AhuririPokemonCenter1F_Text_Sailor:
	.string "Half the boats in the marina\n"
	.string "answer to the Mob these days.\p"
	.string "The other half answer faster.$"
