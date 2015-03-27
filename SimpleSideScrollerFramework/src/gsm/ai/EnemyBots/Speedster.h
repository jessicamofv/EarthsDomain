#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "stdafx.h"
#include "src\gsm\ai\Bot.h"
#include "src\gsm\physics\Physics.h"
#include "src\game\Game.h"
// final bm add
#include "src\gsm\ai\Bullet.h"
// CHANGED THIS
#include "src\PoseurSpriteTypeImporter.h";

class Speedster : public Bot
{
private:
	unsigned int xPosition;
	unsigned int yPosition;
	unsigned int level;

	unsigned int cyclesRemainingBeforeThinking;
	unsigned int maxVelocity;
	unsigned int health;		//BM4
	unsigned int damage;
	unsigned int speed;
	unsigned int collisionDamage;

	// final bm add
	Bullet *enemyBullet_1;
	Bullet *enemyBullet_2;
	b2Body *enemyBullet_1Body;
	b2Body *enemyBullet_2Body;
	// CHANGED THIS
	PhysicalProperties *bulletpp_1;
	PhysicalProperties *bulletpp_2;

	// THIS PRIVATE CONSTRUCTOR IS ONLY USED FOR CLONING
	Speedster(	unsigned int initMin, 
						unsigned int initMax, 
						unsigned int initMaxVelocity);

public:
	Speedster(	Game *game,
						Physics *physics,
						unsigned int initXPosition, 
						unsigned int initYPosition,
						unsigned int initLevel);
	~Speedster();
	Bot*	clone();
	void initBot(	unsigned int initMaxVelocity);
	void	pickRandomVelocity();
	void	think(Game *game);

	// INLINED METHODS
	unsigned int getCyclesRemainingBeforeThinking()	{ return cyclesRemainingBeforeThinking; }
};