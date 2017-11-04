#pragma once
#include "Blit3D.h"

enum class TileType { BASE, SPACE, FLOOR, WALL, VENT, EXIT, DOOR, END_ENUM};

class baseTile
{
public:
	Sprite *sprite = NULL;
	bool passable = false; //can player/fire move here?
	TileType tileID = TileType::BASE;
	bool onFire = false;
	bool connectsToVent = false; //can this tile connect via passable

	virtual void Draw(float x, float y);
	virtual void Update(float seconds);
	baseTile();
	virtual ~baseTile();
};