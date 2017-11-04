#pragma once
#include "Blit3D.h"
#include "Flame.h"
#include "Vent.h"
#include "Player.h"
#include<string>

enum class TileType {BASE, SPACE, FLOOR, WALL, DOORH, DOORV, VENT, EXIT};

#define MAPWIDTH 30
#define MAPHEIGHT 16

#define TILESIZE 64

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

class TileMap
{
public:
	baseTile* theMap[MAPWIDTH][MAPHEIGHT] = { NULL };
	Flame flame;
	Player player;
	void Draw(); //draws all tiles and the flames
	void Update(float seconds); //updates animations for tiles and flame
	bool SpreadFire(std::vector<Vent>); //returns true if player dies
	bool isPlayerOnFlame(int nowX, int nowY);// return true if player is on fire
	bool LoadLevel(std::string filename); //returns false if it can't load the file
	void SaveLevel(std::string filename);
};
