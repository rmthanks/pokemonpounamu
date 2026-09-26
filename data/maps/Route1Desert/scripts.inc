Route1Desert_MapScripts::
	.byte 0

Route1Desert_EventScript_Koa::
	trainerbattle_single TRAINER_R1D_KOA, Route1Desert_Text_KoaIntro, Route1Desert_Text_KoaDefeat
	msgbox Route1Desert_Text_KoaPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_EventScript_Ari::
	trainerbattle_single TRAINER_R1D_ARI, Route1Desert_Text_AriIntro, Route1Desert_Text_AriDefeat
	msgbox Route1Desert_Text_AriPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_KoaIntro:
	.string "The Desert Road! Nothing but\n"
	.string "tussock and three volcanoes\l"
	.string "watching you.\p"
	.string "They won't battle. I will!$"

Route1Desert_Text_KoaDefeat:
	.string "Blown flat.$"

Route1Desert_Text_KoaPost:
	.string "Those mountains south are tapu.\n"
	.string "Tongariro. You'll want to bow,\l"
	.string "even from here.$"

Route1Desert_Text_AriIntro:
	.string "Coldest, highest, emptiest road\n"
	.string "in the North Island.\p"
	.string "I love it. My Numel keeps me\n"
	.string "warm. Come on!$"

Route1Desert_Text_AriDefeat:
	.string "Out cold on the plateau…$"

Route1Desert_Text_AriPost:
	.string "West from here the road forgets\n"
	.string "itself for a while.\p"
	.string "Route 43. The Forgotten World.\n"
	.string "Beautiful and a bit spooky.$"

@ Taha - "the side". One of two wanderers. Never explained.
Route1Desert_EventScript_Taha::
	lock
	faceplayer
	msgbox Route1Desert_Text_Taha, MSGBOX_DEFAULT
	release
	end

Route1Desert_Text_Taha:
	.string "Taha: Don't mind me. I walk\n"
	.string "this road most days.\p"
	.string "Which way's it to… ah. Doesn't\n"
	.string "matter. Both ways are the same\l"
	.string "road, on this one.\p"
	.string "…I had brothers, once. We\n"
	.string "hauled up something enormous\l"
	.string "together, the five of us.\p"
	.string "Biggest catch anyone ever made.\p"
	.string "The youngest did the real work,\n"
	.string "mind. We just carved it up.\l"
	.string "Couldn't wait to.\p"
	.string "You'd think a man who was there\n"
	.string "for THAT would have something\l"
	.string "to show for it, eh.\p"
	.string "…Don't mind me. I walk.$"

Route1Desert_EventScript_PMia::
	trainerbattle_single TRAINER_R1DP_MIA, Route1Desert_Text_PMiaIntro, Route1Desert_Text_PMiaDefeat
	msgbox Route1Desert_Text_PMiaPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_PMiaIntro:
	.string "Mia: I've tramped every track in\nthis region. Fight me.$"

Route1Desert_Text_PMiaDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route1Desert_Text_PMiaPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route1Desert_EventScript_PNate::
	trainerbattle_single TRAINER_R1DP_NATE, Route1Desert_Text_PNateIntro, Route1Desert_Text_PNateDefeat
	msgbox Route1Desert_Text_PNatePost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_PNateIntro:
	.string "Nate: This is protected land.\nProve you respect it.$"

Route1Desert_Text_PNateDefeat:
	.string "You fight like you care.$"

Route1Desert_Text_PNatePost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Route1Desert_EventScript_PNikki::
	trainerbattle_single TRAINER_R1DP_NIKKI, Route1Desert_Text_PNikkiIntro, Route1Desert_Text_PNikkiDefeat
	msgbox Route1Desert_Text_PNikkiPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_PNikkiIntro:
	.string "Nikki: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route1Desert_Text_PNikkiDefeat:
	.string "The forecast said nothing\nabout you.$"

Route1Desert_Text_PNikkiPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route1Desert_EventScript_POlive::
	trainerbattle_single TRAINER_R1DP_OLIVE, Route1Desert_Text_POliveIntro, Route1Desert_Text_POliveDefeat
	msgbox Route1Desert_Text_POlivePost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_POliveIntro:
	.string "Olive: My mokopuna says I'm out of\ndate. Let's test that.$"

Route1Desert_Text_POliveDefeat:
	.string "Tell no one.$"

Route1Desert_Text_POlivePost:
	.string "Old tricks are just good\ntricks that lasted.$"

Route1Desert_EventScript_POllie::
	trainerbattle_single TRAINER_R1DP_OLLIE, Route1Desert_Text_POllieIntro, Route1Desert_Text_POllieDefeat
	msgbox Route1Desert_Text_POlliePost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_POllieIntro:
	.string "Ollie: I train where the weather's\nworst. Makes us honest.$"

