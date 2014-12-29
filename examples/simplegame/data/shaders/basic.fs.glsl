#version 410

in vec3 normal;
in vec3 vertex;

out vec4 color;

void main() {
    color = vec4(normal, 1.0);
}
