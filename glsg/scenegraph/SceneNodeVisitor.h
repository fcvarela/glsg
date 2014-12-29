#ifndef GLSG_SCENENODEVISITOR_H
#define GLSG_SCENENODEVISITOR_H

#include <scenegraph/SceneNode.h>

namespace glsg {

/**
* A scene graph traversal visitor from which specific traversal types inherit from.
* @ingroup scenegraph
*/
class SceneNodeVisitor {
public:
    /**
    * List of VisitorModes, by traversal type. Traverse all will always cause node to accept
    * visitor, traverse active will cause nodes marked inactive to reject traversal.
    */
    enum VisitorMode {
        TRAVERSE_ALL,
        TRAVERSE_ACTIVE
    };

    /**
    * The traversal type, for node information purposes.
    */
    enum VisitorType {
        UPDATE_VISITOR,
        CULL_VISITOR
    };

    /**
    * SceneNodeVisitor constructor.
    * @param visitorType the visitor type.
    * @param visitorMode the visitor traversal mode.
    */
    SceneNodeVisitor(VisitorType visitorType, VisitorMode visitorMode);

    /**
    * Returns the visitor type.
    */
    virtual VisitorType getVisitorType();

    /**
    * Returns the visitor mode.
    */
    virtual VisitorMode getVisitorMode();

    /**
    * The visitor traversal method signature.
    * @param SceneNode* a pointer to the visitee scene node.
    */
    virtual void visit(SceneNode::Ptr sceneNode) = 0;

private:
    /**
    * Holds this visitor visitorMode.
    */
    VisitorMode _visitorMode;

    /**
    * Holds this visitor visitorType.
    */
    VisitorType _visitorType;
};

}

#endif
