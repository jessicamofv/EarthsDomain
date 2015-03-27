#include "stdafx.h"
#include "src\game\Game.h"
#include "src\gsm\ai\health.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gsm\physics\Physics.h"
#include  "src\game\Game.h"

#include "src\PoseurSpriteTypeImporter.h";

/*
	This is the public constructor used by other classes for 
	creating these types of bots.
*/
health::health(Physics *physics, unsigned int initLife)
{
	life=initLife;
	counter=0;
}

Bot*health::clone()
{
	return NULL;
}
void health::think(Game *game)
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

	int worldWidth = game->getGSM()->getWorld()->getWorldHeight();
	
	if(counter<=0){
		player->setCurrentlyCollidable(true);
		player->setCurrentState(L"IDLE");
		counter=66;

	}
	else{
		if(!player->isCurrentlyCollidable()&& (player->getCurrentState()!=(L"HIT"))){
			player->setCurrentState(L"HIT");
			counter=66;
			player->getPhysicalProperties()->setCurrentHealth(player->getPhysicalProperties()->getcurrentHealth()-1);
		}
		else
			counter--;
	}
		
			if (player->getPhysicalProperties()->getcurrentHealth()==10){
				this->setCurrentState(L"TEN");
			}
			else if(player->getPhysicalProperties()->getcurrentHealth()==9){
				this->setCurrentState(L"NINE");
			}
			else if (player->getPhysicalProperties()->getcurrentHealth()==8){
				this->setCurrentState(L"EIGHT");
			}
			else if (player->getPhysicalProperties()->getcurrentHealth()==7){
				this->setCurrentState(L"SEVEN");
			}
			else if (player->getPhysicalProperties()->getcurrentHealth()==6){
				this->setCurrentState(L"SIX");
			}
			else if (player->getPhysicalProperties()->getcurrentHealth()==5){
				this->setCurrentState(L"FIVE");
			}
			else if (player->getPhysicalProperties()->getcurrentHealth()==4){
				this->setCurrentState(L"FOUR");
			}
			else if (player->getPhysicalProperties()->getcurrentHealth()==3){
				this->setCurrentState(L"THREE");
			}
			else if (player->getPhysicalProperties()->getcurrentHealth()==2){
				this->setCurrentState(L"TWO");
			}
			else if (player->getPhysicalProperties()->getcurrentHealth()==1){
				this->setCurrentState(L"ONE");
			}
			else{
				player->getPhysicalProperties()->decLives();
				// game over add
				if (player->getPhysicalProperties()->getLives() >= 0)
				{
					player->getPhysicalProperties()->setCurrentHealth(player->getPhysicalProperties()->getMaxHealth());
				}
			}
}