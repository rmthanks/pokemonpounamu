Route1Kapiti_MapScripts::
	.byte 0
Route1Kapiti_EventScript_Tama2::
	trainerbattle_single TRAINER_R1K_TAMA2, Route1Kapiti_Text_Tama2Intro, Route1Kapiti_Text_Tama2Defeat
	msgbox Route1Kapiti_Text_Tama2Post, MSGBOX_AUTOCLOSE
	end
Route1Kapiti_EventScript_Rae::
	trainerbattle_single TRAINER_R1K_RAE, Route1Kapiti_Text_RaeIntro, Route1Kapiti_Text_RaeDefeat
	msgbox Route1Kapiti_Text_RaePost, MSGBOX_AUTOCLOSE
	end
Route1Kapiti_Text_Tama2Intro:
	.string "Kapiti Island's out there in the\n"
	.string "haze. Sanctuary. No predators.\p"
	.string "Bit like a checkpoint, really.\n"
	.string "Keeps things OUT.$"
Route1Kapiti_Text_Tama2Defeat:
	.string "Grounded.$"
Route1Kapiti_Text_Tama2Post:
	.string "You've got that look. Somebody\n"
	.string "back home shut a door on you.\p"
	.string "…Yeah. I know the look.$"
Route1Kapiti_Text_RaeIntro:
	.string "Wind farm country! Every ridge\n"
	.string "has a turbine and every turbine\l"
	.string "has a name.\p"
	.string "That one's Kevin. Battle!$"
Route1Kapiti_Text_RaeDefeat:
	.string "Kevin is disappointed.$"
Route1Kapiti_Text_RaePost:
	.string "The capital's just south now.\p"
	.string "Te Whanganui-a-Tara. End of the\n"
	.string "island. You'll feel it.$"

Route1Kapiti_EventScript_PGus::
	trainerbattle_single TRAINER_R1KP_GUS, Route1Kapiti_Text_PGusIntro, Route1Kapiti_Text_PGusDefeat
	msgbox Route1Kapiti_Text_PGusPost, MSGBOX_AUTOCLOSE
	end

Route1Kapiti_Text_PGusIntro:
	.string "Gus: These paddocks don't run\nthemselves, but the dog helps.$"

Route1Kapiti_Text_PGusDefeat:
	.string "The dog's still the best\nworker here.$"

Route1Kapiti_Text_PGusPost:
	.string "Gates SHUT behind you,\nthanks.$"

Route1Kapiti_EventScript_PHeath::
	trainerbattle_single TRAINER_R1KP_HEATH, Route1Kapiti_Text_PHeathIntro, Route1Kapiti_Text_PHeathDefeat
	msgbox Route1Kapiti_Text_PHeathPost, MSGBOX_AUTOCLOSE
	end

Route1Kapiti_Text_PHeathIntro:
	.string "Heath: Shh! You'll scare the fish!\n…Too late. Battle.$"

Route1Kapiti_Text_PHeathDefeat:
	.string "Snapped my line AND my streak.$"

Route1Kapiti_Text_PHeathPost:
	.string "They're biting better since\nyou showed up. Weird.$"

Route1Kapiti_EventScript_PIvy::
	trainerbattle_single TRAINER_R1KP_IVY, Route1Kapiti_Text_PIvyIntro, Route1Kapiti_Text_PIvyDefeat
	msgbox Route1Kapiti_Text_PIvyPost, MSGBOX_AUTOCLOSE
	end

Route1Kapiti_Text_PIvyIntro:
	.string "Ivy: I train where the weather's\nworst. Makes us honest.$"

Route1Kapiti_Text_PIvyDefeat:
	.string "Honestly beaten.$"

Route1Kapiti_Text_PIvyPost:
	.string "Strength is showing up in\nthe rain.$"

Route1Kapiti_EventScript_PJonty::
	trainerbattle_single TRAINER_R1KP_JONTY, Route1Kapiti_Text_PJontyIntro, Route1Kapiti_Text_PJontyDefeat
	msgbox Route1Kapiti_Text_PJontyPost, MSGBOX_AUTOCLOSE
	end

Route1Kapiti_Text_PJontyIntro:
	.string "Jonty: This is protected land.\nProve you respect it.$"

Route1Kapiti_Text_PJontyDefeat:
	.string "You fight like you care.$"

Route1Kapiti_Text_PJontyPost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Route1Kapiti_EventScript_PKane::
	trainerbattle_single TRAINER_R1KP_KANE, Route1Kapiti_Text_PKaneIntro, Route1Kapiti_Text_PKaneDefeat
	msgbox Route1Kapiti_Text_PKanePost, MSGBOX_AUTOCLOSE
	end

Route1Kapiti_Text_PKaneIntro:
	.string "Kane: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route1Kapiti_Text_PKaneDefeat:
	.string "You earned the view.$"

Route1Kapiti_Text_PKanePost:
	.string "One more ridge. There's always\none more ridge.$"

Route1Kapiti_EventScript_PLena::
	trainerbattle_single TRAINER_R1KP_LENA, Route1Kapiti_Text_PLenaIntro, Route1Kapiti_Text_PLenaDefeat
	msgbox Route1Kapiti_Text_PLenaPost, MSGBOX_AUTOCLOSE
	end

Route1Kapiti_Text_PLenaIntro:
	.string "Lena: My mokopuna says I'm out of\ndate. Let's test that.$"

Route1Kapiti_Text_PLenaDefeat:
	.string "Tell no one.$"

Route1Kapiti_Text_PLenaPost:
	.string "Old tricks are just good\ntricks that lasted.$"

Route1Kapiti_EventScript_PMilo::
	trainerbattle_single TRAINER_R1KP_MILO, Route1Kapiti_Text_PMiloIntro, Route1Kapiti_Text_PMiloDefeat
	msgbox Route1Kapiti_Text_PMiloPost, MSGBOX_AUTOCLOSE
	end

Route1Kapiti_Text_PMiloIntro:
	.string "Milo: Shh! You'll scare the fish!\n…Too late. Battle.$"

Route1Kapiti_Text_PMiloDefeat:
	.string "Snapped my line AND my streak.$"

Route1Kapiti_Text_PMiloPost:
	.string "They're biting better since\nyou showed up. Weird.$"
