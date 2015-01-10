layout (location = 0) in vec3 v;
layout (location = 1) in vec3 n;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

out vec3 normal;
out vec3 vertex;

void do_common();
