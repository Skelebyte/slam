#version 450 core

out vec4 FragColor;

in vec3 pos;
in vec2 texture_coord;
in vec3 normal;

uniform sampler2D diffuse_texture;
uniform vec3 light_color = vec3(0.0, 1.0, 0.0);
// uniform sampler2D specular_texture;
// uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
// uniform float specular_strength = 0.5;

void main() {
  FragColor = texture(diffuse_texture, texture_coord) * vec4(light_color, 1.0);
  // FragColor = texture(diffuse_texture, texture_coord);
}
