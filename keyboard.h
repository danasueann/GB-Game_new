#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <gb/gb.h>
#include "cursor.h"

// Constants for keyboard layout
#define KEYBOARD_WIDTH 10
#define KEYBOARD_HEIGHT 4
#define KEYBOARD_START_X 12
#define KEYBOARD_START_Y 80

// Cursor movement boundaries
extern const UINT8 mincursor_x;
extern const UINT8 maxcursor_x;
extern const UINT8 mincursor_y;
extern const UINT8 maxcursor_y;

// Global variables for keyboard state
extern UBYTE keydown;
extern UBYTE pet_has_name;
extern UINT8 name_character_index;
extern UINT8 pet_name[6]; // Array to hold the pet name, max 18 characters
extern struct Cursor cursor;

// Function declarations
void choose_name(void);
void keyboard_input_loop(void);
void update_pet_name(struct Cursor *cursor);
void add_character_to_name(struct Cursor *cursor);
void remove_from_pet_name(void);
void draw_pet_name(void);
UBYTE is_within_keyboard(UINT8 x, UINT8 y);
void handle_keyboard_input(UBYTE joy);
void move_cursor_up(void);
void move_cursor_down(void);
void move_cursor_left(void);
void move_cursor_right(void);
void performantdelay(UINT8 numloops);
void array_to_string(char *output_string);
char *get_pet_name(void);

#endif // KEYBOARD_H