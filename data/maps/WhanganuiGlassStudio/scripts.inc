WhanganuiGlassStudio_MapScripts::
	.byte 0

WhanganuiGlassStudio_EventScript_GlassArtist::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x039, WhanganuiGlassStudio_EventScript_GlassArtist_Done
	msgbox WhanganuiGlassStudio_Text_GlassArtist, MSGBOX_DEFAULT
	giveitem ITEM_HYPER_POTION, 1
	setflag FLAG_UNUSED_0x039
	release
	end

WhanganuiGlassStudio_EventScript_GlassArtist_Done::
	msgbox WhanganuiGlassStudio_Text_GlassArtist_After, MSGBOX_DEFAULT
	release
	end

WhanganuiGlassStudio_Text_GlassArtist:
	.string "Glass is river sand that got\n"
	.string "ambitious. I melt it, spin it,\l"
	.string "and it remembers being water.\p"
	.string "The awa runs through everyone\n"
	.string "here. Legal person, our river.\l"
	.string "First in the world.\p"
	.string "Here, take this. Fired it\n"
	.string "myself. Well. The potion's\l"
	.string "from the chemist, the bottle's\l"
	.string "art.$"

WhanganuiGlassStudio_Text_GlassArtist_After:
	.string "The river is high today.\n"
	.string "She's showing off.$"

