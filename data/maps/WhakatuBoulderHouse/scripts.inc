WhakatuBoulderHouse_MapScripts::
	.byte 0

WhakatuBoulderHouse_EventScript_BoulderMan::
	lock
	faceplayer
	msgbox WhakatuBoulderHouse_Text_BoulderMan, MSGBOX_DEFAULT
	release
	end

WhakatuBoulderHouse_Text_BoulderMan:
	.string "The Boulder Bank! Eight miles\n"
	.string "of stacked stones the sea\l"
	.string "built all by itself!\p"
	.string "Geologists call it a 'natural\n"
	.string "phenomenon'. I call it the\l"
	.string "sea showing off. Same thing,\l"
	.string "less romance.$"

