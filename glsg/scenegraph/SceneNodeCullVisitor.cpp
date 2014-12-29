#include <log/Log.h>
#include <scenegraph/SceneNodeCullVisitor.h>

namespace glsg {

void SceneNodeCullVisitor::visit(SceneNode::Ptr sceneNode) {
    LDEBUG("Cull visitor visited node: " << sceneNode->getName());

    _visited.push_back(sceneNode);
}

std::vector<SceneNode::Ptr> SceneNodeCullVisitor::getVisited() {
    return _visited;
}

}
