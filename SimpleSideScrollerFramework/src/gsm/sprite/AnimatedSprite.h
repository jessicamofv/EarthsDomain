/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	AnimatedSprite.h

	This class represents a sprite that can can
	be used to animate a game character or object.
*/

#pragma once
#include "stdafx.h"
#include "src\gsm\physics\BoundingVolume.h"
#include "src\gsm\physics\CollidableObject.h"
#include "src\gsm\physics\PhysicalProperties.h"
#include "src\gsm\sprite\AnimatedSpriteType.h"
#include "src\gui\Viewport.h"
// i added this
#include <Box2D/Box2D.h>

class AnimatedSprite : public CollidableObject
{
private:
	// SPRITE TYPE FOR THIS SPRITE. THE SPRITE TYPE IS THE ID
	// OF AN AnimatedSpriteType OBJECT AS STORED IN THE SpriteManager
	AnimatedSpriteType *spriteType;

	// TRANSPARENCY/OPACITY
	int alpha;

	// THE "current" STATE DICTATES WHICH ANIMATION SEQUENCE 
	// IS CURRENTLY IN USE, BUT IT MAP ALSO BE USED TO HELP
	// WITH OTHER GAME ACTIVITIES, LIKE PHYSICS
	wstring currentState;

	// THE INDEX OF THE CURRENT FRAME IN THE ANIMATION SEQUENCE
	// NOTE THAT WE WILL COUNT BY 2s FOR THIS SINCE THE VECTOR
	// THAT STORES THIS DATA HAS (ID,DURATION) TUPLES
	unsigned int frameIndex;

	// USED TO ITERATE THROUGH THE CURRENT ANIMATION SEQUENCE
	unsigned int animationCounter;

	// i added this
	// have a variable that associates the sprite
	// with a box2d body
	b2Body *body;

	// 5-7
	int destroyFlag;

public:
	// INLINED ACCESSOR METHODS
	int					getAlpha()			{ return alpha;				}
	wstring				getCurrentState()	{ return currentState;		}
	unsigned int		getFrameIndex()		{ return frameIndex;		}
	AnimatedSpriteType*	getSpriteType()		{ return spriteType;		}
	// i added this
	b2Body*				getBody()			{ return body;				}
	// 5-7
	int					getDestroyFlag()		{ return destroyFlag; }

	// INLINED MUTATOR METHODS
	void setAlpha(int initAlpha)
	{	alpha = initAlpha;						}
	void setSpriteType(AnimatedSpriteType *initSpriteType)
	{	spriteType = initSpriteType;			}
	// i added this
	void setBody(b2Body *initBody)
	{	body = initBody;						}
	// 5-7
	void setDestroyFlag(int initDestroyFlag)
	{	destroyFlag = initDestroyFlag;		}

	// METHODS DEFINED IN AnimatedSprite.cpp
	AnimatedSprite();
	~AnimatedSprite();
	void changeFrame();
	unsigned int getCurrentImageID();
	void setCurrentState(wstring newState);
	void updateSprite();
};