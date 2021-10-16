#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/gtc/quaternion.hpp"
struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		
		this->pos = pos;
		this->rotation.x = rot.x;
		this->rotation.y = rot.y;
		this->rotation.z = rot.z;
		this->scale = scale;
	}
	inline glm::mat4 GetModel() const 
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;
		return posMat * rotMat * scaleMat;
	}
	inline glm::vec3* GetPos() { return &pos; } //getters
	//inline glm::vec3* GetRot() { return &rotation; }
	inline glm::vec3* GetScale() { return &scale; }
	inline void SetPos(const glm::vec3& pos) { this->pos = pos; } // setters
	inline void SetRot(const glm::vec3& rot) { this->rotation = rot; }
	inline void SetScale(const glm::vec3& scale) { this->scale = scale; }
	glm::vec3 pos;
protected:
private:

	glm::quat rotation;
	glm::vec3 scale;
};


