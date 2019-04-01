#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;

	// walk backward animation (arcade sprite sheet)
//forward.frames.PushBack({9, 136, 53, 83});
	backward.PushBack({ 78, 131, 60, 88 });
	backward.PushBack({ 162, 128, 64, 92 });
	backward.PushBack({ 259, 128, 63, 90 });
	backward.PushBack({ 352, 128, 54, 91 });
	backward.PushBack({ 432, 131, 50, 89 });
	backward.speed = 0.1f;

	//punch
	punch.PushBack({ 16, 270, 80, 95 });
	punch.PushBack({ 110, 265, 94, 95});
	punch.speed = 0.1f;

	//kick
	kick.PushBack({ 600, 265, 70, 96 });
	kick.PushBack({ 690, 265, 75, 95 });
	kick.PushBack({ 770, 265, 125, 95 });
	kick.speed = 0.1f;

	//jump
	jump.PushBack({ 16, 846, 58, 88 });
	jump.PushBack({ 99, 822, 58, 108 });
	jump.PushBack({ 173, 804, 54, 90 });
	jump.PushBack({ 250, 797, 56, 79 });
	jump.PushBack({ 326, 812, 51, 91 });
	jump.PushBack({ 395, 809, 50, 90 });
	jump.PushBack({ 462, 818, 58, 109 });
	jump.PushBack({ 16, 846, 58, 88 });
	jump.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_Q] == 1)
	{
		current_animation = &punch;
	}

	if (App->input->keyboard[SDL_SCANCODE_E] == 1)
	{
		current_animation = &kick;
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &jump;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}