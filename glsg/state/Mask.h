#ifndef GLSG_MASK_H
#define GLSG_MASK_H

#include <render/GL.h>

namespace glsg {

class Mask {
public:
    bool rgb;
    bool alpha;
    bool depth;
    bool stencil;

    Mask();

    /**
    * Distance calculation, measure state call distance
    * between two states.
    * @param state state to measure distance to
    */
    size_t distance(Mask ask);

    /**
    * Apply the state and make it active if different from active.
    * @param from the currently set blending state.
    */
    void apply(Mask from, bool force);
};

}

#endif
