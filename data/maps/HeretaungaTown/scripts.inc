HeretaungaTown_MapScripts::
	.byte 0

@ Threshold 1: the pair, whole, overhead - the only time until the tower.
HeretaungaTown_EventScript_Shadows::
	lockall
	delay 30
	playse SE_FLEE
	msgbox HeretaungaTown_Text_TwoShadows, MSGBOX_DEFAULT
	setvar VAR_POUNAMU_INTRO_STATE, 2
	releaseall
	end

HeretaungaTown_Text_TwoShadows:
	.string "…?\p"
	.string "Two great shadows sweep across\n"
	.string "the orchard, side by side…\p"
	.string "By the time you look up,\n"
	.string "the sky is empty.$"

HeretaungaTown_EventScript_Girl::
	msgbox HeretaungaTown_Text_Girl, MSGBOX_NPC
	end

HeretaungaTown_Text_Girl:
	.string "This orchard is the oldest in\n"
	.string "all of Heretaunga!\p"
	.string "Miss Rata lets me pick apples\n"
	.string "sometimes. If I'm careful.$"

HeretaungaTown_EventScript_Neighbour::
	msgbox HeretaungaTown_Text_Neighbour, MSGBOX_NPC
	end

HeretaungaTown_Text_Neighbour:
	.string "Your dad's in town, eh?\p"
	.string "…Haven't seen him round here\n"
	.string "since the split. Big day.\p"
	.string "He keeps different company in\n"
	.string "Ahuriri these days. You'd know\l"
	.string "better than me.$"

HeretaungaTown_EventScript_Woman::
	msgbox HeretaungaTown_Text_Woman, MSGBOX_NPC
	end

HeretaungaTown_Text_Woman:
	.string "Everyone knows everyone out\n"
	.string "Flaxmere way.\p"
	.string "Half this town worked a season\n"
	.string "in that orchard, me included.$"

HeretaungaTown_EventScript_TeMataBoy::
	msgbox HeretaungaTown_Text_TeMataBoy, MSGBOX_NPC
	end

HeretaungaTown_Text_TeMataBoy:
	.string "See that ridge past the trees?\n"
	.string "That's Te Mata.\p"
	.string "Nan reckons a giant sleeps in\n"
	.string "that hill.\p"
	.string "…I reckon she's having me on.\n"
	.string "Probably.$"

HeretaungaTown_EventScript_OrchardWorker::
	msgbox HeretaungaTown_Text_OrchardWorker, MSGBOX_NPC
	end

HeretaungaTown_Text_OrchardWorker:
	.string "The shelterbelts keep the wind\n"
	.string "off the fruit.\p"
	.string "Combee do the pollinating, and\n"
	.string "the odd Applin sneaks a feed.\p"
	.string "Miss Rata says every guest earns\n"
	.string "their keep somehow.$"

HeretaungaTown_EventScript_TeMataGate::
	msgbox HeretaungaTown_Text_TeMataGate, MSGBOX_NPC
	end

HeretaungaTown_Text_TeMataGate:
	.string "The Te Mata track? Closed, love.\p"
	.string "Slips all along the ridge after\n"
	.string "the storms.\p"
	.string "That hill will still be asleep\n"
	.string "whenever it opens again.$"

HeretaungaTown_EventScript_FlaxKid::
	msgbox HeretaungaTown_Text_FlaxKid, MSGBOX_NPC
	end

HeretaungaTown_Text_FlaxKid:
	.string "We play down at the park pond\n"
	.string "after kura.\p"
	.string "Sometimes something ripples the\n"
	.string "water and it's NOT an eel…$"

HeretaungaTown_EventScript_HavelockLady::
	msgbox HeretaungaTown_Text_HavelockLady, MSGBOX_NPC
	end

HeretaungaTown_Text_HavelockLady:
	.string "Havelock's quieter than the city\n"
	.string "side. We like it that way.\p"
	.string "Lovely view of the ridge from my\n"
	.string "washing line.$"

HeretaungaTown_EventScript_Route2Gate::
	msgbox HeretaungaTown_Text_Route2Gate, MSGBOX_NPC
	end

