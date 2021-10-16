#include "Time.h"

void Time::calculateDeltaTime()
{
	lastFrame = thisFrame;
	thisFrame = (float)SDL_GetPerformanceCounter();
	deltaTime = (thisFrame - lastFrame)* 1000/ (float)SDL_GetPerformanceFrequency();

}
