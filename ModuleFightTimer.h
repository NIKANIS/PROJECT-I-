#ifndef __ModuleFightTimer_H__
#define __ModuleFightTimer_H__ 

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleFightTimer : public Module
{
public:
	ModuleFightTimer();
	~ModuleFightTimer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect timer;
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
	int n[2];
	SDL_Rect r[2];
};


#endif
