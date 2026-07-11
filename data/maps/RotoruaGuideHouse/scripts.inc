RotoruaGuideHouse_MapScripts::
	.byte 0

RotoruaGuideHouse_EventScript_Guide::
	lock
	faceplayer
	msgbox RotoruaGuideHouse_Text_Guide, MSGBOX_DEFAULT
	release
	end

RotoruaGuideHouse_Text_Guide:
	.string "My great-great-nana guided\n"
	.string "people across the lake to the\l"
	.string "Pink and White Terraces.\p"
	.string "The mountain took the terraces\n"
	.string "back. Guides stayed. There is\l"
	.string "always somewhere to lead\l"
	.string "people, even after the wonder.\p"
	.string "The gym leader, Whenua? Solid\n"
	.string "as the ground and twice as\l"
	.string "patient. You'll like him.$"

