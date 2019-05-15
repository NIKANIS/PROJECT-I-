#ifndef __MODULESCENENEOGEO_H__
#define __MODULESCENENEOGEO_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleAudio.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneNeoGeo : public Module
{
public:
	ModuleSceneNeoGeo();
	~ModuleSceneNeoGeo();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation backgroundanim;
	Mix_Music* music = nullptr;
};

#endif // __MODULESCENENEOGEO_H__
