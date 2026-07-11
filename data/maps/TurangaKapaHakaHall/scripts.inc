TurangaKapaHakaHall_MapScripts::
	.byte 0

TurangaKapaHakaHall_EventScript_Tutor::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x033, TurangaKapaHakaHall_EventScript_Tutor_Done
	msgbox TurangaKapaHakaHall_Text_Tutor, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL, 2
	setflag FLAG_UNUSED_0x033
	release
	end

TurangaKapaHakaHall_EventScript_Tutor_Done::
	msgbox TurangaKapaHakaHall_Text_Tutor_After, MSGBOX_DEFAULT
	release
	end

TurangaKapaHakaHall_Text_Tutor:
	.string "Practice ran late. The rangatahi\n"
	.string "are getting GOOD.\p"
	.string "You're travelling? Stand tall,\n"
	.string "sing loud, know your maunga.\l"
	.string "And take these - manners cost\l"
	.string "nothing, balls cost plenty.$"

TurangaKapaHakaHall_Text_Tutor_After:
	.string "Come back for Matariki.\n"
	.string "The whole coast sings.$"

