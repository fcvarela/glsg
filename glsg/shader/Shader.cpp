#include <render/GL.h>
#include <shader/Shader.h>
#include <log/Log.h>

namespace glsg {

Shader::Shader(const std::string &name, GLenum shaderType) {
    LINFO("Alloc");

    _type = shaderType;
    _name = name;

    LDEBUG("Creating shader: " << _name);

    _shader = glCreateShader(_type);

    GLenum err = glGetError();
    if (err == GL_INVALID_VALUE) {
        LERROR("Invalid value");
    } else if (err == GL_INVALID_OPERATION) {
        LERROR("Invalid operation");
    } else if (err == GL_INVALID_ENUM) {
        LERROR("Invalid enum");
    }
}

Shader::~Shader() {
    LDEBUG("Dealloc " << _name);
    glDeleteShader(_shader);
}

void Shader::updateSource(const std::string &name, const char *source) {
    glShaderSource(_shader, 1, &source, NULL);
    GLenum err = glGetError();
    if (err == GL_INVALID_VALUE) {
        LERROR("Invalid value");
    } else if (err == GL_INVALID_OPERATION) {
        LERROR("Invalid operation");
    } else if (err == GL_INVALID_ENUM) {
        LERROR("Invalid enum");
    }

    LINFO("Compiling: " << name);
    glCompileShader(_shader);
    err = glGetError();
    if (err == GL_INVALID_VALUE) {
        LERROR("Invalid value");
    } else if (err == GL_INVALID_OPERATION) {
        LERROR("Invalid operation");
    } else if (err == GL_INVALID_ENUM) {
        LERROR("Invalid enum");
    }

    GLint success = 0;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        LERROR("Error: Shader " << name << " failed to compile:");

        GLint logSize;
        glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logSize);

        char *logMsg = new char[logSize];
        glGetShaderInfoLog(_shader, logSize, NULL, logMsg);

        LERROR(logMsg);

        delete[] logMsg;
    }

}

GLuint Shader::getShader() {
    return _shader;
}

const std::string &Shader::getName() {
    return _name;
}

}
