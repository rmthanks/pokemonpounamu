// Pokemon Pounamu: the opening before the title screen (Sept 2026).
//
// Night over the Heretaunga plains. The stars go out one by one as dawn comes up
// behind Te Mata o Rongokako, and two great shadows cross the sky together -
// Lugia and Ho-Oh, whole and free (the only time the player sees them so until
// the end; see the threshold rule in the story doc). Then first light, and the
// title rises out of the same view.
//
// Everything reused: the title screen's dawn vista and mist, the game's own
// Lugia and Ho-Oh front sprites (drawn as translucent silhouettes). Only the
// 8x8 star is new. Any button skips, as before.

#include "global.h"
#include "main.h"
#include "decompress.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "intro.h"
#include "m4a.h"
#include "palette.h"
#include "pokemon.h"
#include "pounamu_intro.h"
#include "random.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "task.h"
#include "title_screen.h"
#include "trig.h"
#include "constants/rgb.h"
#include "constants/songs.h"

extern u32 gIntroFrameCounter;

static const u32 sVistaGfx[]     = INCGFX_U32("graphics/title_screen/rayquaza.png", ".4bpp.smol");
static const u32 sVistaTilemap[] = INCGFX_U32("graphics/title_screen/rayquaza.bin", ".smolTM");
static const u32 sMistGfx[]      = INCGFX_U32("graphics/title_screen/clouds.png", ".4bpp.smol");
static const u32 sStarGfx[]      = INCGFX_U32("graphics/intro/pounamu_star.png", ".4bpp");
static const u16 sStarPal[]      = INCGFX_U16("graphics/intro/pounamu_star.png", ".gbapal");

#define VISTA_PAL     14
#define TAG_STAR      0x5E01
#define NUM_STARS     14

// ---- timeline (frames; MUS_INTRO's first phrase runs ~1000) ----
#define T_FADE_IN        0     // up from black into deep night
#define T_DAWN_START    90     // the sky starts to lift
#define T_STARS_GO     240     // stars begin to go out
#define T_SHADOWS      430     // the pair enters, high on the right
#define T_DAWN_END     780     // full colour
#define T_SHADOWS_GONE 900
#define T_FADE_OUT     930     // first light: fade to white, cut to title

static EWRAM_DATA u16 sDawnPal[16] = {0};
static EWRAM_DATA u8 sPicBuf[2][MON_PIC_SIZE * MAX_MON_PIC_FRAMES] = {0};
static EWRAM_DATA struct SpriteFrameImage sPicFrames[2][MAX_MON_PIC_FRAMES] = {0};
static EWRAM_DATA u8 sStars[NUM_STARS] = {0};
static EWRAM_DATA u8 sShadows[2] = {0};
static EWRAM_DATA u16 sMistX = 0;

static void Task_PounamuIntro_Run(u8 taskId);
static void Task_PounamuIntro_End(u8 taskId);

// ---------------------------------------------------------------- stars
static const struct OamData sOam_Star = {
    .shape = SPRITE_SHAPE(8x8), .size = SPRITE_SIZE(8x8), .priority = 2,
};
static const union AnimCmd sAnim_StarSlow[] = {
    ANIMCMD_FRAME(0, 30), ANIMCMD_FRAME(1, 6), ANIMCMD_FRAME(0, 24), ANIMCMD_FRAME(2, 12), ANIMCMD_JUMP(0),
};
static const union AnimCmd sAnim_StarFast[] = {
    ANIMCMD_FRAME(2, 10), ANIMCMD_FRAME(0, 14), ANIMCMD_FRAME(1, 4), ANIMCMD_FRAME(0, 20), ANIMCMD_JUMP(0),
};
static const union AnimCmd *const sAnims_Star[] = { sAnim_StarSlow, sAnim_StarFast };
static const struct SpriteSheet sSpriteSheet_Star = { .data = sStarGfx, .size = 3 * 32, .tag = TAG_STAR };
static const struct SpritePalette sSpritePal_Star = { .data = sStarPal, .tag = TAG_STAR };
static const struct SpriteTemplate sSpriteTemplate_Star = {
    .tileTag = TAG_STAR, .paletteTag = TAG_STAR, .oam = &sOam_Star, .anims = sAnims_Star,
    .images = NULL, .affineAnims = gDummySpriteAffineAnimTable, .callback = SpriteCallbackDummy,
};

