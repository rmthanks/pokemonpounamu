WellingtonCableHouse_MapScripts::
	.byte 0

WellingtonCableHouse_EventScript_Bureaucrat::
	lock
	faceplayer
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

