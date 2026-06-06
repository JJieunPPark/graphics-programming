#include "Camera.h"

void Camera::set_rotation(const glm::quat& _q)
{
  glm::mat3 R = glm::mat3_cast(_q);

  right_dir_ = glm::normalize(glm::vec3(R[0]));
  up_dir_    = glm::normalize(glm::vec3(R[1]));
  front_dir_ = glm::normalize(-glm::vec3(R[2]));
}

const glm::quat Camera::get_rotation() const
{
  glm::mat3 R;

  R[0] = right_dir_;
  R[1] = up_dir_;
  R[2] = -front_dir_;

  return glm::quat_cast(R);
}

void Camera::set_pose(const glm::quat& _q, const glm::vec3& _t)
{
  set_rotation(_q);
  position_ = _t;
}

void Camera::get_pose(glm::quat& _q, glm::vec3& _t) const
{
  _q = get_rotation();
  _t = position_;
}

const glm::mat4 Camera::get_pose() const
{
  glm::mat4 frame(1.0f);

  frame[0] = glm::vec4(right_dir_, 0.0f);
  frame[1] = glm::vec4(up_dir_, 0.0f);
  frame[2] = glm::vec4(-front_dir_, 0.0f);
  frame[3] = glm::vec4(position_, 1.0f);

  return frame;
}

void Camera::set_pose(const glm::mat4& _frame)
{
  right_dir_ = glm::normalize(glm::vec3(_frame[0]));
  up_dir_    = glm::normalize(glm::vec3(_frame[1]));
  front_dir_ = glm::normalize(-glm::vec3(_frame[2]));
  position_  = glm::vec3(_frame[3]);
}

void Camera::set_pose(const glm::vec3& _pos, const glm::vec3& _at, const glm::vec3& _up_dir)
{
  position_ = _pos;

  front_dir_ = glm::normalize(_at - _pos);
  right_dir_ = glm::normalize(glm::cross(front_dir_, _up_dir));
  up_dir_    = glm::normalize(glm::cross(right_dir_, front_dir_));
}

const glm::mat4 Camera::get_view_matrix() const
{
  return glm::lookAt(
    position_,
    position_ + front_dir_,
    up_dir_
  );
}

const glm::mat4 Camera::get_projection_matrix() const
{
  if (mode_ == kPerspective)
  {
    return glm::perspective(
      glm::radians(fovy_),
      aspect_,
      near_,
      far_
    );
  }
  else
  {
    float half_height = ortho_scale_;
    float half_width = ortho_scale_ * aspect_;

    return glm::ortho(
      -half_width,
       half_width,
      -half_height,
       half_height,
       near_,
       far_
    );
  }
}

void Camera::move_forward(float delta)
{
  position_ += front_dir_ * delta;
}

void Camera::move_backward(float delta)
{
  position_ -= front_dir_ * delta;
}

void Camera::move_left(float delta)
{
  position_ -= right_dir_ * delta;
}

void Camera::move_right(float delta)
{
  position_ += right_dir_ * delta;
}

void Camera::move_up(float delta)
{
  position_ += up_dir_ * delta;
}

void Camera::move_down(float delta)
{
  position_ -= up_dir_ * delta;
}