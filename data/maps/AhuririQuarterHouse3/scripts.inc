AhuririQuarterHouse3_MapScripts::
	.byte 0

AhuririQuarterHouse3_EventScript_Widow::
	lock
	faceplayer
	msgbox AhuririQuarterHouse3_Text_Widow, MSGBOX_DEFAULT
	release
	end

AhuririQuarterHouse3_Text_Widow:
	.string "My husband kept the books for\n"
	.string "the Bay's 'development firm'.\l"
	.string "He kept two sets, of course.\p"
	.string "He's at peace now. The books,\n"
	.string "I burned. Some arithmetic\l"
	.string "shouldn't survive you.$"

