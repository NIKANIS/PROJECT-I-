#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleParticles.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleAudio.h"

void ModuleEnemy::Jump() {
	if (jumping) {
		t++;
		position.y = 220 - 7 * t + 0.12*(t*t);
		vy = -7 + 0.24*t;
		if (position.y >= 220) {
			jumping = false;
			position.y = 220;
		}
		if (vy > 0) {
			if (current_animation != &jumpidown)
			{
				jumpidown.Reset();
				current_animation = &jumpidown;
			}
		}
	}
}

int ModuleEnemy::Health()
{
	return health;
}

int ModuleEnemy::Score()
{
	return score;
}

ModuleEnemy::ModuleEnemy()
{
	health = 100;
	already_hit = false;
	score = 0;

	// idle animation done 
	idle.PushBack({ 27, 913, 60, 105 });
	idle.PushBack({ 95, 915, 61, 104 });
	idle.PushBack({ 164, 914, 60, 103 });
	idle.PushBack({ 95, 915, 61, 104 });
	idle.loop = true;
	idle.speed = 0.13f;

	// jump idle up done
	jumpiup.PushBack({ 907, 471, 61, 128 });

	// jump idle down 
	jumpidown.PushBack({ 908, 655, 60, 96 });

	//jump while moving done
	jump.PushBack({ 828, 565 , 63, 107 });

	//go forward done
	forward.PushBack({ 1111, 270, 69, 105 });
	forward.PushBack({ 1193, 271, 59, 104 });
	forward.PushBack({ 1267, 274, 59, 101 });
	forward.PushBack({ 1036, 273, 59, 102 });
	forward.speed = 0.13f;
	forward.loop = true;

	//go backwards done
	backward.PushBack({ 1465, 446, 59, 102 });
	backward.PushBack({ 1396, 445, 55, 104 });
	backward.PushBack({ 1327, 442, 56, 106 });
	backward.PushBack({ 1258, 444, 57, 104 });
	backward.speed = 0.13f;
	backward.loop = true;

	// crowch done
	crowch.PushBack({ 440, 606, 52, 63 });

	// crowch while going backwards and viceversa
	crowchprotecc.PushBack({ 380,607,52,62 });

	//punch while standing done
	punchstanding.PushBack({ 434, 919, 71, 99 });
	punchstanding.PushBack({ 507, 919, 61, 100 });
	punchstanding.PushBack({ 575, 917, 95, 102 });
	punchstanding.PushBack({ 507, 919, 61, 100 });
	punchstanding.PushBack({ 434, 919, 71, 99 });
	punchstanding.speed = 0.17f;
	punchstanding.loop = false;

	//kick while standing done
	kickingstanding.PushBack({ 1119,631,59,103 });
	kickingstanding.PushBack({ 1196,628,47,106 });
	kickingstanding.PushBack({ 1261,642,47,93 });
	kickingstanding.PushBack({ 1314,617,57,120 });
	kickingstanding.PushBack({ 1379,617,42,120 });
	kickingstanding.PushBack({ 1441,612,116,125 });
	kickingstanding.PushBack({ 1572,628,62,117 });
	kickingstanding.PushBack({ 1653,625,57,91 });
	kickingstanding.speed = 0.20f;
	kickingstanding.loop = false;

	//special attack while standing done
	specialattack.PushBack({ 620, 689, 51, 105 });
	specialattack.PushBack({ 547, 682, 54, 112 });
	specialattack.PushBack({ 482, 699, 60, 95 });
	specialattack.PushBack({ 399, 717, 67, 76 });
	specialattack.PushBack({ 399, 717, 67, 76 });
	specialattack.PushBack({ 260, 727, 65, 67 });
	specialattack.PushBack({ 195, 714, 60, 80 });
	specialattack.speed = 0.15f;
	specialattack.loop = false;

	//die
	die.PushBack({ 1929,836,64,155 });
	die.PushBack({ 1851,836,69,155 });
	die.PushBack({ 1756,836,84,155 });
	die.PushBack({ 1644,836,107,155 });
	die.PushBack({ 1542,836,87,155 });
	die.PushBack({ 1425,836,102,155 });
	die.PushBack({ 1303,836,112,155 });
	die.PushBack({ 1178,836,115,155 });
	die.speed = 0.15f;
	die.loop = false;

	//victory
	victory.PushBack({ 699,324,56,136 });
	victory.PushBack({ 772,324,56,136 });
	victory.PushBack({ 839,324,60,136 });
	victory.PushBack({ 908,324,56,136 });
	victory.speed = 0.15f;
	victory.loop = false;

	//hit
	hit.PushBack({ 20, 473, 67, 104 });
	hit.PushBack({ 88, 470, 73, 110 });
	hit.PushBack({ 20, 473, 67, 104 });
	hit.speed = 0.15f;
	hit.loop = false;

}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading player textures");
	health = 100;
	score = 0;
	already_hit = false;

	position.x = 200;
	position.y = 220;
	App->lifebar2->Enable();
	App->enscore->Enable();
	enemy_col = App->collision->AddCollider({ position.x + 10, position.y - 91, 33, 105 }, COLLIDER_ENEMY, App->enemy);
	
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard.png"); // arcade version

	skillFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Special Attacks/FX_BurnKnuckleAttackTerryBogardVoice.wav");
	punchFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Special Attacks/FX_BurnKnuckleAttackTerryBogardVoice.wav");

	return ret;
}

