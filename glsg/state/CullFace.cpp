#include <state/CullFace.h>

namespace glsg {

CullFace::CullFace() {
    enabled = true;
    mode = GL_BACK;
}

size_t CullFace::distance(CullFace cullFace) {
    size_t dist = 0;

    if (mode != cullFace.mode) dist++;
    if (enabled != cullFace.enabled) dist++;

    return dist;
}

void CullFace::apply(CullFace from, bool force) {
    if (mode != from.mode || force) {
        glCullFace(mode);
    }

    if (enabled != from.enabled || force) {
        if (enabled) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }
    }
}

}
