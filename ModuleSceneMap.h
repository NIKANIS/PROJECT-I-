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
	void Timer();
	void SelectMap();
	void ResetTimer();

public:
	Mix_Chunk* select = nullptr;
	Mix_Chunk* selected = nullptr;

	SDL_Texture* back_graphics = nullptr;
	SDL_Rect background;
	iPoint position;

	int map;
	int fadetoblack = 0;
	bool map_chosen = false;
	SDL_Rect pao_pao;
	SDL_Rect sound_beach;
	SDL_Rect west_sub;
	SDL_Rect howard_arena;
	SDL_Rect map_select_tittle;
	SDL_Rect timer;
	int frames_timer = 0;

	SDL_Rect pao_pao_selected;
	SDL_Rect sound_beach_selected;
	SDL_Rect west_sub_selected;
	SDL_Rect howard_arena_selected;

	Animation map_1;
	Animation map_2;
	Animation map_3;
	Animation map_4;

};

#endif // __MODULESCENEMAP_H__