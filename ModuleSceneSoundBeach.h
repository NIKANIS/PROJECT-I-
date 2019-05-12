#ifndef __MODULESCENESOUNDBEACH_H__
#define __MODULESCENESOUNDBEACH_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneSoundBeach : public Module
{
public:
	ModuleSceneSoundBeach();
	~ModuleSceneSoundBeach();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* music = nullptr;
	//SI hace falta efecte Mix_Chunk*;
	SDL_Texture* back_graphics = nullptr;
	SDL_Rect landscape;
	Animation background;

	float foreground_pos;
	bool forward;
};

#endif // __MODULESCENESOUNDBEACH_H__

