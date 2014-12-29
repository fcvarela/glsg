#ifndef GLSG_MESH_H
#define GLSG_MESH_H

#include <memory>
#include <map>
#include <vector>
#include <string>

#include <render/GL.h>
#include <glmext/glmext.h>

namespace glsg {

/**s
* @defgroup render render
* @ingroup glsg
* Classes for managing OpenGL objects, bindings and render states.
*/

/**
* An OpenGL mesh container object. Holds vertices, indices and attributes.
* @ingroup render.
*/
class Mesh {
public:
    typedef std::shared_ptr<Mesh> Ptr;
    typedef std::map<std::string, Ptr> Map;
    typedef std::vector<Ptr> Vec;

    /**
    * Mesh constructor.
    */
    Mesh(GLenum mode, GLenum usage);

    /**
    * Mesh destructor.
    */
    ~Mesh();

    /**
    * Sets mesh vertex buffer
    * @param vertexBuffer the source vertex buffer.
    */
    void setVertexBuffer(std::vector<glm::vec3> vertexBuffer);

    /**
    * Sets the normal buffer
    * @param normalBuffer the source normal buffer.
    */
    void setNormalBuffer(std::vector<glm::vec3> normalBuffer);

    /**
    * Sets mesh index array
    * @param indexBuffer the source index array.
    */
    void setIndexBuffer(std::vector<glm::u16> indexBuffer);

    /**
    * Sets mesh vertex attribute buffer.
    * @param index the vertex attribute number.
    * @param vertexAttributeBuffer the source vertex attribute array.
    */
    //void setVertexAttributeBuffer(uint32_t index, std::vector<T> vertexAttributeBuffer);

    /**
    * Returns the mesh bounding box in local space.
    */
    virtual glm::dbox3 getBounds();

    /**
    * The draw implementation for this mesh.
    */
    virtual void draw();

private:
    /**
    * The mesh Vertex Array Object. Required in OpenGL Core Profiles which is
    * the only mode we support.
    */
    GLuint _vao;

    /**
    * How the mesh primitives are to be interpreted for drawing.
    * OpenGL primitve types: (ie) GL_TRIANGLES.
    */
    GLenum _mode;

    /**
    * How the mesh buffer usage is to be interpreted for memory management.
    * OpenGL buffer usage modes: (ie) GL_STATIC_DRAW.
    */
    GLenum _usage;

    /**
    * The mesh buffers map. Keeps track of the buffers used by this mesh, along with a tag,
    * which is useful for program binding by name (location->name aliasing).
    */
    std::map<std::string, GLuint> _buffers;

    /**
    * Index count in index buffer. After we've copied data to VRAM, we remove local
    * buffers. This is needed to keep a count of how many indices we had.
    */
    GLuint _indexCount;

    /**
    * The mesh bounding box.
    */
    glm::dbox3 _bounds;
};

}

#endif
