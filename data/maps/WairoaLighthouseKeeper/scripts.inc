WairoaLighthouseKeeper_MapScripts::
	.byte 0

WairoaLighthouseKeeper_EventScript_Keeper::
	lock
	faceplayer
	msgbox WairoaLighthouseKeeper_Text_Keeper, MSGBOX_DEFAULT
	release
	end

WairoaLighthouseKeeper_Text_Keeper:
	.string "Kept the old lighthouse forty\n"
	.string "years. Now it sits in town\l"
	.string "like a retired soldier.\p"
	.string "A light doesn't choose who it\n"
	.string "saves. Worth thinking about,\l"
	.string "the company you're headed for.$"

