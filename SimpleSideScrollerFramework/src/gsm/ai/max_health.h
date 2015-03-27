#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "stdafx.h"
#include "src\gsm\ai\Bot.h"
#include "src\gsm\physics\Physics.h"
#include "src\game\Game.h"

class max_health : public Bot
{
private:
	unsigned int life;
	boolean hit;
	int hitCount;
	int counter;

public:
	max_health(Physics *physics, unsigned int initLife);
	Bot*	clone();
	~max_health();
	void initHealthBar(unsigned int initLife);
	void	think(Game *game);

	// INLINED METHODS
	

};
