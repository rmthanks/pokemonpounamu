TamakiFerryHouse_MapScripts::
	.byte 0

TamakiFerryHouse_EventScript_FerryKoro::
	lock
	faceplayer
	msgbox TamakiFerryHouse_Text_FerryKoro, MSGBOX_DEFAULT
	release
	end

TamakiFerryHouse_Text_FerryKoro:
	.string "Devonport ferry, forty years,\n"
	.string "every weekday. The harbour at\l"
	.string "dawn forgives you anything.\p"
	.string "From the water you see the\n"
	.string "whole city at once. Tower and\l"
	.string "all. Nothing looks big from\l"
	.string "the sea, boy. Nothing.$"

