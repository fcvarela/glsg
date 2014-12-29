#ifndef GLSG_BLENDING_H
#define GLSG_BLENDING_H

#include <render/GL.h>

namespace glsg {

class Blending {
public:
    GLenum src_mode;
    GLenum dst_mode;
    GLboolean enabled;

    Blending();

    /**
    * Distance calculation, measure state call distance
    * between two states.
    * @param state state to measure distance to
    */
    size_t distance(Blending blending);

    /**
    * Apply the state and make it active if different from active.
    * @param from the currently set blending state.
    */
    void apply(Blending from, bool force);
};

}

#endif
