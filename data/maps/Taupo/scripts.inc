Taupo_MapScripts::
	.byte 0

Taupo_EventScript_LakeMan::
	msgbox Taupo_Text_LakeMan, MSGBOX_NPC
	end

Taupo_EventScript_StreetWoman::
	msgbox Taupo_Text_StreetWoman, MSGBOX_NPC
	end

Taupo_EventScript_GateOldMan::
	msgbox Taupo_Text_GateOldMan, MSGBOX_NPC
	end

Taupo_EventScript_Kid::
	msgbox Taupo_Text_Kid, MSGBOX_NPC
	end

Taupo_EventScript_LakeSign::
	msgbox Taupo_Text_LakeSign, MSGBOX_SIGN
	end

Taupo_Text_LakeMan:
	.string "The lake is the crater of\n"
	.string "something enormous and asleep.\p"
	.string "Best fishing in the world,\n"
	.string "right on top of it.\p"
	.string "…We don't think about it much.$"

Taupo_Text_StreetWoman:
	.string "Everything south of here is\n"
	.string "mountains and weather.\p"
	.string "Everything east is home for\n"
	.string "somebody.\p"
	.string "…You looked east just then.$"

Taupo_Text_GateOldMan:
	.string "That road east goes over the\n"
	.string "ranges to Ahuriri. Three days,\l"
	.string "beautiful the whole way.\p"
	.string "The Mob shut it overnight. No\n"
	.string "notice, no reason given.\p"
	.string "…Some folk out there just want\n"
	.string "to keep a door shut, eh.$"

Taupo_Text_Kid:
	.string "I skimmed a stone THIRTEEN times\n"
	.string "on the lake!\p"
	.string "Then something skimmed it back.$"

Taupo_Text_LakeSign:
	.string "LAKE TAUPO\p"
	.string "“The heart of the fish.”$"

@ ---- The Choice: north fork (Lugia) ----
Taupo_EventScript_LakeBoatman::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x903, Taupo_EventScript_BoatmanAfter
	goto_if_set FLAG_UNUSED_0x902, Taupo_EventScript_BoatmanTooLate
	goto_if_unset FLAG_UNUSED_0x900, Taupo_EventScript_BoatmanPreChoice
	msgbox Taupo_Text_BoatmanWarn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Taupo_EventScript_BoatmanNo
	setflag FLAG_UNUSED_0x901
	closemessage
	warp MAP_TAUPO_LAKE_ISLE, 13, 17
	waitstate
	end

Taupo_EventScript_BoatmanClosed::
	msgbox Taupo_Text_BoatmanClosed, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_BoatmanNo::
	msgbox Taupo_Text_BoatmanNo, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_BoatmanTooLate::
	msgbox Taupo_Text_BoatmanTooLate, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_BoatmanAfter::
	msgbox Taupo_Text_BoatmanAfter, MSGBOX_DEFAULT
	release
	end

Taupo_Text_BoatmanClosed:
	.string "Boatman: The isle? Nobody lands\n"
	.string "there, e hoa. That water\l"
	.string "belongs to what's under it.$"

Taupo_Text_BoatmanWarn:
	.string "Boatman: …So it's true, then.\n"
	.string "What your old man said.\p"
	.string "Listen once: if I row you out,\n"
	.string "there's no rowing to the OTHER\l"
	.string "one after. There isn't time.\l"
	.string "There was never time for both.\p"
	.string "You choose with your feet.\n"
	.string "…Get in?$"

Taupo_Text_BoatmanNo:
	.string "Boatman: Aye. Think on it.\p"
	.string "But don't think long. Your\n"
	.string "brother isn't.$"

Taupo_Text_BoatmanTooLate:
	.string "Boatman: You went south.\p"
	.string "…The lake's been dark two days\n"
	.string "now. Whatever came for the\l"
	.string "diver, it didn't row.$"

Taupo_Text_BoatmanAfter:
	.string "Boatman: Done is done, e hoa.\p"
	.string "Whatever you carry now, carry\n"
	.string "it all the way to that tower.$"

@ ------------------------------------------------------------------
@ Tawhai - the road mentor, keeper of the Tongariro gate. He barred
@ this road all game; post-tower, with Awhi's pointer, he opens it.
@ ------------------------------------------------------------------
Taupo_EventScript_Tawhai::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x90C, Taupo_EventScript_TawhaiOpen
	goto_if_unset FLAG_UNUSED_0x907, Taupo_EventScript_TawhaiBarred
	goto_if_unset FLAG_UNUSED_0x90B, Taupo_EventScript_TawhaiWaiting
	msgbox Taupo_Text_TawhaiOpens, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x90C
	goto Taupo_EventScript_TawhaiAsk

