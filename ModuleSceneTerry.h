#ifndef __MODULESCENETERRY_H__
#define __MODULESCENETERRY_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneTerry : public Module
{
public:
	ModuleSceneTerry();
	~ModuleSceneTerry();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* back_graphics = nullptr;
	SDL_Rect ground;
	Animation background;

	float foreground_pos;
	bool forward;
};

#endif // __MODULESCENETERRY_H__