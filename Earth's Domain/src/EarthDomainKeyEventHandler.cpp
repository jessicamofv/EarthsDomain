/*
*****Earth Domain Game*****
	Author: Laugh Out Loud

		Jeffrey Lin
		Jessica Mortellaro
		Jia Hao Wang

		CSE 380 

	EarthDomainKeyEventHandler.cpp

	See EarthDomainKeyEventHandler.h for a class description.
*/

#include "stdafx.h"
#include "src\EarthDomainKeyEventHandler.h"
#include "src\game\Game.h"
#include "src\game\WStringTable.h"
#include "src\graphics\GameGraphics.h"
#include "src\gsm\physics\Physics.h"
#include "src\gsm\physics\PhysicalProperties.h"
#include "src\gsm\sprite\AnimatedSprite.h"
#include "src\gsm\state\GameState.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gui\Cursor.h"
#include "src\gui\GameGUI.h"
#include "src\input\GameInput.h"
#include "src\timer\GameTimer.h"
#include "src\PlatformPlugins\WindowsPlugin\WindowsTimer.h"
#include "src\gui\Viewport.h"
// text add
#include "src\EarthDomainTextGenerator.h"
#include "src\text\GameText.h"
#include "src\PlatformPlugins\DirectXPlugin\DirectXTextureManager.h"
#include "src\EarthDomainGame.h"
#include "src\EarthDomainDataLoader.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gsm\ai\Bullet.h"
#include "src\gsm\ai\Bots.h"
// i added this
// box2d include
#include <Box2D/Box2D.h>

// bm3 AUDIO add
#include <windows.h>
#include <xact3.h>
#include "src\game\XACT3Audio.h"

// USED FOR MOVEMENT
const unsigned int W_KEY = (unsigned int)'W';
const unsigned int A_KEY = (unsigned int)'A';
const unsigned int S_KEY = (unsigned int)'S';
const unsigned int D_KEY = (unsigned int)'D';

//BM3 DEBUGGING AND CHEATTING BUTTONS
const unsigned int ONE_KEY = (unsigned int)'1';
const unsigned int TWO_KEY = (unsigned int)'2';
const unsigned int THREE_KEY = (unsigned int)'3';
const unsigned int FOUR_KEY = (unsigned int)'4';
const unsigned int FIVE_KEY = (unsigned int)'5';

// USED FOR SHOOTING
const unsigned int SPACE_KEY = (unsigned int)' ';

// MOVES THE VIEWPORT(DEBUGGING)
const unsigned int UP_KEY = VK_UP;
const unsigned int DOWN_KEY = VK_DOWN;
const unsigned int LEFT_KEY = VK_LEFT;
const unsigned int RIGHT_KEY = VK_RIGHT;

// THIS IS JUST FOR SHOWING HOW THE CURSOR CAN BE CHANGED
const unsigned int C_KEY = (unsigned int)'C';

const float PLAYER_SPEED = 5.0f;
const int MIN_FPS = 5;
const int MAX_FPS = 100;
const int FPS_INC = 1;
int bullet_waiting_interval = 33;
bool wait = false;

// bm3 AUDIO add
// replay song for level 1 after 2 min,
// 22 sec, the length of the song
int cyclesBeforeReplayLevel1 = 4260;
// replay song for level 2 after 2 min,
// 45 sec, the length of the song
int cyclesBeforeReplayLevel2 = 5445;
// replay song for level 3 after 1 min,
// 52 sec, the lenght of the song
int cyclesBeforeReplayLevel3 = 3360;
// know if song from other level needs
// to be stopped
int isLevel1SongPlaying = 0;
int isLevel2SongPlaying = 0;
int isLevel3SongPlaying = 0;

// bm4 add
int cyclesBeforeBulletStops = 180;
AnimatedSprite *bulletToStop;

// final bm add
Bullet *playerBullet_1;
Bullet *playerBullet_2;
b2Body *playerBullet_1Body;
b2Body *playerBullet_2Body;
// CHANGED THIS
PhysicalProperties *bulletpp_1;
PhysicalProperties *bulletpp_2;


/*
// bm3 AUDIO add
EarthDomainKeyEventHandler::EarthDomainKeyEventHandler()
{
	LoadContent();
}

// bm3 AUDIO add
EarthDomainKeyEventHandler::~EarthDomainKeyEventHandler()
{
	UnloadContent();
}
*/

