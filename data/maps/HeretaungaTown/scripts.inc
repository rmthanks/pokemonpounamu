HeretaungaTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HeretaungaTown_OnTransition
	.byte 0

HeretaungaTown_OnTransition::
	goto_if_set FLAG_UNUSED_0x907, HeretaungaTown_OnTransition_ShowAwhi
	setflag FLAG_UNUSED_0x90A
	end

HeretaungaTown_OnTransition_ShowAwhi::
	clearflag FLAG_UNUSED_0x90A
	end

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
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x025, HeretaungaTown_EventScript_TeMataBoyPostQuake
	msgbox HeretaungaTown_Text_TeMataBoy, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_TeMataBoyPostQuake::
	msgbox HeretaungaTown_Text_TeMataBoyPostQuake, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Text_TeMataBoy:
	.string "See that ridge past the trees?\n"
	.string "That's Te Mata.\p"
	.string "Nan reckons a giant sleeps in\n"
	.string "that hill.\p"
	.string "…I reckon she's having me on.\n"
	.string "Probably.$"

HeretaungaTown_Text_TeMataBoyPostQuake:
	.string "Nan didn't say “I told you so.”\p"
	.string "She just put the kettle on and\n"
	.string "looked out the window at the\l"
	.string "ridge for a really long time.\p"
	.string "…The ridge looks DIFFERENT,\n"
	.string "eh. Like a made bed.$"

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
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x025, HeretaungaTown_EventScript_TeMataGateOpen
	msgbox HeretaungaTown_Text_TeMataGate, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_TeMataGateOpen::
	msgbox HeretaungaTown_Text_TeMataGateOpen, MSGBOX_DEFAULT
	release
	end

@ The waharoa itself. Post-game, stepping east opens the first ascent.
HeretaungaTown_EventScript_TeMataTrackEntry::
	lockall
	goto_if_set FLAG_UNUSED_0x025, HeretaungaTown_EventScript_TeMataTrackGo
	msgbox HeretaungaTown_Text_TeMataTrackClosed, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, HeretaungaTown_Movement_StepBackWest
	waitmovement 0
	releaseall
	end

HeretaungaTown_EventScript_TeMataTrackGo::
	releaseall
	warp MAP_TE_MATA_TRACK, 10, 43
	waitstate
	end

HeretaungaTown_Movement_StepBackWest:
	walk_left
	step_end

HeretaungaTown_Text_TeMataGate:
	.string "The Te Mata track? Closed, love.\p"
	.string "Slips all along the ridge after\n"
	.string "the storms.\p"
	.string "That hill will still be asleep\n"
	.string "whenever it opens again.$"

HeretaungaTown_Text_TeMataGateOpen:
	.string "The quake snapped the chain on\n"
	.string "the waharoa like it was string.\p"
	.string "Rangers went up Tuesday morning.\n"
	.string "Came back down Tuesday morning,\l"
	.string "walking very fast.\p"
	.string "…Track's open, love.\p"
	.string "Nobody said it was SAFE.$"

HeretaungaTown_Text_TeMataTrackClosed:
	.string "The waharoa is chained shut.\p"
	.string "A weathered notice hangs from\n"
	.string "the crossbar:\p"
	.string "“TRACK CLOSED - slips along\n"
	.string "the ridge.\p"
	.string "The hill will still be here\n"
	.string "when you're older.”$"

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
	goto_if_unset FLAG_UNUSED_0x044, HeretaungaTown_EventScript_RataQuietOrchard
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
	setflag FLAG_UNUSED_0x045
	msgbox HeretaungaTown_Text_ISite, MSGBOX_DEFAULT
	goto_if_set FLAG_UNUSED_0x021, HeretaungaTown_EventScript_ISiteDone
	msgbox HeretaungaTown_Text_ISiteFreebies, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	setflag FLAG_UNUSED_0x021
HeretaungaTown_EventScript_ISiteDone::
	releaseall
	end

HeretaungaTown_EventScript_MatarikiHall::
	setflag FLAG_UNUSED_0x046
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

@ ---------------- Act 1 loop: Job 02 - The Pollinator Problem ----------------
HeretaungaTown_EventScript_RataQuietOrchard::
	goto_if_set FLAG_UNUSED_0x042, HeretaungaTown_EventScript_RataQueenStillOut
	msgbox HeretaungaTown_Text_RataQuiet, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x042
	release
	end

HeretaungaTown_EventScript_RataQueenStillOut::
	msgbox HeretaungaTown_Text_RataStillOut, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_Queen::
	lock
	faceplayer
	goto_if_unset FLAG_UNUSED_0x042, HeretaungaTown_EventScript_QueenSulk
	goto_if_set FLAG_UNUSED_0x043, HeretaungaTown_EventScript_QueenReturn
	msgbox HeretaungaTown_Text_QueenNeedsSweet, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_QueenSulk::
	msgbox HeretaungaTown_Text_QueenSulk, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_QueenReturn::
	msgbox HeretaungaTown_Text_QueenSniffs, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_VESPIQUEN, CRY_MODE_ENCOUNTER
	waitmoncry
	closemessage
	setflag FLAG_UNUSED_0x044
	removeobject VAR_LAST_TALKED
	msgbox HeretaungaTown_Text_QueenGone, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	releaseall
	end

