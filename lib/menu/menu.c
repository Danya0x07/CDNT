#include "menu.h"

static struct menu *current_menu = NULL;

void menu_set_current(struct menu *menu)
{
    current_menu = menu;
    if (menu) {
        if (menu->on_entrance)
            menu->on_entrance(menu);
        if (menu->view_init)
            menu->view_init(menu);
    }
}

enum menu_reply menu_execute(enum menu_command cmd)
{
    enum menu_reply reply = MENU_RP_NOTHING;

    if (!current_menu)
        return MENU_RP_NOTHING;
    
    switch (cmd)
    {
    case MENU_CMD_DEC:
        if (current_menu->fields) {
            struct menu_field *field = &current_menu->fields[current_menu->cursor];

            if (field->value > field->min) {
                field->value--;
                reply = MENU_RP_VALUE_CHANGED;
            } else {
                if (field->overflow) {
                    field->value = field->max;
                    reply = MENU_RP_VALUE_CHANGED;
                }
            }
        }
        break;
    
    case MENU_CMD_INC:
        if (current_menu->fields) {
            struct menu_field *field = &current_menu->fields[current_menu->cursor];

            if (field->value < field->max) {
                field->value++;
                reply = MENU_RP_VALUE_CHANGED;
            } else {
                if (field->overflow) {
                    field->value = field->min;
                    reply = MENU_RP_VALUE_CHANGED;
                }
            }
        }
        break;
    
    case MENU_CMD_PREV:
        if (current_menu->cursor > 0) {
            current_menu->cursor--;
            reply = MENU_RP_CURSOR_MOVED;
        } else {
            reply = MENU_RP_TRANSITED;
        }
        break;
    
    case MENU_CMD_NEXT:
        if (current_menu->cursor < current_menu->num_fields - 1) {
            current_menu->cursor++;
            reply = MENU_RP_CURSOR_MOVED;
        } else {
            reply = MENU_RP_TRANSITED;
        }
        break;
    }

    switch (reply)
    {
    case MENU_RP_VALUE_CHANGED:
        if (current_menu->on_value_change)
            current_menu->on_value_change(current_menu);
        if (current_menu->view_update)
            current_menu->view_update(current_menu);
        break;
    
    case MENU_RP_CURSOR_MOVED:
        if (current_menu->on_cursor_move)
            current_menu->on_cursor_move(current_menu);
        if (current_menu->view_update)
            current_menu->view_update(current_menu);
        break;
    
    case MENU_RP_TRANSITED:
        {
            struct menu *next;
            
            if (cmd == MENU_CMD_PREV) {
                next = current_menu->on_exit_prev(current_menu);
            } else {
                next = current_menu->on_exit_next(current_menu);
            }
            if (next == current_menu) {
                if (next->on_entrance)
                    next->on_entrance(next);
                break;
            }

            if (current_menu->view_deinit)
                current_menu->view_deinit(current_menu);
            menu_set_current(next);
        }

    case MENU_RP_NOTHING:
    default:
        break;
    }

    return reply;
}

bool menu_is_active(void)
{
    return current_menu != NULL;
}
