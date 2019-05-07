#ifndef __MODULESCENEMAP_H__
#define __MODULESCENEMAP_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneMap : public Module
{
public:
	ModuleSceneMap();
	~ModuleSceneMap();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* music = nullptr;
	SDL_Texture* back_graphics = nullptr;
	SDL_Rect background;
	iPoint position;
	SDL_Rect pao_pao;
	SDL_Rect sound_beach;
	SDL_Rect west_sub;
	SDL_Rect howard_arena;


};

#endif // __MODULESCENEMAP_H__