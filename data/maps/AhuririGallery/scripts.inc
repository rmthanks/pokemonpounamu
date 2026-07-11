AhuririGallery_MapScripts::
	.byte 0

AhuririGallery_EventScript_Curator::
	lock
	faceplayer
	msgbox AhuririGallery_Text_Curator, MSGBOX_DEFAULT
	release
	end

AhuririGallery_Text_Curator:
	.string "Welcome to the little gallery.\n"
	.string "All local work: the reef, the\l"
	.string "gannets, Pania in bronze.\p"
	.string "The harbour keeps giving us\n"
	.string "subjects. We keep saying\l"
	.string "thank you.$"

AhuririGallery_EventScript_Painter::
	lock
	faceplayer
	msgbox AhuririGallery_Text_Painter, MSGBOX_DEFAULT
	release
	end

AhuririGallery_Text_Painter:
	.string "I paint the same sea every\n"
	.string "day, and it has never once\l"
	.string "been the same sea.$"

