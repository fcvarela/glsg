#ifndef GLSG_SCENE_H
#define GLSG_SCENE_H

#include <memory>
#include <stack>

#include <core/Object.h>

namespace glsg {
/**
* @defgroup scene scene
* @ingroup glsg
* Scene management classes. SceneManager manages a stack of Scene implementations. It uses a state machine
* to react to user events and determine which scene to present. It forwards events to the active scene.
* The active scene requires its own event handlers to be provided by the user.
*/

/**
* A scene is an abstract class which exposes traversal methods to the scenemanager.
* It encapsulates the entire app/game logic for a given part of the application.
* @ingroup scene
*/
class Scene: public Object {
public:
    typedef std::shared_ptr<Scene> Ptr;
    typedef std::stack<Ptr> Stack;

    /**
    * Runs the update traversal.
    * @param dt time elapsed since last call, in seconds.
    */
    virtual void update(double dt) = 0;

    /**
    * Runs the cull traversal.
    */
    virtual void cull() = 0;

    /**
    * Draws the scene to the set render target.
    */
    virtual void draw() = 0;

protected:
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
};

}

#endif