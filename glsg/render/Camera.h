#ifndef GLSG_CAMERA_H
#define GLSG_CAMERA_H

#include <string>
#include <memory>

#include <glmext/glmext.h>
#include <render/Framebuffer.h>
#include <scenegraph/SceneNode.h>
#include <component/InputComponent.h>

namespace glsg {

class Camera {
public:
    typedef std::shared_ptr<Camera> Ptr;
    typedef std::map<std::string, Ptr> Map;

    Camera(double vfov, double near, double far);

    virtual ~Camera();

    /**
    * Set this camera's clear mode (before rendering).
    */
    void setClearMode(GLenum clearMode);

    /**
    * Set this camera's clear color.
    */
    void setClearColor(glm::vec4 clearColor);

    /**
    * Set this camera's viewport.
    */
    void setViewport(uint32_t width, uint32_t height);

    /**
    * Set this camera's framebuffer.
    */
    void setFramebuffer(Framebuffer::Ptr framebuffer);

    /**
    * Get this camera's framebuffer
    */
    Framebuffer::Ptr getFramebuffer();

    /**
    * Render this camera to an RTT target.
    */
    void draw(SceneNode::Vec drawables);

    /**
    * Sets this camera's scene node. Useful for attaching to scenegraph.
    * @param scenenode the scene node to set.
    */
    void setSceneNode(SceneNode::Ptr sceneNode);

    /**
    * Return this camera's scene node. Useful for attaching to scenegraph.
    */
    SceneNode::Ptr getSceneNode();

    /**
    * Returns this camera's projection matrix.
    */
    glm::dmat4 getProjectionMatrix();

    /**
    * Returns this camera's view matrix.
    */
    glm::dmat4 getViewMatrix();

    /**
    * Sets the camera's input component.
    */
    void setInputComponent(InputComponent *inputComponent) {
        _sceneNode->setInputComponent(inputComponent);
    }

private:
    /**
    * This camera's vertical field of view.
    */
    double _vfov;

    /**
    * This camera's near plane distance.
    */
    double _near;

    /**
    * This camera's far plane distance.
    */
    double _far;

    /**
    * This camera's clearmode.
    */
    GLenum _clearMode;

    /**
    * This camera's clear color.
    */
    glm::vec4 _clearColor;

    /**
    * This camera's RTT width.
    */
    uint32_t _width;

    /**
    * This camera's RTT height.
    */
    uint32_t _height;

    /**
    * This camera's framebuffer.
    */
    Framebuffer::Ptr _framebuffer;

    /**
    * This camera's scene node.
    */
    SceneNode::Ptr _sceneNode;

    /**
    * This camera's projection matrix.
    */
    glm::dmat4 _projectionMatrix;
};

}

#endif