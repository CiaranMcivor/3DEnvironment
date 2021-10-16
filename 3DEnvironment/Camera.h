#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "GameObject.h"
#include <iostream>

#define print(x) std::cout << x << std::endl
struct Camera
{
public:

	Camera()
	{
	}

	void setViewtarget(GameObject* target) {
		viewTarget = target;
		print(viewTarget);
	};

	glm::vec3 getPos()
	{
		return this->pos;
	}

	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const
	{
		glm::mat4 view = glm::lookAt(pos, pos + forward, up);
		return projection * view;//pos of camera, position camera is pointing (vector), up (vector)
	}

	inline glm::mat4 getProjection() const
	{
		return projection;
	}

	inline glm::mat4 getView() const
	{
		return glm::lookAt(pos, pos + forward, up);
	}

	void MoveForward(float amt);


	void MoveHorizontal(float amt);

	void MoveVertical(float amt);


	void Pitch(float angle);

	void lookAt();

	void RotateY(float angle);

	void update();

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	GameObject *viewTarget;
};

