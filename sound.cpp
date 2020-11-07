#include "sound.h"

void openSound()
{
	mciSendString(_T("open shot.mp3 alias shot"), NULL, 0, NULL);
	mciSendString(_T("open boom.mp3 alias boom"), NULL, 0, NULL);
}

void playBackground()
{
	mciSendString(_T("open back.mp3 alias back"), NULL, 0, NULL);
	mciSendString(_T("play back repeat"), NULL, 0, NULL);
}

void playShot()
{
	mciSendString(_T("play shot from 0"), NULL, 0, NULL);
	
}

void playBoom()
{
	mciSendString(_T("play boom from 0"), NULL, 0, NULL);
}