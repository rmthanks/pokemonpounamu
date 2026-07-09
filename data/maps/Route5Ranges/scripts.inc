Route5Ranges_MapScripts::
	.byte 0

@ ------------------------------------------------------------------
@ The exemplar gate. You can SEE the road home. You cannot take it.
@ ------------------------------------------------------------------
Route5Ranges_EventScript_Grunt1::
	lock
	faceplayer
	msgbox Route5Ranges_Text_Grunt1, MSGBOX_DEFAULT
	release
	end

Route5Ranges_EventScript_Grunt2::
	lock
	faceplayer
	msgbox Route5Ranges_Text_Grunt2, MSGBOX_DEFAULT
	release
	end

Route5Ranges_EventScript_Sign::
	msgbox Route5Ranges_Text_Sign, MSGBOX_SIGN
	end

Route5Ranges_Text_Grunt1:
	.string "…You.\p"
	.string "We know your face. You're ON\n"
	.string "the list. THE list.\p"
	.string "The Bay doesn't know you any\n"
	.string "more, remember?$"

Route5Ranges_Text_Grunt2:
	.string "Road's right there, eh.\p"
	.string "Ahuriri. Three days over the\n"
	.string "ranges. Prettiest walk in the\l"
	.string "North Island.\p"
	.string "…For everyone except you.\p"
	.string "Boss's little sibling walks the\n"
	.string "LONG way. Boss was very clear.$"

Route5Ranges_Text_Sign:
	.string "ROUTE 5 EAST\n"
	.string "AHURIRI via the Titiokura ranges.\p"
	.string "A handwritten note is nailed\n"
	.string "underneath:\p"
	.string "“CLOSED. Bay business.\n"
	.string "Don't ask.”$"
