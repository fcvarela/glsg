#include <log/Log.h>
#include <state/State.h>
#include <AntTweakBar.h>

namespace glsg {

namespace graphics {

GLFWwindow *_window = NULL;
uint32_t _width = 0;
uint32_t _height = 0;

void initialize() {
    LINFO("Graphics starting");
    glfwInit();
}

double dt() {
    return glfwGetTime();
}

void shutdown() {
    LINFO("Graphics shutdown");
    glfwSetWindowShouldClose(_window, 1);
    glfwTerminate();
}

void makeFullscreenContext() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    _width = (uint32_t)mode->width;
    _height = (uint32_t)mode->height;

    _window = glfwCreateWindow(_width, _height, " ", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw ("ERROR: glewInit failed\n");
    }

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    LINFO("Renderer: " << renderer << " (" << version << ")");

    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(_width, _height);

    State::setDefault();
}

void makeWindowContext(uint32_t width, uint32_t height) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(width, height, " ", NULL, NULL);
    _width = width;
    _height = height;
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw ("ERROR: glewInit failed\n");
    }

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    LINFO("Renderer: " << renderer << " (" << version << ")");

    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(_width, _height);

    State::setDefault();
}

GLFWwindow *getWindow() {
    return _window;
}

uint32_t getWidth() {
    return _width;
}

uint32_t getHeight() {
    return _height;
}

void swapBuffers() {
//    TwDraw();
    glfwSwapBuffers(_window);
}

}

}
