#ifndef SLAM_MATHF_HPP
#define SLAM_MATHF_HPP

namespace slam::math {

class Mathf {
public:
  static float ToRadians(float value);
  static float ToDegrees(float value);
  static float Lerp(float a, float b, float t);
  // Vec2 v3_to_v2(Vec3 value);
  // Vec3 v2_to_v3(Vec2 value, float z_value);
};

} // namespace slam::math

#endif