#version 450 core

layout(location = 0) in vec3 i_pos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main() { gl_Position = projection * view * model * vec4(i_pos, 1.0); }