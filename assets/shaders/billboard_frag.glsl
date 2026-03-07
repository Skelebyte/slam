#version 450 core

out vec4 FragColor;

in vec3 pos;
in vec2 texture_coord;
in vec3 normal;

uniform sampler2D diffuse_texture;

void main() {
  if (texture(diffuse_texture, texture_coord).w < 1.0)
    discard;
  FragColor = texture(diffuse_texture, texture_coord);
}