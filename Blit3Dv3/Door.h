#pragma once
#include "baseTile.h"

enum class DoorType { R_V_CLOSED = 100, R_V_OPEN, R_H_CLOSED, R_H_OPEN, B_V_CLOSED, B_V_OPEN, B_H_CLOSED, B_H_OPEN };

enum class DoorColor { RED, BLUE };
enum class DoorOrientation { HOREZONTAL, VERTICAL };

class Door : public baseTile
{
public:
	int color;
	int orientation;
	Sprite* open;

	Door();
	~Door();

	void Draw(float x, float y);
	void Update(float seconds);
};

