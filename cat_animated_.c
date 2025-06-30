#include <gb/gb.h>
#include "cat_animated.h"
#include "sprites/cat.h"
#include "sprites/cat_animated_2.h"

void setup_cat(int start_x, int start_y)
{
    set_sprite_data(0, cat_size, cat);
    for (int i = 0; i < cat_size; i++)
    {
        set_sprite_tile(i, cat_tilemap[i]);
    }
    int tile_width = 8;
    int tile_height = 8;
    int sprite_index = 0;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            move_sprite(sprite_index, start_x + col * tile_width, start_y + row * tile_height);
            sprite_index++;
            if (sprite_index > 15)
                break;
        }
    }

    SHOW_SPRITES;
}

void animate_cat_selection()
{
    UBYTE frame_delay = 10;
    UBYTE current_frame = 0;
    UBYTE frame_counter = 0;

    while (1)
    {
        UBYTE joy = joypad();
        if (joy & (J_A | J_B))
        {
            break;
        }

        frame_counter++;
        if (frame_counter >= frame_delay)
        {
            frame_counter = 0;
            current_frame = !current_frame;

            if (current_frame == 0)
            {
                set_sprite_data(0, cat_size, cat);
            }
            else
            {
                set_sprite_data(0, cat_animated_2_size, cat_animated_2);
            }
        }

        wait_vbl_done();
    }

    set_sprite_data(0, cat_size, cat);
}

void start_cat_animation()
{
    animation_active = 1;
    frame_counter = 0;
    current_frame = 0;
}

void stop_cat_animation()
{
    animation_active = 0;
    set_sprite_data(0, cat_size, cat);
}

void update_cat_animation()
{
    if (!animation_active)
        return;

    frame_counter++;
    if (frame_counter >= frame_delay)
    {
        frame_counter = 0;
        current_frame = !current_frame;
        if (current_frame == 0)
        {
            set_sprite_data(0, cat_size, cat);
        }
        else
        {
            set_sprite_data(0, cat_animated_2_size, cat_animated_2);
        }
    }
}

void setup_cat_home()
{
    setup_cat(100, 100);
    start_cat_animation();
}
