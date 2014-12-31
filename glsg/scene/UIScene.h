#ifndef GLSG_UISCENE_H
#define GLSG_UISCENE_H

#include <scene/Scene.h>

namespace glsg {
/**
* A UIScene manages 2D UI scene. It merges both scene and camera behaviours as it is implemented
* as an immediate mode UI using IMGUI.
* @ingroup scene
*/
class UIScene: public Scene {
public:
    typedef std::shared_ptr<UIScene> Ptr;

    /**
    * UIScene default constructor
    */
    UIScene(const std::string &name, uint32_t width, uint32_t height);

    /**
    * UIScene destructor.
    */
    virtual ~UIScene();

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
};

}

#endif