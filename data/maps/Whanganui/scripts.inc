Whanganui_MapScripts::
	.byte 0
Whanganui_EventScript_RiverMan::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x293, Whanganui_MailJob_Done
	goto_if_set FLAG_UNUSED_0x4B1, Whanganui_MailJob_Carrying
	msgbox Whanganui_Text_RiverMan, MSGBOX_DEFAULT
	msgbox Whanganui_Text_MailJobAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Whanganui_MailJob_No
	setflag FLAG_UNUSED_0x4B1
	msgbox Whanganui_Text_MailJobGo, MSGBOX_DEFAULT
	release
	end
Whanganui_EventScript_Kid::
	msgbox Whanganui_Text_Kid, MSGBOX_NPC
	end
Whanganui_EventScript_RiverSign::
	msgbox Whanganui_Text_RiverSign, MSGBOX_SIGN
	end
Whanganui_Text_RiverMan:
	.string "The awa is our tupuna. Our\n"
	.string "ancestor. Ko au te awa, ko te\l"
	.string "awa ko au.\p"
	.string "I am the river and the river\n"
	.string "is me.\p"
	.string "You look like someone who could\n"
	.string "use a river to belong to.$"
Whanganui_Text_Kid:
	.string "I'm going to paddle the whole\n"
	.string "awa one day! Source to sea!\p"
	.string "…After lunch, though.$"
Whanganui_Text_RiverSign:
	.string "WHANGANUI\p"
	.string "“Ko au te awa, ko te awa ko au.”$"

@ ---- Mission batch S2 (2026-09-26) ----
@ Job 25: The River Mail - carry the letter to his moko in Wellington; done FLAG_UNUSED_0x293
Whanganui_MailJob_No::
	msgbox Whanganui_Text_MailJobNo, MSGBOX_DEFAULT
	release
	end

Whanganui_MailJob_Carrying::
	msgbox Whanganui_Text_MailJobCarrying, MSGBOX_DEFAULT
	release
	end

Whanganui_MailJob_Done::
	msgbox Whanganui_Text_MailJobAfter, MSGBOX_DEFAULT
	release
	end
Whanganui_Text_MailJobAsk:
	.string "For a hundred years the\n"
	.string "riverboats carried the mail up\l"
	.string "and down this awa.\p"
	.string "My moko is at university in\n"
	.string "Wellington. Would you carry a\l"
	.string "letter downriver for me?$"
Whanganui_Text_MailJobGo:
	.string "Tell him his koro says eat\n"
	.string "properly and ring his mother.\l"
	.string "He lives in a student flat, the\l"
	.string "cold kind.$"
Whanganui_Text_MailJobNo:
	.string "All good. The awa is patient.$"
Whanganui_Text_MailJobCarrying:
	.string "My moko's in a student flat in\n"
	.string "Wellington. The cold kind. You\l"
	.string "can't miss it.$"
Whanganui_Text_MailJobAfter:
	.string "He rang his mother! Three whole\n"
	.string "minutes. The river mail still\l"
	.string "works miracles.$"

@ Job 26: Durie Hill - the lift operator's lost-and-found, and the Dowsing Machine; done FLAG_UNUSED_0x294
Whanganui_EventScript_DURIEJOB::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x294, Whanganui_DurieJob_Done
	goto_if_set FLAG_UNUSED_0x4B2, Whanganui_DurieJob_Check
	msgbox Whanganui_Text_DurieJobIntro, MSGBOX_DEFAULT
	giveitem ITEM_DOWSING_MACHINE
	goto_if_eq VAR_RESULT, FALSE, Whanganui_DurieJob_Full
	setflag FLAG_UNUSED_0x4B2
	msgbox Whanganui_Text_DurieJobGo, MSGBOX_DEFAULT
	release
	end

Whanganui_DurieJob_Check::
	goto_if_unset FLAG_UNUSED_0x4B3, Whanganui_DurieJob_NotYet
	goto_if_unset FLAG_UNUSED_0x4B4, Whanganui_DurieJob_NotYet
	goto_if_unset FLAG_UNUSED_0x4B5, Whanganui_DurieJob_NotYet
	msgbox Whanganui_Text_DurieJobThanks, MSGBOX_DEFAULT
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Whanganui_DurieJob_Full
	setflag FLAG_UNUSED_0x294
Whanganui_DurieJob_Full::
	release
	end

Whanganui_DurieJob_NotYet::
	msgbox Whanganui_Text_DurieJobNotYet, MSGBOX_DEFAULT
	release
	end

Whanganui_DurieJob_Done::
	msgbox Whanganui_Text_DurieJobAfter, MSGBOX_DEFAULT
	release
	end
Whanganui_Text_DurieJobIntro:
	.string "I run the Durie Hill lift. It\n"
	.string "goes up through the inside of\l"
	.string "the hill. Only one in the\l"
	.string "country!\p"
	.string "People drop things on the way\n"
	.string "up. Three things this week\l"
	.string "alone. Here, this beeps near\l"
	.string "buried bits and bobs.$"
Whanganui_Text_DurieJobGo:
	.string "Have a poke around town. Bring\n"
	.string "me word when you've found all\l"
	.string "three.$"
Whanganui_Text_DurieJobNotYet:
	.string "Still some beeping to do, I\n"
	.string "reckon. Three lost things.\l"
	.string "Check round the edges of town.$"
Whanganui_Text_DurieJobThanks:
	.string "All three! You've got a nose\n"
	.string "for it.\p"
	.string "Keep that gadget. And take\n"
	.string "this. Somebody left it in the\l"
	.string "lift in 1983 and never came\l"
	.string "back.$"
Whanganui_Text_DurieJobAfter:
	.string "Up through the hill and out the\n"
	.string "top. Best view on the river.$"