// ---------------------------------------------------------------- the two shadows
static const struct OamData sOam_Shadow = {
    .affineMode = ST_OAM_AFFINE_DOUBLE, .objMode = ST_OAM_OBJ_BLEND,
    .shape = SPRITE_SHAPE(64x64), .size = SPRITE_SIZE(64x64), .priority = 1,
};

static u8 CreateShadow(u32 which, u16 species)
{
    u32 i;
    u8 spriteId;
    struct SpriteTemplate t = {
        .tileTag = TAG_NONE, .paletteTag = TAG_NONE, .oam = &sOam_Shadow,
        .anims = gSpeciesInfo[species].frontAnimFrames, .images = sPicFrames[which],
        .affineAnims = gDummySpriteAffineAnimTable, .callback = SpriteCallbackDummy,
    };
    LoadSpecialPokePic(sPicBuf[which], species, 0, TRUE);
    for (i = 0; i < MAX_MON_PIC_FRAMES; i++)
    {
        sPicFrames[which][i].data = sPicBuf[which] + MON_PIC_SIZE * i;
        sPicFrames[which][i].size = MON_PIC_SIZE;
    }
    spriteId = CreateSprite(&t, -128, -128, 1 + which);
    gSprites[spriteId].oam.paletteNum = 0;          // the shadow palette: one flat dark blue
    gSprites[spriteId].affineAnimBeginning = FALSE;
    gSprites[spriteId].affineAnimPaused = TRUE;
    gSprites[spriteId].invisible = TRUE;
    CalcCenterToCornerVec(&gSprites[spriteId], SPRITE_SHAPE(64x64), SPRITE_SIZE(64x64), ST_OAM_AFFINE_DOUBLE);
    return spriteId;
}

// place a shadow along its flight: t runs 0..256 across the sky
static void FlyShadow(u8 spriteId, s32 t, s32 lag, s32 dy, s32 scaleStart, s32 scaleEnd)
{
    struct Sprite *s = &gSprites[spriteId];
    s32 scale;
    t -= lag;
    if (t < 0 || t > 256)
    {
        s->invisible = TRUE;
        return;
    }
    s->invisible = FALSE;
    // enter high on the right, glide west and a little lower, receding toward the ridge
    s->x = 310 - (t * 400) / 256;
    s->y = 22 + dy + (t * 34) / 256 + Sin((gIntroFrameCounter * 3 + lag * 8) & 0xFF, 4);
    scale = scaleStart + ((scaleEnd - scaleStart) * t) / 256;      // 256 = 1x
    SetOamMatrix(s->oam.matrixNum, (256 * 256) / scale, 0, 0, (256 * 256) / scale);
}

// ---------------------------------------------------------------- the sky
// night 0..256: 256 is deep night, 0 the dawn vista as painted
static void SetNight(s32 night)
{
    u32 i;
    for (i = 1; i < 16; i++)
    {
        u16 c = sDawnPal[i];
        s32 r = GET_R(c), g = GET_G(c), b = GET_B(c);
        s32 nr = r / 6, ng = g / 5 + 1, nb = b / 3 + 5;       // cool and dark, not grey
        if (nb > 31)
            nb = 31;
        r += ((nr - r) * night) >> 8;
        g += ((ng - g) * night) >> 8;
        b += ((nb - b) * night) >> 8;
        gPlttBufferUnfaded[BG_PLTT_ID(VISTA_PAL) + i] = RGB(r, g, b);
        if (!gPaletteFade.active)
            gPlttBufferFaded[BG_PLTT_ID(VISTA_PAL) + i] = RGB(r, g, b);
    }
}

static s32 Ease(s32 t, s32 t0, s32 t1)   // smoothstep, 0..256
{
    s32 x;
    if (t <= t0)
        return 0;
    if (t >= t1)
        return 256;
    x = ((t - t0) * 256) / (t1 - t0);
    return (x * x * (768 - 2 * x)) >> 16;
}

static void VBlankCB_PounamuIntro(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    SetGpuReg(REG_OFFSET_BG1HOFS, sMistX >> 3);
}

