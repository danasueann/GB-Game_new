#ifndef CURSOR_H
#define CURSOR_H


#include <gb/gb.h>

typedef struct Cursor
{
    UINT8 x;
    UINT8 y;
    UINT8 col;
    UINT8 row;
} Cursor;

#endif // CURSOR_H