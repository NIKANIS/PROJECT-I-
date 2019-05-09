#ifndef __MODULESCENEWESTSUBWAY_H__
#define __MODULESCENEWESTSUBWAY_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneWestSubway : public Module
{
public:
	ModuleSceneWestSubway();
	~ModuleSceneWestSubway();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* music = nullptr;
	//SI hace falta efecte Mix_Chunk*;
	SDL_Texture* back_graphics = nullptr;
	SDL_Rect ground;
	Animation background;

	float foreground_pos;
	bool forward;
};

#endif // __MODULESCENEWESTSUBWAY_H__
