#include <log/Log.h>
#include <scenegraph/SceneNodeUpdateVisitor.h>

namespace glsg {

void SceneNodeUpdateVisitor::visit(SceneNode::Ptr sceneNode) {
    LDEBUG("Update visitor visiting node: " << sceneNode->getName());

    // run our component updates
    auto input = sceneNode->getInputComponent();
    if (input != nullptr) {
        for (auto cmd : input->run(sceneNode.get(), _dt)) {
            cmd->run(sceneNode.get());
        }
    }

    if (sceneNode->dirtyTransform()) {
        LDEBUG("Node " << sceneNode->getName() << " has been moved or rotated, localToWorld needs update. Will recurse.");
        sceneNode->recomputeTransforms();
    }

    if (sceneNode->dirtyBounds()) {
        LDEBUG("Node " << sceneNode->getName() << " children or meshes have moved. Need bounds update.");
        sceneNode->recomputeBounds();
    }

    LDEBUG("Update visitor visited node: " << sceneNode->getName());
}

}
