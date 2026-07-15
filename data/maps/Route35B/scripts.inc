Route35B_MapScripts::
	.byte 0

Route35B_EventScript_Manaia::
	trainerbattle_single TRAINER_R35_MANAIA, Route35B_Text_ManaiaIntro, Route35B_Text_ManaiaDefeat
	msgbox Route35B_Text_ManaiaPost, MSGBOX_AUTOCLOSE
	end

Route35B_EventScript_Aroha::
	trainerbattle_single TRAINER_R35_AROHA, Route35B_Text_ArohaIntro, Route35B_Text_ArohaDefeat
	msgbox Route35B_Text_ArohaPost, MSGBOX_AUTOCLOSE
	end

Route35B_Text_ManaiaIntro:
	.string "Every bird on this coast knows\n"
	.string "me by name.\p"
	.string "…Alright, by silhouette.\n"
	.string "Up you go, Taillow!$"

Route35B_Text_ManaiaDefeat:
	.string "Clipped wings, eh.$"

Route35B_Text_ManaiaPost:
	.string "See a bird riding the updraft\n"
	.string "and not flapping once?\p"
	.string "That's the Cape teaching\n"
	.string "patience.$"

Route35B_Text_ArohaIntro:
	.string "I bike the whole Cape every\n"
	.string "summer with my Skiploom!\p"
	.string "Downhill, she rides in the\n"
	.string "basket. Uphill, I do!$"

Route35B_Text_ArohaDefeat:
	.string "Puffed! Totally puffed!$"

Route35B_Text_ArohaPost:
	.string "Opotiki's not far now.\p"
	.string "There's an old fulla at the\n"
	.string "wharf with the BEST story.\l"
	.string "Ask him about the dolphin.$"

Route35B_EventScript_PHuhana::
	trainerbattle_single TRAINER_R35B_HUHANA, Route35B_Text_PHuhanaIntro, Route35B_Text_PHuhanaDefeat
	msgbox Route35B_Text_PHuhanaPost, MSGBOX_AUTOCLOSE
	end

Route35B_Text_PHuhanaIntro:
	.string "Huhana: Kaitiaki of this stretch.\nShow me your manners.$"

Route35B_Text_PHuhanaDefeat:
	.string "Manners AND muscle. Ka pai.$"

Route35B_Text_PHuhanaPost:
	.string "Leave it better than you\nfound it.$"

Route35B_EventScript_POriwa::
	trainerbattle_single TRAINER_R35B_ORIWA, Route35B_Text_POriwaIntro, Route35B_Text_POriwaDefeat
	msgbox Route35B_Text_POriwaPost, MSGBOX_AUTOCLOSE
	end

Route35B_Text_POriwaIntro:
	.string "Oriwa: I've tramped every track in\nthis region. Fight me.$"

Route35B_Text_POriwaDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route35B_Text_POriwaPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route35B_EventScript_PPeti::
	trainerbattle_single TRAINER_R35B_PETI, Route35B_Text_PPetiIntro, Route35B_Text_PPetiDefeat
	msgbox Route35B_Text_PPetiPost, MSGBOX_AUTOCLOSE
	end

Route35B_Text_PPetiIntro:
	.string "Peti: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route35B_Text_PPetiDefeat:
	.string "You earned the view.$"

Route35B_Text_PPetiPost:
	.string "One more ridge. There's always\none more ridge.$"

Route35B_EventScript_PRuta::
	trainerbattle_single TRAINER_R35B_RUTA, Route35B_Text_PRutaIntro, Route35B_Text_PRutaDefeat
	msgbox Route35B_Text_PRutaPost, MSGBOX_AUTOCLOSE
	end

Route35B_Text_PRutaIntro:
	.string "Ruta: My mokopuna says I'm out of\ndate. Let's test that.$"

Route35B_Text_PRutaDefeat:
	.string "Tell no one.$"

Route35B_Text_PRutaPost:
	.string "Old tricks are just good\ntricks that lasted.$"

Route35B_EventScript_PMeri::
	trainerbattle_single TRAINER_R35B_MERI, Route35B_Text_PMeriIntro, Route35B_Text_PMeriDefeat
	msgbox Route35B_Text_PMeriPost, MSGBOX_AUTOCLOSE
	end

Route35B_Text_PMeriIntro:
	.string "Meri: I've been training out here\nALL morning!$"

Route35B_Text_PMeriDefeat:
	.string "Okay, MOST of the morning.$"

Route35B_Text_PMeriPost:
	.string "Don't tell my nan I lost.$"

Route35B_EventScript_PRiria::
	trainerbattle_single TRAINER_R35B_RIRIA, Route35B_Text_PRiriaIntro, Route35B_Text_PRiriaDefeat
	msgbox Route35B_Text_PRiriaPost, MSGBOX_AUTOCLOSE
	end

Route35B_Text_PRiriaIntro:
	.string "Riria: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route35B_Text_PRiriaDefeat:
	.string "You earned the view.$"

Route35B_Text_PRiriaPost:
	.string "One more ridge. There's always\none more ridge.$"

Route35B_EventScript_PKuini::
	trainerbattle_single TRAINER_R35B_KUINI, Route35B_Text_PKuiniIntro, Route35B_Text_PKuiniDefeat
	msgbox Route35B_Text_PKuiniPost, MSGBOX_AUTOCLOSE
	end

Route35B_Text_PKuiniIntro:
	.string "Kuini: I've been training out here\nALL morning!$"

Route35B_Text_PKuiniDefeat:
	.string "Okay, MOST of the morning.$"

Route35B_Text_PKuiniPost:
	.string "Don't tell my nan I lost.$"
