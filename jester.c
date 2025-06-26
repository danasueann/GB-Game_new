#include <gb/gb.h>
#include "jester.h"
#include "sprites/jester_sprite.h"

void setup_jester(int start_x, int start_y)
{

    set_sprite_data(32, jester_size, jester);

    for (int i = 0; i < jester_size; i++)
    {
        set_sprite_tile(i+16, jester_tilemap[i] + 32);
    }

    int tile_width = 8;
    int tile_height = 8;
    int sprite_index = 16;

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            move_sprite(sprite_index, start_x + col * tile_width, start_y + row * tile_height);
            sprite_index++;
            if (sprite_index > 31) // Adjusted to 31 since we have 16 sprites and start from 16
                break;
        }
    }

    SHOW_SPRITES; // Show the sprites on the screen
}

void setup_jester_home()
{
    setup_jester(100, 100);
}