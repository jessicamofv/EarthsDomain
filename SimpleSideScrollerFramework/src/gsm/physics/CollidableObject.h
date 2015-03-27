#pragma once
#include "stdafx.h"
#include "src\gsm\physics\BoundingVolume.h"
#include "src\gsm\physics\PhysicalProperties.h"

class CollidableObject
{
protected:
	bool currentlyCollidable;
	BoundingVolume bv;
	PhysicalProperties pp;

public:
	CollidableObject()	{}
	~CollidableObject()	{}

	// INLINED METHODS
	bool				isCurrentlyCollidable()	{ return currentlyCollidable;	}
	BoundingVolume*		getBoundingVolume()		{ return &bv;					}
	PhysicalProperties* getPhysicalProperties() { return &pp;					}

	void setCurrentlyCollidable(bool initCurrentlyCollidable)
	{	currentlyCollidable = initCurrentlyCollidable; }
};