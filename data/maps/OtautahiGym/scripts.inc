OtautahiGym_MapScripts::
	.byte 0

OtautahiGym_EventScript_Pou::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, OtautahiGym_EventScript_PouRetalk
	goto_if_unset FLAG_BADGE06_GET, OtautahiGym_EventScript_PouNoBadge
	msgbox OtautahiGym_Text_Pre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_POU, OtautahiGym_Text_Defeat
	msgbox OtautahiGym_Text_BadgeSpeech, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message OtautahiGym_Text_ReceivedBadge
	waitfanfare
	waitmessage
	setflag FLAG_BADGE07_GET
	msgbox OtautahiGym_Text_After, MSGBOX_DEFAULT
	release
	end

OtautahiGym_EventScript_PouNoBadge::
	msgbox OtautahiGym_Text_NoBadge, MSGBOX_DEFAULT
	release
	end

OtautahiGym_EventScript_PouRetalk::
	msgbox OtautahiGym_Text_Retalk, MSGBOX_DEFAULT
	release
	end

OtautahiGym_EventScript_Prospect::
	trainerbattle_single TRAINER_OTAUTAHI_PROSPECT, OtautahiGym_Text_ProspectIn, OtautahiGym_Text_ProspectDefeat
	msgbox OtautahiGym_Text_ProspectPost, MSGBOX_AUTOCLOSE
	end

OtautahiGym_Text_NoBadge:
	.string "Pou: Not yet, challenger.\nEarn your way down the island first.\pCome back with the badge before mine.$"

OtautahiGym_Text_Pre:
	.string "Pou: This city fell down once. All of it, near enough.\pWe rebuilt with steel and stubbornness and a lot of road cones.\pMy team's the same. Bent, tested, standing.\pShow me you can stand too.$"

OtautahiGym_Text_Defeat:
	.string "…Still standing. Good.$"

OtautahiGym_Text_BadgeSpeech:
	.string "Pou: Well fought. Take it - you\nearned every inch.$"

OtautahiGym_Text_ReceivedBadge:
	.string "{PLAYER} received the Anchor Badge\nfrom Pou!$"

OtautahiGym_Text_After:
	.string "Pou: Seventh. One left - Huka, in the deep south, and she's the coldest fight you'll ever have.\pTake the main road south. Wear a coat. Mean it.$"

OtautahiGym_Text_Retalk:
	.string "Pou: We don't say 'good as new' here. We say 'better braced.' Remember that.$"

OtautahiGym_Text_ProspectIn:
	.string "Leader Pou taught me: a structure's only as strong as it is honest. Test me!$"

OtautahiGym_Text_ProspectDefeat:
	.string "Buckled…$"

OtautahiGym_Text_ProspectPost:
	.string "Every building here has a story about the quake. Pou says the gym is one of them.$"