/*
	handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
	gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
	key states since the last frame, which can allow us to respond to key presses, including when keys
	are held down for multiple frames.
*/
void EarthDomainKeyEventHandler::handleKeyEvents(Game *game)
{
	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	PhysicalProperties *pp = player->getPhysicalProperties();
	Viewport *viewport = game-> getGUI()->getViewport();
	World *world = gsm->getWorld();

	GameGraphics *graphics = game->getGraphics();
	TextureManager *levelTextureManager = graphics->getWorldTextureManager();
	SpriteManager *spriteManager = gsm->getSpriteManager();

	/*// i added this
	// for dealing with contacts
	EarthDomainContactListener *contactListener = new EarthDomainContactListener();
	b2World *ourWorld = game->getOurWorld();
	ourWorld->SetContactListener(contactListener);
	*/

	/*
	// for the simulation
	float32 timeStep = 1.0f / 60.f;
	int32 velocityIterations = 10;
	int32 positionIterations = 8;
	*/

	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		// CHECK FOR WASD KEYS FOR MOVEMENT
		int incX = 0;
		int incY = 0;
		// ADDS TO THE BULLET INTERVAL
		if(wait == true)
		{
			bullet_waiting_interval--;
			if(bullet_waiting_interval == 0)
			{
				wait = false;
			}

		}

		bool moveViewport = true;

		
	if(player->getPhysicalProperties()->getEnemyRemaining() == 0 )
	{
		if(player->getPhysicalProperties()->getWave() > 5 || player->getPhysicalProperties()->getLevel() == 4)
		{	
			if(player->getPhysicalProperties()->getLevel() < 3)
			{
				player->getPhysicalProperties()->setLevel(player->getPhysicalProperties()->getLevel()+1);
				game->getGSM()->getSpriteManager()->clearSprites();
				graphics->clearWorldTextures();		
				game->getDataLoader()->loadLevel(game, pp->getLevel());
			}
			else if(player->getPhysicalProperties()->getLevel() == 3)
			{
				game->getGSM()->getSpriteManager()->clearSprites();
				graphics->clearWorldTextures();		
				game->getDataLoader()->loadBoss(game, pp->getLevel());
			}
			else if(player->getPhysicalProperties()->getLevel() == 4)
			{
				MessageBoxA(NULL, "CONGRADULATIONS, YOU'VE WON THE GAME!!","WIN SCREEN", 0);
					game->getGSM()->getWorld()->unloadWorld();
				game->deleteBodies();
				game->getGraphics()->getGUIRenderList()->clear();
				game->getGraphics()->getWorldRenderList()->clear();
				game->getGraphics()->getWorldTextureManager()->clear();
				game->getOurWorld()->ClearForces();
				game->getTimer()->resetTimer();
				game->getGraphics()->clearWorldTextures();
				game->getGSM()->getSpriteManager()->clearSprites();
				graphics->clearWorldTextures();

				game->getDataLoader()->loadLevel(game, 1);
				gsm->goToMainMenu();
			}
	
		}
		else
		{
			player->getPhysicalProperties()->setWave(pp->getWave() + 1);
			player->getPhysicalProperties()->setEnemyRemaining(game->getDataLoader()->loadWave(game, player->getPhysicalProperties()->getLevel()));
		
		}
	}
		// WASD AND DIRECTION KEY PRESSES WILL CONTROL THE PLAYER,
		// SO WE'LL UPDATE THE PLAYER VELOCITY WHEN THESE KEYS ARE
		// PRESSED, THAT WAY PHYSICS CAN CORRECT AS NEEDED
		float vX = pp->getVelocityX();
		float vY = pp->getVelocityY();
		float viewX = pp->getVelocityX();
		float viewY = pp->getVelocityY();
		int viewportX = viewport->getViewportX();
		int viewportY = viewport->getViewportY();
		int width = world -> getWorldHeight();
		int height = world -> getWorldHeight();
		int vWidth = viewport -> getViewportWidth();
		int vHeight = viewport -> getViewportHeight();
		

		//These if statements makes sure that the player does not leave the world.
		if(pp->getY()>world->getWorldHeight()-64)
			pp->setY(world->getWorldHeight()-65);

		if(pp->getX()>world->getWorldWidth()-64)
			pp->setX(world->getWorldWidth()-65);

		if(pp->getX()<0)
			pp->setX(1);

		if(pp->getY()<0)
			pp->setY(1);
		
		// scrolling add
		// check if the player is being moved in any
		// direction
		if (input->isKeyDown(W_KEY) || input->isKeyDown(A_KEY) || input->isKeyDown(S_KEY) || input->isKeyDown(D_KEY))
		{
			// then check which direction he's being
			// moved in
			//These if statements control the player and adjusts his movements.
			if (input->isKeyDown(W_KEY)) 
			{
				if(pp->getMoveSpeed() == 1)
				{
					vY = -PLAYER_SPEED;
				}
				else if(pp->getMoveSpeed() == 2)
				{
					vY = -PLAYER_SPEED - 1.5f;
				}
				else if(pp->getMoveSpeed() == 3)
				{
					vY = -PLAYER_SPEED - 2.5f;
				}
				else if(pp->getMoveSpeed() == 4)
				{
					vY = -PLAYER_SPEED - 3.5f;
				}
				else if(pp->getMoveSpeed() == 5)
				{
					vY = -PLAYER_SPEED - 4.5f;
				}
				// viewportY = viewportY - PLAYER_SPEED;
			}
			if (input->isKeyDown(A_KEY))
			{
				if(pp->getMoveSpeed() == 1)
				{
					vX = -PLAYER_SPEED;
				}
				else if(pp->getMoveSpeed() == 2)
				{
					vX = -PLAYER_SPEED - 1.5f;
				}
				else if(pp->getMoveSpeed() == 3)
				{
					vX = -PLAYER_SPEED - 2.5f;
				}
				else if(pp->getMoveSpeed() == 4)
				{
					vX = -PLAYER_SPEED - 3.5f;
				}
				else if(pp->getMoveSpeed() == 5)
				{
					vX = -PLAYER_SPEED - 4.5f;
				}
				// viewportX = viewportX - PLAYER_SPEED;
			}
			if (input->isKeyDown(S_KEY))
			{
				if(pp->getMoveSpeed() == 1)
				{
					vY = PLAYER_SPEED;
				}
				else if(pp->getMoveSpeed() == 2)
				{
					vY = PLAYER_SPEED + 1.5f;
				}
				else if(pp->getMoveSpeed() == 3)
				{
					vY = PLAYER_SPEED + 2.5f;
				}
				else if(pp->getMoveSpeed() == 4)
				{
					vY = PLAYER_SPEED + 3.5f;
				}
				else if(pp->getMoveSpeed() == 5)
				{
					vY = PLAYER_SPEED + 4.5f;
				}
				// viewportY = viewportY + PLAYER_SPEED;
			}
			if (input->isKeyDown(D_KEY))
			{
				if(pp->getMoveSpeed() == 1)
				{
					vX = PLAYER_SPEED;
				}
				else if(pp->getMoveSpeed() == 2)
				{
					vX = PLAYER_SPEED + 1.5f;
				}
				else if(pp->getMoveSpeed() == 3)
				{
					vX = PLAYER_SPEED + 2.5f;
				}
				else if(pp->getMoveSpeed() == 4)
				{
					vX = PLAYER_SPEED + 3.5f;
				}
				else if(pp->getMoveSpeed() == 5)
				{
					vX = PLAYER_SPEED + 4.5f;
				}
				// viewportX = viewportX + PLAYER_SPEED;
			}

			// NOW SET THE ACTUAL VELOCITY
			Physics *physics = gsm->getPhysics();
			pp->setVelocitySafely(physics, vX, vY + (-5.0f)); //Scrolling Add

		}
		// scrolling add
		// if the player isn't being moved in any
		// direction, make sure he's still keeping
		// up with the moving viewport
		else
		{
			Physics *physics = gsm->getPhysics();
			pp->setVelocitySafely(physics,0,-5.0f);
		}

		if (input->isKeyDown(SPACE_KEY))
		{
			if(wait == false)
			{
				// bm3 AUDIO add
				// have shooting sound play when bullets
				// are shot
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("shooting_cue");
				game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );

				// First Bullet
				Bullet *Bullet1 = new Bullet(game,game->getGSM()->getPhysics(),4,
					player->getPhysicalProperties()->getX()+10,
					player->getPhysicalProperties()->getY()+24,1,-1.0);

				Bullet *Bullet2 = new Bullet(game,game->getGSM()->getPhysics(),4,
				player->getPhysicalProperties()->getX()+50,
				player->getPhysicalProperties()->getY()+26,1,-1.0);
				
				if(pp->getAttackSpeed() == 1)
				{
					bullet_waiting_interval = 55;
				}
				else if(pp->getAttackSpeed() == 2)
				{
					bullet_waiting_interval = 44;
				}
				else if(pp->getAttackSpeed() == 3)
				{
					bullet_waiting_interval = 35;
				}
				else if(pp->getAttackSpeed() == 4)
				{
					bullet_waiting_interval = 28;
				}
				else if(pp->getAttackSpeed() == 5)
				{
					bullet_waiting_interval = 20;
				}
				wait = true;
			}
		}

		// NOTE THAT THE VIEWPORT SHOULD FOLLOW THE PLAYER, AND SO SHOULD BE CORRECTED AFTER PHYSICS
		// ARE APPLIED. I HAVE PROVIDED A SIMPLE WAY OF DOING SO, WHICH SHOULD BE IMPROVED, DEPENDING
		// ON THE GAME'S NEED

		// scrolling add
		// viewportY, width, and height defined above
		if (viewportY >= 0)
		{
			// had to reverse it so that x is incremented
			// instead of y
			viewport->moveViewport(0, -5.0f, width, height);
		}
		
		// scrolling add
		// when game reaches the end of the background,
		// loop back to the beginning of the background
		if (viewportY == 1)
		{
			viewport->setViewportY(game->getGSM()->getWorld()->getWorldHeight() - viewport->getViewportHeight());
			player->getPhysicalProperties()->setPosition(player->getPhysicalProperties()->getX(), 
															player->getPhysicalProperties()->getY() + viewport->getViewportY());
			list<Bot*>::iterator updateBotsIterator;
			updateBotsIterator = spriteManager->getBotsIterator();
			while (updateBotsIterator != spriteManager->getEndOfBotsIterator())
			{
				Bot *botToUpdate = (*updateBotsIterator);
				botToUpdate->getPhysicalProperties()->setPosition(botToUpdate->getPhysicalProperties()->getX(),
																	botToUpdate->getPhysicalProperties()->getY() + viewport->getViewportY());
				updateBotsIterator++;
			}
		}

		// scrolling add
		// make sure the player doesn't go below the
		// bottom of the viewport
		if ((pp->getY() + player->getSpriteType()->getTextureHeight()) > (viewport->getViewportY() + viewport->getViewportHeight()))
		{
			pp->setY(viewport->getViewportY() + viewport->getViewportHeight() - player->getSpriteType()->getTextureHeight());
		}
		// or above the top of it (account for
		// 16-pixel health bar on top of the player)
		if (pp->getY() < viewport->getViewportY() + 16)
		{
			pp->setY(viewport->getViewportY() + 16);
		}
	
		// Makes it so that the Sprite is in the middle of the screen.
	/*	if((viewport ->areWorldCoordinatesInViewport(viewportX, viewportY, vWidth, vHeight)) == true)
		{
			if (pp->getX() >= vWidth/2 && pp-> getY() < vHeight/2)
			{
				viewport -> moveViewport(vX, 0, width, height);
			}
			else if (pp-> getY() >= vHeight/2 && pp->getX() < vWidth/2)
			{
				viewport -> moveViewport(0, vY, width, height);
			}
			else if (pp-> getY() >= vHeight/2 && pp->getX() >= vWidth/2)
			{
				if(pp -> getX() <= (width-vWidth) && pp -> getY() <= (height-vHeight))
				{
					viewport -> moveViewport(vX, vY, width, height);
				}
				else if (pp -> getX() <= (width-vWidth))
				{
					viewport -> moveViewport(vX, 0, width, height);
				}
				else if (pp -> getY() <= (height-vHeight))
				{
					viewport -> moveViewport(0, vY, width, height);
				}
			}		
		}
		*/
		
		// i added this
		// update associated body's position based on
		// player's new position after having been moved
		// by W-A-S-D
		b2Body *playerBody = player->getBody();
		int playerWidth = player->getSpriteType()->getTextureWidth();
		int playerHeight = player->getSpriteType()->getTextureHeight();
		playerBody->SetTransform(b2Vec2(pp->getX()/3.0f + playerWidth/2- 8, pp->getY()/3.0f + playerHeight/2), 0);
		player->setBody(playerBody);


		// bm3 AUDIO add
		// play song on start-up, using level
		// number to know which song to play
		if (game->getLevel() == 1)
		{
			if (isLevel2SongPlaying == 1)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("sprinkler_song_cue");
				game->getAudioBanks().soundBank->Stop(clipCue, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
			}
			if (isLevel3SongPlaying == 1)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("rainbow_road_song_cue");
				game->getAudioBanks().soundBank->Stop(clipCue, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
			}
			isLevel1SongPlaying = 1;

			if (cyclesBeforeReplayLevel1 == 4260)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("kweh!_song_cue");
				game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
			}
			// decrement amount of time before
			// replaying of song
			if (cyclesBeforeReplayLevel1 != 0)
			{
				cyclesBeforeReplayLevel1--;
			}
			else
			{
				// if replay countdown has reached 0,
				// start the song again, because the end
				// of the 2 min, 22 sec (== 4260 frames)
				// long song has been reached
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("kweh!_song_cue");
				game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
				cyclesBeforeReplayLevel1 = 4260;
			}
		}
		else if (game->getLevel() == 2)
		{
			if (isLevel1SongPlaying == 1)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("kweh!_song_cue");
				game->getAudioBanks().soundBank->Stop(clipCue, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
			}
			if (isLevel3SongPlaying == 1)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("rainbow_road_song_cue");
				game->getAudioBanks().soundBank->Stop(clipCue, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
			}
			isLevel2SongPlaying = 1;

			if (cyclesBeforeReplayLevel2 == 5445)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("sprinkler_song_cue");
				game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
			}
			// decrement amount of time before
			// replaying of song
			if (cyclesBeforeReplayLevel2 != 0)
			{
				cyclesBeforeReplayLevel2--;
			}
			else
			{
				// if replay countdown has reached 0,
				// start the song again, because the end
				// of the 2 min, 45 sec (== 5445 frames)
				// long song has been reached
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("sprinkler_song_cue");
				game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
				cyclesBeforeReplayLevel2 = 5445;
			}
		}
		else
		{
			if (isLevel1SongPlaying == 1)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("kweh!_song_cue");
				game->getAudioBanks().soundBank->Stop(clipCue, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
			}
			if (isLevel2SongPlaying == 1)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("sprinkler_song_cue");
				game->getAudioBanks().soundBank->Stop(clipCue, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
			}
			isLevel3SongPlaying = 1;

			if (cyclesBeforeReplayLevel3 == 3360)
			{
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("rainbow_road_song_cue");
				game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
			}
			// decrement amount of time before
			// replaying of song
			if (cyclesBeforeReplayLevel3 != 0)
			{
				cyclesBeforeReplayLevel3--;
			}
			else
			{
				// if replay countdown has reached 0,
				// start the song again, because the end
				// of the 1 min, 52 sec (== 3360 frames)
				// long song has been reached
				XACTINDEX clipCue = game->getAudioBanks().soundBank->GetCueIndex("rainbow_road_song_cue");
				game->getAudioBanks().soundBank->Play( clipCue, 0, 0, 0 );
				cyclesBeforeReplayLevel3 = 3360;
			}
		}

		// bm3 AUDIO add
		// update the audio engine
		unsigned long state = 0;
		if( game->getSoundEngine() != 0 && game->getAudioBanks().soundBank != 0 )
		{
			game->getAudioBanks().soundBank->GetState( &state );
			if( state && XACT_CUESTATE_PLAYING )
			{
				game->getSoundEngine()->DoWork( );
			}
		}
	}

	// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
	// THIS CHANGES THE CURSOR IMAGE
	if ((input->isKeyDownForFirstTime(C_KEY))
		&& input->isKeyDown(VK_SHIFT))
	{
		Cursor *cursor = game->getGUI()->getCursor();
		unsigned int id = cursor->getActiveCursorID();
		id++;
		if (id == cursor->getNumCursorIDs())
			id = 0;		
		cursor->setActiveCursorID(id);
	}

	//BM3
	if ((input->isKeyDownForFirstTime(ONE_KEY))
		&& input->isKeyDown(VK_CONTROL)){
	
	game->getGSM()->getWorld()->unloadWorld();
	game->deleteBodies();
	game->getGraphics()->getGUIRenderList()->clear();
	game->getGraphics()->getWorldRenderList()->clear();
	game->getGraphics()->getWorldTextureManager()->clear();
	game->getOurWorld()->ClearForces();
	game->getTimer()->resetTimer();
	game->getGraphics()->clearWorldTextures();
	game->getGSM()->getSpriteManager()->clearSprites();
	graphics->clearWorldTextures();

	//bm3 AUDIO add
	// reset replay countdowns for
	// other levels
	cyclesBeforeReplayLevel2 = 5445;
	cyclesBeforeReplayLevel3 = 3360;

	game->getDataLoader()->loadLevel(game, 1);
	}

	//BM3
	if ((input->isKeyDownForFirstTime(TWO_KEY))
		&& input->isKeyDown(VK_CONTROL)){
	
	game->getGSM()->getWorld()->unloadWorld();
	game->deleteBodies();
	game->getGraphics()->getGUIRenderList()->clear();
	game->getGraphics()->getWorldRenderList()->clear();
	game->getGraphics()->getWorldTextureManager()->clear();
	game->getOurWorld()->ClearForces();
	game->getTimer()->resetTimer();
	game->getGraphics()->clearWorldTextures();
	game->getGSM()->getSpriteManager()->clearSprites();

	//bm3 AUDIO add
	// reset replay countdowns for
	// other levels
	cyclesBeforeReplayLevel1 = 4260;
	cyclesBeforeReplayLevel3 = 3360;

	game->getDataLoader()->loadLevel(game, 2);
	}

	//BM3
	if ((input->isKeyDownForFirstTime(THREE_KEY))
		&& input->isKeyDown(VK_CONTROL)){

	game->getGSM()->getWorld()->unloadWorld();
	game->deleteBodies();
	game->getGraphics()->getGUIRenderList()->clear();
	game->getGraphics()->getWorldRenderList()->clear();
	game->getGraphics()->getWorldTextureManager()->clear();
	game->getOurWorld()->ClearForces();
	game->getTimer()->resetTimer();
	game->getGraphics()->clearWorldTextures();
	game->getGSM()->getSpriteManager()->clearSprites();
	graphics->clearWorldTextures();

	//bm3 AUDIO add
	// reset replay countdowns for
	// other levels
	cyclesBeforeReplayLevel1 = 4260;
	cyclesBeforeReplayLevel2 = 5445;

	game->getDataLoader()->loadLevel(game, 3);

	}

	if ((input->isKeyDownForFirstTime(FOUR_KEY))
		&& input->isKeyDown(VK_CONTROL)){

	game->getGSM()->getWorld()->unloadWorld();
	game->deleteBodies();
	game->getGraphics()->getGUIRenderList()->clear();
	game->getGraphics()->getWorldRenderList()->clear();
	game->getGraphics()->getWorldTextureManager()->clear();
	game->getOurWorld()->ClearForces();
	game->getTimer()->resetTimer();
	game->getGraphics()->clearWorldTextures();
	game->getGSM()->getSpriteManager()->clearSprites();
	graphics->clearWorldTextures();

	//bm3 AUDIO add
	// reset replay countdowns for
	// other levels
	cyclesBeforeReplayLevel1 = 4260;
	cyclesBeforeReplayLevel2 = 5445;

	
	pp->setWave(6);
	game->getDataLoader()->loadLevel(game, 4);

	}

	if ((input->isKeyDownForFirstTime(FIVE_KEY))
		&& input->isKeyDown(VK_CONTROL))
	{

		pp->setCurrency(5000);

	}

	game->getText()->clear();

	// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
	WindowsTimer *timer = (WindowsTimer*)game->getTimer();
	int fps = timer->getTargetFPS();

	// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
	// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
	// A BETTER PLAYER EXPERIENCE
	if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
		timer->setTargetFPS(fps + FPS_INC);

	// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
	else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
		timer->setTargetFPS(fps - FPS_INC);
}

/*
// bm3 AUDIO add
bool EarthDomainKeyEventHandler::LoadContent()
{
	ZeroMemory( &audioBanks_, sizeof( stXACTAudio ) );
	if( SetupXACT( &soundEngine_ ) == false )
		return false;
	if( LoadXACTAudio( soundEngine_, audioBanks_,"Win/First Wave Bank.xwb","Win/First Sound Bank.xsb" ) == false )
		return false;
	return true;
}

// bm3 AUDIO add
void EarthDomainKeyEventHandler::UnloadContent()
{
	if( audioBanks_.soundBank ) audioBanks_.soundBank->Destroy( );
	if( audioBanks_.waveBank ) audioBanks_.waveBank->Destroy( );
	if( soundEngine_ )
	{
		soundEngine_->ShutDown( );
		soundEngine_->Release( );
	}
	if( audioBanks_.soundBankData )
	{
		UnmapViewOfFile( audioBanks_.soundBankData );
		audioBanks_.soundBankData = 0;
	}
	if( audioBanks_.waveBankData )
	{
		UnmapViewOfFile( audioBanks_.waveBankData );
		audioBanks_.waveBankData = 0;
	}
	CoUninitialize( );
}
*/