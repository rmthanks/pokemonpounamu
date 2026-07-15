WellingtonCentralIsite_MapScripts::
	.byte 0

WellingtonCentralIsite_EventScript_CentralRanger::
	lock
	faceplayer
	msgbox WellingtonCentralIsite_Text_CentralRanger, MSGBOX_DEFAULT
	release
	end

WellingtonCentralIsite_Text_CentralRanger:
	.string "Central i-SITE, kia ora! Every\n"
	.string "job board in the motu reports\l"
	.string "back to this desk.\p"
	.string "Ten jobs done earns a wee\n"
	.string "koha. Twenty, something rare.\l"
	.string "Thirty-five... come see me at\l"
	.string "thirty-five.\p"
	.string "The ferry over the strait is\n"
	.string "weather-dependent. In\l"
	.string "Wellington that's a lifestyle,\l"
	.string "not a warning.$"

WellingtonCentralIsite_EventScript_Reporter::
	lock
	faceplayer
	msgbox WellingtonCentralIsite_Text_Reporter, MSGBOX_DEFAULT
	release
	end

WellingtonCentralIsite_Text_Reporter:
	.string "I'm chasing the storm story.\n"
	.string "Three genies riding the strait\l"
	.string "winds, locals swear by it.\p"
	.string "The Weather Institute calls it\n"
	.string "'anomalous rotation'. My nana\l"
	.string "calls it Tawhirimatea having\l"
	.string "a tangi. I know who I trust.$"


WellingtonCentralIsite_EventScript_MilestoneClerk::
	lock
	faceplayer
	special CountPounamuJobs
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox WellingtonCentralIsite_Text_JobCount, MSGBOX_DEFAULT
	switch VAR_RESULT
	goto_if_ge VAR_RESULT, 10, WellingtonCentralIsite_Clerk_Check10
	msgbox WellingtonCentralIsite_Text_KeepGoing, MSGBOX_DEFAULT
	release
	end

WellingtonCentralIsite_Clerk_Check10::
	goto_if_set FLAG_UNUSED_0x2A9, WellingtonCentralIsite_Clerk_Check20
	msgbox WellingtonCentralIsite_Text_Reward10, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_BALL, 10
	setflag FLAG_UNUSED_0x2A9
	release
	end

WellingtonCentralIsite_Clerk_Check20::
	goto_if_lt VAR_RESULT, 20, WellingtonCentralIsite_Clerk_Praise
	goto_if_set FLAG_UNUSED_0x2AA, WellingtonCentralIsite_Clerk_Check35
	msgbox WellingtonCentralIsite_Text_Reward20, MSGBOX_DEFAULT
	givemon SPECIES_LARVESTA, 5
	setflag FLAG_UNUSED_0x2AA
	release
	end

WellingtonCentralIsite_Clerk_Check35::
	goto_if_lt VAR_RESULT, 35, WellingtonCentralIsite_Clerk_Praise
	goto_if_set FLAG_UNUSED_0x2AB, WellingtonCentralIsite_Clerk_Praise
	msgbox WellingtonCentralIsite_Text_Reward35, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM
	setflag FLAG_UNUSED_0x2AB
	release
	end

WellingtonCentralIsite_Clerk_Praise::
	msgbox WellingtonCentralIsite_Text_Praise, MSGBOX_DEFAULT
	release
	end

WellingtonCentralIsite_Text_JobCount:
	.string "Kia ora! Central i-SITE - we\n"
	.string "track the Job Boards nationwide.\p"
	.string "You've completed {STR_VAR_1} jobs\n"
	.string "for communities around the motu.$"

WellingtonCentralIsite_Text_KeepGoing:
	.string "Ten jobs earns the first taonga.\n"
	.string "The Bay looks after its own -\l"
	.string "and the motu remembers.$"

WellingtonCentralIsite_Text_Reward10:
	.string "Ten and counting! The boards\n"
	.string "talk about you, you know.\p"
	.string "These are from the DOC crew.$"

