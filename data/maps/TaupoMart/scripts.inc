TaupoMart_MapScripts::
	.byte 0

TaupoMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart TaupoMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TaupoMart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend

TaupoMart_EventScript_Man::
	msgbox TaupoMart_Text_Man, MSGBOX_NPC
	end

TaupoMart_Text_Man:
	.string "We stock for trampers, anglers,\n"
	.string "and people staring at the east\l"
	.string "road looking gutted.\p"
	.string "…Aisle three, mate.$"
