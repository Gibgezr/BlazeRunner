#pragma once
#include "Blit3D.h"
#include<vector>


class Flame
{
public:
	std::vector<Sprite *> spriteList;
	int frameNum = 0;
	float frameTimeSoFar = 0;
	float timePerFrame = 1.f / 10.f;

	void Draw(float x, float y);
	void Update(float seconds);
};