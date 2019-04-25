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
	if (player == 0)
	{
		this->player = 0;
		position.x = 100;
		position.y = 220;
	}
	if (player != 0)
	{
		this->player = 1;
		position.x = 200;
		position.y = 220;
	}
	// idle animation
	idle.PushBack({ 0, 19, 48, 90 });
	idle.PushBack({ 49, 18, 49, 91 });
	idle.PushBack({ 98, 17, 48, 92 });
	idle.PushBack({ 49, 18, 49, 91 });
	idle.loop = true;
	idle.speed = 0.13f;

	// jump idle up
	jumpiup.PushBack({ 146, 0, 43, 109 });

	// jump idle down
	jumpidown.PushBack({ 189,27,48,82 });

	//jump while moving
	jump.PushBack({ 309,18,47,91 });

	//go forward
	forward.PushBack({ 356,15,57,94 });
	forward.PushBack({ 413,16,49,93 });
	forward.PushBack({ 462,19,50,90 });
	forward.PushBack({ 512,19,48,90 });
	forward.speed = 0.13f;
	forward.loop = true;

	//go backwards
	backward.PushBack({ 560,18,51,91 });
	backward.PushBack({ 611,16,47,93 });
	backward.PushBack({ 658,15,47,94 });
	backward.PushBack({ 705,16,45,93 });
	backward.speed = 0.13f;
	backward.loop = true;

	// crowch
	crowch.PushBack({ 750,16,44,92 });

	// crowch while going backwards and viceversa
	crowchprotecc.PushBack({ 839,17,44,92 });

	//punch while standing
	punchstanding.PushBack({ 0,114,58,88 });
	punchstanding.PushBack({ 59,114,45,88 });
	punchstanding.PushBack({ 103,111,79,91 });
	punchstanding.PushBack({ 59,114,45,88 });
	punchstanding.PushBack({ 0,114,58,88 });
	punchstanding.speed = 0.13f;
	punchstanding.loop = false;

	//kick while standing
	kickingstanding.PushBack({ 1,208,49,90 });
	kickingstanding.PushBack({ 51,206,39,92 });
	kickingstanding.speed = 0.13f;
	kickingstanding.loop = false;

	//special attack while standing
	specialattack.PushBack({ 2,307,42,92 });
	specialattack.PushBack({ 45,300,44,99 });
	specialattack.PushBack({ 90,315,49,84 });
	specialattack.PushBack({ 140,332,55,67 });
	specialattack.speed = 0.15f;
	specialattack.loop = false;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	if (player == 0) 
	{
		App->lifebar->Enable();
		App->plscore->Enable();
		player_col = App->collision->AddCollider({ position.x+10, position.y - 91, 33, 90 }, COLLIDER_PLAYER);
	}
	if (player == 1) 
	{
		App->lifebar2->Enable();
		App->enscore->Enable();
		enemy_col = App->collision->AddCollider({ position.x+10, position.y - 91, 33, 90 }, COLLIDER_ENEMY, App->player);
	}
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/Terry Bogard.gif"); // arcade version
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
		this->player = 0;
		position.x = 100;
		position.y = 220;
	}
	if (player != 0)
	{
		this->player = 1;
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
		if (at == 35)
		{
			kicking = false;
		}
	}

	if (specialattack_ == true) {
		at++;
		if (at == 25) //para que añada la particula justo cuando el personaje toque al suelo
		{
			App->particles->AddParticle(App->particles->skillsmall, position.x + 40, position.y - 42);
		}
		if (at == 35)
		{
			specialattack_ = false;
		}
	}

	Jump();

	if (player == 0)
	{
		//health--;
		if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
			health = 0;

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
		player_col->SetPos(position.x+10, position.y - 91);
		
	}

	if (player == 1)
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

		enemy_col->SetPos(position.x+10, position.y - 91);
	}
	

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider*, Collider*)
{
	App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_gameover);
}