WellingtonCentralIsite_Text_Reward20:
	.string "Twenty jobs. Twenty!\p"
	.string "…We've been minding something.\n"
	.string "An egg came in from the Matariki\l"
	.string "observatory - it hatched, and\l"
	.string "nobody can raise a sun-moth in\l"
	.string "an office.\p"
	.string "She's yours. Raise her toward\n"
	.string "the light.$"

WellingtonCentralIsite_Text_Reward35:
	.string "Thirty-five. You've worked for\n"
	.string "every town on the map.\p"
	.string "This is the motu's thanks -\n"
	.string "they say fortune follows the\l"
	.string "ones who show up.$"

WellingtonCentralIsite_Text_Praise:
	.string "The boards will have more work\n"
	.string "when you do. Ka pai!$"

WellingtonCentralIsite_EventScript_DocRanger::
	lock
	faceplayer
	special CountPounamuTrainersBeaten
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox WellingtonCentralIsite_Text_TrainerCount, MSGBOX_DEFAULT
	goto_if_ge VAR_RESULT, 250, WellingtonCentralIsite_Ranger_All
	goto_if_ge VAR_RESULT, 100, WellingtonCentralIsite_Ranger_Hundred
	msgbox WellingtonCentralIsite_Text_RangerEarly, MSGBOX_DEFAULT
	release
	end

WellingtonCentralIsite_Ranger_Hundred::
	goto_if_set FLAG_UNUSED_0x2AC, WellingtonCentralIsite_Ranger_Onward
	msgbox WellingtonCentralIsite_Text_Ranger100, MSGBOX_DEFAULT
	giveitem ITEM_MAX_REVIVE, 3
	setflag FLAG_UNUSED_0x2AC
	release
	end

WellingtonCentralIsite_Ranger_Onward::
	msgbox WellingtonCentralIsite_Text_RangerOnward, MSGBOX_DEFAULT
	release
	end

WellingtonCentralIsite_Ranger_All::
	goto_if_set FLAG_UNUSED_0x2AD, WellingtonCentralIsite_Ranger_Legend
	msgbox WellingtonCentralIsite_Text_Ranger250, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	setflag FLAG_UNUSED_0x2AD
	release
	end

WellingtonCentralIsite_Ranger_Legend::
	msgbox WellingtonCentralIsite_Text_RangerLegend, MSGBOX_DEFAULT
	release
	end

WellingtonCentralIsite_Text_TrainerCount:
	.string "DOC Volunteer Logbook, kia ora.\p"
	.string "We log every trainer who tests\n"
	.string "themselves on the tracks.\p"
	.string "Your record: {STR_VAR_1} trainers\n"
	.string "battled and bested.$"

WellingtonCentralIsite_Text_RangerEarly:
	.string "The motu has 250 registered\n"
	.string "trainers, track to track.\p"
	.string "Meet them ALL and there's a\n"
	.string "taonga in it. The rare kind.$"

WellingtonCentralIsite_Text_Ranger100:
	.string "A hundred! You're walking the\n"
	.string "whole country, aren't you.\p"
	.string "Here - field supplies. DOC\n"
	.string "issue. Don't tell the office.$"

WellingtonCentralIsite_Text_RangerOnward:
	.string "The far tracks still hold\n"
	.string "trainers you've never met.\p"
	.string "The logbook waits.$"

WellingtonCentralIsite_Text_Ranger250:
	.string "…All of them. Every trainer on\n"
	.string "every track in Aotearoa.\p"
	.string "Nobody's ever filled the book.\p"
	.string "This has been in the safe since\n"
	.string "the programme started. It's\l"
	.string "yours, e hoa.$"

WellingtonCentralIsite_Text_RangerLegend:
	.string "The full logbook sits framed\n"
	.string "behind the counter now.\p"
	.string "Kids come in just to look at\n"
	.string "your name.$"
