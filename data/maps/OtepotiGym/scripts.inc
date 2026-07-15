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
	.string "Huka: The end of the road, and the end of the country.\pSouth of me there's only the ice and the birds and the long dark.\pEight badges means you've walked the whole motu, top to bottom.\pProve you didn't just pass through. Prove you FELT it.\p"
	.string "It's snowing indoors. It won't\nstop. Last one standing keeps\ltheir warmth.$"

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

OtepotiGym_EventScript_PSadie::
	trainerbattle_single TRAINER_GYM8_SADIE, OtepotiGym_Text_PSadieIntro, OtepotiGym_Text_PSadieDefeat
	msgbox OtepotiGym_Text_PSadiePost, MSGBOX_AUTOCLOSE
	end

OtepotiGym_Text_PSadieIntro:
	.string "Sadie: You've got badges. I've got\nstandards. Let's see.$"

OtepotiGym_Text_PSadieDefeat:
	.string "Standards met.$"

OtepotiGym_Text_PSadiePost:
	.string "The League's tougher than me.\nBarely.$"

OtepotiGym_EventScript_PTeddy::
	trainerbattle_single TRAINER_GYM8_TEDDY, OtepotiGym_Text_PTeddyIntro, OtepotiGym_Text_PTeddyDefeat
	msgbox OtepotiGym_Text_PTeddyPost, MSGBOX_AUTOCLOSE
	end

OtepotiGym_Text_PTeddyIntro:
	.string "Teddy: Sixty years I've watched this\nland. Show me something new.$"

OtepotiGym_Text_PTeddyDefeat:
	.string "…That was new.$"

OtepotiGym_Text_PTeddyPost:
	.string "The land remembers everyone\nwho crosses it.$"
