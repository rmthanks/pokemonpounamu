OtepotiScarfieFlat_MapScripts::
	.byte 0

OtepotiScarfieFlat_EventScript_Scarfie::
	lock
	faceplayer
	msgbox OtepotiScarfieFlat_Text_Scarfie, MSGBOX_DEFAULT
	release
	end

OtepotiScarfieFlat_Text_Scarfie:
	.string "Coldest flat in the southern\n"
	.string "hemisphere, probably. We burn\l"
	.string "last year's lecture notes.\p"
	.string "Worth it. Steepest street in\n"
	.string "the world's up the road - we\l"
	.string "race cheese wheels down it.\l"
	.string "Education, mate.$"

OtepotiScarfieFlat_EventScript_Scarfie2::
	lock
	faceplayer
	msgbox OtepotiScarfieFlat_Text_Scarfie2, MSGBOX_DEFAULT
	release
	end

OtepotiScarfieFlat_Text_Scarfie2:
	.string "The albatross colony out on\n"
	.string "the peninsula? Only mainland\l"
	.string "one ON EARTH.\p"
	.string "Those wings never get tired.\n"
	.string "Imagine caring about one thing\l"
	.string "that completely.$"

