#ifndef SLAM_MATHF_HPP
#define SLAM_MATHF_HPP

#define GLM_ENABLE_EXPERIMENTAL
#include "../common.hpp"
#include "../ext/glm/ext/matrix_transform.hpp"
#include "../ext/glm/ext/quaternion_geometric.hpp"
#include "../ext/glm/geometric.hpp"
#include "../ext/glm/glm.hpp"
#include "../ext/glm/gtc/type_ptr.hpp"
#include "../ext/glm/gtx/rotate_vector.hpp"
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
  static sString ToString(const Vec3 &target);
  static Vec3 Normalized(const Vec3 &target);
  static Vec3 RotateX(const Vec3 &target, float angleDeg);
  static Vec3 RotateY(const Vec3 &target, float angleDeg);
  static Vec3 RotateZ(const Vec3 &target, float angleDeg);
};

} // namespace slam::math

#endif