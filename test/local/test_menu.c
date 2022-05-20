#include <unity.h>
#include <menu.h>

static struct io {
    bool entered;
    int16_t value;
    uint8_t cursor;
    bool view_inited;
    uint8_t view_upd_count;
} m1_io = {0}, m2_io = {0};

void menu1_entrance_cb(struct menu *this)
{
    struct io *io = this->io;
    io->entered = true;
}

void menu1_value_change_cb(struct menu *this)
{
    struct io *io = this->io;
    io->value = this->fields[this->cursor].value;
}

void menu1_cursor_move_cb(struct menu *this)
{
    struct io *io = this->io;
    io->cursor = this->cursor;
}

struct menu *menu1_exit_prev_cb(struct menu *this)
{
    return this;
}

struct menu *menu1_exit_next_cb(struct menu *this)
{
    extern struct menu menu2;
    struct io *io = this->io;
    io->entered = false;
    
    if (this->fields[1].value == 1) {
        return &menu2;
    } else {
        return NULL;
    }
}

void menu1_view_init_cb(struct menu *this)
{
    struct io *io = this->io;
    io->view_inited = true;
}

void menu1_view_update_cb(struct menu *this)
{
    struct io *io = this->io;
    io->view_upd_count++;
}

void menu1_view_deinit_cb(struct menu *this)
{
    struct io *io = this->io;
    io->view_inited = false;
}


struct menu *menu2_exit_prev_cb(struct menu *this)
{
    extern struct menu menu1;
    struct io *io = this->io;
    io->entered = false;
    return &menu1;
}

struct menu *menu2_exit_next_cb(struct menu *this)
{
    struct io *io = this->io;
    io->entered = false;
    return NULL;
}

struct menu menu1 = {
    .fields = (struct menu_field []) {
        {5, 1, 10, false},
        {0, 0, 1, true},
        {0, -3, 3, true}
    },
    .labels = (const char *[]) {
        "Label_1",
        "Label_2",
        "Label_3"
    },
    .io = &m1_io,
    .on_entrance = menu1_entrance_cb,
    .on_value_change = menu1_value_change_cb,
    .on_cursor_move = menu1_cursor_move_cb,
    .on_exit_next = menu1_exit_next_cb,
    .on_exit_prev = menu1_exit_prev_cb,
    .view_init = menu1_view_init_cb,
    .view_update = menu1_view_update_cb,
    .view_deinit = menu1_view_deinit_cb,
    .num_fields = 3,
    .num_labels = 3,
    .cursor = 0
};

struct menu menu2 = {
    .fields = NULL,
    .labels = (const char *[]) {
        "Label of menu 2"
    },
    .io = &m2_io,
    .on_entrance = menu1_entrance_cb,
    .on_value_change = NULL,
    .on_cursor_move = NULL,
    .on_exit_next = menu2_exit_next_cb,
    .on_exit_prev = menu2_exit_prev_cb,
    .view_init = NULL,
    .view_update = NULL,
    .view_deinit = NULL,
    .num_fields = MENU_NO_FIELDS,
    .num_labels = 1,
    .cursor = 0
};

void test_menu(void)
{
    TEST_ASSERT_FALSE(menu_is_active());
    TEST_ASSERT_FALSE(m1_io.entered);
    TEST_ASSERT_FALSE(m1_io.view_inited);
    
    menu_enter(&menu1);
    TEST_ASSERT_TRUE(menu_is_active());
    TEST_ASSERT_TRUE(m1_io.entered);
    TEST_ASSERT_TRUE(m1_io.view_inited);

    TEST_ASSERT_EQUAL(MENU_RP_NOTHING, menu_execute(MENU_CMD_PREV));
    TEST_ASSERT_TRUE(menu_is_active());
    TEST_ASSERT_TRUE(m1_io.view_inited);

    menu_enter(&menu1);
    TEST_ASSERT_EQUAL(MENU_RP_VALUE_CHANGED, menu_execute(MENU_CMD_INC));
    TEST_ASSERT_EQUAL(MENU_RP_VALUE_CHANGED, menu_execute(MENU_CMD_INC));
    TEST_ASSERT_EQUAL(7, m1_io.value);
    TEST_ASSERT_EQUAL(2, m1_io.view_upd_count);

    for (int i = 0; i < 100; i++)
        menu_execute(MENU_CMD_INC);
    TEST_ASSERT_EQUAL(10, m1_io.value);

    for (int i = 0; i < 100; i++)
        menu_execute(MENU_CMD_DEC);
    TEST_ASSERT_EQUAL(1, m1_io.value);

    m1_io.view_upd_count = 0;

    TEST_ASSERT_EQUAL(MENU_RP_CURSOR_MOVED, menu_execute(MENU_CMD_NEXT));
    TEST_ASSERT_EQUAL(1, m1_io.cursor);
    TEST_ASSERT_EQUAL(1, m1_io.view_upd_count);
    TEST_ASSERT_EQUAL(MENU_RP_VALUE_CHANGED, menu_execute(MENU_CMD_INC));
    TEST_ASSERT_EQUAL(1, m1_io.value);
    TEST_ASSERT_EQUAL(MENU_RP_VALUE_CHANGED, menu_execute(MENU_CMD_INC));
    TEST_ASSERT_EQUAL(0, m1_io.value);

    TEST_ASSERT_EQUAL(MENU_RP_CURSOR_MOVED, menu_execute(MENU_CMD_PREV));
    TEST_ASSERT_EQUAL(MENU_RP_NOTHING, menu_execute(MENU_CMD_PREV));
    TEST_ASSERT_TRUE(menu_is_active());
    TEST_ASSERT_TRUE(m1_io.entered);
    TEST_ASSERT_TRUE(m1_io.view_inited);

    TEST_ASSERT_EQUAL(MENU_RP_CURSOR_MOVED, menu_execute(MENU_CMD_NEXT));
    TEST_ASSERT_EQUAL(MENU_RP_VALUE_CHANGED, menu_execute(MENU_CMD_DEC));
    TEST_ASSERT_EQUAL(1, m1_io.value);

    TEST_ASSERT_EQUAL(MENU_RP_CURSOR_MOVED, menu_execute(MENU_CMD_NEXT));
    TEST_ASSERT_EQUAL(MENU_RP_TRANSITED, menu_execute(MENU_CMD_NEXT));
    TEST_ASSERT_TRUE(menu_is_active());
    TEST_ASSERT_FALSE(m1_io.entered);
    TEST_ASSERT_FALSE(m1_io.view_inited);

    TEST_ASSERT_TRUE(m2_io.entered);
    TEST_ASSERT_EQUAL(MENU_RP_TRANSITED, menu_execute(MENU_CMD_PREV));
    TEST_ASSERT_TRUE(menu_is_active());
    TEST_ASSERT_TRUE(m1_io.entered);
    TEST_ASSERT_TRUE(m1_io.view_inited);
    TEST_ASSERT_FALSE(m2_io.entered);
    TEST_ASSERT_FALSE(m2_io.view_inited);

    menu_enter(&menu2);
    TEST_ASSERT_EQUAL(MENU_RP_TRANSITED, menu_execute(MENU_CMD_NEXT));
    TEST_ASSERT_FALSE(m2_io.entered);
    TEST_ASSERT_FALSE(menu_is_active());
}
