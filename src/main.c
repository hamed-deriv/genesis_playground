#include <genesis.h>
#include <resources.h>

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
  setupPlayerSprite();

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

void setupPlayerSprite(void)
{
  PAL_setPalette(PAL2, sonicSprite.palette->data, DMA);
  player = SPR_addSprite(&sonicSprite, 0, 0, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
}
