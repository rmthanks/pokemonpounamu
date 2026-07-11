TurangaNannyFlat_MapScripts::
	.byte 0

TurangaNannyFlat_EventScript_Nanny::
	lock
	faceplayer
	msgbox TurangaNannyFlat_Text_Nanny, MSGBOX_DEFAULT
	release
	end

TurangaNannyFlat_Text_Nanny:
	.string "Up Kaiti hill on a clear night\n"
	.string "you can count every star of\l"
	.string "Matariki, one by one.\p"
	.string "Each star holds someone we\n"
	.string "lost. You say their names.\l"
	.string "That's how they stay.$"

