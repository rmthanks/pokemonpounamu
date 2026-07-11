TamakiRecordShop_MapScripts::
	.byte 0

TamakiRecordShop_EventScript_RecordGuy::
	lock
	faceplayer
	msgbox TamakiRecordShop_Text_RecordGuy, MSGBOX_DEFAULT
	release
	end

TamakiRecordShop_Text_RecordGuy:
	.string "Vinyl only. Don't ask for\n"
	.string "tapes, don't ask for downloads,\l"
	.string "don't ask about the tower.\p"
	.string "...Fine, ONE thing about the\n"
	.string "tower: the day it went quiet,\l"
	.string "every busker in the city\l"
	.string "played the same song. Nobody\l"
	.string "planned it. Cities know.$"

