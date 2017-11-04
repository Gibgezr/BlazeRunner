/*
	Simple example of loading/rotating/displaying sprites in Blit3D
*/
//memory leak detection
#define CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <stdlib.h>
#include <crtdbg.h>

#include "map.h"
#include "Blit3D.h"


Blit3D *blit3D = NULL;


//GLOBAL DATA
float angle = 0; //for rotating the hearts

TileMap* tileMap;
Sprite* playerSpriteFront;
Sprite* playerSpriteBack;
Sprite* playerSpriteLeft;
Sprite* playerSpriteRight;

Sprite* spaceSprite;
Sprite* floorSprite;
Sprite* wallSprite;
Sprite* ventSprite;
Sprite* exitSprite;

Sprite* door_Red_V_Open_Sprite;
Sprite* door_Red_V_Closed_Sprite;
Sprite* door_Red_H_Open_Sprite;
Sprite* door_Red_H_Closed_Sprite;

Sprite* door_Blue_V_Open_Sprite;
Sprite* door_Blue_V_Closed_Sprite;
Sprite* door_Blue_H_Open_Sprite;
Sprite* door_Blue_H_Closed_Sprite;

Sprite *flame1;


void Init()
{
	tileMap = new TileMap();

	flame1 = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Fire_Fix_Frame_1.png");

	tileMap->flame.spriteList.push_back(flame1);
	//make player

	playerSpriteFront = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Character_Idle_Front.png");
	playerSpriteBack = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Character_Idle_Back.png");
	playerSpriteLeft = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Character_Idle_Left.png");
	playerSpriteRight = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Character_Idle_Right.png");
	tileMap->player.sprite = playerSpriteFront;


	door_Blue_H_Closed_Sprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\H_Door_Blue_Close-1.png");
	door_Blue_H_Open_Sprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\H_Door_Blue_Open.png");
	door_Blue_V_Closed_Sprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\V_Door_Blue_Close-1.png");
	door_Blue_V_Open_Sprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\V_Door_Blue_Open.png");

	door_Red_H_Closed_Sprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\H_Door_Red_Close-1.png");
	door_Red_H_Open_Sprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\H_Door_Red_Open.png");
	door_Red_V_Closed_Sprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\V_Door_Red_Close-1.png");
	door_Red_V_Open_Sprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\V_Door_Red_Open.png");

	spaceSprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Space_Tile_A.png");
	floorSprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Floor_Tile_Base.png");
	wallSprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Wall_Tile_A.png");
	ventSprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Vent_Tile_Glow.png");
	exitSprite = blit3D->MakeSprite(0, 0, 64, 64, "Media\\Exit_Tile.png");

	tileMap->LoadLevel("level1.txt");

	//for (int y = 0; y < MAPHEIGHT; ++y)
	//	for (int x = 0; x < MAPWIDTH; ++x)
	//	{
	//		tileMap->theMap[x][y] = new FloorTile;
	//		tileMap->theMap[x][y]->tileID = TileType::FLOOR;
	//	}

	for (int y = 0; y < MAPHEIGHT; ++y)
		for (int x = 0; x < MAPWIDTH; ++x)
		{
			switch (tileMap->theMap[x][y]->tileID)
			{
			case TileType::DOOR:
			{
				Door* door = (Door*)tileMap->theMap[x][y];

				if (door->color == (int)DoorColor::RED)
				{
					if (door->orientation == (int)DoorOrientation::HOREZONTAL)
					{
						door->sprite = door_Red_H_Closed_Sprite;
						door->open = door_Red_H_Open_Sprite;
					}
					else
					{
						door->sprite = door_Red_V_Closed_Sprite;
						door->open = door_Red_V_Open_Sprite;
					}
				}
				else
				{
					if (door->orientation == (int)DoorOrientation::HOREZONTAL)
					{
						door->sprite = door_Blue_H_Closed_Sprite;
						door->open = door_Blue_H_Open_Sprite;
					}
					else
					{
						door->sprite = door_Blue_V_Closed_Sprite;
						door->open = door_Blue_V_Open_Sprite;
					}
				}
			}
			break;

			case TileType::SPACE:
				tileMap->theMap[x][y]->sprite = spaceSprite;
				break;

			case TileType::FLOOR:
				tileMap->theMap[x][y]->sprite = floorSprite;
				break;

			case TileType::WALL:
				tileMap->theMap[x][y]->sprite = wallSprite;
				break;

			case TileType::VENT:
				tileMap->theMap[x][y]->sprite = ventSprite;
				break;

			case TileType::EXIT:
				tileMap->theMap[x][y]->sprite = exitSprite;
				break;

			default:
				assert(false && "Unknown tile id!");
				break;
			}
		}
}


