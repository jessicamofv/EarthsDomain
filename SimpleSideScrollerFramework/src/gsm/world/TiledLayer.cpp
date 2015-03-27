/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	TiledLayer.cpp

	See TiledLayer.h for a class description.
*/

#include "stdafx.h"
#include "src\game\Game.h"
#include "src\graphics\GameGraphics.h"
#include "src\graphics\RenderList.h"
#include "src\gsm\world\TiledLayer.h"
#include "src\gui\Viewport.h"

/*
	TiledLayer - Constructor, it initializes the data structures
	for rendering a tiled background, including the parallax
	factor for the x & y axes. It does not, however, fill the
	data structure with Tiles, that must be done using the
	addTile method.
*/
TiledLayer::TiledLayer(	int initColumns, 
						int initRows,
						int initTileWidth, 
						int initTileHeight,
						int initZ,
						bool initCollidableTiles,
						int worldWidth,
						int worldHeight)
{
	init(	initColumns,
			initRows,
			initTileWidth,
			initTileHeight,
			initZ,
			initCollidableTiles,
			worldWidth,
			worldHeight);
}

/*
	~TiledLayer - Destructor, it cleans up the Tile grid.
	This method should be called when a level is changed
	so that the old level is removed from memory.
*/
TiledLayer::~TiledLayer() 
{
	vector<Tile*>::iterator it = tileLayout->begin();
	Tile* prevTile = *(it);
	while (it != tileLayout->end())
	{
		it++;
		delete prevTile;
		prevTile = *(it);
	}
	delete tileLayout;
}

/*
	addRenderItemsToRenderList - This method is called once per
	frame for each TiledLayer in a game world while the game is
	being played. It determines which Tiles in the layer are in
	the viewport, and creates a RenderItem for each one. It then
	adds each one to the provided render list.
*/
void TiledLayer::addRenderItemsToRenderList(RenderList *renderList,
											Viewport *viewport)
{
	// WE'LL USE THIS IN OUR CALCULATIONS
	int viewportX = viewport->getViewportX();
	int viewportY = viewport->getViewportY();

	// THE GUI MIGHT TAKE UP PART OF THE SCREEN, SO FACTOR
	// THAT IN TO OUR RENDERING OF THE GAME WORLD
	int viewportWidth = viewport->getViewportWidth();
	int viewportHeight = viewport->getViewportHeight();

	// TILES THAT WE PUT IN THE RENDER LIST ARE GOING TO BE
	// RENDERED OF COURSE, SO WE ONLY WANT TO PUT TILES IN THE
	// LIST THAT ARE ACTUALLY IN THE CURRENT VIEWPORT. HERE
	// WE ARE CALCULATING WHICH Tiles IN OUR GRID ARE IN THE
	// VIEWPORT. FOR THIS, WE NEED THE START AND END rows AND
	// columns OF THE GRID.

	// 0 IS THE LOWEST COLUMN, SO CLAMP AT 0
	int startCol = calculateViewportStartColumn(viewportX);
	if (startCol < 0)
		startCol = 0;

	// columns - 1 IS THE LARGEST COLUMN, SO CLAMP THERE
	int endCol = calculateViewportEndColumn(viewportX, 
											viewportWidth);
	if (endCol >= columns)
		endCol = columns - 1;

	// 0 IS THE LOWEST ROW, SO CLAMP AT 0
	int startRow = calculateViewportStartRow(viewportY);
	if (startRow < 0)
		startRow = 0;

	// rows - 1 IS THE LARGEST ROW, SO CLAMP THERE
	int endRow = calculateViewportEndRow(	viewportY, 
											viewportHeight);
	if (endRow >= rows)
		endRow = rows - 1;

	int tileX, tileY;

	// NOW GO THROUGH THE PART OF THE GRID THAT WE'VE DETERMINED
	// IS IN THE VIEWPORT AND ADD THOSE CELLS TO THE RENDER LIST
	// AS RenderItemS. TO ENSURE PARALLAX SCROLLING, SUBTRACT
	// THE CORRECTED parallaxViewportX & parallaxViewportY FROM
	// THE TILE X & Y VALUES TO SCALE SCROLLING.
	for (int i = startRow; i <= endRow; i++)
	{
		for (int j = startCol; j <= endCol; j++)
		{
			Tile *tileToAdd = getTile(i,j);
			tileX = (j * tileWidth) - viewportX;
			tileY = (i * tileHeight) - viewportY;
			renderList->addRenderItem(	tileToAdd->textureID,
										tileX,
										tileY,
										z,
										255,
										tileWidth,
										tileHeight);
		}
	}
}

