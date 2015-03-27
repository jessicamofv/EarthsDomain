#include "stdafx.h"
#include "src\game\Game.h"
#include "src\gsm\ai\EnemyBots\Bosses\FirstBossCenter.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gsm\physics\Physics.h"
#include "src\EarthDomainGame.h"
// final add
#include <windows.h>
#include <xact3.h>
#include "src\game\XACT3Audio.h"

#include "src\PoseurSpriteTypeImporter.h";
/*
	This private constructor is only to be used for cloning bots, note
	that this does not setup the velocity for this bot.
*/
FirstBossCenter::FirstBossCenter(	unsigned int initMin, 
										unsigned int initMax, 
										unsigned int initMaxVelocity)
{

}

/*
	This is the public constructor used by other classes for 
	creating these types of bots.
*/
FirstBossCenter::FirstBossCenter(	Game *game,
										Physics *physics,
										unsigned int initXPosition, 
										unsigned int initYPosition, 
										unsigned int initLevel)
{
	AnimatedSpriteType *BossBot1;
	PoseurSpriteTypeImporter psti;
	b2PolygonShape rectangleShape;

	psti.loadSpriteTypes(game, SPRITE_TYPES_LIST);
	
	b2World *ourWorld = game->getOurWorld();
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	BossBot1 = spriteManager->getSpriteType(9);
	this->setSpriteType(BossBot1);
	this->setAlpha(255);
	this->setCurrentState(L"IDLE");
	PhysicalProperties *bosspp = this->getPhysicalProperties();
	
	unsigned int spriteTypeID;
	spriteTypeID = spriteManager->addSpriteType(BossBot1);
	BossBot1->setSpriteTypeID(spriteTypeID);

	// scrolling add
	bosspp->setVelocity(0,-5.0f);
	bosspp->setX(initXPosition);
	bosspp->setY(initYPosition);
	// i added this
	bosspp->setPlayerFlag(0);
	// updated this
	bosspp->setEnemyFlag(1);
	// bm4 add
	bosspp->setPlayerBulletFlag(0);
	bosspp->setEnemyBulletFlag(0);

	// i added this
	// create a body for the enemy
	// and associate it with the
	// enemy bot
	b2BodyDef bossBodyDef;
	bossBodyDef.type = b2_dynamicBody;
	// set the position of the body so that
	// it corresponds to the position of
	// the bot
	int bossWidth = this->getSpriteType()->getTextureWidth();
	int bossHeight = this->getSpriteType()->getTextureHeight();
	// enemyBodyDef.position.Set(playerProps->getX()/3.0f + playerWidth/2, playerProps->getY()/3.0f + playerHeight/2);
	bossBodyDef.position.Set(bosspp->getX()/3.0f + bossWidth/2, bosspp->getY()/3.0f + bossHeight/2);
	bossBodyDef.userData = (AnimatedSprite*)this;
	b2Body *bossBody = ourWorld->CreateBody(&bossBodyDef);

	// attach a fixture to the body to give it a
	// shape and density (and thus mass)
	/*rectangleShape;*/
	// if the conversion factor is 1 m = 3 pixels,
	// then the half-width of the rectangle
	// representing the bot's shape, in meters,
	// is the bot's width/3/2 = bot's width/6,
	// and likewise for the height
	rectangleShape.SetAsBox(bossWidth/6.0f, bossHeight/6.0f);
	b2FixtureDef bossFixtureDef;
	bossFixtureDef.shape = &rectangleShape;
	bossFixtureDef.density = 1.0f;
	bossBody->CreateFixture(&bossFixtureDef);
	// set bot's body variable
	this->setBody(bossBody);

	spriteManager->addBot(this);
	health=15;
	cyclesRemainingBeforeThinking=280;
	this->think(game);
}

/*
	clone - this method makes another RandomFloatingBot object, but does
	not completely initialize it with similar data to this. Most of the 
	object, like velocity and position, are left uninitialized.
*/
Bot* FirstBossCenter::clone()
{
	return NULL;
}

/*
	initBot - this initialization method sets up the basic bot
	properties, but does not setup its velocity.
*/
void FirstBossCenter::initBot(			unsigned int initMaxVelocity)
{
}


/*
	pickRandomVelocity - calculates a random velocity vector for this
	bot and initializes the appropriate instance variables.
*/
void FirstBossCenter::pickRandomVelocity()
{
	}

/*
	think - called once per frame, this is where the bot performs its
	decision-making. Note that we might not actually do any thinking each
	frame, depending on the value of cyclesRemainingBeforeThinking.
*/
void FirstBossCenter::think(Game *game)
{
	GameStateManager *gsm = game->getGSM();
	SpriteManager *spriteManager = gsm->getSpriteManager();
	AnimatedSprite *player = spriteManager->getPlayer();

	
	
	if (cyclesRemainingBeforeThinking == 0){
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
		cyclesRemainingBeforeThinking=280;
	}
	else{
			if ( cyclesRemainingBeforeThinking==140){
				Bullet *Bullet1 = new Bullet(game,game->getGSM()->getPhysics(),12,
				this->getPhysicalProperties()->getX()+20,
				this->getPhysicalProperties()->getY()+250,5,currentDirection);
			}
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
		this->getPhysicalProperties()->setVelocity(0,-5);
		cyclesRemainingBeforeThinking=500;
		this->setCurrentState(L"EXPLODE");
		player->getPhysicalProperties()->setEnemyRemaining(player->getPhysicalProperties()->getEnemyRemaining() - 1);
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

	// bm3 box2d add
	// update associated body's position based on
	// bot's new position after having moved
	b2Body *bossCenterBody = this->getBody();
	int bossCenterWidth = this->getSpriteType()->getTextureWidth();
	int bossCenterHeight = this->getSpriteType()->getTextureHeight();
	bossCenterBody->SetTransform(b2Vec2(this->pp.getX()/3.0f + bossCenterWidth/3 + 20, this->pp.getY()/3.0f + bossCenterHeight/5+15), 0);
	this->setBody(bossCenterBody);
}
