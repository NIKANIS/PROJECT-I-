#ifndef __MODULESCENECHOOSEPLAYER_H__
#define __MODULESCENECHOOSEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleAudio.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneChoosePlayer : public Module
{
public:
	ModuleSceneChoosePlayer();
	~ModuleSceneChoosePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Animation* current_animation = nullptr;

	SDL_Texture* graphicschooseplayer = nullptr;
	SDL_Rect background;
	SDL_Rect grey_joehigashi;
	SDL_Rect grey_terrybogard;
	SDL_Rect grey_andybogard;
	SDL_Rect player_select_tittle;
	Animation selected_joehigashi;
	Animation selected_terrybogard;
	Animation selected_andybogard;
	int player_selected = 2; //player 1 -> Joe Higashi, player 2 -> Terry Bogard, player 3 -> Andy Bogard 
	Mix_Music* music = nullptr;
};

#endif // __MODULESCENECHOOSEPLAYER_H__