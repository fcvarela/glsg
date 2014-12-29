#include <mutex>
#include <shader/Program.h>
#include <script/PythonScript.h>

namespace glsg {

Program::Program(const std::string &name) {
    LINFO("Alloc");
    _name = name;
    _program = glCreateProgram();
    PythonScript<Program>::Ptr(new PythonScript<Program>(name, this));
}

Program::~Program() {
    LINFO("Dealloc " << _name << " deallocating and deleting GL object");
    glDeleteProgram(_program);
}

void Program::attach(Shader *shader) {
    LDEBUG("Program " << _name << " attaching shader: " << shader->getName());

    glAttachShader(_program, shader->getShader());
    _shaders[shader->getName()] = shader;
}

void Program::link() {
    LDEBUG("Program " << _name << " (" << _program << ") linking");

    glLinkProgram(_program);
    GLint status;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(_program, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        LERROR(msg);
    }
}

void Program::reload() {
    link();
}

GLuint Program::getProgramID() {
    return _program;
}

void Program::activate() {
    glUseProgram(_program);
}

void Program::deactivate() {
    glUseProgram(0);
}

}
