AhuririCity_MapScripts::
	.byte 0

AhuririCity_EventScript_DecoLady::
	msgbox AhuririCity_Text_DecoLady, MSGBOX_NPC
	end

@ Job 10: Pania's Reef - show the keeper a Pokemon that sings the sea
@ done flag: FLAG_UNUSED_0x02D
AhuririCity_EventScript_PaniaMan::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x02D, AhuririCity_Pania_Done
	msgbox AhuririCity_Text_PaniaMan, MSGBOX_DEFAULT
	msgbox AhuririCity_Text_PaniaAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AhuririCity_Pania_Declined
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, AhuririCity_Pania_Cancel
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_LAPRAS, AhuririCity_Pania_Sings
	goto_if_eq VAR_RESULT, SPECIES_POPPLIO, AhuririCity_Pania_Sings
	goto_if_eq VAR_RESULT, SPECIES_BRIONNE, AhuririCity_Pania_Sings
	goto_if_eq VAR_RESULT, SPECIES_PRIMARINA, AhuririCity_Pania_Sings
	goto_if_eq VAR_RESULT, SPECIES_WAILMER, AhuririCity_Pania_Sings
	goto_if_eq VAR_RESULT, SPECIES_WAILORD, AhuririCity_Pania_Sings
	bufferspeciesname STR_VAR_1, VAR_RESULT
	msgbox AhuririCity_Text_PaniaNotIt, MSGBOX_DEFAULT
	release
	end

AhuririCity_Pania_Cancel::
AhuririCity_Pania_Declined::
	msgbox AhuririCity_Text_PaniaLater, MSGBOX_DEFAULT
	release
	end

AhuririCity_Pania_Sings::
	bufferspeciesname STR_VAR_1, VAR_RESULT
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	waitmoncry
	msgbox AhuririCity_Text_PaniaSings, MSGBOX_DEFAULT
	giveitem ITEM_PEARL_STRING
	setflag FLAG_UNUSED_0x02D
	release
	end

AhuririCity_Pania_Done::
	msgbox AhuririCity_Text_PaniaAfter, MSGBOX_DEFAULT
	release
	end

@ Job 08: The Pounamu Trail - the carver's apprentice
@ met: FLAG_UNUSED_0x02E; tiers paid: 0x05A (3), 0x05B (8), 0x05C (12)
AhuririCity_EventScript_Carver::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x02E, AhuririCity_Carver_CheckTiers
	msgbox AhuririCity_Text_CarverIntro, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x02E
	goto AhuririCity_Carver_CheckTiers

AhuririCity_Carver_CheckTiers::
	goto_if_unset FLAG_UNUSED_0x270, AhuririCity_Carver_TryTier1
	goto_if_unset FLAG_UNUSED_0x271, AhuririCity_Carver_TryTier2
	goto_if_unset FLAG_UNUSED_0x272, AhuririCity_Carver_TryTier3
	msgbox AhuririCity_Text_CarverAllDone, MSGBOX_DEFAULT
	release
	end

AhuririCity_Carver_TryTier1::
	checkitem ITEM_STAR_PIECE, 3
	goto_if_eq VAR_RESULT, FALSE, AhuririCity_Carver_NotYet
	msgbox AhuririCity_Text_CarverTier1, MSGBOX_DEFAULT
	giveitem ITEM_SHELL_BELL
	setflag FLAG_UNUSED_0x270
	release
	end

AhuririCity_Carver_TryTier2::
	checkitem ITEM_STAR_PIECE, 8
	goto_if_eq VAR_RESULT, FALSE, AhuririCity_Carver_NotYet
	msgbox AhuririCity_Text_CarverTier2, MSGBOX_DEFAULT
	giveitem ITEM_MUSCLE_BAND
	setflag FLAG_UNUSED_0x271
	release
	end

AhuririCity_Carver_TryTier3::
	checkitem ITEM_STAR_PIECE, 12
	goto_if_eq VAR_RESULT, FALSE, AhuririCity_Carver_NotYet
	msgbox AhuririCity_Text_CarverTier3, MSGBOX_DEFAULT
	giveitem ITEM_LIFE_ORB
	setflag FLAG_UNUSED_0x272
	release
	end

AhuririCity_Carver_NotYet::
	msgbox AhuririCity_Text_CarverNotYet, MSGBOX_DEFAULT
	release
	end

AhuririCity_EventScript_Kid::
	msgbox AhuririCity_Text_Kid, MSGBOX_NPC
	end

