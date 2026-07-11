OtautahiGardenFlat_MapScripts::
	.byte 0

OtautahiGardenFlat_EventScript_GardenLady::
	lock
	faceplayer
	msgbox OtautahiGardenFlat_Text_GardenLady, MSGBOX_DEFAULT
	release
	end

OtautahiGardenFlat_Text_GardenLady:
	.string "Garden City, they call us.\n"
	.string "After the shakes, people\l"
	.string "planted like it was praying.\p"
	.string "Daffodils in the red zone.\n"
	.string "Roses through the fences.\l"
	.string "Things grow back. People too,\l"
	.string "but slower, and never quite\l"
	.string "the same shape.$"

