RotoruaSteamHouse_MapScripts::
	.byte 0

RotoruaSteamHouse_EventScript_SteamMan::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x036, RotoruaSteamHouse_EventScript_SteamMan_Done
	msgbox RotoruaSteamHouse_Text_SteamMan, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_REPEL, 2
	setflag FLAG_UNUSED_0x036
	release
	end

RotoruaSteamHouse_EventScript_SteamMan_Done::
	msgbox RotoruaSteamHouse_Text_SteamMan_After, MSGBOX_DEFAULT
	release
	end

RotoruaSteamHouse_Text_SteamMan:
	.string "Whole house is heated by the\n"
	.string "earth herself. Free steam,\l"
	.string "forever. Smells like eggs.\p"
	.string "You get used to the smell.\n"
	.string "The tourists don't. Take\l"
	.string "these for the thermal flats.$"

RotoruaSteamHouse_Text_SteamMan_After:
	.string "If the ground gurgles at you,\n"
	.string "gurgle back politely.$"

