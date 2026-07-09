HeretaungaMart_MapScripts::
	.byte 0

HeretaungaMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart HeretaungaMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
HeretaungaMart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	pokemartlistend

HeretaungaMart_EventScript_Woman::
	msgbox HeretaungaMart_Text_Woman, MSGBOX_NPC
	end

HeretaungaMart_Text_Woman:
	.string "Poké Balls are back in stock!\p"
	.string "The orchard's crawling with\n"
	.string "Combee this time of year.$"
