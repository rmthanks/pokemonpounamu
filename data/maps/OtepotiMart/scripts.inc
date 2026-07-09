OtepotiMart_MapScripts::
	.byte 0
OtepotiMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart OtepotiMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
	.align 2
OtepotiMart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend
OtepotiMart_EventScript_Man::
	msgbox OtepotiMart_Text_Man, MSGBOX_NPC
	end
OtepotiMart_Text_Man:
	.string "Last mart in the country, near enough. Stock up like it. Huka gives no quarter.$"
