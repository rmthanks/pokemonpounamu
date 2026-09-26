// Pounamu QA harness: headless mGBA driven by a tiny command script.
// Build: see qa/build_harness.sh. Usage: harness ROM SCRIPT OUTDIR [RTC_UNIX_SECONDS]
//   run N            advance N frames, no keys
//   tap K [N]        press key K for 4 frames then release for 12 (N times)
//   hold K N         hold K for N frames, then release
//   mash K N GAP     tap K N times with GAP idle frames between
//   shot NAME        write OUTDIR/NAME.ppm
// Keys: A B SELECT START RIGHT LEFT UP DOWN R L
#include <mgba/flags.h>
#include <mgba/core/core.h>
#include <mgba/core/interface.h>
#include <mgba/core/log.h>
#include <mgba-util/vfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct mCore* core;
static uint32_t* fb;
static unsigned W, H;
static const char* outdir;

static void quiet(struct mLogger* l, int c, enum mLogLevel lv, const char* f, va_list a) {
	(void) l; (void) c; (void) lv; (void) f; (void) a;
}
static struct mLogger logger = { .log = quiet };

static int keybit(const char* k) {
	static const char* names[] = { "A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN", "R", "L" };
	for (int i = 0; i < 10; ++i) if (!strcmp(k, names[i])) return 1 << i;
	fprintf(stderr, "bad key %s\n", k); exit(2);
}

static void frames(int n, int keys) {
	core->setKeys(core, keys);
	for (int i = 0; i < n; ++i) core->runFrame(core);
	core->setKeys(core, 0);
}

static void shot(const char* name) {
	char p[512];
	snprintf(p, sizeof p, "%s/%s.ppm", outdir, name);
	FILE* f = fopen(p, "wb");
	fprintf(f, "P6 %u %u 255\n", W, H);
	for (unsigned i = 0; i < W * H; ++i) {
		uint32_t c = fb[i];
		unsigned char px[3] = { c & 0xFF, (c >> 8) & 0xFF, (c >> 16) & 0xFF };
		fwrite(px, 1, 3, f);
	}
	fclose(f);
}

int main(int argc, char** argv) {
	if (argc < 4) { fprintf(stderr, "usage: harness ROM SCRIPT OUTDIR [RTC]\n"); return 1; }
	outdir = argv[3];
	mLogSetDefaultLogger(&logger);
	core = mCoreFind(argv[1]);
	if (!core || !core->init(core)) { fprintf(stderr, "no core\n"); return 1; }
	mCoreInitConfig(core, NULL);
	core->baseVideoSize(core, &W, &H);
	fb = calloc(W * H, 4);
	core->setVideoBuffer(core, (mColor*) fb, W);
	if (!mCoreLoadFile(core, argv[1])) { fprintf(stderr, "load failed\n"); return 1; }
	if (argc > 4) {
		core->rtc.override = RTC_FIXED;
		core->rtc.value = atoll(argv[4]) * 1000LL; // mGBA expects milliseconds
	}
	core->reset(core);

	FILE* s = fopen(argv[2], "r");
	char line[256];
	while (fgets(line, sizeof line, s)) {
		char cmd[32], a[64] = "", b[32] = "", c[32] = "";
		if (sscanf(line, "%31s %63s %31s %31s", cmd, a, b, c) < 1 || cmd[0] == '#') continue;
		if (!strcmp(cmd, "run")) frames(atoi(a), 0);
		else if (!strcmp(cmd, "tap")) {
			int n = b[0] ? atoi(b) : 1;
			for (int i = 0; i < n; ++i) { frames(4, keybit(a)); frames(12, 0); }
		}
		else if (!strcmp(cmd, "hold")) frames(atoi(b), keybit(a));
		else if (!strcmp(cmd, "mash")) {
			for (int i = 0; i < atoi(b); ++i) { frames(4, keybit(a)); frames(atoi(c), 0); }
		}
		else if (!strcmp(cmd, "shot")) shot(a);
		else if (!strcmp(cmd, "steps")) { // steps KEY N PREFIX: tap, wait 50, shot, N times
			static int seq = 0;
			for (int i = 0; i < atoi(b); ++i) {
				char nm[96];
				frames(4, keybit(a)); frames(50, 0);
				snprintf(nm, sizeof nm, "%s_%02d", c, seq++);
				shot(nm);
			}
		}
	}
	fclose(s);
	core->deinit(core);
	return 0;
}
