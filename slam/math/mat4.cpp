#include "mat4.hpp"
#include "mathf.hpp"

using namespace slam;
using namespace slam::math;

Mat4::Mat4(bool identity) {
  if (identity) {
    this->Identity();
  } else {
    for (int i = 0; i < 16; i++) {
      this->data[i] = 0;
    }
  }
}
Mat4 Mat4::Transformation(Vec3 pos, Vec3 rot, Vec3 sca,
                          Mat4_MultiplicationOrder order) {
  Mat4 result = Mat4();
  Mat4 position = Mat4();
  Mat4 rotation = Mat4();
  Mat4 scale = Mat4();
  position.Translate(pos);
  rotation.Rotate(rot);
  scale.Scale(sca);
  Mat4 half_matrix;
  switch (order) {
  case Mat4_TRS:
    half_matrix = rotation * scale;
    result = position * half_matrix;
    break;
  case Mat4_TSR:
    half_matrix = scale * rotation;
    result = position * half_matrix;
    break;
  case Mat4_RTS:
    half_matrix = position * scale;
    result = rotation * half_matrix;
    break;
  case Mat4_RST:
    half_matrix = scale * position;
    result = rotation * half_matrix;
    break;
  case Mat4_STR:
    half_matrix = position * rotation;
    result = scale * half_matrix;
    break;
  case Mat4_SRT:
    half_matrix = rotation * position;
    result = scale * half_matrix;
    break;
  }

  return result;
}

void Mat4::Identity() {
  for (int i = 0; i < 16; i++)
    this->data[i] = 0;

  this->data[0] = 1;
  this->data[5] = 1;
  this->data[10] = 1;
  this->data[15] = 1;
}

void Mat4::Translate(Vec3 point) {
  this->data[12] = point.x;
  this->data[13] = point.y;
  this->data[14] = point.z;
}

void Mat4::Rotate(Vec3 angles) {
  Mat4 x_rot;
  Mat4 y_rot;
  Mat4 z_rot;

  Vec3 angles_in_rad =
      Vec3(Mathf::ToRadians(angles.x), Mathf::ToRadians(angles.y),
           Mathf::ToRadians(angles.z));

  x_rot.data[5] = cos(angles_in_rad.x);
  x_rot.data[6] = sin(angles_in_rad.x);
  x_rot.data[9] = -sin(angles_in_rad.x);
  x_rot.data[10] = cos(angles_in_rad.x);

  y_rot.data[0] = cos(angles_in_rad.y);
  y_rot.data[2] = -sin(angles_in_rad.y);
  y_rot.data[8] = sin(angles_in_rad.y);
  y_rot.data[10] = cos(angles_in_rad.y);

  z_rot.data[0] = cos(angles_in_rad.z);
  z_rot.data[1] = sin(angles_in_rad.z);
  z_rot.data[4] = -sin(angles_in_rad.z);
  z_rot.data[5] = cos(angles_in_rad.z);

  Mat4 xy_rot = x_rot * y_rot;
  Mat4 xyz_rot = xy_rot * z_rot;
  Mat4 rot = *this * xyz_rot;
  for (int i = 0; i < 16; i++) {
    this->data[i] = rot.data[i];
  }
}

void Mat4::Scale(Vec3 scale) {
  this->data[0] = scale.x;
  this->data[5] = scale.y;
  this->data[10] = scale.z;
}

void Mat4::Perspective(float fov_deg, float aspect, float near_plane,
                       float far_plane) {
  float fov_rads = Mathf::ToRadians(fov_deg);

  this->Identity();
  this->data[0] = 1 / (aspect * tan(fov_rads / 2));
  this->data[5] = 1 / tan(fov_rads / 2);
  this->data[10] = -(far_plane + near_plane) / (far_plane - near_plane);
  this->data[11] = -1;
  this->data[14] = -(2 * far_plane * near_plane) / (far_plane - near_plane);
  this->data[15] = 0;
}

void Mat4::Orthogonal(float left, float right, float top, float bottom,
                      float near_plane, float far_plane) {
  this->Identity();
  this->data[0] = 2 / (right - left);
  this->data[5] = 2 / (top - bottom);
  this->data[10] = -2 / (far_plane - near_plane);
  this->data[12] = -(right + left) / (right - left);
  this->data[13] = -(top + bottom) / (top - bottom);
  this->data[14] = -(far_plane + near_plane) / (far_plane - near_plane);
  this->data[15] = 1;
}

void Mat4::LookAt(Vec3 position, Vec3 target_position, Vec3 forward) {
  this->Identity();
  Vec3 forward_ = (position - target_position).Normalized();
  Vec3 right = Vec3::Cross(Vec3(0.0f, 1.0f, 0.0f), forward_).Normalized();
  Vec3 up = Vec3::Cross(forward_, right);

  this->data[0] = right.x;
  this->data[4] = right.y;
  this->data[8] = right.z;
  this->data[12] = -Vec3::Dot(right, position);
  this->data[1] = up.x;
  this->data[5] = up.y;
  this->data[9] = up.z;
  this->data[13] = -Vec3::Dot(up, position);
  this->data[2] = forward_.x;
  this->data[6] = forward_.y;
  this->data[10] = forward_.z;
  this->data[14] = -Vec3::Dot(forward_, position);
}

sString Mat4::ToString() const {
  sString result;

  for (sUint i = 0; i < 16; i++) {
    result.append(std::to_string(data[i]) + ", ");
  }

  return result;
}

Mat4 Mat4::Inverse() const {
  Mat4 inv;

  inv.data[0] = this->data[0];
  inv.data[1] = this->data[4];
  inv.data[2] = this->data[8];
  inv.data[3] = 0;
  inv.data[4] = this->data[1];
  inv.data[5] = this->data[5];
  inv.data[6] = this->data[9];
  inv.data[7] = 0;
  inv.data[8] = this->data[2];
  inv.data[9] = this->data[6];
  inv.data[10] = this->data[10];
  inv.data[11] = 0;
  inv.data[15] = 1;
  inv.data[12] = 0;
  inv.data[13] = 0;
  inv.data[14] = 0;

  Vec3 t(this->data[12], this->data[13], this->data[14]);
  Vec3 invT =
      Vec3(-(inv.data[0] * t.x + inv.data[4] * t.y + inv.data[8] * t.z),
           -(inv.data[1] * t.x + inv.data[5] * t.y + inv.data[9] * t.z),
           -(inv.data[2] * t.x + inv.data[6] * t.y + inv.data[10] * t.z));

  inv.data[12] = invT.x;
  inv.data[13] = invT.y;
  inv.data[14] = invT.z;

  return inv;
}

Mat4 Mat4::operator*(const Mat4 &other) {
  Mat4 out;
  Mat4 current = *this;

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      float sum = 0;
      for (int i = 0; i < 4; i++) {
        sum += current.data[i * 4 + row] * other.data[col * 4 + i];
      }
      out.data[col * 4 + row] = sum;
    }
  }
  return out;
}
