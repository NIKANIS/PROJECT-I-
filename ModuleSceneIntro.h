#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro();
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Animation water;
};

#endif // __MODULESCENEHONDA_H__