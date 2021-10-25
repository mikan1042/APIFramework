#pragma once


typedef struct tagSoundInfo
{
	FMOD::Sound* SoundObj;
	FMOD::Channel* SoundChannel;
	int ChannelID;

}SOUNDINFO;