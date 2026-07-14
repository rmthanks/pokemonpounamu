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
