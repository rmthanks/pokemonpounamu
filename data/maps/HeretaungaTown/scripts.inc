HeretaungaTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HeretaungaTown_OnTransition
	.byte 0

HeretaungaTown_OnTransition::
	call HeretaungaTown_OnTransition_OrchardHide
	call HeretaungaTown_OnTransition_Awhi
	call HeretaungaTown_OnTransition_Break
	call HeretaungaTown_OnTransition_Parents
	call HeretaungaTown_OnTransition_Pack
	end

HeretaungaTown_OnTransition_Awhi::
	goto_if_set FLAG_UNUSED_0x907, HeretaungaTown_OnTransition_ShowAwhi
	setflag FLAG_UNUSED_0x90A
	return

HeretaungaTown_OnTransition_ShowAwhi::
	clearflag FLAG_UNUSED_0x90A
	return

HeretaungaTown_OnTransition_OrchardHide::
	goto_if_set FLAG_UNUSED_0x029, HeretaungaTown_OnTransition_OrchardKeepHidden
	setflag FLAG_UNUSED_0x027
	setflag FLAG_UNUSED_0x028
	return
HeretaungaTown_OnTransition_OrchardKeepHidden::
	setflag FLAG_UNUSED_0x027
	setflag FLAG_UNUSED_0x028
	return

HeretaungaTown_OnTransition_Break::
	@ The Break now happens inside the Ahuriri gym coup (exile is immediate).
	@ This object is permanently retired; script kept only for label integrity.
	goto HeretaungaTown_OnTransition_HideTama

HeretaungaTown_OnTransition_ShowTama::
	clearflag FLAG_UNUSED_0x049
	return

HeretaungaTown_OnTransition_HideTama::
	setflag FLAG_UNUSED_0x049
	return

HeretaungaTown_OnTransition_Parents::
	goto_if_set FLAG_UNUSED_0x04E, HeretaungaTown_OnTransition_HideParents
	goto_if_set FLAG_UNUSED_0x907, HeretaungaTown_OnTransition_ShowParents
	goto HeretaungaTown_OnTransition_HideParents

HeretaungaTown_OnTransition_ShowParents::
	clearflag FLAG_UNUSED_0x04F
	return

HeretaungaTown_OnTransition_HideParents::
	setflag FLAG_UNUSED_0x04F
	return

@ Threshold 1: the pair, whole, overhead - the only time until the tower.
HeretaungaTown_EventScript_Shadows::
	lockall
	delay 30
	playse SE_FLEE
	msgbox HeretaungaTown_Text_TwoShadows, MSGBOX_DEFAULT
	@ --- the brother stumbles in from the orchard ---
	clearflag FLAG_UNUSED_0x027
	addobject 24
	delay 16
	playse SE_PIN
	turnobject 24, DIR_NORTH
	msgbox HeretaungaTown_Text_OrchardTama1, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_OrchardTama2, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_OrchardWave, MSGBOX_DEFAULT
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_TAMA_ORCHARD, HeretaungaTown_Text_OrchardTamaLost
	clearflag B_FLAG_NO_WHITEOUT
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HeretaungaTown_EventScript_OrchardPlayerWon
	msgbox HeretaungaTown_Text_OrchardTamaGloat, MSGBOX_DEFAULT
	goto HeretaungaTown_EventScript_OrchardMum

HeretaungaTown_EventScript_OrchardPlayerWon::
	msgbox HeretaungaTown_Text_OrchardTamaFluke, MSGBOX_DEFAULT
	goto HeretaungaTown_EventScript_OrchardMum

HeretaungaTown_EventScript_OrchardMum::
	removeobject 24
	setflag FLAG_UNUSED_0x027
	delay 16
	clearflag FLAG_UNUSED_0x028
	addobject 25
	delay 16
	playse SE_PIN
	msgbox HeretaungaTown_Text_OrchardMum1, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_OrchardMum2, MSGBOX_DEFAULT
	special HealPlayerParty
	removeobject 25
	setflag FLAG_UNUSED_0x028
	setflag FLAG_UNUSED_0x029
	setvar VAR_POUNAMU_INTRO_STATE, 2
	releaseall
	end

HeretaungaTown_EventScript_TamaOrchardIdle::
	msgbox HeretaungaTown_Text_OrchardTama1, MSGBOX_NPC
	end

HeretaungaTown_EventScript_MumOrchardIdle::
	msgbox HeretaungaTown_Text_OrchardMum2, MSGBOX_NPC
	end

HeretaungaTown_Text_OrchardTama1:
	.string "Tama: …So there you are.\p"
	.string "Down here showing off your\n"
	.string "birthday present to the bees?$"

HeretaungaTown_Text_OrchardTama2:
	.string "Tama: Let's see it, then.\n"
	.string "The gift Mum and Dad drove\l"
	.string "across the island for.\p"
	.string "The one nobody drove anywhere\n"
	.string "for me.\p"
	.string "Send it out. I want to see how\n"
	.string "much of it is real.$"

