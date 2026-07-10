HeretaungaFlowerShop_MapScripts::
	.byte 0

@ ------------------------------------------------------------------
@ The old Bay Mob headquarters. Dad ran the whole operation from this
@ floor once. Now Mum sells cuttings, seedlings and nature mints from
@ behind the same counter. She kept the building. She changed what it
@ was for.
@ ------------------------------------------------------------------
HeretaungaFlowerShop_EventScript_Mum::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, HeretaungaFlowerShop_EventScript_MumShop
	msgbox HeretaungaFlowerShop_Text_MumIntro, MSGBOX_DEFAULT
	call HeretaungaFlowerShop_EventScript_OpenMintShop
	msgbox HeretaungaFlowerShop_Text_MumOutro, MSGBOX_DEFAULT
	release
	end

HeretaungaFlowerShop_EventScript_MumShop::
	msgbox HeretaungaFlowerShop_Text_MumReturning, MSGBOX_DEFAULT
	call HeretaungaFlowerShop_EventScript_OpenMintShop
	msgbox HeretaungaFlowerShop_Text_MumOutro, MSGBOX_DEFAULT
	release
	end

HeretaungaFlowerShop_EventScript_OpenMintShop::
	message HeretaungaFlowerShop_Text_WhichMint
	waitmessage
	pokemart HeretaungaFlowerShop_MintShelf
	return

	.align 2
HeretaungaFlowerShop_MintShelf:
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_MODEST_MINT
	.2byte ITEM_JOLLY_MINT
	.2byte ITEM_TIMID_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_IMPISH_MINT
	.2byte ITEM_CAREFUL_MINT
	.2byte ITEM_RELAXED_MINT
	.2byte ITEM_HASTY_MINT
	pokemartlistend

HeretaungaFlowerShop_EventScript_Regular::
	lock
	faceplayer
	msgbox HeretaungaFlowerShop_Text_Regular, MSGBOX_DEFAULT
	release
	end

HeretaungaFlowerShop_EventScript_PlaqueSign::
	msgbox HeretaungaFlowerShop_Text_Plaque, MSGBOX_SIGN
	end

@ ------------------------- text -------------------------
HeretaungaFlowerShop_Text_MumIntro:
	.string "Mum: Kia ora, love. Mind the\n"
	.string "seed trays.\p"
	.string "This was your father's building\n"
	.string "once. The whole Bay was run out\l"
	.string "of this room - deals, favours,\l"
	.string "that awful brass sign on the\l"
	.string "door.\p"
	.string "I tore the sign down the week\n"
	.string "he moved to Ahuriri. Put in\l"
	.string "grow-lights instead.\p"
	.string "Now it grows things.\n"
	.string "That's better work.$"

HeretaungaFlowerShop_Text_MumReturning:
	.string "Mum: Back again, Orchard Badge\n"
	.string "and all.\p"
	.string "Your father collects power.\n"
	.string "I collect cuttings.\p"
	.string "…One of us sleeps at night.\p"
	.string "The mints are fresh in. Take\n"
	.string "your pick.$"

HeretaungaFlowerShop_Text_WhichMint:
	.string "Mum: A mint won't change what a\n"
	.string "Pokemon IS.\p"
	.string "Just which parts of it lean\n"
	.string "toward the sun. Which one?$"

HeretaungaFlowerShop_Text_MumOutro:
	.string "Mum: Plant them somewhere they\n"
	.string "can grow into it.\p"
	.string "…That goes for the mints AND\n"
	.string "for you, love.$"

HeretaungaFlowerShop_Text_Regular:
	.string "Old-timers still call this place\n"
	.string "“the Mob office.”\p"
	.string "Force of habit. Nobody's signed\n"
	.string "a deal in here for years.\p"
	.string "Best rongoa and seedlings in\n"
	.string "Heretaunga now, but.$"

HeretaungaFlowerShop_Text_Plaque:
	.string "A brass rectangle, unscrewed and\n"
	.string "left leaning in the corner.\p"
	.string "The old lettering still reads:\p"
	.string "“BAY DEVELOPMENT - HEAD OFFICE.”\p"
	.string "Someone has taped a seed packet\n"
	.string "over the word OFFICE.$"
