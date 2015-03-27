#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "stdafx.h"
#include "src\gsm\ai\Bot.h"
#include "src\gsm\physics\Physics.h"
#include "src\game\Game.h"

class Bullet : public Bot
{
private:

	unsigned int cyclesRemainingBeforeThinking;
	unsigned int minCyclesBeforeThinking;
	unsigned int maxCyclesBeforeThinking;
	unsigned int maxVelocity;
	unsigned int attack;
	unsigned int path;
	float dir;

	// bm3 AUDIO add
	stXACTAudio audioBanks_;
	IXACT3Engine* soundEngine_;

	// THIS PRIVATE CONSTRUCTOR IS ONLY USED FOR CLONING
	Bullet(	unsigned int initMin, 
						unsigned int initMax, 
						unsigned int initMaxVelocity);

public:
	Bullet(	Game *game,
					Physics *physics,
					unsigned int bulletType,
					unsigned int initMin, 
					unsigned int initMax,
					unsigned int pathType,
					float initMaxVelocity);
	~Bullet();
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