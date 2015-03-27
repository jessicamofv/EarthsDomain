// bm4 add
#pragma once
#include "stdafx.h"
#include <windows.h>
#include <xact3.h>

struct stXACTAudio
{
	IXACT3WaveBank *waveBank;
	IXACT3SoundBank *soundBank;
	void *waveBankData;
	void *soundBankData;
};

void* LoadBankFile( char* filePath, DWORD& fileSize );
bool LoadWaveBank( IXACT3Engine* audioEngine, stXACTAudio& audio, char* waveBankFile );
bool LoadSoundBank( IXACT3Engine* audioEngine, stXACTAudio& audio, char* soundBankFile );
bool LoadXACTAudio( IXACT3Engine* audioEngine, stXACTAudio& audio, char* waveBank, char* soundBank );
bool SetupXACT( IXACT3Engine** audioEngine );