#include <genesis.h>
#include <resources.h>

#define STILL_ANIMATION 0
#define IDLE_ANIMATION 1
#define WALK_ANIMATION 2
#define UPPERCUT_ANIMATION 3

u16 tileIndex = TILE_USER_INDEX;

int horizontalScrollOffsetBackground = 0;
int horizontalScrollOffsetForeground = 0;
int scrollSpeedBackground = 1;
int scrollSpeedForeground = 2;

Sprite *player;

void main(void)
{
  setupBackground();

  SPR_init();
  setupPlayerSprite(WALK_ANIMATION);

  while (1)
  {
    setParallaxBackground(scrollSpeedBackground, scrollSpeedForeground);

    SPR_update();
    SYS_doVBlankProcess();
  }
}

void setupBackground(void)
{
  PAL_setPalette(PAL0, sonicBackground.palette->data, DMA);
  VDP_drawImageEx(BG_B, &sonicBackground, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tileIndex), 0, -4, FALSE, TRUE);

  tileIndex += sonicBackground.tileset->numTile;
  PAL_setPalette(PAL1, sonicForeground.palette->data, DMA);
  VDP_drawImageEx(BG_A, &sonicForeground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, tileIndex), 0, -4, FALSE, TRUE);

  VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
}

void setParallaxBackground(int scrollSpeedBackground, int scrollSpeedForeground)
{
  VDP_setHorizontalScroll(BG_B, horizontalScrollOffsetBackground -= scrollSpeedBackground);
  VDP_setHorizontalScroll(BG_A, horizontalScrollOffsetForeground -= scrollSpeedForeground);
}

void setupPlayerSprite(int animation)
{
  PAL_setPalette(PAL2, alexAnimatedSprite.palette->data, DMA);
  player = SPR_addSprite(&alexAnimatedSprite, 0, 75, TILE_ATTR(PAL2, FALSE, FALSE, TRUE));

  SPR_setAnim(player, animation);
}
