#ifndef GLSG_INPUT_H
#define GLSG_INPUT_H

namespace glsg {

typedef struct {
    /**
    * Type of input event.
    * Invalid is used to signal an event has been consumed and will
    * not match any object rules.
    */
    enum Type {
        INVALID,
        MOUSEMOVE,
        MOUSEBUTTON,
        MOUSESCROLL,
        KEY,
    };

    Type type;

    /**
    * X coordinate of input event.
    */
    double x;

    /**
    * Y coordinate of input event.
    */
    double y;

    /**
    * Key code of input event.
    */
    int key;

    /**
    * HID device button of input event.
    */
    int button;

    /**
    * Action type of input event (press|release)
    */
    int action;

    /**
    * Modifiers for input event (alt? shift?)
    */
    int mods;

    /**
    * Scan code of input event
    */
    int scancode;
} Input;

}

#endif