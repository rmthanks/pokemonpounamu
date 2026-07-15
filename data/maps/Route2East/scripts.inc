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

Route2East_EventScript_PMatiu::
	trainerbattle_single TRAINER_R2E2_MATIU, Route2East_Text_PMatiuIntro, Route2East_Text_PMatiuDefeat
	msgbox Route2East_Text_PMatiuPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PMatiuIntro:
	.string "Matiu: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route2East_Text_PMatiuDefeat:
	.string "The forecast said nothing\nabout you.$"

Route2East_Text_PMatiuPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route2East_EventScript_PPetera::
	trainerbattle_single TRAINER_R2E2_PETERA, Route2East_Text_PPeteraIntro, Route2East_Text_PPeteraDefeat
	msgbox Route2East_Text_PPeteraPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PPeteraIntro:
	.string "Petera: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route2East_Text_PPeteraDefeat:
	.string "The forecast said nothing\nabout you.$"

Route2East_Text_PPeteraPost:
	.string "Southerly's coming. Take care\nup the track.$"

Route2East_EventScript_PRawiri::
	trainerbattle_single TRAINER_R2E2_RAWIRI, Route2East_Text_PRawiriIntro, Route2East_Text_PRawiriDefeat
	msgbox Route2East_Text_PRawiriPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PRawiriIntro:
	.string "Rawiri: This is protected land.\nProve you respect it.$"

Route2East_Text_PRawiriDefeat:
	.string "You fight like you care.$"

Route2East_Text_PRawiriPost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Route2East_EventScript_PTimoti::
	trainerbattle_single TRAINER_R2E2_TIMOTI, Route2East_Text_PTimotiIntro, Route2East_Text_PTimotiDefeat
	msgbox Route2East_Text_PTimotiPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PTimotiIntro:
	.string "Timoti: These paddocks don't run\nthemselves, but the dog helps.$"

Route2East_Text_PTimotiDefeat:
	.string "The dog's still the best\nworker here.$"

Route2East_Text_PTimotiPost:
	.string "Gates SHUT behind you,\nthanks.$"

Route2East_EventScript_PHohepa::
	trainerbattle_single TRAINER_R2E2_HOHEPA, Route2East_Text_PHohepaIntro, Route2East_Text_PHohepaDefeat
	msgbox Route2East_Text_PHohepaPost, MSGBOX_AUTOCLOSE
	end

Route2East_Text_PHohepaIntro:
	.string "Hohepa: Kia ora! Great day for it, eh?\nBattle before the weather turns?$"

Route2East_Text_PHohepaDefeat:
	.string "The forecast said nothing\nabout you.$"

Route2East_Text_PHohepaPost:
	.string "Southerly's coming. Take care\nup the track.$"
