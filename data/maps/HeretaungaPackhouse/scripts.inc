HeretaungaPackhouse_MapScripts::
	.byte 0

HeretaungaPackhouse_EventScript_Forewoman::
	lock
	faceplayer
	msgbox HeretaungaPackhouse_Text_Forewoman, MSGBOX_DEFAULT
	release
	end

HeretaungaPackhouse_Text_Forewoman:
	.string "This packhouse graded every\n"
	.string "apple in the Bay before the\l"
	.string "new sheds went up.\p"
	.string "Now it's crates, cobwebs and\n"
	.string "committee meetings.\l"
	.string "Some retirement, eh?$"

HeretaungaPackhouse_EventScript_Packer::
	lock
	faceplayer
	msgbox HeretaungaPackhouse_Text_Packer, MSGBOX_DEFAULT
	release
	end

HeretaungaPackhouse_Text_Packer:
	.string "Sweet apples ship north,\n"
	.string "sour ones go south for cider.\p"
	.string "Miss Rata reckons you need\n"
	.string "both kinds to call it a\l"
	.string "harvest. She'd know.$"

