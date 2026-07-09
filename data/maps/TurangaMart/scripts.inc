TurangaMart_MapScripts::
	.byte 0

TurangaMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart TurangaMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TurangaMart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend

TurangaMart_EventScript_Man::
	msgbox TurangaMart_Text_Man, MSGBOX_NPC
	end

TurangaMart_Text_Man:
	.string "Stock up properly before the\n"
	.string "Cape road. I mean it.\p"
	.string "Three hundred kilometres and\n"
	.string "one dairy, mate.$"
