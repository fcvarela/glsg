#ifndef GLSG_APPLICATION_H
#define GLSG_APPLICATION_H

#include <string>

#include <core/Object.h>
#include <core/StateMachine.h>
#include <component/InputComponent.h>
#include <render/GL.h>
#include <scene/SceneManager.h>

namespace glsg {

/**
* @defgroup application application
* @ingroup glsg
* Provides Windowing and context management support for client applications.
*/

/**
* An application is the higher level entity and manages every other subsystem.
* @ingroup application
*/
class Application: public Object {
public:
    typedef std::shared_ptr<Application> Ptr;

    /**
    * Default constructor, will initialize subsystems
    * @param width Width of the window.
    * @param height Height of the window.
    * @param whether to set this window to fullscreen mode.
    */
    Application(uint32_t width, uint32_t height, bool fullscreen);

    /**
    * Deletes the window and destroys its context.
    */
    virtual ~Application();

    /**
    * Starts the window main loop.
    */
    void start();

    /**
    * Terminates the main loop, clean shutdown and cascading dealloc.
    */
    void stop();

    /**
    * Issues the update traversal.
    */
    virtual void update(double dt);

    /**
    * Set a scene manager.
    * @param sceneManager a user-provided scene manager.
    */
    void setSceneManager(SceneManager::Ptr sceneManager) {
        _sceneManager = sceneManager;
    }

    /**
    * Sets the application's input component.
    */
    void setInputComponent(InputComponent *inputComponent) {
        _inputComponent = InputComponent::Ptr(inputComponent);
    }

private:
    /**
    * Continue running flag.
    */
    bool _wantsStop;

    /**
    * This application's scenemanager.
    */
    SceneManager::Ptr _sceneManager;

    /**
    * Application input component.
    */
    InputComponent::Ptr _inputComponent;
};

}

#endif
