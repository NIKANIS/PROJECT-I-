#ifndef __ModulelifeBar_H__
#define __ModuleLifeBar_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleLifeBar : public Module
{
public:
	ModuleLifeBar(const int player);
	~ModuleLifeBar();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect P1photo;
	SDL_Rect P2photo;
	SDL_Rect P3photo;
	SDL_Rect health;
	Animation healthy;
	Animation lowhealth;
	Animation dead;
	iPoint position;
	int player; //0 = P1 , 1 = P2

};

#endif