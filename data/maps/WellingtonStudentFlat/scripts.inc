WellingtonStudentFlat_MapScripts::
	.byte 0

WellingtonStudentFlat_EventScript_Student::
	lock
	faceplayer
	msgbox WellingtonStudentFlat_Text_Student, MSGBOX_DEFAULT
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

