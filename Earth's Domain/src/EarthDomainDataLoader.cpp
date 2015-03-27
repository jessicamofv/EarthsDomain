#include "stdafx.h"

// EarthDomain GAME INCLUDES
#include "src\EarthDomainButtonEventHandler.h"
#include "src\EarthDomainDataLoader.h"
#include "src\EarthDomainGame.h"
#include "src\EarthDomainKeyEventHandler.h"
// text add
#include "src\EarthDomainTextGenerator.h"

#include "src\gsm\ai\Lives.h"
// GAME OBJECT INCLUDES
#include "src\game\Game.h"
#include "src\graphics\GameGraphics.h"
#include "src\gsm\state\GameState.h"
#include "src\gsm\world\TiledLayer.h"
#include "src\gui\Cursor.h"
#include "src\gui\GameGUI.h"
#include "src\gui\ScreenGUI.h"
#include "src\input\GameInput.h"
#include "src\os\GameOS.h"
#include "src\text\GameText.h"
#include "src\gsm\ai\Bots.h"

// WINDOWS PLATFORM INCLUDES
#include "src\PlatformPlugins\WindowsPlugin\WindowsOS.h"
#include "src\PlatformPlugins\WindowsPlugin\WindowsInput.h"
#include "src\PlatformPlugins\WindowsPlugin\WindowsTimer.h"

// DIRECTX INCLUDES
#include "src\PlatformPlugins\DirectXPlugin\DirectXGraphics.h"
#include "src\PlatformPlugins\DirectXPlugin\DirectXTextureManager.h"

#include "src\PoseurSpriteTypeImporter.h";

#include "src\gsm\ai\EnemyBots\Attacker.h"
#include "src\gsm\ai\EnemyBots\Defender.h"
#include "src\gsm\ai\EnemyBots\Speedster.h"
#include "src\gsm\ai\EnemyBots\Bosses\FirstBossCenter.h"
#include "src\gsm\ai\EnemyBots\Bosses\FirstBossLeft.h"
#include "src\gsm\ai\EnemyBots\Bosses\FirstBossRight.h"
#include "src\gsm\ai\health.h"
#include "src\gsm\sprite\AnimatedSpriteType.h"

/*
	loadGame - This method loads the setup game data into the game and
	constructs all the needed objects for the game to work.
*/


void EarthDomainDataLoader::loadGame(Game *game, wstring gameInitFile)
{
	// AND LET'S READ IN THE GAME SETUP INFO
	// FIRST LOAD ALL THE PROPERTIES
	map<wstring,wstring> *properties = new map<wstring,wstring>();
	loadGameProperties(game, properties, gameInitFile);

	// WE NEED THE TITLE AND USE_FULLSCREEN_MODE TO INITIALIZE OUR WINDOW
	wstring titleProp = (*properties)[W_TITLE];
	wstring useFullscreenProp = (*properties)[W_USE_FULLSCREEN_MODE];
	bool useFullscreen = false;
	if (useFullscreenProp.compare(L"true") == 0)
		useFullscreen = true;

	// GET THE SCREEN WIDTH AND HEIGHT
	int screenWidth, screenHeight;
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;

	// MAKE A CUSTOM GameOS OBJECT (WindowsOS) FOR SOME WINDOWS
	// PLATFORM STUFF, INCLUDING A Window OF COURSE
	WindowsOS *earthDomainOS = new WindowsOS(	hInstance, 
										nCmdShow,
										useFullscreen,
										titleProp,
										screenWidth, screenHeight,
										game);
	
	int textFontSize;
	wstring textFontSizeProp = (*properties)[W_TEXT_FONT_SIZE];
	wstringstream(textFontSizeProp) >> textFontSize;

	// RENDERING WILL BE DONE USING DirectX
	DirectXGraphics *earthDomainGraphics = new DirectXGraphics(game);
	earthDomainGraphics->init(screenWidth, screenHeight);
	earthDomainGraphics->initGraphics(earthDomainOS, useFullscreen);
	earthDomainGraphics->initTextFont(textFontSize);

	// AND NOW LOAD THE COLORS THE GRAPHICS WILL USE
	// AS A COLOR KEY AND FOR RENDERING TEXT
	initColors(earthDomainGraphics, properties);

	// WE'LL USE WINDOWS PLATFORM METHODS FOR GETTING INPUT
	WindowsInput *earthDomainInput = new WindowsInput();

	// AND WINDOWS FOR THE TIMER AS WELL
	WindowsTimer *earthDomainTimer = new WindowsTimer();

	// NOW INITIALIZE THE Game WITH ALL THE
	// PLATFORM AND GAME SPECIFIC DATA WE JUST CREATED
	game->initPlatformPlugins(	(GameGraphics*)earthDomainGraphics,
								(GameInput*)earthDomainInput,
								(GameOS*)earthDomainOS,
								(GameTimer*)earthDomainTimer);

	// INIT THE VIEWPORT TOO
	initViewport(game->getGUI(), properties);	

	// WE DON'T NEED THE PROPERTIES MAP ANYMORE, THE GAME IS ALL LOADED
	delete properties;
}

