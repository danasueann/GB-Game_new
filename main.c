#include <gb/gb.h>
#include <stdio.h>
#include "include/vwf.h"
#include "include/vwf_font_ru.h"
#include "backgrounds/background_cat.h"
#include "backgrounds/background_dog.h"
#include "home.h"
#include "backgrounds/SelectMenu_tileset.h"
#include "SelectMenu.h"
#include "sprites/cat.h"
#include "cat_animated.h"
#include "jester.h"
#include "keyboard.h"
#include "foregrounds/hud.h"
#include "pet_status.h"

void clear_background(void);
void clear_sprites(void);

UBYTE selected_pet = 0;
UBYTE prev_joy = 0;

void main()
{
    // Grundlegende Initialisierung
    DISPLAY_OFF;

    init_pet_status();
    setup_font();

    // Pet Selection Phase
    setup_select_menu_background();
    setup_cat(32, 80);
    setup_jester(110, 80);

    DISPLAY_ON;
    selected_pet = choose_pet();

    // Name Selection Phase
    DISPLAY_OFF;
    clear_background();
    clear_sprites();

    DISPLAY_ON;
    choose_name();
    keyboard_input_loop();

    // Home Screen Setup
    clear_background();
    clear_sprites();

    if (selected_pet == 0)
    {
        scroll_bkg(4, 0);
        setup_home_background_cat();
        setup_cat_home();
    }
    else if (selected_pet == 1)
    {
        scroll_bkg(4, 0);
        setup_home_background_dog();
        setup_jester_home();
    }

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    // Main Game Loop
    while (1)
    {
        UBYTE joy = joypad();
        update_pet_stats();
        display_pet_status_if_needed();
        if ((joy & J_A))
        {
            cuddle_pet(10);
            if (selected_pet == 0)
            {
                cuddle_pet_display_message(0);
            }

            if (selected_pet == 1)
            {
                cuddle_pet_display_message(1);
            }
        }
        if ((joy & J_B))
        {
            feed_pet(10);
            if (selected_pet == 0)
            {
                feed_pet_display_message(0);
            }

            if (selected_pet == 1)
            {
                feed_pet_display_message(1);
            }
        }
        if ((joy & J_SELECT))
        {
            pet_sleep(10);
            if (selected_pet == 0)
            {
                sleep_pet_display_message(0);
            }

            if (selected_pet == 1)
            {
                sleep_pet_display_message(1);
            }
        }

        if ((joy & J_UP))
        {
            if (selected_pet == 0)
            {
                up_key_display_message(0);
            }
            else if (selected_pet == 1)
            {
                up_key_display_message(1);
            }
        }
        if ((joy & J_DOWN))
        {
            if (selected_pet == 0)
            {
                down_key_display_message(0);
            }
            else if (selected_pet == 1)
            {
                down_key_display_message(1);
            }
        }

        if ((joy & J_LEFT))
        {
            if (selected_pet == 0)
            {
                left_key_display_message(0);
            }
            else if (selected_pet == 1)
            {
                left_key_display_message(1);
            }
        }

        if ((joy & J_RIGHT))
        {
            if (selected_pet == 0)
            {
                right_key_display_message(0);
            }
            else if (selected_pet == 1)
            {
                right_key_display_message(1);
            }
        }
        display_pet_status();

        prev_joy = joy;
        wait_vbl_done();
    }
}

void clear_background()
{
    for (UBYTE x = 0; x < 32; x++)
    {
        for (UBYTE y = 0; y < 32; y++)
        {
            set_bkg_tile_xy(x, y, 0);
        }
    }
}

void clear_sprites()
{
    for (UBYTE i = 0; i < 40; i++)
    {
        move_sprite(i, 0, 0);
        set_sprite_tile(i, 0);
    }
}