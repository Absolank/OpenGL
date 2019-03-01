#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>
const float YAW = -89.f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.f;

using namespace glm;
void Camera::UpdateCamera()
{
	float y = radians(__yaw_);
	float p = radians(__pitch_);
	__front_.x = cos(p) * cos(y);
	__front_.y = sin(p);
	__front_.z = cos(p) * sin(y);
	__front_ = glm::normalize(__front_);
	__right_ = normalize(cross(__front_, __world_up_));
	__up_ = normalize(cross(__right_, __front_));
}
void Camera::Mouse(double xoffset, double yoffset)
{
	xoffset *= __mouse_sensitivity_;
	yoffset *= __mouse_sensitivity_;

	__yaw_ += xoffset;
	__pitch_ += yoffset;

	glm::clamp(__pitch_, -89.f, 89.f);
	UpdateCamera();
}
Camera::Camera() :
	__position_(vec3(0.f, 0.f, 3.f)),
	__world_up_(vec3(0.f, 1.f, 0.f)),
	__yaw_(YAW),
	__pitch_(PITCH),
	__mouse_sensitivity_(SENSITIVITY),
	__mouse_speed_(SPEED),
	__zoom_(ZOOM)
{
	UpdateCamera();
}

Camera::Camera(vec3& __pos_, vec3& __up_) :
	__position_(__pos_),
	__world_up_(__up_),
	__yaw_(YAW),
	__pitch_(PITCH),
	__mouse_sensitivity_(SENSITIVITY),
	__mouse_speed_(SPEED),
	__zoom_(ZOOM)
{
	UpdateCamera();
}

glm::vec3 Camera::GetPositionVector()
{
	return __position_;
}

void Camera::MoveUp(float delta_time)
{
	__position_ += __up_ * __mouse_speed_* delta_time;
}

void Camera::MoveDown(float delta_time)
{
	MoveUp(-delta_time);
}

void Camera::MoveForward(float delta_time)
{
	__position_ += __front_ * __mouse_speed_* delta_time;
}

void Camera::MoveBackward(float delta_time)
{
	MoveForward(-delta_time);
}

void Camera::MoveRight(float delta_time)
{
	__position_ += __right_ * __mouse_speed_ * delta_time;
}

void Camera::MoveLeft(float delta_time)
{
	MoveRight(-delta_time);
}

glm::mat4 Camera::GetViewMatrix()
{
	return lookAt(__position_, __position_ + __front_, __up_);
}

Camera::~Camera()
{
}
