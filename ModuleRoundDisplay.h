#ifndef _ModuleRoundDisplay_H__
#define _ModuleRoundDisplay_H__

#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleRoundDisplay : public Module
{
public:
	ModuleRoundDisplay(const int player);
	~ModuleRoundDisplay();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

	SDL_Texture* graphics = nullptr;
	Animation off;
	Animation on;
	iPoint position;
	int player;
};

#endif
