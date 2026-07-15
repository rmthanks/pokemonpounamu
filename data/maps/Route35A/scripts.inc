Route35A_MapScripts::
	.byte 0

Route35A_EventScript_Tai::
	trainerbattle_single TRAINER_R35_TAI, Route35A_Text_TaiIntro, Route35A_Text_TaiDefeat
	msgbox Route35A_Text_TaiPost, MSGBOX_AUTOCLOSE
	end

Route35A_EventScript_Nikora::
	trainerbattle_single TRAINER_R35_NIKORA, Route35A_Text_NikoraIntro, Route35A_Text_NikoraDefeat
	msgbox Route35A_Text_NikoraPost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_TaiIntro:
	.string "Three hundred k of coast and\n"
	.string "every k is mine.\p"
	.string "Well. Mine and the fish's.$"

Route35A_Text_TaiDefeat:
	.string "Reeled in by a ranger!$"

Route35A_Text_TaiPost:
	.string "You won't see another shop till\n"
	.string "Opotiki, e hoa.\p"
	.string "You'll see everything else\n"
	.string "though. Look up sometimes.$"

Route35A_Text_NikoraIntro:
	.string "I've camped every bay on this\n"
	.string "Cape.\p"
	.string "My Electrike keeps the tent\n"
	.string "warm. Mostly on purpose!$"

Route35A_Text_NikoraDefeat:
	.string "Sparks out!$"

Route35A_Text_NikoraPost:
	.string "At night out here the sky goes\n"
	.string "all the way down to the sea.\p"
	.string "No lights between here and\n"
	.string "forever.$"

@ ==================================================================
@ TAWHAI - Dad's oldest friend, the one who got out when Kauri
@ stayed. Self-exiled at the Hikurangi foothills; Tama hunts him.
@ First met here; reappears post-tower as the Ruapehu gatekeeper.
@ met flag: FLAG_UNUSED_0x278 (also gates the Sitrus gift)
@ ==================================================================
Route35A_EventScript_Tawhai::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x278, Route35A_EventScript_TawhaiRetalk
	msgbox Route35A_Text_TawhaiCamp, MSGBOX_DEFAULT
	msgbox Route35A_Text_TawhaiKnowsYou, MSGBOX_DEFAULT
	msgbox Route35A_Text_TawhaiTwoBoys, MSGBOX_DEFAULT
	msgbox Route35A_Text_TawhaiTheSplit, MSGBOX_DEFAULT
	msgbox Route35A_Text_TawhaiHunted, MSGBOX_DEFAULT
	msgbox Route35A_Text_TawhaiWaharoa, MSGBOX_DEFAULT
	msgbox Route35A_Text_TawhaiFoothills, MSGBOX_DEFAULT
	giveitem ITEM_SITRUS_BERRY, 3
	setflag FLAG_UNUSED_0x278
	msgbox Route35A_Text_TawhaiSendoff, MSGBOX_DEFAULT
	release
	end

Route35A_EventScript_TawhaiRetalk::
	goto_if_set FLAG_UNUSED_0x907, Route35A_EventScript_TawhaiPostTower
	msgbox Route35A_Text_TawhaiRetalk, MSGBOX_DEFAULT
	release
	end

Route35A_EventScript_TawhaiPostTower::
	msgbox Route35A_Text_TawhaiPostTower, MSGBOX_DEFAULT
	release
	end

Route35A_Text_TawhaiCamp:
	.string "A tent. A billy over a small\n"
	.string "driftwood fire.\p"
	.string "An old man watching the sea\n"
	.string "like it owes him something.\p"
	.string "Tawhai: Sit, e hoa. Tea's just\n"
	.string "come to the boil, and you look\l"
	.string "like the road's been long.$"

Route35A_Text_TawhaiKnowsYou:
	.string "Tawhai: …The stance is your\n"
	.string "father's. The eyes are your\l"
	.string "mother's.\p"
	.string "You don't know me. But you've\n"
	.string "felt where I should be.\p"
	.string "I'm the hole in your dad's\n"
	.string "stories. The friend who isn't\l"
	.string "in any photo after the wedding.$"

Route35A_Text_TawhaiTwoBoys:
	.string "Tawhai: Two boys ran with the\n"
	.string "Bay Mob once. Best mates.\p"
	.string "One of them saw where the road\n"
	.string "ended, and left.\p"
	.string "The other stayed - to hold the\n"
	.string "roof up for everyone under it.\p"
	.string "…Your dad was always the\n"
	.string "stronger one. That's WHY he\l"
	.string "stayed.\p"
	.string "Strength like his makes a good\n"
	.string "hinge for a heavy door.$"

Route35A_Text_TawhaiTheSplit:
	.string "Tawhai: Those years I tried to\n"
	.string "pull him out… your mum thought\l"
	.string "I was taking him from HER.\p"
	.string "Maybe I was.\p"
	.string "When I finally left alone,\n"
	.string "something in him closed.\p"
	.string "I've carried that every day\n"
	.string "since. Up and down this beach.$"

Route35A_Text_TawhaiHunted:
	.string "Tawhai: Your brother reckons I\n"
	.string "broke your family.\p"
	.string "He's had crews looking for me\n"
	.string "since his voice dropped.\p"
	.string "That's the tent, e hoa. That's\n"
	.string "why the fire stays small.$"

