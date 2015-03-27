#include "stdafx.h"
#include "src\game\Game.h"
#include "src\gsm\ai\max_health.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gsm\physics\Physics.h"
#include  "src\game\Game.h"

#include "src\PoseurSpriteTypeImporter.h";


/*
	This is the public constructor used by other classes for 
	creating these types of bots.
*/
max_health::max_health(Physics *physics, unsigned int initLife)
{
	hit=false;
	life=initLife;
	counter=0;
	this->setCurrentState(L"FIVE");
}

Bot*max_health::clone()
{
	return NULL;
}
void max_health::think(Game *game)
{
	PhysicalProperties *pp = this->getPhysicalProperties();
	int width  = this->getBoundingVolume()->getWidth();
	int height = this->getBoundingVolume()->getHeight();
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	
	AnimatedSprite *player = spriteManager->getPlayer();
	PhysicalProperties *playerProps = player->getPhysicalProperties();
	int playerX = playerProps->getX();
	int playerY = playerProps->getY();
	this->getPhysicalProperties()->setX(playerX);
	this->getPhysicalProperties()->setY(playerY-20);

	if (player->getPhysicalProperties()->getMaxHealth()==10){
		this->setCurrentState(L"TEN");
	}
	else if(player->getPhysicalProperties()->getMaxHealth()==9){
		this->setCurrentState(L"NINE");
	}
	else if (player->getPhysicalProperties()->getMaxHealth()==8){
		this->setCurrentState(L"EIGHT");
	}
	else if (player->getPhysicalProperties()->getMaxHealth()==7){
		this->setCurrentState(L"SEVEN");
	}
	else if (player->getPhysicalProperties()->getMaxHealth()==6){
		this->setCurrentState(L"SIX");
	}
	else if (player->getPhysicalProperties()->getMaxHealth()==5){
		this->setCurrentState(L"FIVE");
	}
}