#ifndef GLSG_FRAMEBUFFER_H
#define GLSG_FRAMEBUFFER_H

#include <string>
#include <memory>

#include <render/GL.h>
#include <glmext/glmext.h>

namespace glsg {

class Framebuffer {
public:
    typedef std::shared_ptr<Framebuffer> Ptr;

    // fixme: very crude and simple attachment management, this __NEEDS__ to be refined later
    // fixme: ie, RTT internal storage types, precision, etc
    Framebuffer(uint32_t width, uint32_t height, bool depthAttachment);
    ~Framebuffer();

    /**
    * Bind this framebuffer.
    */
    void activate();

    /**
    * Unbind this framebuffer.
    */
    void deactivate();

private:
    /**
    * Whether this framebuffer renders depth renderbuffer or not.
    */
    bool _depthAttachment;

    /**
    * The target texture width.
    */
    uint32_t _width;

    /**
    * The target texture height.
    */
    uint32_t _height;

    /**
    * Our target framebuffer.
    */
    GLuint _framebuffer;

    /**
    * Our target depth renderbuffer.
    */
    GLuint _depthRenderBuffer;

    /**
    * Our RTT target.
    */
    GLuint _texture;
};

}

#endif
