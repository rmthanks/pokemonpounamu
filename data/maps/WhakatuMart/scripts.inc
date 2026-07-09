WhakatuMart_MapScripts::
	.byte 0
WhakatuMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart WhakatuMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
	.align 2
WhakatuMart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend
WhakatuMart_EventScript_Man::
	msgbox WhakatuMart_Text_Man, MSGBOX_NPC
	end
WhakatuMart_Text_Man:
	.string "Heading over the pass? Take Revives. The trainers up there fight like the weather - suddenly.$"
