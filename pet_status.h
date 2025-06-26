#ifndef PET_STATUS_H
#define PET_STATUS_H

#include <gb/gb.h>

// Pet types
#define PET_CAT    0
#define PET_POODLE 1


// Pet status structure
typedef struct {
    UBYTE love;
    UBYTE hunger; 
    UBYTE energy;
} PetStatus;

extern PetStatus pet_status;
extern UBYTE status_needs_update;

// Function declarations ()
void init_pet_status(void) ;
void update_pet_stats(void) ;
void display_pet_status(void) ;
void setup_font(void) ;
void int_to_str(UBYTE value, char* str);
void display_pet_status_if_needed(void);
void clear_status_area(void);
void feed_pet_display_message(UBYTE selected_pet);
void cuddle_pet_display_message(UBYTE selected_pet);
void sleep_pet_display_message(UBYTE selected_pet);
void up_key_display_message(UBYTE selected_pet);
void down_key_display_message(UBYTE selected_pet);
void left_key_display_message(UBYTE selected_pet);
void right_key_display_message(UBYTE selected_pet);


// Pet-specific message functions ()
// const char *get_feed_message(void) ;
// const char *get_cuddle_message(void) ;
// const char *get_up_message(void) ;
// const char *get_down_message(void) ;
// const char *get_left_message(void) ;
// const char *get_right_message(void) ;

// Pet action functions ()
void feed_pet(UBYTE amount);
void cuddle_pet(UBYTE amount);
void pet_sleep(UBYTE amount);

#endif // PET_STATUS_H
