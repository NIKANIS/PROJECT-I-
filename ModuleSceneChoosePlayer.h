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

	SDL_Texture* graphicschooseplayer = nullptr;
	SDL_Rect background;
	SDL_Rect grey_joehigashi;
	SDL_Rect grey_terrybogard;
	SDL_Rect grey_andybogard;
	Animation selected_joehigashi;
	Animation selected_terrybogard;
	Animation selected_andybogard;
	Mix_Music* music = nullptr;
};

#endif // __MODULESCENECHOOSEPLAYER_H__