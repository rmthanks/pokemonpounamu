TaurangaGym_MapScripts::
	.byte 0

@ ------------------------------------------------------------------
@ Mua - Water. Maui's fishing brother. Badge 4.
@ ------------------------------------------------------------------
TaurangaGym_EventScript_Mua::
	lock
	faceplayer
	goto_if_set FLAG_BADGE04_GET, TaurangaGym_EventScript_MuaRetalk
	goto_if_unset FLAG_BADGE03_GET, TaurangaGym_EventScript_MuaNoBadge
	msgbox TaurangaGym_Text_MuaPreBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MUA, TaurangaGym_Text_MuaDefeat
	msgbox TaurangaGym_Text_MuaBadgeSpeech, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message TaurangaGym_Text_ReceivedTaiBadge
	waitfanfare
	waitmessage
	setflag FLAG_BADGE04_GET
	msgbox TaurangaGym_Text_MuaSurf, MSGBOX_DEFAULT
	giveitem ITEM_HM03
	msgbox TaurangaGym_Text_MuaAfter, MSGBOX_DEFAULT
	release
	end

TaurangaGym_EventScript_MuaNoBadge::
	msgbox TaurangaGym_Text_MuaNoBadge, MSGBOX_DEFAULT
	release
	end

TaurangaGym_EventScript_MuaRetalk::
	msgbox TaurangaGym_Text_MuaRetalk, MSGBOX_DEFAULT
	release
	end

TaurangaGym_EventScript_Prospect::
	trainerbattle_single TRAINER_TAURANGA_PROSPECT, TaurangaGym_Text_ProspectIntro, TaurangaGym_Text_ProspectDefeat
	msgbox TaurangaGym_Text_ProspectPost, MSGBOX_AUTOCLOSE
	end

@ ------------------------- text -------------------------
TaurangaGym_Text_MuaNoBadge:
	.string "Mua: Whenua's mud first, kid.\n"
	.string "Order of the road.\p"
	.string "The tide can wait.\n"
	.string "The tide is EXCELLENT at\l"
	.string "waiting.$"

TaurangaGym_Text_MuaPreBattle:
	.string "Mua: My little brother slowed\n"
	.string "the sun. Fished up an island.\p"
	.string "You've met him, I hear. Flash as\n"
	.string "ever, was he?\p"
	.string "…Me, I just fish.\p"
	.string "Every day, out past the break,\n"
	.string "since before your parents met.\p"
	.string "Let's see if you can land ME.\p"
	.string "The tide's coming in on your side\nof the sand. Your Pokemon fight\lslowed until it turns.$"

TaurangaGym_Text_MuaDefeat:
	.string "…Well.\p"
	.string "Snapped my line, didn't you.$"

TaurangaGym_Text_MuaBadgeSpeech:
	.string "Mua: You set the hook early and\n"
	.string "you didn't panic when I ran.\p"
	.string "That's fishing. That's the whole\n"
	.string "of it.$"

TaurangaGym_Text_ReceivedTaiBadge:
	.string "{PLAYER} received the Tai Badge\n"
	.string "from Mua!$"

TaurangaGym_Text_MuaAfter:
	.string "Mua: Fourth of eight.\p"
	.string "My famous brother will be\n"
	.string "watching you now. He watches\l"
	.string "everything. Never LIFTS anything,\l"
	.string "mind. Just watches.\p"
	.string "…Family, eh.\p"
	.string "You'd know.$"

TaurangaGym_Text_MuaRetalk:
	.string "Mua: Tide's turning.\p"
	.string "Somewhere south, something's\n"
	.string "biting. I can feel it in my\l"
	.string "elbows.$"

TaurangaGym_Text_ProspectIntro:
	.string "First trial of the Tauranga gym:\n"
	.string "paddle out past the break!\p"
	.string "Second trial: me!$"

TaurangaGym_Text_ProspectDefeat:
	.string "Wiped out past the break…$"

TaurangaGym_Text_ProspectPost:
	.string "Mua's caught everything in that\n"
	.string "ocean except a day off.$"

TaurangaGym_Text_MuaSurf:
	.string "Mua: One more thing. The first\n"
	.string "haul is always shared.\p"
	.string "SURF. My brothers and I pulled\n"
	.string "a whole island out of the sea\l"
	.string "with less.\p"
	.string "The water's yours now. Treat\n"
	.string "her like whanau.$"
