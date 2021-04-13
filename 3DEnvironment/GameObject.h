#pragma once
#include <SDL\SDL.h>
#include "Transform.h"
#include "Texture.h"
#include "Mesh.h"
using namespace std;

class GameObject
{
private:

	Texture texture;
	Mesh mesh;
	Transform transform;
	glm::vec3 pos;
	glm::vec3 velocity;
	float mass = 0.005;
	glm::vec3 acceleration;
	glm::vec3 maxSpeed = {10,10,10};




public:
	GameObject();
	~GameObject();
	Transform getTransform() { return transform; }
	glm::vec3 getPosition() { return *transform.GetPos(); }
	glm::vec3 getVelocity() { return velocity; }
	glm::vec3 getCollisionPos() { return mesh.getSpherePos(); }
	float getMass() { return mass; };
	float getCollisionRadius() { return mesh.getSphereRadius(); }
	void move();
	void setPosition(glm::vec3 position);
	void setVelocity(glm::vec3 velocity);
	void setRotation(float angle);
	void init(const std::string& meshPath, glm::vec3 collisionPos, float collisionRadius);
	void init(const std::string& meshPath, const std::string& texturePath, glm::vec3 collisionPos, float collisionRadius);
	void draw();
	void draw(unsigned int texID);
	void update();
	void euclideanTorus();
};

