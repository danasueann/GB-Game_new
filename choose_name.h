// choose_name.h
#ifndef CHOOSE_NAME_H
#define CHOOSE_NAME_H

#include "<gb/gb.h>"
#include <stdio.h>
#include <string.h>

// Constants
#define MAX_NAME_LENGTH 7
#define KEYBOARD_WIDTH 6
#define KEYBOARD_HEIGHT 5
#define KEYBOARD_SIZE 30
#define FONT_TILE_OFFSET 0x00 // Adjust based on your font tiles

// Global Variables (declare only, define in .c file)
extern char pet_name[MAX_NAME_LENGTH + 1];
extern char keyboard_chars[KEYBOARD_SIZE + 1];
extern UINT8 cursor_x, cursor_y;
extern UINT8 name_length;
extern UINT8 name_entry_done;

// Function declarations only
void init_name_entry(void);
void draw_keyboard(void);
void draw_current_name(void);
void draw_cursor(void);
void clear_cursor(void);
void handle_navigation(UINT8 joypad);
void handle_select_char(void);
void handle_delete_char(void);
void handle_confirm_name(void);
UINT8 choose_name(void);
UINT8 get_selected_char_index(void);
UINT8 is_name_valid(void);
void show_message(const char *message);
void clear_screen(void);
UINT8 wait_for_input(void);
UINT8 char_to_tile(char c);
void draw_text_at(UINT8 x, UINT8 y, const char *text);

#endif 

// Global Variables
char pet_name[MAX_NAME_LENGTH + 1] = {0};
char keyboard_chars[KEYBOARD_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123";
UINT8 cursor_x = 0;
UINT8 cursor_y = 0;
UINT8 name_length = 0;
UINT8 name_entry_done = 0;

// Helper function to convert character to tile index
UINT8 char_to_tile(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return FONT_TILE_OFFSET + (c - 'A');
    }
    else if (c >= '0' && c <= '9')
    {
        return FONT_TILE_OFFSET + 26 + (c - '0');
    }
    else if (c == ' ')
    {
        return FONT_TILE_OFFSET + 36;
    }
    else if (c == ':')
    {
        return FONT_TILE_OFFSET + 37;
    }
    else if (c == '_')
    {
        return FONT_TILE_OFFSET + 38;
    }
    else if (c == '[')
    {
        return FONT_TILE_OFFSET + 39;
    }
    else if (c == ']')
    {
        return FONT_TILE_OFFSET + 40;
    }
    return FONT_TILE_OFFSET; // Default to first tile
}

// Helper function to draw text
void draw_text_at(UINT8 x, UINT8 y, const char *text)
{
    UINT8 len = strlen(text);
    UINT8 tile_buffer[20]; // Adjust size as needed
    UINT8 i;

    for (i = 0; i < len && i < 20; i++)
    {
        tile_buffer[i] = char_to_tile(text[i]);
    }

    set_bkg_tiles(x, y, len, 1, tile_buffer);
}

void init_name_entry(void)
{
    // Reset name
    memset(pet_name, 0, MAX_NAME_LENGTH + 1);
    name_length = 0;

    // Reset cursor position
    cursor_x = 0;
    cursor_y = 0;

    // Reset status
    name_entry_done = 0;

    // Prepare screen
    clear_screen();
    draw_keyboard();
    draw_current_name();
    draw_cursor();
}

void draw_keyboard(void)
{
    UINT8 i, x, y;
    UINT8 char_tile;

    // Display title
    draw_text_at(6, 2, "ENTER NAME:");

    // Draw keyboard (starting from row 8)
    for (i = 0; i < KEYBOARD_SIZE; i++)
    {
        x = (i % KEYBOARD_WIDTH) * 3 + 2;
        y = (i / KEYBOARD_WIDTH) + 8;

        char_tile = char_to_tile(keyboard_chars[i]);
        set_bkg_tiles(x, y, 1, 1, &char_tile);
    }

    // Special options
    draw_text_at(2, 14, "SELECT: Choose");
    draw_text_at(2, 15, "B: Delete");
    draw_text_at(2, 16, "START: Confirm");
}

void draw_current_name(void)
{
    UINT8 i;
    UINT8 display_tiles[MAX_NAME_LENGTH + 2];

    // Prepare display tiles - fill with spaces
    for (i = 0; i < MAX_NAME_LENGTH + 1; i++)
    {
        display_tiles[i] = char_to_tile(' ');
    }

    // Copy name
    for (i = 0; i < name_length; i++)
    {
        display_tiles[i] = char_to_tile(pet_name[i]);
    }

    // Show cursor at end
    if (name_length < MAX_NAME_LENGTH)
    {
        display_tiles[name_length] = char_to_tile('_');
    }

    // Position for name (row 4)
    set_bkg_tiles(8, 4, MAX_NAME_LENGTH + 1, 1, display_tiles);
}

