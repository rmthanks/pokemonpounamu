#!/usr/bin/env python3
"""Toggle the QA-only debug hooks:  python3 tools_pounamu/qa/qa_hooks.py on|off

ON adds a POUNAMU_QA block to src/new_game.c and src/main_menu.c that skips the
opening speech, names the player RYAN, sets all badges, gives the QA party
(test species first, then a Lv100 Kyogre knowing only Surf, or QA_KYOGRE_MOVE), sets the in-game hour and
warps to the spawn in include/qa_spawn.h (written by run.py).
OFF restores both files from git. NEVER commit with the hooks on:
    grep -rn POUNAMU_QA src   # must print nothing before a commit
"""
import os, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
NG, MM = os.path.join(ROOT, 'src/new_game.c'), os.path.join(ROOT, 'src/main_menu.c')

QA_BLOCK = '''#ifdef POUNAMU_QA // QA-ONLY: never commit
    {
        static const u8 sQaName[] = _("RYAN");
        static const u16 sQaParty[] = QA_PARTY;
        static const u16 sQaFlags[] = QA_FLAGS;
        u32 i;
#ifdef QA_KYOGRE_MOVE
        u16 move = QA_KYOGRE_MOVE, none = MOVE_NONE;
#else
        u16 move = MOVE_SURF, none = MOVE_NONE;
#endif
        u8 pp = 15, zero = 0;
        StringCopy(gSaveBlock2Ptr->playerName, sQaName);
        gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
        gSaveBlock2Ptr->optionsBattleSceneOff = TRUE;
        for (i = FLAG_BADGE01_GET; i <= FLAG_BADGE08_GET; i++)
            FlagSet(i);
        FlagSet(FLAG_SYS_POKEMON_GET);
        FlagSet(FLAG_SYS_POKEDEX_GET);
        for (i = 0; i < ARRAY_COUNT(sQaFlags); i++)
            if (sQaFlags[i]) FlagSet(sQaFlags[i]);
        VarSet(VAR_POUNAMU_INTRO_STATE, 6);
#ifdef QA_INTRO
        VarSet(VAR_POUNAMU_INTRO_STATE, QA_INTRO);
#endif
#ifdef QA_DECO
        VarSet(VAR_POUNAMU_DECO_STATE, QA_DECO);
#endif
        for (i = 0; i < ARRAY_COUNT(sQaParty); i++)
            if (sQaParty[i] != SPECIES_NONE) ScriptGiveMon(sQaParty[i], 20, ITEM_NONE);
        ScriptGiveMon(SPECIES_KYOGRE, 100, ITEM_NONE);
        {
            struct Pokemon *k = &gParties[B_TRAINER_PLAYER][CalculatePlayerPartyCount() - 1];
            SetMonData(k, MON_DATA_MOVE1, &move);
            SetMonData(k, MON_DATA_PP1, &pp);
            SetMonData(k, MON_DATA_MOVE2, &none);
            SetMonData(k, MON_DATA_MOVE3, &none);
            SetMonData(k, MON_DATA_MOVE4, &none);
            SetMonData(k, MON_DATA_PP2, &zero);
            SetMonData(k, MON_DATA_PP3, &zero);
            SetMonData(k, MON_DATA_PP4, &zero);
        }
        RtcInitLocalTimeOffset(QA_HOUR, 0);
        SetWarpDestination(MAP_GROUP(QA_MAP), MAP_NUM(QA_MAP), WARP_ID_NONE, QA_X, QA_Y);
        WarpIntoMap();
    }
#endif
'''
INCLUDES = ('#ifdef POUNAMU_QA\n#include "qa_spawn.h"\n#include "script_pokemon_util.h"\n#include "rtc.h"\n'
            '#include "string_util.h"\n#include "constants/moves.h"\n#endif\n')
ANCHOR = ('    if (IS_FRLG)\n        RunScriptImmediately(EventScript_ResetAllMapFlagsFrlg);\n'
          '    else\n        RunScriptImmediately(EventScript_ResetAllMapFlags);\n')
SPEECH = 'static void Task_NewGameBirchSpeech_Init(u8 taskId)\n{\n'
SKIP = ('#ifdef POUNAMU_QA // QA-ONLY: never commit\n    gSaveBlock2Ptr->playerGender = MALE;\n'
        '    SetMainCallback2(CB2_NewGame);\n    DestroyTask(taskId);\n    return;\n#endif\n')
DEFINE = '#define POUNAMU_QA // QA-ONLY: never commit\n'

def on():
    s = open(NG).read()
    if 'POUNAMU_QA' in s:
        return print('already on')
    assert ANCHOR in s and '#include "follower_npc.h"\n' in s
    s = s.replace('#include "follower_npc.h"\n', '#include "follower_npc.h"\n' + INCLUDES, 1)
    s = DEFINE + s.replace(ANCHOR, ANCHOR + QA_BLOCK, 1)
    open(NG, 'w').write(s)
    m = open(MM).read()
    assert SPEECH in m
    open(MM, 'w').write(DEFINE + m.replace(SPEECH, SPEECH + SKIP, 1))
    print('QA hooks ON (remember: qa_hooks.py off before committing)')

def off():
    subprocess.run(['git', 'checkout', '--', 'src/new_game.c', 'src/main_menu.c'], cwd=ROOT, check=True)
    p = os.path.join(ROOT, 'include/qa_spawn.h')
    if os.path.exists(p):
        os.remove(p)
    print('QA hooks OFF')

if __name__ == '__main__':
    {'on': on, 'off': off}[sys.argv[1]]()
