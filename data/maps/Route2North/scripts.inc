Route2North_MapScripts::
	.byte 0

Route2North_EventScript_Rewi::
	trainerbattle_single TRAINER_R2N_REWI, Route2North_Text_RewiIntro, Route2North_Text_RewiDefeat
	msgbox Route2North_Text_RewiPost, MSGBOX_AUTOCLOSE
	end

Route2North_EventScript_Piri::
	trainerbattle_single TRAINER_R2N_PIRI, Route2North_Text_PiriIntro, Route2North_Text_PiriDefeat
	msgbox Route2North_Text_PiriPost, MSGBOX_AUTOCLOSE
	end

Route2North_Text_RewiIntro:
	.string "River's run odd since that\n"
	.string "checkpoint went up.\p"
	.string "Fish still bite, though.\n"
	.string "Let's see if you do!$"

Route2North_Text_RewiDefeat:
	.string "Hooked, lined, and sunk.$"

Route2North_Text_RewiPost:
	.string "You came out of the Bay, eh?\p"
	.string "…Keep that to yourself north\n"
	.string "of here. Folk talk.$"

Route2North_Text_PiriIntro:
	.string "Slips took the rail line out\n"
	.string "years back.\p"
	.string "Road's all we've got - and now\n"
	.string "the Mob's got the road!$"

Route2North_Text_PiriDefeat:
	.string "Solid as the ranges, you are.$"

Route2North_Text_PiriPost:
	.string "Wairoa's just up the way.\p"
	.string "Get a proper feed and a proper\n"
	.string "sleep. The coast road is long.$"
