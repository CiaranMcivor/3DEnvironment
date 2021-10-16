#include "Camera.h"



void Camera::MoveForward(float amt)
{
	this->pos += forward * amt;
}

void Camera::MoveHorizontal(float amt)
{
	this -> pos += glm::cross(up, forward) * amt;
}

void Camera::MoveVertical(float amt)
{
	this->pos += up * amt;
}

void Camera::Pitch(float angle)
{
	glm::vec3 right = glm::normalize(glm::cross(up, forward));

	forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	up = glm::normalize(glm::cross(forward, right));
}

void Camera::lookAt()
{
	forward = glm::normalize(viewTarget->getPosition() - pos);
}

void Camera::RotateY(float angle)
{
	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	glm::mat4 rotation = glm::rotate(angle, UP);

	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
}

void Camera::update()
{
	lookAt();
}
