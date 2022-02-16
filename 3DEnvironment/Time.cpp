#include "Time.h"

void Time::calculateDeltaTime()
{
	lastFrame = thisFrame;
	thisFrame = SDL_GetPerformanceCounter();
	deltaTime = (float)(thisFrame - lastFrame) / (float)SDL_GetPerformanceFrequency();

}
