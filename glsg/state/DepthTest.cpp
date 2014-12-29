#include <state/DepthTest.h>

namespace glsg {

DepthTest::DepthTest() {
    enabled = true;
    function = GL_LEQUAL;
}

size_t DepthTest::distance(DepthTest depthTest) {
    size_t dist = 0;

    if (enabled != depthTest.enabled) dist++;
    if (function != depthTest.function) dist++;

    return dist;
}

void DepthTest::apply(DepthTest from, bool force) {
    if (function != from.function || force) {
        glDepthFunc(function);
    }

    if (enabled != from.enabled || force) {
        if (enabled) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }
}

}
