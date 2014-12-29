#ifndef GLSG_SCENENODEUPDATEVISITOR_H
#define GLSG_SCENENODEUPDATEVISITOR_H

#include <scenegraph/SceneNodeVisitor.h>

namespace glsg {

class SceneNodeUpdateVisitor : public SceneNodeVisitor {
public:
    SceneNodeUpdateVisitor(double dt) :
            _dt(dt),
            SceneNodeVisitor(VisitorType::UPDATE_VISITOR, VisitorMode::TRAVERSE_ALL) {}

    virtual void visit(SceneNode::Ptr sceneNode);

private:
    double _dt;
};

}

#endif
