#version 330 core

out vec4 FragColor;

in vec3 pos;
in vec2 texture_coord;
in vec3 normal;

uniform sampler2D diffuse_texture;
uniform vec3 light_color = vec3(1.0, 1.0, 1.0);
// uniform sampler2D specular_texture;
uniform vec3 color = vec3(1.0, 1.0, 1.0);

// uniform float specular_strength = 0.5;

uniform vec3 light_position = vec3(0, 0, 0);
uniform vec3 ambient_color = vec3(0.1, 0.1, 0.1);

uniform vec3 fog_color = vec3(0.1, 0.1, 0.1);

uniform vec3 camera_position;

uniform float density = 0.05;
uniform float gradient = 1.5;

uniform bool affected_by_fog = true;
uniform bool unlit = false;

vec4 fog(vec4 mixer) {
  float distance = length(camera_position - pos);
  float visibility = exp(-pow((distance * density), gradient));
  visibility = clamp(visibility, 0.0, 1.0);

  return mix(vec4(fog_color, 1.0), mixer, visibility);
}

void main() {
  if (texture(diffuse_texture, texture_coord).w < 1.0)
    discard;

  // vec3 norm = vec3(0, 1, 0);
  vec3 norm = normalize(normal);
  vec3 light_dir = normalize(light_position - pos);

  float diff = max(dot(norm, light_dir), 0.0);

  vec3 diffuse = diff * light_color;

  vec3 result = (ambient_color + diffuse) * color;

  // FragColor = vec4(normal, 1.0);

  vec4 output = vec4(0);

  if (unlit) {
    output = texture(diffuse_texture, texture_coord) * vec4(color, 1.0);

  } else {
    vec4 final = (texture(diffuse_texture, texture_coord)) * vec4(result, 1.0);
    if (affected_by_fog == true) {
      output = fog(final);
    } else {
      output = final;
    }
  }

  // FragColor = vec4(1.0 - output.rgb, output.a); // invert
  FragColor = output;
}
