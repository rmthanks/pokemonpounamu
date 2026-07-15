@ ============================================================
@ THE MAUNGA SYSTEM - the two-visit shrines
@ Drop-in scripts for the climb maps when they're built.
@ First visit (mid-game, after the story wound): the guardian
@ WAKES - cry, presence, no battle. Return visit (with the
@ finished Mauri Kohatu, post-badge-8): the encounter.
@ Flags: 0x297 Hikurangi woken / 0x298 Taranaki / 0x299 Aoraki
@        0x29A Zapdos caught-or-beaten / 0x29B Moltres / 0x29C Articuno
@ ============================================================

Maunga_Shrine_Hikurangi::
	lockall
	goto_if_set FLAG_UNUSED_0x29A, Maunga_Hikurangi_Still
	goto_if_unset FLAG_UNUSED_0x297, Maunga_Hikurangi_FirstWaking
	checkitem ITEM_RED_ORB
	goto_if_eq VAR_RESULT, TRUE, Maunga_Hikurangi_Return
	msgbox Maunga_Text_SummitWaits, MSGBOX_DEFAULT
	releaseall
	end

Maunga_Hikurangi_FirstWaking::
	msgbox Maunga_Text_HikurangiDawn, MSGBOX_DEFAULT
	playmoncry SPECIES_ZAPDOS, CRY_MODE_ENCOUNTER
	delay 40
	setweather WEATHER_RAIN_THUNDERSTORM
	doweather
	delay 60
	msgbox Maunga_Text_HikurangiWakes, MSGBOX_DEFAULT
	setweather WEATHER_SUNNY
	doweather
	setflag FLAG_UNUSED_0x297
	releaseall
	end

Maunga_Hikurangi_Return::
	msgbox Maunga_Text_HikurangiReturn, MSGBOX_DEFAULT
	playmoncry SPECIES_ZAPDOS, CRY_MODE_ENCOUNTER
	delay 40
	setwildbattle SPECIES_ZAPDOS, 60
	dowildbattle
	setflag FLAG_UNUSED_0x29A
	releaseall
	end

Maunga_Hikurangi_Still::
	msgbox Maunga_Text_SummitAtPeace, MSGBOX_DEFAULT
	releaseall
	end

Maunga_Text_HikurangiDawn:
	.string "The first light in the country\n"
	.string "touches the summit stone.\p"
	.string "The pendant at your neck hums,\n"
	.string "faint as a held breath.$"

Maunga_Text_HikurangiWakes:
	.string "Wings. Storm-wide.\p"
	.string "It circles the summit once and\n"
	.string "looks at you - THROUGH you.\p"
	.string "It does not fight. It has seen\n"
	.string "what it needed to see.\p"
	.string "The storm passes. The dawn holds.$"

Maunga_Text_HikurangiReturn:
	.string "The Mauri Kohatu sings against\n"
	.string "your chest.\p"
	.string "The sky answers.$"

Maunga_Text_SummitWaits:
	.string "The summit is quiet.\p"
	.string "Something here is waiting for\n"
	.string "the stone to be finished.$"

Maunga_Text_SummitAtPeace:
	.string "The summit is at peace.\n"
	.string "The dawn comes first here,\l"
	.string "same as it always has.$"

@ Taranaki and Aoraki follow the same pattern - swap species
@ (MOLTRES/ARTICUNO), flags (0x298+0x29B / 0x299+0x29C), and
@ text themes: Taranaki = the mountain that became its exile
@ (the player chooses not to); Aoraki = the shrine sits BELOW
@ the peak - you do not stand on his head.
