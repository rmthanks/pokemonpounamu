Turanga_MapScripts::
	.byte 0

@ ------------------------------------------------------------------
@ Turanga - first light city. Gateway to the East Cape.
@ ------------------------------------------------------------------
Turanga_EventScript_Kaitiaki::
	msgbox Turanga_Text_Kaitiaki, MSGBOX_NPC
	end

Turanga_EventScript_Roadworks::
	msgbox Turanga_Text_Roadworks, MSGBOX_NPC
	end

Turanga_EventScript_MainStreetWoman::
	msgbox Turanga_Text_MainStreetWoman, MSGBOX_NPC
	end

Turanga_EventScript_HarbourMan::
	msgbox Turanga_Text_HarbourMan, MSGBOX_NPC
	end

Turanga_EventScript_SunKid::
	msgbox Turanga_Text_SunKid, MSGBOX_NPC
	end

@ Tairawhiti museum: lore + a one-time gift rack.
Turanga_EventScript_Museum::
	lockall
	msgbox Turanga_Text_Museum, MSGBOX_DEFAULT
	goto_if_set FLAG_UNUSED_0x023, Turanga_EventScript_MuseumDone
	msgbox Turanga_Text_MuseumGift, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL, 3
	setflag FLAG_UNUSED_0x023
Turanga_EventScript_MuseumDone::
	releaseall
	end

Turanga_EventScript_TrackSign::
	msgbox Turanga_Text_TrackSign, MSGBOX_SIGN
	end

Turanga_EventScript_TownSign::
	msgbox Turanga_Text_TownSign, MSGBOX_SIGN
	end

@ ------------------------- text -------------------------
Turanga_Text_Kaitiaki:
	.string "That track leads to Hikurangi,\n"
	.string "e hoa. First mountain to catch\l"
	.string "the morning.\p"
	.string "You don't climb it. You're\n"
	.string "WELCOMED onto it.\p"
	.string "…And the mountain isn't\n"
	.string "welcoming anyone just yet.$"

Turanga_Text_Roadworks:
	.string "Route 35 round the East Cape?\n"
	.string "Longest, loneliest, most\l"
	.string "beautiful road in the country.\p"
	.string "All clear as of this morning.\n"
	.string "Off you go, eh.\p"
	.string "Tell the Cape I said hello.$"

Turanga_Text_MainStreetWoman:
	.string "News from the Bay says the gym\n"
	.string "changed hands overnight.\p"
	.string "The son, they're saying.\n"
	.string "…You'd know nothing about\l"
	.string "that, of course.$"

Turanga_Text_HarbourMan:
	.string "Waka came into this bay a\n"
	.string "thousand years ago.\p"
	.string "Everything since is just\n"
	.string "footnotes, mate.$"

Turanga_Text_SunKid:
	.string "I got up SO early and saw the\n"
	.string "sun before ANYONE in the world!\p"
	.string "…Then I had a nap.$"

Turanga_Text_Museum:
	.string "TAIRAWHITI MUSEUM\p"
	.string "“Te Tairawhiti - the coast the\n"
	.string "sun crosses first.”\p"
	.string "Inside: waka hourua, whale bone,\n"
	.string "and a very old photo of a very\l"
	.string "big Wailord.$"

Turanga_Text_MuseumGift:
	.string "The visitor rack has a gift for\n"
	.string "travelling trainers.$"

Turanga_Text_TrackSign:
	.string "HIKURANGI TRACK\p"
	.string "Access by arrangement with the\n"
	.string "kaitiaki. First light is earned.$"

Turanga_Text_TownSign:
	.string "TURANGA\p"
	.string "“First to see the sun.”$"
