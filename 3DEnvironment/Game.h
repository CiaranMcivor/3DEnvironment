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
#include "SkyBox.h"
#include <vector>
enum class GameState { PLAY, EXIT };

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
	void linkFogShader();
	void linkToonShader();
	void linkRimShader();
	void linkGeometryShader();
	void linkEnvMapping(Transform object);

	Window gameWindow;
	GameState gameState;
	GameObject gameObject;
	GameObject gameObject2;
	GameObject gameObject3;
	GameObject gameObject4;
	Camera camera;
	Texture texture;
	Shader shader;
	Shader fogShader;
	Shader toonShader;
	Shader rimShader;
	Shader geometryShader;
	Shader environmentMapping;
	Audio audio;
	Skybox skybox;
	Mesh mesh;
	unsigned int bang;
	unsigned int music;
	float counter;

};

