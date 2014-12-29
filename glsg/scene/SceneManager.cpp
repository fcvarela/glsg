#include <log/Log.h>
#include <scene/SceneManager.h>

namespace glsg {

SceneManager::SceneManager() {
    LINFO("Alloc");
}

SceneManager::~SceneManager() {
    LINFO("Dealloc");
}

void SceneManager::pushScene(Scene::Ptr scene) {
    _managedScenes.push(scene);
}

void SceneManager::popScene() {
    _managedScenes.pop();
}

void SceneManager::update(double dt) {
    _inputComponent->run(this, dt);

    if (_managedScenes.top() != nullptr) {
        _managedScenes.top()->update(dt);
    }
}

void SceneManager::cull() {
    if (_managedScenes.top() != nullptr) {
        _managedScenes.top()->cull();
    }
}

void SceneManager::draw() {
    if (_managedScenes.top() != nullptr) {
        _managedScenes.top()->draw();
    }
}

}