AhuririCity_EventScript_MobWatcher::
	msgbox AhuririCity_Text_MobWatcher, MSGBOX_NPC
	end

AhuririCity_EventScript_Nana::
	msgbox AhuririCity_Text_Nana, MSGBOX_NPC
	end

@ ------------------------- text -------------------------
AhuririCity_Text_DecoLady:
	.string "After the big quake, the whole\n"
	.string "city rebuilt itself in one style.\p"
	.string "Matching corners. Sunburst\n"
	.string "windows. All of it at once.\p"
	.string "Buildings hold the line better\n"
	.string "when they hold it together.$"

AhuririCity_Text_PaniaMan:
	.string "You know the story of Pania?\p"
	.string "She loved this shore so much\n"
	.string "she became the reef.\p"
	.string "On still mornings you can see\n"
	.string "Water Pokémon sunning out there…\p"
	.string "I like to think it's her lot.$"

AhuririCity_Text_Kid:
	.string "The gym leader Kauri is my hero!\p"
	.string "Nobody in Ahuriri has ever\n"
	.string "beaten him. Not once!\p"
	.string "Dad says that's not the only\n"
	.string "thing nobody's ever done to him…\l"
	.string "whatever that means.$"

AhuririCity_Text_MobWatcher:
	.string "…You're the kid from Heretaunga,\n"
	.string "eh.\p"
	.string "The president knows you're\n"
	.string "coming.\p"
	.string "The president knows everything\n"
	.string "that moves in this Bay.$"

AhuririCity_Text_Nana:
	.string "Ahuriri is all sun and jazz on\n"
	.string "the surface, dear.\p"
	.string "Underneath… well.\p"
	.string "Every family has cellars.$"

AhuririCity_Text_PaniaAsk:
	.string "They say Pania still listens for\n"
	.string "singing over the water.\p"
	.string "Have you a Pokemon that sings\n"
	.string "the sea? Would you show me?$"

AhuririCity_Text_PaniaLater:
	.string "Another still morning, maybe.\p"
	.string "The reef's not going anywhere.\n"
	.string "That's rather the point of her.$"

AhuririCity_Text_PaniaNotIt:
	.string "{STR_VAR_1}, is it? A fine friend.\p"
	.string "…But the sea didn't answer.\p"
	.string "I'll know the right voice when\n"
	.string "I hear it. So will she.$"

AhuririCity_Text_PaniaSings:
	.string "…Aue. Listen to that.\p"
	.string "The whole morning went still.\n"
	.string "Did you feel it?\p"
	.string "Pania heard. I'm sure of it.\p"
	.string "Here - divers bring these up off\n"
	.string "the reef now and then.\p"
	.string "For {STR_VAR_1}. And for you.$"

AhuririCity_Text_PaniaAfter:
	.string "On still mornings I bring the\n"
	.string "reef flowers.\p"
	.string "Someone has to.$"

AhuririCity_Text_CarverIntro:
	.string "See this? River pounamu. Raw.\p"
	.string "The awa tumbles it for a hundred\n"
	.string "years, then leaves it on a bank\l"
	.string "for someone with good eyes.\p"
	.string "I'm apprenticed to a carver away\n"
	.string "down Hokitika. I'm to come home\l"
	.string "with shards - and stories.\p"
	.string "You look like you cover ground.\p"
	.string "Find pounamu shards on your\n"
	.string "travels and bring them past.\l"
	.string "I'll make it worth your while.\p"
	.string "Riverbanks. Lake shores. Anywhere\n"
	.string "the water's done the carrying.$"

AhuririCity_Text_CarverTier1:
	.string "Three shards! Good eyes, eh?\p"
	.string "Keep them - the carver will want\n"
	.string "to see the lot one day.\p"
	.string "But a find deserves a find.\n"
	.string "A wee hei matau. For safe water.$"

AhuririCity_Text_CarverTier2:
	.string "EIGHT? You're not walking the\n"
	.string "motu, you're reading it.\p"
	.string "This one's a toki charm.\n"
	.string "For work that needs doing.$"

AhuririCity_Text_CarverTier3:
	.string "Twelve shards…\p"
	.string "When I write to the carver about\n"
	.string "you, he won't believe me.\p"
	.string "This is a koru. A new spiral off\n"
	.string "an old stem.\p"
	.string "Seemed right, somehow. Go well.$"

AhuririCity_Text_CarverAllDone:
	.string "Hold your shards close. Down in\n"
	.string "Hokitika there's a bench with\l"
	.string "your name on it, I reckon.$"