Taupo_EventScript_TawhaiOpen::
	msgbox Taupo_Text_TawhaiRoadOpen, MSGBOX_DEFAULT
	goto Taupo_EventScript_TawhaiAsk

Taupo_EventScript_TawhaiAsk::
	msgbox Taupo_Text_TawhaiHeadUp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Taupo_EventScript_TawhaiStay
	msgbox Taupo_Text_TawhaiGoSlow, MSGBOX_DEFAULT
	closemessage
	warp MAP_RUAPEHU_ASCENT, 28, 40
	waitstate
	release
	end

Taupo_EventScript_TawhaiStay::
	msgbox Taupo_Text_TawhaiStay, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_TawhaiBarred::
	msgbox Taupo_Text_TawhaiBarred, MSGBOX_DEFAULT
	release
	end

Taupo_EventScript_TawhaiWaiting::
	msgbox Taupo_Text_TawhaiWaiting, MSGBOX_DEFAULT
	release
	end

Taupo_Text_TawhaiBarred:
	.string "Tawhai: The mountain-family is\n"
	.string "grieving, e tama. That road\l"
	.string "stays shut while the Bay burns.\p"
	.string "Not for you. Not for anyone.$"

Taupo_Text_TawhaiWaiting:
	.string "Tawhai: The tower is quiet.\n"
	.string "Good. You did that.\p"
	.string "…You're looking for something\n"
	.string "now. When you know WHAT, come\l"
	.string "back and ask me properly.$"

Taupo_Text_TawhaiOpens:
	.string "Tawhai: …Ruapehu. I know.\p"
	.string "I've seen the smoke of his\n"
	.string "campfire from the tea tree\l"
	.string "line, most evenings.\p"
	.string "I barred this road to everyone\n"
	.string "for years. Today I open it.\p"
	.string "He asked me the same thing\n"
	.string "you're about to.$"

Taupo_Text_TawhaiRoadOpen:
	.string "Tawhai: The maunga waits.\n"
	.string "So does he.$"

Taupo_Text_TawhaiHeadUp:
	.string "Head up the mountain now?$"

Taupo_Text_TawhaiGoSlow:
	.string "Tawhai: Go up slow.\n"
	.string "Come down whole.$"

Taupo_Text_TawhaiStay:
	.string "Tawhai: The mountain has\n"
	.string "waited this long. It can wait\l"
	.string "for you to be ready.$"

@ ------------------------------------------------------------------
@ Hori, the Mob's least effective grunt. He wants your shoes.
@ ------------------------------------------------------------------
Taupo_EventScript_Hori::
	lock
	faceplayer
	trainerbattle_single TRAINER_HORI_3, Taupo_Text_HoriIntro, Taupo_Text_HoriDefeat, Taupo_EventScript_HoriBeaten
	release
	end

Taupo_EventScript_HoriBeaten::
	msgbox Taupo_Text_HoriAfter, MSGBOX_DEFAULT
	closemessage
	playse SE_FLEE
	removeobject 7
	setflag FLAG_UNUSED_0x275
	release
	end

Taupo_Text_HoriIntro:
	.string "Oi! Remember me? Hori?\p"
	.string "Me Scraggy EVOLVED. It's got\n"
	.string "proper pants now.\p"
	.string "One on one for your shoes,\n"
	.string "your socks, AND your hat.$"

Taupo_Text_HoriDefeat:
	.string "Even the pants weren't enough!$"

Taupo_Text_HoriAfter:
	.string "…Hang on. You're President\n"
	.string "Kauri's kid, eh.\p"
	.string "…Nah. Doesn't matter whose kid\n"
	.string "y'are. Shoes are shoes.\p"
	.string "Next town. Bring the shoes.$"

@ ==================================================================
@ THE LAKE MEETS YOU. Mid-game Lugia bond - a recognition, not a
@ capture. Gated: badge 3+, before the Choice opens. FLAG_UNUSED_0x27F
@ ==================================================================
Taupo_EventScript_BoatmanPreChoice::
	goto_if_set FLAG_UNUSED_0x27F, Taupo_EventScript_BoatmanClosed
	goto_if_unset FLAG_BADGE03_GET, Taupo_EventScript_BoatmanClosed
	msgbox Taupo_Text_BondOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Taupo_EventScript_BondNo
	closemessage
	fadescreen FADE_TO_BLACK
	delay 30
	fadescreen FADE_FROM_BLACK
	msgbox Taupo_Text_BondOut, MSGBOX_DEFAULT
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox Taupo_Text_BondRises, MSGBOX_DEFAULT
	msgbox Taupo_Text_BondGone, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	delay 30
	fadescreen FADE_FROM_BLACK
	msgbox Taupo_Text_BondShore, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x27F
	release
	end

