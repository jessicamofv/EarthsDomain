#include "stdafx.h"
#include "src\game\Game.h"
#include "src\gsm\ai\Bullet.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gsm\physics\Physics.h"
#include "src\gsm\physics\Physics.h"
#include "src\gsm\ai\Bots.h"
#include "src\EarthDomainGame.h"
// bm4 add
#include <Box2D/Box2D.h>

#include "src\PoseurSpriteTypeImporter.h";

/*
	This private constructor is only to be used for cloning bots, note
	that this does not setup the velocity for this bot.
*/
Bullet::Bullet(	unsigned int initMin, 
										unsigned int initMax, 
										unsigned int initMaxVelocity)
{
	// INIT THE BASIC STUFF
	initBot(initMin, initMax, initMaxVelocity);
}

/*
	This is the public constructor used by other classes for 
	creating these types of bots.
*/
Bullet::Bullet(Game *game,
										Physics *physics,
										unsigned int bulletType,
										unsigned int initXposition, 
										unsigned int initYposition,
										unsigned int pathType,
										float initDir)
{

	XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("shooting_cue");
	game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );

	Bullet *playerBullet_1;
	GameStateManager *gsm = game->getGSM();
	SpriteManager *spriteManager = gsm->getSpriteManager();
	PhysicalProperties *bulletpp_1;
	b2Body *playerBullet_1Body;
	AnimatedSpriteType *bullet_1;

	PoseurSpriteTypeImporter psti;
	psti.loadSpriteTypes(game, SPRITE_TYPES_LIST);

	bullet_1 = spriteManager->getSpriteType(bulletType);

	this->setSpriteType(bullet_1);
				this->setAlpha(255);
				this->setCurrentState(L"IDLE");
				// CHANGED THIS
				bulletpp_1 = this->getPhysicalProperties();
	
				unsigned int spriteTypeID = spriteManager->addSpriteType(bullet_1);
				bullet_1->setSpriteTypeID(spriteTypeID);

				bulletpp_1->setX(initXposition);
				bulletpp_1->setY(initYposition);
				bulletpp_1->setVelocity(0.0f, 4.0f*initDir);
				bulletpp_1->setAccelerationX(0);
				bulletpp_1->setAccelerationY(0);
				bulletpp_1->setPlayerFlag(0);
				// updated this
				bulletpp_1->setEnemyFlag(0);
				// bm4 add
				// is it a player bullet?
				if (bulletType == 4)
				{
					bulletpp_1->setPlayerBulletFlag(1);
					bulletpp_1->setEnemyBulletFlag(0);
				}
				// if not, it's an enemy bullet
				else
				{
					bulletpp_1->setPlayerBulletFlag(0);
					bulletpp_1->setEnemyBulletFlag(1);
				}
				this->setCurrentState(L"IDLE");
				this->setAlpha(255);

				// bm3 box2d add
				// create a body for the bullet
				// and associate it with the
				// bullet bot
				b2BodyDef playerBullet_1BodyDef;
				playerBullet_1BodyDef.type = b2_dynamicBody;
				// set the position of the body so that
				// it corresponds to the position of
				// the bot
				int bullet1Width = this->getSpriteType()->getTextureWidth();
				int bullet1Height = this->getSpriteType()->getTextureHeight();
				playerBullet_1BodyDef.position.Set(bulletpp_1->getX()/3.0f + bullet1Width/2, bulletpp_1->getY()/3.0f + bullet1Height/2);
				playerBullet_1BodyDef.userData = (AnimatedSprite*)this;

				// make the bullet a box2d "bullet body"
				playerBullet_1BodyDef.bullet = true;

				b2World *ourWorld = game->getOurWorld();
				// final bm add
				playerBullet_1Body = ourWorld->CreateBody(&playerBullet_1BodyDef);

				// attach a fixture to the body to give it a
				// shape and density (and thus mass)
				b2PolygonShape rectangleShape;
				// if the conversion factor is 1 m = 3 pixels
				// then the half-width of the rectangle
				// representing the bullet's shape, in meters,
				// is the bullets's width/3/2 = bullet's width/6,
				// and likewise for the height
				rectangleShape.SetAsBox(bullet1Width/6.0f, bullet1Height/6.0f);
				b2FixtureDef playerBullet_1FixtureDef;
				playerBullet_1FixtureDef.shape = &rectangleShape;
				playerBullet_1FixtureDef.density = 1.0f;
				playerBullet_1Body->CreateFixture(&playerBullet_1FixtureDef);
				// set bullet's body variable
				this->setBody(playerBullet_1Body);

				spriteManager->addBot(this);

				path=pathType;
				dir=initDir;
				this->think(game);
				cyclesRemainingBeforeThinking=100;
				/*
	// INIT THE BASIC STUFF
	initBot(initMin, initMax, initMaxVelocity);
	// AND START THE BOT OFF IN A RANDOM DIRECTION AND VELOCITY
	// AND WITH RANDOM INTERVAL UNTIL IT THINKS AGAIN
	pickRandomVelocity(physics);
	pickRandomCyclesInRange();
	*/
}

