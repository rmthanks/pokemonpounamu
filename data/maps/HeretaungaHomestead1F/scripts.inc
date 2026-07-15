HeretaungaHomestead1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HeretaungaHomestead1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, HeretaungaHomestead1F_OnFrame
	.byte 0

HeretaungaHomestead1F_OnFrame:
	map_script_2 VAR_POUNAMU_INTRO_STATE, 0, Homestead_EventScript_Birthday
	map_script_2 VAR_TEMP_2, 1, Homestead_EventScript_Homecoming
	.2byte 0

@ Tama vanishes from home once the Break happens; Awhi appears for the
@ homecoming (post-tower). VAR_TEMP_2 arms the homecoming scene once.
HeretaungaHomestead1F_OnTransition::
	setvar VAR_TEMP_2, 0
	call HeretaungaHomestead1F_OnTransition_Tama
	call HeretaungaHomestead1F_OnTransition_Awhi
	end

HeretaungaHomestead1F_OnTransition_Tama::
	goto_if_set FLAG_UNUSED_0x048, HeretaungaHomestead1F_HideTama
	clearflag FLAG_UNUSED_0x054
	return
HeretaungaHomestead1F_HideTama::
	setflag FLAG_UNUSED_0x054
	return

HeretaungaHomestead1F_OnTransition_Awhi::
	goto_if_unset FLAG_UNUSED_0x907, HeretaungaHomestead1F_HideAwhi
	clearflag FLAG_UNUSED_0x055
	goto_if_set FLAG_UNUSED_0x068, HeretaungaHomestead1F_AwhiDone
	setvar VAR_TEMP_2, 1
	return
HeretaungaHomestead1F_AwhiDone::
	return
HeretaungaHomestead1F_HideAwhi::
	setflag FLAG_UNUSED_0x055
	return

@ ------------------------------------------------------------------
@ The birthday cold-open. A rare gathering: both parents in one room,
@ Tama across it. The gift is a real, wide choice.
@ ------------------------------------------------------------------
Homestead_EventScript_Birthday::
	lockall
	playbgm MUS_ROUTE118, TRUE
	applymovement LOCALID_HOMESTEAD_RATA, Homestead_Movement_RataNotice
	applymovement LOCALID_HOMESTEAD_KAURI, Homestead_Movement_KauriNotice
	waitmovement 0
	msgbox Homestead_Text_RataThereYouAre, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Homestead_Movement_PlayerToTable
	waitmovement 0
	msgbox Homestead_Text_RataHappyBirthday, MSGBOX_DEFAULT
	msgbox Homestead_Text_KauriLookAtYou, MSGBOX_DEFAULT
	msgbox Homestead_Text_RataWePlanned, MSGBOX_DEFAULT
	msgbox Homestead_Text_KauriChoose, MSGBOX_DEFAULT
	goto Homestead_EventScript_ChooseTriad

Homestead_EventScript_ChooseTriad::
	msgbox Homestead_Text_WhichCallsToYou, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_POUNAMU_TRIAD, FALSE
	switch VAR_RESULT
	case 0, Homestead_EventScript_ChooseBush
	case 1, Homestead_EventScript_ChooseEarth
	case 2, Homestead_EventScript_ChooseSea
	msgbox Homestead_Text_KauriTakeYourTime, MSGBOX_DEFAULT
	goto Homestead_EventScript_ChooseTriad

Homestead_EventScript_ChooseBush::
	multichoice 17, 4, MULTI_POUNAMU_BUSH, FALSE
	switch VAR_RESULT
	case 0, Homestead_EventScript_GiveRowlet
	case 1, Homestead_EventScript_GiveTreecko
	case 2, Homestead_EventScript_GiveSprigatito
	case 3, Homestead_EventScript_GiveChespin
	goto Homestead_EventScript_ChooseTriad

