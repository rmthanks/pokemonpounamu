Route2East_MapScripts::
	.byte 0

Route2East_EventScript_Mihi::
	trainerbattle_single TRAINER_R2E_MIHI, Route2East_Text_MihiIntro, Route2East_Text_MihiDefeat
	msgbox Route2East_Text_MihiPost, MSGBOX_AUTOCLOSE
	end

Route2East_EventScript_Hemi::
	trainerbattle_single TRAINER_R2E_HEMI, Route2East_Text_HemiIntro, Route2East_Text_HemiDefeat
	msgbox Route2East_Text_HemiPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_MihiIntro:
	.string "Picnic spot with a view of\n"
	.string "Young Nick's Head!\p"
	.string "You can share it if you can\n"
	.string "beat me for it.$"

Route2East_Text_MihiDefeat:
	.string "Fine! There's plenty of view.$"

Route2East_Text_MihiPost:
	.string "My Hoppip family have ridden\n"
	.string "this coast wind for six\l"
	.string "generations.\p"
	.string "Watch them go. Little legends.$"

Route2East_Text_HemiIntro:
	.string "First light in the whole world\n"
	.string "lands on Turanga!\p"
	.string "Nan says the sun's lazy\n"
	.string "everywhere else. Battle me!$"

Route2East_Text_HemiDefeat:
	.string "Aue! Beaten before breakfast.$"

Route2East_Text_HemiPost:
	.string "If you're chasing the sunrise,\n"
	.string "Hikurangi's the mountain for it.\p"
	.string "But you don't just WALK up\n"
	.string "Hikurangi, eh. It's tapu.$"
