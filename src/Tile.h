#pragma once
#ifndef __TILE__
#define __TILE__
#include "DisplayObject.h"

class Tile : public DisplayObject
{
public:

	Tile();

	~Tile();

	//Life-Cycle Functions
	void draw() override;
	void update() override;
	void clean() override;
};

#endif