Homestead_EventScript_ChooseEarth::
	multichoice 17, 4, MULTI_POUNAMU_EARTH, FALSE
	switch VAR_RESULT
	case 0, Homestead_EventScript_GiveCyndaquil
	case 1, Homestead_EventScript_GiveCharmander
	case 2, Homestead_EventScript_GiveTorchic
	case 3, Homestead_EventScript_GiveLitten
	goto Homestead_EventScript_ChooseTriad

Homestead_EventScript_ChooseSea::
	multichoice 17, 4, MULTI_POUNAMU_SEA, FALSE
	switch VAR_RESULT
	case 0, Homestead_EventScript_GivePiplup
	case 1, Homestead_EventScript_GiveQuaxly
	case 2, Homestead_EventScript_GiveFroakie
	case 3, Homestead_EventScript_GiveOshawott
	goto Homestead_EventScript_ChooseTriad

	.macro pounamu_give species:req
	bufferspeciesname STR_VAR_1, \species
	msgbox Homestead_Text_ThisOneYouAreSure, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Homestead_EventScript_ChooseTriad
	givemon \species, 5
	playfanfare MUS_OBTAIN_ITEM
	message Homestead_Text_ReceivedMon
	waitfanfare
	waitmessage
	goto Homestead_EventScript_AfterGift
	.endm

Homestead_EventScript_GiveRowlet::
	pounamu_give SPECIES_ROWLET
Homestead_EventScript_GiveTreecko::
	pounamu_give SPECIES_TREECKO
Homestead_EventScript_GiveSprigatito::
	pounamu_give SPECIES_SPRIGATITO
Homestead_EventScript_GiveChespin::
	pounamu_give SPECIES_CHESPIN
Homestead_EventScript_GiveCyndaquil::
	pounamu_give SPECIES_CYNDAQUIL
Homestead_EventScript_GiveCharmander::
	pounamu_give SPECIES_CHARMANDER
Homestead_EventScript_GiveTorchic::
	pounamu_give SPECIES_TORCHIC
Homestead_EventScript_GiveLitten::
	pounamu_give SPECIES_LITTEN
Homestead_EventScript_GivePiplup::
	pounamu_give SPECIES_PIPLUP
Homestead_EventScript_GiveQuaxly::
	pounamu_give SPECIES_QUAXLY
Homestead_EventScript_GiveFroakie::
	pounamu_give SPECIES_FROAKIE
Homestead_EventScript_GiveOshawott::
	pounamu_give SPECIES_OSHAWOTT

Homestead_EventScript_AfterGift::
	msgbox Homestead_Text_RataItSuitsYou, MSGBOX_DEFAULT
	@ --- the brother's beat ---
	applymovement LOCALID_HOMESTEAD_TAMA, Homestead_Movement_TamaNotice
	waitmovement 0
	playse SE_PIN
	msgbox Homestead_Text_TamaMustBeNice, MSGBOX_DEFAULT
	msgbox Homestead_Text_RataTama, MSGBOX_DEFAULT
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Homestead_EventScript_ParentsRetortM
	msgbox Homestead_Text_KauriWeHearYouF, MSGBOX_DEFAULT
	goto Homestead_EventScript_TamaSoftens
Homestead_EventScript_ParentsRetortM::
	msgbox Homestead_Text_KauriWeHearYouM, MSGBOX_DEFAULT
Homestead_EventScript_TamaSoftens::
	applymovement LOCALID_HOMESTEAD_TAMA, Homestead_Movement_TamaLookAway
	waitmovement 0
	msgbox Homestead_Text_TamaDotDotDot, MSGBOX_DEFAULT
	msgbox Homestead_Text_TamaGoodOneThough, MSGBOX_DEFAULT
	msgbox Homestead_Text_TamaHalfWave, MSGBOX_DEFAULT
	@ --- Dad's second gift: the field logbook (the Pokedex + DexNav) ---
	msgbox Homestead_Text_KauriLogbook, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message Homestead_Text_ReceivedLogbook
	waitmessage
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	setflag FLAG_UNUSED_0x281
	setflag FLAG_UNUSED_0x282
	msgbox Homestead_Text_KauriLogbook2, MSGBOX_DEFAULT
	@ --- Mum's gift: the pounamu pendant (nan's carving) ---
	msgbox Homestead_Text_RataPendant, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message Homestead_Text_ReceivedPendant
	waitmessage
	waitfanfare
	giveitem ITEM_BLUE_ORB
	msgbox Homestead_Text_RataPendant2, MSGBOX_DEFAULT
	msgbox Homestead_Text_TamaPendantBitter, MSGBOX_DEFAULT
	msgbox Homestead_Text_RataOrchardIsYours, MSGBOX_DEFAULT
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_SYS_B_DASH
	setvar VAR_POUNAMU_INTRO_STATE, 1
	releaseall
	end

