#include "Game.h"


Game::Game()
{
	gameState = GameState::PLAY;
	Window* gameWindow = new Window();

	counter = 0.0f;
}

Game::~Game()
{
}

void Game::run()
{
	init();
	gameLoop();
}

void Game::init()
{
	/*Initialize window*/
	gameWindow.init("3D Env");		

	/* Initialize each game object, set the object to be loaded, texture, collision position and radius*/

	gameObject.init("..\\res\\monkey3.obj", "..\\res\\bricks.jpg", *gameObject.getTransform().GetPos(), 2.0f);
	gameObject.setPosition(glm::vec3{ 0,0,0 });
	gameObject2.init("..\\res\\cube.obj", *gameObject2.getTransform().GetPos(), 2.0f);
	gameObject2.setPosition(glm::vec3{0,0,-20 });
	gameObject2.setRotation(0);



	/*load all required audio files*/
	bang = audio.loadSound("..\\res\\bang.wav");
	music = audio.loadSound("..\\res\\background.wav");
	/*Shaders*/
	//shader.init("..\\res\\shader"); 
	fogShader.init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");
	toonShader.init("..\\res\\toonShader.vert", "..\\res\\toonShader.frag");
	rimShader.init("..\\res\\rimShader.vert", "..\\res\\rimShader.frag");
	geometryShader.init("..\\res\\geometryShader.vert", "..\\res\\geometryShader.frag","..\\res\\geometryShader.geom");
	environmentMapping.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");
	
	/*Skybox Init*/
	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};

	skybox.init(faces);

	/*Initialize the camera, taking position in world, fov,width,height and culling distances*/
	camera.initCamera(glm::vec3(0, 0, -30), 70.0f, (float)gameWindow.getWidth() / gameWindow.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void Game::handleInput()
{

	SDL_Event event;

	while (SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;

			// Standard WASD controls from moving an object in the 4 cardinal directions W - Up,S - Down,A - Left, D - Right
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				/* All inputs get the current position of the object, its transform vector, and adds a new vector to the value of the relevant axis. */
			case SDLK_w:
				camera.RotateY(10.0f);
				break;

			case SDLK_s:
				gameObject.setVelocity(glm::vec3{ 0,-0.1,0 });
				break;
			case SDLK_a:
				gameObject.setVelocity(glm::vec3{ 0.1,0,0 });
				break;

			case SDLK_d:
				gameObject.setVelocity(glm::vec3{ -0.1,0,0 });
				break;

			case SDLK_SPACE:
				gameObject.setVelocity(glm::vec3{ 0,0,-0.1 });
				break;

			case SDLK_LSHIFT:
				gameObject.setVelocity(glm::vec3{ 0,0,0.1 });
				break;

			case SDLK_e:
				gameObject.setVelocity(glm::vec3{ 0,0,0});
				break;
			}

			
		}



	}
}


void Game::playAudio(unsigned int Source, glm::vec3 pos)
{

	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		audio.playSound(Source, pos);
	}
}

void Game::linkFogShader() 
{
	//fogShader.setMat4("u_pm", camera.getProjection());
	//fogShader.setMat4("u_vm", camera.getView());
	//fogShader.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	fogShader.setFloat("minDist", -5.0f);
	fogShader.setFloat("maxDist", 40.0f);

	fogShader.setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

}

void Game::linkToonShader() 
{
	toonShader.setVec3("lightDirection", glm::vec3(0.5f, 0.5f, 0.5f));
}
void Game::linkRimShader()
{
	glm::vec3 camDir;
	camDir = gameObject.getCollisionPos() - camera.getPos();
	camDir = glm::normalize(camDir);
	rimShader.setMat4("u_pm", camera.getProjection());
	rimShader.setMat4("u_vm", camera.getView());
	rimShader.setMat4("model", gameObject.getTransform().GetModel());
	rimShader.setMat4("view", camera.getView());
	rimShader.setVec3("lightDir", glm::vec3(0.2f, 0.2f, 0.2f));
}
void Game::linkGeometryShader()
{
	//float randX = ((float)rand() / (RAND_MAX));
	//float randY = ((float)rand() / (RAND_MAX));
	//float randZ = ((float)rand() / (RAND_MAX));
	//// Frag: uniform float randColourX; uniform float randColourY; uniform float randColourZ;
	//geometryShader.setFloat("randColourX", randX);
	//geometryShader.setFloat("randColourY", randY);
	//geometryShader.setFloat("randColourZ", randZ);
	// Geom: uniform float time;
	geometryShader.setFloat("time", counter * 2);
}
void Game::linkEnvMapping(Transform object)
{
	//environmentMapping.setInt("skybox", 0);
	environmentMapping.setMat4("projection", camera.getProjection());
	environmentMapping.setMat4("view", camera.getView());
	environmentMapping.setMat4("model", object.GetModel());
	environmentMapping.setVec3("cameraPos", camera.getPos());
}
void Game::update()
{
	counter = counter + 0.001f;
	/*Check for collision between two objects using their collision spheres*/
	//hasCollided(gameObject,gameObject2);
	//hasCollided(gameObject2, gameObject3);
	gameObject.update();
	gameObject.setRotation(counter);
	gameObject2.setRotation(counter);
	gameObject2.update();

}

bool Game::hasCollided(GameObject& object1, GameObject& object2)
{
	float distance = ((object2.getCollisionPos().x - object1.getCollisionPos().x) * object2.getCollisionPos().x - object1.getCollisionPos().x) + (object2.getCollisionPos().y - object1.getCollisionPos().y) * (object2.getCollisionPos().y - object1.getCollisionPos().y) + (object2.getCollisionPos().z - object1.getCollisionPos().z) * (object2.getCollisionPos().z - object1.getCollisionPos().z);		// Distance between the center of each game objcets collision spheres. sqr root avoided due to computation cost

	if (distance * distance < (object1.getCollisionRadius() + object2.getCollisionRadius()))	// If they are closer than the radius of the sphere return true
	{
		audio.setlistener(camera.getPos(), object1.getPosition());
		std::cout << "Collided" << std::endl;
		//playAudio(bang, object1.getPosition());
		object2.setVelocity(object1.getVelocity());
		object1.setVelocity(-object1.getVelocity());
		return true;
	}
	else
	{
		return false;
	}
}

void Game::gameLoop()
{
	while (gameState != GameState::EXIT)
	{
		handleInput();
		update();
		draw();
		//playAudio(music, glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void Game::draw()
{
	// Clear the widows colours.
	gameWindow.clear(0.8f, 0.8f, 0.8f, 1.0f); //sets our background colour


	environmentMapping.Bind();
	linkEnvMapping(gameObject2.getTransform());
	environmentMapping.Update(gameObject2.getTransform(), camera);
	gameObject2.draw(skybox.textureID);



	//linkToonShader();
	//toonShader.Bind();
	//toonShader.Update(gameObject2.getTransform(),camera);
	//gameObject2.draw();

	geometryShader.Bind();
	linkGeometryShader();
	geometryShader.Update(gameObject.getTransform(), camera);
	gameObject.draw();

	skybox.draw(&camera);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameWindow.swapBuffer();

}