HeretaungaTown_Text_OrchardWave:
	.string "You raise your hand - force of\n"
	.string "habit, the old gate-wave.\p"
	.string "He's already reaching for a\n"
	.string "Poke Ball.$"

HeretaungaTown_Text_OrchardTamaLost:
	.string "…$"

HeretaungaTown_Text_OrchardTamaWon:
	.string "Tama: Hm.$"

HeretaungaTown_Text_OrchardTamaGloat:
	.string "Tama: That's it?\p"
	.string "All that fuss, and it goes down\n"
	.string "to a stray dog I caught behind\l"
	.string "the packhouse.\p"
	.string "Keep it if it makes you happy.\n"
	.string "Presents don't make you strong,\l"
	.string "little brother.$"

HeretaungaTown_Text_OrchardTamaFluke:
	.string "Tama: …Lucky. The dog's tired.\p"
	.string "Don't let it go to your head.\n"
	.string "A present is still just a\l"
	.string "present.$"

HeretaungaTown_Text_OrchardMum1:
	.string "Rata: Oi! Tama - leave your\n"
	.string "brother be!\p"
	.string "…And you. Up off the grass,\n"
	.string "love. It's only a scrape.$"

HeretaungaTown_Text_OrchardMum2:
	.string "Rata: Don't you worry about\n"
	.string "your brother. That's an old\l"
	.string "ache in him, not a strong one.\p"
	.string "Here's what you do: take that\n"
	.string "wee one out along the rows, out\l"
	.string "into the wild, and you GROW it.\p"
	.string "Same as any seedling. Roots\n"
	.string "first.\p"
	.string "And when it's ready - when\n"
	.string "YOU'RE ready - you come back to\l"
	.string "the orchard and you battle me\l"
	.string "properly. For the badge.\p"
	.string "I don't go easy, mind. Not even\n"
	.string "for my own.$"


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
	goto_if_unset FLAG_UNUSED_0x04E, HeretaungaTown_EventScript_RataRetalkPlain
	goto_if_set FLAG_UNUSED_0x27E, HeretaungaTown_EventScript_RataRevealDone
	msgbox HeretaungaTown_Text_RevealWalk, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_RevealLayer1, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_RevealLayer1b, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_RevealLayer2, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_RevealLayer3, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_RevealHeld, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_RevealRelief, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x27E
	release
	end

HeretaungaTown_EventScript_RataRevealDone::
	msgbox HeretaungaTown_Text_RevealAfter, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_RataRetalkPlain::
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
	.string "the rows.\p"
	.string "We fight on living ground, love.\nIt feeds everything rooted in it.$"

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

@ ==================================================================
@ THE BREAK - Act 1 climax. The first of the four double battles.
@ ==================================================================
HeretaungaTown_EventScript_TamaBreak::
	lock
	faceplayer
	msgbox HeretaungaTown_Text_BreakTama1, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_BreakRata1, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_BreakTama2, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_BreakRataWithMe, MSGBOX_DEFAULT
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto_if_ne VAR_RESULT, 0, HeretaungaTown_EventScript_BreakBattle
	special LoadPlayerParty
	msgbox HeretaungaTown_Text_BreakRataWithMe, MSGBOX_DEFAULT
	closemessage
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto HeretaungaTown_EventScript_BreakBattle

HeretaungaTown_EventScript_BreakBattle::
	multi_2_vs_1 TRAINER_TAMA_BREAK, HeretaungaTown_Text_BreakTamaWinsBattle, PARTNER_RATA
	special LoadPlayerParty
	special HealPlayerParty
	goto_if_eq VAR_RESULT, 1, HeretaungaTown_EventScript_BreakPlayerWon
	msgbox HeretaungaTown_Text_BreakAfterLoss, MSGBOX_DEFAULT
	goto HeretaungaTown_EventScript_BreakOutcome

HeretaungaTown_EventScript_BreakPlayerWon::
	msgbox HeretaungaTown_Text_BreakAfterWin, MSGBOX_DEFAULT
	goto HeretaungaTown_EventScript_BreakOutcome

HeretaungaTown_EventScript_BreakOutcome::
	msgbox HeretaungaTown_Text_BreakTamaTaunt, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_BreakWave, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_BreakRataSendaway, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x048
	setflag FLAG_UNUSED_0x049
	setvar VAR_POUNAMU_INTRO_STATE, 4
	removeobject 21
	release
	end

HeretaungaTown_Text_BreakTama1:
	.string "Tama: There he is.\p"
	.string "The kid who beat the president.\p"
	.string "He lost to a CHILD, so the\n"
	.string "chair was loose. I tightened\l"
	.string "it. The Bay answers to me now,\l"
	.string "little brother.$"

HeretaungaTown_Text_BreakRata1:
	.string "Rata: Tama. Not here.\n"
	.string "Not like this.$"

HeretaungaTown_Text_BreakTama2:
	.string "Tama: Like WHAT, Mum?\p"
	.string "Like sons picking up what\n"
	.string "fathers drop?\p"
	.string "You taught me gardens. He\n"
	.string "taught me weight.\p"
	.string "Only one lesson stuck.$"

