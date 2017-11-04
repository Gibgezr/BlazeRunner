#pragma once
#include "Blit3D.h"

class Player
{
public:
	Sprite *sprite = NULL;
	int x = 0;
	int y = 0;

	Player();
	~Player();
	void Draw(float x, float y); //draws the player
	void Draw(); //draws the player
	void Update(float seconds); //updates animations for player
};