bool ModuleEnemy::CleanUp()
{

	App->lifebar2->Disable();
	App->enscore->Disable();
	
	App->textures->Unload(graphics);

	return true;
}

void ModuleEnemy::Reset()
{
	health = 100;

	position.x = 200;
	position.y = 220;

	current_animation = &idle;
	lockX = false;
	jumping = false;
	punching = false;
	kicking = false;
	crowchaction = false;
	specialattack_ = false;
	t = 0;
	at = 0;
	vy = 0;
}

update_status ModuleEnemy::Update()
{
	if (punching == true) {
		at++;
		if (at == 15)
		{
			enemy_punch_col = App->collision->AddCollider({ position.x + 52, position.y - 90, 41, 12 }, COLLIDER_ENEMY_ATTACK, App->enemy);
		}
		if (at > 20)
		{
			enemy_punch_col->to_delete = true;
			already_hit = false;
		}
		if (at == 35)
		{
			punching = false;
		}
	}

	if (health < 0)
		health = 0;

	int speed = 1;

	if (kicking == true) {
		at++;
		if (at == 20)
		{
			enemy_kick_col = App->collision->AddCollider({ position.x + 43, position.y - 86, 49, 17 }, COLLIDER_ENEMY_ATTACK, App->enemy);
		}
		if (at == 28)
		{
			enemy_kick_col->to_delete = true;
			already_hit = false;
		}
		if (at == 45)
		{

			kicking = false;
		}
	}

	if (specialattack_ == true) {
		at++;

		if (at == 25) //para que añada la particula justo cuando el personaje toque al suelo
		{
			//skill1 = App->collision->AddCollider({ position.x + 40, position.y -40, 16, 40 }, COLLIDER_PLAYER_SKILL, App->enemy);
			App->particles->AddParticle(App->particles->skill, position.x + 40, position.y - 97);
		}
		if (at == 35)
		{
			specialattack_ = false;
		}
	}
	

	Jump();
	if (health == 0)
	{
		if (current_animation != &die)
		{
			die.Reset();
			current_animation = &die;
		}
	}
	else
	{
		if (App->enemy->Health() != 0)
		{			
						
			if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_DOWN)
				health = 0;

			if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_)
			{
				position.x -= speed;
				if (current_animation != &backward && !jumping && current_animation != &crowch)
				{
					backward.Reset();
					current_animation = &backward;
				}
			}			

			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_)
			{
				position.x += speed;
				if (current_animation != &forward && !jumping)
				{
					forward.Reset();
					current_animation = &forward;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && !jumping && !punching && !kicking && !specialattack_)
			{
				if (current_animation != &crowch)
				{
					lockX = true;
					crowchaction = true;
					crowch.Reset();
					current_animation = &crowch;

				}
				if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && !punching && !kicking && !specialattack_)
				{
					if (current_animation != &crowchprotecc)
					{
						crowchprotecc.Reset();
						current_animation = &crowchprotecc;						
					}
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_UP) {
				lockX = false;
				crowchaction = false;
				enemy_col->SetPos(position.x + 10, position.y - 91);
				enemy_col->rect.h = 90;
				enemy_col->rect.w = 33;
			}		

			if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN && !jumping && !punching && !kicking && !specialattack_)
			{
				if (current_animation != &jumpiup)
				{
					jumping = true;
					t = 0;
					jumpiup.Reset();
					current_animation = &jumpiup;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN && !punching && !kicking && !crowchaction && !specialattack_) {
				if (current_animation != &punchstanding && !jumping)
				{
					punching = true;
					at = 0;
					punchstanding.Reset();
					current_animation = &punchstanding;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction && !specialattack_) {
				if (current_animation != &kickingstanding && !jumping && !crowchaction)
				{
					kicking = true;
					at = 0;
					kickingstanding.Reset();
					current_animation = &kickingstanding;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction) {
				if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_)
				{
					specialattack_ = true;
					at = 0;
					specialattack.Reset();
					current_animation = &specialattack;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
				&& !jumping && !punching && !kicking && !specialattack_)
				current_animation = &idle;
			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT
				&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT
				&& App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
				&& !jumping && !punching && !kicking && !specialattack_)
				current_animation = &idle;

			if (current_animation == &crowch)
			{
				enemy_col->rect.h = 65;
				enemy_col->rect.w = 41;
				enemy_col->SetPos(position.x + 5, position.y - 67);
			}
			if (current_animation == &crowchprotecc)
			{
				enemy_col->rect.h = 65;
				enemy_col->rect.w = 41;
				enemy_col->SetPos(position.x + 5, position.y - 67);
			}
			else
			{
				enemy_col->SetPos(position.x + 10, position.y - 91);
				enemy_col->rect.h = 90;
				enemy_col->rect.w = 33;
			}			
		}
		else
		{
			if (current_animation != &victory)
			{
				victory.Reset();
				current_animation = &victory;
			}
			
		}
	}

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r,true);

	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* a, Collider* b)
{
	if (a->type == COLLIDER_ENEMY_ATTACK && b->type == COLLIDER_PLAYER && !already_hit)
	{
		already_hit = true;
		App->player->health -= 20;
	}	
}