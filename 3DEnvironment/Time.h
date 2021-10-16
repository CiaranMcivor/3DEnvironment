#pragma once
#include <SDL/SDL.h>

class Time
{

public:
	float getMilliseconds() { return deltaTime; }
	float getSeconds(){ return deltaTime * 0.001; }
	void calculateDeltaTime();

	operator float() const { return deltaTime; }
private:
	float thisFrame,lastFrame,deltaTime;




};

