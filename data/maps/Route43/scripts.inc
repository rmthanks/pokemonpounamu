Route43_MapScripts::
	.byte 0

Route43_EventScript_Wai::
	trainerbattle_single TRAINER_R43_WAI, Route43_Text_WaiIntro, Route43_Text_WaiDefeat
	msgbox Route43_Text_WaiPost, MSGBOX_AUTOCLOSE
	end

Route43_Text_WaiIntro:
	.string "They call this the Forgotten\n"
	.string "World Highway.\p"
	.string "One lane, one tunnel, one very\n"
	.string "confused Swablu. Battle!$"

Route43_Text_WaiDefeat:
	.string "Lost in the fog…$"

Route43_Text_WaiPost:
	.string "Ngamotu's at the end of the\n"
	.string "road, under the mountain.\p"
	.string "You can't miss the mountain.\n"
	.string "Believe me.$"

Route43_EventScript_PRiley::
	trainerbattle_single TRAINER_R43P_RILEY, Route43_Text_PRileyIntro, Route43_Text_PRileyDefeat
	msgbox Route43_Text_PRileyPost, MSGBOX_AUTOCLOSE
	end

Route43_Text_PRileyIntro:
	.string "Riley: This is protected land.\nProve you respect it.$"

Route43_Text_PRileyDefeat:
	.string "You fight like you care.$"

Route43_Text_PRileyPost:
	.string "The birds come back when\nthe stoats go. Remember that.$"

Route43_EventScript_PRuby::
	trainerbattle_single TRAINER_R43P_RUBY, Route43_Text_PRubyIntro, Route43_Text_PRubyDefeat
	msgbox Route43_Text_PRubyPost, MSGBOX_AUTOCLOSE
	end

Route43_Text_PRubyIntro:
	.string "Ruby: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route43_Text_PRubyDefeat:
	.string "You earned the view.$"

Route43_Text_PRubyPost:
	.string "One more ridge. There's always\none more ridge.$"

Route43_EventScript_PSam::
	trainerbattle_single TRAINER_R43P_SAM, Route43_Text_PSamIntro, Route43_Text_PSamDefeat
	msgbox Route43_Text_PSamPost, MSGBOX_AUTOCLOSE
	end

Route43_Text_PSamIntro:
	.string "Sam: I've tramped every track in\nthis region. Fight me.$"

Route43_Text_PSamDefeat:
	.string "Blisters AND a loss. Ka pai.$"

Route43_Text_PSamPost:
	.string "The huts are full this weekend.\nBook ahead, e hoa.$"

Route43_EventScript_PSophie::
	trainerbattle_single TRAINER_R43P_SOPHIE, Route43_Text_PSophieIntro, Route43_Text_PSophieDefeat
	msgbox Route43_Text_PSophiePost, MSGBOX_AUTOCLOSE
	end

Route43_Text_PSophieIntro:
	.string "Sophie: My mokopuna says I'm out of\ndate. Let's test that.$"

Route43_Text_PSophieDefeat:
	.string "Tell no one.$"

Route43_Text_PSophiePost:
	.string "Old tricks are just good\ntricks that lasted.$"

Route43_EventScript_PThomas::
	trainerbattle_single TRAINER_R43P_THOMAS, Route43_Text_PThomasIntro, Route43_Text_PThomasDefeat
	msgbox Route43_Text_PThomasPost, MSGBOX_AUTOCLOSE
	end

Route43_Text_PThomasIntro:
	.string "Thomas: Oi! You walked into my line\nof sight. Them's the rules!$"

Route43_Text_PThomasDefeat:
	.string "Aw, heck!$"

Route43_Text_PThomasPost:
	.string "Mum says losing builds\ncharacter. I'm SO strong now.$"

Route43_EventScript_PTyler::
	trainerbattle_single TRAINER_R43P_TYLER, Route43_Text_PTylerIntro, Route43_Text_PTylerDefeat
	msgbox Route43_Text_PTylerPost, MSGBOX_AUTOCLOSE
	end

Route43_Text_PTylerIntro:
	.string "Tyler: Shortcut? There's no shortcut.\nThere's only the long way.$"

Route43_Text_PTylerDefeat:
	.string "You earned the view.$"

Route43_Text_PTylerPost:
	.string "One more ridge. There's always\none more ridge.$"

Route43_EventScript_PWillow::
	trainerbattle_single TRAINER_R43P_WILLOW, Route43_Text_PWillowIntro, Route43_Text_PWillowDefeat
	msgbox Route43_Text_PWillowPost, MSGBOX_AUTOCLOSE
	end

Route43_Text_PWillowIntro:
	.string "Willow: You've got badges. I've got\nstandards. Let's see.$"

Route43_Text_PWillowDefeat:
	.string "Standards met.$"

Route43_Text_PWillowPost:
	.string "The League's tougher than me.\nBarely.$"
