Whakatu_MapScripts::
	.byte 0
Whakatu_EventScript_SunWoman::
	msgbox Whakatu_Text_SunWoman, MSGBOX_NPC
	end
Whakatu_EventScript_GymKid::
	msgbox Whakatu_Text_GymKid, MSGBOX_NPC
	end
Whakatu_EventScript_ArtWoman::
	msgbox Whakatu_Text_ArtWoman, MSGBOX_NPC
	end
Whakatu_EventScript_Kid::
	msgbox Whakatu_Text_Kid, MSGBOX_NPC
	end
Whakatu_EventScript_GymSign::
	msgbox Whakatu_Text_GymSign, MSGBOX_SIGN
	end
Whakatu_Text_SunWoman:
	.string "More sunshine hours than anywhere\nin the country! We keep count.\pIt's a competitive sort of sunny.$"
Whakatu_Text_GymKid:
	.string "Leader Roto runs a FIRE gym in\nthe coldest island. Show-off.\p…He does make good soup, but.$"
Whakatu_Text_ArtWoman:
	.string "Every second person here is a\npotter or a painter.\pThe other half run the cafe that\nsells to the first half.$"
Whakatu_Text_Kid:
	.string "The middle of the whole country's\njust up the hill! There's a sign\land everything!$"
Whakatu_Text_GymSign:
	.string "WHAKATU GYM\nLeader: ROTO - keeps the coals.\p“Warmth is a kind of welcome.”$"

@ AWHI - road meeting 3 of 4. The undertow. met: FLAG_UNUSED_0x27B
Whakatu_EventScript_Awhi::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x27B, Whakatu_EventScript_AwhiRetalk
	msgbox Whakatu_Text_Awhi1, MSGBOX_DEFAULT
	msgbox Whakatu_Text_Awhi2, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x27B
	release
	end

Whakatu_EventScript_AwhiRetalk::
	msgbox Whakatu_Text_AwhiAfter, MSGBOX_DEFAULT
	release
	end

Whakatu_Text_Awhi1:
	.string "Awhi: You made it across the\n"
	.string "strait. He knows, by the way.\p"
	.string "He counts your badges out loud\n"
	.string "like they're personal insults.\p"
	.string "…Your dad's out, kid. Deposed\n"
	.string "isn't even the word. Gone\l"
	.string "quiet. Nobody up home has seen\l"
	.string "him since Wellington.\p"
	.string "You look like you know\n"
	.string "something. Keep it. Safer.$"

Whakatu_Text_Awhi2:
	.string "Awhi: And me… I'll tell you the\n"
	.string "ugly bit, since you're grown.\p"
	.string "He calls me. Late. Doesn't talk.\n"
	.string "Just breathes down the line,\l"
	.string "like the boy I knew is in there\l"
	.string "trying to get out.\p"
	.string "And I still answer.\p"
	.string "…Don't look at me like that.\n"
	.string "I know. I KNOW.$"

Whakatu_Text_AwhiAfter:
	.string "Awhi: Go get the cold badges\n"
	.string "done, kid.\p"
	.string "I'll be… around.$"
