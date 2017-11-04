#include "Player.h"
#include "map.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Draw(float x, float y)
{
	sprite->Blit(x, y);
}

void Player::Draw()
{
	sprite->Blit(x * TILESIZE + TILESIZE / 2, 1080 - (y * TILESIZE + TILESIZE / 2 + 25));
}

void Player::Update(float seconds)
{

}