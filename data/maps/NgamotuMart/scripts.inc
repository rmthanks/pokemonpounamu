NgamotuMart_MapScripts::
	.byte 0
NgamotuMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart NgamotuMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
	.align 2
NgamotuMart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend
NgamotuMart_EventScript_Man::
	msgbox NgamotuMart_Text_Man, MSGBOX_NPC
	end
NgamotuMart_Text_Man:
	.string "Revives in stock. The Kapiti\n"
	.string "road south is no joke now.\p"
	.string "Trainers down there hit like\n"
	.string "the southerly.$"
