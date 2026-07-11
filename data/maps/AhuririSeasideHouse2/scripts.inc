AhuririSeasideHouse2_MapScripts::
	.byte 0

AhuririSeasideHouse2_EventScript_BeachKid::
	lock
	faceplayer
	msgbox AhuririSeasideHouse2_Text_BeachKid, MSGBOX_DEFAULT
	release
	end

AhuririSeasideHouse2_Text_BeachKid:
	.string "The gannets at the cape dive\n"
	.string "like DARTS! Fwoosh!\p"
	.string "Koro says the cape is a\n"
	.string "jawbone. A giant's fish-hook!\l"
	.string "Imagine the fish!$"

