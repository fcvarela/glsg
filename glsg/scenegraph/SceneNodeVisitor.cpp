#include <scenegraph/SceneNodeVisitor.h>

namespace glsg {

SceneNodeVisitor::SceneNodeVisitor(SceneNodeVisitor::VisitorType visitorType, SceneNodeVisitor::VisitorMode visitorMode) {
    _visitorType = visitorType;
    _visitorMode = visitorMode;
}

SceneNodeVisitor::VisitorType SceneNodeVisitor::getVisitorType() {
    return _visitorType;
};

SceneNodeVisitor::VisitorMode SceneNodeVisitor::getVisitorMode() {
    return _visitorMode;
};

}