Homestead_Movement_PlayerToTable:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

Homestead_Movement_RataNotice:
	emote_exclamation_mark
	delay_16
	face_right
	step_end

Homestead_Movement_KauriNotice:
	emote_exclamation_mark
	delay_16
	face_up
	step_end

Homestead_Movement_TamaNotice:
	emote_exclamation_mark
	delay_16
	face_right
	step_end

Homestead_Movement_TamaLookAway:
	face_up
	delay_16
	delay_16
	face_right
	step_end

@ --- re-talk lines after the scene ---
Homestead_EventScript_Rata::
	msgbox Homestead_Text_RataRetalk, MSGBOX_NPC
	end

Homestead_EventScript_Kauri::
	msgbox Homestead_Text_KauriRetalk, MSGBOX_NPC
	end

Homestead_EventScript_Tama::
	msgbox Homestead_Text_TamaRetalk, MSGBOX_NPC
	end

@ ------------------------- text -------------------------
Homestead_Text_RataThereYouAre:
	.string "Rata: …! There you are,\n"
	.string "sleepyhead!\p"
	.string "Come down, come down…\n"
	.string "everyone's waiting.$"

Homestead_Text_RataHappyBirthday:
	.string "Rata: Happy birthday, sweetheart.\p"
	.string "Look at us, eh? All four of us,\n"
	.string "under one roof.$"

Homestead_Text_KauriLookAtYou:
	.string "Kauri: Ha! Look at you.\p"
	.string "Last time I stood in this kitchen\n"
	.string "you were half the height.\p"
	.string "…It's been a while. I know.$"

Homestead_Text_RataWePlanned:
	.string "Rata: Your father and I have been\n"
	.string "planning this one for a long time.\p"
	.string "Together. For once.$"

Homestead_Text_KauriChoose:
	.string "Kauri: We called in every favour\n"
	.string "we had, kid. Both of us.\p"
	.string "Any Pokémon you want.\n"
	.string "Go on. Choose.$"

Homestead_Text_WhichCallsToYou:
	.string "Which calls to you…\n"
	.string "the bush, the earth, or the sea?$"

Homestead_Text_KauriTakeYourTime:
	.string "Kauri: Take your time.\n"
	.string "A choice like this shapes you.$"

Homestead_Text_ThisOneYouAreSure:
	.string "{STR_VAR_1}?\n"
	.string "You're sure?$"

Homestead_Text_ReceivedMon:
	.string "{PLAYER} received {STR_VAR_1}\n"
	.string "from Mum and Dad!$"

Homestead_Text_RataItSuitsYou:
	.string "Rata: {STR_VAR_1}, eh?\p"
	.string "…Yes. It suits you.$"

Homestead_Text_TamaMustBeNice:
	.string "Tama: Must be nice being the\n"
	.string "favourite one.\p"
	.string "I didn't get these same choices\n"
	.string "when I turned your age.$"

Homestead_Text_RataTama:
	.string "Rata: Tama…$"

Homestead_Text_KauriWeHearYouM:
	.string "Kauri: We hear you, son.\p"
	.string "But today, let's be here for your\n"
	.string "little brother.\p"
	.string "It's been a long time since we've\n"
	.string "all been together as a family.$"

Homestead_Text_KauriWeHearYouF:
	.string "Kauri: We hear you, son.\p"
	.string "But today, let's be here for your\n"
	.string "little sister.\p"
	.string "It's been a long time since we've\n"
	.string "all been together as a family.$"