Route1Desert_Text_POllieDefeat:
	.string "Honestly beaten.$"

Route1Desert_Text_POlliePost:
	.string "Strength is showing up in\nthe rain.$"

Route1Desert_EventScript_PPaige::
	trainerbattle_single TRAINER_R1DP_PAIGE, Route1Desert_Text_PPaigeIntro, Route1Desert_Text_PPaigeDefeat
	msgbox Route1Desert_Text_PPaigePost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_PPaigeIntro:
	.string "Paige: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route1Desert_Text_PPaigeDefeat:
	.string "The forecast said nothing\nabout you.$"

Route1Desert_Text_PPaigePost:
	.string "Southerly's coming. Take care\nup the track.$"

Route1Desert_EventScript_PQuinn::
	trainerbattle_single TRAINER_R1DP_QUINN, Route1Desert_Text_PQuinnIntro, Route1Desert_Text_PQuinnDefeat
	msgbox Route1Desert_Text_PQuinnPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_Text_PQuinnIntro:
	.string "Quinn: I've tramped every track in\nthis region. Fight me.$"

Route1Desert_Text_PQuinnDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route1Desert_Text_PQuinnPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

@ ---- Mission batch S2 (2026-09-26) ----
@ Job 23: The Desert Road Convoy - clear the Mob toll so the stock truck can pass; done FLAG_UNUSED_0x291
Route1Desert_EventScript_CONVOYJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x291, Route1Desert_ConvoyJob_Done
	goto_if_not_defeated TRAINER_DESERT_TOLL_DEAN, Route1Desert_ConvoyJob_Blocked
	goto_if_not_defeated TRAINER_DESERT_TOLL_KASEY, Route1Desert_ConvoyJob_Blocked
	msgbox Route1Desert_Text_ConvoyJobThanks, MSGBOX_DEFAULT
	giveitem ITEM_MAX_POTION, 2
	goto_if_eq VAR_RESULT, FALSE, Route1Desert_ConvoyJob_Full
	setflag FLAG_UNUSED_0x291
Route1Desert_ConvoyJob_Full::
	release
	end

Route1Desert_ConvoyJob_Blocked::
	msgbox Route1Desert_Text_ConvoyJobBlocked, MSGBOX_DEFAULT
	release
	end

Route1Desert_ConvoyJob_Done::
	msgbox Route1Desert_Text_ConvoyJobAfter, MSGBOX_DEFAULT
	release
	end

Route1Desert_EventScript_TollDean::
	trainerbattle_single TRAINER_DESERT_TOLL_DEAN, Route1Desert_Text_DeanIntro, Route1Desert_Text_DeanDefeat
	msgbox Route1Desert_Text_DeanPost, MSGBOX_AUTOCLOSE
	end

Route1Desert_EventScript_TollKasey::
	trainerbattle_single TRAINER_DESERT_TOLL_KASEY, Route1Desert_Text_KaseyIntro, Route1Desert_Text_KaseyDefeat
	msgbox Route1Desert_Text_KaseyPost, MSGBOX_AUTOCLOSE
	end
Route1Desert_Text_ConvoyJobBlocked:
	.string "Trucker: Got a truck of stock\n"
	.string "bound for Waiouru and two Mob\l"
	.string "tollies wanting a cut to let me\l"
	.string "through.\p"
	.string "Some road. Some tax. If you can\n"
	.string "talk to them in a language they\l"
	.string "understand, I'd be grateful.$"
Route1Desert_Text_ConvoyJobThanks:
	.string "Trucker: Road's clear! The\n"
	.string "sheep thank you. Well, they\l"
	.string "don't, but I do.\p"
	.string "Take these. The Desert Road\n"
	.string "eats people who don't carry\l"
	.string "spares.$"
Route1Desert_Text_ConvoyJobAfter:
	.string "Trucker: Forty years on this\n"
	.string "road. Snow in summer, sun in\l"
	.string "winter, Mob in between.$"
Route1Desert_Text_DeanIntro:
	.string "Road toll. Not the government\n"
	.string "kind. Ours is quicker.$"
Route1Desert_Text_DeanDefeat:
	.string "Fine. Waived. This once.$"
Route1Desert_Text_DeanPost:
	.string "The President doesn't know we\n"
	.string "run this one. Keep it that way,\l"
	.string "eh?$"
Route1Desert_Text_KaseyIntro:
	.string "Everyone pays on the Desert\n"
	.string "Road. Pay in battles, pay in\l"
	.string "bruises.$"
Route1Desert_Text_KaseyDefeat:
	.string "Okay, you've paid.$"
Route1Desert_Text_KaseyPost:
	.string "Wild horses out here don't pay\n"
	.string "anyone. I'm starting to see the\l"
	.string "appeal.$"

