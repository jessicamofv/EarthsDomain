#include "stdafx.h"
#include "Physics.h"
#include "src\game\Game.h"
#include "src\gsm\sprite\SpriteManager.h"
#include "src\gsm\state\GameStateManager.h"

/*
	Default constructor, it initializes all data using default values.
*/
Physics::Physics()
{
	maxVelocity = DEFAULT_MAX_VELOCITY;
	gravity = DEFAULT_GRAVITY;
}

/*
	Noting to destroy at the moment.
*/
Physics::~Physics()
{

}

void Physics::update(Game *game)
{
	// REMEMBER, AT THIS POINT, ALL PLAYER INPUT AND AI
	// HAVE ALREADY BEEN PROCESSED AND BOT AND PLAYER
	// STATES, VELOCITIES, AND ACCELERATIONS HAVE ALREADY
	// BEEN UPDATED. NOW WE HAVE TO PROCESS THE PHYSICS
	// OF ALL THESE OBJECTS INTERACTING WITH EACH OTHER
	// AND THE STATIC GAME WORLD. THIS MEANS WE NEED TO
	// DETECT AND RESOLVE COLLISIONS IN THE ORDER THAT
	// THEY WILL HAPPEN, AND WITH EACH COLLISION, EXECUTE
	// ANY GAMEPLAY RESPONSE CODE, UPDATE VELOCITIES, AND
	// IN THE END, UPDATE POSITIONS

	// FIRST, YOU SHOULD START BY ADDING ACCELERATION TO ALL 
	// VELOCITIES, WHICH INCLUDES GRAVITY, NOTE THE EXAMPLE
	// BELOW DOES NOT DO THAT


	// FOR NOW, WE'LL JUST ADD THE VELOCITIES TO THE
	// POSITIONS, WHICH MEANS WE'RE NOT APPLYING GRAVITY OR
	// ACCELERATION AND WE ARE NOT DOING ANY COLLISION 
	// DETECTION OR RESPONSE
	GameStateManager *gsm = game->getGSM();
	SpriteManager *sm = gsm->getSpriteManager();
	AnimatedSprite *player;
	PhysicalProperties *pp;

	// FIRST WE'LL MOVE THE PLAYER
	player = sm->getPlayer();
	pp = player->getPhysicalProperties();
	pp->setPosition(pp->getX() + pp->getVelocityX(), pp->getY() + pp->getVelocityY());

	// FOR NOW THE PLAYER IS DIRECTLY CONTROLLED BY THE KEYBOARD,
	// SO WE'LL NEED TO TURN OFF ANY VELOCITY APPLIED BY INPUT
	// SO THE NEXT FRAME IT DOESN'T GET ADDED
	pp->setVelocity(0.0f, 0.0f);

	// AND NOW MOVE ALL THE BOTS
	list<Bot*>::iterator botIterator = sm->getBotsIterator();
	while (botIterator != sm->getEndOfBotsIterator())
	{			
		Bot *bot = (*botIterator);
		pp = bot->getPhysicalProperties();
		pp->setPosition(pp->getX() + pp->getVelocityX(), pp->getY() + pp->getVelocityY());
		botIterator++;
	}
}