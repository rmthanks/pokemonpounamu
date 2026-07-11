NgamotuSurfHighway_MapScripts::
	.byte 0

NgamotuSurfHighway_EventScript_Surfer2::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x038, NgamotuSurfHighway_EventScript_Surfer2_Done
	msgbox NgamotuSurfHighway_Text_Surfer2, MSGBOX_DEFAULT
	giveitem ITEM_SHARP_BEAK, 1
	setflag FLAG_UNUSED_0x038
	release
	end

NgamotuSurfHighway_EventScript_Surfer2_Done::
	msgbox NgamotuSurfHighway_Text_Surfer2_After, MSGBOX_DEFAULT
	release
	end

NgamotuSurfHighway_Text_Surfer2:
	.string "Surf Highway 45. Every bend\n"
	.string "is a break, every break has\l"
	.string "a name and a local who owns it.\p"
	.string "Found this on the beach under\n"
	.string "the wand. Bird that dropped it\l"
	.string "was gone before I looked up.\l"
	.string "Big shadow, though. BIG.$"

NgamotuSurfHighway_Text_Surfer2_After:
	.string "Swells up Thursday.\n"
	.string "Pray to the mountain.$"