/*
	addTile - This method places initTile into the Tile grid
	for this background. Note that all tiles must be added
	using this method. Once all the tiles in the rows X columns
	grid have been added, they may be set if desired, but
	not before. Trying to set a tile that hasn't been added
	will result in an exception being thrown.
*/
void TiledLayer::addTile(Tile *initTile)
{
	tileLayout->push_back(initTile);
}

/*
	calculateAndSetLayerWidth - If the layerWidth of a TiledLayer 
	is different from the world width, parallax scrolling will
	be used in the x axis. layerWidth is used in the calculation
	for setting the parallaxFactorX. It is simply the width of
	tiles used in this layer times the number of rows.
*/
int TiledLayer::calculateAndSetLayerWidth()
{
	layerWidth = rows * tileWidth;
	return layerWidth;
}

/*
	calculateAndSetLayerHeight - If the layerHeight of a TiledLayer 
	is different from the world height, parallax scrolling will
	be used in the y axis. layerHeight is used in the calculation
	for setting the parallaxFactorY. It is simply the height of
	tiles used in this layer times the number of columns.
*/
int TiledLayer::calculateAndSetLayerHeight()
{ 
	layerHeight = columns * tileHeight;
	return layerHeight;
}

/*
	calculateViewportEndColumn - This method determines
	what column the visible tiles in the right-most part of the
	viewport belong to. This lets us know which columns of tiles
	need to be rendered and which can be ignored. There is no
	need to render tiles in columns that are not in the viewport.
*/
int TiledLayer::calculateViewportEndColumn(int viewportX,
										   int viewportWidth)
{
	int viewportRight = viewportX + viewportWidth;
	return viewportRight/tileWidth;
}

/*
	calculateViewportEndRow - This method determines
	what row the visible tiles in the bottom-most part of the
	viewport belong to. This lets us know which rows of tiles
	need to be rendered and which can be ignored. There is no
	need to render tiles in rows that are not in the viewport.
*/
int TiledLayer::calculateViewportEndRow(int viewportY,
										int viewportHeight)
{
	int viewportBottom = viewportY + viewportHeight;
	return viewportBottom/tileHeight;
}

/*
	calculateViewportStartColumn - This method determines
	what column the visible tiles in the left-most part of the
	viewport belong to. This lets us know which columns of tiles
	need to be rendered and which can be ignored. There is no
	need to render tiles in columns that are not in the viewport.
*/
int TiledLayer::calculateViewportStartColumn(int viewportX)
{
	return viewportX/tileWidth;
}

/*
	calculateViewportStartRow - This method determines
	what row the visible tiles in the top-most part of the
	viewport belong to. This lets us know which rows of tiles
	need to be rendered and which can be ignored. There is no
	need to render tiles in rows that are not in the viewport.
*/
int TiledLayer::calculateViewportStartRow(int viewportY)
{
	return viewportY/tileHeight;
}

/*
	getTile - This accessor method retrieves the Tile in
	the grid at row,column. Since the Tiles are stored in 
	a single dimensional vector, we must convert the coordinates
	from 2D to 1D.
*/
Tile* TiledLayer::getTile(int row, int column) 
{
	int cellIndex = (row * columns) + column;
	return tileLayout->at(cellIndex);
}	

/*
	init - This method initializes the layer, including calculating
	the dimensions of the layer based on the sizes of the tiles and 
	the numbers of rows & columns. In addition, it calculates the parallax
	factor used for parallax scrolling.
*/
void TiledLayer::init(int initColumns, 
						int initRows,
						int initTileWidth, 
						int initTileHeight,
						int initZ,
						bool initCollidableTiles,
						int worldWidth,
						int worldHeight)
{
	columns = initColumns;
	rows = initRows;
	tileWidth = initTileWidth;
	tileHeight = initTileHeight;
	z = initZ;
	collidableTiles = initCollidableTiles;
	tileLayout = new vector<Tile*>();
	calculateAndSetLayerWidth();
	calculateAndSetLayerHeight();
}

/*
	setTile - This mutator method allows for the changing
	of a Tile in the grid at location row, column that has
	already been added. Note that tiles cannot be set before
	they are added. In fact, after construction of this object,
	the first thing one should do is add all the tiles such
	that the vector storing Tiles is filled.
*/
void TiledLayer::setTile(Tile *initTile, int row, int column)
{
	int cellIndex = (row * columns) + column;
	tileLayout->at(cellIndex) = initTile;
}