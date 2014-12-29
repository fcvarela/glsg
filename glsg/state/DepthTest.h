#ifndef GLSG_DEPTHTEST_H
#define GLSG_DEPTHTEST_H

#include <render/GL.h>

namespace glsg {

class DepthTest {
public:
    GLenum function;
    bool enabled;

    DepthTest();

    /**
    * Distance calculation, measure state call distance
    * between two states.
    * @param state state to measure distance to
    */
    size_t distance(DepthTest depthTest);

    /**
    * Apply the state and make it active if different from active.
    * @param from the currently set blending state.
    */
    void apply(DepthTest from, bool force);
};

}

#endif
