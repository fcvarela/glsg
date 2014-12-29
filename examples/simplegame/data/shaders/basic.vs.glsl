#version 410

#include <include/common.h.glsl>

void main() {
    // common stuff
    do_common();

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(v, 1.0);
}
