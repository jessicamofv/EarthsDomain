/*
*****Earth Domain Game*****
	Author: Laugh Out Loud

		Jeffrey Lin
		Jessica Mortellaro
		Jia Hao Wang

		CSE 380 

	EarthDomainButtonEventHandler.cpp

	See EarthDomainButtonEventHandler.h for a class description.
*/

#include "stdafx.h"
#include "src\EarthDomainGame.h"
#include "src\EarthDomainButtonEventHandler.h"
#include "src\game\Game.h"
#include "src\gsm\state\GameStateManager.h"


void EarthDomainButtonEventHandler::handleButtonEvents(	Game *game, 
													wstring command)
{

	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	PhysicalProperties *pp = player->getPhysicalProperties();

	// THE USER PRESSED THE Exit BUTTON ON THE MAIN MENU,
	// SO LET'S SHUTDOWN THE ENTIRE APPLICATION
	if (command.compare(W_EXIT_COMMAND) == 0)
	{
		game->shutdown();
	}
	// THE USER PRESSED THE MOUSE BUTTON ON THE SPLASH
	// SCREEN, SO LET'S GO TO THE MAIN MENU
	else if (command.compare(W_GO_TO_MM_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToMainMenu();
	}
	// THE USER PRESSED THE Start BUTTON ON THE MAIN MENU,
	// SO LET'S START THE GAME FROM THE FIRST LEVEL
	else if (command.compare(W_START_COMMAND) == 0)
	{
		game->setCurrentLevelFileName(W_LEVEL_1);
		game->startGame();
	}

	// THE USER PRESSED THE CONTROL BUTTON ON THE MAIN MENU
	else if (command.compare(W_CONTROLS_COMMAND) == 0)
	{
		// screens add
		GameStateManager *gsm = game->getGSM();
		gsm->goToControlsScreen();
		// game->goToControls();
	}

	// THE USER PRESSED THE ABOUT BUTTON ON THE MAIN MENU
	else if (command.compare(W_ABOUT_COMMAND) == 0)
	{
		// screens add
		GameStateManager *gsm = game->getGSM();
		gsm->goToAboutScreen();
		// game->goToAbout();
	}

	// screens add
	else if (command.compare(W_BACK_TO_MM_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToMainMenu();
	}

	// THE USER HAS PRESSED THE SHOP BUTTON
	else if (command.compare(W_SHOP_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToUpgradeShop();
	}
	else if(command.compare(W_GO_TO_GAME_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToGame();
	}
	else if(command.compare(W_UPGRADE_HEALTH_COMMAND) == 0)
	{
		if(pp->getMaxHealth() == 5)
		{
			if(pp->getCurrency() >= 100)
			{
				pp->setCurrentHealth(pp->getcurrentHealth()+1);
				pp->setMaxHealth(6);
				pp->setCurrency(pp->getCurrency()-100);
				// upgrades add
				game->setNumHealthUpgrades(game->getNumHealthUpgrades() + 1);
				// upgrades add
				game->setPriceHealth(game->getPriceHealth() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMaxHealth() == 6)
		{
			if(pp->getCurrency() >= 200)
			{
				pp->setCurrentHealth(pp->getcurrentHealth()+1);
				pp->setMaxHealth(7);
				pp->setCurrency(pp->getCurrency()-200);
				// upgrades add
				game->setNumHealthUpgrades(game->getNumHealthUpgrades() + 1);
				// upgrades add
				game->setPriceHealth(game->getPriceHealth() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMaxHealth() == 7)
		{
			if(pp->getCurrency() >= 300)
			{
				pp->setCurrentHealth(pp->getcurrentHealth()+1);
				pp->setMaxHealth(8);
				pp->setCurrency(pp->getCurrency()-300);
				// upgrades add
				game->setNumHealthUpgrades(game->getNumHealthUpgrades() + 1);
				// upgrades add
				game->setPriceHealth(game->getPriceHealth() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMaxHealth() == 8)
		{
			if(pp->getCurrency() >= 400)
			{
				pp->setCurrentHealth(pp->getcurrentHealth()+1);
				pp->setMaxHealth(9);
				pp->setCurrency(pp->getCurrency()-400);
				// upgrades add
				game->setNumHealthUpgrades(game->getNumHealthUpgrades() + 1);
				// upgrades add
				game->setPriceHealth(game->getPriceHealth() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMaxHealth() == 9)
		{
			if(pp->getCurrency() >= 500)
			{
				pp->setCurrentHealth(pp->getcurrentHealth()+1);
				pp->setMaxHealth(10);
				pp->setCurrency(pp->getCurrency()-500);
				// upgrades add
				game->setNumHealthUpgrades(game->getNumHealthUpgrades() + 1);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMaxHealth() == 10)
		{
			MessageBoxA(NULL, "Upgrade failed. You've achieved the maximum upgrade.","Upgrade Failed", 0);
		}
	}
	else if(command.compare(W_UPGRADE_ATTACK_SPEED_COMMAND) == 0)
	{
		if(pp->getAttackSpeed() == 1)
		{
			if(pp->getCurrency() >= 100)
			{
				pp->setAttackSpeed(2);
				pp->setCurrency(pp->getCurrency()-100);
				// upgrades add
				game->setNumAttackSpeedUpgrades(game->getNumAttackSpeedUpgrades() + 1);
				// upgrades add
				game->setPriceAttackSpeed(game->getPriceAttackSpeed() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getAttackSpeed() == 2)
		{
			if(pp->getCurrency() >= 200)
			{
				pp->setAttackSpeed(3);
				pp->setCurrency(pp->getCurrency()-200);
				// upgrades add
				game->setNumAttackSpeedUpgrades(game->getNumAttackSpeedUpgrades() + 1);
				// upgrades add
				game->setPriceAttackSpeed(game->getPriceAttackSpeed() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getAttackSpeed() == 3)
		{
			if(pp->getCurrency() >= 300)
			{
				pp->setAttackSpeed(4);
				pp->setCurrency(pp->getCurrency()-300);
				// upgrades add
				game->setNumAttackSpeedUpgrades(game->getNumAttackSpeedUpgrades() + 1);
				// upgrades add
				game->setPriceAttackSpeed(game->getPriceAttackSpeed() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getAttackSpeed() == 4)
		{
			if(pp->getCurrency() >= 400)
			{
				pp->setAttackSpeed(5);
				pp->setCurrency(pp->getCurrency()-400);
				// upgrades add
				game->setNumAttackSpeedUpgrades(game->getNumAttackSpeedUpgrades() + 1);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getAttackSpeed() == 5)
		{
			MessageBoxA(NULL, "Upgrade failed. You've achieved the maximum upgrade.","Upgrade Failed", 0);
		}
	}
	else if(command.compare(W_UPGRADE_ATTACK_DAMAGE_COMMAND) == 0)
	{
		if(pp->getAttackDamage() == 1)
		{
			if(pp->getCurrency() >= 100)
			{
				pp->setAttackDamage(2);
				pp->setCurrency(pp->getCurrency()-100);
				// upgrades add
				game->setNumAttackDamageUpgrades(game->getNumAttackDamageUpgrades() + 1);
				// upgrades add
				game->setPriceAttackDamage(game->getPriceAttackDamage() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getAttackDamage() == 2)
		{
			if(pp->getCurrency() >= 200)
			{
				pp->setAttackDamage(3);
				pp->setCurrency(pp->getCurrency()-200);
				// upgrades add
				game->setNumAttackDamageUpgrades(game->getNumAttackDamageUpgrades() + 1);
				// upgrades add
				game->setPriceAttackDamage(game->getPriceAttackDamage() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getAttackDamage() == 3)
		{
			if(pp->getCurrency() >= 300)
			{
				pp->setAttackDamage(4);
				pp->setCurrency(pp->getCurrency()-300);
				// upgrades add
				game->setNumAttackDamageUpgrades(game->getNumAttackDamageUpgrades() + 1);
				// upgrades add
				game->setPriceAttackDamage(game->getPriceAttackDamage() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getAttackDamage() == 4)
		{
			if(pp->getCurrency() >= 400)
			{
				pp->setAttackDamage(5);
				pp->setCurrency(pp->getCurrency()-400);
				// upgrades add
				game->setNumAttackDamageUpgrades(game->getNumAttackDamageUpgrades() + 1);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getAttackDamage() == 5)
		{
			MessageBoxA(NULL, "Upgrade failed. You've achieved the maximum upgrade.","Upgrade Failed", 0);
		}
	}
	else if(command.compare(W_UPGRADE_MOVE_SPEED_COMMAND) == 0)
	{
		if(pp->getMoveSpeed() == 1)
		{
			if(pp->getCurrency() >= 100)
			{
				pp->setMoveSpeed(2);
				pp->setCurrency(pp->getCurrency()-100);
				// upgrades add
				game->setNumMoveSpeedUpgrades(game->getNumMoveSpeedUpgrades() + 1);
				// upgrades add
				game->setPriceMoveSpeed(game->getPriceMoveSpeed() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMoveSpeed() == 2)
		{
			if(pp->getCurrency() >= 200)
			{
				pp->setMoveSpeed(3);
				pp->setCurrency(pp->getCurrency()-200);
				// upgrades add
				game->setNumMoveSpeedUpgrades(game->getNumMoveSpeedUpgrades() + 1);
				// upgrades add
				game->setPriceMoveSpeed(game->getPriceMoveSpeed() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMoveSpeed() == 3)
		{
			if(pp->getCurrency() >= 300)
			{
				pp->setMoveSpeed(4);
				pp->setCurrency(pp->getCurrency()-300);
				// upgrades add
				game->setNumMoveSpeedUpgrades(game->getNumMoveSpeedUpgrades() + 1);
				// upgrades add
				game->setPriceMoveSpeed(game->getPriceMoveSpeed() + 100);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMoveSpeed() == 4)
		{
			if(pp->getCurrency() >= 400)
			{
				pp->setMoveSpeed(5);
				pp->setCurrency(pp->getCurrency()-400);
				// upgrades add
				game->setNumMoveSpeedUpgrades(game->getNumMoveSpeedUpgrades() + 1);
			}
			else
			{
				MessageBoxA(NULL, "Upgrade failed. You don't have enough money for this upgrade.","Upgrade Failed", 0);
			}
		}
		else if(pp->getMoveSpeed() == 5)
		{
			MessageBoxA(NULL, "Upgrade failed. You've achieved the maximum upgrade.","Upgrade Failed", 0);
		}
	}
	// THE USER PRESSED THE Quit BUTTON ON THE IN-GAME MENU,
	// SO LET'S UNLOAD THE LEVEL AND RETURN TO THE MAIN MENU
	else if (command.compare(W_QUIT_COMMAND) == 0)
	{
		game->quitGame();
	}
}