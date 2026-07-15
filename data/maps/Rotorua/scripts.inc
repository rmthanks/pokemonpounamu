Rotorua_MapScripts::
	.byte 0

Rotorua_EventScript_PoolMan::
	msgbox Rotorua_Text_PoolMan, MSGBOX_NPC
	end

Rotorua_EventScript_StreetWoman::
	msgbox Rotorua_Text_StreetWoman, MSGBOX_NPC
	end

Rotorua_EventScript_GymFan::
	msgbox Rotorua_Text_GymFan, MSGBOX_NPC
	end

Rotorua_EventScript_NoseKid::
	msgbox Rotorua_Text_NoseKid, MSGBOX_NPC
	end

Rotorua_EventScript_Kuia::
	msgbox Rotorua_Text_Kuia, MSGBOX_NPC
	end

Rotorua_EventScript_GeyserSign::
	msgbox Rotorua_Text_GeyserSign, MSGBOX_SIGN
	end

Rotorua_Text_PoolMan:
	.string "These pools have been cooking\n"
	.string "dinners and easing backs for\l"
	.string "seven hundred years.\p"
	.string "The Numel line them up at dusk\n"
	.string "like old men at a spa.$"

Rotorua_Text_StreetWoman:
	.string "You get used to the smell.\p"
	.string "Day three, usually.\n"
	.string "…Day five, tops.$"

Rotorua_Text_GymFan:
	.string "Whenua's never lost on home\n"
	.string "mud!\p"
	.string "Away mud? Different story.\n"
	.string "Don't tell her I said that.$"

Rotorua_Text_NoseKid:
	.string "My teacher says the smell is\n"
	.string "science!\p"
	.string "My nose says the smell is\n"
	.string "PERSONAL.$"

Rotorua_Text_Kuia:
	.string "The land here breathes, dear.\n"
	.string "In and out, same as you.\p"
	.string "Tread like a guest and you'll\n"
	.string "never be one.$"

Rotorua_Text_GeyserSign:
	.string "POHUTU GEYSER VIEWPOINT\p"
	.string "“Please do not time your visit.\n"
	.string "He is not a bus.”$"

@ AWHI - road meeting 2 of 4. The news worsens. met: FLAG_UNUSED_0x27A
Rotorua_EventScript_Awhi::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x27A, Rotorua_EventScript_AwhiRetalk
	msgbox Rotorua_Text_Awhi1, MSGBOX_DEFAULT
	msgbox Rotorua_Text_Awhi2, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x27A
	release
	end

Rotorua_EventScript_AwhiRetalk::
	msgbox Rotorua_Text_AwhiAfter, MSGBOX_DEFAULT
	release
	end

Rotorua_Text_Awhi1:
	.string "Awhi: There you are. You've\n"
	.string "grown a badge or two since\l"
	.string "Wairoa.\p"
	.string "News. It's not good.\p"
	.string "The orchard's struggling - he's\n"
	.string "squeezing every supplier in\l"
	.string "the Bay.\p"
	.string "And my own parents… you should\n"
	.string "hear them now. Under your dad\l"
	.string "they had lines they wouldn't\l"
	.string "cross.\p"
	.string "Under Tama there are no lines.\n"
	.string "I don't recognise them, kid.$"

Rotorua_Text_Awhi2:
	.string "Awhi: …You want to know why I\n"
	.string "left your brother?\p"
	.string "I watched him put the armour on.\n"
	.string "One plate at a time. Every hurt,\l"
	.string "another plate.\p"
	.string "And one day I said something\n"
	.string "true and kind, and it just…\l"
	.string "clinked off.\p"
	.string "You can't love a man through\n"
	.string "armour. I tried, kid. I tried\l"
	.string "for years.$"

Rotorua_Text_AwhiAfter:
	.string "Awhi: The mud pools are good\n"
	.string "for thinking.\p"
	.string "Not so good for answers.$"

Rotorua_EventScript_PHana3::
	trainerbattle_single TRAINER_RTT_HANA3, Rotorua_Text_PHana3Intro, Rotorua_Text_PHana3Defeat
	msgbox Rotorua_Text_PHana3Post, MSGBOX_AUTOCLOSE
	end

Rotorua_Text_PHana3Intro:
	.string "Kahurangi: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Rotorua_Text_PHana3Defeat:
	.string "You can have the sammie.$"

Rotorua_Text_PHana3Post:
	.string "Worth it. Rematch at smoko?$"

Rotorua_EventScript_PToa::
	trainerbattle_single TRAINER_RTT_TOA, Rotorua_Text_PToaIntro, Rotorua_Text_PToaDefeat
	msgbox Rotorua_Text_PToaPost, MSGBOX_AUTOCLOSE
	end

Rotorua_Text_PToaIntro:
	.string "Tuku: I've tramped every track in\nthis region. Fight me.$"

Rotorua_Text_PToaDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Rotorua_Text_PToaPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Rotorua_EventScript_PIpo::
	trainerbattle_single TRAINER_RTT_IPO, Rotorua_Text_PIpoIntro, Rotorua_Text_PIpoDefeat
	msgbox Rotorua_Text_PIpoPost, MSGBOX_AUTOCLOSE
	end

Rotorua_Text_PIpoIntro:
	.string "Marata: My mokopuna says I'm out of\ndate. Let's test that.$"

Rotorua_Text_PIpoDefeat:
	.string "Tell no one.$"

Rotorua_Text_PIpoPost:
	.string "Old tricks are just good\ntricks that lasted.$"

Rotorua_EventScript_RTJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x2A1, Rotorua_EventScript_RTJOB_Done
	msgbox Rotorua_Text_RTJOBAsk, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Rotorua_EventScript_RTJOB_Cancel
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_SLUGMA, Rotorua_EventScript_RTJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_MAGCARGO, Rotorua_EventScript_RTJOB_Good
	msgbox Rotorua_Text_RTJOBWrong, MSGBOX_DEFAULT
	release
	end

Rotorua_EventScript_RTJOB_Good::
	msgbox Rotorua_Text_RTJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_MOOMOO_MILK, 3
	setflag FLAG_UNUSED_0x2A1
	release
	end

Rotorua_EventScript_RTJOB_Cancel::
	release
	end

Rotorua_EventScript_RTJOB_Done::
	msgbox Rotorua_Text_RTJOBAfter, MSGBOX_DEFAULT
	release
	end

Rotorua_Text_RTJOBAsk:
	.string "Kuia Rina: The mud pools miss\ntheir Slugma - the spraying\lscared them off the banks.\pShow me one safe in your care\land I'll believe the pools will\lbe alright.$"

Rotorua_Text_RTJOBThanks:
	.string "Kuia Rina: Aue, there it is!\nWarm as the earth itself.\pThe pools will call them home.$"

Rotorua_Text_RTJOBWrong:
	.string "Kuia Rina: That's not a mud\ndweller, dear.$"

Rotorua_Text_RTJOBAfter:
	.string "Ka pai. The board's been told.$"
