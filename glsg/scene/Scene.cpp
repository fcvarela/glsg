#include <log/Log.h>
#include <scene/Scene.h>
#include <scenegraph/SceneNodeUpdateVisitor.h>
#include <scenegraph/SceneNodeCullVisitor.h>

namespace glsg {

Scene::Scene(const std::string &name, uint32_t width, uint32_t height) :
        _name(name), _width(width), _height(height) {
    LINFO("Alloc - " << _name);
}

Scene::~Scene() {
    LINFO("Dealloc - " << _name);
}

void Scene::setSceneGraph(SceneNode::Ptr sceneGraph) {
    _sceneGraph = sceneGraph;
}

void Scene::setCamera(const std::string &name, Camera::Ptr camera) {
    _cameras[name] = camera;
    _cameras[name]->setViewport(_width, _height);
}

void Scene::update(double dt) {
    LDEBUG("Update start - " << _name);

    if (_sceneGraph == nullptr) {
        LWARNING("Scene update aborting, no scenegraph");
        return;
    }

    SceneNodeUpdateVisitor visitor(dt);
    _sceneGraph->accept(visitor);

    LDEBUG("Update finish - " << _name);
}

void Scene::cull() {
    LDEBUG("Cull start");

    if (_sceneGraph == nullptr) {
        LWARNING("Scene cull aborting, no scenegraph");
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

void Scene::draw() {
    LDEBUG("Draw start");

    for (auto camera: _cameras) {
        camera.second->draw(_drawables[camera.first]);
    }

    LDEBUG("Draw finish");
}

}
