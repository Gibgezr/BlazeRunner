#pragma once

class Player
{
public:

	int x = 0;
	int y = 0;

	Player();
	~Player();
	void Draw(); //draws the player
	void Update(float seconds); //updates animations for player
};