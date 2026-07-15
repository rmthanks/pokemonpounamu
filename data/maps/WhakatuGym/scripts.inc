WhakatuGym_MapScripts::
	.byte 0

WhakatuGym_EventScript_Roto::
	lock
	faceplayer
	goto_if_set FLAG_BADGE06_GET, WhakatuGym_EventScript_RotoRetalk
	goto_if_unset FLAG_BADGE05_GET, WhakatuGym_EventScript_RotoNoBadge
	msgbox WhakatuGym_Text_Pre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ROTO, WhakatuGym_Text_Defeat
	msgbox WhakatuGym_Text_BadgeSpeech, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message WhakatuGym_Text_ReceivedBadge
	waitfanfare
	waitmessage
	setflag FLAG_BADGE06_GET
	msgbox WhakatuGym_Text_After, MSGBOX_DEFAULT
	release
	end

WhakatuGym_EventScript_RotoNoBadge::
	msgbox WhakatuGym_Text_NoBadge, MSGBOX_DEFAULT
	release
	end

WhakatuGym_EventScript_RotoRetalk::
	msgbox WhakatuGym_Text_Retalk, MSGBOX_DEFAULT
	release
	end

WhakatuGym_EventScript_Prospect::
	trainerbattle_single TRAINER_WHAKATU_PROSPECT, WhakatuGym_Text_ProspectIn, WhakatuGym_Text_ProspectDefeat
	msgbox WhakatuGym_Text_ProspectPost, MSGBOX_AUTOCLOSE
	end

WhakatuGym_Text_NoBadge:
	.string "Roto: Not yet, challenger.\nEarn your way down the island first.\pCome back with the badge before mine.$"

WhakatuGym_Text_Pre:
	.string "Roto: Sunniest city in the country, and I keep it warmer still.\pMy brother Maui slowed the sun so folk had time to live.\pMe? I just make sure they're never cold doing it.\pWarm up, challenger!\p"
	.string "My brother snared the sun once.\nIn here, I never let it set.\lHarsh sunlight, all battle.$"

WhakatuGym_Text_Defeat:
	.string "…Hot enough for you?$"

WhakatuGym_Text_BadgeSpeech:
	.string "Roto: Well fought. Take it - you\nearned every inch.$"

WhakatuGym_Text_ReceivedBadge:
	.string "{PLAYER} received the Ember Badge\nfrom Roto!$"

WhakatuGym_Text_After:
	.string "Roto: Sixth of eight. Two to go, and the last two bite - the mountains take the warmth right out of a road.\pWrap up. Head to Otautahi. Pou's waiting, and Pou does NOT do warm.$"

WhakatuGym_Text_Retalk:
	.string "Roto: Stay for a feed. The south gets cold and I've got soup.$"

WhakatuGym_Text_ProspectIn:
	.string "I keep the coals for Leader Roto! Mind the sparks!$"

WhakatuGym_Text_ProspectDefeat:
	.string "Doused!$"

WhakatuGym_Text_ProspectPost:
	.string "Roto says a Fire gym in the coldest island is a promise. Someone has to hold the warm.$"

WhakatuGym_EventScript_PNell::
	trainerbattle_single TRAINER_GYM6_NELL, WhakatuGym_Text_PNellIntro, WhakatuGym_Text_PNellDefeat
	msgbox WhakatuGym_Text_PNellPost, MSGBOX_AUTOCLOSE
	end

WhakatuGym_Text_PNellIntro:
	.string "Nell: Sixty years I've watched this\nland. Show me something new.$"

WhakatuGym_Text_PNellDefeat:
	.string "…That was new.$"

WhakatuGym_Text_PNellPost:
	.string "The land remembers everyone\nwho crosses it.$"

WhakatuGym_EventScript_POscar::
	trainerbattle_single TRAINER_GYM6_OSCAR, WhakatuGym_Text_POscarIntro, WhakatuGym_Text_POscarDefeat
	msgbox WhakatuGym_Text_POscarPost, MSGBOX_AUTOCLOSE
	end

WhakatuGym_Text_POscarIntro:
	.string "Oscar: I've tramped every track in\nthis region. Fight me.$"

WhakatuGym_Text_POscarDefeat:
	.string "Blisters AND a loss. Ka pai.$"

WhakatuGym_Text_POscarPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"