Homestead_Text_TamaDotDotDot:
	.string "Tama: …$"

Homestead_Text_TamaGoodOneThough:
	.string "Tama nods at the Poke Ball\n"
	.string "in your hands.\p"
	.string "Tama: …Well. I hope you\n"
	.string "appreciate it.\p"
	.string "It's a good Pokémon.\p"
	.string "Not everyone grew up getting\n"
	.string "treated like you.\l"
	.string "That's all I'm saying.$"

Homestead_Text_TamaHalfWave:
	.string "For a second his hand comes up -\n"
	.string "the old wave, the one he'd give\l"
	.string "you from the orchard gate when\l"
	.string "you were small, waving you home\l"
	.string "from the school road.\p"
	.string "Then he catches himself,\n"
	.string "and puts it away.$"

Homestead_Text_KauriLogbook:
	.string "Kauri: …Hold on. One more thing,\n"
	.string "before your mother has you out\l"
	.string "the door.\p"
	.string "Every kid in this Bay gets a\n"
	.string "starter. Not every kid gets\l"
	.string "taught to READ the land.\p"
	.string "This was mine. Ranger-issue,\n"
	.string "before… well. Before.\p"
	.string "It logs every creature you meet.\n"
	.string "Names them. Remembers them.$"

Homestead_Text_KauriLogbook2:
	.string "Kauri: There's a SCOPE built in.\n"
	.string "Flick it on and it'll pick up\l"
	.string "what's hiding in the long grass -\p"
	.string "the shy ones. The ones worth\n"
	.string "finding.\p"
	.string "…Fill it, {PLAYER}. All of it.\p"
	.string "Learn this country better than\n"
	.string "I ever bothered to.$"

Homestead_Text_RataOrchardIsYours:
	.string "Rata: Go on, you two. Some fresh air.\p"
	.string "The orchard's yours today, {PLAYER}.\n"
	.string "Show the little one around.$"

Homestead_Text_RataRetalk:
	.string "Rata: The whole orchard grew from\n"
	.string "one tree, you know.\p"
	.string "Roots first. Always roots first.\p"
	.string "…I'll be out among the rows when\n"
	.string "you're ready for a proper battle.\p"
	.string "Bring that little one of yours.\n"
	.string "I don't go easy. Not even on\l"
	.string "birthdays.$"

Homestead_Text_KauriRetalk:
	.string "Kauri: Don't mind your brother.\p"
	.string "He's… had a harder run of it\n"
	.string "than you know.\p"
	.string "…I should head back to Ahuriri\n"
	.string "before dark. Work won't wait.$"

Homestead_Text_TamaRetalk:
	.string "Tama: What?\p"
	.string "…Look after it. That's all\n"
	.string "I'm saying.$"

@ ==================================================================
@ THE HOMECOMING - the birthday room, answered. Post-tower, before
@ the final climb. Parents reconciled, Tama's chair empty, Awhi at
@ the table. Maui's call arrives while everyone is together.
@ ==================================================================
Homestead_EventScript_Homecoming::
	lockall
	setvar VAR_TEMP_2, 0
	msgbox Homestead_Text_HomecomingRata, MSGBOX_DEFAULT
	msgbox Homestead_Text_HomecomingKauri, MSGBOX_DEFAULT
	msgbox Homestead_Text_HomecomingAwhi1, MSGBOX_DEFAULT
	msgbox Homestead_Text_HomecomingChair, MSGBOX_DEFAULT
	playse SE_PIN
	msgbox Homestead_Text_HomecomingPhone, MSGBOX_DEFAULT
	msgbox Homestead_Text_HomecomingCall, MSGBOX_DEFAULT
	msgbox Homestead_Text_HomecomingAwhi2, MSGBOX_DEFAULT
	msgbox Homestead_Text_HomecomingRata2, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_UNUSED_0x068
	releaseall
	end

