#include "Window.h"

Window::Window()
{
	sdlWindow = nullptr; //initialise to generate null access violation for debugging. 
	screenWidth = 1920;
	screenHeight = 1080;
}

Window::~Window()
{
	SDL_GL_DeleteContext(glContext); // delete context
	SDL_DestroyWindow(sdlWindow); // detete window (delete the context and the window in the opposite order of creation in init)
	SDL_Quit();
}

void Window::init(const char* windowName)
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	sdlWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL); // create window

	/*Error handling*/

	if (sdlWindow == nullptr)
	{
		errorMessage("window failed to create");
	}

	glContext = SDL_GL_CreateContext(sdlWindow);

	if (glContext == nullptr)
	{
		errorMessage("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		errorMessage("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow);	//swap buffer
}

void Window::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void Window::errorMessage(std::string errorMessage)
{
	std::cout << errorMessage << std::endl;
	std::cout << "Press any  key to quit..." << std::endl;
	int input;
	std::cin >> input;
	SDL_Quit();
}

float Window::getWidth() 
{ 
	return screenWidth; 
} 
float Window::getHeight() 
{ 
	return screenHeight; 
}

