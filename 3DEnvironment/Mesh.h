#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normalMap = normalMap;
	}




	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normalMap; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normalMap;

};
class CollisionSphere
{
public:

	CollisionSphere() {}

	CollisionSphere(glm::vec3& pos, float radius)
	{
		this->pos = pos;
	}

	glm::vec3 GetPos() { return pos; }
	float GetRadius() { return radius; }

	void SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 pos;
	float radius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void draw();
	void draw(unsigned int texID);
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model);
	void initCollisionData(glm::vec3 pos, float radius);
	void updateCollisionData(glm::vec3 pos);
	glm::vec3 getSpherePos() { return collisionSphere.GetPos(); }
	float getSphereRadius() { return collisionSphere.GetRadius(); }
private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	CollisionSphere collisionSphere;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};

