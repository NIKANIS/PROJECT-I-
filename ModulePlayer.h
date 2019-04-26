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
	ModulePlayer(const int player);
	~ModulePlayer();

	bool Start();
	update_status Update();
	int Health();
	int Score();
	bool CleanUp();
	void Reset();

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
	Animation specialattack;
	Animation die;
	iPoint position;
	int health;
	int score;
	//bool stunt_hit; //stunt time after getting hit
	bool already_hit;
	bool lockX = false; //locks the sideways movement
	bool jumping = false; //true while jumping
	bool punching = false; //true while punching
	bool kicking = false; //true while kicking
	bool crowchaction = false; //true while crowching
	bool specialattack_ = false; //true while special attacking
	int t = 0; //jumping coldown time
	int at = 0; //attack coldown time
	int vy = 0; //velocity y
	int player;

	Collider* player_col = nullptr;
	Collider* player_punch_col = nullptr;
	Collider* enemy_col = nullptr;
	Collider* enemy_punch_col = nullptr;

	void OnCollision(Collider*, Collider*) override;
};

#endif