#include "stdafx.h"
#include "src\game\Game.h"
#include "src\gsm\ai\EnemyBots\Defender.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gsm\physics\Physics.h"
#include "src\gsm\ai\Bullet.h"
//BM3
#include "src\gsm\ai\Bots.h"
#include "src\EarthDomainGame.h"
// bm4 add
#include <windows.h>
#include <xact3.h>
#include "src\game\XACT3Audio.h"

#include "src\PoseurSpriteTypeImporter.h";
/*
	This private constructor is only to be used for cloning bots, note
	that this does not setup the velocity for this bot.
*/
Defender::Defender(	unsigned int initMin, 
										unsigned int initMax, 
										unsigned int initMaxVelocity)
{
	// INIT THE BASIC STUFF
	initBot(initMaxVelocity);
}

/*
	This is the public constructor used by other classes for 
	creating these types of bots.
*/
Defender::Defender(	Game *game,
										Physics *physics,
										unsigned int initXPosition, 
										unsigned int initYPosition, 
										unsigned int initLevel)
{
	//Enemy 1
	AnimatedSpriteType *EnemyBot1;
	PoseurSpriteTypeImporter psti;
	b2PolygonShape rectangleShape;

	psti.loadSpriteTypes(game, SPRITE_TYPES_LIST);

	b2World *ourWorld = game->getOurWorld();
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	EnemyBot1 = spriteManager->getSpriteType(2);
	this->setSpriteType(EnemyBot1);
	this->setAlpha(255);
	this->setCurrentState(L"IDLE");
	PhysicalProperties *enemypp = this->getPhysicalProperties();

	unsigned int spriteTypeID;
	spriteTypeID = spriteManager->addSpriteType(EnemyBot1);
	EnemyBot1->setSpriteTypeID(spriteTypeID);

	enemypp->setVelocity(0,0);
	enemypp->setX(initXPosition);
	enemypp->setY(initYPosition);
	// i added this
	enemypp->setPlayerFlag(0);
	// updated this
	enemypp->setEnemyFlag(1);
	// bm4 add
	enemypp->setPlayerBulletFlag(0);
	enemypp->setEnemyBulletFlag(0);

	// i added this
	// create a body for the enemy
	// and associate it with the
	// enemy bot
	b2BodyDef enemyBodyDef;
	enemyBodyDef.type = b2_dynamicBody;
	// set the position of the body so that
	// it corresponds to the position of
	// the bot
	int enemyWidth = this->getSpriteType()->getTextureWidth();
	int enemyHeight = this->getSpriteType()->getTextureHeight();
	// enemyBodyDef.position.Set(playerProps->getX()/3.0f + playerWidth/2, playerProps->getY()/3.0f + playerHeight/2);
	enemyBodyDef.position.Set(enemypp->getX()/3.0f + enemyWidth/2, enemypp->getY()/3.0f + enemyHeight/2);
	enemyBodyDef.userData = (AnimatedSprite*)this;
	b2Body *enemyBody = ourWorld->CreateBody(&enemyBodyDef);

	// attach a fixture to the body to give it a
	// shape and density (and thus mass)
	/*rectangleShape;*/
	// if the conversion factor is 1 m = 3 pixels,
	// then the half-width of the rectangle
	// representing the bot's shape, in meters,
	// is the bot's width/3/2 = bot's width/6,
	// and likewise for the height
	rectangleShape.SetAsBox(enemyWidth/6.0f, enemyHeight/6.0f);
	b2FixtureDef enemyFixtureDef;
	enemyFixtureDef.shape = &rectangleShape;
	enemyFixtureDef.density = 1.0f;
	enemyBody->CreateFixture(&enemyFixtureDef);
	// set bot's body variable
	this->setBody(enemyBody);

	spriteManager->addBot(this);
	pickRandomVelocity();
	health=3;
	this->think(game);

}

/*
	clone - this method makes another RandomFloatingBot object, but does
	not completely initialize it with similar data to this. Most of the 
	object, like velocity and position, are left uninitialized.
*/
Bot* Defender::clone()
{
	Defender *botClone = new Defender(0,0,1);
	return botClone;
}