@ ---------------- Job 04 - The Neighbour's Cure ----------------
HeretaungaTown_EventScript_Kuia::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x04C, HeretaungaTown_EventScript_KuiaDone
	checkitem ITEM_PECHA_BERRY
	goto_if_eq VAR_RESULT, FALSE, HeretaungaTown_EventScript_KuiaNeeds
	msgbox HeretaungaTown_Text_KuiaAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_EventScript_KuiaNeeds
	removeitem ITEM_PECHA_BERRY
	msgbox HeretaungaTown_Text_KuiaThanks, MSGBOX_DEFAULT
	giveitem ITEM_ORAN_BERRY, 5
	setflag FLAG_UNUSED_0x04C
	release
	end

HeretaungaTown_EventScript_KuiaNeeds::
	msgbox HeretaungaTown_Text_KuiaNeeds, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_KuiaDone::
	msgbox HeretaungaTown_Text_KuiaDone, MSGBOX_DEFAULT
	release
	end

@ ---------------- Job 01 delivery + the Job Board ----------------
HeretaungaTown_EventScript_Watchers::
	lockall
	goto_if_set FLAG_UNUSED_0x040, HeretaungaTown_EventScript_WatchersEnd
	goto_if_unset FLAG_UNUSED_0x041, HeretaungaTown_EventScript_WatchersEnd
	playse SE_PIN
	msgbox HeretaungaTown_Text_WatchersStop, MSGBOX_DEFAULT
	releaseall
	end

HeretaungaTown_EventScript_WatchersEnd::
	releaseall
	end

HeretaungaTown_EventScript_JobBoard::
	lockall
	goto_if_set FLAG_UNUSED_0x040, HeretaungaTown_EventScript_BoardOpen
	goto_if_set FLAG_UNUSED_0x041, HeretaungaTown_EventScript_BoardDeliver
	msgbox HeretaungaTown_Text_BoardLocked, MSGBOX_DEFAULT
	releaseall
	end

HeretaungaTown_EventScript_BoardDeliver::
	msgbox HeretaungaTown_Text_BoardDeliver, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x040
	giveitem ITEM_POKE_BALL, 5
	msgbox HeretaungaTown_Text_BoardUnlocked, MSGBOX_DEFAULT
	releaseall
	end

HeretaungaTown_EventScript_BoardOpen::
	goto_if_set FLAG_UNUSED_0x04B, HeretaungaTown_EventScript_BoardJobs
	goto_if_unset FLAG_UNUSED_0x045, HeretaungaTown_EventScript_BoardJobs
	goto_if_unset FLAG_UNUSED_0x046, HeretaungaTown_EventScript_BoardJobs
	goto_if_unset FLAG_UNUSED_0x047, HeretaungaTown_EventScript_BoardJobs
	msgbox HeretaungaTown_Text_LiteracyDone, MSGBOX_DEFAULT
	giveitem ITEM_REPEL, 3
	setflag FLAG_UNUSED_0x04B
	releaseall
	end

HeretaungaTown_EventScript_BoardJobs::
	msgbox HeretaungaTown_Text_BoardJobs, MSGBOX_DEFAULT
	goto_if_set FLAG_UNUSED_0x04D, HeretaungaTown_EventScript_BoardJobsEnd
	msgbox HeretaungaTown_Text_ManuLog, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x04D
HeretaungaTown_EventScript_BoardJobsEnd::
	releaseall
	end

@ ---------------- text ----------------
HeretaungaTown_Text_RataQuiet:
	.string "Rata: Not yet, love.\p"
	.string "Listen. No hum. The Combee\n"
	.string "haven't worked since the\l"
	.string "spraying trucks came through.\p"
	.string "Their queen took it personally.\n"
	.string "Sulking somewhere behind the\l"
	.string "homestead, I'd say.\p"
	.string "No queen, no orchard. No\n"
	.string "orchard, no gym battle.$"

HeretaungaTown_Text_RataStillOut:
	.string "Rata: Found her yet?\p"
	.string "Stubborn old thing. Something\n"
	.string "sweet from my shop might turn\l"
	.string "her head.$"

HeretaungaTown_Text_QueenSulk:
	.string "A great VESPIQUEN sits with her\n"
	.string "back to the orchard.\p"
	.string "Every line of her says NOT\n"
	.string "TALKING TO ANYONE.$"

HeretaungaTown_Text_QueenNeedsSweet:
	.string "The VESPIQUEN turns one royal\n"
	.string "eye toward you, then away.\p"
	.string "…She won't be argued back.\n"
	.string "Something sweet, maybe.$"

HeretaungaTown_Text_QueenSniffs:
	.string "You hold out Mum's sweet\n"
	.string "nectar.\p"
	.string "The VESPIQUEN goes very still…$"

