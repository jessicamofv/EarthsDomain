/*	
*****Earth Domain Game*****
	Author: Laugh Out Loud

		Jeffrey Lin
		Jessica Mortellaro
		Jia Hao Wang

		CSE 380 

	EarthDomainKeyEventHandler.h

	This is a custom key event handler. Each game can choose
	to use different keyboard keys and respond differently to when
	they are pressed. This class will handle key presses for
	this particular game following the KeyEventHandler pattern.
*/

#pragma once
#include "stdafx.h"
#include "src\input\KeyEventHandler.h"
// bm3 AUDIO add
#include <windows.h>
#include <xact3.h>
#include "src\game\XACT3Audio.h"

class Game;

class EarthDomainKeyEventHandler : public KeyEventHandler
{
/*
// bm3 AUDIO add
private:
	stXACTAudio audioBanks_;
	IXACT3Engine* soundEngine_;
*/

public:
	/*// bm3 AUDIO add*/
	EarthDomainKeyEventHandler()		{}
	~EarthDomainKeyEventHandler()		{}
	void handleKeyEvents(Game *game);
	
	/*
	// bm3 AUDIO add
	bool LoadContent();
	void UnloadContent();
	*/
};