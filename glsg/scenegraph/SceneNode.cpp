#include <log/Log.h>
#include <scenegraph/SceneNode.h>
#include <scenegraph/SceneNodeVisitor.h>
#include <render/MeshLoader.h>

namespace glsg {

SceneNode::SceneNode(const std::string &name) :
        _name(name), _localBounds(glm::dbox3()) {

    LINFO("Alloc " << name);

    _transformMatrix = glm::dmat4(1.0);
    _localToWorldMatrix = glm::dmat4(1.0);
    _active = true;
    _parent = nullptr;
    _dirtyTransform = false;
    _dirtyBounds = false;
}

const std::string &SceneNode::getName() {
    return _name;
}

SceneNode::~SceneNode() {
    LINFO("Dealloc " << _name);
}

Mesh::Ptr SceneNode::getMesh() {
    return _mesh;
}

void SceneNode::loadMesh(const std::string &name) {
    _mesh = MeshLoader::loadMesh(name);
    _dirtyBounds = true;
}

void SceneNode::removeMesh() {
    _mesh = nullptr;
    _dirtyBounds = true;
}

std::vector<SceneNode::Ptr> SceneNode::getChildren() {
    return _children;
}

uint64_t SceneNode::getChildrenCount() {
    return _children.size();
}

SceneNode::Ptr SceneNode::getChild(int index) {
    return _children[index];
}

void SceneNode::addChild(SceneNode::Ptr child) {
    child->setParent(this);
    _children.push_back(child);
    _dirtyBounds = true;
}

void SceneNode::removeChild(int index) {
    _children.erase(_children.begin() + index);
    _dirtyBounds = true;
}

void SceneNode::setParent(SceneNode *parentNode) {
    _parent = parentNode;
}

void SceneNode::rotate(double angle, double x, double y, double z) {
    _transformMatrix = glm::rotate(_transformMatrix, angle, glm::dvec3(x, y, z));
    _dirtyTransform = true;
}

void SceneNode::translate(double x, double y, double z) {
    _transformMatrix = glm::translate(_transformMatrix, glm::dvec3(x, y, z));
    _dirtyTransform = true;
}

glm::dbox3 SceneNode::getLocalBounds() {
    if (_dirtyBounds) {
        recomputeBounds();
    }

    return _localBounds;
}

void SceneNode::recomputeBounds() {
    // do not update until all children are done
    LDEBUG("Node " << _name << " updating bounds");
    _localBounds = glm::dbox3();

    for (auto c: _children) {
        // extend our bounds by our childrens localToParent matrix
        _localBounds.extend(glm::dvec3(c->getTransformMatrix() * glm::dvec4(c->getLocalBounds().minimum, 1.0)));
        _localBounds.extend(glm::dvec3(c->getTransformMatrix() * glm::dvec4(c->getLocalBounds().maximum, 1.0)));
    }

    if (_mesh != nullptr) {
        _localBounds.extend(_mesh->getBounds());
    }

    // now we need to recompute our bounds in world space
    _worldBounds = glm::dbox3();
    _worldBounds.extend(glm::dvec3(_localToWorldMatrix * glm::dvec4(_localBounds.minimum, 1.0)));
    _worldBounds.extend(glm::dvec3(_localToWorldMatrix * glm::dvec4(_localBounds.maximum, 1.0)));

    _dirtyBounds = false;
}

glm::dbox3 SceneNode::getWorldBounds() {
    return _worldBounds;
}

glm::dmat4 SceneNode::getTransformMatrix() {
    return _transformMatrix;
}

glm::dmat4 SceneNode::getLocalToWorldMatrix() {
    return _localToWorldMatrix;
}

glm::dmat4 SceneNode::getWorldToLocalMatrix() {
    return _worldToLocalMatrix;
}

glm::dvec3 SceneNode::getWorldPosition() {
    return _worldPosition;
}

void SceneNode::setActive(bool active) {
    _active = active;
}

void SceneNode::recomputeTransforms() {
    if (_parent != nullptr) {
        _localToWorldMatrix = _parent->getLocalToWorldMatrix() * _transformMatrix;
    } else {
        _localToWorldMatrix = _transformMatrix;
    }

    // this needs to be recursive
    for (auto child : _children) {
        child->recomputeTransforms();
    }

    _worldToLocalMatrix = glm::inverse(_localToWorldMatrix);
    _worldPosition = glm::dvec3(_localToWorldMatrix * glm::dvec4(1.0));

    _dirtyTransform = false;

    // we moved or rotated, therefore, we should notify our parent that its bounds
    // need to be recomputed
    if (_parent != nullptr) {
        LDEBUG("Node " << _name << " setting dirty parent bounds");
        _parent->_dirtyBounds = true;
    }
}

void SceneNode::accept(SceneNodeVisitor &visitor) {
    // abort if we're not active
    if (visitor.getVisitorMode() == SceneNodeVisitor::VisitorMode::TRAVERSE_ACTIVE && !_active) {
        return;
    }

    // visit us
    visitor.visit(shared_from_this());

    // traverse children
    for (auto child: _children) {
        child->accept(visitor);
    }
}

}
