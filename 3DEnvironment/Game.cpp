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

	int gameObjNum = 3;
	/* Initialize each game object, set the object to be loaded, texture, collision position and radius*/
	for (size_t i = 0; i < gameObjNum; i++)
	{
		renderData.push_back(ShaderData());
	}

	renderData[0].gameObject.init("..\\res\\monkey3.obj", "..\\res\\bricks.jpg", *renderData[0].gameObject.getTransform().GetPos(), 2.0f);
	renderData[0].gameObject.setPosition(glm::vec3{ 0,0,-15 });
	renderData[1].gameObject.init("..\\res\\cube.obj", *renderData[1].gameObject.getTransform().GetPos(), 2.0f);
	renderData[1].gameObject.setPosition(glm::vec3{-10,0,-15});
	renderData[1].gameObject.setRotation(0);
	renderData[2].gameObject.init("..\\res\\sphere.obj", *renderData[2].gameObject.getTransform().GetPos(), 2.0f);
	renderData[2].gameObject.setPosition(glm::vec3{ 10,0,-15 });
	camera.setViewtarget(&renderData[0].gameObject);

	/*load all required audio files*/
	bang = audio.loadSound("..\\res\\bang.wav");
	music = audio.loadSound("..\\res\\background.wav");
	/*Shaders*/
	//shader.init("..\\res\\shader"); 
	raymarchShader.init("..\\res\\thirdShader.vert", "..\\res\\thirdShader.frag");
	thirdShader.init("..\\res\\phongShader.vert", "..\\res\\phongShader.frag");
	renderData[2].shader.init("..\\res\\phongShader.vert", "..\\res\\phongShader.frag");
	renderData[1].shader.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");
	renderData[0].shader.init("..\\res\\geometryShader.vert", "..\\res\\geometryShader.frag", "..\\res\\geometryShader.geom");
	renderData[2].linkerType = ShaderType::PHONG;
	renderData[1].linkerType = ShaderType::ENVMAPPING;
	renderData[0].linkerType = ShaderType::GEOMETRY;
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

		case SDL_MOUSEWHEEL:

			camera.MoveForward(event.wheel.y * deltaTime);
			
			// Standard WASD controls from moving an object in the 4 cardinal directions W - Up,S - Down,A - Left, D - Right
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				/* All inputs get the current position of the object, its transform vector, and adds a new vector to the value of the relevant axis. */
			case SDLK_1:
				camera.setViewtarget(&renderData[0].gameObject);
				break;

			case SDLK_2:
				camera.setViewtarget(&renderData[1].gameObject);
				break;
			case SDLK_3:
				camera.setViewtarget(&renderData[2].gameObject);
				break;

			//case SDLK_d:
			//	gameObject.setVelocity(glm::vec3{ -0.1,0,0 });
			//	break;

			//case SDLK_SPACE:
			//	gameObject.setVelocity(glm::vec3{ 0,0,-0.1 });
			//	break;

			//case SDLK_LSHIFT:
			//	gameObject.setVelocity(glm::vec3{ 0,0,0.1 });
			//	break;

			//case SDLK_e:
			//	gameObject.setVelocity(glm::vec3{ 0,0,0});
			//	break;
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


void Game::update()
{
	deltaTime.calculateDeltaTime();
	cout <<deltaTime << endl;
	counter = (counter + 0.001f);
	/*Check for collision between two objects using their collision spheres*/
	//hasCollided(gameObject,gameObject2);
	//hasCollided(gameObject2, gameObject3);
	camera.update();
	renderData[0].gameObject.update();
	renderData[0].gameObject.setRotation(counter);
	renderData[1].gameObject.setRotation(counter/2);
	renderData[1].gameObject.update();



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

void Game::runThirdShader()
{
	glDisable(GL_DEPTH_TEST);

	raymarchShader.Bind();
	raymarchShader.setFloat("time", counter * 2);
	raymarchShader.setVec2("resolution", glm::vec2(gameWindow.getWidth(), gameWindow.getHeight()));
	raymarchShader.setVec3("camera", camera.getPos());
	thirdShader.setVec3("lightColour", 1.0f, 1.0f, 1.0f);

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_QUADS);
	glVertex3f(1, -1.0f, 0);
	glVertex3f(1, 1, -1);
	glVertex3f(-1.0f, 1, 0);
	glVertex3f(-1.0f, -1, 0);

}

void Game::draw()
{
	// Clear the widows colours.
	gameWindow.clear(0.0f, 0.0f, 0.0f, 1.0f); //sets our background colour

	for (int i = 0; i < 3; i++) 
	{
		renderData[i].shader.Bind();
		linker.linkShader(&renderData[i].shader, &renderData[i].gameObject, &camera, &counter, renderData[i].linkerType);
		renderData[i].shader.Update(renderData[i].gameObject.getTransform(), camera);
		renderData[i].gameObject.draw();
	}

	//geometryShader.Bind();
	//linkGeometryShader();
	//geometryShader.Update(gameObject.getTransform(), camera);
	//gameObject.draw();

	//environmentMapping.Bind();
	//linkEnvMapping(gameObject2.getTransform());
	//environmentMapping.Update(gameObject2.getTransform(), camera);
	//gameObject2.draw();

	//thirdShader.Bind();
	//linkPhongShader(gameObject3.getTransform());
	//thirdShader.Update(gameObject3.getTransform(), camera);
	//gameObject3.draw();



	//Uncomment for raymarched sphere with phong shading, could only get the shader to run on a fullscreen plane and it will render over eveything.
	//runThirdShader();

	skybox.draw(&camera);


	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameWindow.swapBuffer();

}
