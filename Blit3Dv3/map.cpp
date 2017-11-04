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

bool TileMap::SpreadFire(std::vector<Vent> vent)
{

	bool touchedPlayer = false;
	int xOffSet[4] = { -1,1,0,0 };
	int yOffSet[4] = { 0,0,-1,1 };
	//get current vent's location
	for (int i = 0; i < vent.size(); i++)
	{
		int x = vent[i].x;
		int y = vent[i].y;
		//do checks on contiguous tiles 
		for (int dir = 0; dir < 4; ++dir)
		{
			int nowX = x + xOffSet[dir];
			int nowY = y + yOffSet[dir];

			if (nowX < MAPWIDTH && nowY < MAPHEIGHT)
			{

				//do a check to see if character sprite is present on current tile
				/*
				if ()
				{
				//return true is the player is dead???
				touchedPlayer = true;
				}
				*/
			}
			else if (theMap[nowX][nowY]->passable == true && theMap[nowX][nowY]->onFire == false)
			{
				theMap[nowX][nowY]->onFire = true;
			}


		}

	}


	return false; //player didn't die
}

bool TileMap::LoadLevel(std::string filename)
{
	std::string row;
	std::ifstream mapFile(filename);
	if (mapFile.is_open())
	{
		while (getline(mapFile, row))
		{
			for (int y = 0; y < MAPHEIGHT; ++y)
			{
				for (int x = 0; x < MAPWIDTH; ++x)
				{
					//TileType{ BASE, SPACE, FLOOR, WALL, DOORH, DOORV, VENT, EXIT };
					switch (row.c_str()[x]) {
					case '0':
						theMap[x][y] = new baseTile();
						theMap[x][y]->tileID = TileType::SPACE;
						break;
					case '1':
						theMap[x][y] = new baseTile();
						theMap[x][y]->tileID = TileType::FLOOR;
						break;
					case '2':
						theMap[x][y] = new baseTile();
						theMap[x][y]->tileID = TileType::WALL;
						break;
					case '3':
						theMap[x][y] = new baseTile();
						theMap[x][y]->tileID = TileType::DOORH;
						break;
					case '4':
						theMap[x][y] = new baseTile();
						theMap[x][y]->tileID = TileType::DOORV;
						break;
					case '5':
						theMap[x][y] = new baseTile();
						theMap[x][y]->tileID = TileType::VENT;
						break;
					case '6':
						theMap[x][y] = new baseTile();
						theMap[x][y]->tileID = TileType::EXIT;
						break;
					default:

						break;
					}

				}
			}

		}
		mapFile.close();
	}

	else std::cout << "Unable to open file";

	return true; //successfully loaded map
}

void TileMap::SaveLevel(std::string filename)
{
	std::ofstream mapFile(filename);
	if (mapFile.is_open())
	{

		for (int y = 0; y < MAPHEIGHT; ++y)
		{
			for (int x = 0; x < MAPWIDTH; ++x)
			{
				//TileType{ BASE, SPACE, FLOOR, WALL, DOORH, DOORV, VENT, EXIT };
				switch (theMap[x][y]->tileID) {
				case TileType::SPACE:
					mapFile << '0';
					break;
				case  TileType::FLOOR:
					mapFile << '1';
					break;
				case  TileType::WALL:
					mapFile << '2';
					break;
				case  TileType::DOORH:
					mapFile << '3';
					break;
				case  TileType::DOORV:
					mapFile << '4';
					break;
				case  TileType::VENT:
					mapFile << '5';
					break;
				case  TileType::EXIT:
					mapFile << '6';
					break;
				default:

					break;
				}
			}
			mapFile << '\n';
		}
		mapFile.close();
	}
	else std::cout << "Unable to open file";
}
