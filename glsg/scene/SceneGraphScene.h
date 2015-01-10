#ifndef GLSG_SCENEGRAPHSCENE_H
#define GLSG_SCENEGRAPHSCENE_H

#include <memory>
#include <vector>
#include <stack>

#include <external/imgui/imgui.h>
#include <scenegraph/SceneNode.h>
#include <render/Camera.h>
#include <scene/Scene.h>

namespace glsg {
/**
* A scene manages a single scenegraph. It interfaces external events (window, input, etc) to a
* single scene graph, and manages the graphs rendering pipeline (camera and renderpasses).
* @ingroup scene
*/
class SceneGraphScene : public Scene {
public:
    typedef std::shared_ptr<SceneGraphScene> Ptr;

    /**
    * SceneGraphScene constructor.
    */
    SceneGraphScene(const std::string &name, uint32_t width, uint32_t height);

    /**
    * SceneGraphScene destructor.
    */
    virtual ~SceneGraphScene();

    /**
    * Sets the camera map entry to provided camera.
    */
    void setCamera(const std::string &name, Camera::Ptr camera);

    /**
    * Gets the camera with the given name
    */
    Camera::Ptr getCamera(const std::string &name);

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
