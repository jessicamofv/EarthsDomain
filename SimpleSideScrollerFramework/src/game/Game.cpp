/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	Game.cpp

	See Game.h for a class description.
*/
#include "stdafx.h"
#include "src\dataLoader\GameDataLoader.h"
#include "src\game\Game.h"
#include "src\gsm\state\GameStateManager.h"
#include "src\gui\Button.h"
#include "src\gui\Cursor.h"
#include "src\gui\GameGUI.h"
#include "src\gui\ScreenGUI.h"
#include "src\graphics\GameGraphics.h"
#include "src\input\GameInput.h"
#include "src\os\GameOS.h"
#include "src\text\GameText.h"
#include "src\text\TextFileWriter.h"
// text add
#include "src\text\TextGenerator.h"
#include "src\timer\GameTimer.h"
// i added this
// box2d include
#include <Box2D/Box2D.h>;
// bm4 add
#include <windows.h>
#include <xact3.h>
#include "XACT3Audio.h"

/*
	Game  - Constructor, this method begins the 
	construction and loading of all major game objects. 
	This method only needs to be called once, when the 
	application is first started.

	NOTE: This constructor will not initialize the custom
	game objects: graphics, input, os, & timer.
	These must be constructed separately and fed to this
	object using the init method. Doing it this way allows for
	more platform independence.
*/
Game::Game()
{
	// NOTE THAT graphics, input, os, & timer
	// ARE CUSTOM GAME OBJECTS. DEPENDING ON WHAT TECHNOLOGY 
	// IS TO BE USED THESE OBJECT SHOULD BE CONSTRUCTED
	// AND THEN FED TO THIS Game USING THE init METHOD
	gsm = new GameStateManager();
	gui = new GameGUI();
	text = new GameText();

	// i added this
	// set up the box2d world
	b2Vec2 gravity(0.0f, /*-10.0f*/ 0.0f);
	ourWorld = new b2World(gravity);
	// CHANGED THIS
	ourWorld->SetAllowSleeping(false);

	// bm4 add
	LoadContent();

	// upgrades add
	numHealthUpgrades = 0;
	numAttackSpeedUpgrades = 0;
	numAttackDamageUpgrades = 0;
	numMoveSpeedUpgrades = 0;
	numLivesUpgrades = 0;

	// upgrades add
	priceHealth = 100;
	priceAttackSpeed = 100;
	priceAttackDamage = 100;
	priceMoveSpeed = 100;
	priceLives = 100;
}

/*
	~Game - Desctructor, it recovers memory allocated for
	the game objects. If Game is deleted, the application
	is closing, so everything should be cleaned up. Note that
	this 
*/
Game::~Game() 
{
	// THESE WERE CREATED BY Game, AND SO SHOULD BE
	// DELETED BY GAME
	delete gsm;
	delete gui;
	delete text;

	delete ourWorld;
	ourWorld = NULL;

	// bm4 add
	UnloadContent();

	// THE GAME AND PLATFORM STUFF SHOULD BE DELETED
	// BY WHOEVER CREATED THEM
}

/*
	initPlatformPlugins - This method is to be used to feed this Game
	the constructed, technology-specific, objects. 
*/
void Game::initPlatformPlugins(		GameGraphics *initGraphics,
									GameInput *initInput,
									GameOS *initOS,									
									GameTimer *initTimer)
{
	// INITIALIZE ALL OF THE GAME'S CUSTOM OBJECTS
	graphics = initGraphics;
	input = initInput;
	os = initOS;
	timer = initTimer;
}

/*
	reloadAllDevices - Windows applications must cooperate
	with other running applications, so when someone hits
	ALT-TAB and switches from a full-screen game, it might
	lose ownership of the graphics card. This method can
	be called when a full-screen application retains ownership
	of all necessary resources such that all necessary
	data (like textures, sound, music, etc.) can be reloaded.
*/
void Game::reloadAllDevices()
{
	graphics->reloadGraphics();

	// WE MIGHT ADD MORE LATER
}
	
