OtautahiIsite_MapScripts::
	.byte 0

OtautahiIsite_EventScript_SouthRanger::
	lock
	faceplayer
	msgbox OtautahiIsite_Text_SouthRanger, MSGBOX_DEFAULT
	release
	end

OtautahiIsite_Text_SouthRanger:
	.string "South Island i-SITE, kia ora.\n"
	.string "Aoraki passes, garden maps,\l"
	.string "rebuild tours.\p"
	.string "The road to the glacier country\n"
	.string "asks more than it used to.\l"
	.string "Go acclimatised, go insured,\l"
	.string "go with someone who knows.$"

