#pragma once
#include <string>
#include <GL\glew.h>
#include <iostream>
#include "Shader.h"
class FBO

{
private:
	GLuint FBO; // Frame Buffer 
	GLuint RBO; // Render Buffer 
	GLuint CBO; // Colour Buffer 

	GLuint quadVAO;
	GLuint quadVBO;

	Shader shader;
public:
	void init(float width, float height);
	void bind();
	void unbind();
	void render();
	void generateQuad();
	void initShader();

};

