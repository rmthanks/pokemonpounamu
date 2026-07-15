Route7_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route7_OnTransition
	.byte 0

Route7_OnTransition:
	call_if_set FLAG_UNUSED_0x27D, Route7_EventScript_SceneDone
	end

Route7_EventScript_SceneDone::
	setvar VAR_TEMP_0, 1
	return

Route7_EventScript_Kae::
	trainerbattle_single TRAINER_R7_KAE, Route7_Text_KaeIntro, Route7_Text_KaeDefeat
	msgbox Route7_Text_KaePost, MSGBOX_AUTOCLOSE
	end

Route7_EventScript_Rangi::
	trainerbattle_single TRAINER_R7_RANGI, Route7_Text_RangiIntro, Route7_Text_RangiDefeat
	msgbox Route7_Text_RangiPost, MSGBOX_AUTOCLOSE
	end

Route7_Text_KaeIntro:
	.string "Lewis Pass! Longest, highest, loneliest road in the country.\pIf you make it through, you've earned Otautahi. Onix, go!$"
Route7_Text_KaeDefeat:
	.string "Passed…$"
Route7_Text_KaePost:
	.string "Beech forest the whole way. Robins'll follow you for company. Bit of a laugh.$"

Route7_Text_RangiIntro:
	.string "Snow on the tops even now. My Absol smells the weather turning before I do.\pBattle before the front hits!$"
Route7_Text_RangiDefeat:
	.string "Storm's here…$"
Route7_Text_RangiPost:
	.string "Down out of the pass it flattens right out. Canterbury Plains. Big sky, straight roads.$"


@ ==================================================================
@ THE HUNT ENDS HERE. Tama corners Tawhai in the beech forest of the
@ pass - and cannot finish it. Then the confession (staged reveal 1).
@ localids: Tawhai 3, Tama 4. done: FLAG_UNUSED_0x27D
@ ==================================================================
Route7_EventScript_Cornered::
	lockall
	setvar VAR_TEMP_0, 1
	msgbox Route7_Text_Voices, MSGBOX_DEFAULT
	msgbox Route7_Text_CornerTama1, MSGBOX_DEFAULT
	msgbox Route7_Text_CornerTawhai1, MSGBOX_DEFAULT
	msgbox Route7_Text_CornerTama2, MSGBOX_DEFAULT
	msgbox Route7_Text_CornerTawhai2, MSGBOX_DEFAULT
	msgbox Route7_Text_CornerTama3, MSGBOX_DEFAULT
	msgbox Route7_Text_TheFalter, MSGBOX_DEFAULT
	msgbox Route7_Text_CornerTawhai3, MSGBOX_DEFAULT
	msgbox Route7_Text_TheHandShakes, MSGBOX_DEFAULT
	msgbox Route7_Text_CornerTamaExit, MSGBOX_DEFAULT
	closemessage
	playse SE_FLEE
	removeobject 4
	delay 30
	applymovement 3, Route7_Movement_TawhaiFacePlayer
	waitmovement 0
	msgbox Route7_Text_ComeOut, MSGBOX_DEFAULT
	msgbox Route7_Text_Confession1, MSGBOX_DEFAULT
	msgbox Route7_Text_Confession2, MSGBOX_DEFAULT
	msgbox Route7_Text_Confession3, MSGBOX_DEFAULT
	msgbox Route7_Text_Confession4, MSGBOX_DEFAULT
	msgbox Route7_Text_Absolution, MSGBOX_DEFAULT
	msgbox Route7_Text_TawhaiThanks, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x27D
	releaseall
	end

Route7_Movement_TawhaiFacePlayer:
	face_down
	step_end

Route7_Text_Voices:
	.string "Voices, through the beech\n"
	.string "trunks ahead.\p"
	.string "One old. One that you would\n"
	.string "know anywhere.$"

Route7_Text_CornerTama1:
	.string "Tama: TEN YEARS I've looked for\n"
	.string "you, old man.\p"
	.string "You cost me my family, and you\n"
	.string "get a tent and a billy and the\l"
	.string "quiet hills?$"

Route7_Text_CornerTawhai1:
	.string "Tawhai: …Hello, Tama.\p"
	.string "You've your father's stance.$"

Route7_Text_CornerTama2:
	.string "Tama: Don't. Don't do the warm\n"
	.string "thing.\p"
	.string "You tried to take him from us.\n"
	.string "Everything after - the shouting,\l"
	.string "the split, her leaving -\p"
	.string "that's YOURS.$"

