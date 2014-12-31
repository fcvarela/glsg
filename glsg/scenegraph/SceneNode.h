#ifndef GLSG_SCENENODE_H
#define GLSG_SCENENODE_H

#include <map>
#include <vector>
#include <string>
#include <render/Mesh.h>
#include <glmext/glmext.h>
#include <state/State.h>

namespace glsg {
/**
* A scene graph node which implements coordinate transformation and encapsulation.
* @ingroup scenegraph
*/
class SceneNode : public std::enable_shared_from_this<SceneNode> {
public:
    typedef std::shared_ptr<SceneNode> Ptr;
    typedef std::vector<Ptr> Vec;

    /**
    * Empty SceneNode constructor.
    * @param name name of the new scene node (debug purposes only).
    */
    SceneNode(const std::string &name);

    /**
    * Destructor.
    */
    virtual ~SceneNode();

    /**
    * Returns the node name.
    */
    const std::string &getName();

    /**
    * Get a mesh by name.
    * @param name name of mesh to lookup and return.
    */
    Mesh::Ptr getMesh();

    /**
    * Sets this node's mesh.
    * @param name of the model file to load.
    */
    void loadMesh(const std::string& name);

    /**
    * Removes a mesh named as passed.
    * @param name name of the mesh to remove from this node.
    */
    void removeMesh();

    /**
    * Returns the entire collection of children from this node.
    */
    std::vector<SceneNode::Ptr> getChildren();

    /**
    * Returns this node children count.
    */
    uint64_t getChildrenCount();

    /**
    * Get a child by index.
    * @param index index of child to return
    */
    SceneNode::Ptr getChild(int index);

    /**
    * Adds a child to this node.
    * @param child the node to add as a child of this node.
    */
    void addChild(SceneNode::Ptr child);

    /**
    * Removes a child from this node.
    * @param index index of child to remove.
    */
    void removeChild(int index);

    /**
    * Sets this node's parent node.
    * @param parentNode node to set as parent.
    */
    void setParent(SceneNode *parentNode);

    /**
    * Rotate node.
    * @param angle rotate this much.
    * @param x rotation axis x component.
    * @param y rotation axis x component.
    * @param z rotation axis x component.
    */
    void rotate(double angle, double x, double y, double z);

    /**
    * Translate node.
    *
    */
    void translate(double x, double y, double z);

    /**
    * Returns the dirtyTransform state.
    */
    inline bool dirtyTransform() {
        return _dirtyTransform;
    }

    /**
    * Returns the dirty bounds state.
    */
    inline bool dirtyBounds() {
        return _dirtyBounds;
    }

    /**
    * Compute world matrices.
    */
    void recomputeTransforms();

    /**
    * Compute bounding boxes.
    */
    void recomputeBounds();

    /**
    * Returns this node bounding box in local reference frame.
    */
    glm::dbox3 getLocalBounds();

    /**
    * Returns this node bounding box in world reference frame.
    */
    glm::dbox3 getWorldBounds();

    /**
    * Get local frame to parent frame transformation matrix.
    */
    glm::dmat4 getTransformMatrix();

    /**
    * Get local frame to world frame transformation matrix.
    */
    glm::dmat4 getLocalToWorldMatrix();

    /**
    * Get world frame to local frame transformation matrix.
    */
    glm::dmat4 getWorldToLocalMatrix();

    /**
    * Get world position.
    */
    glm::dvec3 getWorldPosition();

    /**
    * Set whether this node is active and should, therefore, be updated, culled and drawn.
    * @param active active state.
    */
    void setActive(bool active);

    /**
    * The visitor visit method, will be called with different
    * visitor types, one per traversal type.
    * @param visitor the node visitor visiting this node
    */
    virtual void accept(class SceneNodeVisitor &visitor);

    /**
    * Returns the node's renderstate.
    */
    inline State *getState() {
        return &_renderState;
    }

private:
    /**
    * This node unique name.
    */
    std::string _name;

    /**
    * Node bounding box in local reference frame.
    */
    glm::dbox3 _localBounds;

    /**
    * Node bounding box in world reference frame.
    */
    glm::dbox3 _worldBounds;

    /**
    * Node position in world coordinates.
    */
    glm::dvec3 _worldPosition;

    /**
    * Node active state.
    */
    bool _active;

    /**
    * Node dirty transform state.
    */
    bool _dirtyTransform;

    /**
    * Node dirty bnounds state.
    */
    bool _dirtyBounds;

    /**
    * Matrix to transform local frame to parent frame.
    */
    glm::dmat4 _transformMatrix;

    /**
    * Matrix to transform local frame to world frame.
    */
    glm::dmat4 _localToWorldMatrix;

    /**
    * Matrix to transform world frame to local frame.
    */
    glm::dmat4 _worldToLocalMatrix;

    /**
    * The mesh contained in this node.
    */
    Mesh::Ptr _mesh;

    /**
    * This node's parent node.
    */
    SceneNode *_parent;

    /**
    * The vector of children nodes contained in this node.
    */
    std::vector<SceneNode::Ptr> _children;

    /**
    * This node's renderstate for drawing and sorting.
    */
    State _renderState;
};

}

#endif
