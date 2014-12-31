#include <log/Log.h>
#include <render/GL.h>
#include <scene/UIScene.h>

namespace glsg {

UIScene::UIScene(const std::string &name, uint32_t width, uint32_t height) {
    LINFO("Alloc");

    _name = name;
    _width = _width;
    _height = _height;
}

void UIScene::update(double dt) {}

void UIScene::cull() {}

void UIScene::draw() {
    glViewport(0, 0, _width, _height);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

UIScene::~UIScene() {
    LINFO("Dealloc");
}

}
