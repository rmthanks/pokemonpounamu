TeMataTrack_MapScripts::
	.byte 0

@ ------------------------------------------------------------------
@ Te Mata Track. Closed the entire game. The quake opened it.
@ The first ascent happens in the post-game, after the credits.
@ ------------------------------------------------------------------
TeMataTrack_EventScript_Tramper::
	lock
	faceplayer
	msgbox TeMataTrack_Text_Tramper, MSGBOX_DEFAULT
	release
	end

TeMataTrack_EventScript_RidgeWoman::
	lock
	faceplayer
	msgbox TeMataTrack_Text_RidgeWoman, MSGBOX_DEFAULT
	release
	end

TeMataTrack_Text_Tramper:
	.string "They felt it in Otepoti. They\n"
	.string "felt it in Waihopai.\p"
	.string "One quake, the whole motu,\n"
	.string "same second.\p"
	.string "But it STARTED here. Right\n"
	.string "under this track.\p"
	.string "…Something stood up inside the\n"
	.string "hill, kid.\p"
	.string "I carried a fridge up the\n"
	.string "Kaimais once. I'm not going\l"
	.string "up THERE.$"

TeMataTrack_Text_RidgeWoman:
	.string "The pou at the crown split down\n"
	.string "the middle. Clean.\p"
	.string "Like something opened it from\n"
	.string "the inside. Not broken - OPENED.\p"
	.string "My nan always said the ridge\n"
	.string "was a body. A rangatira lying\l"
	.string "down, sleeping off a long walk.\p"
	.string "Whole town laughed at her.\p"
	.string "…Nobody's laughed since\n"
	.string "Tuesday.$"