/*
	initBot - this initialization method sets up the basic bot
	properties, but does not setup its velocity.
*/
void Defender::initBot(	unsigned int initMin)
{
}

/*
	pickRandomVelocity - calculates a random velocity vector for this
	bot and initializes the appropriate instance variables.
*/
void Defender::pickRandomVelocity()
{
	
	int randomNumber = rand() % 150 + 40;
	cyclesRemainingBeforeThinking=randomNumber;
}

/*
	think - called once per frame, this is where the bot performs its
	decision-making. Note that we might not actually do any thinking each
	frame, depending on the value of cyclesRemainingBeforeThinking.
*/
void Defender::think(Game *game)
{
	GameStateManager *gsm = game->getGSM();
	SpriteManager *spriteManager = gsm->getSpriteManager();
	AnimatedSprite *player = spriteManager->getPlayer();
			
	if (cyclesRemainingBeforeThinking == 0){
			
		// finalBM
		
		Bullet *Bullet1 = new Bullet(game,game->getGSM()->getPhysics(),5,
				this->getPhysicalProperties()->getX()+10,
				this->getPhysicalProperties()->getY()+25,3,1.0);

		Bullet *Bullet2 = new Bullet(game,game->getGSM()->getPhysics(),5,
				this->getPhysicalProperties()->getX()+50,
				this->getPhysicalProperties()->getY()+25,3,1.0);
		
		Physics *physics = gsm->getPhysics();
		if(currentDirection==0){
			// scrolling add
			this->pp.setVelocitySafely(physics, 2 * sin(-1.0),-5.0f);
			currentDirection=1;
		}
		else{
			// scrolling add
			this->pp.setVelocitySafely(physics, 2 * sin(1.0),-5.0f);
			currentDirection=0;
		}
		pickRandomVelocity();
	}
	else{
			//scrolling add
			if(currentDirection==0)
			{
				this->pp.setVelocitySafely(game->getGSM()->getPhysics(),2 * sin(-1.0),-5.0f);
			}
			else
			{
				this->pp.setVelocitySafely(game->getGSM()->getPhysics(),2 * sin(1.0),-5.0f);
			}
			cyclesRemainingBeforeThinking--;
	}	
	if( cyclesRemainingBeforeThinking==450){
			this->setDestroyFlag(true);
		}
	//if the enemy health is zero
		if(health==0 && this->getCurrentState()!=(L"EXPLODE")){
		XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("hitting_target_cue");
		game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
		this->getPhysicalProperties()->setVelocity(0,-5);
		cyclesRemainingBeforeThinking=500;
		this->setCurrentState(L"EXPLODE");
		player->getPhysicalProperties()->setEnemyRemaining(player->getPhysicalProperties()->getEnemyRemaining() - 1);
		srand(time(NULL));
		int money = 10 + (rand() % 9); // random generate 10-19
		player->getPhysicalProperties()->setCurrency(player->getPhysicalProperties()->getCurrency() + money);
	}
	//if the enemy is hit
	else if (!this->isCurrentlyCollidable()){
		this->setCurrentlyCollidable(true);
		damage = player->getPhysicalProperties()->getAttackDamage();
		if(damage > health)
		{
			health = 0;
		}
		else
		{
			health = health - damage;
		}
	}

	if(this->getPhysicalProperties()->getX()<=0){
		this->getPhysicalProperties()->setX(1);
		currentDirection=1;
	}
	else if(this->getPhysicalProperties()->getX()>=game->getGSM()->getWorld()->getWorldWidth()-65){
		this->getPhysicalProperties()->setX(game->getGSM()->getWorld()->getWorldWidth()-64);
		currentDirection=0;
	}

	// bm3 box2d add
	// update associated body's position based on
	// bot's new position after having moved
	b2Body *defenderBody = this->getBody();
	int defenderWidth = this->getSpriteType()->getTextureWidth();
	int defenderHeight = this->getSpriteType()->getTextureHeight();
	defenderBody->SetTransform(b2Vec2(this->pp.getX()/3.0f + defenderWidth/2, this->pp.getY()/3.0f + defenderHeight/2), 0);
	this->setBody(defenderBody);
}
