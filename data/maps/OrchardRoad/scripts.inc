OrchardRoad_MapScripts::
	.byte 0

@ ------------------------------------------------------------------
@ Route 51 trainers - locals on the orchard road north to Ahuriri.
@ ------------------------------------------------------------------
OrchardRoad_EventScript_Anaru::
	trainerbattle_single TRAINER_R51_ANARU, OrchardRoad_Text_AnaruIntro, OrchardRoad_Text_AnaruDefeat
	msgbox OrchardRoad_Text_AnaruPost, MSGBOX_AUTOCLOSE
	end

OrchardRoad_EventScript_Mereana::
	trainerbattle_single TRAINER_R51_MEREANA, OrchardRoad_Text_MereanaIntro, OrchardRoad_Text_MereanaDefeat
	msgbox OrchardRoad_Text_MereanaPost, MSGBOX_AUTOCLOSE
	end

OrchardRoad_EventScript_Wiremu::
	trainerbattle_single TRAINER_R51_WIREMU, OrchardRoad_Text_WiremuIntro, OrchardRoad_Text_WiremuDefeat
	msgbox OrchardRoad_Text_WiremuPost, MSGBOX_AUTOCLOSE
	end

@ ------------------------- text -------------------------
OrchardRoad_Text_AnaruIntro:
	.string "You're the homestead kid, eh?\p"
	.string "Whole orchard's talking about\n"
	.string "you heading north.\p"
	.string "Your mum pretends she isn't\n"
	.string "worried. Come on, then!$"

OrchardRoad_Text_AnaruDefeat:
	.string "Yeah… you're ready, alright.$"

OrchardRoad_Text_AnaruPost:
	.string "Picked apples up this road since\n"
	.string "I was your size.\p"
	.string "Watch the tall grass past the\n"
	.string "shelterbelts. Good luck, kid.$"

OrchardRoad_Text_MereanaIntro:
	.string "The wind comes off the ranges\n"
	.string "and my Hoppip rides it all day!\p"
	.string "Hold on to your hat!$"

OrchardRoad_Text_MereanaDefeat:
	.string "Blown away…$"

OrchardRoad_Text_MereanaPost:
	.string "On a clear day you can see Te Mata\n"
	.string "from here. The sleeping giant.\p"
	.string "Nan says he only wakes for\n"
	.string "weddings and wars.$"

OrchardRoad_Text_WiremuIntro:
	.string "My nan reckons the Mob started\n"
	.string "out as a footy club.\p"
	.string "Nan says a lot of things.\n"
	.string "My Poochyena says GRRRR!$"

OrchardRoad_Text_WiremuDefeat:
	.string "Chur. You're good, eh.$"

OrchardRoad_Text_WiremuPost:
	.string "There's a checkpoint north of\n"
	.string "Ahuriri now. Mob fellas.\p"
	.string "Nobody goes up the coast without\n"
	.string "a nod from the president.$"
