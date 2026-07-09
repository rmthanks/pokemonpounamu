OpotikiPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OpotikiPokemonCenter1F_OnTransition
	.byte 0

OpotikiPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_OPOTIKI
	end

OpotikiPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OpotikiPokemonCenter1F_EventScript_Nana::
	msgbox OpotikiPokemonCenter1F_Text_Nana, MSGBOX_NPC
	end

OpotikiPokemonCenter1F_Text_Nana:
	.string "Heading west to Tauranga?\p"
	.string "Big smoke, that. They've got\n"
	.string "TWO kinds of milk.$"