AhuririCity_Text_CarverNotYet:
	.string "No rush. Pounamu's been waiting\n"
	.string "in those rivers a hundred years.\p"
	.string "It'll wait for you.$"

@ ------------------------------------------------------------------
@ Hori, the Mob's least effective grunt. He wants your shoes.
@ ------------------------------------------------------------------
AhuririCity_EventScript_Hori::
	lock
	faceplayer
	trainerbattle_single TRAINER_HORI_2, AhuririCity_Text_HoriIntro, AhuririCity_Text_HoriDefeat, AhuririCity_EventScript_HoriBeaten
	release
	end

AhuririCity_EventScript_HoriBeaten::
	msgbox AhuririCity_Text_HoriAfter, MSGBOX_DEFAULT
	closemessage
	playse SE_FLEE
	removeobject 7
	setflag FLAG_UNUSED_0x274
	release
	end

AhuririCity_Text_HoriIntro:
	.string "You AGAIN. Right. Rematch.\p"
	.string "One on one for your shoes.\n"
	.string "Double or nothing.\p"
	.string "Shoes AND socks.$"

AhuririCity_Text_HoriDefeat:
	.string "Not the socks too…$"

AhuririCity_Text_HoriAfter:
	.string "The boys keep asking where me\n"
	.string "shoe money's at.\p"
	.string "This changes nothing. I'm in\n"
	.string "a growth phase, me.$"

@ The wharf fisherman - the OLD ROD. (Job 12 seeds from here later.)
AhuririCity_EventScript_WharfFisher::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x283, AhuririCity_EventScript_WharfFisherDone
	msgbox AhuririCity_Text_WharfFisher, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_UNUSED_0x283
	msgbox AhuririCity_Text_WharfFisher2, MSGBOX_DEFAULT
	release
	end

AhuririCity_EventScript_WharfFisherDone::
	msgbox AhuririCity_Text_WharfFisherDone, MSGBOX_DEFAULT
	release
	end

AhuririCity_Text_WharfFisher:
	.string "Half this city's fed off that\n"
	.string "water, one way or another.\p"
	.string "You've got the look of a kid\n"
	.string "who's never dropped a line.\p"
	.string "Here. Spare rod. Old, but the\n"
	.string "fish don't check.$"

AhuririCity_Text_WharfFisher2:
	.string "Kahawai off the wharf. Eels up\n"
	.string "the awa. Carp EVERYWHERE -\l"
	.string "someone let them loose and\l"
	.string "they never left.\p"
	.string "Same old story, eh.$"

AhuririCity_Text_WharfFisherDone:
	.string "Tight lines, kid.\p"
	.string "Mind the reef. She's watching.$"

AhuririCity_EventScript_PPaikea::
	trainerbattle_single TRAINER_AHC_PAIKEA, AhuririCity_Text_PPaikeaIntro, AhuririCity_Text_PPaikeaDefeat
	msgbox AhuririCity_Text_PPaikeaPost, MSGBOX_AUTOCLOSE
	end

AhuririCity_Text_PPaikeaIntro:
	.string "Paikea: Oi! You walked into my line\nof sight. Them's the rules!$"

AhuririCity_Text_PPaikeaDefeat:
	.string "Aw, heck!$"

AhuririCity_Text_PPaikeaPost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"

AhuririCity_EventScript_PRongo::
	trainerbattle_single TRAINER_AHC_RONGO, AhuririCity_Text_PRongoIntro, AhuririCity_Text_PRongoDefeat
	msgbox AhuririCity_Text_PRongoPost, MSGBOX_AUTOCLOSE
	end

AhuririCity_Text_PRongoIntro:
	.string "Rongo: My mokopuna says I'm out of\ndate. Let's test that.$"

AhuririCity_Text_PRongoDefeat:
	.string "Tell no one.$"

AhuririCity_Text_PRongoPost:
	.string "Old tricks are just good\ntricks that lasted.$"

AhuririCity_EventScript_PTaika::
	trainerbattle_single TRAINER_AHC_TAIKA, AhuririCity_Text_PTaikaIntro, AhuririCity_Text_PTaikaDefeat
	msgbox AhuririCity_Text_PTaikaPost, MSGBOX_AUTOCLOSE
	end

AhuririCity_Text_PTaikaIntro:
	.string "Taika: Shh! You'll scare the fish!\n…Too late. Battle.$"

AhuririCity_Text_PTaikaDefeat:
	.string "Snapped my line AND my streak.$"

AhuririCity_Text_PTaikaPost:
	.string "They're biting better since\nyou showed up. Weird.$"
