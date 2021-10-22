#include "GameObject.h"
#include <iostream>

GameObject::GameObject() 
{

}
GameObject::~GameObject()
{

}

void GameObject::move()
{
	this->setPosition(this->getPosition() += velocity);						//set the position to be equal to the current position + the velocity of the object
}

void GameObject::setPosition(glm::vec3 position)
{
	this->transform.SetPos(position);
}

void GameObject::setVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

void GameObject::setRotation(float angle)
{
	transform.SetRot(glm::vec3(0.0, angle * 5, 0.0));
}


void GameObject::init(Mesh* meshType, const std::string &texturePath, glm::vec3 collisionPos, float collisionRadius)
{
	/*Initialise collisions , model and texture for this object*/
	mesh = meshType;
	mesh->initCollisionData(collisionPos,collisionRadius);													//initialise the collision data for this object
	texture.init(texturePath);

	//shader.init("..\\res\\shader"); //new shader
	
}

void GameObject::init(Mesh* meshType, glm::vec3 collisionPos, float collisionRadius)
{
	/*Initialise collisions , model and texture for this object*/
	mesh = meshType;
	mesh->initCollisionData(collisionPos, collisionRadius);													//initialise the collision data for this object

	//shader.init("..\\res\\shader"); //new shader

}

void GameObject::draw()
{
	texture.Bind(0);
	mesh->draw();
}

void GameObject::draw(unsigned int texID)
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	mesh->draw();
}

void GameObject::update()
{
	move();
	mesh->updateCollisionData(getPosition());			//set the position of the Collision sphere to be the same as the position of the transform
}

/*Wraps objecs around the screen when they exit the edges*/

void GameObject::screenWrap()
{
	if (transform.GetPos()->x > 30) {
		transform.SetPos(glm::vec3{ -25,this->getPosition().y,this->getPosition().z });

	}
	else if (transform.GetPos()->x < -30) {
		transform.SetPos(glm::vec3{ 25,this->getPosition().y,this->getPosition().z });

	}
	else if (transform.GetPos()->y > 20) {
		transform.SetPos(glm::vec3{ this->getPosition().x,-15,this->getPosition().z });

	}
	else if (transform.GetPos()->y < -20) {
		transform.SetPos(glm::vec3{ this->getPosition().x,15,this->getPosition().z });

	}
}

