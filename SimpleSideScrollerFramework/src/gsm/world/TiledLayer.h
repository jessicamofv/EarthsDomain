/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	TiledLayer.h

	A TiledLayer manages a tiled background, which is basically
	a grid of images that together create a game background.
	TiledLayers are packed, meaning there is a tile in every
	grid cell.
*/
#pragma once
#include "stdafx.h"
#include "src\graphics\RenderList.h"
#include "src\gsm\world\WorldLayer.h"
#include "src\gui\Viewport.h"

/*
	A Tile represents a single image in a tiled background.
	Tiles can be collidable or not collidable. Tiles do not
	know where they are placed. They do know the index of
	the texture that should be used for rendering themselves
	as stored in the GameGraphics's world string table and
	it's partnered texture manager.
*/
struct Tile
{
	int textureID;
	bool collidable;
};

// THIS CLASS IS-A WorldLayer

class TiledLayer: public WorldLayer
{
protected:
	// NOTE: tileLayout stores a grid of Tiles (rows X columns),
	// but does so using a one-dimensional vector. So, when
	// accessing and changing tiles in this data structure,
	// rows and columns must be converted into indices.
	vector<Tile*> *tileLayout;
	int columns;
	int rows;
	int tileWidth;
	int tileHeight;
	int layerWidth;
	int layerHeight;
	int z;
	// NOTE: z IS HERE IN CASE WE WANT TO LAYER SPRITES
	// IN FRONT OF OR BEHIND LAYERS IN A GAME WORLD

public:
	// INLINED ACCESSOR METHODS
	int getColumns()			{ return columns;		}
	int getRows()				{ return rows;			}
	int getTileHeight()			{ return tileHeight;	}
	int getTileWidth()			{ return tileWidth;		}
	int getLayerWidth()			{ return layerWidth;	}
	int getLayerHeight()		{ return layerHeight;	}
	int getZ()					{ return z;				}

	// INLINED MUTATOR METHOD
	void setZ(int initZ)		{ z = initZ;			}

	// METHODS DEFINED IN TiledLayer.cpp
	TiledLayer(	int initColumns,	int initRows, 
				int initTileWidth,	int initTileHeight, 
				int initZ, 
				bool initCollidableTiles, 
				int worldWidth, int worldHeight);
	~TiledLayer();
	void	addRenderItemsToRenderList(RenderList *renderList, Viewport *viewport);
	void	addTile(Tile *initTile);
	int		calculateAndSetLayerHeight();
	int		calculateAndSetLayerWidth();
	int		calculateViewportEndColumn(int viewportX, int viewportWidth);
	int		calculateViewportEndRow(int viewportY, int viewportHeight);
	int		calculateViewportStartColumn(int viewportX);
	int		calculateViewportStartRow(int viewportY);
	Tile*	getTile(int row, int column);
	void	init(	int initColumns,	int initRows, 
					int initTileWidth,	int initTileHeight, 
					int initZ, 
					bool collidableTiles, 
					int worldWidth, int worldHeight);
	void	setTile(Tile *initTile, int row, int column);
};