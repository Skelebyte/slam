#version 450 core

layout(location = 0) in vec3 i_pos;

uniform mat4 view;
uniform mat4 projection;

void main() { gl_Position = projection * view * vec4(i_pos, 1.0); }