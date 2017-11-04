#include "Door.h"



Door::Door()
{
	tileID = TileType::DOOR;
	passable = false;
}


Door::~Door()
{
}

void Door::Draw(float x, float y)
{
	if (passable)
	{
		open->Blit(x, y);
	}
	else
	{
		sprite->Blit(x, y);
	}
}

void Door::Update(float seconds) {}