Homestead_EventScript_AwhiHome::
	lock
	faceplayer
	msgbox Homestead_Text_AwhiHomeRetalk, MSGBOX_DEFAULT
	release
	end

Homestead_Text_HomecomingRata:
	.string "Rata: …There you are,\n"
	.string "sleepyhead.\p"
	.string "Same words as that morning, eh.\n"
	.string "Same kitchen.\p"
	.string "Different everything.$"

Homestead_Text_HomecomingKauri:
	.string "Kauri: The tower's yours to\n"
	.string "finish, they tell me. The four\l"
	.string "walls are going home. The\l"
	.string "summit's waiting.\p"
	.string "…I'm not president of anything\n"
	.string "anymore.\p"
	.string "Turns out I don't miss it.\n"
	.string "Turns out I was only ever\l"
	.string "guarding the wrong thing.$"

Homestead_Text_HomecomingAwhi1:
	.string "Awhi: They gave me the seedling\n"
	.string "shift AND the good chair.\p"
	.string "Fifteen years I hovered at the\n"
	.string "edge of this family.\p"
	.string "Turns out you just… sit down.\n"
	.string "That's the whole trick.$"

Homestead_Text_HomecomingChair:
	.string "One chair at the table sits\n"
	.string "empty.\p"
	.string "Nobody has moved it.\p"
	.string "Nobody will.$"

Homestead_Text_HomecomingPhone:
	.string "…The phone rings.\p"
	.string "Rata answers - then goes very\n"
	.string "still, and holds it out to\l"
	.string "Awhi with both hands.$"

Homestead_Text_HomecomingCall:
	.string "Awhi: …Yes. Yes, this is her.\p"
	.string "…\p"
	.string "The whanau seat.\p"
	.string "…You're sure? You know where\n"
	.string "I've been. You know WHOSE I-\p"
	.string "…\p"
	.string "…Yeah. Yes.\p"
	.string "I accept.$"

Homestead_Text_HomecomingAwhi2:
	.string "Awhi: The League wants me to\n"
	.string "hold the whanau wall. Me.\p"
	.string "…Marama. When you climb it -\n"
	.string "and you will - I want you\l"
	.string "first.\p"
	.string "My first challenge, your last\n"
	.string "climb. Deal?\p"
	.string "Don't you dare go easy.$"

Homestead_Text_HomecomingRata2:
	.string "Rata: Eat something before you\n"
	.string "go, love.\p"
	.string "Champions still need breakfast.$"

Homestead_Text_AwhiHomeRetalk:
	.string "Awhi: First challenge.\n"
	.string "Your last climb.\p"
	.string "I'll be waiting at the tower.$"

Homestead_Text_ReceivedLogbook:
	.string "{PLAYER} received the\n"
	.string "POKENAV LOGBOOK!$"

Homestead_Text_RataPendant:
	.string "Rata: And one more. From my side.\p"
	.string "In this family, when you come of\n"
	.string "age - when you're about to become\l"
	.string "your own person - you're given\l"
	.string "pounamu.\p"
	.string "My mum carved this one.\n"
	.string "River stone, from up the back\l"
	.string "of beyond.$"

Homestead_Text_ReceivedPendant:
	.string "{PLAYER} received the POUNAMU PENDANT!$"

Homestead_Text_RataPendant2:
	.string "Rata: 'Wear it, and the rivers\n"
	.string "remember you.'\p"
	.string "It's so you don't forget where\n"
	.string "you came from. No matter how\l"
	.string "far you go.\p"
	.string "It carries the mana of your\n"
	.string "family with you.\p"
	.string "…I never worked out the rivers\n"
	.string "part. Maybe you will.$"

Homestead_Text_TamaPendantBitter:
	.string "Tama: Oh. The stone.\n"
	.string "The famous stone.\p"
	.string "I got mine, my year.\n"
	.string "That's ALL I got.\p"
	.string "A rock on a string to remind me\n"
	.string "where I come from.\p"
	.string "As if I could forget.\p"
	.string "…Enjoy the Pokemon, {PLAYER}.$"