HeretaungaTown_Text_BreakRataWithMe:
	.string "Rata: Marama - with me.\p"
	.string "One time, love, we do this\n"
	.string "together.$"

HeretaungaTown_Text_BreakTamaWinsBattle:
	.string "That's the whole of it, then.$"

HeretaungaTown_Text_BreakAfterLoss:
	.string "It wasn't close.\p"
	.string "It was arithmetic.$"

HeretaungaTown_Text_BreakAfterWin:
	.string "Tama: …Hm.\p"
	.string "Crews. Numbers. Every road out\n"
	.string "of the Bay, mine by morning.\p"
	.string "It changes nothing.$"

HeretaungaTown_Text_BreakTamaTaunt:
	.string "Tama: Run, little brother.\n"
	.string "Run far.\p"
	.string "You could NEVER come back.\p"
	.string "…Remember that I said it\n"
	.string "kindly.$"

HeretaungaTown_Text_BreakWave:
	.string "You raise your hand anyway.\p"
	.string "The old wave. The orchard-gate\n"
	.string "wave.\p"
	.string "Tama looks at it for a long\n"
	.string "moment.\p"
	.string "He turns away.$"

HeretaungaTown_Text_BreakRataSendaway:
	.string "Rata: Go, love. North. Past the\n"
	.string "checkpoints. Don't stop.\p"
	.string "Not because you're weak.\p"
	.string "Because you're the one thing\n"
	.string "I can still save.$"

@ ==================================================================
@ THE PARENTS' DOUBLE BATTLE - post-game gate to Te Mata. "Reunited."
@ ==================================================================
HeretaungaTown_EventScript_ParentsGate::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x04E, HeretaungaTown_EventScript_ParentsDone
	msgbox HeretaungaTown_Text_ParentsIntro, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_ParentsReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_EventScript_ParentsNotYet
	trainerbattle_two_trainers TRAINER_RATA_POSTGAME, HeretaungaTown_Text_ParentsRataLose, TRAINER_KAURI_POSTGAME, HeretaungaTown_Text_ParentsKauriLose
	msgbox HeretaungaTown_Text_ParentsAfter, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x04E
	release
	end

HeretaungaTown_EventScript_ParentsNotYet::
	msgbox HeretaungaTown_Text_ParentsNotYet, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_ParentsDone::
	msgbox HeretaungaTown_Text_ParentsDoneMsg, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Text_ParentsIntro:
	.string "Rata: Love. We've been waiting.\n"
	.string "Both of us.\p"
	.string "Kauri: The mountain's awake up\n"
	.string "there. Before you climb it…\p"
	.string "…your mother and I have one\n"
	.string "thing left to teach you.\p"
	.string "Rata: Together, this time.\p"
	.string "First time for everything, eh.$"

HeretaungaTown_Text_ParentsReady:
	.string "Face them both at once?$"

HeretaungaTown_Text_ParentsNotYet:
	.string "Rata: We'll be here, love.\p"
	.string "We're not going anywhere.\n"
	.string "Either of us. Not this time.$"

HeretaungaTown_Text_ParentsRataLose:
	.string "There it is.\p"
	.string "The whole apple.$"

HeretaungaTown_Text_ParentsKauriLose:
	.string "…Sweet and sour and standing.\p"
	.string "That's my kid.$"

HeretaungaTown_Text_ParentsAfter:
	.string "Kauri: …We couldn't stay\n"
	.string "standing together, your mother\l"
	.string "and I. Not once. Not ever.\p"
	.string "Today we did.\p"
	.string "You did that.\p"
	.string "Rata: Go on up, love.\p"
	.string "Wave to the giant for me.$"

HeretaungaTown_Text_ParentsDoneMsg:
	.string "Rata: The track's yours, love.\p"
	.string "Kauri: Tell the giant we said\n"
	.string "good morning.$"

@ ---------------------------------------------------------------
@ Job 06: Shadows at the Gate - the pond pack (VAR_POUNAMU_PACK_STATE)
@ 0 none / 1 hunting / 2 leader out / 3 leader beaten / 4 done
@ pups: FLAG_UNUSED_0x02A/057/058, temp vis: FLAG_TEMP_2/3/4, leader FLAG_TEMP_5
@ localids: kid 26, pups 27/28/29, leader 30
@ ---------------------------------------------------------------
HeretaungaTown_OnTransition_Pack::
	goto_if_eq VAR_POUNAMU_PACK_STATE, 1, HeretaungaTown_Pack_TransHunting
	goto_if_eq VAR_POUNAMU_PACK_STATE, 2, HeretaungaTown_Pack_TransLeader
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	return

HeretaungaTown_Pack_TransHunting::
	setflag FLAG_TEMP_5
	call_if_set FLAG_UNUSED_0x02A, HeretaungaTown_Pack_HideP1
	call_if_set FLAG_UNUSED_0x02B, HeretaungaTown_Pack_HideP2
	call_if_set FLAG_UNUSED_0x02C, HeretaungaTown_Pack_HideP3
	return

