NgamotuWindGallery_MapScripts::
	.byte 0

NgamotuWindGallery_EventScript_Kinetic::
	lock
	faceplayer
	msgbox NgamotuWindGallery_Text_Kinetic, MSGBOX_DEFAULT
	release
	end

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

