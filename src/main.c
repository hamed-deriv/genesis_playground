#include <genesis.h>
#include <resources.h>

#define STILL_ANIMATION 0
#define IDLE_ANIMATION 1
#define WALK_ANIMATION 2
#define UPPERCUT_ANIMATION 3

const int ATTACK_DURATION = 8 * 7;

void setupBackground(void);
void setParallaxBackground(int scrollSpeedBackground, int scrollSpeedForeground);
void setupPlayerSprite(int x, int y);
void handleInput(Sprite *player, int *x, int *y, u16 joypadNumber);
void handleInputEvents(u16 input, u16 changed, u16 state);
void handleActions(void);

u16 tileIndex = TILE_USER_INDEX;

int horizontalScrollOffsetBackground = 0;
int horizontalScrollOffsetForeground = 0;
int scrollSpeedBackground = 1;
int scrollSpeedForeground = 2;

Sprite *player1;
int player1X = 0;
int player1Y = 75;

int attackTimer = 0;

void main()
{
  setupBackground();

  SPR_init();
  setupPlayerSprite(player1X, player1Y);

  JOY_setEventHandler(handleInputEvents);

  while (1)
  {
    // setParallaxBackground(scrollSpeedBackground, scrollSpeedForeground);

    handleActions();

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

void setupPlayerSprite(int x, int y)
{
  PAL_setPalette(PAL2, alexAnimatedSprite.palette->data, DMA);
  player1 = SPR_addSprite(&alexAnimatedSprite, x, y, TILE_ATTR(PAL2, FALSE, FALSE, TRUE));
}

void handleInput(Sprite *player, int *x, int *y, u16 joypadNumber)
{
  u16 joypadValue = JOY_readJoypad(joypadNumber);

  if (joypadValue & BUTTON_LEFT)
  {
    (*x)--;
    SPR_setAnim(player, WALK_ANIMATION);
    SPR_setHFlip(player, FALSE);
  }
  else if (joypadValue & BUTTON_RIGHT)
  {
    (*x)++;
    SPR_setAnim(player, WALK_ANIMATION);
    SPR_setHFlip(player, TRUE);
  }

  if (joypadValue & BUTTON_UP)
  {
    (*y)--;
    SPR_setAnim(player, WALK_ANIMATION);
  }
  else if (joypadValue & BUTTON_DOWN)
  {
    (*y)++;
    SPR_setAnim(player, WALK_ANIMATION);
  }

  if (!(joypadValue & BUTTON_LEFT) && !(joypadValue & BUTTON_RIGHT) && !(joypadValue & BUTTON_UP) && !(joypadValue & BUTTON_DOWN))
  {
    SPR_setAnim(player, IDLE_ANIMATION);
  }

  SPR_setPosition(player, *x, *y);
}

void handleInputEvents(u16 input, u16 changed, u16 state)
{
  if ((changed & state & BUTTON_B) && !attackTimer)
  {
    SPR_setAnim(player1, UPPERCUT_ANIMATION);

    attackTimer++;
  }
}

void handleActions(void)
{
  if (!attackTimer)
  {
    handleInput(player1, &player1X, &player1Y, JOY_1);
  }
  else if (attackTimer && attackTimer < ATTACK_DURATION)
  {
    attackTimer++;
  }
  else if (attackTimer == ATTACK_DURATION)
  {
    attackTimer = 0;
  }
}
