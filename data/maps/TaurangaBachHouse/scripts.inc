TaurangaBachHouse_MapScripts::
	.byte 0

TaurangaBachHouse_EventScript_BachDad::
	lock
	faceplayer
	msgbox TaurangaBachHouse_Text_BachDad, MSGBOX_DEFAULT
	release
	end

TaurangaBachHouse_Text_BachDad:
	.string "Mount in summer, mate. You\n"
	.string "can't park within a mile and\l"
	.string "you wouldn't want to.\p"
	.string "Half of Wellington gyms up\n"
	.string "here in January. The Flying\l"
	.string "leader trains in our wind!$"

