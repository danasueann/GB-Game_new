#include "pet_status.h"
#include <stdio.h>
#include <string.h>
#include "include/vwf.h"
#include "include/vwf_font_ru.h"
#include <gbdk/emu_debug.h>
#include <stdlib.h>

PetStatus pet_status;
UBYTE status_needs_update = 1;

void init_pet_status(void)
{
    pet_status.love = 50;
    pet_status.hunger = 30;
    pet_status.energy = 70;
    status_needs_update = 1;
}

void update_pet_stats(void)
{
    static UWORD time_counter = 0;
    time_counter++;

    // Alle 300 Frames (ca. 5 Sekunden bei 60 FPS)
    if (time_counter >= 300)
    {
        time_counter = 0;
        UBYTE changed = 0;

        // Hunger verringern
        if (pet_status.hunger > 0)
        {
            pet_status.hunger--;
            changed = 1;
        }

        // Energy verringern
        if (pet_status.energy > 0)
        {
            pet_status.energy--;
            changed = 1;
        }

        // Love verringern wenn hunger oder energy niedrig
        if ((pet_status.hunger < 30 || pet_status.energy < 30) && pet_status.love > 0)
        {
            pet_status.love--;
            changed = 1;
        }

        if (changed)
        {
            status_needs_update = 1;
        }
    }
}

void int_to_str(UBYTE value, char *str)
{
    char temp[4];
    UBYTE i = 0;

    if (value == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (value > 0 && i < 3)
    {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }

    for (UBYTE j = 0; j < i; j++)
    {
        str[j] = temp[i - 1 - j];
    }
    str[i] = '\0';
}

void display_pet_status(void)
{
    clear_status_area();

    pet_status.love = 50;
    pet_status.hunger = 30;
    pet_status.energy = 70;

    EMU_printf("Love: %u, Hunger: %u, Sleep: %u \n", pet_status.love, pet_status.hunger, pet_status.energy);

    char love_str[8];
    char hunger_str[8];
    char energy_str[8];

    // int_to_str(pet_status.love, love_str);
    itoa(pet_status.love, love_str, 10);
    strcat(love_str, "/100");

    int_to_str(pet_status.hunger, hunger_str);
    strcat(hunger_str, "/100");

    int_to_str(pet_status.energy, energy_str);
    strcat(energy_str, "/100");

    // EMU_printf("Love: %d, Hunger: %d, Sleep: %d\n", pet_status.love, pet_status.hunger, pet_status.energy);
    // EMU_printf("hallo");
    // EMU_printf("Love: %s, Hunger: %s, Sleep: %s\n", love_str, hunger_str, energy_str);

    vwf_draw_text(16, 0, 241, love_str);
    vwf_draw_text(16, 1, 247, hunger_str);
    vwf_draw_text(16, 2, 252, energy_str);
}

void display_pet_status_if_needed(void)
{
    if (status_needs_update)
    {
        display_pet_status();
        status_needs_update = 0;
    }
}

void cuddle_pet(UBYTE amount)
{
    UBYTE old_love = pet_status.love;

    if (pet_status.love + amount > 100)
        pet_status.love = 100;
    else
        pet_status.love += amount;

    if (old_love != pet_status.love)
    {
        status_needs_update = 1;
    }
}

void feed_pet(UBYTE amount)
{
    UBYTE old_hunger = pet_status.hunger;

    if (pet_status.hunger + amount > 100)
        pet_status.hunger = 100;
    else
        pet_status.hunger += amount;

    if (old_hunger != pet_status.hunger)
    {
        status_needs_update = 1;
    }
}

void pet_sleep(UBYTE amount)
{
    UBYTE old_energy = pet_status.energy;

    if (pet_status.energy + amount > 100)
        pet_status.energy = 100;
    else
        pet_status.energy += amount;

    if (old_energy != pet_status.energy)
    {
        status_needs_update = 1;
    }
}

void feed_pet_display_message(UBYTE selected_pet)
{
    if (selected_pet == 0)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*crunch crunch* Meow!");
    }

    if (selected_pet == 1)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*chews happily* Yumm!");
    }
}

void cuddle_pet_display_message(UBYTE selected_pet)
{
    if (selected_pet == 0)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*purrs loudly* Meow!");
    }

    if (selected_pet == 1)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*wagging tail* Woof!");
    }
}

void sleep_pet_display_message(UBYTE selected_pet)
{
    if (selected_pet == 0)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*curls up and purrs* Zzz...");
    }

    if (selected_pet == 1)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*snores softly* Zzz...");
    }
}

void up_key_display_message(UBYTE selected_pet)
{
    if (selected_pet == 0)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*ears perk up* Meow?");
    }

    if (selected_pet == 1)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*looks up curiously* Woof?");
    }
}

void down_key_display_message(UBYTE selected_pet)
{
    if (selected_pet == 0)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*sniffs around* Meow!");
    }

    if (selected_pet == 1)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*sniffs the ground* Woof!");
    }
}

void left_key_display_message(UBYTE selected_pet)
{
    if (selected_pet == 0)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*stretches left* Meow?");
    }

    if (selected_pet == 1)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*turns left* Woof?");
    }
}

void right_key_display_message(UBYTE selected_pet)
{
    if (selected_pet == 0)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*stretches right* Meow?");
    }

    if (selected_pet == 1)
    {
        vwf_draw_text(2, 16, 224, "                                ");
        vwf_draw_text(2, 16, 224, "*turns right* Woof?");
    }
}

void clear_status_area(void)
{
    vwf_draw_text(16, 0, 241, "       ");
    vwf_draw_text(16, 1, 247, "       ");
    vwf_draw_text(16, 2, 252, "       ");
}

void setup_font(void)
{
    vwf_load_font(0, font_ru, BANK(font_ru));
    vwf_activate_font(0);
    vwf_set_destination(VWF_RENDER_BKG);
    vwf_set_colors(3, 1);
}
