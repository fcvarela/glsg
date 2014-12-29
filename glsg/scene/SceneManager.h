#ifndef _GLSG_SCENEMANAGER_H
#define _GLSG_SCENEMANAGER_H

#include <core/Object.h>
#include <scene/Scene.h>
#include <scene/SceneManager.h>
#include <component/InputComponent.h>

namespace glsg {

class SceneManager: public Object {
public:
    typedef std::shared_ptr<SceneManager> Ptr;

    SceneManager();

    ~SceneManager();

    void pushScene(Scene::Ptr scene);

    void popScene();

    void update(double dt);

    void cull();

    void draw();

    /**
    * Factory method to make scenemanager.
    * @param inputComponent set this input component.
    */
    static SceneManager *makeSceneManager(
            InputComponent *inputComponent
    ) {
        SceneManager *sm = new SceneManager();
        sm->_inputComponent = InputComponent::Ptr(inputComponent);
        return sm;
    }


private:
    Scene::Stack _managedScenes;

    /**
    * The input component.
    */
    InputComponent::Ptr _inputComponent;
};

}

#endif
