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

Route1South_EventScript_PFaye::
	trainerbattle_single TRAINER_R1SP_FAYE, Route1South_Text_PFayeIntro, Route1South_Text_PFayeDefeat
	msgbox Route1South_Text_PFayePost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_PFayeIntro:
	.string "Faye: These paddocks don't run\nthemselves, but the dog helps.$"

Route1South_Text_PFayeDefeat:
	.string "The dog's still the best\nworker here.$"

Route1South_Text_PFayePost:
	.string "Gates SHUT behind you,\nthanks.$"

Route1South_EventScript_PGil::
	trainerbattle_single TRAINER_R1SP_GIL, Route1South_Text_PGilIntro, Route1South_Text_PGilDefeat
	msgbox Route1South_Text_PGilPost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_PGilIntro:
	.string "Gil: These paddocks don't run\nthemselves, but the dog helps.$"

Route1South_Text_PGilDefeat:
	.string "The dog's still the best\nworker here.$"

Route1South_Text_PGilPost:
	.string "Gates SHUT behind you,\nthanks.$"

Route1South_EventScript_PIke::
	trainerbattle_single TRAINER_R1SP_IKE, Route1South_Text_PIkeIntro, Route1South_Text_PIkeDefeat
	msgbox Route1South_Text_PIkePost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_PIkeIntro:
	.string "Ike: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route1South_Text_PIkeDefeat:
	.string "You earned the view.$"

Route1South_Text_PIkePost:
	.string "One more ridge. There's always\none more ridge.$"

Route1South_EventScript_PJoss::
	trainerbattle_single TRAINER_R1SP_JOSS, Route1South_Text_PJossIntro, Route1South_Text_PJossDefeat
	msgbox Route1South_Text_PJossPost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_PJossIntro:
	.string "Joss: I train where the weather's\nworst. Makes us honest.$"

Route1South_Text_PJossDefeat:
	.string "Honestly beaten.$"

Route1South_Text_PJossPost:
	.string "Strength is showing up in\nthe rain.$"

Route1South_EventScript_PKea::
	trainerbattle_single TRAINER_R1SP_KEA, Route1South_Text_PKeaIntro, Route1South_Text_PKeaDefeat
	msgbox Route1South_Text_PKeaPost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_PKeaIntro:
	.string "Kea: I train where the weather's\nworst. Makes us honest.$"

Route1South_Text_PKeaDefeat:
	.string "Honestly beaten.$"

Route1South_Text_PKeaPost:
	.string "Strength is showing up in\nthe rain.$"

Route1South_EventScript_PLevi::
	trainerbattle_single TRAINER_R1SP_LEVI, Route1South_Text_PLeviIntro, Route1South_Text_PLeviDefeat
	msgbox Route1South_Text_PLeviPost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_PLeviIntro:
	.string "Levi: My mokopuna says I'm out of\ndate. Let's test that.$"

Route1South_Text_PLeviDefeat:
	.string "Tell no one.$"

Route1South_Text_PLeviPost:
	.string "Old tricks are just good\ntricks that lasted.$"

Route1South_EventScript_PMila::
	trainerbattle_single TRAINER_R1SP_MILA, Route1South_Text_PMilaIntro, Route1South_Text_PMilaDefeat
	msgbox Route1South_Text_PMilaPost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_PMilaIntro:
	.string "Mila: Shh! You'll scare the fish!\n…Too late. Battle.$"

Route1South_Text_PMilaDefeat:
	.string "Snapped my line AND my streak.$"

Route1South_Text_PMilaPost:
	.string "They're biting better since\nyou showed up. Weird.$"

Route1South_EventScript_PNed::
	trainerbattle_single TRAINER_R1SP_NED, Route1South_Text_PNedIntro, Route1South_Text_PNedDefeat
	msgbox Route1South_Text_PNedPost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_PNedIntro:
	.string "Ned: This is protected land.\nProve you respect it.$"

Route1South_Text_PNedDefeat:
	.string "You fight like you care.$"

Route1South_Text_PNedPost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Route1South_EventScript_POrla::
	trainerbattle_single TRAINER_R1SP_ORLA, Route1South_Text_POrlaIntro, Route1South_Text_POrlaDefeat
	msgbox Route1South_Text_POrlaPost, MSGBOX_AUTOCLOSE
	end

Route1South_Text_POrlaIntro:
	.string "Orla: You've got badges. I've got\nstandards. Let's see.$"

Route1South_Text_POrlaDefeat:
	.string "Standards met.$"

Route1South_Text_POrlaPost:
	.string "The League's tougher than me.\nBarely.$"
