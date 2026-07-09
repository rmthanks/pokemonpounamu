Opotiki_MapScripts::
	.byte 0

Opotiki_EventScript_WharfOldMan::
	msgbox Opotiki_Text_WharfOldMan, MSGBOX_NPC
	end

Opotiki_EventScript_Woman::
	msgbox Opotiki_Text_Woman, MSGBOX_NPC
	end

Opotiki_EventScript_Kid::
	msgbox Opotiki_Text_Kid, MSGBOX_NPC
	end

Opotiki_EventScript_WharfSign::
	msgbox Opotiki_Text_WharfSign, MSGBOX_SIGN
	end

Opotiki_Text_WharfOldMan:
	.string "Way up north, in the Hokianga,\n"
	.string "there was a dolphin once.\p"
	.string "Opo, they called her. Towed the\n"
	.string "kids round the harbour on her\l"
	.string "back. True story.\p"
	.string "…One day, someone like you will\n"
	.string "go all the way up and find out\l"
	.string "if she ever came back.$"

Opotiki_Text_Woman:
	.string "You walked the Cape road?\n"
	.string "The WHOLE thing?\p"
	.string "Sit down, love. I'll put the\n"
	.string "jug on.$"

Opotiki_Text_Kid:
	.string "The harbour dolphins race the\n"
	.string "boats every morning!\p"
	.string "The boats have never won.\n"
	.string "Not once. It's embarrassing.$"

Opotiki_Text_WharfSign:
	.string "OPOTIKI WHARF\p"
	.string "“All tides welcome.”$"
