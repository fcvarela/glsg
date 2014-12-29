#ifndef GLSG_CULLFACE_H
#define GLSG_CULLFACE_H

#include <render/GL.h>

namespace glsg {

class CullFace {
public:
    GLenum mode;
    bool enabled;

    CullFace();

    /**
    * Distance calculation, measure state call distance
    * between two states.
    * @param state state to measure distance to
    */
    size_t distance(CullFace cullFace);

    /**
    * Apply the state and make it active if different from active.
    * @param from the currently set blending state.
    */
    void apply(CullFace from, bool force);

    };
}

#endif
