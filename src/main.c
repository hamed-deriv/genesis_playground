#include <genesis.h>
#include <resources.h>

int main()
{
    u16 tileIndex = TILE_USER_INDEX;
    PAL_setPalette(PAL0, alleyBackground.palette->data, DMA);
    VDP_drawImageEx(BG_B, &alleyBackground, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tileIndex), 0, 0, FALSE, TRUE);

    tileIndex += alleyBackground.tileset->numTile;
    PAL_setPalette(PAL1, alleyForeground.palette->data, DMA);
    VDP_drawImageEx(BG_A, &alleyForeground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, tileIndex), 0, 0, FALSE, TRUE);

    tileIndex += alleyForeground.tileset->numTile;

    while (1)
    {
        SYS_doVBlankProcess();
    }

    return (0);
}
