#pragma once
#include <SDL\SDL.h>
#include "Transform.h"
#include "Texture.h"
#include "Mesh.h"
#include <map>;
using namespace std;


class GameObject
{
private:

	std::map<std::string,Texture> textures;
	Mesh* mesh;
	Transform transform;
	glm::vec3 pos;
	glm::vec3 velocity;
	float mass = 0.005;
	glm::vec3 acceleration;
	glm::vec3 maxSpeed = {10,10,10};

	Texture diffuse;
	Texture specular;


public:
	GameObject();
	~GameObject();
	Transform getTransform() { return transform; }
	glm::vec3 getPosition() { return *transform.GetPos(); }
	glm::vec3 getVelocity() { return velocity; }
	glm::vec3 getCollisionPos() { return mesh->getSpherePos(); }
	Texture* getDiffuse() { return &diffuse; }
	Texture* getSpecular() { return &specular; }

	float getMass() { return mass; };
	float getCollisionRadius() { return mesh->getSphereRadius(); }
	void move();
	void setPosition(glm::vec3 position);
	void setVelocity(glm::vec3 velocity);
	void setRotation(float angle);
	void init(Mesh* meshType, glm::vec3 collisionPos, float collisionRadius);
	void init(Mesh* meshType, const std::string& diffusePath, const std::string& specularPath, glm::vec3 collisionPos, float collisionRadius);
	void draw();
	void draw(unsigned int texID);
	void update();
	void screenWrap();
};

