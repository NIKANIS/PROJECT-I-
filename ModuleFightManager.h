#ifndef _ModuleFightManager_H__
#define _ModuleFightManager_H__

#include "Globals.h"
#include "Module.h"
#include "p2Point.h"
#include "ModuleAudio.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleFightManager : public Module
{
public:
	ModuleFightManager();
	~ModuleFightManager();

	bool Start();
	update_status Update();
	bool CleanUp();
	int Time() { return timer_num; }
	int Player() { return pl_won_rounds; }
	int Enemy() { return en_won_rounds; }
	int Winner() { return winner; }


public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsFight = nullptr;

	SDL_Rect win;
	SDL_Rect lose;
	SDL_Rect draw;
	SDL_Rect round;
	SDL_Rect f;
	iPoint position;
	int cam_pos_x;
	int winner = 3; // 0 = P1_win, 1 = P2_win, 2 = draw
	int pl_won_rounds;
	int en_won_rounds;
	int timer_num;
	int timer_counter;
	bool time_stop;
	bool blockpoints; 
	void Reset();
	Mix_Chunk* roundFX = nullptr;
	Mix_Chunk* fightFX = nullptr;

	Animation fightAnimX;
};

#endif

