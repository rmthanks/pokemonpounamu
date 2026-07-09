OtepotiGym_MapScripts::
	.byte 0

OtepotiGym_EventScript_Huka::
	lock
	faceplayer
	goto_if_set FLAG_BADGE08_GET, OtepotiGym_EventScript_HukaRetalk
	goto_if_unset FLAG_BADGE07_GET, OtepotiGym_EventScript_HukaNoBadge
	msgbox OtepotiGym_Text_Pre, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_HUKA, OtepotiGym_Text_Defeat
	msgbox OtepotiGym_Text_BadgeSpeech, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message OtepotiGym_Text_ReceivedBadge
	waitfanfare
	waitmessage
	setflag FLAG_BADGE08_GET
	msgbox OtepotiGym_Text_After, MSGBOX_DEFAULT
	release
	end

OtepotiGym_EventScript_HukaNoBadge::
	msgbox OtepotiGym_Text_NoBadge, MSGBOX_DEFAULT
	release
	end

OtepotiGym_EventScript_HukaRetalk::
	msgbox OtepotiGym_Text_Retalk, MSGBOX_DEFAULT
	release
	end

OtepotiGym_EventScript_Prospect::
	trainerbattle_single TRAINER_OTEPOTI_PROSPECT, OtepotiGym_Text_ProspectIn, OtepotiGym_Text_ProspectDefeat
	msgbox OtepotiGym_Text_ProspectPost, MSGBOX_AUTOCLOSE
	end

OtepotiGym_Text_NoBadge:
	.string "Huka: Not yet, challenger.\nEarn your way down the island first.\pCome back with the badge before mine.$"

OtepotiGym_Text_Pre:
	.string "Huka: The end of the road, and the end of the country.\pSouth of me there's only the ice and the birds and the long dark.\pEight badges means you've walked the whole motu, top to bottom.\pProve you didn't just pass through. Prove you FELT it.$"

OtepotiGym_Text_Defeat:
	.string "…Cold enough to see clearly now?$"

OtepotiGym_Text_BadgeSpeech:
	.string "Huka: Well fought. Take it - you\nearned every inch.$"

OtepotiGym_Text_ReceivedBadge:
	.string "{PLAYER} received the Frost Badge\nfrom Huka!$"

OtepotiGym_Text_After:
	.string "Huka: Eighth. The last one.\pYou came out of Hawke's Bay with nothing and walked the length of two islands.\pWhatever they took from you up there - you built something bigger down here.\p…Go home when you're ready. The road back opens for champions.$"

OtepotiGym_Text_Retalk:
	.string "Huka: The cold isn't cruel. It's just honest. It shows you what you're made of.$"

OtepotiGym_Text_ProspectIn:
	.string "Leader Huka trains where the sea freezes. Think you can handle the chill?$"

OtepotiGym_Text_ProspectDefeat:
	.string "Frozen solid…$"

OtepotiGym_Text_ProspectPost:
	.string "Huka came here from up north too, they say. The cold suited her. Or she suited it.$"
