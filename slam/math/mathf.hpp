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
#include <SDL3/SDL.h>
#include <cstdlib>
#include <ctime>
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
  static f32 ToRadians(f32 value);
  static f32 ToDegrees(f32 value);
  static f32 Lerp(f32 a, f32 b, f32 t);
  static f32 Clamp(f32 target, f32 min, f32 max);
  static f32 Wrap(f32 target, f32 min, f32 max);
  static str ToString(const Vec3 &target);
  static str ToString(const Quat &target);
  static f32 Distance(const Vec3 &a, const Vec3 &b);
  static f32 Dot(CRef<Vec3> a, CRef<Vec3> b);
  static i32 Abs(i32 value);
  static f32 Abs(f32 value);
  static Vec3 Normalized(const Vec3 &target);
  static Vec3 RotateX(const Vec3 &target, f32 angleDeg);
  static Vec3 RotateY(const Vec3 &target, f32 angleDeg);
  static Vec3 RotateZ(const Vec3 &target, f32 angleDeg);
  /**
   * @brief Generates a random number.
   *
   * @param max Largest nubmer it can regenerate (inclusive)
   * @return i32
   */
  static i32 Random(i32 max);
};

} // namespace slam::math

#endif