#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	// Destructor
	~ModuleAudio();

	bool Init();
	update_status Update();
	bool CleanUp();

	Mix_Chunk* const ModuleAudio::loadWAV(const char* path);
	Mix_Music* const ModuleAudio::loadMusic(const char* path);
	bool playMusic(Mix_Music *music);
	bool playFx(Mix_Chunk *chunk);
public:

};

#endif // __ModuleAudio_H__