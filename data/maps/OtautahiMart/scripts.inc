OtautahiMart_MapScripts::
	.byte 0
OtautahiMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart OtautahiMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
	.align 2
OtautahiMart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend
OtautahiMart_EventScript_Woman::
	msgbox OtautahiMart_Text_Woman, MSGBOX_NPC
	end
OtautahiMart_Text_Woman:
	.string "Full Heals and Revives, stocked deep. Huka's Ice gym down south doesn't take prisoners.$"
