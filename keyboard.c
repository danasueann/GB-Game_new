#include "keyboard.h"
#include "keyboard/keyboarddata.h"
#include "keyboard/keyboardmap.h"
#include "sprites/cursor.h"

#pragma bank 1

const UINT8 mincursor_x = 12;
const UINT8 maxcursor_x = 156;
const UINT8 mincursor_y = 80;
const UINT8 maxcursor_y = 128;

// Global variables
UBYTE keydown = 0;
UBYTE pet_has_name = 0;
UINT8 name_character_index = 0;
UINT8 pet_name[6]; // Array to hold the pet name, max 6 characters
struct Cursor cursor;

void choose_name(void)
{
    cursor.x = KEYBOARD_START_X;
    cursor.y = KEYBOARD_START_Y;
    cursor.col = 0;
    cursor.row = 0;

    set_sprite_data(0, 1, cursor_sprite);
    set_sprite_tile(0, 0);

    move_sprite(0, cursor.x, cursor.y);
    set_bkg_data(0, 45, keyboarddata);
    set_bkg_tiles(0, 0, 20, 18, keyboardmap);
    scroll_bkg(-4, 0);

    SHOW_BKG;
    SHOW_SPRITES;
}

void keyboard_input_loop(void)
{
    // Main keyboard navigation loop
    while (pet_has_name == 0)
    {
        if (keydown)
        {
            waitpad(J_UP | J_DOWN | J_LEFT | J_RIGHT | J_A | J_B);
            keydown = 0;
        }

        UBYTE joy = joypad();
        if (joy)
        {
            handle_keyboard_input(joy);
        }

        performantdelay(10);
    }
}

void handle_keyboard_input(UBYTE joy)
{
    switch (joy)
    {
    case J_UP:
        move_cursor_up();
        break;
    case J_DOWN:
        move_cursor_down();
        break;
    case J_LEFT:
        move_cursor_left();
        break;
    case J_RIGHT:
        move_cursor_right();
        break;
    case J_A:
        update_pet_name(&cursor);
        keydown = 1;
        break;
    case J_B:
        draw_pet_name();
        remove_from_pet_name();
        keydown = 1;
        break;
    case J_START:

        pet_has_name = 1;
        draw_pet_name();

        keydown = 1;
        break;
    }
}

void move_cursor_up(void)
{
    if (is_within_keyboard(cursor.x, cursor.y - 16))
    {
        cursor.row--;
        cursor.y -= 16;
        move_sprite(0, cursor.x, cursor.y);
        keydown = 1;
    }
}

void move_cursor_down(void)
{
    if (is_within_keyboard(cursor.x, cursor.y + 16))
    {
        cursor.row++;
        cursor.y += 16;
        move_sprite(0, cursor.x, cursor.y);
        keydown = 1;
    }
}

void move_cursor_left(void)
{
    if (is_within_keyboard(cursor.x - 16, cursor.y))
    {
        cursor.col--;
        cursor.x -= 16;
        move_sprite(0, cursor.x, cursor.y);
        keydown = 1;
    }
}

void move_cursor_right(void)
{
    if (is_within_keyboard(cursor.x + 16, cursor.y))
    {
        cursor.col++;
        cursor.x += 16;
        move_sprite(0, cursor.x, cursor.y);
        keydown = 1;
    }
}

UBYTE is_within_keyboard(UINT8 x, UINT8 y)
{
    if ((x == 140 && y == 144) || (x == 156 && y == 144))
    {
        return 1;
    }
    return (x >= mincursor_x && x <= maxcursor_x && y >= mincursor_y && y <= maxcursor_y);
}

void add_character_to_name(struct Cursor *cursor)
{
    UINT8 character_index = cursor->row * 10 + cursor->col + 1;

    if (name_character_index == 6)
        return;

    pet_name[name_character_index] = character_index;
    name_character_index++;
}

void update_pet_name(struct Cursor *cursor)
{
    if (cursor->col == 8 && cursor->row == 4)
    {
        remove_from_pet_name();
        draw_pet_name();
    }
    else if (cursor->col == 9 && cursor->row == 4)
    {
        pet_has_name = 1;
        draw_pet_name();
    }
    else
    {
        add_character_to_name(cursor);
        draw_pet_name();
    }
}

void draw_pet_name(void)
{
    set_bkg_tiles(1, 4, 6, 1, pet_name);
}

void remove_from_pet_name(void)
{
    if (name_character_index > 0)
    {
        name_character_index--;
        pet_name[name_character_index] = 0; // Clear the last character
    }
}

// Prevent cursor from being too fast
void performantdelay(UINT8 numloops)
{
    UINT8 i;
    for (i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

const char keyboard_chars[] = {
    ' ',                                              // Index 0 (leer)
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', // Row 0 (Index 1-10)
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', // Row 1 (Index 11-20)
    'U', 'V', 'W', 'X', 'Y', 'Z', '.', ',', '-', ' ', // Row 2 (Index 21-30)
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'  // Row 3 (Index 31-40)
};

void array_to_string(char *output_string)
{
    UINT8 i;

    for (i = 0; i < name_character_index && i < 6; i++)
    {
        UINT8 char_index = pet_name[i];

        if (char_index < sizeof(keyboard_chars))
        {
            output_string[i] = keyboard_chars[char_index];
        }
        else
        {
            output_string[i] = '?';
        }
    }

    output_string[i] = '\0';
}

char *get_pet_name(void)
{
    static char pet_name_string[7];
    array_to_string(pet_name_string);
    return pet_name_string;
}