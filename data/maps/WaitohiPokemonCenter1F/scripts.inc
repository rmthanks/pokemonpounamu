WaitohiPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WaitohiPokemonCenter1F_OnTransition
	.byte 0
WaitohiPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_WAITOHI
	end
WaitohiPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
WaitohiPokemonCenter1F_EventScript_Sailor::
	msgbox WaitohiPokemonCenter1F_Text_Sailor, MSGBOX_NPC
	end
WaitohiPokemonCenter1F_Text_Sailor:
	.string "South road runs down the sounds to Whakatu. Sunniest city in the country - you'll want it after that boat.$"