/*
	initColors - this helper method loads the color key, used for loading
	images, and the font color, used for rendering text.
*/
void EarthDomainDataLoader::initColors(	GameGraphics *graphics,
									map<wstring,wstring> *properties)
{
	int fontRed, fontGreen, fontBlue;
	wstring fontRedProp = (*properties)[W_FONT_COLOR_RED];
	wstring fontGreenProp = (*properties)[W_FONT_COLOR_GREEN];
	wstring fontBlueProp = (*properties)[W_FONT_COLOR_BLUE];
	wstringstream(fontRedProp) >> fontRed;
	wstringstream(fontGreenProp) >> fontGreen;
	wstringstream(fontBlueProp) >> fontBlue;

	// COLOR USED FOR RENDERING TEXT
	graphics->setFontColor(fontRed, fontGreen, fontBlue);

	int keyRed, keyGreen, keyBlue;
	wstring keyRedProp = (*properties)[W_COLOR_KEY_RED];
	wstring keyGreenProp = (*properties)[W_COLOR_KEY_GREEN];
	wstring keyBlueProp = (*properties)[W_COLOR_KEY_BLUE];
	wstringstream(keyRedProp) >> keyRed;
	wstringstream(keyGreenProp) >> keyGreen;
	wstringstream(keyBlueProp) >> keyBlue;

	// COLOR KEY - COLOR TO BE IGNORED WHEN LOADING AN IMAGE
	// NOTE, IF YOU WISH TO USE PNG IMAGES THAT CONTAIN ALPHA
	// CHANNEL DATA, YOU DON'T NEED A COLOR KEY
	graphics->setColorKey(keyRed, keyGreen, keyBlue);
}

/*
	loadGUI - This method loads all the GUI assets described in the guiInitFile
	argument. Note that we are loading all GUI art for all GUIs when the application
	first starts. We'll learn a better technique later in the semester.
*/
void EarthDomainDataLoader::loadGUI(Game *game, wstring guiInitFile)
{
	// WE'RE JUST GOING TO IGNORE THE GUI FILE FOR NOW.
	// FOR THE MOMENT WE ARE CALLING THIS HARD-CODED GUI LOADER
	hardCodedLoadGUIExample(game);
}


/*
	loadLevel - This method should load the data the level described by the
	levelInitFile argument in to the Game's game state manager.
*/
void EarthDomainDataLoader::loadWorld(Game *game, wstring levelInitFile)	
{
	// NOTE:	I AM DEMONSTRATING HOW TO LOAD A LEVEL
	//			PROGRAMICALLY. YOU SHOULD DO THIS
	//			USING CSV FILES.
	/*
	map<wstring,wstring> *properties = new map<wstring,wstring>();
	loadGameProperties(game, properties, levelInitFile);

	// WE NEED THE TITLE AND USE_FULLSCREEN_MODE TO INITIALIZE OUR WINDOW
	wstring levelProp = (*properties)[W_LEVEL_1];
	*/

	// scrolling add
	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	PhysicalProperties *pp = player->getPhysicalProperties();

	//Initilizes the stat
	pp->setCurrency(0);
	pp->setCurrentHealth(5);
	pp->setMaxHealth(5);
	pp->setAttackDamage(1);
	pp->setAttackSpeed(1);
	pp->setMoveSpeed(1);
	// game over add
	pp->setLives(2);

	loadLevel(game, 1);

	// text add
	// LOAD OUR CUSTOM TEXT GENERATOR, WHICH DRAWS
	// TEXT ON THE SCREEN EACH FRAME
	EarthDomainTextGenerator *earthDomainTextGenerator = new EarthDomainTextGenerator();
	earthDomainTextGenerator->initText(game);
	GameText *text = game->getText();
	text->setTextGenerator((TextGenerator*)earthDomainTextGenerator);
}

