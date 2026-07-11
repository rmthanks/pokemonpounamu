TamakiMarketHouse_MapScripts::
	.byte 0

TamakiMarketHouse_EventScript_MarketMum::
	lock
	faceplayer
	msgbox TamakiMarketHouse_Text_MarketMum, MSGBOX_DEFAULT
	release
	end

TamakiMarketHouse_Text_MarketMum:
	.string "Markets still run Sunday.\n"
	.string "Best pineapple pies south of\l"
	.string "the islands, no exceptions.\p"
	.string "The suits tried a 'stall fee'\n"
	.string "once. Once. Aunty Vai spoke\l"
	.string "to them in the old language.\l"
	.string "All five feet of her.$"

