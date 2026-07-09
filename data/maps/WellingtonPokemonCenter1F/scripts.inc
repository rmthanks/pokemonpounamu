WellingtonPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WellingtonPokemonCenter1F_OnTransition
	.byte 0
WellingtonPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_WELLINGTON
	end
WellingtonPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
WellingtonPokemonCenter1F_EventScript_Gent::
	msgbox WellingtonPokemonCenter1F_Text_Gent, MSGBOX_NPC
	end
WellingtonPokemonCenter1F_Text_Gent:
	.string "End of the line for now, my\n"
	.string "friend. The strait is closed.\p"
	.string "When it opens - and it will -\n"
	.string "the whole South Island's yours.$"
