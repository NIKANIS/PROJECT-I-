#ifndef __MODULEPLAYERSCORE_H__
#define __MODULEPLAYERSCORE_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModulePlayerScore : public Module
{
public:
	ModulePlayerScore(const int player);
	~ModulePlayerScore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect zero;
	SDL_Rect one;
	SDL_Rect two;
	SDL_Rect three;
	SDL_Rect four;
	SDL_Rect five;
	SDL_Rect six;
	SDL_Rect seven;
	SDL_Rect eight;
	SDL_Rect nine;
	iPoint position;
	int n[5];
	SDL_Rect r[5];
	int pastscore;
	int player;
};

#endif
