#include "stdafx.h"
#include "src\game\Game.h"
#include "src\gsm\ai\Bots.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gsm\physics\Physics.h"

/*
	This private constructor is only to be used for cloning bots, note
	that this does not setup the velocity for this bot.
*/
Bots::Bots(	unsigned int initMin, 
										unsigned int initMax, 
										unsigned int initMaxVelocity)
{
	// INIT THE BASIC STUFF
	initBot(initMin, initMax, initMaxVelocity);
}

/*
	This is the public constructor used by other classes for 
	creating these types of bots.
*/
Bots::Bots(	Physics *physics,
										unsigned int initMin, 
										unsigned int initMax, 
										unsigned int initMaxVelocity)
{
	// INIT THE BASIC STUFF
	initBot(initMin, initMax, initMaxVelocity);

	// AND START THE BOT OFF IN A RANDOM DIRECTION AND VELOCITY
	// AND WITH RANDOM INTERVAL UNTIL IT THINKS AGAIN
	srand((unsigned int)time(0));
	pickRandomVelocity(physics);
	pickRandomCyclesInRange();
}

/*
	clone - this method makes another Bots object, but does
	not completely initialize it with similar data to this. Most of the 
	object, like velocity and position, are left uninitialized.
*/
Bot* Bots::clone()
{
	Bots *botClone = new Bots(	minCyclesBeforeThinking, 
															maxCyclesBeforeThinking, 
															maxVelocity);
	return botClone;
}

/*
	initBot - this initialization method sets up the basic bot
	properties, but does not setup its velocity.
*/
void Bots::initBot(	unsigned int initMin,
									unsigned int initMax,
									unsigned int initMaxVelocity)
{
	// IF THE MAX IS SMALLER THAN THE MIN, SWITCH THEM
	if (initMax < initMin)
	{
		unsigned int temp = initMax;
		initMax = initMin;
		initMin = temp;
	}
	// IF THEY ARE THE SAME, ADD 100 CYCLES TO THE MAX
	else if (initMax == initMin)
		initMax += 100;

	// INIT OUR RANGE VARIABLES
	minCyclesBeforeThinking = initMin;
	maxCyclesBeforeThinking = initMax;

	// AND OUR VELOCITY CAPPER
	maxVelocity = initMaxVelocity;
}

/*
	pickRandomCyclesInRange - a randomized method for determining when this bot
	will think again. This method sets that value.
*/
void Bots::pickRandomCyclesInRange()
{
	cyclesRemainingBeforeThinking = maxCyclesBeforeThinking - minCyclesBeforeThinking + 1;
	cyclesRemainingBeforeThinking = rand() % cyclesRemainingBeforeThinking;
	cyclesRemainingBeforeThinking += minCyclesBeforeThinking;
}

/*
	pickRandomVelocity - calculates a random velocity vector for this
	bot and initializes the appropriate instance variables.
*/
void Bots::pickRandomVelocity(Physics *physics)
{
	

	// NOW WE CAN SCALE OUR X AND Y VELOCITIES
	this->pp.setVelocitySafely(physics, 0, 0);
}

/*
	think - called once per frame, this is where the bot performs its
	decision-making. Note that we might not actually do any thinking each
	frame, depending on the value of cyclesRemainingBeforeThinking.
*/
void Bots::think(Game *game)
{
	// EACH FRAME WE'LL TEST THIS BOT TO SEE IF WE NEED
	// TO PICK A DIFFERENT DIRECTION TO FLOAT IN

	if (cyclesRemainingBeforeThinking == 0)
	{
		GameStateManager *gsm = game->getGSM();
		pickRandomVelocity(gsm->getPhysics());
		pickRandomCyclesInRange();
	}
	else
		cyclesRemainingBeforeThinking--;
}