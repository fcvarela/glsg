#ifndef GLSG_INPUT_H
#define GLSG_INPUT_H

namespace glsg {

typedef struct {
    bool valid;
    double x, y;
    double dist_x, dist_y;
} MouseMove;

typedef struct {
    bool valid;
    double x, y;
    int action;
} MouseClick;

typedef struct {
    bool valid;
    int key, action, mods, scancode;
    bool active[255];
} Key;

typedef struct {
    MouseMove mouseMove;
    MouseClick mouseClick;
    Key key;
} Input;

}

#endif