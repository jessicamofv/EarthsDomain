/*	
*****Earth Domain Game*****
	Author: Laugh Out Loud

		Jeffrey Lin
		Jessica Mortellaro
		Jia Hao Wang

		CSE 380 

	EarthDomainButtonEventHandler.h

	This is a custom button event handler. Each game can choose
	to use different buttons and respond differently to when
	buttons are pressed. This class will handle button presses for
	the EarthDomainGame following the ButtonEventHandler pattern.
*/

#pragma once
#include "stdafx.h"
#include "src\input\ButtonEventHandler.h"

class Game;

class EarthDomainButtonEventHandler: public ButtonEventHandler
{
public:
	// AS-IS, THIS CLASS HAS NO DATA, SO THERE IS NOTHING
	// TO INITIALIZE OR DESTROY
	EarthDomainButtonEventHandler()	{}
	~EarthDomainButtonEventHandler()	{}

	// DEFINED INSIDE EarthDomainButtonEventHandler.cpp
	void handleButtonEvents(Game *game, 
							wstring command);
};