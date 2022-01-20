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
	fbo.init(gameWindow.getWidth(), gameWindow.getHeight());
	fbo.initShader();
	fbo.generateQuad();

	gBuffer.init(gameWindow.getWidth(), gameWindow.getHeight());
	gBuffer.generateQuad();
	gBuffer.initShader();

	int gameObjNum = 3;
	
	/* Initialize each game object, set the object to be loaded, texture, collision position and radius*/
	for (size_t i = 0; i < gameObjNum; i++)
	{
		renderData.push_back(ShaderData());
	}
	for (size_t i = 0; i < 4; i++)
	{
		mesh.push_back(Mesh());
	}

	for (size_t i = 0; i < gameObjNum; i++)
	{
		//gameObject.push_back(GameObject());
	}
	std::ifstream modelPaths("ModelPath.txt");
	std::string path;

	

	for (int i = 0; i < 4; i++) {
		std::getline(modelPaths, path);
		mesh[i].loadModel(path);
		//str.push_back('\n');
		std::cout << path;
	}

	gameObject[0].init(&mesh[0], "..\\res\\bricks.jpg", *gameObject[0].getTransform().GetPos(), 2.0f);
	gameObject[0].setPosition(glm::vec3{ 0,0,-15 });
	gameObject[1].init(&mesh[1], *gameObject[1].getTransform().GetPos(), 2.0f);
	gameObject[1].setPosition(glm::vec3{ -10,0,-15 });
	gameObject[1].setRotation(0);
	gameObject[2].init(&mesh[2], *gameObject[2].getTransform().GetPos(), 2.0f);
	gameObject[2].setPosition(glm::vec3{ 10,0,-15 });


	gameObject1.init(&mesh[3], *gameObject1.getTransform().GetPos(), 2.0f);
	gameObject1.setPosition(glm::vec3{ 0,0,-15 });
	for (int i = 0; i < 3; i++) {
		renderData[i].gameObject = &gameObject[i];
	}

	camera.setViewtarget(&gameObject1);

	/*load all required audio files*/
	bang = audio.loadSound("..\\res\\bang.wav");
	music = audio.loadSound("..\\res\\background.wav");
	/*Shaders*/
	//shader.init("..\\res\\shader"); 
	raymarchShader.init("..\\res\\thirdShader.vert", "..\\res\\thirdShader.frag");
	thirdShader.init("..\\res\\phongShader.vert", "..\\res\\phongShader.frag");

	renderData[2].linkerType = ShaderType::PHONG;
	renderData[1].linkerType = ShaderType::ENVMAPPING;
	renderData[0].linkerType = ShaderType::ENVMAPPING;

	for (int i = 0; i < renderData.size(); i++) {
		linker.init(&renderData[i].shader, renderData[i].linkerType);
	}
	fogShader.init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");
	toonShader.init("..\\res\\toonShader.vert", "..\\res\\toonShader.frag");
	rimShader.init("..\\res\\rimShader.vert", "..\\res\\rimShader.frag");
	geometryShader.init("..\\res\\geometryShader.vert", "..\\res\\geometryShader.frag","..\\res\\geometryShader.geom");
	environmentMapping.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");
	
	/*Skybox Init*/
	vector<std::string> faces
	{
		"..\\res\\skybox1\\right.png",
		"..\\res\\skybox1\\left.png",
		"..\\res\\skybox1\\top.png",
		"..\\res\\skybox1\\bottom.png",
		"..\\res\\skybox1\\front.png",
		"..\\res\\skybox1\\back.png"
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
				camera.setViewtarget(&gameObject[0]);
				break;

			case SDLK_2:
				camera.setViewtarget(&gameObject[1]);
				break;
			case SDLK_3:
				camera.setViewtarget(&gameObject[2]);
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
	gameObject[0].update();
	gameObject[0].setRotation(counter);
	gameObject[1].setRotation(counter/2);
	gameObject[1].update();
	cameraPosition = camera.getPos();



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


	//fbo.bind();
	//for (int i = 0; i < 3; i++) 
	//{
	//	renderData[i].shader.Bind();
	//	linker.linkShader(&renderData[i].shader, renderData[i].gameObject, &camera, &counter, renderData[i].linkerType);
	//	renderData[i].shader.Update(renderData[i].gameObject->getTransform(), camera);
	//	renderData[i].gameObject->draw();
	//}

	//renderData[1].shader.Bind();
	//linker.linkShader(&renderData[1].shader, renderData[1].gameObject, &camera, &counter, renderData[1].linkerType);
	//renderData[1].gameObject->draw();
	//skybox.draw(&camera);

	//fbo.unbind();
	//fbo.render();

	gBuffer.render(&gameObject1, &camera);



	//Uncomment for raymarched sphere with phong shading, could only get the shader to run on a fullscreen plane and it will render over eveything.
	//runThirdShader();

	gameWindow.swapBuffer();

}
