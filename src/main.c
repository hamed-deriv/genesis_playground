#include <genesis.h>
#include <resources.h>

int main()
{
    u16 index = TILE_USER_INDEX;

    PAL_setPalette(PAL0, alleyBackground.palette->data, DMA);
    VDP_drawImageEx(BG_B, &alleyBackground, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, index), 0, 0, FALSE, TRUE);

    while (1)
    {
        VDP_waitVSync();
    }

    return (0);
}
