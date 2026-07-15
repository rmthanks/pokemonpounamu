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

TeMataTrack_EventScript_PMiriama::
	trainerbattle_single TRAINER_TMTP_MIRIAMA, TeMataTrack_Text_PMiriamaIntro, TeMataTrack_Text_PMiriamaDefeat
	msgbox TeMataTrack_Text_PMiriamaPost, MSGBOX_AUTOCLOSE
	end

TeMataTrack_Text_PMiriamaIntro:
	.string "Miriama: My mokopuna says I'm out of\ndate. Let's test that.$"

TeMataTrack_Text_PMiriamaDefeat:
	.string "Tell no one.$"

TeMataTrack_Text_PMiriamaPost:
	.string "Old tricks are just good\ntricks that lasted.$"

TeMataTrack_EventScript_PRerewa::
	trainerbattle_single TRAINER_TMTP_REREWA, TeMataTrack_Text_PRerewaIntro, TeMataTrack_Text_PRerewaDefeat
	msgbox TeMataTrack_Text_PRerewaPost, MSGBOX_AUTOCLOSE
	end

TeMataTrack_Text_PRerewaIntro:
	.string "Rerewa: My mokopuna says I'm out of\ndate. Let's test that.$"

TeMataTrack_Text_PRerewaDefeat:
	.string "Tell no one.$"

TeMataTrack_Text_PRerewaPost:
	.string "Old tricks are just good\ntricks that lasted.$"

TeMataTrack_EventScript_PTainui::
	trainerbattle_single TRAINER_TMTP_TAINUI, TeMataTrack_Text_PTainuiIntro, TeMataTrack_Text_PTainuiDefeat
	msgbox TeMataTrack_Text_PTainuiPost, MSGBOX_AUTOCLOSE
	end

TeMataTrack_Text_PTainuiIntro:
	.string "Tainui: You've got badges. I've got\nstandards. Let's see.$"

TeMataTrack_Text_PTainuiDefeat:
	.string "Standards met.$"

TeMataTrack_Text_PTainuiPost:
	.string "The League's tougher than me.\nBarely.$"

TeMataTrack_EventScript_PWaka::
	trainerbattle_single TRAINER_TMTP_WAKA, TeMataTrack_Text_PWakaIntro, TeMataTrack_Text_PWakaDefeat
	msgbox TeMataTrack_Text_PWakaPost, MSGBOX_AUTOCLOSE
	end

TeMataTrack_Text_PWakaIntro:
	.string "Waka: I train where the weather's\nworst. Makes us honest.$"

TeMataTrack_Text_PWakaDefeat:
	.string "Honestly beaten.$"

TeMataTrack_Text_PWakaPost:
	.string "Strength is showing up in\nthe rain.$"

TeMataTrack_EventScript_PWhetu::
	trainerbattle_single TRAINER_TMTP_WHETU, TeMataTrack_Text_PWhetuIntro, TeMataTrack_Text_PWhetuDefeat
	msgbox TeMataTrack_Text_PWhetuPost, MSGBOX_AUTOCLOSE
	end

TeMataTrack_Text_PWhetuIntro:
	.string "Waru: Kaitiaki of this stretch.\nShow me your manners.$"

TeMataTrack_Text_PWhetuDefeat:
	.string "Manners AND muscle. Ka pai.$"

TeMataTrack_Text_PWhetuPost:
	.string "Leave it better than you\nfound it.$"
