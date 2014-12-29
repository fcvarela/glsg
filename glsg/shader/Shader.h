#ifndef GLSG_SHADER_H
#define GLSG_SHADER_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <render/GL.h>

namespace glsg {

class Shader : public std::enable_shared_from_this<Shader> {
public:
    typedef std::shared_ptr<Shader> Ptr;
    typedef std::vector<std::shared_ptr<Shader>> Vec;
    typedef std::map<std::string, std::shared_ptr<Shader>> Map;

    /**
    * Returns shared from this
    */
    Shader::Ptr getptr() {
        return shared_from_this();
    }

    Shader(const std::string &name, GLenum shaderType);

    virtual ~Shader();

    GLuint getShader();

    const std::string &getName();

    inline GLenum getType() {
        return _type;
    }

    void updateSource(const std::string &name, const char *source);

    inline void setModTime(uint64_t mtime) {
        _mtime = mtime;
    }

    inline uint64_t getModTime() {
        return _mtime;
    }

private:
    std::string _name;
    GLenum _type;
    GLuint _shader;
    uint64_t _mtime;
};

}

#endif
