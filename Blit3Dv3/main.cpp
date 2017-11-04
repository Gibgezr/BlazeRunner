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

#include "Blit3D.h"

#include "map.h"

Blit3D *blit3D = NULL;

//GLOBAL DATA
Sprite *backgroundSprite = NULL; //a pointer to a background sprite
Sprite *heartSprite = NULL;		//a pointer to a heart-shaped sprite
float angle = 0; //for rotating the hearts

TileMap* tileMap;

void Init()
{
	tileMap = new TileMap();

	Sprite* hdoor = blit3D->MakeSprite(0, 0, 64, 64, "Media\\H_Door_Close.png");

	//tileMap.LoadLevel("level1.txt");
	for(int y = 0; y < MAPHEIGHT; ++y)
		for (int x = 0; x < MAPWIDTH; ++x)
		{
			switch (tileMap->theMap[x][y]->tileID)
			{
			case TileType::DOORH:
				tileMap->theMap[x][y]->sprite = hdoor;
				break;


			default:
				assert(false && "Unknown tile id!");
				break;
			}
		}

	tileMap->flame.spriteList.push_back(hdoor);
	tileMap->flame.spriteList.push_back(hdoor);
	tileMap->flame.spriteList.push_back(hdoor);
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

//the key codes/actions/mods for DoInput are from GLFW: check its documentation for their values
void DoInput(int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		blit3D->Quit(); //start the shutdown sequence
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