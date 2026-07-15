AhuririSeasideHouse1_MapScripts::
	.byte 0

AhuririSeasideHouse1_EventScript_ReefMan::
	lock
	faceplayer
	msgbox AhuririSeasideHouse1_Text_ReefMan, MSGBOX_DEFAULT
	release
	end

AhuririSeasideHouse1_Text_ReefMan:
	.string "Pania waits out there on the\n"
	.string "reef, they say. Loved a man,\l"
	.string "went back to the sea.\p"
	.string "Some mornings the swell sings.\n"
	.string "Bring a Pokemon that can sing\l"
	.string "back, show the statue keeper.$"


AhuririSeasideHouse1_EventScript_Sully::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x29E, AhuririSeasideHouse1_Sully_After
	goto_if_unset FLAG_UNUSED_0x29D, AhuririSeasideHouse1_Sully_NoBusiness
	msgbox AhuririSeasideHouse1_Text_SullyTakes, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x29E
	release
	end

AhuririSeasideHouse1_Sully_NoBusiness::
	msgbox AhuririSeasideHouse1_Text_SullyNothing, MSGBOX_DEFAULT
	release
	end

AhuririSeasideHouse1_Sully_After::
	msgbox AhuririSeasideHouse1_Text_SullyAfter, MSGBOX_DEFAULT
	release
	end

AhuririSeasideHouse1_Text_SullyTakes:
	.string "…You're the president's kid.\p"
	.string "He sent YOU with this?\p"
	.string "Ha. Starting you early, aren't\n"
	.string "they.\p"
	.string "Sully took the parcel without\n"
	.string "looking at you.$"

AhuririSeasideHouse1_Text_SullyNothing:
	.string "No business with you, kid.$"

AhuririSeasideHouse1_Text_SullyAfter:
	.string "You did fine.\p"
	.string "That's the thing about fine.\n"
	.string "They remember it.$"
