Wairoa_MapScripts::
	.byte 0

Wairoa_EventScript_Woman::
	msgbox Wairoa_Text_Woman, MSGBOX_NPC
	end

Wairoa_EventScript_Kid::
	msgbox Wairoa_Text_Kid, MSGBOX_NPC
	end

Wairoa_EventScript_OldMan::
	msgbox Wairoa_Text_OldMan, MSGBOX_NPC
	end

Wairoa_EventScript_TownSign::
	msgbox Wairoa_Text_TownSign, MSGBOX_SIGN
	end

Wairoa_Text_Woman:
	.string "You came up through the\n"
	.string "checkpoint?\p"
	.string "…Nobody comes up through the\n"
	.string "checkpoint, dear.\p"
	.string "Come in, sit down. You look like\n"
	.string "you've had a week of it.$"

Wairoa_Text_Kid:
	.string "Our Poochyena can smell the\n"
	.string "river before the rain!\p"
	.string "Everyone here has one. Best\n"
	.string "dogs on the coast!$"

Wairoa_Text_OldMan:
	.string "South road's Mob business now.\p"
	.string "Was a time the whole Bay came up\n"
	.string "for the river races…\p"
	.string "…Was a time.$"

Wairoa_Text_TownSign:
	.string "WAIROA\p"
	.string "“Where the river meets the sea.”$"

@ ==================================================================
@ AWHI - road meeting 1 of 4. Tama's ex, Mob-born, got out earlier.
@ The window onto home begins. met: FLAG_UNUSED_0x279
@ ==================================================================
Wairoa_EventScript_Awhi::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x279, Wairoa_EventScript_AwhiRetalk
	msgbox Wairoa_Text_Awhi1, MSGBOX_DEFAULT
	msgbox Wairoa_Text_Awhi2, MSGBOX_DEFAULT
	msgbox Wairoa_Text_Awhi3, MSGBOX_DEFAULT
	setflag FLAG_UNUSED_0x279
	release
	end

Wairoa_EventScript_AwhiRetalk::
	msgbox Wairoa_Text_AwhiAfter, MSGBOX_DEFAULT
	release
	end

Wairoa_Text_Awhi1:
	.string "A young woman leans on the dairy\n"
	.string "wall like she's been waiting\l"
	.string "all morning.\p"
	.string "Awhi: Heard a truck came through\n"
	.string "the checkpoint with a kid in\l"
	.string "the back.\p"
	.string "…Look at you. Last time I saw\n"
	.string "you, you were knee-high and the\l"
	.string "house was loud.\p"
	.string "You won't remember me. Awhi.\n"
	.string "I used to walk you to kura.$"

Wairoa_Text_Awhi2:
	.string "Awhi: I was your brother's girl,\n"
	.string "back before he went hard.\p"
	.string "Mob-born, me. My parents were\n"
	.string "your dad's seconds.\p"
	.string "I got out before Tama could\n"
	.string "drag me down with him.\p"
	.string "…Mostly out. It's work, staying\n"
	.string "out. Nobody tells you that part.$"

Wairoa_Text_Awhi3:
	.string "Awhi: Word from home, since\n"
	.string "that's my job now, apparently:\p"
	.string "the Bay's sealed tight. Both\n"
	.string "roads. His people on the gates.\p"
	.string "Your mum's still in the orchard\n"
	.string "and she is NOT leaving it.\p"
	.string "Chin up. That woman bends for\n"
	.string "nobody.\p"
	.string "Go north, kid. I'll find you on\n"
	.string "the road. Someone's got to keep\l"
	.string "you fed with news.$"

Wairoa_Text_AwhiAfter:
	.string "Awhi: North, kid. Hikurangi\n"
	.string "first - watch for the camp at\l"
	.string "the foothills.\p"
	.string "I'll find you.$"
