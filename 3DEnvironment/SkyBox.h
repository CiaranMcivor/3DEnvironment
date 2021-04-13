#pragma once
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"

class Skybox
{
public:
	void init(std::vector<std::string> faces);
	void draw(Camera* camera);

	unsigned int textureID;
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;

private:
	Shader shader;

};

