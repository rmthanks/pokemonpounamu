OtepotiPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OtepotiPokemonCenter1F_OnTransition
	.byte 0
OtepotiPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_OTEPOTI
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
OtepotiPokemonCenter1F_Text_Student:
	.string "Eight badges from here. That's the whole country walked.\pWhatever's waiting back home in the Bay… you're ready for it now.$"
