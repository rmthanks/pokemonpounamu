WairoaPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WairoaPokemonCenter1F_OnTransition
	.byte 0

WairoaPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_WAIROA
	end

WairoaPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

WairoaPokemonCenter1F_EventScript_Fisherman::
	msgbox WairoaPokemonCenter1F_Text_Fisherman, MSGBOX_NPC
	end

WairoaPokemonCenter1F_Text_Fisherman:
	.string "The coast road to Turanga is a\n"
	.string "solid two days' walk.\p"
	.string "Sleep here. The grass past the\n"
	.string "hedgerows gets lively at night.$"