Route35A_Text_TawhaiWaharoa:
	.string "Tawhai: See the waharoa at the\n"
	.string "track head?\p"
	.string "Guardians sleep in every maunga\n"
	.string "of this island. Bird above.\l"
	.string "Taniwha beneath.\p"
	.string "Stone, until the day the giant\n"
	.string "turns over in his sleep.\p"
	.string "Hikurangi catches the first\n"
	.string "light in the world.\p"
	.string "Even a man who can't go home\n"
	.string "can watch that.$"

Route35A_Text_TawhaiFoothills:
	.string "Tawhai: Me? I don't climb.\p"
	.string "I got out of the Bay, but I\n"
	.string "never got FREE of it.\p"
	.string "A man half-escaped keeps to\n"
	.string "the foothills.\p"
	.string "…I keep gates instead.\p"
	.string "Maybe one day I'll keep a gate\n"
	.string "that matters.$"

Route35A_Text_TawhaiSendoff:
	.string "Tawhai: From a tree that\n"
	.string "shouldn't grow this far east.\p"
	.string "Bay stock. I keep it alive out\n"
	.string "of spite.\p"
	.string "You, though - you climb.\p"
	.string "Stay open on the way up. And\n"
	.string "keep your feet on the earth\l"
	.string "that grew you.$"

Route35A_Text_TawhaiRetalk:
	.string "Tawhai: The billy's always on,\n"
	.string "e hoa.\p"
	.string "First light's free.$"

Route35A_Text_TawhaiPostTower:
	.string "Tawhai: Word crawls up the\n"
	.string "coast, even to here.\p"
	.string "The tower's quiet. And Kauri…\p"
	.string "…he stood up in front of it\n"
	.string "all and took the fall himself.\p"
	.string "At the end, with everything\n"
	.string "gone, my mate finally CHOSE.\p"
	.string "You gave him that.\p"
	.string "Don't you carry it like a\n"
	.string "weight, e hoa. Carry it like\l"
	.string "a light.$"

Route35A_EventScript_PEruera::
	trainerbattle_single TRAINER_R35A_ERUERA, Route35A_Text_PErueraIntro, Route35A_Text_PErueraDefeat
	msgbox Route35A_Text_PErueraPost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_PErueraIntro:
	.string "Eruera: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route35A_Text_PErueraDefeat:
	.string "You earned the view.$"

Route35A_Text_PErueraPost:
	.string "One more ridge. There's always\none more ridge.$"

Route35A_EventScript_PHirini::
	trainerbattle_single TRAINER_R35A_HIRINI, Route35A_Text_PHiriniIntro, Route35A_Text_PHiriniDefeat
	msgbox Route35A_Text_PHiriniPost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_PHiriniIntro:
	.string "Hirini: I've tramped every track in\nthis region. Fight me.$"

Route35A_Text_PHiriniDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route35A_Text_PHiriniPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route35A_EventScript_PWetini::
	trainerbattle_single TRAINER_R35A_WETINI, Route35A_Text_PWetiniIntro, Route35A_Text_PWetiniDefeat
	msgbox Route35A_Text_PWetiniPost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_PWetiniIntro:
	.string "Wetini: DOC ranger. Checking traps.\nAnd checking trainers.$"

Route35A_Text_PWetiniDefeat:
	.string "Pest-free AND beaten.$"

Route35A_Text_PWetiniPost:
	.string "Keep to the track and take\nyour rubbish out, eh.$"

Route35A_EventScript_PMihi::
	trainerbattle_single TRAINER_R35A_MIHI, Route35A_Text_PMihiIntro, Route35A_Text_PMihiDefeat
	msgbox Route35A_Text_PMihiPost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_PMihiIntro:
	.string "Mihi: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route35A_Text_PMihiDefeat:
	.string "You can have the sammie.$"

Route35A_Text_PMihiPost:
	.string "Worth it. Rematch at smoko?$"

Route35A_EventScript_PNgaio::
	trainerbattle_single TRAINER_R35A_NGAIO, Route35A_Text_PNgaioIntro, Route35A_Text_PNgaioDefeat
	msgbox Route35A_Text_PNgaioPost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_PNgaioIntro:
	.string "Ngaio: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route35A_Text_PNgaioDefeat:
	.string "You earned the view.$"

Route35A_Text_PNgaioPost:
	.string "One more ridge. There's always\none more ridge.$"

Route35A_EventScript_PRima::
	trainerbattle_single TRAINER_R35A_RIMA, Route35A_Text_PRimaIntro, Route35A_Text_PRimaDefeat
	msgbox Route35A_Text_PRimaPost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_PRimaIntro:
	.string "Rima: Sixty years I've watched this\nland. Show me something new.$"

Route35A_Text_PRimaDefeat:
	.string "…That was new.$"

Route35A_Text_PRimaPost:
	.string "The land remembers everyone\nwho crosses it.$"

Route35A_EventScript_PKawe::
	trainerbattle_single TRAINER_R35A_KAWE, Route35A_Text_PKaweIntro, Route35A_Text_PKaweDefeat
	msgbox Route35A_Text_PKawePost, MSGBOX_AUTOCLOSE
	end

Route35A_Text_PKaweIntro:
	.string "Kawe: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route35A_Text_PKaweDefeat:
	.string "You can have the sammie.$"

Route35A_Text_PKawePost:
	.string "Worth it. Rematch at smoko?$"
