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
	goto_if_eq VAR_POUNAMU_DECO_STATE, 1, AhuririGallery_EventScript_PainterPosy
	msgbox AhuririGallery_Text_Painter, MSGBOX_DEFAULT
	release
	end

AhuririGallery_EventScript_PainterPosy::
	msgbox AhuririGallery_Text_PainterPosy, MSGBOX_DEFAULT
	setvar VAR_POUNAMU_DECO_STATE, 2
	release
	end

AhuririGallery_Text_Painter:
	.string "I paint the same sea every\n"
	.string "day, and it has never once\l"
	.string "been the same sea.$"

@ ---- Mission batch S2 (2026-09-26) ----
AhuririGallery_Text_PainterPosy:
	.string "Flowers from Kiri? For me?\p"
	.string "...She knows I'll paint them\n"
	.string "instead of putting them in\l"
	.string "water. She always knows.$"