/*
	initEarthDomainGUI - This method builds a GUI for the EarthDomain Game application.
	Note that we load all the GUI components from this method, including
	the ScreenGUI with Buttons and Overlays and the Cursor.
*/
void EarthDomainDataLoader::hardCodedLoadGUIExample(Game *game)
{
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	DirectXTextureManager *guiTextureManager = (DirectXTextureManager*)graphics->getGUITextureManager();

	// SETUP THE CURSOR VIA OUR HELPER METHOD
	initCursor(gui, guiTextureManager);
	initSplashScreen(game, gui, guiTextureManager);
	initUpgradeShop(game, gui, guiTextureManager);
	initMainMenu(gui, guiTextureManager);
	initInGameGUI(gui, guiTextureManager);
	// screens add
	initControlsScreen(gui, guiTextureManager);
	initAboutScreen(gui, guiTextureManager);
	// game over add
	initGameOverScreen(gui, guiTextureManager);
}

/*
	initCursor - initializes a simple little cursor for the gui.
*/
void EarthDomainDataLoader::initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// SETUP THE CURSOR
	vector<unsigned int> *imageIDs = new vector<unsigned int>();
	int imageID;

	// - FIRST LOAD THE GREEN CURSOR IMAGE
	imageID = guiTextureManager->loadTexture(W_PLAYER_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - AND NOW THE RED ONE
	imageID = guiTextureManager->loadTexture(W_ENEMY_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - NOW BUILD AND LOAD THE CURSOR
	Cursor *cursor = new Cursor();
	cursor->initCursor(	imageIDs,
						*(imageIDs->begin()),
						0,
						0,
						0,
						255,
						32,
						32);
	gui->setCursor(cursor);
}

/*
	initSplashScreen - initializes the game's splash screen gui.
*/
void EarthDomainDataLoader::initSplashScreen(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	// NOW, FIRST LET'S ADD A SPLASH SCREEN GUI
	ScreenGUI *splashScreenGUI = new ScreenGUI();

	// WE'LL ONLY HAVE ONE IMAGE FOR OUR GIANT BUTTON
	unsigned int normalTextureID = guiTextureManager->loadTexture(W_SPLASH_SCREEN_PATH);
	unsigned int mouseOverTextureID = normalTextureID;

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							0,
							0,
							0,
							255,
							game->getGraphics()->getScreenWidth(),
							game->getGraphics()->getScreenHeight(),
							false,
							W_GO_TO_MM_COMMAND);
	splashScreenGUI->addButton(buttonToAdd);

	// AND REGISTER IT WITH THE GUI
	gui->addScreenGUI(GS_SPLASH_SCREEN, splashScreenGUI);
}

// screens add
void EarthDomainDataLoader::initControlsScreen(GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	ScreenGUI *controlsScreenGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_CONTROLS_SCREEN_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	controlsScreenGUI->addOverlayImage(imageToAdd);

	Button *buttonToAdd = new Button();

	int normalTextureID = guiTextureManager->loadTexture(W_BACK_TO_MM_IMAGE_PATH);
	int mouseOverTextureID = normalTextureID;
		//guiTextureManager->loadTexture(W_BACK_TO_MM_IMAGE_MO_PATH);

	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							744,
							703,
							0,
							255,
							280,
							65,
							false,
							W_BACK_TO_MM_COMMAND);

	controlsScreenGUI->addButton(buttonToAdd);

	gui->addScreenGUI(GS_MENU_CONTROLS_MENU,	controlsScreenGUI);
}

// screens add
void EarthDomainDataLoader::initAboutScreen(GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	ScreenGUI *aboutScreenGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_ABOUT_SCREEN_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	aboutScreenGUI->addOverlayImage(imageToAdd);

	Button *buttonToAdd = new Button();

	int normalTextureID = guiTextureManager->loadTexture(W_BACK_TO_MM_IMAGE_MO_PATH);
	int mouseOverTextureID = normalTextureID;
		//guiTextureManager->loadTexture(W_BACK_TO_MM_IMAGE_MO_PATH);

	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							744,
							703,
							0,
							255,
							280,
							65,
							false,
							W_BACK_TO_MM_COMMAND);

	aboutScreenGUI->addButton(buttonToAdd);

	gui->addScreenGUI(GS_MENU_ABOUT_MENU,	aboutScreenGUI);
}

// game over add
void EarthDomainDataLoader::initGameOverScreen(GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	ScreenGUI *gameOverScreenGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_GAME_OVER_SCREEN_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	gameOverScreenGUI->addOverlayImage(imageToAdd);

	Button *buttonToAdd = new Button();

	int normalTextureID = guiTextureManager->loadTexture(W_BACK_TO_MM_2_IMAGE_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(W_BACK_TO_MM_2_IMAGE_MO_PATH);;

	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							744,
							703,
							0,
							255,
							280,
							65,
							false,
							W_BACK_TO_MM_COMMAND);

	gameOverScreenGUI->addButton(buttonToAdd);

	gui->addScreenGUI(GS_GAME_OVER,	gameOverScreenGUI);
}

