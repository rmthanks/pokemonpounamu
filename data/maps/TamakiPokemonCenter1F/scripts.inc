TamakiPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TamakiPokemonCenter1F_OnTransition
	.byte 0

TamakiPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_TAMAKI_MAKAURAU
	end

TamakiPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
