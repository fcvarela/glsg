#include <glsg/application/Application.h>
#include <glsg/script/PythonScript.h>
#include <glsg/scene/UIScene.h>
#include <glsg/scene/SceneGraphScene.h>

#include "SGSceneManagerInputComponent.h"
#include "SGCameraInputComponent.h"
#include "SGAppInputComponent.h"

using namespace glsg;

SceneGraphScene::Ptr makeGameScene(uint32_t width, uint32_t height) {
    auto scene = SceneGraphScene::Ptr(new SceneGraphScene("GameScene", width, height));
    PythonScript<SceneGraphScene>::Ptr(new PythonScript<SceneGraphScene>("game_scene", scene.get()));

    // add our custom handler to this scene's camera (script this later)
    auto cameraInputComponent = new SGCameraInputComponent();
    scene->getCamera("mainCamera")->setInputComponent(cameraInputComponent);
    return scene;
}

UIScene::Ptr makeMainMenuScene(uint32_t width, uint32_t height) {
    auto scene = UIScene::Ptr(new UIScene("MainMenuScene", width, height));
    PythonScript<UIScene>::Ptr(new PythonScript<UIScene>("mainmenu_scene", scene.get()));
    return scene;
}

int App_main() {
    // create the application instance with an input component
    auto app = Application::Ptr(new Application(960, 600, false));
    auto appInputComponent = new SGAppInputComponent();
    app->setInputComponent(appInputComponent);

    // create an input component for the scene manager
    auto sceneManager = SceneManager::Ptr(new SceneManager());
    auto sceneManagerInputComponent = new SGSceneManagerInputComponent();
    sceneManager->setInputComponent(sceneManagerInputComponent);

    // set scenemanager to app
    app->setSceneManager(SceneManager::Ptr(sceneManager));

    // create our mainmenu scene and push it to the scenemanager
    auto mainMenuScene = makeMainMenuScene(glsg::graphics::getWidth(), glsg::graphics::getHeight());
    sceneManager->pushScene(mainMenuScene);

    // create our game scene and push it to the scenemanager
    auto gameScene = makeGameScene(glsg::graphics::getWidth(), glsg::graphics::getHeight());
    sceneManager->pushScene(gameScene);

    // start the app
    app->start();

    // done
    return 0;
}
