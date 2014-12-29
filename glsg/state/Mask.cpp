#include <state/Mask.h>

namespace glsg {

Mask::Mask() {
    rgb = true;
    depth = true;
    alpha = true;
}

size_t Mask::distance(Mask mask) {
    size_t dist = 0;

    if (rgb != mask.rgb || alpha != mask.alpha) dist++;
    if (depth != mask.depth) dist++;

    return dist;
}

void Mask::apply(Mask from, bool force) {

}

}
