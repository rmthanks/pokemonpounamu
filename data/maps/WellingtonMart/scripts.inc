WellingtonMart_MapScripts::
	.byte 0
WellingtonMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart WellingtonMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
	.align 2
WellingtonMart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend
WellingtonMart_EventScript_Gent::
	msgbox WellingtonMart_Text_Gent, MSGBOX_NPC
	end
WellingtonMart_Text_Gent:
	.string "Ultra Balls, this far south?\p"
	.string "The capital gets the good stock\n"
	.string "first. Perks of the Beehive.$"
