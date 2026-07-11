HeretaungaOrchardCottage_MapScripts::
	.byte 0

HeretaungaOrchardCottage_EventScript_Picker::
	lock
	faceplayer
	msgbox HeretaungaOrchardCottage_Text_Picker, MSGBOX_DEFAULT
	release
	end

HeretaungaOrchardCottage_Text_Picker:
	.string "Picking season never really\n"
	.string "ends around here.\p"
	.string "Miss Rata pays fair and asks\n"
	.string "nothing but honest work.\l"
	.string "Not everyone in this town can\l"
	.string "say that.$"

HeretaungaOrchardCottage_EventScript_Kid::
	lock
	faceplayer
	msgbox HeretaungaOrchardCottage_Text_Kid, MSGBOX_DEFAULT
	release
	end

HeretaungaOrchardCottage_Text_Kid:
	.string "The queen bee lives behind the\n"
	.string "big homestead!\p"
	.string "Dad says if she ever stops\n"
	.string "flying, the whole orchard\l"
	.string "stops with her.$"

