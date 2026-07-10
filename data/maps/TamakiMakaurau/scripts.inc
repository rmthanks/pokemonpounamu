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
