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
