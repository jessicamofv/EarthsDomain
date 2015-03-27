#pragma once
#include "stdafx.h"

/*
	EarthDomainGame.h

	This file contains setup data for making the EarthDomain game. Note that nearly
	all of this data would better serve us if loaded from files.
*/

// HERE IS THE EarthDomain GAME SETUP/INIT FILE. EVERYTHING WOULD START FROM HERE
static const wstring	W_LEVEL_1				= L"data/EarthDomainLevel1.txt";
static const wstring	W_INIT_FILE				= L"data/EarthDomainInit.txt";
static const wstring	W_GUI_INIT_FILE			= L"data/EarthDomainGUI.txt";

static const string		W_DEBUG_FILE			= "DebugOutput.txt";


// HERE ARE THE GAME PROPERTIES WE ARE LOADING FROM FROM THE SETUP FILE
static const wstring	W_TITLE					= L"TITLE";
static const wstring	W_SCREEN_WIDTH			= L"SCREEN_WIDTH";
static const wstring	W_SCREEN_HEIGHT			= L"SCREEN_HEIGHT";
static const wstring	W_USE_FULLSCREEN_MODE	= L"USE_FULLSCREEN_MODE";
static const wstring	W_TEXT_FONT_SIZE		= L"TEXT_FONT_SIZE";
static const wstring	W_VIEWPORT_OFFSET_X		= L"VIEWPORT_OFFSET_X";
static const wstring	W_VIEWPORT_OFFSET_Y		= L"VIEWPORT_OFFSET_Y";
static const wstring	W_FONT_COLOR_RED		= L"FONT_COLOR_RED";
static const wstring	W_FONT_COLOR_GREEN		= L"FONT_COLOR_GREEN";
static const wstring	W_FONT_COLOR_BLUE		= L"FONT_COLOR_BLUE";
static const wstring	W_COLOR_KEY_RED			= L"COLOR_KEY_RED";
static const wstring	W_COLOR_KEY_GREEN		= L"COLOR_KEY_GREEN";
static const wstring	W_COLOR_KEY_BLUE		= L"COLOR_KEY_BLUE";

// CONSTANTS FOR ARTWORK - NOTE, THIS SHOULD REALLY BE LOADED FROM A FILE
static const wstring	W_GO_TO_MM_COMMAND		= L"Go To Main Menu";
static const wstring	W_GO_TO_GAME_COMMAND	= L"Go Back To Game";
static const wstring	W_START_COMMAND			= L"Start";
static const wstring	W_EXIT_COMMAND			= L"Exit";
static const wstring	W_QUIT_COMMAND			= L"Quit";
static const wstring	W_ABOUT_COMMAND			= L"About";
static const wstring	W_CONTROLS_COMMAND		= L"Controls";
static const wstring	W_UPGRADE_HEALTH_COMMAND = L"Upgrade Health";
static const wstring	W_UPGRADE_ATTACK_SPEED_COMMAND = L"Upgrade Attack Speed";
static const wstring	W_UPGRADE_ATTACK_DAMAGE_COMMAND = L"Upgrade Attack Damage";
static const wstring	W_UPGRADE_MOVE_SPEED_COMMAND = L"Upgrade Move Speed";
// screens add
static const wstring	W_BACK_TO_MM_COMMAND	= L"Back to Main Menu";
static const wstring	W_SHOP_COMMAND			= L"Shop";
static const wstring	W_PLAYER_CURSOR_PATH	= L"data/cursor/player_cursor.png";
static const wstring	W_ENEMY_CURSOR_PATH		= L"data/cursor/enemy_cursor.png";
static const wstring	W_SPLASH_SCREEN_PATH	= L"data/overlays/Earth's_Domain_splash_screen_overlay.png";
static const wstring	W_SHOP_OVERLAY_PATH		= L"data/overlays/Earth's_Domain_upgrade_shop_overlay.png";
static const wstring	W_MAIN_MENU_PATH		= L"data/overlays/Earth's_Domain_main_menu_overlay.png";
static const wstring	W_UPGRADE_MENU_PATH		= L"data/overlays/Earth's_Domain_upgrade_menu_overlay.png";
static const wstring	W_GO_TO_GAME_PATH		= L"data/buttons/go_to_game.png";
static const wstring	W_START_IMAGE_PATH		= L"data/buttons/start_game.png";
static const wstring	W_START_IMAGE_MO_PATH	= L"data/buttons/start_game_mo.png";
static const wstring	W_EXIT_IMAGE_PATH		= L"data/buttons/exit_game.png";
static const wstring	W_EXIT_IMAGE_MO_PATH	= L"data/buttons/exit_game_mo.png";
static const wstring	W_QUIT_IMAGE_PATH		= L"data/buttons/quit.png";
static const wstring	W_QUIT_IMAGE_MO_PATH	= L"data/buttons/quit_mo.png";
static const wstring	W_ABOUT_IMAGE_PATH		= L"data/buttons/about.png";
static const wstring	W_ABOUT_IMAGE_MO_PATH	= L"data/buttons/about_mo.png";
static const wstring	W_CONTROLS_IMAGE_PATH	= L"data/buttons/controls.png";
static const wstring	W_CONTROLS_IMAGE_MO_PATH= L"data/buttons/controls_mo.png";
// screens add
static const wstring    W_CONTROLS_SCREEN_PATH = L"data/overlays/Earth's_Domain_controls_screen_overlay.png";
static const wstring	W_ABOUT_SCREEN_PATH	   = L"data/overlays/Earth's_Domain_about_screen_overlay.png";
// game over add
static const wstring	W_GAME_OVER_SCREEN_PATH = L"data/overlays/Earth's_Domain_game_over_screen_overlay.png";
static const wstring	W_BACK_TO_MM_IMAGE_PATH = L"data/buttons/back_to_main_menu.png";
static const wstring	W_BACK_TO_MM_IMAGE_MO_PATH = L"data/buttons/back_to_main_menu_mo.png";
static const wstring	W_BACK_TO_MM_2_IMAGE_PATH = L"data/buttons/back_to_main_menu_2.png";
static const wstring	W_BACK_TO_MM_2_IMAGE_MO_PATH = L"data/buttons/back_to_main_menu_2_mo.png";
static const wstring	W_UPGRADE_IMAGE_PATH	= L"data/buttons/upgrade_mo.png";
static const wstring	W_UPGRADE_IMAGE_MO_PATH = L"data/buttons/upgrade.png";
static const wstring	W_HEALTH_UPGRADE_PATH	= L"data/buttons/health_upgrade.png";
static const wstring	W_ATTACK_SPEED_UPGRADE_PATH	= L"data/buttons/attack_speed_upgrade.png";
static const wstring	W_MOVEMENT_UPGRADE_PATH	= L"data/buttons/movement_upgrade.png";
static const wstring	W_DAMAGE_UPGRADE_PATH	= L"data/buttons/damage_upgrade.png";
static const wstring	W_BUY_PATH				= L"data/buttons/buy.png";
static const wstring	W_LIVES_UPGRADE_PATH	= L"data/buttons/lives_upgrade.png";
static const wstring	LIVES_2_PATH			= L"data/sprite_types/Lives/Lives_2.png";

