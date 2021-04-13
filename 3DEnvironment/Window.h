#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;
class Window
{
public:
	Window();
	~Window();
	void init(const char *windowName);
	void swapBuffer();
	void clear(float r, float g, float b, float a);
	float getWidth();
	float getHeight();

private:

	void errorMessage(std::string errorMessage);

	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to window
	int screenWidth;
	int screenHeight;
};

