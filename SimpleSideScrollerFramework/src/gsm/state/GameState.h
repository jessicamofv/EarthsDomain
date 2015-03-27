#pragma once

/**
	The GameState dictates how to handle user input with regards to 
	processing GUI interactions. Each state potentially represents
	a different GUIScreen.
**/
enum GameState
{
	// NOTE THAT AS IS, ONLY THE TOP 5 GAME STATES ARE ACTUALLY
	// BEING USED. THE REST ARE INCLUDED AS EXAMPLES OF WHAT 
	// STATES MAY BE NEEDED, WHICH YOU MAY CHOOSE TO USE IF YOU LIKE

	// AT GAME APP STARTUP, WE CAN DISPLAY A GAME WELCOME/SPLASH SCREEN,
	// WHICH WILL GO RIGHT TO THE MAIN MENU AT FIRST KEY PRESS OR
	// MOUSE BUTTON PRESS
	GS_SPLASH_SCREEN,

	// AFTER THE SPLASH SCREEN, THE PLAYER WOULD GO TO THE MAIN MENU, WHICH
	// HAS ITS OWN CONTROLS. FROM THERE WE COULD TRANSITION TO OTHER
	// MENUS OR TO ACTUALLY STARTING THE GAME
	GS_MAIN_MENU,

	// Testing Purposes
	GS_TEST_SCREEN,//WB3 TESTING

	// AT LEVEL STARTUP, WHICH MAY BE WHEN WE FIRST START PLAYING
	// FROM THE MAIN MENU, OR MOVING FROM ONE LEVEL TO ANOTHER. NOTE
	// WE MAY WISH TO DISPLAY A LEVEL WELCOME SCREEN AS WELL, WHICH
	// THEN WOULD TRANSITION TO IN_PROGRESS
	GS_STARTING_LEVEL,

	// WHILE THE GAME IS NOT OVER AND THE LOGIC NEEDS TO BE PROCESSED AND 
	// THE GAME WORLD NEEDS NO BE RENDERED, THE GAME WILL BE IN THIS STATE
	GS_GAME_IN_PROGRESS,

	// WHEN THE GAME APPLICATION IS DONE. CHANGING TO THIS STATE CAUSES
	// THE ENTIRE APPLICATION TO CLOSE
	GS_EXIT_GAME,

	// NOTE THAT THE REST OF THE STATES BELOW ARE NOT CURRENTLY IN USE,
	// BUT COULD BE USEFUL IN YOUR OWN IMPLEMENTATION

	// THERE MAY BE MORE MENUS THAN JUST THE MAIN MENU
	GS_MENU_HELP_MENU,
	GS_MENU_ABOUT_MENU,
	GS_MENU_CONTROLS_MENU,

	// THESE ARE MID-LEVEL GAME PLAYING STATES. NONE OF THEM WOULD PROCESS
	// GAME LOGIC, BUT YOU MAY WISH TO RENDER THE CURRENT GAME WITH A
	// GUI OVERLAYED ON TOP
	GS_PAUSED,
	GS_GAME_OVER,
	GS_IN_GAME_HELP,
	GS_IN_GAME_ABOUT,
	GS_IN_GAME_CONTROLS,

	// WHEN A LEVEL IS CLEARED AND THE PLAYER WANTS TO MOVE ON, OR IF
	// A PLAYER WISHES TO GO BACK TO THE MAIN MENU, WE MAY NEED TO UNLOAD ALL
	// THE ARTWORK THE CURRENT LEVEL, WHICH IS WHAT THIS STATE IS FOR
	GS_UNLOADING_LEVEL,

	// WHEN A GAME APP IS TO CLOSE, WE'LL NEED TO UNLOAD GUI ARTWORK
	GS_UNLOADING_GAME,

	// For going to the upgrade shop
	GS_UPGRADE_SHOP,
};