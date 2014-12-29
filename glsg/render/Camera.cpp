#include <log/Log.h>
#include <render/Camera.h>

namespace glsg {

Camera::Camera(double vfov, double near, double far) {
    _framebuffer = nullptr;
    _width = 0;
    _height = 0;
    _vfov = vfov;
    _near = near;
    _far = far;

    // set default clear mode
    _clearMode = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    // set default clear color
    _clearColor = glm::vec4(0.0, 0.0, 0.0, 1.0);
}

Camera::~Camera() {
}

void Camera::setClearColor(glm::vec4 clearColor) {
    _clearColor = clearColor;
}

void Camera::setClearMode(GLenum clearMode) {
    _clearMode = clearMode;
}

void Camera::setViewport(uint32_t width, uint32_t height) {
    _width = width;
    _height = height;

    double aspectRatio = (double)width / (double)height;

    _projectionMatrix = glm::perspective(glm::radians(_vfov), aspectRatio, _near, _far);
}

void Camera::setFramebuffer(Framebuffer::Ptr framebuffer) {
    _framebuffer = framebuffer;
}

Framebuffer::Ptr Camera::getFramebuffer() {
    return _framebuffer;
}

void Camera::setSceneNode(SceneNode::Ptr sceneNode) {
    _sceneNode = sceneNode;
}

SceneNode::Ptr Camera::getSceneNode() {
    return _sceneNode;
}

glm::dmat4 Camera::getProjectionMatrix() {
    return _projectionMatrix;
}

glm::dmat4 Camera::getViewMatrix() {
    return _sceneNode->getLocalToWorldMatrix();
}

void Camera::draw(SceneNode::Vec drawables) {
    LDEBUG("Camera drawing drawables");

    if (_framebuffer != nullptr) {
        _framebuffer->activate();
    }

    glViewport(0, 0, _width, _height);
    glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    glClear(_clearMode);

    glm::mat4 f_pm(_projectionMatrix);
    glm::mat4 f_vm(getViewMatrix());

    // go through the nodes which contain drawables and apply their renderstate
    for (auto drawable: drawables) {
        LDEBUG("Scene applying state for drawable");
        drawable->getState()->apply();

        //fixme: this should be optimized, uniform locations _should_ come from program in order to support caching
        //fixme: uniform values should come from nodes, which should be updated before drawing if dirty
        //fixme: shared uniforms (projection) should come from camera class and updated before drawing if dirty
        GLint projectionMatrix_id = glGetUniformLocation(drawable->getState()->program->getProgramID(), "projectionMatrix");
        GLint viewMatrix_id = glGetUniformLocation(drawable->getState()->program->getProgramID(), "viewMatrix");
        GLint modelMatrix_id = glGetUniformLocation(drawable->getState()->program->getProgramID(), "modelMatrix");

        glUniformMatrix4fv(projectionMatrix_id, 1, GL_FALSE, &f_pm[0][0]);
        glUniformMatrix4fv(viewMatrix_id, 1, GL_FALSE, &f_vm[0][0]);

        glm::mat4 f_mm(drawable->getLocalToWorldMatrix());

        glUniformMatrix4fv(modelMatrix_id, 1, GL_FALSE, &f_mm[0][0]);

        // get the meshes and draw them
        if (drawable->getMesh() != nullptr) {
            drawable->getMesh()->draw();
        }
    }

    if (_framebuffer != nullptr) {
        _framebuffer->deactivate();
    }

    LDEBUG("Camera finished");
}

}
