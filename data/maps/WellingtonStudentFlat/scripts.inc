WellingtonStudentFlat_MapScripts::
	.byte 0

WellingtonStudentFlat_EventScript_Student::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x293, WellingtonStudentFlat_Student_Petition
	goto_if_unset FLAG_UNUSED_0x4B1, WellingtonStudentFlat_Student_Petition
	msgbox WellingtonStudentFlat_Text_StudentMail, MSGBOX_DEFAULT
	giveitem ITEM_EXP_CANDY_M, 3
	goto_if_eq VAR_RESULT, FALSE, WellingtonStudentFlat_Student_End
	setflag FLAG_UNUSED_0x293
	release
	end

WellingtonStudentFlat_Student_Petition::
	goto_if_unset FLAG_UNUSED_0x4B6, WellingtonStudentFlat_Student_Normal
	goto_if_set FLAG_UNUSED_0x4B9, WellingtonStudentFlat_Student_Normal
	msgbox WellingtonStudentFlat_Text_StudentSign, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x4B9
	release
	end

WellingtonStudentFlat_Student_Normal::
	msgbox WellingtonStudentFlat_Text_Student, MSGBOX_DEFAULT
WellingtonStudentFlat_Student_End::
	release
	end

WellingtonStudentFlat_Text_Student:
	.string "Flat's cold, rent's criminal,\n"
	.string "the mould has a name. We call\l"
	.string "him Gerald.\p"
	.string "But mate, the harbour on a\n"
	.string "still day? There's maybe six\l"
	.string "a year and every one is worth\l"
	.string "the other three fifty-nine.$"

@ ---- Mission batch S2 (2026-09-26) ----
WellingtonStudentFlat_Text_StudentMail:
	.string "A letter? From Koro? Up the\n"
	.string "river?\p"
	.string "“Eat properly and ring your\n"
	.string "mother.” ...Yeah. Yeah, fair.\p"
	.string "Here, have these. They're my\n"
	.string "study snacks. Koro would want\l"
	.string "you fed too.$"
WellingtonStudentFlat_Text_StudentSign:
	.string "A petition! I have never not\n"
	.string "signed a petition. Gerald the\l"
	.string "mould would sign too if he had\l"
	.string "hands.$"

