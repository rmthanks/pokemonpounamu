WhanganuiPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WhanganuiPokemonCenter1F_OnTransition
	.byte 0
WhanganuiPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_WHANGANUI
	end
WhanganuiPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
WhanganuiPokemonCenter1F_EventScript_Fisherman::
	msgbox WhanganuiPokemonCenter1F_Text_Fisherman, MSGBOX_NPC
	end
WhanganuiPokemonCenter1F_Text_Fisherman:
	.string "South road hugs the Kapiti coast\n"
	.string "all the way to the capital.\p"
	.string "Big city. Big wind. Big gym.$"
