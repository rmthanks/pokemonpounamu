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

Route2North_EventScript_PTui::
	trainerbattle_single TRAINER_R2N_TUI, Route2North_Text_PTuiIntro, Route2North_Text_PTuiDefeat
	msgbox Route2North_Text_PTuiPost, MSGBOX_AUTOCLOSE
	end

Route2North_Text_PTuiIntro:
	.string "Tui: These paddocks don't run\nthemselves, but the dog helps.$"

Route2North_Text_PTuiDefeat:
	.string "The dog's still the best\nworker here.$"

Route2North_Text_PTuiPost:
	.string "Gates SHUT behind you,\nthanks.$"

Route2North_EventScript_PMiro::
	trainerbattle_single TRAINER_R2N_MIRO, Route2North_Text_PMiroIntro, Route2North_Text_PMiroDefeat
	msgbox Route2North_Text_PMiroPost, MSGBOX_AUTOCLOSE
	end

Route2North_Text_PMiroIntro:
	.string "Miro: Between milkings. You've got\nten minutes. Go.$"

Route2North_Text_PMiroDefeat:
	.string "Back to the shed, then.$"

Route2North_Text_PMiroPost:
	.string "Rain's coming. Good for the\ngrass, good for nothing else.$"

Route2North_EventScript_PRipeka::
	trainerbattle_single TRAINER_R2N_RIPEKA, Route2North_Text_PRipekaIntro, Route2North_Text_PRipekaDefeat
	msgbox Route2North_Text_PRipekaPost, MSGBOX_AUTOCLOSE
	end

Route2North_Text_PRipekaIntro:
	.string "Ripeka: I've tramped every track in\nthis region. Fight me.$"

Route2North_Text_PRipekaDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route2North_Text_PRipekaPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route2North_EventScript_PHine::
	trainerbattle_single TRAINER_R2N_HINE, Route2North_Text_PHineIntro, Route2North_Text_PHineDefeat
	msgbox Route2North_Text_PHinePost, MSGBOX_AUTOCLOSE
	end

Route2North_Text_PHineIntro:
	.string "Hine: Bet you can't beat me.\nDouble or nothing on my lunch!$"

Route2North_Text_PHineDefeat:
	.string "You can have the sammie.$"

Route2North_Text_PHinePost:
	.string "Worth it. Rematch at smoko?$"

Route2North_EventScript_PIhaia::
	trainerbattle_single TRAINER_R2N_IHAIA, Route2North_Text_PIhaiaIntro, Route2North_Text_PIhaiaDefeat
	msgbox Route2North_Text_PIhaiaPost, MSGBOX_AUTOCLOSE
	end

Route2North_Text_PIhaiaIntro:
	.string "Ihaia: DOC ranger. Checking traps.\nAnd checking trainers.$"

Route2North_Text_PIhaiaDefeat:
	.string "Pest-free AND beaten.$"

Route2North_Text_PIhaiaPost:
	.string "Keep to the track and take\nyour rubbish out, eh.$"
