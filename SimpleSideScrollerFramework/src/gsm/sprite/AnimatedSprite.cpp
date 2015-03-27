/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	AnimatedSprite.cpp

	See AnimatedSprite.h for a class description.
*/

#include "stdafx.h"
#include "src\gsm\physics\PhysicalProperties.h"
#include "src\gsm\sprite\AnimatedSprite.h"
#include "src\gsm\sprite\AnimatedSpriteType.h"

/*
	AnimatedSprite - Default constructor, just sets everything to 0.
*/
AnimatedSprite::AnimatedSprite()  
{
	spriteType = 0;
	frameIndex = 0;
	animationCounter = 0;
	pp.setVelocity(0.0f, 0.0f);
	pp.setAccelerationX(0.0f);
	pp.setAccelerationY(0.0f);
	pp.setPosition(0.0f, 0.0f);
	// i added this
	body = NULL;
	// 5-7
	destroyFlag = 0;
}

/*
	Destructor - Nothing to clean up. We don't want to clean up the
	sprite type because it is a shared variable.
*/
AnimatedSprite::~AnimatedSprite() 
{
	// i added this
	// delete body;
}

/*
	changeFrame - This method allows for the changing of an image in an 
	animation sequence for a given animation state.
*/
void AnimatedSprite::changeFrame()
{
	// RESET THE COUNTER
	animationCounter = 0;

	// REMEMBER, WE COUNT BY 2s
	frameIndex += 2;

	// GO BACK TO FIRST INDEX IF NECESSARY
	if (frameIndex == spriteType->getSequenceSize(currentState))
		frameIndex = 0;
}

/*
	getCurrentImageID - This method does the work of retrieving
	the image id that corresponds to this sprite's current state
	and frame index.
*/
unsigned int AnimatedSprite::getCurrentImageID()
{
	return spriteType->getAnimationFrameID(currentState, frameIndex);
}

/*
	setCurrentState - This method sets this sprite to the newState
	state and starts its animtion sequence from the beginning.
*/
void AnimatedSprite::setCurrentState(wstring newState) 
{
	// SET THE ANIMATINO STATE
	currentState = newState;

	// AND RESET OUR COUNTERS
	animationCounter = 0;
	frameIndex = 0;
}

/*
	updateSprite - To be called every frame of animation. This
    method advances the animation counter appropriately per
	the animation speed. It also updates the sprite location
	per the current velocity.
*/
void AnimatedSprite::updateSprite()
{
	unsigned int duration = spriteType->getDuration(currentState, frameIndex);
	animationCounter++;

	// WE ONLY CHANGE THE ANIMATION FRAME INDEX WHEN THE
	// ANIMATION COUNTER HAS REACHED THE DURATION
	if (animationCounter == duration)
		changeFrame();
}