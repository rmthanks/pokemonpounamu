RotoruaPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RotoruaPokemonCenter1F_OnTransition
	.byte 0

RotoruaPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_ROTORUA
	end

RotoruaPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RotoruaPokemonCenter1F_EventScript_Hiker::
	msgbox RotoruaPokemonCenter1F_Text_Hiker, MSGBOX_NPC
	end

RotoruaPokemonCenter1F_Text_Hiker:
	.string "The nurse warms the healing\n"
	.string "machine in the hot pool water.\p"
	.string "Placebo, they reckon.\n"
	.string "My Geodude disagrees.$"
