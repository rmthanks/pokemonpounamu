OtautahiPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OtautahiPokemonCenter1F_OnTransition
	.byte 0
OtautahiPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_OTAUTAHI
	end
OtautahiPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
OtautahiPokemonCenter1F_EventScript_Gent::
	msgbox OtautahiPokemonCenter1F_Text_Gent, MSGBOX_NPC
	end
OtautahiPokemonCenter1F_Text_Gent:
	.string "South road's the last leg - Route 1 down to Otepoti. Gets cold. Gets beautiful. Gets cold.$"
