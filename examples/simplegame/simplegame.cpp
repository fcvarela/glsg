#include <glsg/application/Application.h>
#include <glsg/script/PythonScript.h>

#include "SGSceneManagerInputComponent.h"
#include "SGAppInputComponent.h"

using namespace glsg;

Scene::Ptr makeGameScene(uint32_t width, uint32_t height) {
    auto scene = Scene::Ptr(new Scene("GameScene", width, height));
    PythonScript<Scene>::Ptr(new PythonScript<Scene>("game_scene", scene.get()));
    return scene;
}

Scene::Ptr makeMainMenuScene(uint32_t width, uint32_t height) {
    auto scene = Scene::Ptr(new Scene("MainMenuScene", width, height));
    PythonScript<Scene>::Ptr(new PythonScript<Scene>("mainmenu_scene", scene.get()));
    return scene;
}

int App_main() {
    // create the application instance
    auto app = Application::Ptr(new Application(640, 400, false));

    // create an input component for the app
    auto appInputComponent = new SGAppInputComponent();
    app->setInputComponent(appInputComponent);

    // create an input component for the scene manager
    auto sceneInputComponent = new SGSceneManagerInputComponent();
    SceneManager *sm = SceneManager::makeSceneManager(sceneInputComponent);
    app->setSceneManager(SceneManager::Ptr(sm));

    // create our mainmenu scene and push it to the scenemanager
    auto mainMenuScene = makeMainMenuScene(640, 400);
    sm->pushScene(mainMenuScene);

    // create our game scene and push it to the scenemanager
    auto gameScene = makeGameScene(640, 400);
    sm->pushScene(gameScene);

    // start the app
    app->start();

    // done
    return 0;
}
