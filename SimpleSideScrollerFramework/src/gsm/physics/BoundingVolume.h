#pragma once
#include "stdafx.h"

#define AABB 0
#define CIRCLE 1

class BoundingVolume
{
protected:
	float x;
	float y;
	float width;
	float height;
	int type;

public:
	BoundingVolume(){}
	~BoundingVolume(){}

	// INLINED METHODS	

	void incX(float xInc) { x += xInc; }
	void incY(float yInc) { y += yInc; }

	// METHODS DEFINED INSIDE DESCENDANTS
	int getType(){ return type; }
	float getWidth() { return width; }
	float getHeight(){ return height; }
	float getX() { return x; };
	float getY() { return y; };

	void setType(int initType) { type = initType; }
	void setWidth(float initWidth) { width = initWidth; }
	void setHeight(float initHeight) { height = initHeight; }
	void setX(float initX) { x = initX; }
	void setY(float initY) { y = initY; }
};