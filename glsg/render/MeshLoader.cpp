#include <iosfwd>

#include <render/MeshLoader.h>
#include <resource/ResourceLoader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace glsg {

Mesh::Ptr MeshLoader::loadMesh(const std::string &name) {
    ResourceLoader::Resource modelData = ResourceLoader::get()->loadModel(name);

    // implement now, refactor later to model class
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFileFromMemory(
            modelData.data, modelData.size,
            aiProcessPreset_TargetRealtime_MaxQuality | \
            aiProcess_OptimizeGraph | \
            aiProcess_OptimizeMeshes | \
            aiProcess_CalcTangentSpace);

    if (!scene) {
        LDEBUG(importer.GetErrorString());
        return nullptr;
    }

    // we're good to go, inspect loaded scene, we only load the first mesh
    if (scene->mNumMeshes == 0) {
        LERROR("Cannot find meshes in " << name);
        return nullptr;
    }

    // got here? got at least one mesh and that's all we support
    aiMesh *mesh = scene->mMeshes[0];

    // our mesh instance
    auto internal_mesh = glsg::Mesh::Ptr(new glsg::Mesh(GL_TRIANGLES, GL_STATIC_DRAW));

    // copy all vertices and normals into the appropriate buffers
    std::vector<glm::vec3> vertexBuffer;
    std::vector<glm::vec3> normalBuffer;

    for (size_t v = 0; v < mesh->mNumVertices; v++) {
        vertexBuffer.push_back(glm::vec3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z));
        normalBuffer.push_back(glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z));
    }

    // and copy indexes as well
    std::vector<glm::u16> indexBuffer;

    for (size_t j = 0; j < mesh->mNumFaces; j++) {
        const aiFace &face = mesh->mFaces[j];
        for (size_t ind = 0; ind < face.mNumIndices; ind++) {
            indexBuffer.push_back(face.mIndices[ind]);
        }
    }

    // link the mesh to these buffers
    internal_mesh->setVertexBuffer(vertexBuffer);
    internal_mesh->setNormalBuffer(normalBuffer);
    internal_mesh->setIndexBuffer(indexBuffer);

    // we're good to go
    return internal_mesh;
}

}