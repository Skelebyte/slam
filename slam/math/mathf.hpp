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
  static sF32 ToRadians(sF32 value);
  static sF32 ToDegrees(sF32 value);
  static sF32 Lerp(sF32 a, sF32 b, sF32 t);
  static sF32 Clamp(sF32 target, sF32 min, sF32 max);
  static sF32 Wrap(sF32 target, sF32 min, sF32 max);
  static sString ToString(const Vec3 &target);
  static Vec3 Normalized(const Vec3 &target);
  static Vec3 RotateX(const Vec3 &target, sF32 angleDeg);
  static Vec3 RotateY(const Vec3 &target, sF32 angleDeg);
  static Vec3 RotateZ(const Vec3 &target, sF32 angleDeg);
};

} // namespace slam::math

#endif