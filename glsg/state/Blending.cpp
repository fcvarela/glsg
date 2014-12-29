#include <state/Blending.h>

namespace glsg {

Blending::Blending() {
    enabled = true;
    src_mode = GL_SRC_ALPHA;
    dst_mode = GL_ONE_MINUS_SRC_ALPHA;
}

size_t Blending::distance(Blending blending) {
    size_t dist = 0;

    if (enabled != blending.enabled) dist++;
    if (src_mode != blending.src_mode || dst_mode != blending.dst_mode) dist++;

    return dist;
}

void Blending::apply(Blending fromBlending, bool force) {
    if (enabled != fromBlending.enabled || force) {
        if (enabled) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }
    }

    if (src_mode != fromBlending.src_mode || dst_mode != fromBlending.dst_mode || force) {
        glBlendFunc(src_mode, dst_mode);
    }
}

}
