Otepoti_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Otepoti_OnTransition
	.byte 0

Otepoti_OnTransition:
	setflag FLAG_VISITED_MOSSDEEP_CITY
	call_if_unset FLAG_BADGE08_GET, Otepoti_EventScript_HideKauri
	call_if_set FLAG_UNUSED_0x900, Otepoti_EventScript_HideKauri
	end

Otepoti_EventScript_HideKauri::
	setflag FLAG_UNUSED_0x904
	return
Otepoti_EventScript_ColdWoman::
	msgbox Otepoti_Text_ColdWoman, MSGBOX_NPC
	end
Otepoti_EventScript_GymKid::
	msgbox Otepoti_Text_GymKid, MSGBOX_NPC
	end
Otepoti_EventScript_StudentMan::
	msgbox Otepoti_Text_StudentMan, MSGBOX_NPC
	end
Otepoti_EventScript_Kid::
	msgbox Otepoti_Text_Kid, MSGBOX_NPC
	end
Otepoti_EventScript_GymSign::
	msgbox Otepoti_Text_GymSign, MSGBOX_SIGN
	end
Otepoti_Text_ColdWoman:
	.string "Coldest, southernmost city with\na gym. End of the line, love.\pFrom here it's albatross country.\nThen ice. Then nothing.$"
Otepoti_Text_GymKid:
	.string "Leader Huka is the STRONGEST of\nall eight! Badge 8's the real one!\pShe came from up north, like you.\nShe stayed. Made it hers.$"
Otepoti_Text_StudentMan:
	.string "Student town. Cheapest flats,\ncoldest flats, best nights out.\pWe heat the rooms with pure\nstubbornness.$"
Otepoti_Text_Kid:
	.string "Steepest street in the WORLD is\nright here! I rolled a marble down\lit and never saw it again!$"
Otepoti_Text_GymSign:
	.string "OTEPOTI GYM\nLeader: HUKA - the honest cold.\p“Eight badges. You walked the\nwhole motu to reach me.”$"

@ ---- Kauri's warning: the first fatherly act ----
Otepoti_EventScript_Kauri::
	lock
	faceplayer
	msgbox Otepoti_Text_KauriWarning, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_UNUSED_0x900
	setflag FLAG_UNUSED_0x904
	removeobject VAR_LAST_TALKED
	release
	end

Otepoti_Text_KauriWarning:
	.string "…Don't say my name.\p"
	.string "Eight badges. Your mother will\n"
	.string "be insufferable about it.\l"
	.string "Good.\p"
	.string "Listen. I have one thing to\n"
	.string "give you and it isn't an\l"
	.string "apology, so take it.\p"
	.string "Your brother moves on BOTH the\n"
	.string "great birds. Tonight. The lake\l"
	.string "in the north. The sound in the\l"
	.string "south.\p"
	.string "His crews can take one while\n"
	.string "you save the other. You cannot\l"
	.string "reach both. Nobody can.\p"
	.string "The boatmen know. Taupo, or\n"
	.string "the sound. Choose with your\l"
	.string "feet, kid.\p"
	.string "…They saw me come here. That's\n"
	.string "the last door I'll ever be able\l"
	.string "to open for you.\p"
	.string "Make it count.$"

@ ---- The Choice: south fork (Ho-Oh) ----
Otepoti_EventScript_SoundBoatman::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x903, Otepoti_EventScript_SBoatAfter
	goto_if_set FLAG_UNUSED_0x901, Otepoti_EventScript_SBoatTooLate
	goto_if_unset FLAG_UNUSED_0x900, Otepoti_EventScript_SBoatClosed
	msgbox Otepoti_Text_SBoatWarn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Otepoti_EventScript_SBoatNo
	setflag FLAG_UNUSED_0x902
	closemessage
	warp MAP_PIOPIOTAHI, 13, 19
	waitstate
	end

Otepoti_EventScript_SBoatClosed::
	msgbox Otepoti_Text_SBoatClosed, MSGBOX_DEFAULT
	release
	end

Otepoti_EventScript_SBoatNo::
	msgbox Otepoti_Text_SBoatNo, MSGBOX_DEFAULT
	release
	end

Otepoti_EventScript_SBoatTooLate::
	msgbox Otepoti_Text_SBoatTooLate, MSGBOX_DEFAULT
	release
	end

Otepoti_EventScript_SBoatAfter::
	msgbox Otepoti_Text_SBoatAfter, MSGBOX_DEFAULT
	release
	end

Otepoti_Text_SBoatClosed:
	.string "Sailor: Piopiotahi? In THIS\n"
	.string "season? Not for love nor money,\l"
	.string "mate.$"

