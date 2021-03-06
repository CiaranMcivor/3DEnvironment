#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObject.h"
#include "Audio.h"
#include "Cube.h"
#include "SkyBox.h"
#include "Linker.h"
#include "Time.h"
#include "FBO.h"
#include "GBuffer.h"
#include <vector>
#include <thread>
enum class GameState { PLAY, EXIT };


struct ShaderData {

	GameObject* gameObject;
	Shader shader;
	enum ShaderType linkerType;
};


class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void init();
	void handleInput();
	void gameLoop();
	void draw();
	void playAudio(unsigned int Source, glm::vec3 pos);
	void update();
	bool hasCollided(GameObject& object1, GameObject& object2);
	void runThirdShader();


	glm::vec3 cameraPosition;
	std::vector<ShaderData> renderData;
	std::vector<Mesh> mesh;
	GameObject gameObject[3];
	GameObject gameObject1;

	Window gameWindow;
	GameState gameState;

	FBO fbo;
	GBuffer gBuffer;

	Camera camera;
	Texture texture;
	Linker linker;
	Shader shader;
	Shader fogShader;
	Shader toonShader;
	Shader rimShader;
	Shader geometryShader;
	Shader environmentMapping;
	Shader thirdShader;
	Shader raymarchShader;
	Shader shaders[3];
	Shader gBufferShader;
	Audio audio;
	Skybox skybox;

	Time deltaTime;
	unsigned int bang;
	unsigned int music;
	float counter;
	GLuint shader1;
	GLuint vao;
	GLuint vbo;

	Cube cube;

	float vertices[];


};

