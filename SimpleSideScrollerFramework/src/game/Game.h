/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	Game.h

	The class is the central object of the game
	application. It plays two important roles:

	1) It manages all major game objects (Game...), which
	essentially manage the game data and communicates with
	external technologies like graphics cards and input
	devices. The objects can be accessed via inlined public
	methods, i.e. getGraphics(), getInput(), getTimer(), etc.

	2) It runs the game loop, calling the appropriate
	methods in the other major objects as needed. The
	runGameLoop method iterates once per frame, invoking
	all necessary methods needed each frame to run the game.

	NOTE: I have deliberately avoided making this class 
	technology specific. I would like to be able to change
	the way the graphics are rendered (i.e. DirectX or OpenGL)
	if I want to without having to change this or most other
	classes.
*/

#pragma once

// PREPROCESSOR INCLUDE STATEMENTS
#include "stdafx.h"
#include "src\gsm\state\GameState.h"
#include <Box2D/Box2D.h>
// bm4 add
#include <windows.h>
#include <xact3.h>
#include "XACT3Audio.h"

// FORWARD DECLARATIONS OF CLASSES USED BY GAME
class GameDataLoader;
class GameGraphics;
class GameInput;
class GameOS;
class Physics;
class GameTimer;
class GameStateManager;
class GameGUI;
class GameText;

static const float PI = 3.1415926535897932384626433f;

class Game
{
private:
	// THE GameStateManager DEALS WITH ALL THE
	// GAME-PLAY AND GAME-WORLD STUFF, LIKE AI,
	// PHYSICS, AND GAME WORLD CONSTRUCTION. IT
	// ALSO KNOWS THE CURRENT GAME STATE
	GameStateManager	*gsm;

	// MANAGES ALL THE GUIS
	GameGUI				*gui;

	// MANAGES TEXT FOR RENDERING AND FILE I/O
	GameText			*text;

	// THESE GAME OBJECTS ALL REQUIRE CUSTOM DEFINITIONS, EITHER
	// BECAUSE THEY DEAL WITH PLATFORM-SPECIFIC THINGS, OR GAME-
	// SPECIFIC THINGS
	GameDataLoader		*dataLoader;
	GameGraphics		*graphics;
	GameInput			*input;
	GameOS				*os;
	GameTimer			*timer;

	// THIS WILL KEEP TRACK OF THE NAME OF THE LEVEL FILE
	// THAT IS CURRENTLY BEING USED
	wstring				currentLevelFileName;

	// i added this
	// create box2d world
	b2World *ourWorld;

	// bm3 AUDIO add
	// keep track of level in order to
	// know which music to play
	int level;

	// bm4 add
	stXACTAudio audioBanks_;
	IXACT3Engine* soundEngine_;

	// upgrades add
	int numHealthUpgrades;
	int numAttackSpeedUpgrades;
	int numAttackDamageUpgrades;
	int numMoveSpeedUpgrades;
	int numLivesUpgrades;

	// upgrades add
	int priceHealth;
	int priceAttackSpeed;
	int priceAttackDamage;
	int priceMoveSpeed;
	int priceLives;

public:
	// INLINED ACCESSOR METHODS - THE REAL THINGS
	GameStateManager*	getGSM()				{ return gsm;								}
	GameGUI*			getGUI()				{ return gui;								}
	GameText*			getText()				{ return text;								}

	// INLINED ACCESSOR METHODS - ACTUALLY SUB-CLASSES
	GameDataLoader*		getDataLoader()			{ return dataLoader;						}
	GameGraphics*		getGraphics()			{ return graphics;							}
	GameInput*			getInput()				{ return input;								}
	GameOS*				getOS()					{ return os;								}
	GameTimer*			getTimer()				{ return timer;								}

	// AND FOR GETTING THE NAME OF THE FILE USED FOR LOADING THIS LEVEL
	wstring				getCurrentLevelFileName()	{ return currentLevelFileName;			}

	// i added this
	b2World* getOurWorld() { return ourWorld; }

	// bm3 AUDIO add
	int getLevel() { return level; }

	// bm4 add
	stXACTAudio getAudioBanks() { return audioBanks_; }
	IXACT3Engine* getSoundEngine() { return soundEngine_; }

	// upgrades add
	int getNumHealthUpgrades() { return numHealthUpgrades; }
	int getNumAttackSpeedUpgrades() { return numAttackSpeedUpgrades; }
	int getNumAttackDamageUpgrades() { return numAttackDamageUpgrades; }
	int getNumMoveSpeedUpgrades() { return numMoveSpeedUpgrades; }
	int getNumLivesUpgrades() { return numLivesUpgrades; }

	// upgrades add
	int getPriceHealth() { return priceHealth; }
	int getPriceAttackSpeed() { return priceAttackSpeed; }
	int getPriceAttackDamage() { return priceAttackDamage; }
	int getPriceMoveSpeed() { return priceMoveSpeed; }
	int getPriceLives() { return priceLives; }

	// INLINED MUTATOR METHODS
	void	setDataLoader(GameDataLoader *initDL) { dataLoader = initDL; }
	void	setCurrentLevelFileName(wstring initCurrentLevelFileName) { currentLevelFileName = initCurrentLevelFileName; }
	// bm3 AUDIO add
	void setLevel(int initLevel) { level = initLevel; }
	
	// upgrades add
	void setNumHealthUpgrades(int initNumHealthUpgrades) { numHealthUpgrades = initNumHealthUpgrades; }
	void setNumAttackSpeedUpgrades(int initNumAttackSpeedUpgrades) { numAttackSpeedUpgrades = initNumAttackSpeedUpgrades; }
	void setNumAttackDamageUpgrades(int initNumAttackDamageUpgrades) { numAttackDamageUpgrades = initNumAttackDamageUpgrades; }
	void setNumMoveSpeedUpgrades(int initNumMoveSpeedUpgrades) { numMoveSpeedUpgrades = initNumMoveSpeedUpgrades; }
	void setNumLivesUpgrades(int initNumLivesUpgrades) { numLivesUpgrades = initNumLivesUpgrades; }

	// upgrades add
	void setPriceHealth(int initPriceHealth) { priceHealth = initPriceHealth; }
	void setPriceAttackSpeed(int initPriceAttackSpeed) { priceAttackSpeed = initPriceAttackSpeed; }
	void setPriceAttackDamage(int initPriceAttackDamage) { priceAttackDamage = initPriceAttackDamage; }
	void setPriceMoveSpeed(int initPriceMoveSpeed) { priceMoveSpeed = initPriceMoveSpeed; }
	void setPriceLives(int initPriceLives) { priceLives = initPriceLives; }

	// METHODS DEFINED IN Game.cpp
	Game();
	~Game();
	void	initPlatformPlugins(	GameGraphics *initGraphics, 
									GameInput *initInput, 
									GameOS *initOS,
									GameTimer *initTimer);
	void	processGameData();
	void	quitApp();
	void	quitGame();
	void	reloadAllDevices();
	void	runGameLoop();
	void	shutdown();
	void	startGame();
	void	goToControls();
	void	goToAbout();
	// bm4 add
	bool	LoadContent();
	void	UnloadContent();

	// final benchmark
	// to delete bodies after each level
	// change
	void	deleteBodies();
};