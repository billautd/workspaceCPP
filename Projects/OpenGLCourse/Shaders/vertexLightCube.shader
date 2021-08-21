#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

out vec3 fNormal;
out vec3 fFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fNormal = mat3(transpose(inverse(model))) * normal;
    fFragPos = vec3(model * vec4(pos, 1.0f));
    gl_Position = projection * view * vec4(fFragPos, 1.0f);
}