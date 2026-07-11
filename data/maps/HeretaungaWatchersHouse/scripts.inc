HeretaungaWatchersHouse_MapScripts::
	.byte 0

HeretaungaWatchersHouse_EventScript_QuietMan::
	lock
	faceplayer
	msgbox HeretaungaWatchersHouse_Text_QuietMan, MSGBOX_DEFAULT
	release
	end

HeretaungaWatchersHouse_Text_QuietMan:
	.string "...You didn't see me, and I\n"
	.string "didn't see you.\p"
	.string "Word of advice, free of charge:\n"
	.string "the Bay looks after its own,\l"
	.string "and it never forgets a name.$"

