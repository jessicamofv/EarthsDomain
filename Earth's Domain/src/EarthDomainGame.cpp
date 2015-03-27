/*
*****Earth Domain Game*****
	Author: Laugh Out Loud

		Jeffrey Lin
		Jessica Mortellaro
		Jia Hao Wang

		CSE 380 

	EarthDomainGame.cpp

	This is a test game application, a game that demonstrates use of the 
	SideScrollerFramework to make a little scrolling, interactive demo. It
	demonstrates the rendering of images and text as well as responding to
	key presses and button cicks. Students should make their own named game
	applictions using a similar pattern, gradually adding other components,
	like additional gui controls, tiles, sprites, ai, and physics.
 */

#include "stdafx.h"

// EarthDomain GAME INCLUDES
#include "src\EarthDomainButtonEventHandler.h"
#include "src\EarthDomainDataLoader.h"
#include "src\EarthDomainGame.h"
#include "src\EarthDomainKeyEventHandler.h"
// text add
#include "src\EarthDomainTextGenerator.h"

// GAME OBJECT INCLUDES
#include "src\game\Game.h"
#include "src\graphics\GameGraphics.h"
#include "src\gsm\state\GameState.h"
#include "src\gui\Cursor.h"
#include "src\gui\GameGUI.h"
#include "src\gui\ScreenGUI.h"
#include "src\input\GameInput.h"
#include "src\os\GameOS.h"
#include "src\text\GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "src\PlatformPlugins\WindowsPlugin\WindowsOS.h"
#include "src\PlatformPlugins\WindowsPlugin\WindowsInput.h"
#include "src\PlatformPlugins\WindowsPlugin\WindowsTimer.h"

// DIRECTX INCLUDES
#include "src\PlatformPlugins\DirectXPlugin\DirectXGraphics.h"
#include "src\PlatformPlugins\DirectXPlugin\DirectXTextureManager.h"

/*
	WinMain - This is the application's starting point. In this method we will construct a Game object, 
	then initialize all the platform-dependent technologies, then construct all the custom data for our 
	game, and then initialize the Game with	our custom data. We'll then start the game loop.
*/
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	// CREATE THE GAME
	Game *earthDomainGame = new Game();

	// FIRST WE'LL SETUP THE DATA LOADER, SINCE IT MAY NEED TO READ
	// IN DATA TO SETUP OTHER STUFF
	EarthDomainDataLoader *earthDomainDataLoader = new EarthDomainDataLoader();
	earthDomainDataLoader->initWinHandle(hInstance, nCmdShow);
	earthDomainGame->setDataLoader(earthDomainDataLoader);
	earthDomainDataLoader->loadGame(earthDomainGame, W_INIT_FILE);
	
	// WHAT WE SHOULD BE DOING HERE IS LOADING THE GAME DATA FROM FILES. THIS
	// MEANS THE GUIS THEMSELVES AS WELL AS THE LEVELS. THAT WILL BE LEFT
	// FOR BECHMARK HWS. FOR NOW WE WILL JUST HARD CODE THE LOADING OF THE GUI

	// LOAD THE GUI STUFF, AGAIN, NOTE THAT THIS SHOULD REALLY
	// BE DONE FROM A FILE, NOT HARD CODED
	earthDomainDataLoader->loadGUI(earthDomainGame, W_GUI_INIT_FILE);

	// SPECIFY WHO WILL HANDLE BUTTON EVENTS
	EarthDomainButtonEventHandler *earthDomainButtonHandler = new EarthDomainButtonEventHandler();
	GameGUI *gui = earthDomainGame->getGUI();
	gui->registerButtonEventHandler((ButtonEventHandler*)earthDomainButtonHandler);

	// SPECIFY WHO WILL HANDLE KEY EVENTS
	EarthDomainKeyEventHandler *earthDomainKeyHandler = new EarthDomainKeyEventHandler();
	earthDomainGame->getInput()->registerKeyHandler((KeyEventHandler*)earthDomainKeyHandler);

	// START THE GAME LOOP
	earthDomainGame->runGameLoop();

	// GAME'S OVER SHUTDOWN ALL THE STUFF WE CONSTRUCTED HERE
	delete (WindowsOS*)earthDomainGame->getOS();
	delete (WindowsInput*)earthDomainGame->getInput();
	delete (WindowsTimer*)earthDomainGame->getTimer();
	delete (DirectXGraphics*)earthDomainGame->getGraphics();
	// text add
	delete (EarthDomainTextGenerator*)earthDomainGame->getText()->getTextGenerator();
	delete earthDomainButtonHandler;
	delete earthDomainKeyHandler;
	delete earthDomainGame;

	// AND RETURN
	return 0;
}