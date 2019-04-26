#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_timer.h"

void ModulePlayer::Jump() {
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

int ModulePlayer::Health() 
{
	return health;
}

int ModulePlayer::Score()
{
	return score;
}

ModulePlayer::ModulePlayer(const int player)
{
	health = 100;
	already_hit = false;
	if (player == 0)
	{
		this->player = 0;
	}
	score = 0;

	if (player != 0)
	{
		this->player = 1;

	}
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
	forward.PushBack({ 1030, 269, 62, 105 });
	forward.PushBack({ 1104, 265, 82, 115 });
	forward.PushBack({ 1187, 267, 69, 111 });
	forward.PushBack({ 1267, 272, 69, 111 });
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
	crowch.PushBack({ 264, 946, 57, 74 });

	// crowch while going backwards and viceversa
	crowchprotecc.PushBack({ 839,17,44,92 });

	//punch while standing done
	punchstanding.PushBack({ 434, 917, 72, 101 });
	punchstanding.PushBack({ 506, 917, 63, 102 });
	punchstanding.PushBack({ 578, 916, 99, 91 });
	punchstanding.PushBack({ 506, 917, 63, 102 });
	punchstanding.PushBack({ 434, 917, 72, 101 });
	punchstanding.speed = 0.13f;
	punchstanding.loop = false;

	//kick while standing done
	kickingstanding.PushBack({1035,122,48,126});
	kickingstanding.PushBack({1088,122,58,126});
	kickingstanding.PushBack({1153,122,43,126});
	kickingstanding.PushBack({1215,122,117,126});
	kickingstanding.PushBack({1346,122,63,126});
	kickingstanding.speed = 0.15f;
	kickingstanding.loop = false;

	//special attack while standing done
	specialattack.PushBack({ 613, 684, 64, 115 });
	specialattack.PushBack({ 550, 681, 62, 115 });
	specialattack.PushBack({ 481, 694, 64, 104 });
	specialattack.PushBack({ 398, 705, 84, 92 });
	specialattack.PushBack({ 328, 713, 72, 85 });
	specialattack.PushBack({ 258, 720, 69, 78 });
	specialattack.PushBack({ 192, 711, 65, 86 });
	specialattack.speed = 0.15f;
	specialattack.loop = false;

	//die
	die.PushBack({1929,836,64,155});
	die.PushBack({1851,836,69,155});
	die.PushBack({1756,836,84,155});
	die.PushBack({1644,836,107,155});
	die.PushBack({1542,836,87,155});
	die.PushBack({1425,836,102,155});
	die.PushBack({1303,836,112,155});
	die.PushBack({1178,836,115,155});
	die.speed = 0.15f;
	die.loop = false;

	//victory
	victory.PushBack({699,324,56,136});
	victory.PushBack({772,324,56,136});
	victory.PushBack({839,324,60,136});
	victory.PushBack({908,324,56,136});
	victory.speed = 0.15f;
	victory.loop = false;

	//hit
	hit.PushBack({ 20, 473, 67, 104 });
	hit.PushBack({ 88, 470, 73, 110 });
	hit.PushBack({ 20, 473, 67, 104 });
	hit.speed = 0.15f;
	hit.loop = false;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	health = 100;
	score = 0;
	already_hit = false;
	if (player == 0) 
	{
		position.x = 100;
		position.y = 220;
		App->lifebar->Enable();
		App->plscore->Enable();
		player_col = App->collision->AddCollider({ position.x+10, position.y - 91, 33, 90 }, COLLIDER_PLAYER, App->enemy);
	}
	if (player == 1) 
	{
		position.x = 200;
		position.y = 220;
		App->lifebar2->Enable();
		App->enscore->Enable();
		enemy_col = App->collision->AddCollider({ position.x+10, position.y - 91, 33, 90 }, COLLIDER_ENEMY, App->player);
	}
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard.png"); // arcade version

	return ret;
}

bool ModulePlayer::CleanUp()
{
	if (player == 0)
	{
		App->lifebar->Disable();
		App->plscore->Disable();
	}
	if (player == 1)
	{
		App->lifebar2->Disable();
		App->enscore->Disable();
	}
	App->textures->Unload(graphics);

	return true;
}

void ModulePlayer::Reset()
{
	health = 100;
	if (player == 0)
	{
		position.x = 100;
		position.y = 220;
	}
	if (player == 1)
	{
		position.x = 200;
		position.y = 220;
	}

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

update_status ModulePlayer::Update()
{
	if (punching == true) {
		at++;
		if (at == 15)
		{
			if(player == 0)
				player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 80, 41, 17 }, COLLIDER_PLAYER_ATTACK, App->enemy);
			if (player == 1)
				player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 80, 41, 17 }, COLLIDER_ENEMY_ATTACK, App->player);
		}
		if (at > 20)
		{
			player_punch_col->to_delete = true;
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
			if(player == 0)
				player_kick_col = App->collision->AddCollider({ position.x + 43, position.y - 86, 49, 17 }, COLLIDER_PLAYER_ATTACK, App->enemy);
			if (player == 1)																   
				player_kick_col = App->collision->AddCollider({ position.x + 43, position.y - 86, 49, 17 }, COLLIDER_ENEMY_ATTACK, App->player);
		}
		if (at == 28)
		{
			player_kick_col->to_delete = true;
			already_hit = false;
		}
		if (at == 32)
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
			if (player == 0)
			{
				if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
				{
					health = 0;
				}

				if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_)
				{
					position.x -= speed;

					if (current_animation != &backward && !jumping && current_animation != &crowch)
					{
						backward.Reset();
						current_animation = &backward;
					}

				}

				if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_)
				{
					position.x += speed;
					if (current_animation != &forward && !jumping)
					{
						forward.Reset();
						current_animation = &forward;
					}

				}

				if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !jumping && !punching && !kicking && !specialattack_)
				{
					if (current_animation != &crowch)
					{
						lockX = true;
						crowchaction = true;
						crowch.Reset();
						current_animation = &crowch;
					}
					if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !punching && !kicking && !specialattack_)
					{
						if (current_animation != &crowchprotecc)
						{
							crowchprotecc.Reset();
							current_animation = &crowchprotecc;
						}
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP) {
					lockX = false;
					crowchaction = false;
					player_col->SetPos(position.x + 10, position.y - 91);
					player_col->rect.h = 90;
					player_col->rect.w = 33;
				}

				if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && !jumping && !punching && !kicking && !specialattack_)
				{
					if (current_animation != &jumpiup)
					{
						jumping = true;
						t = 0;
						jumpiup.Reset();
						current_animation = &jumpiup;
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN && !punching && !kicking && !crowchaction && !specialattack_) {
					if (current_animation != &punchstanding && !jumping)
					{
						punching = true;
						at = 0;
						punchstanding.Reset();
						current_animation = &punchstanding;
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction && !specialattack_) {
					if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_)
					{
						kicking = true;
						at = 0;
						kickingstanding.Reset();
						current_animation = &kickingstanding;
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction) {
					if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_)
					{
						specialattack_ = true;
						at = 0;
						specialattack.Reset();
						current_animation = &specialattack;
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
					&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
					&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
					&& !jumping && !punching && !kicking && !specialattack_)
					current_animation = &idle;
				if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
					&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
					&& App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
					&& !jumping && !punching && !kicking && !specialattack_)
					current_animation = &idle;
				
				if (current_animation == &crowch)
				{
					player_col->rect.h = 65;
					player_col->rect.w = 41;
					player_col->SetPos(position.x + 5, position.y - 67);
				}
				else
				{
					player_col->SetPos(position.x + 10, position.y - 91);
					player_col->rect.h = 90;
					player_col->rect.w = 33;
				}	
				//if (skillColDone = true)
				//{
				//	skill1->SetPos(App->particles->skill.position.x, App->particles->skill.position.y);
				//}
				
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
		if (App->player->Health() != 0)
		{
			if (player == 1)
			{
				enemy_col->SetPos(position.x + 10, position.y - 91);
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

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* a, Collider* b)
{
	if (player == 0) {
		if (b->type == COLLIDER_PLAYER_ATTACK && a->type == COLLIDER_ENEMY && !already_hit)
		{
			already_hit = true;
			App->enemy->health -= 20;

		}
	}
	if (player == 1)
	{
		if (b->type == COLLIDER_ENEMY_ATTACK && a->type == COLLIDER_PLAYER && !already_hit)
		{
			already_hit = true;
			App->player->health -= 20;
		}
	}
}

