/*	
*****Earth Domain Game*****
	Author: Laugh Out Loud

		Jeffrey Lin
		Jessica Mortellaro
		Jia Hao Wang

		CSE 380 

	EarthDomainTextGenerator.h

	This class is a custom text generator for the EmptyGame
	application. Basically, by defining the initText and updateText
	methods, we can have it display whatever text we like.
*/

// text add
#pragma once
#include "stdafx.h"
#include "src\text\TextGenerator.h"

class EarthDomainTextGenerator : public TextGenerator
{
private:
	// THIS IS THE TEXT THIS OBJECT WILL UPDATE EACH FRAME
	wstring textToGenerateLevel;
	wstring textToGenerateWave;
	wstring textToGenerateCurrency;

	// upgrades add
	wstring textToGenerateHealth;
	wstring textToGenerateAttackSpeed;
	wstring textToGenerateAttackDamage;
	wstring textToGenerateMoveSpeed;
	wstring textToGenerateLives;

	// upgrades add
	wstring textToGeneratePriceH;
	wstring textToGeneratePriceAS;
	wstring textToGeneratePriceAD;
	wstring textToGeneratePriceMS;
	wstring textToGeneratePriceL;

public:
	// NOTHING TO INITIALIZE OR DESTROY
	EarthDomainTextGenerator()	{}
	~EarthDomainTextGenerator()	{}

	// DEFINED IN EarthDomainTextGenerator.cpp
	// upgrades add
	void appendLWC(Game *game);
	// upgrades add
	void appendUpgrades(Game *game);
	void initText(Game *game);
	void updateText(Game *game);
};