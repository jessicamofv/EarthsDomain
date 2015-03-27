/*
*****Earth Domain Game*****
	Author: Laugh Out Loud

		Jeffrey Lin
		Jessica Mortellaro
		Jia Hao Wang

		CSE 380 
	EarthDomainDataLoader.h

	This class provides a custom importer for the EarthDomainGame to import
	game data, gui data, and world (i.e. level) data.
*/
#pragma once
#include "stdafx.h"
#include "src\dataLoader\GameDataLoader.h"
#include "src\game\Game.h"
#include "src\PlatformPlugins\DirectXPlugin\DirectXTextureManager.h"

class EarthDomainDataLoader : public GameDataLoader
{
private:
	// WE NEED THESE GUYS TO INIT OUR WINDOWS WINDOW
	HINSTANCE hInstance;
	int nCmdShow;

public:
	EarthDomainDataLoader()	{}
	~EarthDomainDataLoader()	{}

	// INLINED MUTATOR METHOD
	void initWinHandle(HINSTANCE initHInstance, int initNCmdShow)
	{
		hInstance = initHInstance;
		nCmdShow = initNCmdShow;
	}
	

	// THESE SHOULD BE LOADING DATA FROM FILES. THEY
	// ARE ALL DEFINED IN EarthDomainDataLoader.cpp
	void loadGame(Game *game, wstring gameInitFile);
	void loadGUI(Game *game, wstring guiInitFile);
	void loadWorld(Game *game, wstring levelInitFile);

	// THESE ARE HARD-CODED EXAMPLES OF GAME DATA LOADING
	void hardCodedLoadGUIExample(Game *game);

	// SOME HELPER METHODS FOR SETTING UP THE GAME
	void initColors(GameGraphics *graphics,	map<wstring,wstring> *properties);
	void initViewport(GameGUI *gui, map<wstring,wstring> *properties);
	
	// AND SOME HELPER METHODS FOR LOADING THE GUI
	void initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initSplashScreen(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager);
	void initMainMenu(GameGUI *gui,	DirectXTextureManager *guiTextureManager);
	void initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	// screens add
	void initControlsScreen( GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initAboutScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	// game over add
	void initGameOverScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initUpgradeShop(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager);//BM3
};