// FOR OUR THE PLAYER
static const wstring	SPRITE_TYPES_DIR = L"data/sprite_types/";
static const wstring	SPRITE_TYPES_LIST = SPRITE_TYPES_DIR + L"sprite_type_list.xml";


// EXAMPLE LEVEL DATA FOR THE HARD-CODED loadLevelExample.
// WE'LL CHANGE THE WAY LEVELS GET LOADED IN HW 2

// FOR BACKGROUND TILES
static const wstring	MOUNTAIN_IMAGE_PATH	= L"data/tiles/mountain.png";
static const wstring	GRASS_IMAGE_PATH	= L"data/tiles/grass.png";
static const wstring	WATER_IMAGE_PATH	= L"data/tiles/water.png";
static const wstring	CLOUD_0_IMAGE_PATH	= L"data/background/cloud_0.PNG";
static const wstring	CLOUD_1_IMAGE_PATH	= L"data/background/cloud_1.PNG";
static const wstring	CLOUD_2_IMAGE_PATH	= L"data/background/cloud_2.PNG";
static const wstring	CLOUD_3_IMAGE_PATH	= L"data/background/cloud_3.PNG";
static const wstring	CLOUD_4_IMAGE_PATH	= L"data/background/cloud_4.PNG";
static const wstring	CLOUD_5_IMAGE_PATH	= L"data/background/cloud_5.PNG";
static const wstring	CLOUD_6_IMAGE_PATH	= L"data/background/cloud_6.PNG";

// FOR OUR SPRITE
static const wstring	BACKGROUND_PATH			= L"data/Formatting/Background.png";
static const wstring	BULLET_1_PATH			= L"data/sprite_types/bullet_1/bullet_1.png";
static const wstring	GUI_TITLE_PATH			= L"data/Formatting/GUI_Title.png";
static const wstring	INFO_PATH				= L"data/Formatting/info.png";
static const wstring	IDLE_STATE				= L"IDLE_STATE";
static const wstring	IDLE_STATE_BULLETS		= L"IDLE_STATE_BULLETS";
static const int		ANIM_SPEED				= 6;

// FOR OUR WORLD
static const int		NUM_COLUMNS = 16;
// scrolling add
static const int		NUM_ROWS = 55;
static const int		TILE_WIDTH = 64;
static const int		TILE_HEIGHT = 64;
static const int		Z_LAYER = 0;