HeretaungaTown_Pack_HideP1::
	setflag FLAG_TEMP_2
	return
HeretaungaTown_Pack_HideP2::
	setflag FLAG_TEMP_3
	return
HeretaungaTown_Pack_HideP3::
	setflag FLAG_TEMP_4
	return

HeretaungaTown_Pack_TransLeader::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	return

HeretaungaTown_EventScript_PondKid::
	lock
	faceplayer
	goto_if_eq VAR_POUNAMU_PACK_STATE, 1, HeretaungaTown_Pack_KidHunting
	goto_if_eq VAR_POUNAMU_PACK_STATE, 2, HeretaungaTown_Pack_KidLeader
	goto_if_eq VAR_POUNAMU_PACK_STATE, 3, HeretaungaTown_Pack_KidReward
	goto_if_eq VAR_POUNAMU_PACK_STATE, 4, HeretaungaTown_Pack_KidDone
	msgbox HeretaungaTown_Text_PondKidOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_Pack_KidNo
	msgbox HeretaungaTown_Text_PondKidAccept, MSGBOX_DEFAULT
	setvar VAR_POUNAMU_PACK_STATE, 1
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_4
	addobject 27
	addobject 28
	addobject 29
	release
	end

HeretaungaTown_Pack_KidNo::
	msgbox HeretaungaTown_Text_PondKidNo, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Pack_KidHunting::
	msgbox HeretaungaTown_Text_PondKidHunting, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Pack_KidLeader::
	msgbox HeretaungaTown_Text_PondKidLeader, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Pack_KidReward::
	msgbox HeretaungaTown_Text_PondKidThanks, MSGBOX_DEFAULT
	giveitem ITEM_SOOTHE_BELL
	setvar VAR_POUNAMU_PACK_STATE, 4
	msgbox HeretaungaTown_Text_PondKidThanks2, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Pack_KidDone::
	msgbox HeretaungaTown_Text_PondKidAfter, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_PackPup1::
	lock
	faceplayer
	playmoncry SPECIES_POOCHYENA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox HeretaungaTown_Text_PupGrowl, MSGBOX_DEFAULT
	setwildbattle SPECIES_POOCHYENA, 7
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, HeretaungaTown_Pack_PupStays
	setflag FLAG_UNUSED_0x02A
	removeobject 27
	goto HeretaungaTown_Pack_AfterPup

HeretaungaTown_EventScript_PackPup2::
	lock
	faceplayer
	playmoncry SPECIES_POOCHYENA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox HeretaungaTown_Text_PupGrowl, MSGBOX_DEFAULT
	setwildbattle SPECIES_POOCHYENA, 7
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, HeretaungaTown_Pack_PupStays
	setflag FLAG_UNUSED_0x02B
	removeobject 28
	goto HeretaungaTown_Pack_AfterPup

HeretaungaTown_EventScript_PackPup3::
	lock
	faceplayer
	playmoncry SPECIES_POOCHYENA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox HeretaungaTown_Text_PupGrowl, MSGBOX_DEFAULT
	setwildbattle SPECIES_POOCHYENA, 7
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, HeretaungaTown_Pack_PupStays
	setflag FLAG_UNUSED_0x02C
	removeobject 29
	goto HeretaungaTown_Pack_AfterPup

HeretaungaTown_Pack_PupStays::
	msgbox HeretaungaTown_Text_PupFlees, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Pack_AfterPup::
	goto_if_unset FLAG_UNUSED_0x02A, HeretaungaTown_Pack_PupsLeft
	goto_if_unset FLAG_UNUSED_0x02B, HeretaungaTown_Pack_PupsLeft
	goto_if_unset FLAG_UNUSED_0x02C, HeretaungaTown_Pack_PupsLeft
	delay 30
	playmoncry SPECIES_MIGHTYENA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox HeretaungaTown_Text_LeaderComes, MSGBOX_DEFAULT
	setvar VAR_POUNAMU_PACK_STATE, 2
	clearflag FLAG_TEMP_5
	addobject 30
	release
	end

HeretaungaTown_Pack_PupsLeft::
	msgbox HeretaungaTown_Text_PupBeaten, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_PackLeader::
	lock
	faceplayer
	playmoncry SPECIES_MIGHTYENA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox HeretaungaTown_Text_LeaderStands, MSGBOX_DEFAULT
	setwildbattle SPECIES_MIGHTYENA, 11
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, HeretaungaTown_Pack_LeaderStays
	setvar VAR_POUNAMU_PACK_STATE, 3
	removeobject 30
	msgbox HeretaungaTown_Text_LeaderBeaten, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Pack_LeaderStays::
	msgbox HeretaungaTown_Text_LeaderStays, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Text_PondKidOffer:
	.string "You know how the pond ripples\n"
	.string "and everyone says it's eels?\p"
	.string "It's not eels. It's PUPS.\p"
	.string "A whole pack of Poochyena snuck\n"
	.string "in and they nicked my togs bag!\p"
	.string "Three of them, hiding round the\n"
	.string "banks. And one BIG one.\p"
	.string "Can you chase them off?$"

