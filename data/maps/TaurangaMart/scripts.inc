TaurangaMart_MapScripts::
	.byte 0

TaurangaMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart TaurangaMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TaurangaMart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_ESCAPE_ROPE
	pokemartlistend

TaurangaMart_EventScript_Sailor::
	msgbox TaurangaMart_Text_Sailor, MSGBOX_NPC
	end

TaurangaMart_Text_Sailor:
	.string "Super Repel. Trust me.\p"
	.string "The geothermal country past\n"
	.string "Route 36 is crawling with\l"
	.string "things that love the warmth.$"
