#include <log/Log.h>
#include "SceneGraphScene.h"
#include <scenegraph/SceneNodeUpdateVisitor.h>
#include <scenegraph/SceneNodeCullVisitor.h>

namespace glsg {

SceneGraphScene::SceneGraphScene(const std::string &name, uint32_t width, uint32_t height) {
    _name = name;
    _width = width;
    _height = height;
    LINFO("Alloc - " << _name);
}

SceneGraphScene::~SceneGraphScene() {
    LINFO("Dealloc - " << _name);
}

void SceneGraphScene::setSceneGraph(SceneNode::Ptr sceneGraph) {
    _sceneGraph = sceneGraph;
}

void SceneGraphScene::setCamera(const std::string &name, Camera::Ptr camera) {
    _cameras[name] = camera;
    _cameras[name]->setViewport(_width, _height);
}

void SceneGraphScene::update(double dt) {
    LDEBUG("Update start - " << _name);

    if (_sceneGraph == nullptr) {
        LWARNING("SceneGraphScene update aborting, no scenegraph");
        return;
    }

    SceneNodeUpdateVisitor visitor(dt);
    _sceneGraph->accept(visitor);

    LDEBUG("Update finish - " << _name);
}

void SceneGraphScene::cull() {
    LDEBUG("Cull start");

    if (_sceneGraph == nullptr) {
        LWARNING("SceneGraphScene cull aborting, no scenegraph");
        return;
    }

    // iterate though cameras and cull - draw
    for (auto camera: _cameras) {
        SceneNodeCullVisitor visitor;
        _sceneGraph->accept(visitor);

        LDEBUG("Clearing drawables to create sorted list for camera" << camera.first);

        _drawables.clear();

        for (auto node: visitor.getVisited()) {
            if (node->getMesh() != nullptr) {
                _drawables[camera.first].push_back(node);
            }
        }

        LDEBUG("Got " << _drawables.size() << " drawables visible for camera" << camera.first);
    }

    LDEBUG("Cull finished");
}

void SceneGraphScene::draw() {
    LDEBUG("Draw start");

    for (auto camera: _cameras) {
        camera.second->draw(_drawables[camera.first]);
    }

    LDEBUG("Draw finish");
}

}
