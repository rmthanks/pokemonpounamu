WhakatuPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WhakatuPokemonCenter1F_OnTransition
	.byte 0
WhakatuPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_WHAKATU
	end
WhakatuPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
WhakatuPokemonCenter1F_EventScript_Camper::
	msgbox WhakatuPokemonCenter1F_Text_Camper, MSGBOX_NPC
	end
WhakatuPokemonCenter1F_Text_Camper:
	.string "East out of town is the Lewis Pass - Route 7. Longest road on the island. Pack a lunch. Pack two.$"
