NgamotuWindGallery_MapScripts::
	.byte 0

NgamotuWindGallery_EventScript_Kinetic::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x292, NgamotuWindGallery_WINDJOB_Done
	msgbox NgamotuWindGallery_Text_WINDJOBAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NgamotuWindGallery_WINDJOB_No
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, NgamotuWindGallery_WINDJOB_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_HOPPIP, NgamotuWindGallery_WINDJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_SKIPLOOM, NgamotuWindGallery_WINDJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_JUMPLUFF, NgamotuWindGallery_WINDJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_COTTONEE, NgamotuWindGallery_WINDJOB_Good
	goto_if_eq VAR_RESULT, SPECIES_WHIMSICOTT, NgamotuWindGallery_WINDJOB_Good
	msgbox NgamotuWindGallery_Text_WINDJOBWrong, MSGBOX_DEFAULT
	release
	end

NgamotuWindGallery_WINDJOB_Good::
	msgbox NgamotuWindGallery_Text_WINDJOBThanks, MSGBOX_DEFAULT
	giveitem ITEM_AIR_BALLOON
	goto_if_eq VAR_RESULT, FALSE, NgamotuWindGallery_WINDJOB_Full
	setflag FLAG_UNUSED_0x292
	release
	end

NgamotuWindGallery_WINDJOB_No::
	msgbox NgamotuWindGallery_Text_WINDJOBNo, MSGBOX_DEFAULT
	release
	end

NgamotuWindGallery_WINDJOB_Full::
	release
	end

NgamotuWindGallery_WINDJOB_Done::
	msgbox NgamotuWindGallery_Text_WINDJOBAfter, MSGBOX_DEFAULT
	release
	end

NgamotuWindGallery_Text_WINDJOBAsk:
	.string "The Wind Wand out front bends\n"
	.string "but never breaks. Kinetic art,\l"
	.string "they call it.\p"
	.string "I'm making a new piece. I want\n"
	.string "to watch something that rides\l"
	.string "the wind like the Wand does.\l"
	.string "Show me one?$"

NgamotuWindGallery_Text_WINDJOBNo:
	.string "The whole coast is kinetic art\n"
	.string "if you ask me. Nothing here\l"
	.string "stands still, not even the\l"
	.string "mountain.$"

NgamotuWindGallery_Text_WINDJOBWrong:
	.string "Lovely, but that one fights the\n"
	.string "wind. I need one that lets it\l"
	.string "carry them.$"

NgamotuWindGallery_Text_WINDJOBThanks:
	.string "Yes! Look how it gives in and\n"
	.string "still gets where it's going.\l"
	.string "That's the whole piece, right\l"
	.string "there.\p"
	.string "Here. A bit of the wind, kept\n"
	.string "in a balloon. Don't ask how.$"

NgamotuWindGallery_Text_WINDJOBAfter:
	.string "The new piece is called\n"
	.string "“Letting Go, Arriving Anyway”.\l"
	.string "The council hates the title.\l"
	.string "Perfect.$"

NgamotuWindGallery_Text_Kinetic:
	.string "The Wind Wand out front bends\n"
	.string "but never breaks. Kinetic art,\l"
	.string "they call it.\p"
	.string "The whole coast is kinetic\n"
	.string "art if you ask me. Nothing\l"
	.string "here stands still, not even\l"
	.string "the mountain. ESPECIALLY not\l"
	.string "the mountain.$"

NgamotuWindGallery_EventScript_ArtKid::
	lock
	faceplayer
	msgbox NgamotuWindGallery_Text_ArtKid, MSGBOX_DEFAULT
	release
	end

NgamotuWindGallery_Text_ArtKid:
	.string "I drew Taranaki maunga with a\n"
	.string "big frowny face and my teacher\l"
	.string "said it was DISRESPECTFUL\l"
	.string "but also ACCURATE.$"

