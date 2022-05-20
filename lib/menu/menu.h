/*
 * Copyright (C) 2022 Daniel Efimenko
 *     github.com/Danya0x07
 */

/*----------------------------------------------------------
 * A simple and universal library 
 * for creating text or character-based menus.
 *---------------------------------------------------------*/

#ifndef _MENU_H
#define _MENU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Adjustable value field structure.
 *
 * Every menu can have 0 or several adjustable fields.
 * 
 * For example, a menu where a number is adjusted digit by digit:
 * here digits are fields, `min` and `max` can be dynamically changed
 * in menu callbacks. Thus, if you need to constrain the value, entered by user
 * between 0000 and 2033 you can change the bounds of digits to 9, 9 and 9 if first value 
 * is less than 2 and to 0, 3 and 3 if it is 2.
 * 
 * Or if you have a menu screen that shows only text, the `menu_field` can represent the
 * number of page shown to make some kind of page scrolling. */
struct menu_field {
    int16_t value;
    int16_t min;
    int16_t max;
    bool overflow;  // Reset value to min if max+1 reached and vice versa.
};

/* Text menu universal representation.
 *
 * The menu is treated as a state of a state machine.
 * It has adjustable fields and a cursor. The cursor indicates which
 * field is being adjusted. When the cursor goes outside it's bounds,
 * (0...num_fields) the state change occurs.
 * 
 * Any pointer field can be NULL unless otherwise specified. */
struct menu {
    struct menu_field *fields;
    const char **labels;  // Can be array of zstrings or bitmap adresses.

    // Address of user defined data structure where the menu can
    // read (in callbacks) parameters and write it's results of work.
    void *io;

    // Callbacks for menu data change handling
    void (*on_entrance)(struct menu *);
    void (*on_value_change)(struct menu *);
    void (*on_cursor_move)(struct menu *);

    // Callbacks that can't be NULL as they determine
    // which menu to move to after this one.
    // And output data building is also expected to be done here.
    struct menu *(*on_exit_next)(struct menu *);
    struct menu *(*on_exit_prev)(struct menu *);

    // Callbacks for view managment. All graphics drawing should be done only here.
    void (*view_init)(struct menu *);
    void (*view_update)(struct menu *);
    void (*view_deinit)(struct menu *);

    uint8_t num_fields;
    uint8_t num_labels;

    uint8_t cursor;
};

/* If menu doesn't have fields, it's `fields` pointer should be set NULL,
 * but formally it will have one "imaginary" field that will not be used. */
#define MENU_NO_FIELDS  1


/* Possible menu commands.
 * 
 * Usually there are 4 buttons or other sources of menu managment signals:
 * some kind of increment, decrement, cancel(go to prev) and confirm(go to next). */
enum menu_command {
    MENU_CMD_DEC,
    MENU_CMD_INC,
    MENU_CMD_PREV,
    MENU_CMD_NEXT
};

// Variants of menu reply for executed command.
enum menu_reply {
    MENU_RP_NOTHING,
    MENU_RP_VALUE_CHANGED,
    MENU_RP_CURSOR_MOVED,
    MENU_RP_TRANSITED
};

void menu_enter(struct menu *menu);
enum menu_reply menu_execute(enum menu_command cmd);
bool menu_is_active(void);

#endif // _MENU_H