#pragma once
#include "Window.h"
#include <GLM/glm.hpp>
class Camera : public MouseCallback
{
	glm::vec3 __position_;
	glm::vec3 __front_;
	glm::vec3 __right_;
	glm::vec3 __up_;

	glm::vec3 __world_up_;
	float __yaw_;
	float __pitch_;

	float __mouse_speed_;
	float __mouse_sensitivity_;
	float __zoom_;

	void UpdateCamera();
public:
	void Mouse(double xoffset, double yoffset);
	Camera();
	Camera(glm::vec3& __pos_, glm::vec3& __up_);
	glm::vec3 GetPositionVector();
	void MoveUp(float delta_time);
	void MoveDown(float delta_time);
	void MoveForward(float delta_time);
	void MoveBackward(float delta_time);
	void MoveRight(float delta_time);
	void MoveLeft(float delta_time);
	glm::mat4 GetViewMatrix();
	~Camera();

};