HeretaungaTown_Text_PondKidAccept:
	.string "Ka pai! Check the banks and the\n"
	.string "flowers. And watch the water!$"

HeretaungaTown_Text_PondKidNo:
	.string "…I'm not going home without\n"
	.string "my togs bag.$"

HeretaungaTown_Text_PondKidHunting:
	.string "Three pups! Round the banks and\n"
	.string "in the flowers. Go get 'em!$"

HeretaungaTown_Text_PondKidLeader:
	.string "Did you HEAR that growl?\p"
	.string "That's the big one! It's down by\n"
	.string "the south bank!$"

HeretaungaTown_Text_PondKidThanks:
	.string "You did it! The pond's ours\n"
	.string "again!\p"
	.string "And look - my togs bag! It was\n"
	.string "under the flax the whole time.\p"
	.string "Here. Nan says it makes Pokemon\n"
	.string "trust you. I want you to have it.$"

HeretaungaTown_Text_PondKidThanks2:
	.string "Nan also says the big one was\n"
	.string "probably just hungry.\p"
	.string "…Nan feels sorry for EVERYTHING.$"

HeretaungaTown_Text_PondKidAfter:
	.string "We're back swimming after kura.\n"
	.string "Come sometime! The water's mint.$"

HeretaungaTown_Text_PupGrowl:
	.string "Grrr! The pup bares its\n"
	.string "little teeth!$"

HeretaungaTown_Text_PupFlees:
	.string "The pup yips and dives back\n"
	.string "into the flax!$"

HeretaungaTown_Text_PupBeaten:
	.string "The pup tumbles, shakes itself,\n"
	.string "and scarpers out the gate!$"

HeretaungaTown_Text_LeaderComes:
	.string "A long, low growl rolls\n"
	.string "across the water…\p"
	.string "Something big steps out of the\n"
	.string "flax on the south bank.$"

HeretaungaTown_Text_LeaderStands:
	.string "The big one plants its feet.\n"
	.string "It is NOT scarpering!$"

HeretaungaTown_Text_LeaderBeaten:
	.string "The big one shakes itself off,\n"
	.string "gives you a long look…\p"
	.string "…and lopes away south, out of\n"
	.string "town.\p"
	.string "The pond is quiet again.$"

@ ---------------------------------------------------------------
@ Job 15: Kids of the Pond - Hemi won't walk home after dark
@ evening/night only (gettimeofday: 2 evening, 3 night). done: FLAG_UNUSED_0x02F
@ localid 31, temp vis FLAG_TEMP_6
@ ---------------------------------------------------------------
HeretaungaTown_OnTransition_PondFriend::
	setflag FLAG_TEMP_6
	goto_if_set FLAG_UNUSED_0x02F, HeretaungaTown_PondFriend_TransEnd
	gettimeofday
	goto_if_eq VAR_0x8000, 2, HeretaungaTown_PondFriend_Show
	goto_if_eq VAR_0x8000, 3, HeretaungaTown_PondFriend_Show
	return
HeretaungaTown_PondFriend_Show::
	clearflag FLAG_TEMP_6
HeretaungaTown_PondFriend_TransEnd::
	return

HeretaungaTown_EventScript_PondFriend::
	lock
	faceplayer
	msgbox HeretaungaTown_Text_HemiScared, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	delay 40
	msgbox HeretaungaTown_Text_HemiWatch, MSGBOX_DEFAULT
	msgbox HeretaungaTown_Text_HemiThanks, MSGBOX_DEFAULT
	giveitem ITEM_BIG_MUSHROOM, 2
	setflag FLAG_UNUSED_0x02F
	closemessage
	playse SE_EXIT
	removeobject 31
	msgbox HeretaungaTown_Text_HemiRuns, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Text_HemiScared:
	.string "Hemi: I stayed too long skimming\n"
	.string "stones and now it's getting dark…\p"
	.string "Mata reckons the pond eel comes\n"
	.string "out at night. The one that's not\l"
	.string "an eel! It's THIS long!\p"
	.string "W-will you stand by the water\n"
	.string "while I leg it for the gate?$"

HeretaungaTown_Text_HemiWatch:
	.string "You plant yourself between Hemi\n"
	.string "and the dark water.\p"
	.string "…Nothing so much as ripples.$"

HeretaungaTown_Text_HemiThanks:
	.string "Hemi: KA PAI! You're staunch as!\p"
	.string "Here - Mum packs me these for\n"
	.string "the walk home. You have them!$"

HeretaungaTown_Text_HemiRuns:
	.string "Hemi legs it for the gate without\n"
	.string "looking back once.$"

HeretaungaTown_Text_LeaderStays:
	.string "It circles back to the bank,\n"
	.string "hackles up.$"

