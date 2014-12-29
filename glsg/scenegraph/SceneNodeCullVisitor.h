#ifndef GLSG_SCENENODECULLVISITOR_H
#define GLSG_SCENENODECULLVISITOR_H

#include <scenegraph/SceneNodeVisitor.h>

namespace glsg {

class SceneNodeCullVisitor : public SceneNodeVisitor {
public:
    SceneNodeCullVisitor() :
            SceneNodeVisitor(VisitorType::CULL_VISITOR, VisitorMode::TRAVERSE_ACTIVE)
    {

    }

    virtual void visit(SceneNode::Ptr sceneNode);
    virtual SceneNode::Vec getVisited();
private:
    SceneNode::Vec _visited;
};

}

#endif
