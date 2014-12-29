#ifndef GLSG_SHADERREGISTRY_H
#define GLSG_SHADERREGISTRY_H

#include <string>
#include <memory>
#include <mutex>

#include <shader/Shader.h>
#include <shader/Program.h>
#include <resource/ResourceLoader.h>

namespace glsg {

class ShaderRegistry {
public:
    ~ShaderRegistry() {
        LDEBUG("ShaderRegistry dealloc");
    }

    static ShaderRegistry *get() {
        static ShaderRegistry *_instance = new ShaderRegistry();
        return _instance;
    }

    Program *loadProgram(const std::string &programScript);

    Shader *loadShader(const std::string &shaderFile, GLenum shaderType);

    void preprocessShaderResource(ResourceLoader::Resource &res);

    void updateShaders();

private:
    ShaderRegistry() {
        LDEBUG("ShaderRegistry alloc");
    };

    Shader::Map _shaders;
    Program::Map _programs;
};

}

#endif
