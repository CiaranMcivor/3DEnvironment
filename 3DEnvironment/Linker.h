#pragma once
#include "Camera.h"
#include "Shader.h"
#include <string.h>

enum class ShaderType {
	FOG = 1,
	RIM = 2,
	ENVMAPPING = 3,
	GEOMETRY = 4,
	PHONG = 5
};
class Linker
{

public:
	void linkShader(Shader* shader, GameObject* object, Camera* camera,float* counter, enum ShaderType shaderType);

	void linkEnvMapping(Shader* shader, GameObject* object, Camera* camera);
	void linkPhongShader(Shader* shader, GameObject* object, Camera* camera);
	void linkFogShader(Shader* shader);
	void linkToonShader(Shader* shader);
	void linkRimShader(Shader* shader, GameObject* object, Camera* camera);
	void linkGeometryShader(Shader* shader, float* counter);
};

