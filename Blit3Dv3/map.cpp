#include "map.h"

baseTile::baseTile()
{
	tileID = TileType::BASE;
}

baseTile::~baseTile()
{

}

void baseTile::Update(float seconds)
{

}

void baseTile::Draw(float x, float y)
{
	sprite->Blit(x, y);
}

void TileMap::Draw()
{
	for (int y = 0; y < MAPHEIGHT; ++y)
	{
		for (int x = 0; x < MAPWIDTH; ++x)
		{
			theMap[x][y]->Draw(x * TILESIZE + TILESIZE / 2, 1080 - (y * TILESIZE + TILESIZE / 2 + 25));
			if (theMap[x][y]->onFire) flame.Draw(x * TILESIZE + TILESIZE / 2, 1080 - (y * TILESIZE + TILESIZE / 2 + 25));
		}
	}
}

void TileMap::Update(float seconds)
{
	flame.Update(seconds);

	for (int y = 0; y < MAPHEIGHT; ++y)
	{
		for (int x = 0; x < MAPWIDTH; ++x)
		{
			theMap[x][y]->Update(seconds);
		}
	}
}

bool TileMap::SpreadFire()
{

	return false; //player didn't die
}
bool TileMap::LoadLevel(std::string filename)
{

	return true; //successfully loaded map
}

void TileMap::SaveLevel(std::string filename)
{

}