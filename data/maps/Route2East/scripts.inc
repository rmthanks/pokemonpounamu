Route2East_MapScripts::
	.byte 0

Route2East_EventScript_Mihi::
	trainerbattle_single TRAINER_R2E_MIHI, Route2East_Text_MihiIntro, Route2East_Text_MihiDefeat
	msgbox Route2East_Text_MihiPost, MSGBOX_AUTOCLOSE
	end

Route2East_EventScript_Hemi::
	trainerbattle_single TRAINER_R2E_HEMI, Route2East_Text_HemiIntro, Route2East_Text_HemiDefeat
	msgbox Route2East_Text_HemiPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_MihiIntro:
	.string "Picnic spot with a view of\n"
	.string "Young Nick's Head!\p"
	.string "You can share it if you can\n"
	.string "beat me for it.$"

Route2East_Text_MihiDefeat:
	.string "Fine! There's plenty of view.$"

Route2East_Text_MihiPost:
	.string "My Hoppip family have ridden\n"
	.string "this coast wind for six\l"
	.string "generations.\p"
	.string "Watch them go. Little legends.$"

Route2East_Text_HemiIntro:
	.string "First light in the whole world\n"
	.string "lands on Turanga!\p"
	.string "Nan says the sun's lazy\n"
	.string "everywhere else. Battle me!$"

Route2East_Text_HemiDefeat:
	.string "Aue! Beaten before breakfast.$"

Route2East_Text_HemiPost:
	.string "If you're chasing the sunrise,\n"
	.string "Hikurangi's the mountain for it.\p"
	.string "But you don't just WALK up\n"
	.string "Hikurangi, eh. It's tapu.$"

Route2East_EventScript_PMatiu::
	trainerbattle_single TRAINER_R2E2_MATIU, Route2East_Text_PMatiuIntro, Route2East_Text_PMatiuDefeat
	msgbox Route2East_Text_PMatiuPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PMatiuIntro:
	.string "Matiu: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route2East_Text_PMatiuDefeat:
	.string "The forecast said nothing\nabout you.$"

Route2East_Text_PMatiuPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route2East_EventScript_PPetera::
	trainerbattle_single TRAINER_R2E2_PETERA, Route2East_Text_PPeteraIntro, Route2East_Text_PPeteraDefeat
	msgbox Route2East_Text_PPeteraPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PPeteraIntro:
	.string "Petera: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route2East_Text_PPeteraDefeat:
	.string "The forecast said nothing\nabout you.$"

Route2East_Text_PPeteraPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route2East_EventScript_PRawiri::
	trainerbattle_single TRAINER_R2E2_RAWIRI, Route2East_Text_PRawiriIntro, Route2East_Text_PRawiriDefeat
	msgbox Route2East_Text_PRawiriPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PRawiriIntro:
	.string "Rawiri: This is protected land.\nProve you respect it.$"

Route2East_Text_PRawiriDefeat:
	.string "You fight like you care.$"

Route2East_Text_PRawiriPost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Route2East_EventScript_PTimoti::
	trainerbattle_single TRAINER_R2E2_TIMOTI, Route2East_Text_PTimotiIntro, Route2East_Text_PTimotiDefeat
	msgbox Route2East_Text_PTimotiPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PTimotiIntro:
	.string "Timoti: These paddocks don't run\nthemselves, but the dog helps.$"

Route2East_Text_PTimotiDefeat:
	.string "The dog's still the best\nworker here.$"

Route2East_Text_PTimotiPost:
	.string "Gates SHUT behind you,\nthanks.$"

Route2East_EventScript_PHohepa::
	trainerbattle_single TRAINER_R2E2_HOHEPA, Route2East_Text_PHohepaIntro, Route2East_Text_PHohepaDefeat
	msgbox Route2East_Text_PHohepaPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PHohepaIntro:
	.string "Hohepa: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route2East_Text_PHohepaDefeat:
	.string "The forecast said nothing\nabout you.$"

Route2East_Text_PHohepaPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route2East_EventScript_SignNorth::
	msgbox Route2East_Text_SignNorth, MSGBOX_SIGN
	end

