#ifndef GLSG_GL_H
#define GLSG_GL_H

#include <GL/glew.h>

#ifdef __APPLE__

#include <OpenCL/OpenCL.h>

#else
#include <CL/cl.h>
#endif

#if defined ( __APPLE__ ) || defined ( MACOSX )
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL

#include <OpenGL/OpenGL.h>

#elif defined ( WIN32 )
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
#else
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace glsg {

namespace graphics {
void initialize();

double dt();

void shutdown();

GLFWwindow *getWindow();

extern GLFWwindow *_window;

void makeFullscreenContext();

void makeWindowContext(uint32_t width, uint32_t height);

void swapBuffers();

}

}

#endif
