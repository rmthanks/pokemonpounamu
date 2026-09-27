Turanga_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Turanga_OnTransition_Visited
	.byte 0

Turanga_OnTransition_Visited:
	setflag FLAG_VISITED_DEWFORD_TOWN
	end

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

@ ==================================================================
@ AWHI - road meeting 1 of 4 (moved from Wairoa, Sept 2026). Tama's ex, Mob-born, got out earlier.
@ The window onto home begins. met: FLAG_UNUSED_0x279
@ ==================================================================
Turanga_EventScript_Awhi::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x279, Turanga_EventScript_AwhiRetalk
	msgbox Turanga_Text_Awhi1, MSGBOX_DEFAULT
	msgbox Turanga_Text_Awhi2, MSGBOX_DEFAULT
	msgbox Turanga_Text_Awhi3, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x279
	release
	end

Turanga_EventScript_AwhiRetalk::
	msgbox Turanga_Text_AwhiAfter, MSGBOX_DEFAULT
	release
	end

Turanga_Text_Awhi1:
	.string "A young woman leans on the dairy\n"
	.string "wall like she's been waiting\l"
	.string "all morning.\p"
	.string "Awhi: Heard a truck came through\n"
	.string "the checkpoint with a kid in\l"
	.string "the back.\p"
	.string "…Look at you. Last time I saw\n"
	.string "you, you were knee-high and the\l"
	.string "house was loud.\p"
	.string "You won't remember me. Awhi.\n"
	.string "I used to walk you to kura.$"

Turanga_Text_Awhi2:
	.string "Awhi: I was your brother's girl,\n"
	.string "back before he went hard.\p"
	.string "Mob-born, me. My parents were\n"
	.string "your dad's seconds.\p"
	.string "I got out before Tama could\n"
	.string "drag me down with him.\p"
	.string "…Mostly out. It's work, staying\n"
	.string "out. Nobody tells you that part.$"

Turanga_Text_Awhi3:
	.string "Awhi: Word from home, since\n"
	.string "that's my job now, apparently:\p"
	.string "the Bay's sealed tight. Both\n"
	.string "roads. His people on the gates.\p"
	.string "Your mum's still in the orchard\n"
	.string "and she is NOT leaving it.\p"
	.string "Chin up. That woman bends for\n"
	.string "nobody.\p"
	.string "Go north, kid. I'll find you on\n"
	.string "the road. Someone's got to keep\l"
	.string "you fed with news.$"

Turanga_Text_AwhiAfter:
	.string "Awhi: North, kid. Hikurangi\n"
	.string "first - watch for the camp at\l"
	.string "the foothills.\p"
	.string "I'll find you.$"

Turanga_EventScript_CheckpointWoman::
	msgbox Turanga_Text_CheckpointWoman, MSGBOX_NPC
	end

Turanga_Text_CheckpointWoman:
	.string "You came up through the\n"
	.string "checkpoint?\p"
	.string "…Nobody comes up through the\n"
	.string "checkpoint, dear.\p"
	.string "Come in, sit down. You look like\n"
	.string "you've had a week of it.$"