HeretaungaTown_Text_QueenGone:
	.string "She rises like a slow decision\n"
	.string "and sails back over the\l"
	.string "shelterbelt toward the orchard.\p"
	.string "Somewhere behind you, a\n"
	.string "thousand wings start humming.$"

HeretaungaTown_Text_KuiaNeeds:
	.string "Kuia: My old Wooloo's eaten\n"
	.string "something wicked off the road.\p"
	.string "A PECHA BERRY would set her\n"
	.string "right. If you find one, love…$"

HeretaungaTown_Text_KuiaAsk:
	.string "Kuia: Is that a PECHA BERRY\n"
	.string "you've got there?\p"
	.string "May she have it?$"

HeretaungaTown_Text_KuiaThanks:
	.string "The Wooloo takes the berry,\n"
	.string "shudders once, and immediately\l"
	.string "falls asleep on your foot.\p"
	.string "Kuia: That's her thank-you.\n"
	.string "Here - from the garden.$"

HeretaungaTown_Text_KuiaDone:
	.string "Kuia: She's grazing again.\p"
	.string "You're your mother's, alright.\n"
	.string "All of the heart, none of the\l"
	.string "nonsense.$"

HeretaungaTown_Text_WatchersStop:
	.string "Two men you don't know step\n"
	.string "into your path.\p"
	.string "“Crate inspection. Bay rules.”\p"
	.string "They lift the lid, look at\n"
	.string "apples for a long moment, and\l"
	.string "put it back.\p"
	.string "“…Rata's kid, eh. He'll want\n"
	.string "to know you're grown.”\p"
	.string "They step aside. They don't\n"
	.string "stop watching.$"

HeretaungaTown_Text_BoardLocked:
	.string "HERETAUNGA i-SITE - JOB BOARD\p"
	.string "Mostly pinned-up flyers for\n"
	.string "fruit picking.\p"
	.string "The clerk inside mouths:\n"
	.string "“ask your mum.”$"

HeretaungaTown_Text_BoardDeliver:
	.string "You hand the crate through the\n"
	.string "i-SITE window.\p"
	.string "Clerk: From the flower shop?\n"
	.string "Then you're the new courier!\p"
	.string "Your mum signed you up for the\n"
	.string "JOB BOARD this morning.\p"
	.string "“The Bay looks after its own,”\n"
	.string "she wrote. “So does my kid.”$"

HeretaungaTown_Text_BoardUnlocked:
	.string "The JOB BOARD is now open!\p"
	.string "Jobs are posted at i-SITEs in\n"
	.string "every town across the motu.\p"
	.string "Finish jobs, and word of you\n"
	.string "travels ahead of you.$"

HeretaungaTown_Text_BoardJobs:
	.string "HERETAUNGA JOB BOARD\p"
	.string "- READING THE BAY: know your\n"
	.string "town. Read its signs and\l"
	.string "plaques. (3)\p"
	.string "- THE NEIGHBOUR'S CURE: kuia\n"
	.string "on the north road needs a\l"
	.string "PECHA BERRY.\p"
	.string "- THE POLLINATOR PROBLEM: ask\n"
	.string "at the orchard.$"

HeretaungaTown_Text_LiteracyDone:
	.string "Clerk: All three plaques?\n"
	.string "Most locals never read ONE.\p"
	.string "Here - courier's rations.$"

HeretaungaTown_Text_ManuLog:
	.string "A ranger's flyer is pinned to\n"
	.string "the corner:\p"
	.string "“MANU SIGHTINGS LOG - record\n"
	.string "the native birds of the motu.\l"
	.string "Every reserve, every coast.\p"
	.string "Start looking UP, e hoa.”\p"
	.string "(The MANU LOG has begun.)$"

@ ------------------------------------------------------------------
@ Awhi, home at last, by the flower shop. The Red-style pointer.
@ ------------------------------------------------------------------
HeretaungaTown_EventScript_AwhiPostgame::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x90B, HeretaungaTown_EventScript_AwhiRepeat
	msgbox HeretaungaTown_Text_AwhiPointer, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x90B
	release
	end

HeretaungaTown_EventScript_AwhiRepeat::
	msgbox HeretaungaTown_Text_AwhiRepeat, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Text_AwhiPointer:
	.string "Awhi: Marama. Look at you.\p"
	.string "Your mum's got me on the\n"
	.string "seedling shift. Turns out I'm\l"
	.string "good at growing things.\l"
	.string "Who knew.\p"
	.string "…Tama? …\p"
	.string "Haven't seen him in a long\n"
	.string "time. He doesn't call.\l"
	.string "He doesn't want to be called.\p"
	.string "Last I heard - round the\n"
	.string "mountains. The big ones,\l"
	.string "middle of the island.\p"
	.string "If you find him, don't try to\n"
	.string "fix him. Just stand there.\p"
	.string "That's the thing he never had.$"

HeretaungaTown_Text_AwhiRepeat:
	.string "Awhi: Round the mountains.\n"
	.string "That's all I know, love.\p"
	.string "Old Tawhai used to keep that\n"
	.string "road, up past Taupo. Ask him.$"
