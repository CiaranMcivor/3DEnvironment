#pragma once
#include "Cube.h"
#include "Transform.h"
#include <GL\glew.h>
class Cube
{
private:
	float vertices;
	Transform transform;
	glm::vec3 pos;
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;

public:
	Transform getTransform() { return transform; }
	glm::vec3 getPosition() { return *transform.GetPos(); }
	void setPosition(glm::vec3 position);
	void draw();
	void init();
};

