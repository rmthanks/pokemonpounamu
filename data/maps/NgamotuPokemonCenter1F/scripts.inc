NgamotuPokemonCenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NgamotuPokemonCenter1F_OnTransition
	.byte 0
NgamotuPokemonCenter1F_OnTransition:
	setrespawn HEAL_LOCATION_NGAMOTU
	end
NgamotuPokemonCenter1F_EventScript_Nurse::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
NgamotuPokemonCenter1F_EventScript_Beauty::
	msgbox NgamotuPokemonCenter1F_Text_Beauty, MSGBOX_NPC
	end
NgamotuPokemonCenter1F_Text_Beauty:
	.string "South of here it's Route 3 all\n"
	.string "the way to the river at\l"
	.string "Whanganui.\p"
	.string "Rest up. The wind doesn't.$"
