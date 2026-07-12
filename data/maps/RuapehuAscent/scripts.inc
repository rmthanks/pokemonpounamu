RuapehuAscent_MapScripts::
	.byte 0

RuapehuAscent_EventScript_Descend::
	lockall
	warp MAP_TAUPO, 4, 13
	waitstate
	releaseall
	end

RuapehuAscent_EventScript_ToSummit::
	lockall
	warp MAP_RUAPEHU_SUMMIT, 23, 30
	waitstate
	releaseall
	end
