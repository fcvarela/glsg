#version 410

#include <include/common.h.glsl>

void do_common() {
    vertex = v;
    normal = normalize(vec3(normalMatrix * vec4(n, 0.0)));
}
