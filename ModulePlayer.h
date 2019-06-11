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
	ModulePlayer(int player);
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


	bool godMode_ = false;
	iPoint position;
	Animation* current_animation = nullptr;

	bool sp = false;
	bool sp2 = false;
	bool sp3 = false;
	bool sp4 = false;
	int score;

	void OnCollision(Collider*, Collider*, bool colliding) override;

	Mix_Chunk* punchFX = nullptr;
	Mix_Chunk* skillFX = nullptr;
	Mix_Chunk* kickFX = nullptr;


	SDL_Texture* graphics = nullptr;

	Animation idle;
	Animation jumpiup;
	Animation jumpfup;
	Animation jumpbup;
	Animation jumpidown;
	Animation jumpfbdown;
	Animation jump;
	Animation crowch;
	Animation crowchprotecc;
	Animation forward;
	Animation backward;
	Animation punchstanding;
	Animation kickingstanding;
	Animation lowkick;
	Animation specialattack;
	Animation die;
	Animation victory;
	Animation hit;
	Animation kickstun;
	Animation punchstun;
	Animation crowchpunch;
	Animation takedown_done;
	Animation takedown_recieved;
	Animation takedown_recieved2;
	Animation takedown_fail;
	Animation airkickstraight;
	Animation airkickdiagonal;
	Animation airpunchstraight;
	Animation airpunchdiagonal;
	Animation JoeSpecialKick;
	Animation JoeSpecialKick2;
	Animation JoeSpecialKnee;
	Animation JoeMultiplePunch;
	Animation JoeYellowPunch;
	Animation TerrySpecialKick;
	Animation TerrySpecialPunch1;
	Animation TerrySpecialPunch2;
	

private:

	Collider* player_col = nullptr;
	Collider* player_punch_col = nullptr;
	Collider* player_kick_col = nullptr;
	Collider* player_skill_col = nullptr;
	Collider* enemy_skill_col = nullptr;

	Particle skillJoe;
	Particle skillJoe2;

	Particle skillAndy;
	Particle skillAndy2;

	Particle skillJoe_;
	Particle skillJoe2_;


	Particle skillAndy_;
	Particle skillAndy2_;

	void Jump();
	void Punch();
	void Kick();
	void SpecialAttack();
	void SpecialAttack2();
	void SpecialAttack3();
	void SpecialAttack4();
	void LowKick();
	void AirKick();
	void TakeDown();


	void LoadJoeAnimations();
	void LoadTerryAnimations();
	void LoadAndyAnimations();

	iPoint spatckpos;

	int stuned; //stunt after getting hit 0 = not stuned / 1 = punch stuned / 2 = kick stuned
	int t = 0; //jumping coldown time
	int at = 0; //attack coldown time
	int jt = 0;
	int st = 0;		// specialattack coldown time
	int vy = 0; //velocity y
	int tktempo = 0;
	int player;
	int health;
	int jumptype; //0 = idle jump / 1 = forward jump / 2 = backwards jump
	int jumpspeed = 2;
	int width = 0;
	//int draw_pos_x = 0;
	int character;

	bool body_collide;
	bool already_hit;
	bool lockX = false; //locks the sideways movement
	bool jumping = false; //true while jumping
	bool punching = false; //true while punching
	bool kicking = false; //true while kicking
	bool crowchaction = false; //true while crowching
	bool specialattack_ = false; //true while special attacking
	bool specialattack2_ = false;
	bool lowkicking = false; //true while lowkicking
	bool airkicking = false;
	bool airpunching = false;
	bool takingdown = false; // true while taking down the opponent o failing the takedown
	bool skillColDone = false;
	bool fliped = false;
	
};

#endif //__ModulePlayer_H__