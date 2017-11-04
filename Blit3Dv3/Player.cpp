#include "Player.h"



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
	sprite->Blit(x, y);
}

void Player::Update(float seconds)
{

}