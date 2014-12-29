#include <log/Log.h>

#include <input/InputListener.h>

namespace glsg {

Input InputListener::_input;

void InputListener::mouse_move_callback(GLFWwindow *window, double x, double y) {
    LDEBUG("MOUSE MOVE CALLBACK");

    _input.type = Input::MOUSEMOVE;
    _input.x = x;
    _input.y = y;
}

void InputListener::mouse_click_callback(GLFWwindow *window, int button, int action, int mods) {
    LDEBUG("MOUSE CLICK CALLBACK");

    _input.type = Input::MOUSEBUTTON;
    _input.button = button;
    _input.action = action;
    _input.mods = mods;
}

void InputListener::mouse_scroll_callback(GLFWwindow *window, double x, double y) {
    LDEBUG("MOUSE SCROLL CALLBACK");

    _input.type = Input::MOUSESCROLL;
    _input.x = x;
    _input.y = y;
}

void InputListener::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    LDEBUG("KEY CALLBACK");

    _input.type = Input::KEY;
    _input.key = key;
    _input.scancode = scancode;
    _input.action = action;
    _input.mods = mods;
}

void InputListener::initialize() {
    LINFO("Starting");

    // register callbacks
    glfwSetKeyCallback(glsg::graphics::getWindow(), InputListener::key_callback);
    glfwSetMouseButtonCallback(glsg::graphics::getWindow(), InputListener::mouse_click_callback);
    glfwSetCursorPosCallback(glsg::graphics::getWindow(), InputListener::mouse_move_callback);
    glfwSetScrollCallback(glsg::graphics::getWindow(), InputListener::mouse_scroll_callback);
}

void InputListener::poll() {
    LDEBUG("Polling events");
    _input.type = Input::INVALID;
    glfwPollEvents();
}

}