//BM3 Testing
void EarthDomainDataLoader::initUpgradeShop(Game *game, GameGUI *gui,DirectXTextureManager *guiTextureManager)
{
	ScreenGUI *UpgradeShopGUI = new ScreenGUI();
	// WE'LL ONLY HAVE ONE IMAGE FOR OUR GIANT BUTTON
	
	unsigned int imageID = guiTextureManager->loadTexture(W_SHOP_OVERLAY_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	UpgradeShopGUI->addOverlayImage(imageToAdd);

	imageID = guiTextureManager->loadTexture(W_UPGRADE_MENU_PATH);
	imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 1024;
	imageToAdd->height = 150;
	imageToAdd->imageID = imageID;
	UpgradeShopGUI->addOverlayImage(imageToAdd);

	imageID = guiTextureManager->loadTexture(W_HEALTH_UPGRADE_PATH);
	imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 350;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 140;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID;
	UpgradeShopGUI->addOverlayImage(imageToAdd);

	imageID = guiTextureManager->loadTexture(W_DAMAGE_UPGRADE_PATH);
	imageToAdd = new OverlayImage();
	imageToAdd->x = 190;
	imageToAdd->y = 350;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 140;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID;
	UpgradeShopGUI->addOverlayImage(imageToAdd);

	imageID = guiTextureManager->loadTexture(W_ATTACK_SPEED_UPGRADE_PATH);
	imageToAdd = new OverlayImage();
	imageToAdd->x = 380;
	imageToAdd->y = 350;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 200;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID;
	UpgradeShopGUI->addOverlayImage(imageToAdd);

	imageID = guiTextureManager->loadTexture(W_MOVEMENT_UPGRADE_PATH);
	imageToAdd = new OverlayImage();
	imageToAdd->x = 630;
	imageToAdd->y = 350;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 200;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID;
	UpgradeShopGUI->addOverlayImage(imageToAdd);

	imageID = guiTextureManager->loadTexture(W_LIVES_UPGRADE_PATH);
	imageToAdd = new OverlayImage();
	imageToAdd->x = 880;
	imageToAdd->y = 350;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 140;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID;
	UpgradeShopGUI->addOverlayImage(imageToAdd);


	unsigned int normalTextureID = guiTextureManager->loadTexture(W_GO_TO_GAME_PATH);
	unsigned int mouseOverTextureID = normalTextureID;
	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							450,
							680,
							0,
							255,
							140,
							65,
							false,
							W_GO_TO_GAME_COMMAND);
	UpgradeShopGUI->addButton(buttonToAdd);


	normalTextureID = guiTextureManager->loadTexture(W_BUY_PATH);
	mouseOverTextureID = normalTextureID;

	buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							40,
							450,
							0,
							255,
							71,
							65,
							false,
							W_UPGRADE_HEALTH_COMMAND ); // Will be changed to health upgrade method
	UpgradeShopGUI->addButton(buttonToAdd);

	buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							230,
							450,
							0,
							255,
							71,
							65,
							false,
							W_UPGRADE_ATTACK_DAMAGE_COMMAND ); // Will be changed to damage upgrade method
	UpgradeShopGUI->addButton(buttonToAdd);

	buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							440,
							450,
							0,
							255,
							71,
							65,
							false,
							W_UPGRADE_ATTACK_SPEED_COMMAND ); // Will be changed to attack speed upgrade method
	UpgradeShopGUI->addButton(buttonToAdd);

	buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							700,
							450,
							0,
							255,
							71,
							65,
							false,
							W_UPGRADE_MOVE_SPEED_COMMAND ); // Will be changed to move speed upgrade method
	UpgradeShopGUI->addButton(buttonToAdd);

	buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							915,
							450,
							0,
							255,
							71,
							65,
							false,
							W_GO_TO_GAME_COMMAND ); // Will be changed to life upgrade method
	UpgradeShopGUI->addButton(buttonToAdd);



		// AND REGISTER IT WITH THE GUI
	gui->addScreenGUI(GS_UPGRADE_SHOP, UpgradeShopGUI);
}


/*
	initMainMenu - initializes the game's main menu gui.
*/