Route7_Text_CornerTawhai2:
	.string "Tawhai: I tried to take him OUT,\n"
	.string "boy. Out of the thing that was\l"
	.string "eating him alive.\p"
	.string "I failed. That much is mine,\n"
	.string "and I have paid it every day\l"
	.string "on every beach since.$"

Route7_Text_CornerTama3:
	.string "Tama: PAID?\p"
	.string "You went CAMPING.\p"
	.string "We went to pieces.$"

Route7_Text_TheFalter:
	.string "Tama's hand goes to a Poke Ball.\p"
	.string "The old man doesn't move.\n"
	.string "Doesn't reach for anything.\p"
	.string "The beech forest holds its\n"
	.string "breath.$"

Route7_Text_CornerTawhai3:
	.string "Tawhai: …Finish it, then.\p"
	.string "If it gives you back one single\n"
	.string "day of your family, finish it.\l"
	.string "I won't raise a hand.\p"
	.string "But if it won't - and you've\n"
	.string "known since Wairoa that it\l"
	.string "won't -\p"
	.string "then what is it FOR, Tama?$"

Route7_Text_TheHandShakes:
	.string "Tama's hand shakes on the ball.\p"
	.string "For one breath he is eight\n"
	.string "years old at an orchard gate,\l"
	.string "waving somebody home.\p"
	.string "…He turns away.$"

Route7_Text_CornerTamaExit:
	.string "Tama: …You're not worth the\n"
	.string "throw.\p"
	.string "Stay dead up here, old man.\n"
	.string "That's the mercy.\p"
	.string "There isn't another.$"

Route7_Text_ComeOut:
	.string "Tawhai: …Come out of the trees,\n"
	.string "e hoa.\p"
	.string "He knew you were there. Why do\n"
	.string "you think he needed the exit\l"
	.string "line?$"

Route7_Text_Confession1:
	.string "Tawhai: Sit. I owe your family\n"
	.string "a truth, and you're the one\l"
	.string "strong enough to carry it now.\p"
	.string "I DID try to take your dad.\n"
	.string "That part of Tama's story is\l"
	.string "true.\p"
	.string "Before you were born, I begged\n"
	.string "Kauri to walk out of the Mob\l"
	.string "with me.\p"
	.string "Your mum saw me pulling at him\n"
	.string "and read it as theft.\p"
	.string "…Maybe it was.$"

Route7_Text_Confession2:
	.string "Tawhai: He stayed. I left alone.\p"
	.string "And your father - who counts\n"
	.string "everyone who leaves as a wound -\p"
	.string "lost his best mate. And then,\n"
	.string "slowly, an inch a year, his\l"
	.string "wife.$"

Route7_Text_Confession3:
	.string "Tawhai: Nobody broke your\n"
	.string "family, e hoa.\p"
	.string "Everybody bent it. An inch at\n"
	.string "a time. Me included.\p"
	.string "Your brother needed one villain,\n"
	.string "because a boy can fight a\l"
	.string "villain.\p"
	.string "A boy can't fight an inch.$"

Route7_Text_Confession4:
	.string "Tawhai: What Tama just learned,\n"
	.string "up here between the beeches,\p"
	.string "is that finishing me wouldn't\n"
	.string "have given him back a single\l"
	.string "day.\p"
	.string "Watch what that knowledge does\n"
	.string "to him. It will get worse\l"
	.string "before it gets better.\p"
	.string "It got worse in me first.$"

Route7_Text_Absolution:
	.string "You tell him what somebody once\n"
	.string "told you on a long road:\p"
	.string "getting out isn't betrayal.\p"
	.string "Getting out is surviving.$"

Route7_Text_TawhaiThanks:
	.string "Tawhai: …Ha.\p"
	.string "Your whole family keeps arriving\n"
	.string "at wisdom the hard way.\p"
	.string "Thank you, e hoa. Truly.\p"
	.string "Go south. Finish your climb.\n"
	.string "And when you next see a gate -\p"
	.string "think of me. I'll be keeping\n"
	.string "one somewhere.$"

Route7_EventScript_PVince::
	trainerbattle_single TRAINER_R7P_VINCE, Route7_Text_PVinceIntro, Route7_Text_PVinceDefeat
	msgbox Route7_Text_PVincePost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PVinceIntro:
	.string "Vince: I've tramped every track in\nthis region. Fight me.$"

