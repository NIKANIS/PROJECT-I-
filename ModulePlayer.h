#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	int Health();
	int Score();
	bool CleanUp();
	void Reset();

	int health;
	int score;
	iPoint position;
	Animation* current_animation = nullptr;

public:

	void Jump();
	SDL_Texture* graphics = nullptr;
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
	Animation victory;
	Animation hit;
	

	//bool stunt_hit; //stunt time after getting hit
	bool already_hit;
	bool lockX = false; //locks the sideways movement
	bool jumping = false; //true while jumping
	bool punching = false; //true while punching
	bool kicking = false; //true while kicking
	bool crowchaction = false; //true while crowching
	bool specialattack_ = false; //true while special attacking
	bool skillColDone = false;
	bool fliped = false;
	int t = 0; //jumping coldown time
	int at = 0; //attack coldown time
	int vy = 0; //velocity y
	int player;

	Collider* player_col = nullptr;
	Collider* player_punch_col = nullptr;
	Collider* player_kick_col = nullptr;
	Collider* enemy_col = nullptr;
	Collider* enemy_punch_col = nullptr;
	Collider* enemy_kick_col = nullptr;
	Collider* skill1 = nullptr;
	Collider* skill2 = nullptr;
	Collider* skill3 = nullptr;
	Collider* skill4 = nullptr;
	Collider* skill5 = nullptr;


	Mix_Chunk* punchFX = nullptr;
	Mix_Chunk* skillFX = nullptr;
	Mix_Chunk* kickFX = nullptr;

	void OnCollision(Collider*, Collider*) override;
};

#endif