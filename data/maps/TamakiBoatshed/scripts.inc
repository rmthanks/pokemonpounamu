TamakiBoatshed_MapScripts::
	.byte 0

TamakiBoatshed_EventScript_BoatBuilder::
	lock
	faceplayer
	msgbox TamakiBoatshed_Text_BoatBuilder, MSGBOX_DEFAULT
	release
	end

TamakiBoatshed_Text_BoatBuilder:
	.string "Building a waka the old way.\n"
	.string "No nails. Lashings and\l"
	.string "patience and good timber.\p"
	.string "My tupuna crossed an ocean on\n"
	.string "trust like this. A kid with\l"
	.string "the right crew can cross\l"
	.string "anything. Even a bad year.$"

