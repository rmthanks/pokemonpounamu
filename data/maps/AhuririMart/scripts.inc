AhuririMart_MapScripts::
	.byte 0

AhuririMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart AhuririMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
AhuririMart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REPEL
	pokemartlistend

AhuririMart_EventScript_Woman::
	msgbox AhuririMart_Text_Woman, MSGBOX_NPC
	end

AhuririMart_Text_Woman:
	.string "Repels sell out every time the\n"
	.string "Mob runs a shipment through.\p"
	.string "Folk suddenly remember errands\n"
	.string "somewhere else.$"