Route7_Text_PVinceDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route7_Text_PVincePost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route7_EventScript_PWade::
	trainerbattle_single TRAINER_R7P_WADE, Route7_Text_PWadeIntro, Route7_Text_PWadeDefeat
	msgbox Route7_Text_PWadePost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PWadeIntro:
	.string "Wade: I've tramped every track in\nthis region. Fight me.$"

Route7_Text_PWadeDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route7_Text_PWadePost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route7_EventScript_PXimena::
	trainerbattle_single TRAINER_R7P_XIMENA, Route7_Text_PXimenaIntro, Route7_Text_PXimenaDefeat
	msgbox Route7_Text_PXimenaPost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PXimenaIntro:
	.string "Ximena: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route7_Text_PXimenaDefeat:
	.string "You earned the view.$"

Route7_Text_PXimenaPost:
	.string "One more ridge. There's always\none more ridge.$"

Route7_EventScript_PYvette::
	trainerbattle_single TRAINER_R7P_YVETTE, Route7_Text_PYvetteIntro, Route7_Text_PYvetteDefeat
	msgbox Route7_Text_PYvettePost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PYvetteIntro:
	.string "Yvette: Sixty years I've watched this\nland. Show me something new.$"

Route7_Text_PYvetteDefeat:
	.string "…That was new.$"

Route7_Text_PYvettePost:
	.string "The land remembers everyone\nwho crosses it.$"

Route7_EventScript_PZach::
	trainerbattle_single TRAINER_R7P_ZACH, Route7_Text_PZachIntro, Route7_Text_PZachDefeat
	msgbox Route7_Text_PZachPost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PZachIntro:
	.string "Zach: I train where the weather's\nworst. Makes us honest.$"

Route7_Text_PZachDefeat:
	.string "Honestly beaten.$"

Route7_Text_PZachPost:
	.string "Strength is showing up in\nthe rain.$"

Route7_EventScript_PAki::
	trainerbattle_single TRAINER_R7P_AKI, Route7_Text_PAkiIntro, Route7_Text_PAkiDefeat
	msgbox Route7_Text_PAkiPost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PAkiIntro:
	.string "Maia: DOC ranger. Checking traps.\nAnd checking trainers.$"

Route7_Text_PAkiDefeat:
	.string "Pest-free AND beaten.$"

Route7_Text_PAkiPost:
	.string "Keep to the track and take\nyour rubbish out, eh.$"

Route7_EventScript_PBex::
	trainerbattle_single TRAINER_R7P_BEX, Route7_Text_PBexIntro, Route7_Text_PBexDefeat
	msgbox Route7_Text_PBexPost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PBexIntro:
	.string "Bex: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route7_Text_PBexDefeat:
	.string "You earned the view.$"

Route7_Text_PBexPost:
	.string "One more ridge. There's always\none more ridge.$"

Route7_EventScript_PCal::
	trainerbattle_single TRAINER_R7P_CAL, Route7_Text_PCalIntro, Route7_Text_PCalDefeat
	msgbox Route7_Text_PCalPost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PCalIntro:
	.string "Cal: I train where the weather's\nworst. Makes us honest.$"

Route7_Text_PCalDefeat:
	.string "Honestly beaten.$"

Route7_Text_PCalPost:
	.string "Strength is showing up in\nthe rain.$"

Route7_EventScript_PDee::
	trainerbattle_single TRAINER_R7P_DEE, Route7_Text_PDeeIntro, Route7_Text_PDeeDefeat
	msgbox Route7_Text_PDeePost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PDeeIntro:
	.string "Dee: My mokopuna says I'm out of\ndate. Let's test that.$"

Route7_Text_PDeeDefeat:
	.string "Tell no one.$"

Route7_Text_PDeePost:
	.string "Old tricks are just good\ntricks that lasted.$"

Route7_EventScript_PEli::
	trainerbattle_single TRAINER_R7P_ELI, Route7_Text_PEliIntro, Route7_Text_PEliDefeat
	msgbox Route7_Text_PEliPost, MSGBOX_AUTOCLOSE
	end

Route7_Text_PEliIntro:
	.string "Eli: I train where the weather's\nworst. Makes us honest.$"

Route7_Text_PEliDefeat:
	.string "Honestly beaten.$"

Route7_Text_PEliPost:
	.string "Strength is showing up in\nthe rain.$"
