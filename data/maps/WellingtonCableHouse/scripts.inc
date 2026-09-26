WellingtonCableHouse_MapScripts::
	.byte 0

WellingtonCableHouse_EventScript_Bureaucrat::
	lock
	faceplayer
	goto_if_unset FLAG_UNUSED_0x4B6, WellingtonCableHouse_Bureaucrat_Normal
	goto_if_set FLAG_UNUSED_0x4B7, WellingtonCableHouse_Bureaucrat_Normal
	msgbox WellingtonCableHouse_Text_BureaucratSign, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x4B7
	release
	end

WellingtonCableHouse_Bureaucrat_Normal::
	msgbox WellingtonCableHouse_Text_Bureaucrat, MSGBOX_DEFAULT
	release
	end

WellingtonCableHouse_Text_Bureaucrat:
	.string "I draft policy at the big\n"
	.string "round building. Twenty years.\l"
	.string "My proudest work? A footnote.\p"
	.string "Don't smirk. That footnote\n"
	.string "keeps the harbour clean. Real\l"
	.string "power is boring, child. Fear\l"
	.string "the exciting kind.$"

@ ---- Mission batch S2 (2026-09-26) ----
WellingtonCableHouse_Text_BureaucratSign:
	.string "A petition? For a crossing?\p"
	.string "...I drafted the policy that\n"
	.string "removed the last one. Give it\l"
	.string "here. I'll sign it. Footnote\l"
	.string "and all.$"