Otepoti_Text_SBoatWarn:
	.string "Sailor: The sound, is it.\p"
	.string "Straight talk: if we sail,\n"
	.string "there's no reaching the lake\l"
	.string "up north after. No time. There\l"
	.string "was never time for both.\p"
	.string "The one you already know sits\n"
	.string "unguarded the moment we cast\l"
	.string "off.\p"
	.string "…Board her?$"

Otepoti_Text_SBoatNo:
	.string "Sailor: Wise to weigh it.\p"
	.string "Unwise to weigh it long.$"

Otepoti_Text_SBoatTooLate:
	.string "Sailor: You went north, mate.\p"
	.string "…Word is something took the\n"
	.string "firebird out of the sound the\l"
	.string "same night. Nets in the sky.$"

Otepoti_Text_SBoatAfter:
	.string "Sailor: Done is done.\p"
	.string "Sail's yours whenever you want\n"
	.string "the water, champ. But the\l"
	.string "choosing's finished.$"

@ AWHI - road meeting 4 of 4. She goes north to him - and becomes
@ the door. Object flag FLAG_UNUSED_0x27C is SET here: she leaves.
Otepoti_EventScript_Awhi::
	lock
	faceplayer
	msgbox Otepoti_Text_Awhi1, MSGBOX_DEFAULT
	msgbox Otepoti_Text_Awhi2, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	removeobject 7
	setflag FLAG_UNUSED_0x27C
	release
	end

Otepoti_Text_Awhi1:
	.string "Awhi: Last one, kid. Then I'm\n"
	.string "gone a while.\p"
	.string "He's got a tower full of\n"
	.string "frightened people and plans\l"
	.string "with wings on them.\p"
	.string "And he asked me to come north.\n"
	.string "To be near him.\p"
	.string "…I'm going.$"

Otepoti_Text_Awhi2:
	.string "Awhi: Don't say it. I know\n"
	.string "exactly what it looks like.\p"
	.string "But hear me: when you come for\n"
	.string "that tower - and you will -\l"
	.string "you'll need a door.\p"
	.string "I'll be the door.\p"
	.string "…Someone who loves him should\n"
	.string "be there when it ends.\p"
	.string "Even if the him I love ended\n"
	.string "years ago.$"

Otepoti_EventScript_PPounamu::
	trainerbattle_single TRAINER_OPT_POUNAMU, Otepoti_Text_PPounamuIntro, Otepoti_Text_PPounamuDefeat
	msgbox Otepoti_Text_PPounamuPost, MSGBOX_AUTOCLOSE
	end

Otepoti_Text_PPounamuIntro:
	.string "Puna: I've been training out here\nALL morning!$"

Otepoti_Text_PPounamuDefeat:
	.string "Okay, MOST of the morning.$"

Otepoti_Text_PPounamuPost:
	.string "Don't tell my nan I lost.$"

Otepoti_EventScript_PRangi::
	trainerbattle_single TRAINER_OPT_RANGI, Otepoti_Text_PRangiIntro, Otepoti_Text_PRangiDefeat
	msgbox Otepoti_Text_PRangiPost, MSGBOX_AUTOCLOSE
	end

Otepoti_Text_PRangiIntro:
	.string "Rewa: I've been training out here\nALL morning!$"

Otepoti_Text_PRangiDefeat:
	.string "Okay, MOST of the morning.$"

Otepoti_Text_PRangiPost:
	.string "Don't tell my nan I lost.$"

Otepoti_EventScript_PTia::
	trainerbattle_single TRAINER_OPT_TIA, Otepoti_Text_PTiaIntro, Otepoti_Text_PTiaDefeat
	msgbox Otepoti_Text_PTiaPost, MSGBOX_AUTOCLOSE
	end

Otepoti_Text_PTiaIntro:
	.string "Tia: You've got badges. I've got\nstandards. Let's see.$"

Otepoti_Text_PTiaDefeat:
	.string "Standards met.$"

Otepoti_Text_PTiaPost:
	.string "The League's tougher than me.\nBarely.$"

Otepoti_EventScript_PWiki::
	trainerbattle_single TRAINER_OPT_WIKI, Otepoti_Text_PWikiIntro, Otepoti_Text_PWikiDefeat
	msgbox Otepoti_Text_PWikiPost, MSGBOX_AUTOCLOSE
	end

Otepoti_Text_PWikiIntro:
	.string "Wiki: My mokopuna says I'm out of\ndate. Let's test that.$"

Otepoti_Text_PWikiDefeat:
	.string "Tell no one.$"

Otepoti_Text_PWikiPost:
	.string "Old tricks are just good\ntricks that lasted.$"

Otepoti_EventScript_OPJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x2A7, Otepoti_EventScript_OPJOB_Done
	msgbox Otepoti_Text_OPJOBAsk, MSGBOX_DEFAULT
	msgbox Otepoti_Text_OPJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_CARBOS
	setflag FLAG_UNUSED_0x2A7
	release
	end

