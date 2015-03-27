// bm4 add
#pragma once
#include "stdafx.h"
#include <windows.h>
#include <xact3.h>
#include "XACT3Audio.h"

void* LoadBankFile( char* filePath, DWORD& fileSize )
{
	HANDLE file = CreateFileA(filePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if( file == INVALID_HANDLE_VALUE )
		return 0;
	fileSize = GetFileSize( file, 0 );
	if( fileSize == -1 )
	{
		CloseHandle( file );
		return 0;
	}
	HANDLE mapFile = CreateFileMapping(file, 0, PAGE_READONLY, 0, fileSize, 0);
	if( !mapFile )
	{
		CloseHandle( file );
		return 0;
	}
	void *ptr = MapViewOfFile( mapFile, FILE_MAP_READ, 0, 0, 0 );
	CloseHandle( mapFile );
	CloseHandle( file );
	return ptr;
}

bool LoadWaveBank( IXACT3Engine* audioEngine, stXACTAudio& audio, char* waveBankFile )
{
	DWORD fileSize = 0;
	audio.waveBankData = LoadBankFile( waveBankFile, fileSize );
	if( FAILED( audioEngine->CreateInMemoryWaveBank( audio.waveBankData, fileSize, 0, 0, &audio.waveBank ) ) )
	{
		return false;
	}
	return true;
}

bool LoadSoundBank( IXACT3Engine* audioEngine, stXACTAudio& audio, char* soundBankFile )
{
	DWORD fileSize = 0;
	audio.soundBankData = LoadBankFile( soundBankFile, fileSize );
	if( FAILED( audioEngine->CreateSoundBank( audio.soundBankData, fileSize, 0, 0, &audio.soundBank ) ) )
	{
		return false;
	}
	return true;
}

bool LoadXACTAudio( IXACT3Engine* audioEngine, stXACTAudio& audio, char* waveBank, char* soundBank )
{
	if( LoadWaveBank( audioEngine, audio, waveBank ) == false )
		return false;
	if( LoadSoundBank( audioEngine, audio, soundBank ) == false )
		return false;
	return true;
}

bool SetupXACT( IXACT3Engine** audioEngine )
{
	if( FAILED( CoInitializeEx( 0, COINIT_MULTITHREADED ) ) )
		return false;
	if( FAILED(XACT3CreateEngine( XACT_FLAG_API_AUDITION_MODE, audioEngine) ))
		return false;
	if( *audioEngine == 0 )
		return false;
	XACT_RUNTIME_PARAMETERS xparams = { 0 };
	xparams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	if( FAILED( ( *audioEngine )->Initialize( &xparams ) ) )
		return false;
	return true;
}