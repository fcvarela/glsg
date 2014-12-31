#ifndef GLSG_MESHLOADER_H
#define GLSG_MESHLOADER_H

#include <render/Mesh.h>

namespace glsg {

class MeshLoader {
public:
    static Mesh::Ptr loadMesh(const std::string& name);
};

}

#endif
