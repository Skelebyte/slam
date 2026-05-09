#ifndef SLAM_MATHF_HPP
#define SLAM_MATHF_HPP

#include "../common.hpp"
#include <SDL3/SDL.h>
#include <cstdlib>
#include <ctime>

// clang-format off
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/rotate_vector.hpp>
// clang-format on

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
  static float32 ToRadians(float32 value);
  static float32 ToDegrees(float32 value);
  static float32 Lerp(float32 a, float32 b, float32 t);
  static float32 Clamp(float32 target, float32 min, float32 max);
  static float32 Wrap(float32 target, float32 min, float32 max);
  static str ToString(const Vec3 &target);
  static str ToString(const Quat &target);
  static float32 Distance(const Vec3 &a, const Vec3 &b);
  static float32 Dot(CRef<Vec3> a, CRef<Vec3> b);
  static int32 Abs(int32 value);
  static float32 Abs(float32 value);
  static Vec3 Normalized(const Vec3 &target);
  static Vec3 RotateX(const Vec3 &target, float32 angleDeg);
  static Vec3 RotateY(const Vec3 &target, float32 angleDeg);
  static Vec3 RotateZ(const Vec3 &target, float32 angleDeg);
  static Vec3 ToEuler(const Quat &target);
  static Quat ToQuat(const Vec3 &target);
  /**
   * @brief Generates a random number.
   *
   * @param max Largest nubmer it can regenerate (inclusive)
   * @return int32
   */
  static int32 Random(int32 max);
};

} // namespace slam::math

#endif