@ ------------------------------------------------------------------
@ Hori, the Mob's least effective grunt. He wants your shoes.
@ ------------------------------------------------------------------
HeretaungaTown_EventScript_Hori::
	lock
	faceplayer
	trainerbattle_single TRAINER_HORI_1, HeretaungaTown_Text_HoriIntro, HeretaungaTown_Text_HoriDefeat, HeretaungaTown_EventScript_HoriBeaten
	release
	end

HeretaungaTown_EventScript_HoriBeaten::
	msgbox HeretaungaTown_Text_HoriAfter, MSGBOX_DEFAULT
	closemessage
	playse SE_FLEE
	removeobject 32
	setflag FLAG_UNUSED_0x273
	release
	end

HeretaungaTown_Text_HoriIntro:
	.string "Oi! You. Yeah, you.\p"
	.string "One on one for your shoes.$"

HeretaungaTown_Text_HoriDefeat:
	.string "Aw NAH!$"

HeretaungaTown_Text_HoriAfter:
	.string "Keep 'em. They'd pinch me toes\n"
	.string "anyway.\p"
	.string "You got lucky, eh. The Mob's got\n"
	.string "HEAPS of shoes… wait.\p"
	.string "Forget I said that.$"

@ ==================================================================
@ MUM'S REVEAL (staged reveal part 2) - post-game, after the parents'
@ double battle. Three layers. The landing of the whole story.
@ done: FLAG_UNUSED_0x27E
@ ==================================================================
HeretaungaTown_Text_RevealWalk:
	.string "Rata: Walk with me a minute,\n"
	.string "love. The sour rows.\p"
	.string "I think best where it's sour.$"

HeretaungaTown_Text_RevealLayer1:
	.string "Rata: You'll have heard pieces\n"
	.string "by now. From Tawhai. From Awhi.\l"
	.string "From your own eyes.\p"
	.string "Here's my piece. It's the\n"
	.string "hardest one, so I'll say it\l"
	.string "plain.\p"
	.string "I have two kinds of apple in\n"
	.string "me, same as the trees.\p"
	.string "And I fed them to the wrong\n"
	.string "people.$"

HeretaungaTown_Text_RevealLayer1b:
	.string "Rata: Your dad, when he was\n"
	.string "drowning - I gave him sour.\p"
	.string "Every time that man reached for\n"
	.string "me, I made him pay for the last\l"
	.string "time first.\p"
	.string "And Tama - my Tama - I gave him\n"
	.string "sweet and only sweet. Never\l"
	.string "once told that boy no.\p"
	.string "Your father gave him armour.\n"
	.string "I gave him appetite.\p"
	.string "We built your brother together,\n"
	.string "love. Between the two of us,\l"
	.string "we built him.$"

HeretaungaTown_Text_RevealLayer2:
	.string "Rata: So when you think of your\n"
	.string "brother - and you will, your\l"
	.string "whole life -\p"
	.string "don't you DARE think “unloved.”\p"
	.string "He was loved past all sense.\n"
	.string "He was loved WRONG.\p"
	.string "There's a world between those.\p"
	.string "Grieve him as a boy everyone\n"
	.string "fed and no one nourished.\p"
	.string "That's the true grief. I'm\n"
	.string "giving it to you because you're\l"
	.string "strong enough to carry the\l"
	.string "true one.$"

HeretaungaTown_Text_RevealLayer3:
	.string "Rata: …And here's my fear,\n"
	.string "since we're standing in the\l"
	.string "sour rows anyway.\p"
	.string "You've got the same stock in\n"
	.string "you. Same roots. Same weather.\p"
	.string "Everything that went to seed in\n"
	.string "your father and your brother is\l"
	.string "IN you, love.\p"
	.string "I sent you away to save you\n"
	.string "from Tama. That's true.\p"
	.string "But I also sent you away from\n"
	.string "ME.\p"
	.string "Before my love could do to you\n"
	.string "what it did to him.$"

HeretaungaTown_Text_RevealHeld:
	.string "You don't argue.\p"
	.string "You just stand there in the\n"
	.string "sour rows - all of it in you,\l"
	.string "held.\p"
	.string "Roots and reach. Sweet and\n"
	.string "sour.\p"
	.string "Your father's stance. Your\n"
	.string "mother's eyes.\p"
	.string "Whole.$"

HeretaungaTown_Text_RevealRelief:
	.string "Rata looks at you for a long\n"
	.string "time.\p"
	.string "Whatever she was afraid of\n"
	.string "seeing…\p"
	.string "…isn't what she sees.\p"
	.string "Rata: No. Not you, eh.\p"
	.string "You're the whole apple.\p"
	.string "…Go on, love. The kettle's on\n"
	.string "when you're done being\l"
	.string "legendary.$"

HeretaungaTown_Text_RevealAfter:
	.string "Rata: The orchard's coming\n"
	.string "back. Slowly. Same as all of\l"
	.string "us.\p"
	.string "Kettle's on, love.$"

