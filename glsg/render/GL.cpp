#include <log/Log.h>
#include <state/State.h>

namespace glsg {

namespace graphics {

GLFWwindow *_window = NULL;

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
    _window = glfwCreateWindow(mode->width, mode->height, " ", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw ("ERROR: glewInit failed\n");
    }

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    LINFO("Renderer: " << renderer << " (" << version << ")");

    State::setDefault();
}

void makeWindowContext(uint32_t width, uint32_t height) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(width, height, " ", NULL, NULL);
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw ("ERROR: glewInit failed\n");
    }

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    LINFO("Renderer: " << renderer << " (" << version << ")");

    State::setDefault();
}

GLFWwindow *getWindow() {
    return _window;
}

void swapBuffers() {
    glfwSwapBuffers(_window);
}

}

}
