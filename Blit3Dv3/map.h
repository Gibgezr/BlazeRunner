#pragma once
#include "Blit3D.h"
#include "Door.h"
#include "Flame.h"
#include "Floor.h"
#include "Space.h"
#include "Vent.h"
#include "Wall.h"
#include "Player.h"
#include "Exit.h"

#include<string>

#define MAPWIDTH 30
#define MAPHEIGHT 16

#define TILESIZE 64



class TileMap
{
public:
	baseTile* theMap[MAPWIDTH][MAPHEIGHT] = { NULL };
	Flame flame;
	Player player;

	bool drawnPlayer1StTime = false;
	void Draw(); //draws all tiles and the flames
	void Update(float seconds); //updates animations for tiles and flame
	bool SpreadFire(std::vector<Vent> vent); //returns true if player dies
	bool isPlayerOnFlame(int nowX, int nowY);// return true if player is on fire
	bool LoadLevel(std::string filename); //returns false if it can't load the file
	void SaveLevel(std::string filename);
};