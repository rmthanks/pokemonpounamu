TamakiApartmentsLobby_MapScripts::
	.byte 0

TamakiApartmentsLobby_EventScript_Concierge::
	lock
	faceplayer
	msgbox TamakiApartmentsLobby_Text_Concierge, MSGBOX_DEFAULT
	release
	end

TamakiApartmentsLobby_Text_Concierge:
	.string "Harbourview Apartments.\n"
	.string "...You're not a resident.\l"
	.string "You're not HIS, either.\p"
	.string "Then listen fast: the tower\n"
	.string "changed hands and the whole\l"
	.string "Sky went private. Bay suits\l"
	.string "on every floor.\p"
	.string "The E4? Nobody's seen them.\n"
	.string "The Champion? Gone quiet.\l"
	.string "This city is holding its\l"
	.string "breath, kid.$"

TamakiApartmentsLobby_EventScript_RichKid::
	lock
	faceplayer
	msgbox TamakiApartmentsLobby_Text_RichKid, MSGBOX_DEFAULT
	release
	end

TamakiApartmentsLobby_Text_RichKid:
	.string "Daddy says the new tower\n"
	.string "management 'renegotiated' his\l"
	.string "marina berth.\p"
	.string "He didn't negotiate anything.\n"
	.string "He just paid. Everyone just\l"
	.string "pays now.$"

