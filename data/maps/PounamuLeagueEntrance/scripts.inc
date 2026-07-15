PounamuLeagueEntrance_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PounamuLeagueEntrance_OnFrame
	.byte 0

PounamuLeagueEntrance_OnFrame:
	map_script_2 VAR_TEMP_1, 0, LeagueEntrance_EventScript_Check
	.2byte 0

LeagueEntrance_EventScript_Check::
	lockall
	setvar VAR_TEMP_1, 1
	goto_if_unset FLAG_BADGE08_GET, LeagueEntrance_EventScript_Idle
	goto_if_set FLAG_SYS_GAME_CLEAR, LeagueEntrance_EventScript_ClearedWarp
	msgbox LeagueEntrance_Text_Welcome, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_POUNAMU_LEAGUE_AWHI, 5, 16
	waitstate
	releaseall
	end

LeagueEntrance_EventScript_ClearedWarp::
	msgbox LeagueEntrance_Text_Cleared, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_POUNAMU_LEAGUE_AWHI, 5, 16
	waitstate
	releaseall
	end

LeagueEntrance_EventScript_Idle::
	releaseall
	end

LeagueEntrance_EventScript_Guard::
	lock
	faceplayer
	msgbox LeagueEntrance_Text_NotYet, MSGBOX_DEFAULT
	release
	end

LeagueEntrance_Text_Welcome:
	.string "So. Eight badges.\p"
	.string "You walked out of Hawke's Bay with\n"
	.string "nothing and you walked the length\l"
	.string "of two islands to stand here.\p"
	.string "Beyond this door wait the four\n"
	.string "walls of the whare - and the one\l"
	.string "who holds the roof.\p"
	.string "Haere ki roto. Go in.$"

LeagueEntrance_Text_NotYet:
	.string "Eight badges to pass, e hoa.\p"
	.string "The whole motu, top to bottom.\n"
	.string "Come back when you've walked it.$"

LeagueEntrance_Text_Cleared:
	.string "The champion's seat is yours now.\p"
	.string "But the walls will test you again\n"
	.string "any time you like. Go in.$"

PounamuLeagueEntrance_EventScript_PWren::
	trainerbattle_single TRAINER_VICT_WREN, PounamuLeagueEntrance_Text_PWrenIntro, PounamuLeagueEntrance_Text_PWrenDefeat
	msgbox PounamuLeagueEntrance_Text_PWrenPost, MSGBOX_AUTOCLOSE
	end

PounamuLeagueEntrance_Text_PWrenIntro:
	.string "Wren: I train where the weather's\nworst. Makes us honest.$"

PounamuLeagueEntrance_Text_PWrenDefeat:
	.string "Honestly beaten.$"

PounamuLeagueEntrance_Text_PWrenPost:
	.string "Strength is showing up in\nthe rain.$"

PounamuLeagueEntrance_EventScript_PXanthe::
	trainerbattle_single TRAINER_VICT_XANTHE, PounamuLeagueEntrance_Text_PXantheIntro, PounamuLeagueEntrance_Text_PXantheDefeat
	msgbox PounamuLeagueEntrance_Text_PXanthePost, MSGBOX_AUTOCLOSE
	end

PounamuLeagueEntrance_Text_PXantheIntro:
	.string "Xanthe: I train where the weather's\nworst. Makes us honest.$"

PounamuLeagueEntrance_Text_PXantheDefeat:
	.string "Honestly beaten.$"

PounamuLeagueEntrance_Text_PXanthePost:
	.string "Strength is showing up in\nthe rain.$"

PounamuLeagueEntrance_EventScript_PYusuf::
	trainerbattle_single TRAINER_VICT_YUSUF, PounamuLeagueEntrance_Text_PYusufIntro, PounamuLeagueEntrance_Text_PYusufDefeat
	msgbox PounamuLeagueEntrance_Text_PYusufPost, MSGBOX_AUTOCLOSE
	end

PounamuLeagueEntrance_Text_PYusufIntro:
	.string "Yusuf: Sixty years I've watched this\nland. Show me something new.$"

PounamuLeagueEntrance_Text_PYusufDefeat:
	.string "…That was new.$"

PounamuLeagueEntrance_Text_PYusufPost:
	.string "The land remembers everyone\nwho crosses it.$"