HeretaungaTown_EventScript_PHika::
	trainerbattle_single TRAINER_HTT_HIKA, HeretaungaTown_Text_PHikaIntro, HeretaungaTown_Text_PHikaDefeat
	msgbox HeretaungaTown_Text_PHikaPost, MSGBOX_AUTOCLOSE
	end

HeretaungaTown_Text_PHikaIntro:
	.string "Hui: I've been training out here\nALL morning!$"

HeretaungaTown_Text_PHikaDefeat:
	.string "Okay, MOST of the morning.$"

HeretaungaTown_Text_PHikaPost:
	.string "Don't tell my nan I lost.$"

HeretaungaTown_EventScript_PManaia::
	trainerbattle_single TRAINER_HTT_MANAIA, HeretaungaTown_Text_PManaiaIntro, HeretaungaTown_Text_PManaiaDefeat
	msgbox HeretaungaTown_Text_PManaiaPost, MSGBOX_AUTOCLOSE
	end

HeretaungaTown_Text_PManaiaIntro:
	.string "Manaia: Oi! You walked into my line\nof sight. Them's the rules!$"

HeretaungaTown_Text_PManaiaDefeat:
	.string "Aw, heck!$"

HeretaungaTown_Text_PManaiaPost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"

HeretaungaTown_EventScript_PNgaire::
	trainerbattle_single TRAINER_HTT_NGAIRE, HeretaungaTown_Text_PNgaireIntro, HeretaungaTown_Text_PNgaireDefeat
	msgbox HeretaungaTown_Text_PNgairePost, MSGBOX_AUTOCLOSE
	end

HeretaungaTown_Text_PNgaireIntro:
	.string "Ngaire: Oi! You walked into my line\nof sight. Them's the rules!$"

HeretaungaTown_Text_PNgaireDefeat:
	.string "Aw, heck!$"

HeretaungaTown_Text_PNgairePost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"

HeretaungaTown_EventScript_PZara::
	trainerbattle_single TRAINER_GYM1_ZARA, HeretaungaTown_Text_PZaraIntro, HeretaungaTown_Text_PZaraDefeat
	msgbox HeretaungaTown_Text_PZaraPost, MSGBOX_AUTOCLOSE
	end

HeretaungaTown_Text_PZaraIntro:
	.string "Zara: Between milkings. You've got\nten minutes. Go.$"

HeretaungaTown_Text_PZaraDefeat:
	.string "Back to the shed, then.$"

HeretaungaTown_Text_PZaraPost:
	.string "Rain's coming. Good for the\ngrass, good for nothing else.$"

HeretaungaTown_EventScript_PAda::
	trainerbattle_single TRAINER_GYM1_ADA, HeretaungaTown_Text_PAdaIntro, HeretaungaTown_Text_PAdaDefeat
	msgbox HeretaungaTown_Text_PAdaPost, MSGBOX_AUTOCLOSE
	end

HeretaungaTown_Text_PAdaIntro:
	.string "Ada: Bet you can't beat me.\nDouble or nothing on my lunch!$"

HeretaungaTown_Text_PAdaDefeat:
	.string "You can have the sammie.$"

HeretaungaTown_Text_PAdaPost:
	.string "Worth it. Rematch at smoko?$"

HeretaungaTown_EventScript_StallAunty::
	lock
	faceplayer
	msgbox HeretaungaTown_Text_StallAunty, MSGBOX_DEFAULT
	pokemart HeretaungaTown_OrchardStallMart
	msgbox HeretaungaTown_Text_StallAuntyBye, MSGBOX_DEFAULT
	release
	end

	.align 2
HeretaungaTown_OrchardStallMart:
	.2byte ITEM_POMEG_BERRY
	.2byte ITEM_KELPSY_BERRY
	.2byte ITEM_QUALOT_BERRY
	.2byte ITEM_HONDEW_BERRY
	.2byte ITEM_GREPA_BERRY
	.2byte ITEM_TAMATO_BERRY
	.2byte ITEM_HP_UP
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CALCIUM
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_POWER_WEIGHT
	.2byte ITEM_POWER_BRACER
	.2byte ITEM_POWER_BELT
	.2byte ITEM_POWER_LENS
	.2byte ITEM_POWER_BAND
	.2byte ITEM_POWER_ANKLET
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_ABILITY_PATCH
	.2byte ITEM_BOTTLE_CAP
	.2byte ITEM_GOLD_BOTTLE_CAP
	.2byte ITEM_EXP_CANDY_M
	.2byte ITEM_EXP_CANDY_L
	.2byte ITEM_RARE_CANDY
	pokemartlistend

