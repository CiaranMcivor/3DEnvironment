#include "Linker.h"

void Linker::linkShader(Shader* shader, GameObject* object, Camera* camera,float* counter, enum class ShaderType shaderType)
{
	
	switch (shaderType) 
	{
	case ShaderType::PHONG:
		 linkPhongShader(shader, object, camera);
		 
	 case  ShaderType::ENVMAPPING:
		 linkEnvMapping(shader, object , camera);

	 case ShaderType::GEOMETRY:
		 linkGeometryShader(shader,counter);
		 
	}
}

void Linker::linkEnvMapping(Shader* shader, GameObject* object, Camera* camera)
{
	shader->setInt("skybox", 0);
	shader->setMat4("projection", camera->getProjection());
	shader->setMat4("view", camera->getView());
	shader->setMat4("model", object->getTransform().GetModel());
	shader->setVec3("cameraPos", camera->getPos());
}

void Linker::linkPhongShader(Shader* shader ,GameObject* object, Camera* camera)
{
	shader->setMat4("projection", camera->getProjection());
	shader->setMat4("view", camera->getView());
	shader->setMat4("model", object->getTransform().GetModel());
	shader->setVec3("lightPosition", glm::vec3(5.0f,5.0f,-20.0f));		// Set light position, can be any vec3 coordinats
	shader->setVec3("lightColour", 1.0f, 1.0f, 1.0f);				// Light colour is RGB values
	shader->setVec3("modelColour", 1.0f, 1.0f, 0.31f);				//Model colour is RGB values
	shader->setVec3("cameraPosition", camera->getPos());
}

void Linker::linkFogShader(Shader* shader)
{
	//fogShader.setMat4("u_pm", camera.getProjection());
	//fogShader.setMat4("u_vm", camera.getView());
	//fogShader.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	shader->setFloat("minDist", -5.0f);
	shader->setFloat("maxDist", 40.0f);

	shader->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));
}


void Linker::linkToonShader(Shader* shader)
{
}

void Linker::linkRimShader(Shader* shader, GameObject* object, Camera* camera)
{
	glm::vec3 camDir;
	camDir = object->getCollisionPos() - camera->getPos();
	camDir = glm::normalize(camDir);
	shader->setMat4("u_pm", camera->getProjection());
	shader->setMat4("u_vm", camera->getView());
	shader->setMat4("model", object->getTransform().GetModel());
	shader->setMat4("view", camera->getView());
	shader->setVec3("lightDir", glm::vec3(0.2f, 0.2f, 0.2f));
}

void Linker::linkGeometryShader(Shader* shader, float* counter)
{
//float randX = ((float)rand() / (RAND_MAX));
//float randY = ((float)rand() / (RAND_MAX));
//float randZ = ((float)rand() / (RAND_MAX));
//// Frag: uniform float randColourX; uniform float randColourY; uniform float randColourZ;
//geometryShader.setFloat("randColourX", randX);
//geometryShader.setFloat("randColourY", randY);
//geometryShader.setFloat("randColourZ", randZ);
// Geom: uniform float time;
	shader->setFloat("time", *counter * 2);
}


