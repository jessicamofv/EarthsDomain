/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	DirectXTextureManager.cpp

	See DirectXTextureManager for a class description.
*/

#include "stdafx.h"
#include "src\graphics\GameGraphics.h"
#include "src\PlatformPlugins\DirectXPlugin\DirectXGraphics.h"
#include "src\PlatformPlugins\DirectXPlugin\DirectXTextureManager.h"

/*
	DirectXTextureManager - Default constructor, it constructs the map that
	will store all of the textures and file paths/names.
*/
DirectXTextureManager::DirectXTextureManager()
{
//	textures = new map<wstring, LPDIRECT3DTEXTURE9>();
}

/*
	~DirectXTextureManager - Destructor, it cleans up all the textures.
*/
DirectXTextureManager::~DirectXTextureManager()
{
	// TODO - GO THROUGH TEXTURE MANAGER AND DELETE EVERYTHING
//	delete textures;
}

/*
	getTexture - This method fetches the texture with the provided id. This
	is done by looking up the file path/name in the wchar_t table that corresponds
	to the id index, and then fetches the appropritate texture out of the map.
*/
LPDIRECT3DTEXTURE9 DirectXTextureManager::getTexture(unsigned int id)
{
	// WHAT'S THE FILE NAME FOR THIS ID?
	wstring fileName = wstringTable.getWStringFromTable(id);

	// RETURN THE TEXTURE MAPPED TO THAT FILE NAME
	return textures[fileName];
}

/*
	loadTexture - This method loads a texture with a path/file name key into
	the GPU memory. It registers the path/file name in the wchar_t table and
	returns the corresponding index. Once the texture is created, it loads
	it into the map.
*/
unsigned int DirectXTextureManager::loadTexture(wstring key)
{
	// USED FOR READING BITMAP FILE INFO
    D3DXIMAGE_INFO info;

	// CONVERT THE FILE NAME INTO A WINDOW LONG CHAR wchar_t (LPCWSTR)
	LPCWSTR fileName = key.c_str();

    // GET THE IMAGE SIZE FROM THE IMAGE FILE
    HRESULT result = D3DXGetImageInfoFromFile(fileName, &info);

	// IF THE IMAGE FILE WAS FOUND
	if (result == S_OK)
	{
		// GET THE COLOR KEY, WE'LL NEED THIS FOR LOADING OUR IMAGE
		D3DCOLOR colorKey = ((DirectXGraphics*)graphics)->getColorKey();

		LPDIRECT3DDEVICE9 graphicsDevice = ((DirectXGraphics*)graphics)->getGraphicsDevice();
		LPDIRECT3DTEXTURE9 textureToLoad;

		// CREATE A NEW TEXTURE
		result = D3DXCreateTextureFromFileEx(
			graphicsDevice,		// GPU
			fileName,			// BITMAP FILE PATH/NAME
			info.Width,			// BITMAP IMAGE WIDTH
			info.Height,		// BITMAP IMAGE HEIGHT
			1,					// MIP-MAP LEVELS (1 FOR NO CHAIN)
			D3DPOOL_DEFAULT,	// THE TYPE OF SURFACE (STANDARD)
			D3DFMT_UNKNOWN,		// SURFACE FORMAT (DEFAULT)
			D3DPOOL_DEFAULT,	// MEMORY CLASS FOR THE TEXTURE
			D3DX_DEFAULT,		// IMAGE FILTER
			D3DX_DEFAULT,		// MIP FILTER
			colorKey,			// COLOR KEY
			&info,				// BITMAP FILE INFO
			NULL,				// COLOR PALETTE
			&textureToLoad );	// THE TEXTURE WE ARE CREATING AND LOADING

		// PUT OUR LOADED TEXTURE INTO OUR MAP
		textures[fileName] = textureToLoad;

		// NOW PUT THE KEY IN THE wchar_t TABLE
		int indexOfTexture = wstringTable.putWStringInTable(fileName);

		// AND RETURN THE TEXTURE'S ID
		return indexOfTexture;
	}
	else
		return -1;
}

/*
	reloadAllTextures - Should our game application lose access to the GPU
	the textures we loaded in may be lost. So, when we get the GPU back
	this method allows us to reload all of the textures in our map.
*/
void DirectXTextureManager::reloadAllTextures()
{
	map<wstring, LPDIRECT3DTEXTURE9>::iterator texturesIterator;

	wstring key;
	for (	texturesIterator = textures.begin();
				texturesIterator != textures.end();
				texturesIterator++ )
	{
		key = texturesIterator->first;
		loadTexture(key);
	}
}

/*
	clear - This method clears out all the textures in our map. It
	results in the deletion of all of these objects. The corresponding
	wchar_t table is then also cleared.
*/
void DirectXTextureManager::clear()
{
	map<wstring, LPDIRECT3DTEXTURE9>::iterator it;
	map<wstring, LPDIRECT3DTEXTURE9>::iterator itToErase;
	it = textures.begin();
	while (it != textures.end())
	{
		wstring keyToDelete = (*it).first;
		LPDIRECT3DTEXTURE9 textureToDelete = (*it).second;
		itToErase = it;
		it++;
		textures.erase(itToErase);
		textureToDelete->Release();
		textureToDelete = NULL;
	}
	textures.clear();
	wstringTable.clear();
}