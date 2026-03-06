#ifndef SLAM_MATHF_HPP
#define SLAM_MATHF_HPP

#include "../ext/glm/glm.hpp"
// #include "../ext/gtx/rotate_vector.hpp"

namespace slam::math {

typedef glm::vec2 Vec2;
typedef glm::ivec2 Vec2i;
typedef glm::vec3 Vec3;
typedef glm::ivec3 Vec3i;
typedef glm::vec4 Vec4;
typedef glm::ivec4 Vec4i;
typedef glm::quat Quat;
typedef glm::mat4 Mat4;
class Mathf {
public:
  static float ToRadians(float value);
  static float ToDegrees(float value);
  static float Lerp(float a, float b, float t);
  static float Clamp(float target, float min, float max);
  static float Wrap(float target, float min, float max);
  static Vec3 Rotate();
};

} // namespace slam::math

#endif