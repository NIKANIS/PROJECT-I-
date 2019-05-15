#ifndef __MODULESCENENEOGEOINTRO_H__
#define __MODULESCENENEOGEOINTRO_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleAudio.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneNeoGeoIntro : public Module
{
public:
	ModuleSceneNeoGeoIntro();
	~ModuleSceneNeoGeoIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation backgroundanim;
	Mix_Music* music = nullptr;
};

#endif // __MODULESCENENEOGEOINTRO_H__
