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

