/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.cpp

	See SpriteManager.h for a class description.
*/

#pragma once
#include "stdafx.h"
#include "src\gsm\ai\Bot.h"
#include "src\gsm\physics\PhysicalProperties.h"
#include "src\graphics\GameGraphics.h"
#include "src\gsm\sprite\AnimatedSprite.h"
#include "src\gsm\sprite\AnimatedSpriteType.h"
#include "src\gsm\sprite\SpriteManager.h"
#include "src\gsm\state\GameStateManager.h"
// text add
#include "src\text\TextGenerator.h"

// bm4 add
SpriteManager::SpriteManager()
{
	// for dealing with contacts
	contactListener = new GameContactListener();
}

SpriteManager::~SpriteManager()
{
	delete contactListener;
}

/*
	addSpriteToRenderList - This method checks to see if the sprite
	parameter is inside the viewport. If it is, a RenderItem is generated
	for that sprite and it is added to the render list.
*/
void SpriteManager::addSpriteToRenderList(AnimatedSprite *sprite,
										  RenderList *renderList,
										  Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();
	PhysicalProperties *pp = sprite->getPhysicalProperties();

	// IS THE SPRITE VIEWABLE?
	if (viewport->areWorldCoordinatesInViewport(	
									pp->getX(),
									pp->getY(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight()))
	{
		// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
		RenderItem itemToAdd;
		itemToAdd.id = sprite->getFrameIndex();
		renderList->addRenderItem(	sprite->getCurrentImageID(),
									pp->round(pp->getX()-viewport->getViewportX()),
									pp->round(pp->getY()-viewport->getViewportY()),
									pp->round(pp->getZ()),
									sprite->getAlpha(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight());
	}
}

/*
	addSpriteItemsToRenderList - This method goes through all of the sprites,
	including the player sprite, and adds the visible ones to the render list.
	This method should be called each frame.
*/
void SpriteManager::addSpriteItemsToRenderList(	Game *game)
{
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{
		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&player, renderList, viewport);

		// NOW ADD THE REST OF THE SPRITES
		list<Bot*>::iterator botIterator;
		botIterator = bots.begin();
		while (botIterator != bots.end())
		{			
			Bot *bot = (*botIterator);
			addSpriteToRenderList(bot, renderList, viewport);
			botIterator++;
		}
	}
}

/*
	addSprite - This method is for adding a new sprite to 
	this sprite manager. Once a sprite is added it can be 
	scheduled for rendering.
*/
void SpriteManager::addBot(Bot *botToAdd)
{
	bots.push_back(botToAdd);
}

/*
	addSpriteType - This method is for adding a new sprite
	type. Note that one sprite type can have many sprites. For
	example, we may say that there may be a "Bunny" type of
	sprite, and specify properties for that type. Then there might
	be 100 different Bunnies each with their own properties, but that
	share many things in common according to what is defined in
	the shared sprite type object.
*/
unsigned int SpriteManager::addSpriteType(AnimatedSpriteType *spriteTypeToAdd)
{
	spriteTypes.push_back(spriteTypeToAdd);
	return spriteTypes.size()-1;
}

/*
	clearSprites - This empties all of the sprites and sprite types.
*/
void SpriteManager::clearSprites()
{
	spriteTypes.clear();
	bots.clear();
}

/*
	getSpriteType - This gets the sprite type object that corresponds
	to the index argument.
*/
AnimatedSpriteType* SpriteManager::getSpriteType(unsigned int typeIndex)
{
	if (typeIndex < spriteTypes.size())
		return spriteTypes.at(typeIndex);
	else
		return NULL;
}

/*
	unloadSprites - This method removes all artwork from memory that
	has been allocated for game sprites.
*/
void SpriteManager::unloadSprites()
{

	// @TODO
}

Bot* SpriteManager::removeBot(Bot *botToRemove)
{
	return NULL;
	// @TODO
}

/*
	update - This method should be called once per frame. It
	goes through all of the sprites, including the player, and calls their
	update method such that they may update themselves.
*/
void SpriteManager::update(Game *game)
{
	// text add
	TextGenerator *tg = game->getText()->getTextGenerator();
	tg->updateText(game);

	// UPDATE THE PLAYER SPRITE
	player.updateSprite();

	// NOW UPDATE THE REST OF THE SPRITES
	list<Bot*>::iterator botIterator;
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		bot->updateSprite();
		bot->think(game);
		botIterator++;
	}

	// bm4 add
	b2World *ourWorld = game->getOurWorld();
	ourWorld->SetContactListener(contactListener);

	// for the simulation
	float32 timeStep = 1.0f / 60.f;
	int32 velocityIterations = 10;
	int32 positionIterations = 8;

	ourWorld->Step(timeStep, velocityIterations, positionIterations);

	list<ContactInfo>::iterator contactToCheck;
	for (contactToCheck = contactListener->contacts.begin(); contactToCheck != contactListener->contacts.end(); 
		++contactToCheck) {
		ContactInfo contact = *contactToCheck;

		b2Fixture *fixtureA = contact.fixtureA;
		b2Body *bodyA = fixtureA->GetBody();
		AnimatedSprite *spriteA = (AnimatedSprite*)bodyA->GetUserData();

		b2Fixture *fixtureB = contact.fixtureB;
		b2Body *bodyB = fixtureB->GetBody();
		AnimatedSprite *spriteB = (AnimatedSprite*)bodyB->GetUserData();

		Physics *physics = game->getGSM()->getPhysics();
		
		// CHANGED THIS
		// updated this
		if (spriteA->getPhysicalProperties()->getPlayerFlag() == 1 
			&& spriteB->getPhysicalProperties()->getEnemyFlag() == 1)
		{
			// bm3 AUDIO add
			// have colliding sound play when player
			// collides with enemy
			// CHANGED THIS
			XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("colliding_cue");
			game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
			// have player bounce off enemy
			/*
			float playerNewVelX = -20 * player.getPhysicalProperties()->getVelocityX();
			float playerNewVelY = -20 * player.getPhysicalProperties()->getVelocityY();
			player.getPhysicalProperties()->setVelocitySafely(physics, playerNewVelX, playerNewVelY);
			*/
			// final add
			float velocityX = spriteA->getPhysicalProperties()->getVelocityX();
			float velocityY = spriteA->getPhysicalProperties()->getVelocityY();
			/*bodyA->ApplyLinearImpulse(b2Vec2(-10 * velocityX, 10 * velocityY), bodyA->GetWorldCenter());*/
			if (velocityY < 0)
			{
				spriteA->getPhysicalProperties()->setPosition(spriteA->getPhysicalProperties()->getX(), bodyA->GetPosition().y * 3);
			}
			else if (velocityY > 0)
			{
				spriteA->getPhysicalProperties()->setPosition(spriteA->getPhysicalProperties()->getX(), bodyA->GetPosition().y * -3);
			}
			/*
			else
			{
				if (velocityX < 0)
				{
					spriteA->getPhysicalProperties()->setPosition(bodyA->GetPosition().x * 3, spriteA->getPhysicalProperties()->getY());
				}
				else if (velocityX > 0)
				{
					spriteA->getPhysicalProperties()->setPosition(bodyA->GetPosition().x * -3, spriteA->getPhysicalProperties()->getY());
				}
			}
			*/

			// MessageBoxA(NULL, "Player has collided with enemy!", "Collision Test", 0);
		}
		// CHANGED THIS
		// updated this
		else if (spriteB->getPhysicalProperties()->getPlayerFlag() == 1 
			&& spriteA->getPhysicalProperties()->getEnemyFlag() == 1)
		{
			// bm3 AUDIO add
			// have colliding sound play when player
			// collides with enemy
			// CHANGED THIS
			XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("colliding_cue");
			game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
			// have player bounce off enemy
			/*
			float playerNewVelX = -20 * player.getPhysicalProperties()->getVelocityX();
			float playerNewVelY = -20 * player.getPhysicalProperties()->getVelocityY();
			player.getPhysicalProperties()->setVelocitySafely(physics, playerNewVelX, playerNewVelY);
			*/
			// final add
			float velocityX = spriteB->getPhysicalProperties()->getVelocityX();
			float velocityY = spriteB->getPhysicalProperties()->getVelocityY();
			/*bodyB->ApplyLinearImpulse(b2Vec2(-10 * velocityX, 10 * velocityY), bodyB->GetWorldCenter());*/
			if (velocityY < 0)
			{
				spriteB->getPhysicalProperties()->setPosition(spriteB->getPhysicalProperties()->getX(), bodyB->GetPosition().y * 3);
			}
			else if (velocityY > 0)
			{
				spriteB->getPhysicalProperties()->setPosition(spriteB->getPhysicalProperties()->getX(), bodyB->GetPosition().y * -3);
			}
			/*
			else
			{
				if (velocityX < 0)
				{
					spriteB->getPhysicalProperties()->setPosition(bodyB->GetPosition().x * 3, spriteB->getPhysicalProperties()->getY());
				}
				else if (velocityX > 0)
				{
					spriteB->getPhysicalProperties()->setPosition(bodyB->GetPosition().x * -3, spriteB->getPhysicalProperties()->getY());
				}
			}
			*/

			// MessageBoxA(NULL, "Player has collided with enemy!", "Collision Test", 0);
		}

		// final bm add
		/*
		if (spriteA->getPhysicalProperties()->getEnemyBulletFlag() == 1
			&& spriteB->getPhysicalProperties()->getPlayerFlag() == 1)
		{
			
			player.setAlpha(0);
		}

		if (spriteB->getPhysicalProperties()->getEnemyBulletFlag() == 1
			&& spriteA->getPhysicalProperties()->getPlayerFlag() == 1)
		{
			player.setAlpha(0);
		}
		*/

		// final bm add
		// updated this
		if (spriteA->getPhysicalProperties()->getEnemyBulletFlag() == 1 
			&& spriteB->getPhysicalProperties()->getPlayerFlag() == 1) 
		{
			// get rid of bullet
			spriteA->setDestroyFlag(1);
			// CHANGED THIS
			player.setCurrentlyCollidable(false);
			
		}
		// updated this
		else if (spriteB->getPhysicalProperties()->getEnemyBulletFlag() == 1 
			&& spriteA->getPhysicalProperties()->getPlayerFlag() == 1)
		{
			// get rid of bullet
			spriteB->setDestroyFlag(1);
			// CHANGED THIS
			player.setCurrentlyCollidable(false);

		}

		// updated this
		if (spriteA->getPhysicalProperties()->getEnemyFlag() == 1
			&& spriteB->getPhysicalProperties()->getPlayerBulletFlag() == 1)
		{
			// 5-7
			// spriteA->setAlpha(0);
			// get rid of bullet
			spriteB->setDestroyFlag(1);
			// get rid of enemy (temporary)
			//spriteA->setDestroyFlag(1);
			//player.getPhysicalProperties()->setEnemyRemaining(player.getPhysicalProperties()->getEnemyRemaining() - 1);
			spriteA->setCurrentlyCollidable(false);
			
		}
		// updated this
		else if (spriteB->getPhysicalProperties()->getEnemyFlag() == 1
			&& spriteA->getPhysicalProperties()->getPlayerBulletFlag() == 1)
		{
			// 5-7
			// spriteB->setAlpha(0);
			// get rid of bullet
			spriteA->setDestroyFlag(1);
			// get rid of enemy (temporary)
			//spriteB->setDestroyFlag(1);
			//player.getPhysicalProperties()->setEnemyRemaining(player.getPhysicalProperties()->getEnemyRemaining() - 1);
			spriteB->setCurrentlyCollidable(false);
		}

		if (spriteA->getPhysicalProperties()->getY() > 
				(game->getGUI()->getViewport()->getViewportY() + game->getGUI()->getViewport()->getViewportHeight())){
				spriteA->setDestroyFlag(1);
		}
		else if (spriteA->getPhysicalProperties()->getY() < (game->getGUI()->getViewport()->getViewportY())){
			spriteA->setDestroyFlag(1);
		}
		if (spriteB->getPhysicalProperties()->getY() > 
				(game->getGUI()->getViewport()->getViewportY() + game->getGUI()->getViewport()->getViewportHeight())){
				spriteB->setDestroyFlag(1);
		}
		else if (spriteB->getPhysicalProperties()->getY() < (game->getGUI()->getViewport()->getViewportY())){
			spriteB->setDestroyFlag(1);
		}

	}

	list<Bot*>::iterator destroyBotsIterator;
	destroyBotsIterator = bots.begin();
	while (destroyBotsIterator != bots.end())
	{
		Bot *currentBot = (*destroyBotsIterator);
		if (currentBot->getDestroyFlag() == 1)
		{
			Bot *botToDestroy = currentBot;
			b2Body *bodyToDestroy = botToDestroy->getBody();
			ourWorld->DestroyBody(bodyToDestroy);
			bodyToDestroy = NULL;
			destroyBotsIterator++;
			bots.remove(botToDestroy);
			delete botToDestroy;
		}
		else
		{
			destroyBotsIterator++;
		}
	}
}