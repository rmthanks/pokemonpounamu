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
