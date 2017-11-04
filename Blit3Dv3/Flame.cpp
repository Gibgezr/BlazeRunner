#include "Flame.h"

void Flame::Draw(float x, float y)
{
	spriteList[frameNum]->Blit(x, y);
}

void Flame::Update(float seconds)
{
	frameTimeSoFar += seconds;
	if (frameTimeSoFar >= timePerFrame)
	{
		frameTimeSoFar -= timePerFrame;
		frameNum++;
		if (frameNum >= spriteList.size())
			frameNum = 0;
	}
}