void DeInit(void)
{
	delete tileMap;
	//any sprites/fonts still allocated are freed automatically by the Blit3D object when we destroy it
}

void Update(double seconds)
{
	//change the angle variable based on time passed since last update
	angle += static_cast<float>(seconds) * 45.f;
	if (angle > 360.f) angle -= 360.f;

	tileMap->Update((float)seconds);
}

void Draw(void)
{
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);	//clear colour: r,g,b,a 	
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw stuff here
	tileMap->Draw();

}

bool canMove(int x, int y)
{
	if (x < 0 || y < 0)
		return false;

	if (x >= MAPWIDTH || y >= MAPHEIGHT)
		return false;

	if (tileMap->theMap[x][y]->passable)
		return true;
	else
		return false;

}
//the key codes/actions/mods for DoInput are from GLFW: check its documentation for their values
void DoInput(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		blit3D->Quit(); //start the shutdown sequence
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		int tempY = tileMap->player.y - 1;
		int tempX = tileMap->player.x;
		if (canMove(tempX, tempY))
		{
			tileMap->player.y = tempY;
		}

	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		int tempY = tileMap->player.y;
		int tempX = tileMap->player.x - 1;
		if (canMove(tempX, tempY))
		{
			tileMap->player.x = tempX;
		}
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		int tempY = tileMap->player.y + 1;
		int tempX = tileMap->player.x;
		if (canMove(tempX, tempY))
		{
			tileMap->player.y = tempY;
		}
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		int tempY = tileMap->player.y;
		int tempX = tileMap->player.x + 1;
		if (canMove(tempX, tempY))
		{
			tileMap->player.x = tempX;
		}
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		//toggle door?

		int offsetX[4] = { -1,1,0,0 };
		int offsetY[4] = { 0,0,-1,1 };

		for (int i = 0; i < 4; ++i)
		{
			int tempX = tileMap->player.x + offsetX[i];
			int tempY = tileMap->player.y + offsetY[i];

			if ((int)tileMap->theMap[tempX][tempY]->tileID == (int)TileType::DOOR)
			{
				Door* door = (Door *)tileMap->theMap[tempX][tempY];
				int doorcolor = door->color;

				for (int y = 0; y < MAPHEIGHT; ++y)
					for (int x = 0; x < MAPHEIGHT; ++x)
					{
						if ((int)tileMap->theMap[x][y]->tileID == (int)TileType::DOOR)
						{
							Door* tdoor = (Door*)tileMap->theMap[x][y];
							if (tdoor->color == doorcolor)
							{
								tdoor->passable = !tdoor->passable;
							}
						}
					}
			}
		}

		for(int y = 0; y < MAPHEIGHT; ++y)
			for (int x = 0; x < MAPHEIGHT; ++x)
			{
				tileMap->theMap[x][y]->onFire = false;
			}

		tileMap->SpreadFire();
	}

}

int main(int argc, char *argv[])
{
	//memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//set X to the memory allocation number in order to force a break on the allocation:
	//useful for debugging memory leaks, as long as your memory allocations are deterministic.
	//_crtBreakAlloc = X;

	blit3D = new Blit3D(Blit3DWindowModel::BORDERLESSFULLSCREEN_1080P, 640, 400);

	//set our callback funcs
	blit3D->SetInit(Init);
	blit3D->SetDeInit(DeInit);
	blit3D->SetUpdate(Update);
	blit3D->SetDraw(Draw);
	blit3D->SetDoInput(DoInput);

	//Run() blocks until the window is closed
	blit3D->Run(Blit3DThreadModel::SINGLETHREADED);
	if (blit3D) delete blit3D;
}