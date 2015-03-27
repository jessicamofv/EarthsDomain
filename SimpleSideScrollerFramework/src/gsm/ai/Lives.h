#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "stdafx.h"
#include "src\gsm\ai\Bot.h"
#include "src\gsm\physics\Physics.h"
#include "src\game\Game.h"

class Lives : public Bot
{
private:
	unsigned int life;
	boolean hit;
	int hitCount;
	int counter;
	// game over add
	int gameOverCounter;

public:
	Lives(Physics *physics, unsigned int initLife);
	Bot*	clone();
	~Lives();
	void initLifeBar(unsigned int initLife);
	void	think(Game *game);

	// INLINED METHODS
	

};