Otepoti_EventScript_OPJOB_Done::
	msgbox Otepoti_Text_OPJOBAfter, MSGBOX_DEFAULT
	release
	end

Otepoti_Text_OPJOBAsk:
	.string "Scarfie: Steepest street in the\nWORLD, that one. We time runs\lup it for chips.\pYou look quick. Go touch the top\lfence and back - GO!\p…Yeah okay I didn't time it.\lBut you went. Respect.$"

Otepoti_Text_OPJOBThanks:
	.string "Scarfie: Chips are on me.\nWell. Chips are this. Same thing.$"

Otepoti_Text_OPJOBAfter:
	.string "Ka pai. The board's been told.$"

@ ---- Mission batch S2 (2026-09-26) ----
@ Job 41: The Lost Luggage - hand the suitcase to the station porter; done FLAG_UNUSED_0x2AE
Otepoti_EventScript_LUGGAGEJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x2AE, Otepoti_LuggageJob_Done
	goto_if_unset FLAG_UNUSED_0x4BA, Otepoti_LuggageJob_Lost
	msgbox Otepoti_Text_LuggageJobThanks, MSGBOX_DEFAULT
	giveitem ITEM_BIG_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Otepoti_LuggageJob_Full
	setflag FLAG_UNUSED_0x2AE
Otepoti_LuggageJob_Full::
	release
	end

Otepoti_LuggageJob_Lost::
	msgbox Otepoti_Text_LuggageJobLost, MSGBOX_DEFAULT
	release
	end

Otepoti_LuggageJob_Done::
	msgbox Otepoti_Text_LuggageJobAfter, MSGBOX_DEFAULT
	release
	end
Otepoti_Text_LuggageJobLost:
	.string "Porter at the old railway\n"
	.string "station. Fanciest station in\l"
	.string "the country, and we still lose\l"
	.string "things.\p"
	.string "A suitcase bounced off the\n"
	.string "excursion train up the line. If\l"
	.string "you're walking the road north,\l"
	.string "keep an eye out.$"
Otepoti_Text_LuggageJobThanks:
	.string "That's the one! Mrs Galbraith\n"
	.string "will be thrilled. It's her good\l"
	.string "cardigans.\p"
	.string "She said to give the finder\n"
	.string "this. She's very generous about\l"
	.string "cardigans.$"
Otepoti_Text_LuggageJobAfter:
	.string "The station's over a hundred\n"
	.string "years old. Everything else here\l"
	.string "is students. It's a balance.$"

Otepoti_EventScript_PAUAJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x2AF, Otepoti_PAUAJOB_Done
	msgbox Otepoti_Text_PAUAJOBAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Otepoti_PAUAJOB_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Otepoti_PAUAJOB_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_SHELLDER, Otepoti_PAUAJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_CLOYSTER, Otepoti_PAUAJOB_Good
	msgbox Otepoti_Text_PAUAJOBWrong, MSGBOX_DEFAULT
	release
	end

Otepoti_PAUAJOB_Good::
	msgbox Otepoti_Text_PAUAJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_BIG_PEARL
	goto_if_eq VAR_RESULT, FALSE, Otepoti_PAUAJOB_Full
	setflag FLAG_UNUSED_0x2AF
	release
	end

Otepoti_PAUAJOB_No::
	msgbox Otepoti_Text_PAUAJOBNo, MSGBOX_DEFAULT
	release
	end

Otepoti_PAUAJOB_Full::
	release
	end

Otepoti_PAUAJOB_Done::
	msgbox Otepoti_Text_PAUAJOBAfter, MSGBOX_DEFAULT
	release
	end

Otepoti_Text_PAUAJOBAsk:
	.string "Diver: I count paua for the\n"
	.string "fisheries lot. Numbers are down\l"
	.string "round here.\p"
	.string "Seen a healthy one on your\n"
	.string "travels? Show me and cheer an\l"
	.string "old diver up.$"

Otepoti_Text_PAUAJOBNo:
	.string "Diver: No worries. I'll keep\n"
	.string "counting. Somebody has to.$"

Otepoti_Text_PAUAJOBWrong:
	.string "Diver: That's no paua, mate.\n"
	.string "Paua shine blue and green\l"
	.string "inside, like the sea at night.$"

Otepoti_Text_PAUAJOBThanks:
	.string "Diver: Now THAT is a healthy\n"
	.string "paua. Good shell, good colour.\p"
	.string "Found this one in a rock pool\n"
	.string "last winter. You have it. Give\l"
	.string "my count a bit of hope.$"

Otepoti_Text_PAUAJOBAfter:
	.string "Diver: One healthy paua. It's a\n"
	.string "start. Everything is, down\l"
	.string "here.$"

