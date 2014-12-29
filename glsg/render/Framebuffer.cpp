#include <render/Framebuffer.h>
#include <log/Log.h>

namespace glsg {

Framebuffer::Framebuffer(uint32_t width, uint32_t height, bool depthAttachment) :
        _depthAttachment(depthAttachment), _width(width), _height(height) {
    LINFO("Framebuffer alloc");

    // fixme: GL ops should be queued for execution outside main thread (early days)
    // fixme: this should use our future texture class
    LINFO("Initializing scene RTT target");
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // initialize our framebuffer
    LINFO("Initializing FB");
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

    // attach our depth renderbuffer
    if (depthAttachment) {
        LINFO("Initializing depth renderbuffer");
        glGenRenderbuffers(1, &_depthRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
    }

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _texture, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LFATAL("glCheckFramebufferStatus failed");
        throw;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    LINFO("Framebuffer alloc finished");
}

Framebuffer::~Framebuffer() {

}

void Framebuffer::activate() {
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}

void Framebuffer::deactivate() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}