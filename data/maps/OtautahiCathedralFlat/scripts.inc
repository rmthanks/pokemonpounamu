OtautahiCathedralFlat_MapScripts::
	.byte 0

OtautahiCathedralFlat_EventScript_ChoirKid::
	lock
	faceplayer
	msgbox OtautahiCathedralFlat_Text_ChoirKid, MSGBOX_DEFAULT
	release
	end

OtautahiCathedralFlat_Text_ChoirKid:
	.string "We sang in the cardboard\n"
	.string "cathedral! It's REAL cardboard\l"
	.string "and it's REALLY a cathedral!\p"
	.string "Dad cried. He said it's not\n"
	.string "about the stone. Buildings are\l"
	.string "just songs you can stand in.$"

