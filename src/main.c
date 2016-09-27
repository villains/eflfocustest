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

    printf("Global key press: %s\n", k);
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
    // Use global key callbacks for testing
    ecore_event_handler_add(ECORE_EVENT_KEY_DOWN, keyEventCallback, NULL);
    // ecore_event_handler_add(ECORE_EVENT_KEY_UP, keyEventCallback, NULL);
    elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

    win = elm_win_add(NULL, "Focus Test", ELM_WIN_BASIC);
    elm_win_autodel_set(win, EINA_TRUE);
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
    evas_object_show(flip);
    elm_box_pack_end(mainBox, flip);

    elm_object_part_content_set(flip, "front", createContent1(win));
    elm_object_part_content_set(flip, "back", createContent2(win));

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
contentKeyDownCallback1(void *data, Evas *e EINA_UNUSED,
    Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    Ecore_Event_Key *ev = (Ecore_Event_Key *)event_info;
    const char *k = ev->keyname;
    printf("Content 1 key down: %s\n", ev->keyname);

    if (!strcmp(k, "g")) {
        elm_flip_go(flip, ELM_FLIP_CUBE_RIGHT);
    }
}

static void
contentKeyCallback2(void *data, Evas *e EINA_UNUSED,
    Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
    Ecore_Event_Key *ev = (Ecore_Event_Key *)event_info;
    printf("Content 2 key press: %s\n", ev->keyname);
}

static Evas_Object *createContent1(Evas_Object *parent)
{
    Evas_Object *rv = NULL; // return value
    Evas_Object *table = NULL;
    Evas_Object *rect = NULL;
    Evas_Object *label = NULL;

    table = elm_table_add(parent);
    evas_object_show(table);

    label = elm_label_add(win);
    evas_object_size_hint_weight_set(rv, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_object_text_set(label,
        "Content 1"
        "<br><br>Press 'f' to flip"
        "<br><br>Should be able to use 'g' to flip also...");
    evas_object_show(label);
    elm_table_pack(table, label, 0, 0, 1, 1);

    /*
    This part is based on ephoto_single_browser.c lines 2195-2203
    Thanks to okra on IRC #edevelop
    */
    rect = evas_object_rectangle_add(parent);
    evas_object_smart_member_add(rect, parent);
    evas_object_color_set(rect, 128, 0, 0, 255);
    //evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_repeat_events_set(rect, EINA_TRUE);
    evas_object_move(rect, 50, 50);
    evas_object_resize(rect, 100, 100);
    evas_object_show(rect);
    evas_object_event_callback_add(rect, EVAS_CALLBACK_KEY_DOWN,
        contentKeyDownCallback1, NULL);
    elm_object_focus_set(rect, EINA_TRUE);
    elm_table_pack(table, rect, 0, 0, 1, 1);
    evas_object_raise(rect);

    rv = table;

    return table;
}

static Evas_Object *createContent2(Evas_Object *parent)
{
    Evas_Object *rv = NULL; // return value
    rv = elm_label_add(win);
    evas_object_size_hint_weight_set(rv, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_object_text_set(rv, "Content 2<br><br>Press 'f' to flip");
    evas_object_show(rv);
    return rv;
}
