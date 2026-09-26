OtautahiCathedralFlat_MapScripts::
	.byte 0

OtautahiCathedralFlat_EventScript_ChoirKid::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x29C, OtautahiCathedralFlat_CONCERTJOB_Done
	msgbox OtautahiCathedralFlat_Text_CONCERTJOBAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OtautahiCathedralFlat_CONCERTJOB_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, OtautahiCathedralFlat_CONCERTJOB_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_CHATOT, OtautahiCathedralFlat_CONCERTJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_POPPLIO, OtautahiCathedralFlat_CONCERTJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_BRIONNE, OtautahiCathedralFlat_CONCERTJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_PRIMARINA, OtautahiCathedralFlat_CONCERTJOB_Good
	msgbox OtautahiCathedralFlat_Text_CONCERTJOBWrong, MSGBOX_DEFAULT
	release
	end

OtautahiCathedralFlat_CONCERTJOB_Good::
	msgbox OtautahiCathedralFlat_Text_CONCERTJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_THROAT_SPRAY
	goto_if_eq VAR_RESULT, FALSE, OtautahiCathedralFlat_CONCERTJOB_Full
	setflag FLAG_UNUSED_0x29C
	release
	end

OtautahiCathedralFlat_CONCERTJOB_No::
	msgbox OtautahiCathedralFlat_Text_CONCERTJOBNo, MSGBOX_DEFAULT
	release
	end

OtautahiCathedralFlat_CONCERTJOB_Full::
	release
	end

OtautahiCathedralFlat_CONCERTJOB_Done::
	msgbox OtautahiCathedralFlat_Text_CONCERTJOBAfter, MSGBOX_DEFAULT
	release
	end

OtautahiCathedralFlat_Text_CONCERTJOBAsk:
	.string "We sang in the cardboard\n"
	.string "cathedral! It's REAL cardboard\l"
	.string "and it's REALLY a cathedral!\p"
	.string "Our soloist has a cold. Do you\n"
	.string "have a Pokemon that can SING?\l"
	.string "Show me!$"

OtautahiCathedralFlat_Text_CONCERTJOBNo:
	.string "Dad says buildings are just\n"
	.string "songs you can stand in. Ours\l"
	.string "needs a new song!$"

OtautahiCathedralFlat_Text_CONCERTJOBWrong:
	.string "Hmm, that one hums. We need a\n"
	.string "singer!$"

OtautahiCathedralFlat_Text_CONCERTJOBThanks:
	.string "It can sing! It can REALLY\n"
	.string "sing! The choir will lose their\l"
	.string "minds.\p"
	.string "Here, the choir leader gave me\n"
	.string "this for our soloist. You have\l"
	.string "it. Your Pokemon earned it!$"

OtautahiCathedralFlat_Text_CONCERTJOBAfter:
	.string "We sang it at the service. Dad\n"
	.string "cried again. He's a very\l"
	.string "reliable crier.$"

OtautahiCathedralFlat_Text_ChoirKid:
	.string "We sang in the cardboard\n"
	.string "cathedral! It's REAL cardboard\l"
	.string "and it's REALLY a cathedral!\p"
	.string "Dad cried. He said it's not\n"
	.string "about the stone. Buildings are\l"
	.string "just songs you can stand in.$"

