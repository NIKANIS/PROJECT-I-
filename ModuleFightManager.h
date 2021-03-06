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
	void Print(int num, iPoint I_pos);


public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsFight = nullptr;
	SDL_Texture* graphicsRound1 = nullptr;
	SDL_Texture* graphicsRound2 = nullptr;
	SDL_Texture* graphicsRound3 = nullptr;
	SDL_Texture* graphicsYouWin = nullptr;
	SDL_Texture* graphicsYouLose = nullptr;
	SDL_Texture* graphicsDrawGame = nullptr;
	SDL_Texture* graphicsPixelFade = nullptr;

	iPoint l;
	iPoint t;
	iPoint tt;

	SDL_Rect win;
	SDL_Rect lose;
	SDL_Rect draw;
	SDL_Rect round;
	SDL_Rect bonus;
	SDL_Rect life;
	SDL_Rect time;
	SDL_Rect total;
	SDL_Rect score_numbers[10];
	SDL_Rect f;
	iPoint position;
	int cam_pos_x;
	int winner = 3; // 0 = P1_win, 1 = P2_win, 2 = draw
	int current_round;
	int pl_won_rounds;
	int en_won_rounds;
	int timer_num;
	int timer_counter;
	int ft = 0; //final round counter
	int lifei;
	int timei;
	int totali;
	bool time_stop;
	bool round_start = false;
	bool blockpoints; 
	void Reset();
	Mix_Chunk* roundFX = nullptr;
	Mix_Chunk* fightFX = nullptr;

	Animation fightAnimX;
	Animation round1Anim;
	Animation round2Anim;
	Animation round3Anim;
	Animation youWinAnim;
	Animation youLoseAnim;
	Animation DrawAnim;
	Animation PixelFadeIn;
	Animation PixelFadeOut;
};

#endif

