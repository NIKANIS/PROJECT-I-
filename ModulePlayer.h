#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"

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
	int Pos_X();
	bool CleanUp();
	void Reset();
	void Damage(const int damage, const int type);
	void godMode();

	int health;
	int score;
	bool godMode_ = false;
	iPoint position;
	Animation* current_animation = nullptr;

public:

	void Jump();
	void Punch();
	void Kick();
	void SpecialAttack();

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
	Animation kickstun;
	Animation punchstun;
	Animation crowchpunch;

	int stuned; //stunt after getting hit 0 = not stuned / 1 = punch stuned / 2 = kick stuned
	bool body_collide;
	bool already_hit;
	bool lockX = false; //locks the sideways movement
	bool jumping = false; //true while jumping
	bool punching = false; //true while punching
	bool kicking = false; //true while kicking
	bool crowchaction = false; //true while crowching
	bool specialattack_ = false; //true while special attacking
	iPoint spatckpos;
	bool sp = false;
	bool skillColDone = false;
	bool fliped = false;
	int t = 0; //jumping coldown time
	int at = 0; //attack coldown time
	int st = 0;		// specialattack coldown time
	int vy = 0; //velocity y
	int player;

	Collider* player_col = nullptr;
	Collider* player_punch_col = nullptr;
	Collider* player_kick_col = nullptr;
	Collider* player_skill_col = nullptr;

	Mix_Chunk* punchFX = nullptr;
	Mix_Chunk* skillFX = nullptr;
	Mix_Chunk* kickFX = nullptr;

	Particle skillJoe;
	Particle skillJoe2;

	Particle skillAndy;
	Particle skillAndy2;

	void OnCollision(Collider*, Collider*, bool colliding) override;
};

#endif //__ModulePlayer_H__