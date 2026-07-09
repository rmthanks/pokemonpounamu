RotoruaGym_MapScripts::
	.byte 0

@ ------------------------------------------------------------------
@ Whenua - Ground. The land here breathes. Badge 3.
@ ------------------------------------------------------------------
RotoruaGym_EventScript_Whenua::
	lock
	faceplayer
	goto_if_set FLAG_BADGE03_GET, RotoruaGym_EventScript_WhenuaRetalk
	goto_if_unset FLAG_BADGE02_GET, RotoruaGym_EventScript_WhenuaNoBadge
	msgbox RotoruaGym_Text_WhenuaPreBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WHENUA, RotoruaGym_Text_WhenuaDefeat
	msgbox RotoruaGym_Text_WhenuaBadgeSpeech, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message RotoruaGym_Text_ReceivedNgawhaBadge
	waitfanfare
	waitmessage
	setflag FLAG_BADGE03_GET
	msgbox RotoruaGym_Text_WhenuaAfter, MSGBOX_DEFAULT
	release
	end

RotoruaGym_EventScript_WhenuaNoBadge::
	msgbox RotoruaGym_Text_WhenuaNoBadge, MSGBOX_DEFAULT
	release
	end

RotoruaGym_EventScript_WhenuaRetalk::
	msgbox RotoruaGym_Text_WhenuaRetalk, MSGBOX_DEFAULT
	release
	end

RotoruaGym_EventScript_Prospect::
	trainerbattle_single TRAINER_ROTORUA_PROSPECT, RotoruaGym_Text_ProspectIntro, RotoruaGym_Text_ProspectDefeat
	msgbox RotoruaGym_Text_ProspectPost, MSGBOX_AUTOCLOSE
	end

@ ------------------------- text -------------------------
RotoruaGym_Text_WhenuaNoBadge:
	.string "Whenua: Slow down, koro's egg.\p"
	.string "The land tells me you've got two\n"
	.string "badges and a long road behind\l"
	.string "you… but the mud takes trainers\l"
	.string "in ORDER.\p"
	.string "…You have two? Good.\n"
	.string "Then why am I still talking?$"

RotoruaGym_Text_WhenuaPreBattle:
	.string "Whenua: Feel that, under your\n"
	.string "boots?\p"
	.string "The whole city sits on a heart\n"
	.string "that never stopped beating.\p"
	.string "I train what the land gives me.\n"
	.string "Mud. Steam. Patience.\p"
	.string "Show me what the road gave YOU.$"

RotoruaGym_Text_WhenuaDefeat:
	.string "…Ha!\p"
	.string "The land approves.\n"
	.string "I felt it.$"

RotoruaGym_Text_WhenuaBadgeSpeech:
	.string "Whenua: You fight like someone\n"
	.string "with nothing to go home to.\p"
	.string "…That's not a compliment, kid.\n"
	.string "But it's not nothing, either.$"

RotoruaGym_Text_ReceivedNgawhaBadge:
	.string "{PLAYER} received the Ngawha Badge\n"
	.string "from Whenua!$"

RotoruaGym_Text_WhenuaAfter:
	.string "Whenua: Third of eight.\p"
	.string "Mua's next - the fishing brother,\n"
	.string "down in Tauranga. All salt and\l"
	.string "sunshine, that one.\p"
	.string "…And when you take the lake road\n"
	.string "south, look east at Taupo.\p"
	.string "You'll see something that hurts.\n"
	.string "Look anyway.$"

RotoruaGym_Text_WhenuaRetalk:
	.string "Whenua: The mud remembers\n"
	.string "everyone who's ever stood in it.\p"
	.string "You're in there now. Forever.\n"
	.string "…Sorry about your shoes.$"

RotoruaGym_Text_ProspectIntro:
	.string "I bathe my team in the hot pools\n"
	.string "every night!\p"
	.string "Toughest skin in the North\n"
	.string "Island. Feel free to check!$"

RotoruaGym_Text_ProspectDefeat:
	.string "Boiled over…$"

RotoruaGym_Text_ProspectPost:
	.string "Whenua says the ground never\n"
	.string "lies.\p"
	.string "She also says my Slugma sleeps\n"
	.string "in her good pool. Also true.$"
