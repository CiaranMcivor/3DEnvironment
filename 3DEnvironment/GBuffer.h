#pragma once
#include <string>
#include <GL\glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Shader.h"
#include "GameObject.h"
#include "Texture.h"


class GBuffer
{
private:
	GLuint gBuffer,renderBuffer;
	GLuint gPosition, gNormal, gDiffSpec;
	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	Shader geometryPassShader;
	Shader lightingPassShader;

	GLuint quadVAO;
	GLuint quadVBO;

	Texture normals;
	Texture	diffuse;
	Texture specular;

public:

	void init(float screenWidth, float screenHeight);
	void loadTextures();
	void initShader();
	void bind();
	void unbind();
	void generateQuad();
	void geometryPass(GameObject* object, Camera* camera);
	void lightingPass(Camera* camera);
	void render();


};

