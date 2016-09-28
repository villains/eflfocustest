#include <stdio.h>
#include <Elementary.h>

static Evas_Object *flip = NULL;
static Evas_Object *win = NULL;
static Evas_Object *mainBox = NULL;
static Evas_Object *table = NULL;
static Evas_Object *rect = NULL;
static Evas_Object *topBar = NULL;

static Eina_Bool
keyEventCallback(void *data, int type, void *event)
{
    Ecore_Event_Key *ev = (Ecore_Event_Key *)event;
    const char *k = ev->keyname;

    if (type == ECORE_EVENT_KEY_DOWN) {
        if (!strcmp(k, "f")) {
            elm_flip_go(flip, ELM_FLIP_CUBE_RIGHT);
        }
    }

    // printf("Global key press: %s\n", k);
    return ECORE_CALLBACK_RENEW;
}

static void
winKeyDown(void *data, Evas *e EINA_UNUSED,
    Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{

}

static Evas_Object *createContent1(Evas_Object *parent);
static Evas_Object *createContent2(Evas_Object *parent);

EAPI_MAIN int
elm_main(int argc, char **argv)
{
    //elm_config_focus_highlight_enabled_set(EINA_FALSE);
    elm_config_focus_move_policy_set(EFL_UI_FOCUS_MOVE_POLICY_IN);
    elm_config_window_auto_focus_enable_set(EINA_FALSE);

    // Use global key callbacks for testing
    ecore_event_handler_add(ECORE_EVENT_KEY_DOWN, keyEventCallback, NULL);
    // ecore_event_handler_add(ECORE_EVENT_KEY_UP, keyEventCallback, NULL);
    elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

    win = elm_win_add(NULL, "Focus Test", ELM_WIN_BASIC);
    elm_win_autodel_set(win, EINA_TRUE);
    elm_win_focus_highlight_enabled_set(win, EINA_FALSE);
    evas_object_resize(win, 200, 150);
    evas_object_show(win);

    mainBox = elm_box_add(win);
    evas_object_size_hint_weight_set(mainBox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(win, mainBox);
    evas_object_show(mainBox);

    topBar = elm_label_add(win);
    evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, 0.0);
    elm_object_text_set(topBar, "Top Status Bar");
    evas_object_show(topBar);
    elm_box_pack_end(mainBox, topBar);

    flip = elm_flip_add(win);
    evas_object_size_hint_weight_set(flip, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(flip, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_fill_set(flip, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(flip);
    elm_box_pack_end(mainBox, flip);

    elm_object_part_content_set(flip, "front", createContent1(win));
    elm_object_part_content_set(flip, "back", createContent2(win));

    // with or without this, no difference
    elm_object_focus_set(flip, EINA_TRUE);

    elm_run();
    return 0;
}
ELM_MAIN()

/*
What should happen is that this callback gets called for key down events
while Content 1 is visible in the flip
*/
static void
content1_KeyDownCallback(void *data, Evas *e EINA_UNUSED,
    Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    Evas_Event_Key_Down *ev = event_info;
    const char *k = ev->keyname;
    printf("Content 1 key down: %s\n", ev->keyname);

    if (!strcmp(k, "g")) {
        elm_flip_go(flip, ELM_FLIP_CUBE_RIGHT);
    }
}

// static void
// content1_FocusInCallback(void *data, Evas *e EINA_UNUSED,
//     Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
// {
//     printf("content1 focused\n");
// }

// static void
// content1_FocusOutCallback(void *data, Evas *e EINA_UNUSED,
//     Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
// {
//     printf("content1 unfocused\n");
// }

static void
contentKeyDownCallback2(void *data, Evas *e EINA_UNUSED,
    Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    Evas_Event_Key_Down *ev = event_info;
    printf("Content 2 key press: %s\n", ev->keyname);
}

static void
content1_FocusedCallback(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
    elm_win_focus_highlight_enabled_set(win, EINA_FALSE);
    printf("content1 focused\n");
}

static void
content1_UnfocusedCallback(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    // elm_win_focus_highlight_enabled_set(win, EINA_TRUE);
    printf("content1 unfocused\n");
}

static void
content2_FocusedCallback(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
}

static void
content2_UnfocusedCallback(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
}

static void
table_FocusedCallback(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
    printf("table focused\n");
}

static Evas_Object *createContent1(Evas_Object *parent)
{
    Evas_Object *rv = NULL; // return value
    Evas_Object *table = NULL;
    Evas_Object *rect = NULL;
    Evas_Object *label = NULL;
    Evas_Object *button = NULL;
    Evas_Object *frame = NULL;
    Evas_Object *box = NULL;
    Evas_Object *otherBox = NULL;

    table = elm_table_add(parent);
    evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(table, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_fill_set(table, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(table);

    box = elm_box_add(parent);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_fill_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(box);
    elm_table_pack(table, box, 0, 0, 1, 1);

    frame = elm_frame_add(parent);
    evas_object_size_hint_weight_set(frame, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_fill_set(frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(frame);
    elm_box_pack_end(box, frame);
    //elm_table_pack(table, frame, 0, 0, 1, 1);

    label = elm_label_add(parent);
    evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_object_text_set(label,
        "Content 1"
        "<br><br>Press 'f' to flip"
        "<br><br>Should be able to use 'g' to flip also...");
    evas_object_show(label);
    elm_object_content_set(frame, label);
    //elm_table_pack(table, label, 0, 0, 1, 1);

    label = elm_label_add(parent);
    evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
    elm_object_text_set(label, "Hello, world!");
    evas_object_show(label);
    elm_box_pack_end(box, label);

    otherBox = elm_box_add(parent);
    evas_object_size_hint_weight_set(otherBox, EVAS_HINT_EXPAND, 0.0);
    evas_object_size_hint_align_set(otherBox, EVAS_HINT_FILL, 0.0);
    evas_object_size_hint_fill_set(otherBox, EVAS_HINT_FILL, 0.0);
    evas_object_show(otherBox);
    elm_box_horizontal_set(otherBox, EINA_TRUE);
    elm_box_pack_end(box, otherBox);

    label = elm_label_add(parent);
    evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
    elm_object_text_set(label, "123");
    evas_object_show(label);
    elm_box_pack_end(otherBox, label);

    label = elm_label_add(parent);
    evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
    elm_object_text_set(label, "456");
    evas_object_show(label);
    elm_box_pack_end(otherBox, label);

    otherBox = elm_box_add(parent);
    evas_object_size_hint_weight_set(otherBox, EVAS_HINT_EXPAND, 0.0);
    evas_object_size_hint_align_set(otherBox, EVAS_HINT_FILL, 0.0);
    evas_object_size_hint_fill_set(otherBox, EVAS_HINT_FILL, 0.0);
    evas_object_show(otherBox);
    elm_box_horizontal_set(otherBox, EINA_TRUE);
    elm_box_pack_end(box, otherBox);

    label = elm_label_add(parent);
    evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
    elm_object_text_set(label, "abc");
    evas_object_show(label);
    elm_box_pack_end(otherBox, label);

    label = elm_label_add(parent);
    evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
    elm_object_text_set(label, "def");
    evas_object_show(label);
    elm_box_pack_end(otherBox, label);

    /*
    This part is based on ephoto_single_browser.c lines 2195-2203
    Thanks to okra on IRC #edevelop
    */
    // rect = evas_object_rectangle_add(parent);
    // evas_object_smart_member_add(rect, parent);
    rect = elm_label_add(parent);
    elm_object_focus_allow_set(rect, EINA_TRUE);
    evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_fill_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_color_set(rect, 0, 0, 0, 0);
    //evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    // evas_object_repeat_events_set(rect, EINA_TRUE);
    evas_object_show(rect);
    evas_object_event_callback_add(rect, EVAS_CALLBACK_KEY_DOWN,
        content1_KeyDownCallback, NULL);
    // evas_object_event_callback_add(rect, EVAS_CALLBACK_FOCUS_IN,
    //     content1_FocusInCallback, NULL);
    // evas_object_event_callback_add(rect, EVAS_CALLBACK_FOCUS_IN,
    //     content1_FocusOutCallback, NULL);
    evas_object_smart_callback_add(rect, "focused", content1_FocusedCallback, NULL);
    evas_object_smart_callback_add(rect, "unfocused", content1_UnfocusedCallback, NULL);
    elm_table_pack(table, rect, 0, 0, 1, 1);
    evas_object_raise(rect);

    elm_object_focus_allow_set(table, EINA_TRUE);
    evas_object_smart_callback_add(table, "focused", table_FocusedCallback, NULL);
    elm_object_focus_set(table, EINA_TRUE);

    // button = elm_button_add(parent);
    // elm_object_text_set(button, "Test Button");
    // evas_object_show(button);
    // elm_table_pack(table, button, 0, 1, 1, 1);

    rv = table;

    return table;
}

static Evas_Object *createContent2(Evas_Object *parent)
{
    Evas_Object *rv = NULL; // return value
    rv = elm_label_add(win);
    elm_object_focus_allow_set(rv, EINA_TRUE);
    evas_object_size_hint_weight_set(rv, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_object_text_set(rv, "Content 2<br><br>Press 'f' to flip");
    evas_object_show(rv);
    evas_object_event_callback_add(rv, EVAS_CALLBACK_KEY_DOWN,
        contentKeyDownCallback2, NULL);
    return rv;
}
