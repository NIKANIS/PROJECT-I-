#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(int player);
	~ModulePlayer();

	bool Start();
	update_status Update();
	int Health();
	int Score();
	bool CleanUp();

private:

	void Jump();
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation jumpiup;
	Animation jumpidown;
	Animation jump;
	Animation crowch;
	Animation crowchprotecc;
	Animation forward;
	Animation backward;
	Animation punchstanding;
	Animation kickingstanding;
	iPoint position;
	int health;
	int score;
	bool lockX = false; //locks the sideways movement
	bool jumping = false; //true while jumping
	bool punching = false; //true while punching
	bool kicking = false; //true while kicking
	bool crowchaction = false; //true while crowching
	int t = 0; //jumping coldown time
	int at = 0; //attack coldown time
	int vy = 0; //velocity y
	int player;
};

#endif