TaupoPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TaupoPokemonCenter1F_OnTransition
	.byte 0

TaupoPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_TAUPO
	end

TaupoPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TaupoPokemonCenter1F_EventScript_Camper::
	msgbox TaupoPokemonCenter1F_Text_Camper, MSGBOX_NPC
	end

TaupoPokemonCenter1F_Text_Camper:
	.string "South of the lake it's all\n"
	.string "waharoa country. Tongariro.\p"
	.string "You don't hike THOSE mountains.\n"
	.string "You're invited, or you're not.$"