Route2East_Text_SignNorth:
	.string "ROUTE 2\n"
	.string "South to AHURIRI$"

Route2East_EventScript_SignSouth::
	msgbox Route2East_Text_SignSouth, MSGBOX_SIGN
	end

Route2East_Text_SignSouth:
	.string "ROUTE 2\n"
	.string "North to TURANGA$"

@ ------------------------------------------------------------------
@ The Wairoa end of the road (moved out of Wairoa, Sept 2026): the old
@ lighthouse keeper and his job, the eel man, and Panapa the fisher.
@ ------------------------------------------------------------------
Route2East_EventScript_LightKeeper::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x28B, Route2East_LIGHTJOB_Done
	msgbox Route2East_Text_LIGHTJOBAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route2East_LIGHTJOB_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Route2East_LIGHTJOB_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_MAREEP, Route2East_LIGHTJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_FLAAFFY, Route2East_LIGHTJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_AMPHAROS, Route2East_LIGHTJOB_Good
	msgbox Route2East_Text_LIGHTJOBWrong, MSGBOX_DEFAULT
	release
	end

Route2East_LIGHTJOB_Good::
	msgbox Route2East_Text_LIGHTJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_MAGNET
	goto_if_eq VAR_RESULT, FALSE, Route2East_LIGHTJOB_Full
	setflag FLAG_UNUSED_0x28B
	release
	end

Route2East_LIGHTJOB_No::
	msgbox Route2East_Text_LIGHTJOBNo, MSGBOX_DEFAULT
	release
	end

Route2East_LIGHTJOB_Full::
	release
	end

Route2East_LIGHTJOB_Done::
	msgbox Route2East_Text_LIGHTJOBAfter, MSGBOX_DEFAULT
	release
	end

Route2East_Text_LIGHTJOBAsk:
	.string "Kept the old lighthouse forty\n"
	.string "years. Now it sits in town like\l"
	.string "a retired soldier.\p"
	.string "They say out east there's a\n"
	.string "sheep with a light in its tail.\l"
	.string "A lighthouse that walks! Show\l"
	.string "me one before I go, would you?$"

Route2East_Text_LIGHTJOBNo:
	.string "A light doesn't choose who it\n"
	.string "saves. Worth thinking about,\l"
	.string "the company you're headed for.$"

Route2East_Text_LIGHTJOBWrong:
	.string "Handsome, but I can't see a\n"
	.string "light on it anywhere.$"

Route2East_Text_LIGHTJOBThanks:
	.string "Would you look at that. A light\n"
	.string "that walks, and it chose to\l"
	.string "walk with you.\p"
	.string "Here. It came off the old lamp\n"
	.string "mechanism. It still pulls\l"
	.string "toward something.$"

Route2East_Text_LIGHTJOBAfter:
	.string "A light doesn't choose who it\n"
	.string "saves. Yours seems to have\l"
	.string "chosen anyway.$"

Route2East_EventScript_EelMan::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x032, Route2East_EventScript_EelMan_Done
	msgbox Route2East_Text_EelMan, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 3
	setflag FLAG_UNUSED_0x032
	release
	end

Route2East_EventScript_EelMan_Done::
	msgbox Route2East_Text_EelMan_After, MSGBOX_DEFAULT
	release
	end

Route2East_Text_EelMan:
	.string "The river's the boss in Wairoa.\n"
	.string "Floods when it wants, feeds\l"
	.string "us when it forgives.\p"
	.string "Heading up the coast? Take\n"
	.string "these. Everything worth\l"
	.string "catching is past the bridge.$"

Route2East_Text_EelMan_After:
	.string "Tight lines, kid. Mind the\n"
	.string "river fog at night.$"

Route2East_EventScript_PWero::
	trainerbattle_single TRAINER_WRT_WERO, Route2East_Text_PWeroIntro, Route2East_Text_PWeroDefeat
	msgbox Route2East_Text_PWeroPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PWeroIntro:
	.string "Panapa: Patience. That's fishing.\nAlso that's battling.$"

Route2East_Text_PWeroDefeat:
	.string "I bit too early.$"

Route2East_Text_PWeroPost:
	.string "A bad day's fishing beats a\ngood day's working.$"
