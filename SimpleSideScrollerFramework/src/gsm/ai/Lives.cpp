#include "stdafx.h"
#include "src\game\Game.h"
#include "src\gsm\ai\Lives.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gsm\physics\Physics.h"
#include  "src\game\Game.h"

#include "src\PoseurSpriteTypeImporter.h";


/*
	This is the public constructor used by other classes for 
	creating these types of bots.
*/
Lives::Lives(Physics *physics, unsigned int initLife)
{
	hit=false;
	life=initLife;
	counter=0;
	// game over add
	gameOverCounter = 150;
}

Bot*Lives::clone()
{
	return NULL;
}
void Lives::think(Game *game)
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
	this->getPhysicalProperties()->setY(playerY);
	
	if (player->getPhysicalProperties()->getLives()==0){
		this->setCurrentState(L"ZERO");
	}
	else if(player->getPhysicalProperties()->getLives()==1){
		this->setCurrentState(L"ONE");
	}
	// game over add
	else if (player->getPhysicalProperties()->getLives()==2){
		this->setCurrentState(L"TWO");
	}
	// game over add
	else if (player->getPhysicalProperties()->getLives()<0)
	{
		// game over add
		if (gameOverCounter == 150)
		{
			GameStateManager *gsm = game->getGSM();
			gsm->goToGameOverScreen();
		}

		if (gameOverCounter > 0)
		{
			gameOverCounter--;
		}

		if (gameOverCounter == 0)
		{
				GameStateManager *gsm = game->getGSM();
				gsm->goToMainMenu();
		}
	}
}