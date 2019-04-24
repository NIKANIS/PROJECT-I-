#ifndef __MODULESCENEGAMEOVER_H__
#define __MODULESCENEGAMEOVER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneGameOver : public Module
{
public:
	ModuleSceneGameOver();
	~ModuleSceneGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Animation water;
};

#endif // __MODULESCENEGAMEOVER_H__