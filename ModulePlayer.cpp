#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

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

ModulePlayer::ModulePlayer()
{
	health = 100;

	position.x = 100;
	position.y = 220;

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
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	App->lifebar->Enable();
	App->plscore->Enable();
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/Terry Bogard.gif"); // arcade version
	return ret;
}

bool ModulePlayer::CleanUp()
{
	App->lifebar->Disable();
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	if (punching == true) {
		at++;
		if (at == 35)
		{
			//current_animation = &idle;
			punching = false;
		}
	}
	if (health < 0)
		health = 0;

	int speed = 1;

	Jump();
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !lockX && !punching)
	{
		position.x -= speed;

		if (current_animation != &backward && !jumping && current_animation != &crowch)
		{
			backward.Reset();
			current_animation = &backward;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !lockX && !punching)
	{
		position.x += speed;
		if (current_animation != &forward && !jumping)
		{
			forward.Reset();
			current_animation = &forward;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !jumping && !punching)
	{
		if (current_animation != &crowch)
		{
			lockX = true;
			crowch.Reset();
			current_animation = &crowch;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !punching)
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
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && !jumping && !punching)
	{
		if (current_animation != &jumpiup)
		{
			jumping = true;
			t = 0;
			jumpiup.Reset();
			current_animation = &jumpiup;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN && !punching) {
		if (current_animation != &punchstanding && !jumping)
		{
			punching = true;
			at = 0;
			punchstanding.Reset();
			current_animation = &punchstanding;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& !jumping && !punching)
		current_animation = &idle;
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& !jumping && !punching)
		current_animation = &idle;
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}