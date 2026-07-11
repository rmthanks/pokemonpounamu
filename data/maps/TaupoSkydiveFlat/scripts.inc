TaupoSkydiveFlat_MapScripts::
	.byte 0

TaupoSkydiveFlat_EventScript_Diver::
	lock
	faceplayer
	msgbox TaupoSkydiveFlat_Text_Diver, MSGBOX_DEFAULT
	release
	end

TaupoSkydiveFlat_Text_Diver:
	.string "Jumped out of the plane six\n"
	.string "times this week. The lake from\l"
	.string "up there is a blue EYE, bro.\p"
	.string "The crater, I mean. Biggest\n"
	.string "eruption the world ever saw,\l"
	.string "and now it's a postcard.$"

