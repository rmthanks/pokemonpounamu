OtautahiRebuildHouse_MapScripts::
	.byte 0

OtautahiRebuildHouse_EventScript_Builder::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x03D, OtautahiRebuildHouse_EventScript_Builder_Done
	msgbox OtautahiRebuildHouse_Text_Builder, MSGBOX_DEFAULT
	giveitem ITEM_METAL_COAT, 1
	setflag FLAG_UNUSED_0x03D
	release
	end

OtautahiRebuildHouse_EventScript_Builder_Done::
	msgbox OtautahiRebuildHouse_Text_Builder_After, MSGBOX_DEFAULT
	release
	end

OtautahiRebuildHouse_Text_Builder:
	.string "I've rebuilt this house twice.\n"
	.string "The second time, I built it\l"
	.string "knowing. That's different.\p"
	.string "Steel in the bones now. The\n"
	.string "gym leader taught us that -\l"
	.string "structure isn't what stands,\l"
	.string "it's what stands BACK UP.\p"
	.string "Spare coat of the good stuff.\n"
	.string "Put it on something you love.$"

OtautahiRebuildHouse_Text_Builder_After:
	.string "Solid ground today.\n"
	.string "We notice, down here.$"