/*
	clone - this method makes another RandomFloatingBot object, but does
	not completely initialize it with similar data to this. Most of the 
	object, like velocity and position, are left uninitialized.
*/
Bot* Bullet::clone()
{
	Bullet *botClone = new Bullet(	minCyclesBeforeThinking, 
															maxCyclesBeforeThinking, 
															maxVelocity);
	return botClone;
}

/*
	initBot - this initialization method sets up the basic bot
	properties, but does not setup its velocity.
*/
void  Bullet::initBot(	unsigned int initMin,
									unsigned int initMax,
									unsigned int initMaxVelocity)
{

	// IF THE MAX IS SMALLER THAN THE MIN, SWITCH THEM
	if (initMax < initMin)
	{
		unsigned int temp = initMax;
		initMax = initMin;
		initMin = temp;
	}
	// IF THEY ARE THE SAME, ADD 100 CYCLES TO THE MAX
	else if (initMax == initMin)
		initMax += 100;

	// INIT OUR RANGE VARIABLES
	minCyclesBeforeThinking = initMin;
	maxCyclesBeforeThinking = initMax;

	// AND OUR VELOCITY CAPPER
	maxVelocity = initMaxVelocity;
}

/*
	pickRandomCyclesInRange - a randomized method for determining when this bot
	will think again. This method sets that value.
*/
void Bullet::pickRandomCyclesInRange()
{
	cyclesRemainingBeforeThinking = maxCyclesBeforeThinking - minCyclesBeforeThinking + 1;
	cyclesRemainingBeforeThinking = rand() % cyclesRemainingBeforeThinking;
	cyclesRemainingBeforeThinking += minCyclesBeforeThinking;
}

/*
	pickRandomVelocity - calculates a random velocity vector for this
	bot and initializes the appropriate instance variables.
*/
void Bullet::pickRandomVelocity(Physics *physics)
{
	// FIRST GET A RANDOM float FROM 0.0 TO 1.0
	float randomAngleInRadians = ((float)rand())/((float)RAND_MAX);

	// NOW SCALE IT FROM 0 TO 2 PI
	randomAngleInRadians *= 2.0f;
	randomAngleInRadians *= PI;

	// NOW WE CAN SCALE OUR X AND Y VELOCITIES
	this->pp.setVelocitySafely(physics, maxVelocity * sin(randomAngleInRadians), maxVelocity * cos(randomAngleInRadians));
}

/*
	think - called once per frame, this is where the bot performs its
	decision-making. Note that we might not actually do any thinking each
	frame, depending on the value of cyclesRemainingBeforeThinking.
*/
void Bullet::think(Game *game)
{
	if (path==1){
		this->pp.setVelocitySafely(game->getGSM()->getPhysics(),0,4*dir);
		
	}
	else if (path>=2){
		if (path==2){
			this->pp.setVelocitySafely(game->getGSM()->getPhysics(),sin(0.5*(double)cyclesRemainingBeforeThinking),cos(0.5*(double)cyclesRemainingBeforeThinking));
			//this->pp.setVelocitySafely(game->getGSM()->getPhysics(),2*sin((double)cyclesRemainingBeforeThinking),3);
		}
		else if (path==3){
			this->pp.setVelocitySafely(game->getGSM()->getPhysics(),10*sin(0.5*(double)cyclesRemainingBeforeThinking),4);
		}
	if (cyclesRemainingBeforeThinking == -100){
	}
	else{
		cyclesRemainingBeforeThinking--;}
	}
	// bm3 box2d add
	// update associated body's position based
	// on bot's new position after it has
	// moved for this frame
	b2Body *bulletBody = this->getBody();
	int bulletWidth = this->getSpriteType()->getTextureWidth();
	int bulletHeight = this->getSpriteType()->getTextureHeight();
	bulletBody->SetTransform(b2Vec2(this->pp.getX()/3.0f+30, this->pp.getY()/3.0f + 30), 0);
	this->setBody(bulletBody);

	// remove bullets if they go offscreen
	Viewport *viewport = game->getGUI()->getViewport();
	
	// if they go below the bottom edge of
	// the viewport (the enemy bullets)
	if (this->getPhysicalProperties()->getY() > (viewport->getViewportY() + viewport->getViewportHeight()))
	{
		this->setDestroyFlag(1);
	}

	// or if they go above the top edge of
	// the viewport (the player bullets)
	if (this->getPhysicalProperties()->getY() < viewport->getViewportY())
	{
		this->setDestroyFlag(1);
	}
}