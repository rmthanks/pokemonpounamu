Taupo_MapScripts::
	.byte 0

Taupo_EventScript_LakeMan::
	msgbox Taupo_Text_LakeMan, MSGBOX_NPC
	end

Taupo_EventScript_StreetWoman::
	msgbox Taupo_Text_StreetWoman, MSGBOX_NPC
	end

Taupo_EventScript_GateOldMan::
	msgbox Taupo_Text_GateOldMan, MSGBOX_NPC
	end

Taupo_EventScript_Kid::
	msgbox Taupo_Text_Kid, MSGBOX_NPC
	end

Taupo_EventScript_LakeSign::
	msgbox Taupo_Text_LakeSign, MSGBOX_SIGN
	end

Taupo_Text_LakeMan:
	.string "The lake is the crater of\n"
	.string "something enormous and asleep.\p"
	.string "Best fishing in the world,\n"
	.string "right on top of it.\p"
	.string "…We don't think about it much.$"

Taupo_Text_StreetWoman:
	.string "Everything south of here is\n"
	.string "mountains and weather.\p"
	.string "Everything east is home for\n"
	.string "somebody.\p"
	.string "…You looked east just then.$"

Taupo_Text_GateOldMan:
	.string "That road east goes over the\n"
	.string "ranges to Ahuriri. Three days,\l"
	.string "beautiful the whole way.\p"
	.string "The Mob shut it overnight. No\n"
	.string "notice, no reason given.\p"
	.string "…Some folk out there just want\n"
	.string "to keep a door shut, eh.$"

Taupo_Text_Kid:
	.string "I skimmed a stone THIRTEEN times\n"
	.string "on the lake!\p"
	.string "Then something skimmed it back.$"

Taupo_Text_LakeSign:
	.string "LAKE TAUPO\p"
	.string "“The heart of the fish.”$"