/*
	runGameLoop - This is the game loop management method.
	It runs continuously while the game is active. Once per
	frame it instructs the major game objects to get
	user input, record user input, update the GUI state, 
	update the sprites' states using AI and input, perform
	collision detection and resolution (physics), render
	the screen, etc.

	This loop is timed such that everything is kept to a 
	consistent framerate, thus the game should run 
	consistently on all machines.
*/
void Game::runGameLoop()
{
	// FIRST PROFILE?
	bool firstTimeThroughLoop = true;

	// LET'S START THE TIMER FROM SCRATCH
	timer->resetTimer();

	// KEEP RENDERING UNTIL SOMEONE PULLS THE PLUG
	while(gsm->isAppActive())
	{
		// MOVE ALONG WINDOWS MESSAGES, THIS ALLOWS
		// US TO GET USER INPUT
		os->processOSMessages();

		// GET USER INPUT AND UPDATE GAME, GUI, OR PLAYER
		// STATE OR WHATEVER IS NECESSARY
		input->processInput(this);

		// IT IS POSSIBLE THE USER REQUESTED A SHUTDOWN
		// OF THE APP, SO WE NEED TO CHECK AGAIN
		if (gsm->isAppActive())
		{
			// USE THE INPUT TO UPDATE THE GAME
			processGameData();

			// AND RENDER THE GAME
			graphics->renderGame(this);
		}
	}
}

/*
	processGameData - This method directs game logic to be
	executed or not, depending on the game state, it addition
	it triggers the building or render lists and game loop
	timing each frame.
*/
void Game::processGameData()
{
	// WE ONLY PERFORM GAME LOGIC IF THE GAME
	// IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		gsm->update(this);
	}
	else if (gsm->isGameLevelLoading())
	{
		gsm->goToGame();
	}

	// text add
	// UPDATE TEXT
	if (gsm->getCurrentGameState() == GS_UPGRADE_SHOP)
	{
		TextGenerator *tg = text->getTextGenerator();
		tg->updateText(this);
	}

	// BUILD THE RENDER LISTS
	graphics->fillRenderLists(this);

	// KEEP THE FRAME RATE CONSISTENT
	timer->timeGameLoop();
}

/*
	quitGame - When called, this method will force the unloading of all game data
	loaded for the current level and then return the user to the main menu.
*/
void Game::quitGame()
{
	// CLEAN UP ALL THE WORLD TEXTURES
	graphics->clearWorldTextures();

	// WE'RE GOING BACK TO THE MAIN MENU
	gsm->goToMainMenu();
}

/*
	Show the Controls the game uses
*/
// screens add
/*void Game::goToControls()
{
	MessageBoxA(NULL, "CONTROLS:\n\nW - Move Up\nA � Move Left\nS � Move Down\nD- Move Right\nSPACE � Shoot\nP � Pause\nSHIFT + C - Change Cursor", "List of Controls", 0 );
}

void Game::goToAbout()
{
	MessageBoxA(NULL, "Version: 1.0\nAuthors: Jeffrey Lin, Jessica Mortellaro, Jia Hao Wang\nGroup Name: Laugh Out Loud\nCSE380", "ABOUT", 0 );
}*/

// bm4 add
bool Game::LoadContent()
{
	ZeroMemory( &audioBanks_, sizeof( stXACTAudio ) );
	if( SetupXACT( &soundEngine_ ) == false )
		return false;
	if( LoadXACTAudio( soundEngine_, audioBanks_,"Win/First Wave Bank.xwb","Win/First Sound Bank.xsb" ) == false )
		return false;
	return true;
}

void Game::UnloadContent()
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

/*
	shutdown - This method starts the termination of the game application, 
	cascading shutdown proceedings through all the necessary classes, resulting
	in the release of all game resources.
*/
void Game::shutdown()
{
	// MAKE SURE THE GAME LOOP ENDS AND THAT THE GSM CLEANS
	// UP ALL THE MEMORY IT IS USING
	gsm->shutdown();

	// CLEAR OUT AND RELEASE THE GPU
	graphics->shutdown();

	// RELEASE GAME CONTROLLERS IF NECESSARY
	input->shutdown();

	// WE MAY SHUTDOWN OTHER THINGS HERE LIKE SOUND & MUSIC
	// RESOURCES IN THE FUTURE
	// AND KILL THE WINDOW
	os->shutdown();
}

/*
	startGame - When called, this method will load the first level of the
	game and start play. Note that one must make sure the currentLeve
*/
void Game::startGame()
{
	// AND UPDATE THE GAME STATE OF COURSE
	gsm->goToLoadLevel();	// NOTE THAT CURRENTLY THERE IS NO LEVEL FILE,
	
	// THAT'S ONE THING YOU'LL BE DOING
	dataLoader->loadWorld(this, currentLevelFileName);
}

// final benchmark
void Game::deleteBodies()
{
	b2Body* body = ourWorld->GetBodyList();
	
	while (body)
	{
		b2Body* currentBody = body;
		body = body->GetNext();
		AnimatedSprite* currentSprite = (AnimatedSprite*)currentBody->GetUserData();
		ourWorld->DestroyBody(currentBody);
	}
}