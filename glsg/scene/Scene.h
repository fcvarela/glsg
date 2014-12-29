#ifndef GLSG_SCENE_H
#define GLSG_SCENE_H

#include <memory>
#include <vector>
#include <stack>

#include <scenegraph/SceneNode.h>
#include <render/Camera.h>
#include <core/Object.h>

namespace glsg {

/**
* @defgroup scenegraph scenegraph
* @ingroup glsg
* A simple scenegraph implementation.
*/

/**
* A scene manages a single scenegraph. It interfaces external events (window, input, etc) to a
* single scene graph, and manages the graphs rendering pipeline (camera and renderpasses).
* @ingroup scenegraph
*/
class Scene: public Object {
public:
    typedef std::shared_ptr<Scene> Ptr;
    typedef std::stack<Ptr> Stack;

    /**
    * Scene constructor.
    */
    Scene(const std::string &name, uint32_t width, uint32_t height);

    /**
    * Scene destructor.
    */
    virtual ~Scene();

    /**
    * Sets the camera map entry to provided camera.
    */
    virtual void setCamera(const std::string &name, Camera::Ptr camera);

    /**
    * Sets the root node of the managed scene graph.
    */
    void setSceneGraph(SceneNode::Ptr sceneGraph);

    /**
    * Runs the update traversal.
    * @param dt time elapsed since last call, in seconds.
    */
    void update(double dt);

    /**
    * Runs the cull traversal.
    */
    void cull();

    /**
    * Draws the scene to the set render target.
    */
    void draw();

private:
    /**
    * This scene's name.
    */
    std::string _name;

    /**
    * The RTT width.
    */
    uint32_t _width;

    /**
    * The RTT height.
    */
    uint32_t _height;

    /**
    * The SceneGraph managed by this scene.
    */
    SceneNode::Ptr _sceneGraph;

    /**
    * The drawables extracted from this scenegraph on cull.
    */
    std::map<std::string, SceneNode::Vec> _drawables;

    /**
    * Our camera collection.
    */
    Camera::Map _cameras;
};

}

#endif
