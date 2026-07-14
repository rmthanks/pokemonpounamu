Otautahi_MapScripts::
	.byte 0
Otautahi_EventScript_RebuildWoman::
	msgbox Otautahi_Text_RebuildWoman, MSGBOX_NPC
	end
Otautahi_EventScript_GymKid::
	msgbox Otautahi_Text_GymKid, MSGBOX_NPC
	end
Otautahi_EventScript_CathedralMan::
	msgbox Otautahi_Text_CathedralMan, MSGBOX_NPC
	end
Otautahi_EventScript_Kid::
	msgbox Otautahi_Text_Kid, MSGBOX_NPC
	end
Otautahi_EventScript_QuakeMan::
	msgbox Otautahi_Text_QuakeMan, MSGBOX_NPC
	end
Otautahi_EventScript_GymSign::
	msgbox Otautahi_Text_GymSign, MSGBOX_SIGN
	end
Otautahi_EventScript_CathedralSign::
	msgbox Otautahi_Text_CathedralSign, MSGBOX_SIGN
	end
Otautahi_Text_RebuildWoman:
	.string "We're a city that came back.\pEvery new building here is\nsomeone deciding to stay.$"
Otautahi_Text_GymKid:
	.string "Leader Pou's a Steel type, but\nhe's the gentlest fella.\p'Steel bends before it breaks,'\nhe says. 'Be steel.'$"
Otautahi_Text_CathedralMan:
	.string "They built a cathedral out of\ncardboard while the stone one\lhealed.\pCardboard! And it's beautiful.\nThat's the whole city, that.$"
Otautahi_Text_Kid:
	.string "There's road cones EVERYWHERE.\nWe've named them all.\pThat one's Sir Cone-ery.$"
Otautahi_Text_QuakeMan:
	.string "Ground shook the whole city down\nonce, son.\pWe don't fear the ground here.\nWe just… respect it. Properly.\p…You'd understand respect for a\nthing that can take your home.$"
Otautahi_Text_GymSign:
	.string "OTAUTAHI GYM\nLeader: POU - braced and standing.\p“Better braced than good as new.”$"
Otautahi_Text_CathedralSign:
	.string "TRANSITIONAL CATHEDRAL\p“Built to last a while. Loved\nlike it'll last forever.”$"

@ ------------------------------------------------------------------
@ Hori, the Mob's least effective grunt. He wants your shoes.
@ ------------------------------------------------------------------
Otautahi_EventScript_Hori::
	lock
	faceplayer
	trainerbattle_single TRAINER_HORI_5, Otautahi_Text_HoriIntro, Otautahi_Text_HoriDefeat, Otautahi_EventScript_HoriBeaten
	release
	end

Otautahi_EventScript_HoriBeaten::
	msgbox Otautahi_Text_HoriAfter, MSGBOX_DEFAULT
	giveitem ITEM_FOCUS_SASH
	closemessage
	playse SE_FLEE
	removeobject 6
	setflag FLAG_UNUSED_0x277
	release
	end

Otautahi_Text_HoriIntro:
	.string "HORI'S FINAL STAND.\p"
	.string "Everything I've got, one last\n"
	.string "time.\p"
	.string "Winner takes every shoe in\n"
	.string "the building.$"

Otautahi_Text_HoriDefeat:
	.string "Take. The. Shoes.$"

Otautahi_Text_HoriAfter:
	.string "…Nah. Keep your shoes, eh.\n"
	.string "They suit ya.\p"
	.string "Tell you what - take me lucky\n"
	.string "sash instead. Never done ME\l"
	.string "any good.\p"
	.string "If the Mob asks? You never saw\n"
	.string "me. I'm off to find honest work.\p"
	.string "…Maybe jandals.$"
