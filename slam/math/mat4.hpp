#ifndef SLAM_MAT4_HPP
#define SLAM_MAT4_HPP

#include "vec3.hpp"

namespace slam::math {

typedef enum Mat4_MultiplicationOrder {
  Mat4_TRS, // `entity` default (`transform * (rotation * scale)`)
  Mat4_TSR, // `ui_entity` default (`transform * (scale * rotation)`)
  Mat4_RST, // `rotation * (scale * transform)`
  Mat4_RTS, // `rotation * (transform * scale)`
  Mat4_SRT, // `scale * (rotation * transform)`
  Mat4_STR, // `scale * (transform * rotation)`
} Mat4_MultiplicationOrder,
    MultiplicationOrder;

struct Mat4 {
  float data[16];
  Mat4(bool identity = true);
  static Mat4 Transformation(Vec3 pos, Vec3 rot, Vec3 sca,
                             Mat4_MultiplicationOrder order = Mat4_TRS);
  void Identity();

  void Translate(Vec3 point);
  void Rotate(Vec3 angles);
  void Scale(Vec3 scale);

  void Perspective(float fov_deg, float aspect, float near_plane,
                   float far_plane);
  void Orthogonal(float left, float right, float top, float bottom,
                  float near_plane, float far_plane);
  void LookAt(Vec3 position, Vec3 target_position, Vec3 forward);

  sString ToString() const;

  Mat4 Inverse() const;

  Mat4 operator*(const Mat4 &other);
};

} // namespace slam::math

// typedef float Mat4[16];

// /**
//  * @brief Default value for a 4x4 matrix.
//  * @code {.c}
//  * 1, 0, 0, 0,
//  * 0, 1, 0, 0,
//  * 0, 0, 1, 0,
//  * 0, 0, 0, 1,
//  * @endcode
//  */

#endif
