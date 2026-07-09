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
