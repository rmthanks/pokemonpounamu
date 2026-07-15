Tauranga_MapScripts::
	.byte 0

Tauranga_EventScript_GymKid::
	msgbox Tauranga_Text_GymKid, MSGBOX_NPC
	end

Tauranga_EventScript_MauaoMan::
	msgbox Tauranga_Text_MauaoMan, MSGBOX_NPC
	end

Tauranga_EventScript_StreetWoman::
	msgbox Tauranga_Text_StreetWoman, MSGBOX_NPC
	end

Tauranga_EventScript_PondMan::
	msgbox Tauranga_Text_PondMan, MSGBOX_NPC
	end

Tauranga_EventScript_SurfKid::
	msgbox Tauranga_Text_SurfKid, MSGBOX_NPC
	end

Tauranga_EventScript_GymSign::
	msgbox Tauranga_Text_GymSign, MSGBOX_SIGN
	end

Tauranga_EventScript_MauaoSign::
	msgbox Tauranga_Text_MauaoSign, MSGBOX_SIGN
	end

Tauranga_Text_GymKid:
	.string "Leader Mua? Out on the water.\p"
	.string "He's ALWAYS out on the water.\n"
	.string "His brother slowed the sun and\l"
	.string "Mua still says the days are\l"
	.string "too short.$"

Tauranga_Text_MauaoMan:
	.string "Mauao stands where the tide\n"
	.string "left him.\p"
	.string "The nameless one, who missed\n"
	.string "his chance to reach the sea\l"
	.string "before the dawn.\p"
	.string "…We all know how that feels,\n"
	.string "one way or another.$"

Tauranga_Text_StreetWoman:
	.string "Half this city surfs before\n"
	.string "work.\p"
	.string "The other half lies about it.$"

Tauranga_Text_PondMan:
	.string "Snapper in that basin the size\n"
	.string "of a Wailmer. I swear it on\l"
	.string "my nan.\p"
	.string "…My nan swears otherwise.$"

Tauranga_Text_SurfKid:
	.string "When the gym opens back up, the\n"
	.string "first challenge is paddling out\l"
	.string "past the break!\p"
	.string "I've seen kids come back green.$"

Tauranga_Text_GymSign:
	.string "TAURANGA GYM\n"
	.string "Leader: MUA - the tide's own.\p"
	.string "“Back from fishing.\n"
	.string "Bring your own bait.”$"

Tauranga_Text_MauaoSign:
	.string "MAUAO\p"
	.string "“He stands where the tide left\n"
	.string "him.” Track opens another day.$"

Tauranga_EventScript_PIrirangi::
	trainerbattle_single TRAINER_TGT_IRIRANGI, Tauranga_Text_PIrirangiIntro, Tauranga_Text_PIrirangiDefeat
	msgbox Tauranga_Text_PIrirangiPost, MSGBOX_AUTOCLOSE
	end

Tauranga_Text_PIrirangiIntro:
	.string "Irirangi: The one that got away was\nTHIS big. Like my Pokemon.$"

Tauranga_Text_PIrirangiDefeat:
	.string "Also got away on me.$"

Tauranga_Text_PIrirangiPost:
	.string "Tide's turning. Good luck out\nthere.$"

Tauranga_EventScript_PKereama::
	trainerbattle_single TRAINER_TGT_KEREAMA, Tauranga_Text_PKereamaIntro, Tauranga_Text_PKereamaDefeat
	msgbox Tauranga_Text_PKereamaPost, MSGBOX_AUTOCLOSE
	end

Tauranga_Text_PKereamaIntro:
	.string "Kereama: The one that got away was\nTHIS big. Like my Pokemon.$"

Tauranga_Text_PKereamaDefeat:
	.string "Also got away on me.$"

Tauranga_Text_PKereamaPost:
	.string "Tide's turning. Good luck out\nthere.$"

Tauranga_EventScript_PMereana::
	trainerbattle_single TRAINER_TGT_MEREANA, Tauranga_Text_PMereanaIntro, Tauranga_Text_PMereanaDefeat
	msgbox Tauranga_Text_PMereanaPost, MSGBOX_AUTOCLOSE
	end

Tauranga_Text_PMereanaIntro:
	.string "Mereana: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Tauranga_Text_PMereanaDefeat:
	.string "You can have the sammie.$"

Tauranga_Text_PMereanaPost:
	.string "Worth it. Rematch at smoko?$"

Tauranga_EventScript_TGJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x2A3, Tauranga_EventScript_TGJOB_Done
	msgbox Tauranga_Text_TGJOBAsk, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Tauranga_EventScript_TGJOB_Cancel
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_KRABBY, Tauranga_EventScript_TGJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_KINGLER, Tauranga_EventScript_TGJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_WINGULL, Tauranga_EventScript_TGJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_PELIPPER, Tauranga_EventScript_TGJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_CRAMORANT, Tauranga_EventScript_TGJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_WAILMER, Tauranga_EventScript_TGJOB_Good
	msgbox Tauranga_Text_TGJOBWrong, MSGBOX_DEFAULT
	release
	end

Tauranga_EventScript_TGJOB_Good::
	msgbox Tauranga_Text_TGJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_PEARL, 2
	setflag FLAG_UNUSED_0x2A3
	release
	end

Tauranga_EventScript_TGJOB_Cancel::
	release
	end

Tauranga_EventScript_TGJOB_Done::
	msgbox Tauranga_Text_TGJOBAfter, MSGBOX_DEFAULT
	release
	end

Tauranga_Text_TGJOBAsk:
	.string "Surfer: Paddle-out at dawn for\nold Manu of the bay - every\lboard on the water.\pBring something that swims and\lyou're welcome in the circle.$"

Tauranga_Text_TGJOBThanks:
	.string "Surfer: Yeah, the sea knows\nthat one. Circle's complete.\pThese wash up after. Take two.$"

Tauranga_Text_TGJOBWrong:
	.string "Surfer: Needs to love the salt,\neh. Try again.$"

Tauranga_Text_TGJOBAfter:
	.string "Ka pai. The board's been told.$"
