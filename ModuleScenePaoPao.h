#ifndef __MODULESCENEPAOPAO_H__
#define __MODULESCENEPAOPAO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleScenePaoPao : public Module
{
public:
	ModuleScenePaoPao();
	~ModuleScenePaoPao();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* music = nullptr;
	//SI hace falta efecte Mix_Chunk*;
	SDL_Texture* back_graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect shadowp1;
	SDL_Rect shadowp2;
	Animation background;

	float foreground_pos;
	bool forward;
};

#endif // __MODULESCENEPAOPAO_H__