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
