#ifndef GLSG_INPUTLISTENER_H
#define GLSG_INPUTLISTENER_H

#include <render/GL.h>
#include <input/Input.h>

namespace glsg {

class InputListener {
public:
    static void mouse_move_callback(GLFWwindow *window, double x, double y);

    static void mouse_click_callback(GLFWwindow *window, int button, int action, int mods);

    static void mouse_scroll_callback(GLFWwindow *window, double x, double y);

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void initialize();

    static void poll();

    static inline Input *getInput() {
        return &_input;
    }

private:
    static Input _input;
};

}

#endif
