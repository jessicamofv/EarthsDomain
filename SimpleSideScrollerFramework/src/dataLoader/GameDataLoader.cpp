#include "stdafx.h"
#include "src\dataLoader\GameDataLoader.h"
#include "src\text\BufferedTextFileReader.h"

#include "src\game\Game.h"
#include "src\EarthDomainGame.h"
#include "src\gsm\world\TiledLayer.h"

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
#include "src\gsm\ai\lives.h"
#include "src\gsm\ai\max_health.h"
#include "src\gsm\sprite\AnimatedSpriteType.h"

/*
	loadGameProperties - Called only once, when the application starts, this method
	loads all the delimited properties into the map argument, which the calling
	method may then take and use to setup the game application.
*/
void GameDataLoader::loadGameProperties(	Game *game, 
											map<wstring, wstring> *properties,
											wstring gameInitFile)
{
	// OPEN THE READER AND LOAD IT WITH
	// THE CONTENTS OF gameInitFile
	BufferedTextFileReader reader;
	reader.initFile(gameInitFile);
	
	// NOW WE CAN READ IN ALL THE GAME DATA. NOTE THAT THE 
	// GAME DATA FILE WE ARE READING NEEDS TO BE IN THE
	// PROPER FORMAT, OBVIOUSLY
	wstring line;

	// LOAD ALL THE PROPERTIES
	while (reader.hasMoreLines())
	{
		line = reader.getNextLine();
		loadProperty(&line, properties);
	}
}

/*
	loadProperty - this method loads the line argument as a delimited
	name,value pair in to the 
*/
void GameDataLoader::loadProperty(	wstring *line,
									map<wstring,wstring> *properties)
{
	unsigned int delimiterIndex = line->find(DEFAULT_DELIMITER);
	wstring name = line->substr(0, delimiterIndex);
	wstring value = line->substr(delimiterIndex+1);
	(*properties)[name] = value;
}

