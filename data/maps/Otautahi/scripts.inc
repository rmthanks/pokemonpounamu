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

Otautahi_EventScript_PEru::
	trainerbattle_single TRAINER_OTT_ERU, Otautahi_Text_PEruIntro, Otautahi_Text_PEruDefeat
	msgbox Otautahi_Text_PEruPost, MSGBOX_AUTOCLOSE
	end

Otautahi_Text_PEruIntro:
	.string "Eru: You've got badges. I've got\nstandards. Let's see.$"

Otautahi_Text_PEruDefeat:
	.string "Standards met.$"

Otautahi_Text_PEruPost:
	.string "The League's tougher than me.\nBarely.$"

Otautahi_EventScript_PHemi::
	trainerbattle_single TRAINER_OTT_HEMI, Otautahi_Text_PHemiIntro, Otautahi_Text_PHemiDefeat
	msgbox Otautahi_Text_PHemiPost, MSGBOX_AUTOCLOSE
	end

Otautahi_Text_PHemiIntro:
	.string "Hemi: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Otautahi_Text_PHemiDefeat:
	.string "The forecast said nothing\nabout you.$"

Otautahi_Text_PHemiPost:
	.string "Southerly's coming. Take care\nup the track.$"

Otautahi_EventScript_PKiri::
	trainerbattle_single TRAINER_OTT_KIRI, Otautahi_Text_PKiriIntro, Otautahi_Text_PKiriDefeat
	msgbox Otautahi_Text_PKiriPost, MSGBOX_AUTOCLOSE
	end

Otautahi_Text_PKiriIntro:
	.string "Kiri: You've got badges. I've got\nstandards. Let's see.$"

Otautahi_Text_PKiriDefeat:
	.string "Standards met.$"

Otautahi_Text_PKiriPost:
	.string "The League's tougher than me.\nBarely.$"

Otautahi_EventScript_PMahina::
	trainerbattle_single TRAINER_OTT_MAHINA, Otautahi_Text_PMahinaIntro, Otautahi_Text_PMahinaDefeat
	msgbox Otautahi_Text_PMahinaPost, MSGBOX_AUTOCLOSE
	end

Otautahi_Text_PMahinaIntro:
	.string "Mahina: Oi! You walked into my line\nof sight. Them's the rules!$"

Otautahi_Text_PMahinaDefeat:
	.string "Aw, heck!$"

Otautahi_Text_PMahinaPost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"

Otautahi_EventScript_PNiko::
	trainerbattle_single TRAINER_OTT_NIKO, Otautahi_Text_PNikoIntro, Otautahi_Text_PNikoDefeat
	msgbox Otautahi_Text_PNikoPost, MSGBOX_AUTOCLOSE
	end

Otautahi_Text_PNikoIntro:
	.string "Niko: Between milkings. You've got\nten minutes. Go.$"

Otautahi_Text_PNikoDefeat:
	.string "Back to the shed, then.$"

Otautahi_Text_PNikoPost:
	.string "Rain's coming. Good for the\ngrass, good for nothing else.$"
