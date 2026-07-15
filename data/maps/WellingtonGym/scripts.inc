WellingtonGym_MapScripts::
	.byte 0

WellingtonGym_EventScript_Manu::
	lock
	faceplayer
	goto_if_set FLAG_BADGE05_GET, WellingtonGym_EventScript_ManuRetalk
	goto_if_unset FLAG_BADGE04_GET, WellingtonGym_EventScript_ManuNoBadge
	msgbox WellingtonGym_Text_Pre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MANU, WellingtonGym_Text_Defeat
	msgbox WellingtonGym_Text_BadgeSpeech, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message WellingtonGym_Text_ReceivedBadge
	waitfanfare
	waitmessage
	setflag FLAG_BADGE05_GET
	msgbox WellingtonGym_Text_After, MSGBOX_DEFAULT
	release
	end

WellingtonGym_EventScript_ManuNoBadge::
	msgbox WellingtonGym_Text_NoBadge, MSGBOX_DEFAULT
	release
	end

WellingtonGym_EventScript_ManuRetalk::
	msgbox WellingtonGym_Text_Retalk, MSGBOX_DEFAULT
	release
	end

WellingtonGym_EventScript_Prospect::
	trainerbattle_single TRAINER_WELLINGTON_PROSPECT, WellingtonGym_Text_ProspectIn, WellingtonGym_Text_ProspectDefeat
	msgbox WellingtonGym_Text_ProspectPost, MSGBOX_AUTOCLOSE
	end

WellingtonGym_Text_NoBadge:
	.string "Manu: The wind doesn't answer to\n"
	.string "just anyone, e hoa.\p"
	.string "Earn your way to the capital\n"
	.string "first. Come back with four\l"
	.string "badges behind you.$"

WellingtonGym_Text_Pre:
	.string "Manu: You can't lean on the wind\n"
	.string "in this town.\p"
	.string "But if you trust it - if you stop\n"
	.string "bracing against it - it'll carry\l"
	.string "you further than your legs ever\l"
	.string "could.\p"
	.string "My birds learned that.\n"
	.string "Let's see if you have.\p"
	.string "The gale blows for my birds.\nThey move first. Every turn.$"

WellingtonGym_Text_Defeat:
	.string "…Caught the updraft, did you.$"

WellingtonGym_Text_BadgeSpeech:
	.string "Manu: You stopped fighting the\n"
	.string "gale halfway through and started\l"
	.string "RIDING it.\p"
	.string "That's the whole lesson. Take\n"
	.string "the badge.$"

WellingtonGym_Text_ReceivedBadge:
	.string "{PLAYER} received the Gale Badge\n"
	.string "from Manu!$"

WellingtonGym_Text_After:
	.string "Manu: Fifth of eight.\p"
	.string "The strait's south of here - the\n"
	.string "door to Te Waipounamu.\p"
	.string "They say it's shut. 'Bay business.'\p"
	.string "…Funny how that phrase follows\n"
	.string "you, eh.\p"
	.string "Winds change, though. Doors too.\n"
	.string "Keep going.$"

WellingtonGym_Text_Retalk:
	.string "Manu: Feel that southerly?\p"
	.string "That's the strait breathing.\n"
	.string "Something's shifting down there.$"

WellingtonGym_Text_ProspectIn:
	.string "Leader Manu says a Flying gym in\n"
	.string "the windiest city is just being\l"
	.string "honest about the weather!\p"
	.string "Ride or get blown over!$"

WellingtonGym_Text_ProspectDefeat:
	.string "Grounded in the gusts…$"

WellingtonGym_Text_ProspectPost:
	.string "On a bad day the wind here knocks\n"
	.string "grown adults flat.\p"
	.string "We call it 'a bit fresh.'$"