HeretaungaTown_Text_Route2Gate:
	.string "Road over the Remutakas is out,\n"
	.string "e hoa. Slips everywhere.\p"
	.string "If you're wanting Te Whanganui-\n"
	.string "a-Tara, it's the long way round\l"
	.string "for you. Sorry, mate.$"

@ ------------------------------------------------------------------
@ Rata - Grass gym leader. The orchard IS the gym. Badge 1.
@ ------------------------------------------------------------------
HeretaungaTown_EventScript_Rata::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, HeretaungaTown_EventScript_RataRetalk
	msgbox HeretaungaTown_Text_RataPreBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_RATA, HeretaungaTown_Text_RataDefeat
	msgbox HeretaungaTown_Text_RataBadgeSpeech, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message HeretaungaTown_Text_ReceivedOrchardBadge
	waitfanfare
	waitmessage
	setflag FLAG_BADGE01_GET
	msgbox HeretaungaTown_Text_RataGoNorth, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_RataRetalk::
	msgbox HeretaungaTown_Text_RataOrchardRetalk, MSGBOX_DEFAULT
	release
	end

@ ------------------------------------------------------------------
@ Functional buildings: the i-SITE and the Matariki hall.
@ ------------------------------------------------------------------
HeretaungaTown_EventScript_ISite::
	lockall
	msgbox HeretaungaTown_Text_ISite, MSGBOX_DEFAULT
	goto_if_set FLAG_UNUSED_0x021, HeretaungaTown_EventScript_ISiteDone
	msgbox HeretaungaTown_Text_ISiteFreebies, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	setflag FLAG_UNUSED_0x021
HeretaungaTown_EventScript_ISiteDone::
	releaseall
	end

HeretaungaTown_EventScript_MatarikiHall::
	msgbox HeretaungaTown_Text_MatarikiHall, MSGBOX_SIGN
	end

@ ------------------------- text -------------------------
HeretaungaTown_Text_RataPreBattle:
	.string "Rata: Out here, love, I'm not\n"
	.string "your mum.\p"
	.string "I'm the Heretaunga gym leader.\n"
	.string "The orchard picked me long\l"
	.string "before you were born.\p"
	.string "Show me what you and your little\n"
	.string "one have learned between\l"
	.string "the rows.$"

HeretaungaTown_Text_RataDefeat:
	.string "…Oh.\p"
	.string "Oh, there it is.$"

HeretaungaTown_Text_RataBadgeSpeech:
	.string "Rata: You've grown right past\n"
	.string "the fence line, my love.\p"
	.string "And I never even saw it happen.$"

HeretaungaTown_Text_ReceivedOrchardBadge:
	.string "{PLAYER} received the Orchard Badge\n"
	.string "from Rata!$"

HeretaungaTown_Text_RataGoNorth:
	.string "Rata: The Orchard Badge.\n"
	.string "First of eight.\p"
	.string "Your father keeps the second,\n"
	.string "up in Ahuriri.\p"
	.string "All Deco corners and sea light,\n"
	.string "that town. Route 51 will take\l"
	.string "you straight up.\p"
	.string "Go and surprise him.\p"
	.string "…He'll pretend he knew you were\n"
	.string "coming. He always pretends.$"

HeretaungaTown_Text_RataOrchardRetalk:
	.string "Rata: Tell your father the apples\n"
	.string "came in sweet this year.\p"
	.string "…And that he still owes me\n"
	.string "a fence post.$"

HeretaungaTown_Text_ISite:
	.string "HERETAUNGA i-SITE\n"
	.string "Your gateway to Te Matau-a-Maui!\p"
	.string "The window display is all Te Mata:\p"
	.string "“THE SLEEPING GIANT -\n"
	.string "RIDGE WALKS OPEN NEXT SEASON.”$"

HeretaungaTown_Text_ISiteFreebies:
	.string "A rack of freebies for new\n"
	.string "trainers stands by the door.$"

HeretaungaTown_Text_MatarikiHall:
	.string "MATARIKI WHANAU HALL\p"
	.string "Closed for preparations.\p"
	.string "The whole town books it out for\n"
	.string "the Matariki festival… nothing\l"
	.string "moves in there till the stars do.$"
