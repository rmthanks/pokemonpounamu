RotoruaMart_MapScripts::
	.byte 0

RotoruaMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart RotoruaMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
RotoruaMart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend

RotoruaMart_EventScript_Woman::
	msgbox RotoruaMart_Text_Woman, MSGBOX_NPC
	end

RotoruaMart_Text_Woman:
	.string "Burn Heals are half price.\p"
	.string "Tourist season, dear. Somebody\n"
	.string "always pats the Slugma.$"