HeretaungaTown_EventScript_TrainingKoro::
	lock
	faceplayer
	checkitem ITEM_GOLD_BOTTLE_CAP
	goto_if_eq VAR_RESULT, TRUE, HeretaungaTown_Koro_Gold
	checkitem ITEM_BOTTLE_CAP
	goto_if_eq VAR_RESULT, TRUE, HeretaungaTown_Koro_Silver
	msgbox HeretaungaTown_Text_KoroNoCaps, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Koro_Gold::
	msgbox HeretaungaTown_Text_KoroGoldAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_Koro_Silver
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, HeretaungaTown_Koro_Cancel
	setvar VAR_0x8005, 1
	special HyperTrainChosenMon
	goto_if_eq VAR_RESULT, FALSE, HeretaungaTown_Koro_Already
	removeitem ITEM_GOLD_BOTTLE_CAP
	msgbox HeretaungaTown_Text_KoroDoneAll, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Koro_Silver::
	checkitem ITEM_BOTTLE_CAP
	goto_if_eq VAR_RESULT, FALSE, HeretaungaTown_Koro_Cancel
	msgbox HeretaungaTown_Text_KoroSilverAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_Koro_Cancel
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, HeretaungaTown_Koro_Cancel
	setvar VAR_0x8005, 0
	special HyperTrainChosenMon
	goto_if_eq VAR_RESULT, FALSE, HeretaungaTown_Koro_Already
	removeitem ITEM_BOTTLE_CAP
	msgbox HeretaungaTown_Text_KoroDoneOne, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Koro_Already::
	msgbox HeretaungaTown_Text_KoroAlready, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_Koro_Cancel::
	msgbox HeretaungaTown_Text_KoroCancel, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_EventScript_ShareKid::
	lock
	faceplayer
	goto_if_unset FLAG_UNUSED_0x285, HeretaungaTown_ShareKid_Off
	msgbox HeretaungaTown_Text_ShareKidOnAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_ShareKid_Done
	clearflag FLAG_UNUSED_0x285
	msgbox HeretaungaTown_Text_ShareKidTurnedOff, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_ShareKid_Off::
	msgbox HeretaungaTown_Text_ShareKidOffAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HeretaungaTown_ShareKid_Done
	setflag FLAG_UNUSED_0x285
	msgbox HeretaungaTown_Text_ShareKidTurnedOn, MSGBOX_DEFAULT
	release
	end

HeretaungaTown_ShareKid_Done::
	release
	end

HeretaungaTown_Text_StallAunty:
	.string "Aunty Hera: Kia ora, love!\n"
	.string "The orchard stall - berries that\l"
	.string "unlearn bad training, tonics that\l"
	.string "build it right, and a few rare\l"
	.string "treats from the packhouse.$"

HeretaungaTown_Text_StallAuntyBye:
	.string "Aunty Hera: Feed them well and\n"
	.string "they'll grow true. Haere ra!$"

HeretaungaTown_Text_KoroNoCaps:
	.string "Koro Tapeta: See these hands?\n"
	.string "Sixty years polishing pounamu.\p"
	.string "Bring me a BOTTLE CAP and I'll\n"
	.string "polish your Pokemon's weakest\l"
	.string "facet till it shines.\p"
	.string "A GOLD one? The whole taonga.\n"
	.string "All six facets.\p"
	.string "Aunty at the stall keeps a few.$"

HeretaungaTown_Text_KoroGoldAsk:
	.string "Koro Tapeta: A GOLD BOTTLE CAP…\n"
	.string "The full polish, then?\l"
	.string "All six facets, one Pokemon?$"

HeretaungaTown_Text_KoroSilverAsk:
	.string "Koro Tapeta: A BOTTLE CAP.\n"
	.string "I'll find the weakest facet\l"
	.string "and polish just that one.\p"
	.string "Shall I?$"

HeretaungaTown_Text_KoroDoneAll:
	.string "Koro Tapeta: …There.\p"
	.string "Every facet catches the light\n"
	.string "now. A taonga finished.$"

HeretaungaTown_Text_KoroDoneOne:
	.string "Koro Tapeta: …There.\p"
	.string "The dullest facet shines now.\n"
	.string "Bring another cap for the next.$"

HeretaungaTown_Text_KoroAlready:
	.string "Koro Tapeta: This one already\n"
	.string "shines from every angle, e hoa.\p"
	.string "Keep your cap. Nothing left\n"
	.string "for these old hands to do.$"

HeretaungaTown_Text_KoroCancel:
	.string "Koro Tapeta: Another day, then.\n"
	.string "The stone waits. Stones are\l"
	.string "good at that.$"

HeretaungaTown_Text_ShareKidOnAsk:
	.string "Everyone in the whanau shares\n"
	.string "the kai right now - the whole\l"
	.string "team grows from every battle!\p"
	.string "Want them to eat separately\n"
	.string "instead?$"

HeretaungaTown_Text_ShareKidOffAsk:
	.string "Right now only the ones who\n"
	.string "fight get fed - old style!\p"
	.string "Want the whole whanau to share\n"
	.string "the kai again?$"

HeretaungaTown_Text_ShareKidTurnedOff:
	.string "Old style! Only workers eat!\n"
	.string "Nan would approve.$"

HeretaungaTown_Text_ShareKidTurnedOn:
	.string "Whanau style! Everyone eats!\n"
	.string "That's how you grow a team.$"
