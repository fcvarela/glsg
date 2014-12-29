#ifndef GLSG_PROGRAM_H
#define GLSG_PROGRAM_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <render/GL.h>
#include <shader/Shader.h>

namespace glsg {

class Program {
public:
    typedef std::shared_ptr<Program> Ptr;
    typedef std::map<std::string, std::shared_ptr<Program>> Map;
    
    Program(const std::string &name);

    virtual ~Program();

    void attach(Shader *shader);

    void link();

    GLuint getProgramID();

    void activate();

    static void deactivate();

    void reload();

private:
    GLuint _program;
    std::string _name;
    std::map<std::string, Shader *> _shaders;
};

}

#endif
