Route1South_MapScripts::
	.byte 0

Route1South_EventScript_Frost::
	trainerbattle_single TRAINER_R1S_FROST, Route1South_Text_FrostIntro, Route1South_Text_FrostDefeat
	msgbox Route1South_Text_FrostPost, MSGBOX_AUTOCLOSE
	end

Route1South_EventScript_Kaia::
	trainerbattle_single TRAINER_R1S_KAIA, Route1South_Text_KaiaIntro, Route1South_Text_KaiaDefeat
	msgbox Route1South_Text_KaiaPost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_FrostIntro:
	.string "Getting properly cold now, eh. My Glalie's finally comfortable.\pYou warm-blooded lot won't last. Battle!$"
Route1South_Text_FrostDefeat:
	.string "Chilled to the bone.$"
Route1South_Text_FrostPost:
	.string "Otepoti's the last city. After that it's just you and the bottom of the world.$"

Route1South_Text_KaiaIntro:
	.string "My Snorunt loves the cold. I do NOT. I'm doing this for her!\pQuick battle before my fingers stop working!$"
Route1South_Text_KaiaDefeat:
	.string "B-b-beaten…$"
Route1South_Text_KaiaPost:
	.string "The road ends at Otepoti. Steepest streets in the world down there. Bring good brakes.$"


@ Pae - "the horizon". The other wanderer.
Route1South_EventScript_Pae::
	lock
	faceplayer
	msgbox Route1South_Text_Pae, MSGBOX_DEFAULT
	release
	end

Route1South_Text_Pae:
	.string "Pae: You can see a long way\n"
	.string "from down here.\p"
	.string "Never quite far enough. But.\p"
	.string "I've walked toward the horizon\n"
	.string "my whole life. You'd be amazed\l"
	.string "how it keeps… moving.\p"
	.string "My little brother stopped\n"
	.string "walking, once. Just STOPPED,\l"
	.string "and looked -\p"
	.string "and the whole world came to\n"
	.string "him.\p"
	.string "Never learned the trick of it\n"
	.string "myself.\p"
	.string "…If you ever meet him - at the\n"
	.string "top of something, probably -\l"
	.string "don't mention me, eh.\p"
	.string "…Or do.\p"
	.string "Do.$"
