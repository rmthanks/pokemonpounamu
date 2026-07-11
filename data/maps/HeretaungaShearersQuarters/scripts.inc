HeretaungaShearersQuarters_MapScripts::
	.byte 0

HeretaungaShearersQuarters_EventScript_Shearer::
	lock
	faceplayer
	msgbox HeretaungaShearersQuarters_Text_Shearer, MSGBOX_DEFAULT
	release
	end

HeretaungaShearersQuarters_Text_Shearer:
	.string "Shore sheep from Wairoa to\n"
	.string "Waipukurau in my day.\p"
	.string "These hands have more scars\n"
	.string "than your Pokedex has pages,\l"
	.string "and I'm proud of every one.$"