void GameDataLoader::loadLevel(Game *game, int level)
{
	// final benchmark
	game->deleteBodies();

	// bm3 AUDIO add
	// set level so that it can be accessed
	// when determining which song to play
	game->setLevel(level);

	// FIRST SETUP THE GAME WORLD DIMENSIONS
	GameStateManager *gsm = game->getGSM();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *worldTextureManager = graphics->getWorldTextureManager();

	int backgroundID;
	int cloud_0ID;
	int cloud_1ID;
	int cloud_2ID;
	AnimatedSpriteType *playerType;
	AnimatedSprite *player = new AnimatedSprite();
	PoseurSpriteTypeImporter psti;

	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	World *world = gsm->getWorld();
	player = spriteManager->getPlayer();
	unsigned int spriteTypeID;

	/*
    list<Bot*>::iterator sTBotsIterator;

	sTBotsIterator = spriteManager->getBotsIterator();

	while (sTBotsIterator != spriteManager->getEndOfBotsIterator())
	{

		 Bot *botToCheck = (*sTBotsIterator);

		 delete botToCheck->getSpriteType();

		sTBotsIterator++;

	}
	*/

	spriteManager->clearSprites();

	// NOTE THAT THE WORLD WILL BE THE SAME DIMENSIONS AS OUR TILED LAYER,
	// WE COULD GET A PARALLAX SCROLLING EFFECT IF WE MADE A LAYER SMALLER,
	// AND THEN SCROLLED IT SLOWER
	
	world->setWorldWidth(NUM_COLUMNS * TILE_WIDTH);
	world->setWorldHeight(NUM_ROWS * TILE_HEIGHT);

	// NOW LOAD OUR TILED BACKGROUND
	TiledLayer *tiledLayer = new TiledLayer(	NUM_COLUMNS,	NUM_ROWS, 
												TILE_WIDTH,		TILE_HEIGHT, 
												0, true, 
												NUM_COLUMNS * TILE_WIDTH,
												NUM_ROWS * TILE_HEIGHT);
	
	/*
	int backgroundID = worldTextureManager->loadTexture(MOUNTAIN_IMAGE_PATH);
	int cloud_0ID = worldTextureManager->loadTexture(CLOUD_0_IMAGE_PATH);
	int cloud_1ID = worldTextureManager->loadTexture(CLOUD_1_IMAGE_PATH);
	int cloud_2ID = worldTextureManager->loadTexture(CLOUD_2_IMAGE_PATH);
	*/

	if(level == 1)
	{
		backgroundID = worldTextureManager->loadTexture(MOUNTAIN_IMAGE_PATH);
		cloud_0ID = worldTextureManager->loadTexture(CLOUD_0_IMAGE_PATH);
		cloud_1ID = worldTextureManager->loadTexture(CLOUD_1_IMAGE_PATH);
		cloud_2ID = worldTextureManager->loadTexture(CLOUD_2_IMAGE_PATH);
	}
	else if (level == 2)
	{
		backgroundID = worldTextureManager->loadTexture(GRASS_IMAGE_PATH);
		cloud_0ID = worldTextureManager->loadTexture(CLOUD_0_IMAGE_PATH);
		cloud_1ID = worldTextureManager->loadTexture(CLOUD_3_IMAGE_PATH);
		cloud_2ID = worldTextureManager->loadTexture(CLOUD_4_IMAGE_PATH);
	}
	else if(level == 3)
	{
		backgroundID = worldTextureManager->loadTexture(WATER_IMAGE_PATH);
		cloud_0ID = worldTextureManager->loadTexture(CLOUD_0_IMAGE_PATH);
		cloud_1ID = worldTextureManager->loadTexture(CLOUD_5_IMAGE_PATH);
		cloud_2ID = worldTextureManager->loadTexture(CLOUD_6_IMAGE_PATH);
	}
	else if(level == 4)
	{
		backgroundID = worldTextureManager->loadTexture(WATER_IMAGE_PATH);
		cloud_0ID = worldTextureManager->loadTexture(CLOUD_0_IMAGE_PATH);
		cloud_1ID = worldTextureManager->loadTexture(CLOUD_5_IMAGE_PATH);
		cloud_2ID = worldTextureManager->loadTexture(CLOUD_6_IMAGE_PATH);
	}

	srand(1);

	// LET'S GENERATE A RANDOM BACKGROUND USING OUR TWO TILES


	// NEEED TO BE CHANGED
	for (int i = 0; i < (NUM_COLUMNS * NUM_ROWS); i++)
	{
		bool isCollidable = false;
		int tileIDToUse = backgroundID;
		Tile *tileToAdd = new Tile();
		tileToAdd->collidable = isCollidable;
		tileToAdd->textureID = tileIDToUse;
		tiledLayer->addTile(tileToAdd);

	}
	
	// BUT LET'S CLEAR OUT THE TOP-LEFT AREA
	// scrolling add
	for (int i = 0; i < 55; i++)
	{
		for (int k = 0; k < 1; k++)
		{
			Tile *tile = tiledLayer->getTile(i,k);
			tile->textureID = cloud_0ID;
		}
		for (int j = 1; j < 2; j++)
		{
			Tile *tile = tiledLayer->getTile(i,j);
			tile->textureID = cloud_1ID;
		}
		for (int h = 15; h < 16; h++)
		{
			Tile *tile = tiledLayer->getTile(i,h);
			tile->textureID = cloud_0ID;
		}
		for (int g = 14; g < 15; g++)
		{
			Tile *tile = tiledLayer->getTile(i,g);
			tile->textureID = cloud_2ID;
		}


	}	
	
	world->addLayer(tiledLayer);

	// CREATE THE PLAYER
	psti.loadSpriteTypes(game, SPRITE_TYPES_LIST);

	// NOTE THAT SPRITETYPE 0 IS BLUE AIRPLANE
	playerType = spriteManager->getSpriteType(0);
	player->setSpriteType(playerType);
	player->setAlpha(255);
	player->setCurrentState(L"IDLE");
	PhysicalProperties *playerProps = player->getPhysicalProperties();
	playerProps->setX((world->getWorldWidth())/2);
	// scrolling add
	playerProps->setY(world->getWorldHeight()-150);
	// scrolling add
	// have player always be moving at least at the
	// speed of the viewport
	playerProps->setVelocity(0.0f, -5.0f);

	spriteTypeID = spriteManager->addSpriteType(playerType);

	playerType->setSpriteTypeID(spriteTypeID);	
	// i added this
	playerProps->setPlayerFlag(1);
	// updated this
	playerProps->setEnemyFlag(0);
	// bm4 add
	playerProps->setPlayerBulletFlag(0);
	playerProps->setEnemyBulletFlag(0);

	// WE WILL SET LOTS OF OTHER PROPERTIES ONCE
	// WE START DOING COLLISIONS AND PHYSICS

	// i added this
	// create a body for the player
	// and associate it with the
	// player sprite
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	// set the position of the body so that
	// it corresponds to the position of
	// the sprite
	int playerWidth = player->getSpriteType()->getTextureWidth();
	int playerHeight = player->getSpriteType()->getTextureHeight();
	playerBodyDef.position.Set(playerProps->getX()/3.0f + playerWidth/3, playerProps->getY()/3.0f + playerHeight/3);
	playerBodyDef.userData = player;
	b2World *ourWorld = game->getOurWorld();
	b2Body *playerBody = ourWorld->CreateBody(&playerBodyDef);

	// attach a fixture to the body to give it a
	// shape and density (and thus mass)
	b2PolygonShape rectangleShape;
	// if the conversion factor is 1 m = 3 pixels
	// then the half-width of the rectangle
	// representing the player's shape, in meters,
	// is the player's width/3/2 = player's width/6,
	// and likewise for the height
	rectangleShape.SetAsBox(playerWidth/6.0f, playerHeight/6.0f);
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &rectangleShape;
	playerFixtureDef.density = 1.0f;
	playerBody->CreateFixture(&playerFixtureDef);
	// set player's body variable
	player->setBody(playerBody);
	
	Physics *physics = game->getGSM()->getPhysics();
	max_health *bot1 = new max_health(physics,3);
	AnimatedSpriteType *max_healthBar = spriteManager->getSpriteType(13);
	bot1->setSpriteType(max_healthBar);
	bot1->setCurrentState(L"TEN");
	bot1->setAlpha(255);
	spriteManager->addBot(bot1);

	health *bot = new health(physics,3);
	AnimatedSpriteType *healthBar = spriteManager->getSpriteType(8);
	bot->setSpriteType(healthBar);
	bot->setCurrentState(L"TEN");
	bot->setAlpha(255);
	spriteManager->addBot(bot);

	Lives *bot3 = new Lives(physics,3);
	AnimatedSpriteType *LifeBar = game->getGSM()->getSpriteManager()->getSpriteType(14);
	bot3->setSpriteType(LifeBar);
	bot3->setCurrentState(L"TWO");
	spriteManager->addBot(bot3);
	/*
	spriteTypeID = spriteManager->addSpriteType(EnemyBot1);
	EnemyBot1->setSpriteTypeID(spriteTypeID);
	AnimatedSprite *Enemy = spriteManager->getPlayer();
	Enemy->setSpriteType(ast);
	PhysicalProperties *EnemyProps = Enemy->getPhysicalProperties();
	EnemyProps->setX(100);
	EnemyProps->setY(0);
	EnemyProps->setVelocity(0.0f, 0.0f);
	EnemyProps->setAccelerationX(0);
	EnemyProps->setAccelerationY(0);
	*/

	// scrolling add
	Viewport *viewport = game->getGUI()->getViewport();
	viewport->setViewportY(game->getGSM()->getWorld()->getWorldHeight() - viewport->getViewportHeight());

	if(level == 4)
	{
		player->getPhysicalProperties()->setEnemyRemaining(loadBoss(game, level));
	}
	else
	{
		player->getPhysicalProperties()->setEnemyRemaining(loadWave(game, level));
	}
	player->getPhysicalProperties()->setWave(1);
	player->getPhysicalProperties()->setLevel(level);
}
int GameDataLoader::loadWave(Game *game, int level)
{
	// scrolling add
 	Viewport *viewport = game->getGUI()->getViewport();
	int viewportX = viewport->getViewportX();
	int viewportY = viewport->getViewportY();
	
	srand(time(NULL));
	int wave = 1 + (rand() % 9); // random generate to 9
	int numEnemies = 0;
	if(wave == 1)
	{
		// scrolling add
		Speedster *enemybot1 = new Speedster(game,game->getGSM()->getPhysics(),50,viewportY + 50,level);
		Attacker  *enemybot2 = new Attacker(game,game->getGSM()->getPhysics(),500,viewportY + 50,level);
		Speedster *enemybot3 = new Speedster(game,game->getGSM()->getPhysics(),950,viewportY + 50,level);
		Defender  *enemybot4 = new Defender(game,game->getGSM()->getPhysics(),275,viewportY + 200,level);
		Defender  *enemybot5 = new Defender(game,game->getGSM()->getPhysics(),725,viewportY + 200,level);
		numEnemies = 5;
	}
	else if(wave == 2)
	{
		Attacker  *enemybot1 = new Attacker(game,game->getGSM()->getPhysics(),375,viewportY + 50,level);
		Attacker  *enemybot2 = new Attacker(game,game->getGSM()->getPhysics(),600,viewportY + 50,level);
		Defender  *enemybot3 = new Defender(game,game->getGSM()->getPhysics(),250,viewportY + 150,level);
		Defender  *enemybot4 = new Defender(game,game->getGSM()->getPhysics(),700,viewportY + 150,level);
		Defender  *enemybot5 = new Defender(game,game->getGSM()->getPhysics(),375,viewportY + 250,level);
		Defender  *enemybot6 = new Defender(game,game->getGSM()->getPhysics(),600,viewportY + 250,level);
		numEnemies = 6;
	}
	else if(wave == 3)
	{
		Attacker  *enemybot1 = new Attacker(game,game->getGSM()->getPhysics(),275,viewportY + 50,level);
		Attacker  *enemybot2 = new Attacker(game,game->getGSM()->getPhysics(),700,viewportY + 50,level);
		Speedster *enemybot3 = new Speedster(game,game->getGSM()->getPhysics(),487,viewportY + 100,level);
		Defender  *enemybot4 = new Defender(game,game->getGSM()->getPhysics(),150,viewportY + 150,level);
		Defender  *enemybot5 = new Defender(game,game->getGSM()->getPhysics(),800,viewportY + 150,level);
		Defender  *enemybot6 = new Defender(game,game->getGSM()->getPhysics(),375,viewportY + 150,level);
		Defender  *enemybot7 = new Defender(game,game->getGSM()->getPhysics(),600,viewportY + 150,level);
		numEnemies = 7;
	}
	else if(wave == 4)
	{
		Attacker  *enemybot1 = new Attacker(game,game->getGSM()->getPhysics(),275,viewportY + 50,level);
		Attacker  *enemybot2 = new Attacker(game,game->getGSM()->getPhysics(),700,viewportY + 50,level);
		Attacker  *enemybot3 = new Attacker(game,game->getGSM()->getPhysics(),487,viewportY + 50,level);
		Attacker  *enemybot4 = new Attacker(game,game->getGSM()->getPhysics(),150,viewportY + 150,level);
		Attacker  *enemybot5 = new Attacker(game,game->getGSM()->getPhysics(),800,viewportY + 150,level);
		Attacker  *enemybot6 = new Attacker(game,game->getGSM()->getPhysics(),375,viewportY + 150,level);
		Attacker  *enemybot7 = new Attacker(game,game->getGSM()->getPhysics(),600,viewportY + 150,level);
		numEnemies = 7;
	}
	else if(wave == 5)
	{
		Attacker  *enemybot1 = new Attacker(game,game->getGSM()->getPhysics(),150,viewportY + 50,level);
		Speedster *enemybot2 = new Speedster(game,game->getGSM()->getPhysics(),500,viewportY + 50,level);
		Attacker  *enemybot3 = new Attacker(game,game->getGSM()->getPhysics(),800,viewportY + 50,level);
		Defender  *enemybot4 = new Defender(game,game->getGSM()->getPhysics(),325,viewportY + 150,level);
		Defender  *enemybot5 = new Defender(game,game->getGSM()->getPhysics(),650,viewportY + 150,level);
		Defender  *enemybot6 = new Defender(game,game->getGSM()->getPhysics(),150,viewportY + 250,level);
		Defender  *enemybot7 = new Defender(game,game->getGSM()->getPhysics(),800,viewportY + 250,level);
		numEnemies = 7;
	}
	else if(wave == 6)
	{
		Speedster  *enemybot1 = new Speedster(game,game->getGSM()->getPhysics(),150,viewportY + 50,level);
		Speedster  *enemybot2 = new Speedster(game,game->getGSM()->getPhysics(),400,viewportY + 50,level);
		Speedster  *enemybot3 = new Speedster(game,game->getGSM()->getPhysics(),600,viewportY + 50,level);
		Speedster  *enemybot4 = new Speedster(game,game->getGSM()->getPhysics(),850,viewportY + 50,level);
		Attacker  *enemybot5 = new Attacker(game,game->getGSM()->getPhysics(),325,viewportY + 200,level);
		Attacker  *enemybot6 = new Attacker(game,game->getGSM()->getPhysics(),675,viewportY + 200,level);
		numEnemies = 6;
	}
	else if(wave == 7)
	{
		Attacker  *enemybot1 = new Attacker(game,game->getGSM()->getPhysics(),500,viewportY + 50,level);
		Defender  *enemybot2 = new Defender(game,game->getGSM()->getPhysics(),225,viewportY + 50,level);
		Defender  *enemybot3 = new Defender(game,game->getGSM()->getPhysics(),775,viewportY + 50,level);
		Defender  *enemybot4 = new Defender(game,game->getGSM()->getPhysics(),388,viewportY + 150,level);
		Defender  *enemybot5 = new Defender(game,game->getGSM()->getPhysics(),638,viewportY + 150,level);
		Defender  *enemybot6 = new Defender(game,game->getGSM()->getPhysics(),275,viewportY + 250,level);
		Defender  *enemybot7 = new Defender(game,game->getGSM()->getPhysics(),725,viewportY + 250,level);
		numEnemies = 7;
	}
	else if(wave == 8)
	{
		Speedster *enemybot1 = new Speedster(game,game->getGSM()->getPhysics(),225,viewportY + 50,level);
		Speedster *enemybot2 = new Speedster(game,game->getGSM()->getPhysics(),775,viewportY + 50,level);
		Defender  *enemybot3 = new Defender(game,game->getGSM()->getPhysics(),200,viewportY + 150,level);
		Defender  *enemybot4 = new Defender(game,game->getGSM()->getPhysics(),800,viewportY + 150,level);
		Defender  *enemybot5 = new Defender(game,game->getGSM()->getPhysics(),375,viewportY + 200,level);
		Defender  *enemybot6 = new Defender(game,game->getGSM()->getPhysics(),625,viewportY + 200,level);
		Defender  *enemybot7 = new Defender(game,game->getGSM()->getPhysics(),500,viewportY + 300,level);
		Attacker  *enemybot8 = new Attacker(game,game->getGSM()->getPhysics(),500,viewportY + 100,level);
		numEnemies = 8;
	}
	return numEnemies;
}

int GameDataLoader::loadBoss(Game *game, int level)
{
	// scrolling add
 	Viewport *viewport = game->getGUI()->getViewport();
	int viewportX = viewport->getViewportX();
	int viewportY = viewport->getViewportY();

	int numEnemies = 0;

	FirstBossLeft   *bossbot2 = new FirstBossLeft(game,game->getGSM()->getPhysics(),50,viewportY,level);
	FirstBossCenter *bossbot1 = new FirstBossCenter(game,game->getGSM()->getPhysics(),256,viewportY,level);
	FirstBossRight  *bossbot3 = new FirstBossRight(game,game->getGSM()->getPhysics(),333,viewportY,level);
	numEnemies = 1;

	return numEnemies;
}