void EarthDomainDataLoader::initMainMenu(GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_MAIN_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	mainMenuGUI->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN EXIT BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(W_EXIT_IMAGE_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							450,
							510,
							0,
							255,
							140,
							60,
							false,
							W_EXIT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD A START BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(W_START_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_START_IMAGE_MO_PATH);

	// - INIT THE START BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							450,
							300,
							0,
							255,
							140,
							60,
							false,
							W_START_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// Added - Jason
	buttonToAdd = new Button();
	normalTextureID = guiTextureManager->loadTexture(W_CONTROLS_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_CONTROLS_IMAGE_MO_PATH);

	// - INIT THE CONTROL BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							450,
							370,
							0,
							255,
							140,
							60,
							false,
							W_CONTROLS_COMMAND);


	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);


	buttonToAdd = new Button();
	normalTextureID = guiTextureManager->loadTexture(W_ABOUT_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_ABOUT_IMAGE_MO_PATH);

	// - INIT THE CONTROL BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							450,
							440,
							0,
							255,
							140,
							60,
							false,
							W_ABOUT_COMMAND);


	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);


	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_MAIN_MENU,	mainMenuGUI);
}


/*
	initInGameGUI - initializes the game's in-game gui.
*/
void EarthDomainDataLoader::initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW ADD THE IN-GAME GUI
	ScreenGUI *inGameGUI = new ScreenGUI();

	unsigned int imageID = guiTextureManager->loadTexture(BACKGROUND_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 1024;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID;
	inGameGUI->addOverlayImage(imageToAdd);
	
	// INIT THE QUIT BUTTON
	unsigned int normalTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_MO_PATH);

	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							884,
							0,
							0,
							255,
							140,
							65,
							false,
							W_QUIT_COMMAND);
	inGameGUI->addButton(buttonToAdd);

	// INIT THE UPGRADE SHOP
	unsigned int upgradeTextureID = guiTextureManager->loadTexture(W_UPGRADE_IMAGE_PATH);
	unsigned int upgradeMouseOverTextureID = guiTextureManager->loadTexture(W_UPGRADE_IMAGE_MO_PATH);

	buttonToAdd = new Button();
	buttonToAdd->initButton(upgradeTextureID, 
							upgradeMouseOverTextureID,
							0,
							0,
							0,
							255,
							140,
							65,
							false,
							W_SHOP_COMMAND);
	inGameGUI->addButton(buttonToAdd);
	

	// INIT THE INFO lAYOUT
	imageToAdd = new OverlayImage();
	unsigned int imageID3 = guiTextureManager->loadTexture(INFO_PATH);
	imageToAdd->x = 679;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 200;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID3;
	inGameGUI->addOverlayImage(imageToAdd);

	imageToAdd = new OverlayImage();
	unsigned int imageID4 = guiTextureManager->loadTexture(GUI_TITLE_PATH);
	imageToAdd->x = 350;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 324;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID4;
	inGameGUI->addOverlayImage(imageToAdd);

	imageToAdd = new OverlayImage();
	unsigned int imageID2 = guiTextureManager->loadTexture(LIVES_2_PATH);
	imageToAdd->x = 145;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 255;
	imageToAdd->width = 200;
	imageToAdd->height = 65;
	imageToAdd->imageID = imageID2;
	inGameGUI->addOverlayImage(imageToAdd);
	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_GAME_IN_PROGRESS,	inGameGUI);

}

/*
	initViewport - initializes the game's viewport.
*/
void EarthDomainDataLoader::initViewport(GameGUI *gui, map<wstring,wstring> *properties)
{
	// AND NOW SPECIFY THE VIEWPORT SIZE AND LOCATION. NOTE THAT IN THIS EXAMPLE,
	// WE ARE PUTTING A TOOLBAR WITH A BUTTON ACCROSS THE NORTH OF THE APPLICATION.
	// THAT TOOLBAR HAS A HEIGHT OF 64 PIXELS, SO WE'LL MAKE THAT THE OFFSET FOR
	// THE VIEWPORT IN THE Y AXIS
	Viewport *viewport = gui->getViewport();

	int viewportOffsetX, viewportOffsetY, screenWidth, screenHeight;
	wstring viewportOffsetXProp = (*properties)[W_VIEWPORT_OFFSET_X];
	wstring viewportOffsetYProp = (*properties)[W_VIEWPORT_OFFSET_Y];
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(viewportOffsetXProp) >> viewportOffsetX;
	wstringstream(viewportOffsetYProp) >> viewportOffsetY;
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;
	int viewportWidth = screenWidth - viewportOffsetX;
	int viewportHeight = screenHeight - viewportOffsetY;
	viewport->setViewportWidth(viewportWidth);
	viewport->setViewportHeight(viewportHeight);
	viewport->setViewportOffsetX(viewportOffsetX);
	viewport->setViewportOffsetY(viewportOffsetY);
}
