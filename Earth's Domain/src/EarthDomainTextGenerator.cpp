/*
*****Earth Domain Game*****
	Author: Laugh Out Loud

		Jeffrey Lin
		Jessica Mortellaro
		Jia Hao Wang

		CSE 380 

	EarthDomainTextGenerator.cpp

	See EarthDomainTextGenerator.h for a class description.
*/

// text add
#include "stdafx.h"
#include "src\EarthDomainGame.h"
#include "src\EarthDomainTextGenerator.h"
#include "src\game\Game.h"
#include "src\graphics\GameGraphics.h"
#include "src\text\GameText.h"
#include "src\timer\GameTimer.h"
#include "src\PlatformPlugins\WindowsPlugin\WindowsTimer.h"
#include "src\gsm\physics\PhysicalProperties.h"

static const wstring	W_TARGET_FPS_TEXT = L"TARGET FPS: ";
static const int		W_TARGET_FPS_X	= 350;
static const int		W_TARGET_FPS_Y	= 50;

/*
	appendTargetFPS - this method gets and appends the target frame rate to
	the text we are generating.
*/
void EarthDomainTextGenerator::appendLWC(Game *game)
{
	/*
	// WE'LL BUILD OUR WIDE STRING USING A WIDE STRING STREAM
	wstringstream wss;
	WindowsTimer *timer = (WindowsTimer*)game->getTimer();

	// BUILD THE WIDE STRING
	textToGenerate.append(W_TARGET_FPS_TEXT);
	wss << timer->getTargetFPS();
	textToGenerate.append(wss.str());
	*/
	
	PhysicalProperties *playerPP = game->getGSM()->getSpriteManager()->getPlayer()->getPhysicalProperties();
	
	wstringstream wss1;
	wss1.clear();
	textToGenerateLevel.append(L"Level: ");
	wss1 << playerPP->getLevel();
	textToGenerateLevel.append(wss1.str());
	wstringstream wss2;
	wss2.clear();
	textToGenerateWave.append(L"Wave: ");
	wss2 << playerPP->getWave();
	textToGenerateWave.append(wss2.str());
	wstringstream wss3;
	wss3.clear();
	textToGenerateCurrency.append(L"Currency: ");
	wss3 << playerPP->getCurrency();
	textToGenerateCurrency.append(wss3.str());
	// upgrades add
	// AND THEN HAND IT TO THE TEXT MANAGER, SPECIFYING WHERE IT SHOULD BE RENDERED
	GameText *text = game->getText();

	text->addText(&textToGenerateLevel, 700, 10, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerateWave, 700, 22, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerateCurrency, 700, 34, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());

}

// upgrades add
void EarthDomainTextGenerator::appendUpgrades(Game *game)
{
	wstringstream wss1;
	textToGeneratePriceH.append(L"Price: $");
	wss1 << game->getPriceHealth();
	textToGeneratePriceH.append(wss1.str());
	wstringstream wss2;
	textToGeneratePriceAS.append(L"Price: $");
	wss2 << game->getPriceAttackSpeed();
	textToGeneratePriceAS.append(wss2.str());
	wstringstream wss3;
	textToGeneratePriceAD.append(L"Price: $");
	wss3 << game->getPriceAttackDamage();
	textToGeneratePriceAD.append(wss3.str());
	wstringstream wss4;
	textToGeneratePriceMS.append(L"Price: $");
	wss4 << game->getPriceMoveSpeed();
	textToGeneratePriceMS.append(wss4.str());
	wstringstream wss5;
	textToGeneratePriceL.append(L"Price: $");
	wss5 << game->getPriceLives();
	textToGeneratePriceL.append(wss5.str());

	wstringstream wss6;
	textToGenerateHealth.append(L"Upgrade Number: ");
	wss6 << game->getNumHealthUpgrades();
	textToGenerateHealth.append(wss6.str());
	wstringstream wss7;
	textToGenerateAttackSpeed.append(L"Upgrade Number: ");
	wss7 << game->getNumAttackSpeedUpgrades();
	textToGenerateAttackSpeed.append(wss7.str());
	wstringstream wss8;
	textToGenerateAttackDamage.append(L"Upgrade Number: ");
	wss8 << game->getNumAttackDamageUpgrades();
	textToGenerateAttackDamage.append(wss8.str());
	wstringstream wss9;
	textToGenerateMoveSpeed.append(L"Upgrade Number: ");
	wss9 << game->getNumMoveSpeedUpgrades();
	textToGenerateMoveSpeed.append(wss9.str());
	wstringstream wss10;
	textToGenerateLives.append(L"Upgrade Number: ");
	wss10 << game->getNumLivesUpgrades();
	textToGenerateLives.append(wss10.str());

	// AND THEN HAND IT TO THE TEXT MANAGER, SPECIFYING WHERE IT SHOULD BE RENDERED
	GameText *text = game->getText();

	text->addText(&textToGeneratePriceH, 20, 320, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGeneratePriceAD, 210, 320, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGeneratePriceAS, 420, 320, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGeneratePriceMS, 680, 320, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGeneratePriceL, 895, 320, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());

	text->addText(&textToGenerateHealth, 0, 541, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerateAttackDamage, 190, 541, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerateAttackSpeed, 400, 541, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerateMoveSpeed, 660, 541, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerateLives, 854, 541, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
}

/*
	initText - Provides an example of how to render text to our screen every frame,
	allowing for the text to continually change. This method adds a text object
	to the text manager (GameText), which allows it to be updated each frame. This
	method should be called only once for each object.
*/
void EarthDomainTextGenerator::initText(Game *game)
{
	// upgrades add
	// FIRST UPDATE THE TEXT THIS GENERATOR IS USING
	appendLWC(game);

	// upgrades add
	/*
	// AND THEN HAND IT TO THE TEXT MANAGER, SPECIFYING WHERE IT SHOULD BE RENDERED
	GameText *text = game->getText();
	text->addText(&textToGenerateLevel, 700, 10, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerateWave, 700, 22, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerateCurrency, 700, 34, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	*/
}

/*
	updateText - updates the text. Note that the text must already have been added
	to the text manager via the initText method. Also not that there should be a
	separate TextGenerator for each line of text we wish to render.
*/
void EarthDomainTextGenerator::updateText(Game *game)
{
	// THE TEXT MANAGER (GameText) HAS A POINTER TO OUR TEXT, SO WE CAN
	// SIMPLY CLEAR IT OUT OF OLD CHARACTER DATA AND FILL IT IN WITH
	// WHAT WE WANT.

	textToGenerateLevel.clear();
	textToGenerateWave.clear();
	textToGenerateCurrency.clear();
	// upgrades add
	textToGenerateHealth.clear();
	textToGenerateAttackSpeed.clear();
	textToGenerateAttackDamage.clear();
	textToGenerateMoveSpeed.clear();
	textToGenerateLives.clear();

	// upgrades add
	textToGeneratePriceH.clear();
	textToGeneratePriceAS.clear();
	textToGeneratePriceAD.clear();
	textToGeneratePriceMS.clear();
	textToGeneratePriceL.clear();
	

	if (game->getGSM()->getCurrentGameState() != GS_UPGRADE_SHOP)
	{
		// upgrades add
		appendLWC(game);
	}

	// upgrades add
	if (game->getGSM()->getCurrentGameState() == GS_UPGRADE_SHOP)
	{
		appendUpgrades(game);
	}
}