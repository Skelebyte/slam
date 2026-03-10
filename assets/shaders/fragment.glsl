#version 450 core

out vec4 FragColor;

in vec3 pos;
in vec2 texture_coord;
in vec3 normal;

uniform sampler2D diffuse_texture;
uniform vec3 light_color = vec3(1.0, 1.0, 1.0);
// uniform sampler2D specular_texture;
uniform vec3 color = vec3(1.0, 1.0, 1.0);

// uniform float specular_strength = 0.5;

uniform vec3 light_position = vec3(10, 10, 10);
uniform vec3 ambient_color = vec3(0.1, 0.1, 0.1);

void main() {
  if (texture(diffuse_texture, texture_coord).w < 1.0)
    discard;

  vec3 norm = normalize(normal);
  vec3 light_dir = normalize(light_position - pos);

  float diff = max(dot(norm, light_dir), 0.0);

  vec3 diffuse = diff * light_color;

  vec3 result = (ambient_color + diffuse) * color;

  FragColor = (texture(diffuse_texture, texture_coord)) * vec4(result, 1.0);
  // FragColor = texture(diffuse_texture, texture_coord) * vec4(color, 0.0);
}
