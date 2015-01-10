#include <log/Log.h>

#include <input/InputListener.h>

namespace glsg {

Input InputListener::_input;

void InputListener::mouse_move_callback(GLFWwindow *window, double x, double y) {
    LDEBUG("MOUSE MOVE CALLBACK");
//    if (TwEventMousePosGLFW(x, y))
//        return;

    _input.mouseMove.valid = true;

    _input.mouseMove.dist_x = x - _input.mouseMove.x;
    _input.mouseMove.dist_y = y - _input.mouseMove.y;

    _input.mouseMove.x = x;
    _input.mouseMove.y = y;
}

void InputListener::mouse_click_callback(GLFWwindow *window, int button, int action, int mods) {
    LDEBUG("MOUSE CLICK CALLBACK");

//    if (TwEventMouseButtonGLFW(button, action))
//        return;

}

void InputListener::mouse_scroll_callback(GLFWwindow *window, double x, double y) {
    LDEBUG("MOUSE SCROLL CALLBACK");
}

void InputListener::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    LDEBUG("KEY CALLBACK");

    _input.key.valid = true;
    _input.key.key = key;
    _input.key.scancode = scancode;
    _input.key.action = action;
    _input.key.mods = mods;

    if (action == GLFW_PRESS) {
        _input.key.active[key] = true;
    }

    if (action == GLFW_RELEASE) {
        _input.key.active[key] = false;
    }
}

void InputListener::initialize() {
    LINFO("Starting");

    // reset cursor position
    int width, height;
    glfwGetWindowSize(glsg::graphics::getWindow(), &width, &height);
    glfwSetCursorPos(glsg::graphics::getWindow(), width/2, height/2);
    glfwGetCursorPos(glsg::graphics::getWindow(),
            &_input.mouseMove.x,
            &_input.mouseMove.y
    );

    _input.mouseMove.dist_x = 0;
    _input.mouseMove.dist_y = 0;
    glfwSetInputMode(glsg::graphics::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // register callbacks
    glfwSetKeyCallback(glsg::graphics::getWindow(), InputListener::key_callback);
    glfwSetMouseButtonCallback(glsg::graphics::getWindow(), InputListener::mouse_click_callback);
    glfwSetCursorPosCallback(glsg::graphics::getWindow(), InputListener::mouse_move_callback);
    glfwSetScrollCallback(glsg::graphics::getWindow(), InputListener::mouse_scroll_callback);
}

void InputListener::poll() {
    LDEBUG("Polling events");

    _input.mouseMove.valid = false;
    _input.mouseClick.valid = false;
    _input.key.valid = false;

    glfwPollEvents();
}

}