Taupo_EventScript_BondNo::
	msgbox Taupo_Text_BondNoReply, MSGBOX_DEFAULT
	release
	end

Taupo_Text_BondOffer:
	.string "Boatman: Flat as glass today.\n"
	.string "Doesn't happen twice a year.\p"
	.string "…I take people out when it's\n"
	.string "like this. Just out and back.\l"
	.string "No rod, no fuss.\p"
	.string "The lake likes some people.\n"
	.string "I've a feeling about you.\p"
	.string "Coming?$"

Taupo_Text_BondNoReply:
	.string "Boatman: Another still day,\n"
	.string "then. If the lake allows one.$"

Taupo_Text_BondOut:
	.string "Halfway out, the water goes\n"
	.string "quiet-heavy, the way a room\l"
	.string "goes quiet when someone\l"
	.string "important walks in.\p"
	.string "Something passes under the\n"
	.string "hull.\p"
	.string "Longer than the boat.\p"
	.string "Longer than the jetty.$"

Taupo_Text_BondRises:
	.string "It rises alongside.\p"
	.string "Silver, in its own weather.\n"
	.string "An eye like a well.\p"
	.string "It holds there, half the lake\n"
	.string "balanced on its stillness -\p"
	.string "watching you.\p"
	.string "Not the boat. Not the boatman.\p"
	.string "You.$"

Taupo_Text_BondGone:
	.string "No fear comes. That's the\n"
	.string "strange part - you keep\l"
	.string "waiting for the fear.\p"
	.string "What comes instead is the\n"
	.string "feeling of being… read.\l"
	.string "Gently. All the way down.\p"
	.string "Then the lake closes over it\n"
	.string "like an eye going shut, and\l"
	.string "the sun remembers to be warm.$"

Taupo_Text_BondShore:
	.string "The boatman doesn't speak\n"
	.string "until the jetty.\p"
	.string "Boatman: …Forty years on this\n"
	.string "lake.\p"
	.string "It has never once come up for\n"
	.string "anybody.\p"
	.string "…Whatever you're carrying,\n"
	.string "kid - carry it careful.$"

Taupo_EventScript_PKiwa::
	trainerbattle_single TRAINER_TPT_KIWA, Taupo_Text_PKiwaIntro, Taupo_Text_PKiwaDefeat
	msgbox Taupo_Text_PKiwaPost, MSGBOX_AUTOCLOSE
	end

Taupo_Text_PKiwaIntro:
	.string "Kiwa: Shh! You'll scare the fish!\n…Too late. Battle.$"

Taupo_Text_PKiwaDefeat:
	.string "Snapped my line AND my streak.$"

Taupo_Text_PKiwaPost:
	.string "They're biting better since\nyou showed up. Weird.$"

Taupo_EventScript_PMarara::
	trainerbattle_single TRAINER_TPT_MARARA, Taupo_Text_PMararaIntro, Taupo_Text_PMararaDefeat
	msgbox Taupo_Text_PMararaPost, MSGBOX_AUTOCLOSE
	end

Taupo_Text_PMararaIntro:
	.string "Marara: The one that got away was\nTHIS big. Like my Pokemon.$"

Taupo_Text_PMararaDefeat:
	.string "Also got away on me.$"

Taupo_Text_PMararaPost:
	.string "Tide's turning. Good luck out\nthere.$"

Taupo_EventScript_PAmiria::
	trainerbattle_single TRAINER_TPT_AMIRIA, Taupo_Text_PAmiriaIntro, Taupo_Text_PAmiriaDefeat
	msgbox Taupo_Text_PAmiriaPost, MSGBOX_AUTOCLOSE
	end

Taupo_Text_PAmiriaIntro:
	.string "Amiria: I've tramped every track in\nthis region. Fight me.$"

Taupo_Text_PAmiriaDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Taupo_Text_PAmiriaPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Taupo_EventScript_PHakopa::
	trainerbattle_single TRAINER_TPT_HAKOPA, Taupo_Text_PHakopaIntro, Taupo_Text_PHakopaDefeat
	msgbox Taupo_Text_PHakopaPost, MSGBOX_AUTOCLOSE
	end

Taupo_Text_PHakopaIntro:
	.string "Hakopa: The one that got away was\nTHIS big. Like my Pokemon.$"

Taupo_Text_PHakopaDefeat:
	.string "Also got away on me.$"

Taupo_Text_PHakopaPost:
	.string "Tide's turning. Good luck out\nthere.$"
