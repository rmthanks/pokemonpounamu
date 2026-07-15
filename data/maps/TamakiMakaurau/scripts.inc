TamakiMakaurau_MapScripts::
	.byte 0

TamakiMakaurau_EventScript_FerryHome::
	lock
	faceplayer
	msgbox TamakiMakaurau_Text_FerryHome, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TamakiMakaurau_EventScript_FerryStay
	closemessage
	warp MAP_WELLINGTON, 25, 20
	waitstate
	end

TamakiMakaurau_EventScript_FerryStay::
	release
	end

TamakiMakaurau_EventScript_TowerSign::
	msgbox TamakiMakaurau_Text_TowerSign, MSGBOX_SIGN
	end

TamakiMakaurau_Text_FerryHome:
	.string "Sailor: Back south, e hoa?$"

TamakiMakaurau_Text_TowerSign:
	.string "TE TAUMATA - THE SKY TOWER\p"
	.string "Someone has painted over the\n"
	.string "visitor information.\p"
	.string "The new lettering reads:\n"
	.string "“PRIVATE. BAY BUSINESS.”$"

TamakiMakaurau_EventScript_PAria::
	trainerbattle_single TRAINER_TMK_ARIA, TamakiMakaurau_Text_PAriaIntro, TamakiMakaurau_Text_PAriaDefeat
	msgbox TamakiMakaurau_Text_PAriaPost, MSGBOX_AUTOCLOSE
	end

TamakiMakaurau_Text_PAriaIntro:
	.string "Aria: I train where the weather's\nworst. Makes us honest.$"

TamakiMakaurau_Text_PAriaDefeat:
	.string "Honestly beaten.$"

TamakiMakaurau_Text_PAriaPost:
	.string "Strength is showing up in\nthe rain.$"

TamakiMakaurau_EventScript_PBodhi::
	trainerbattle_single TRAINER_TMK_BODHI, TamakiMakaurau_Text_PBodhiIntro, TamakiMakaurau_Text_PBodhiDefeat
	msgbox TamakiMakaurau_Text_PBodhiPost, MSGBOX_AUTOCLOSE
	end

TamakiMakaurau_Text_PBodhiIntro:
	.string "Bodhi: I train where the weather's\nworst. Makes us honest.$"

TamakiMakaurau_Text_PBodhiDefeat:
	.string "Honestly beaten.$"

TamakiMakaurau_Text_PBodhiPost:
	.string "Strength is showing up in\nthe rain.$"

TamakiMakaurau_EventScript_PCleo::
	trainerbattle_single TRAINER_TMK_CLEO, TamakiMakaurau_Text_PCleoIntro, TamakiMakaurau_Text_PCleoDefeat
	msgbox TamakiMakaurau_Text_PCleoPost, MSGBOX_AUTOCLOSE
	end

TamakiMakaurau_Text_PCleoIntro:
	.string "Cleo: Sixty years I've watched this\nland. Show me something new.$"

TamakiMakaurau_Text_PCleoDefeat:
	.string "…That was new.$"

TamakiMakaurau_Text_PCleoPost:
	.string "The land remembers everyone\nwho crosses it.$"

TamakiMakaurau_EventScript_PDarcy::
	trainerbattle_single TRAINER_TMK_DARCY, TamakiMakaurau_Text_PDarcyIntro, TamakiMakaurau_Text_PDarcyDefeat
	msgbox TamakiMakaurau_Text_PDarcyPost, MSGBOX_AUTOCLOSE
	end

TamakiMakaurau_Text_PDarcyIntro:
	.string "Darcy: I train where the weather's\nworst. Makes us honest.$"

TamakiMakaurau_Text_PDarcyDefeat:
	.string "Honestly beaten.$"

TamakiMakaurau_Text_PDarcyPost:
	.string "Strength is showing up in\nthe rain.$"

TamakiMakaurau_EventScript_PEddie::
	trainerbattle_single TRAINER_TMK_EDDIE, TamakiMakaurau_Text_PEddieIntro, TamakiMakaurau_Text_PEddieDefeat
	msgbox TamakiMakaurau_Text_PEddiePost, MSGBOX_AUTOCLOSE
	end

TamakiMakaurau_Text_PEddieIntro:
	.string "Eddie: Oi! You walked into my line\nof sight. Them's the rules!$"

TamakiMakaurau_Text_PEddieDefeat:
	.string "Aw, heck!$"

TamakiMakaurau_Text_PEddiePost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"
