# Pounamu QA harness

Headless emulator testing for scripted content: spawn next to an NPC with a test
party, press buttons, get screenshots. Built on libmgba.

## One-time setup (per session; ~5 min)

```sh
git clone --depth 1 https://github.com/mgba-emu/mgba.git ~/mgba-src
apt-get install -y cmake libpng-dev zlib1g-dev pkg-config
cd ~/mgba-src && mkdir build && cd build
cmake .. -DBUILD_QT=OFF -DBUILD_SDL=OFF -DUSE_FFMPEG=OFF -DUSE_LIBZIP=OFF -DUSE_SQLITE3=OFF \
  -DUSE_ELF=OFF -DUSE_LUA=OFF -DUSE_EDITLINE=OFF -DUSE_DISCORD_RPC=OFF -DBUILD_GL=OFF \
  -DBUILD_GLES2=OFF -DBUILD_GLES3=OFF -DUSE_EPOXY=OFF -DENABLE_SCRIPTING=OFF -DM_CORE_GB=OFF \
  -DBUILD_SHARED=OFF -DBUILD_STATIC=ON -DCMAKE_BUILD_TYPE=Release
make -j2 mgba
# compile the harness with the SAME defines libmgba used, or struct mCore's
# layout differs and core->init is a null pointer (segfault on start):
M=~/mgba-src; D="$(grep -h C_DEFINES $M/build/CMakeFiles/mgba.dir/flags.make | cut -d= -f2)"
gcc -O2 $D -o tools_pounamu/qa/harness tools_pounamu/qa/harness.c \
  -I$M/include -I$M/build/include $M/build/libmgba.a -lpng -lz -lm -lpthread
```

## Running a test

```sh
python3 tools_pounamu/qa/qa_hooks.py on     # adds the POUNAMU_QA debug spawn
python3 tools_pounamu/qa/run.py hooks        # builds, runs, writes qa/out/hooks/*.png
python3 tools_pounamu/qa/sheet.py tools_pounamu/qa/out/hooks   # contact sheet
python3 tools_pounamu/qa/qa_hooks.py off    # ALWAYS before committing
```

Tests live in `run.py` (`TESTS`): map, spawn tile, in-game hour, flags to
preset (trainer flags work: `TRAINER_FLAGS_START + TRAINER_X`), test party, and
a command script. Harness commands: `run N`, `tap K [N]`, `hold K N`,
`mash K N GAP`, `shot NAME`, and `steps K N PREFIX` (press, wait 50 frames,
screenshot, N times; the reliable way to walk through dialogue).

## Lessons (Sept 2026)

- Party menus fade in slowly: prefer putting the species under test in slot 0
  and pressing A, over navigating with DOWN.
- NPCs with WANDER movement will dodge a spawn-and-talk test; pin them in a
  throwaway edit of map.json for the test build only, then restore.
- Don't spawn inside an existing trainer's sightline (Ahuriri's gentleman at
  36,26 hijacked the first Wharf Rats run).
- A long fanfare (e.g. receiving a Pokemon) swallows several A presses.
- mGBA RTC override wants milliseconds; the in-game hour is set separately by
  QA_HOUR via RtcInitLocalTimeOffset.