// ---------------------------------------------------------------- tasks
void Task_PounamuIntro_Load(u8 taskId)
{
    u32 i;
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0); SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0); SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
    DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
    DmaFill16(3, 0, (void *)(PLTT + 2), PLTT_SIZE - 2);
    ScanlineEffect_Stop();
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetPaletteFade();

    DecompressDataWithHeaderVram(sVistaGfx, (void *)BG_CHAR_ADDR(2));
    DecompressDataWithHeaderVram(sVistaTilemap, (void *)BG_SCREEN_ADDR(26));
    DecompressDataWithHeaderVram(sMistGfx, (void *)BG_CHAR_ADDR(3));
    DecompressDataWithHeaderVram(gTitleScreenCloudsTilemap, (void *)BG_SCREEN_ADDR(27));
    LoadPalette(gTitleScreenBgPalettes, BG_PLTT_ID(0), 15 * PLTT_SIZE_4BPP);
    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(VISTA_PAL)], sDawnPal, sizeof(sDawnPal));
    SetNight(256);
    SetGpuReg(REG_OFFSET_BG3CNT, BGCNT_PRIORITY(3) | BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(26) | BGCNT_16COLOR | BGCNT_TXT256x256);
    SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(2) | BGCNT_CHARBASE(3) | BGCNT_SCREENBASE(27) | BGCNT_16COLOR | BGCNT_TXT256x256);
    // mist and shadows are translucent over the vista
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG3);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(10, 9));

    // the shadow palette: every colour the same deep night blue
    for (i = 1; i < 16; i++)
        gPlttBufferUnfaded[OBJ_PLTT_ID(0) + i] = RGB(3, 3, 10);
    CpuCopy16(&gPlttBufferUnfaded[OBJ_PLTT_ID(0)], &gPlttBufferFaded[OBJ_PLTT_ID(0)], PLTT_SIZE_4BPP);
    sShadows[0] = CreateShadow(0, SPECIES_LUGIA);
    sShadows[1] = CreateShadow(1, SPECIES_HO_OH);

    gReservedSpritePaletteCount = 1;                 // slot 0 is the shadows'
    LoadSpriteSheet(&sSpriteSheet_Star);
    LoadSpritePalette(&sSpritePal_Star);
    for (i = 0; i < NUM_STARS; i++)
    {
        sStars[i] = CreateSprite(&sSpriteTemplate_Star, 6 + (Random() % 228), 4 + (Random() % 52), 3);
        StartSpriteAnim(&gSprites[sStars[i]], Random() & 1);
        gSprites[sStars[i]].animDelayCounter = Random() % 30;
    }

    sMistX = 0;
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetVBlankCallback(VBlankCB_PounamuIntro);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG1_ON | DISPCNT_BG3_ON | DISPCNT_OBJ_ON);
    gIntroFrameCounter = 0;
    m4aSongNumStart(MUS_INTRO);
    gTasks[taskId].func = Task_PounamuIntro_Run;
}

static void Task_PounamuIntro_Run(u8 taskId)
{
    u32 f = gIntroFrameCounter, i;
    s32 dawn = Ease(f, T_DAWN_START, T_DAWN_END);

    sMistX++;
    SetNight(256 - dawn);

    // stars go out as the sky lifts, a few at a time
    if (f >= T_STARS_GO)
    {
        for (i = 0; i < NUM_STARS; i++)
        {
            if (!gSprites[sStars[i]].invisible && (u32)((dawn * NUM_STARS) >> 8) > i)
                gSprites[sStars[i]].invisible = TRUE;
        }
    }

    // the pair: Lugia leads, Ho-Oh a wingbeat behind and a little higher
    if (f >= T_SHADOWS)
    {
        s32 t = ((f - T_SHADOWS) * 256) / (T_SHADOWS_GONE - T_SHADOWS);
        FlyShadow(sShadows[0], t, 0, 6, 340, 150);
        FlyShadow(sShadows[1], t, 56, -14, 290, 120);
        if ((f - T_SHADOWS) % 96 == 0)
        {
            StartSpriteAnim(&gSprites[sShadows[0]], 0);     // replay the front animation: a wingbeat
            StartSpriteAnim(&gSprites[sShadows[1]], 0);
        }
    }

    if (f >= T_FADE_OUT && !gPaletteFade.active)
    {
        BeginNormalPaletteFade(PALETTES_ALL, 4, 0, 16, RGB_WHITEALPHA);
        gTasks[taskId].func = Task_PounamuIntro_End;
    }
}

static void Task_PounamuIntro_End(u8 taskId)
{
    sMistX++;
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        SetMainCallback2(CB2_InitTitleScreen);
    }
}
