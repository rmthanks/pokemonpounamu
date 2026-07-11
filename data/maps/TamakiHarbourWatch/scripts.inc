TamakiHarbourWatch_MapScripts::
	.byte 0

TamakiHarbourWatch_EventScript_HarbourMaster::
	lock
	faceplayer
	msgbox TamakiHarbourWatch_Text_HarbourMaster, MSGBOX_DEFAULT
	release
	end

TamakiHarbourWatch_Text_HarbourMaster:
	.string "Harbour watch. Twenty berths,\n"
	.string "two hundred stories.\p"
	.string "Some nights a shape crosses\n"
	.string "the harbour mouth. Too big\l"
	.string "for a boat, too quiet for a\l"
	.string "bird. The log says 'seal'.\l"
	.string "The log is a coward.$"

