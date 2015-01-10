#ifndef GLSG_SCENEMANAGER_H
#define GLSG_SCENEMANAGER_H

#include <core/Object.h>
#include <scene/Scene.h>
#include <scene/SceneManager.h>
#include <component/InputComponent.h>

namespace glsg {
/**
* A scenemanager manages a stack of scenes using a state machine and command interface.
* @ingroup scene
*/
class SceneManager: public Object {
public:
    typedef std::shared_ptr<SceneManager> Ptr;

    SceneManager();

    virtual ~SceneManager();

    void pushScene(Scene::Ptr scene);

    void popScene();

    void update(double dt);

    void cull();

    void draw();

    inline void setInputComponent(InputComponent *inputComponent) {
        _inputComponent = InputComponent::Ptr(inputComponent);
    }

private:
    /**
    * The scene manager's scenes.
    */
    Scene::Stack _managedScenes;

    /**
    * The input component.
    */
    InputComponent::Ptr _inputComponent;
};

}

#endif
