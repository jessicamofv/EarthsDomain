#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "stdafx.h"
#include "src\gsm\ai\Bot.h"
#include "src\gsm\physics\Physics.h"
#include "src\game\Game.h"

class Bots : public Bot
{
private:
	unsigned int cyclesRemainingBeforeThinking;
	unsigned int minCyclesBeforeThinking;
	unsigned int maxCyclesBeforeThinking;
	unsigned int maxVelocity;

	// THIS PRIVATE CONSTRUCTOR IS ONLY USED FOR CLONING
	Bots(	unsigned int initMin, 
						unsigned int initMax, 
						unsigned int initMaxVelocity);

public:
	Bots(	Physics *physics,
						unsigned int initMin, 
						unsigned int initMax, 
						unsigned int initMaxVelocity);
	~Bots();
	Bot*	clone();
	void initBot(	unsigned int initMin,
					unsigned int initMax,
					unsigned int initMaxVelocity);
	void	pickRandomCyclesInRange();
	void	pickRandomVelocity(Physics *physics);
	void	think(Game *game);

	// INLINED METHODS
	unsigned int getCyclesRemainingBeforeThinking()	{ return cyclesRemainingBeforeThinking; }
	unsigned int getMinCyclesBeforeThinking()		{ return minCyclesBeforeThinking;		}
	unsigned int getMaxCyclesBeforeThinking()		{ return maxCyclesBeforeThinking;		}
};