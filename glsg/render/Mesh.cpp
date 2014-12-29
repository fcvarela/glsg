#include <log/Log.h>
#include <render/Mesh.h>

namespace glsg {

Mesh::Mesh(GLenum mode, GLenum usage) {
    LINFO("Mesh alloc - generating vertex arrays");

    glGenVertexArrays(1, &_vao);
    _mode = mode;
    _usage = usage;
}


Mesh::~Mesh() {
    LINFO("Mesh dealloc start");

    // we probably don't need this, but we bind the vao either way
    glBindVertexArray(_vao);

    for (auto buffer : _buffers) {
        LINFO("Mesh deleting buffers");
        glDeleteBuffers(1, &buffer.second);
    }

    LINFO("Mesh deleting VAO");
    // and delete the vao
    glDeleteVertexArrays(1, &_vao);
    glBindVertexArray(0);
    _vao = 0;

    LINFO("Mesh dealloc finish");
};

void Mesh::setVertexBuffer(std::vector<glm::vec3> vertexBuffer) {
    LINFO("Mesh copying vertexbuffer");

    // bind the vao
    glBindVertexArray(_vao);

    GLuint _vertexBuffer = 0;

    // create if it doesn't exist
    if (_buffers.find("vertices") == _buffers.end()) {
        // create the buffer
        glGenBuffers(1, &_vertexBuffer);
        LINFO("Generated vertex buffer " << _vertexBuffer);
        _buffers["vertices"] = _vertexBuffer;
    } else {
        LINFO("Returning existing buffer");
        _vertexBuffer = _buffers["vertices"];
    }

    // bind it
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

    // copy the data
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(glm::vec3), &vertexBuffer[0], GL_STATIC_DRAW);

    // assign attrib 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // unbind it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // compute bounds
    LINFO("Computing bounds");

    _bounds = glm::dbox3();
    for (size_t i = 0; i < vertexBuffer.size(); i++) {
        _bounds.extend(glm::dvec3(vertexBuffer[i]));
    }

    LDEBUG(_bounds.minimum.x << ", " << _bounds.minimum.y << ", " << _bounds.minimum.z);
    LDEBUG(_bounds.maximum.x << ", " << _bounds.maximum.y << ", " << _bounds.maximum.z);
}

void Mesh::setNormalBuffer(std::vector<glm::vec3> normalBuffer) {
    // bind the vao
    glBindVertexArray(_vao);

    GLuint _normalBuffer = 0;

    // create it if it doesn't exist
    if (_buffers.find("normals") == _buffers.end()) {
        glGenBuffers(1, &_normalBuffer);
        LINFO("Generated normal buffer: " << _normalBuffer);
        _buffers["normals"] = _normalBuffer;
    } else {
        _normalBuffer = _buffers["normals"];
    }

    // bind it
    glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);

    // copy the data
    glBufferData(GL_ARRAY_BUFFER, normalBuffer.size() * sizeof(glm::vec3), &normalBuffer[0], GL_STATIC_DRAW);

    // assign attrib 1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // unbind it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::setIndexBuffer(std::vector<glm::u16> indexBuffer) {
    // bind the vao
    glBindVertexArray(_vao);

    GLuint _indexBuffer = 0;

    // create if it doesn't exist
    if (_buffers.find("indices") == _buffers.end()) {
        // create the buffer
        glGenBuffers(1, &_indexBuffer);
        LINFO("Generated index buffer " << _indexBuffer);
        _buffers["indices"] = _indexBuffer;
    } else {
        _indexBuffer = _buffers["indices"];
    }

    // bind it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

    // copy the data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(glm::u16), &indexBuffer[0], GL_STATIC_DRAW);

    // unbind it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _indexCount = indexBuffer.size();
}

glm::dbox3 Mesh::getBounds() {
    return _bounds;
}

void Mesh::draw() {
    LDEBUG("Mesh drawing");

    glBindVertexArray(_vao);

    // some drivers don't keep element buffers referenced in VAOs
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers["indices"]);
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
}

}