void draw_cursor(void)
{
    UINT8 screen_x = (cursor_x * 3) + 1;
    UINT8 screen_y = cursor_y + 8;
    UINT8 cursor_tiles[3];

    cursor_tiles[0] = char_to_tile('[');
    cursor_tiles[1] = char_to_tile(keyboard_chars[get_selected_char_index()]);
    cursor_tiles[2] = char_to_tile(']');

    // Draw frame around selected character
    set_bkg_tiles(screen_x, screen_y, 3, 1, cursor_tiles);
}

void clear_cursor(void)
{
    UINT8 screen_x = (cursor_x * 3) + 2;
    UINT8 screen_y = cursor_y + 8;
    UINT8 normal_tiles[3];

    normal_tiles[0] = char_to_tile(' ');
    normal_tiles[1] = char_to_tile(keyboard_chars[get_selected_char_index()]);
    normal_tiles[2] = char_to_tile(' ');

    // Display character without frame (with spaces around)
    set_bkg_tiles(screen_x - 1, screen_y, 3, 1, normal_tiles);
}

void handle_navigation(UINT8 joypad)
{
    UINT8 old_x = cursor_x;
    UINT8 old_y = cursor_y;

    if (joypad & J_LEFT && cursor_x > 0)
    {
        cursor_x--;
    }
    else if (joypad & J_RIGHT && cursor_x < KEYBOARD_WIDTH - 1)
    {
        cursor_x++;
    }
    else if (joypad & J_UP && cursor_y > 0)
    {
        cursor_y--;
    }
    else if (joypad & J_DOWN && cursor_y < KEYBOARD_HEIGHT - 1)
    {
        cursor_y++;
    }

    // Only redraw cursor if position changed
    if (old_x != cursor_x || old_y != cursor_y)
    {
        // Clear old position
        UINT8 temp_x = cursor_x;
        UINT8 temp_y = cursor_y;
        cursor_x = old_x;
        cursor_y = old_y;
        clear_cursor();

        // Draw new position
        cursor_x = temp_x;
        cursor_y = temp_y;
        draw_cursor();
    }
}

void handle_select_char(void)
{
    if (name_length < MAX_NAME_LENGTH)
    {
        UINT8 char_index = get_selected_char_index();
        if (char_index < KEYBOARD_SIZE)
        {
            pet_name[name_length] = keyboard_chars[char_index];
            name_length++;
            draw_current_name();
        }
    }
}

void handle_delete_char(void)
{
    if (name_length > 0)
    {
        name_length--;
        pet_name[name_length] = 0;
        draw_current_name();
    }
}

void handle_confirm_name(void)
{
    if (is_name_valid())
    {
        name_entry_done = 1;
        show_message("NAME SAVED!");
    }
    else
    {
        show_message("ENTER AT LEAST 1 CHAR!");
        // Wait briefly (about 1 second)
        for (UINT8 i = 0; i < 60; i++)
        {
            wait_vbl_done();
        }
        draw_keyboard();
        draw_current_name();
        draw_cursor();
    }
}

UINT8 choose_name(void)
{
    UINT8 joypad_;
    UINT8 previous_joypad = 0;

    init_name_entry();

    while (!name_entry_done)
    {
        joypad_ = joypad();

        // Only react when key is newly pressed
        if (joypad_ && !previous_joypad)
        {
            if (joypad_ & (J_LEFT | J_RIGHT | J_UP | J_DOWN))
            {
                handle_navigation(joypad_);
            }
            else if (joypad_ & J_A)
            {
                handle_select_char();
            }
            else if (joypad_ & J_B)
            {
                handle_delete_char();
            }
            else if (joypad_ & J_START)
            {
                handle_confirm_name();
            }
        }

        previous_joypad = joypad_;

        // Wait for V-Blank for smooth animation
        wait_vbl_done();
    }

    return 1; // Name was successfully entered
}

UINT8 get_selected_char_index(void)
{
    UINT8 index = cursor_y * KEYBOARD_WIDTH + cursor_x;
    return (index < KEYBOARD_SIZE) ? index : 0;
}

UINT8 is_name_valid(void)
{
    return (name_length > 0);
}

void show_message(const char *message)
{
    clear_screen();
    UINT8 msg_len = strlen(message);
    UINT8 start_x = (20 - msg_len) / 2;
    draw_text_at(start_x, 9, message);
}

void clear_screen(void)
{
    UINT8 blank_tile = char_to_tile(' ');
    UINT8 blank_line[20];
    UINT8 i, j;

    for (i = 0; i < 20; i++)
    {
        blank_line[i] = blank_tile;
    }

    for (j = 0; j < 18; j++)
    {
        set_bkg_tiles(0, j, 20, 1, blank_line);
    }
}

UINT8 wait_for_input(void)
{
    UINT8 joypad_state;

    // Wait until no key is pressed
    while (joypad())
    {
        wait_vbl_done();
    }

    // Wait until a key is pressed
    do
    {
        joypad_state = joypad();
        wait_vbl_done();
    } while (!joypad_state);

    return joypad_state;
}

#endif