#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleLifeBar.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

int ModulePlayer::Health() 
{
	return health;
}

ModulePlayer::ModulePlayer()
{
	health = 100;

	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({27, 914, 60, 105});
	idle.PushBack({95, 916, 61, 104});
	idle.PushBack({164, 916, 60, 103});
	idle.speed = 0.1f;

	//// walk forward animation (arcade sprite sheet)
	////forward.frames.PushBack({9, 136, 53, 83});
	//forward.PushBack({78, 131, 60, 88});
	//forward.PushBack({162, 128, 64, 92});
	//forward.PushBack({259, 128, 63, 90});
	//forward.PushBack({352, 128, 54, 91});
	//forward.PushBack({432, 131, 50, 89});
	//forward.speed = 0.1f;

	//// walk backward animation (arcade sprite sheet)
 //   //forward.frames.PushBack({9, 136, 53, 83});
	//backward.PushBack({ 78, 131, 60, 88 });
	//backward.PushBack({ 162, 128, 64, 92 });
	//backward.PushBack({ 259, 128, 63, 90 });
	//backward.PushBack({ 352, 128, 54, 91 });
	//backward.PushBack({ 432, 131, 50, 89 });
	//backward.speed = 0.1f;

	//punch
	punch.PushBack({ 434, 918, 73, 101 });
	punch.PushBack({ 506, 918, 64, 102});
	punch.PushBack({ 574, 916, 97, 104 }); 
	punch.PushBack({ 434, 918, 73, 101 });
	punch.speed = 0.1f;

	//kick
	kick.PushBack({ 448, 805, 61, 105 });
	kick.PushBack({ 512, 802, 49, 108 });
	kick.PushBack({ 565, 812, 81, 99 });
	kick.speed = 0.08f;

//	//jump
//	jump.PushBack({ 16, 846, 58, 88 });
//	jump.PushBack({ 99, 822, 58, 108 });
//	jump.PushBack({ 173, 804, 54, 90 });
//	jump.PushBack({ 250, 797, 56, 79 });
//	jump.PushBack({ 326, 812, 51, 91 });
//	jump.PushBack({ 395, 809, 50, 90 });
//	jump.PushBack({ 462, 818, 58, 109 });
//	jump.PushBack({ 16, 846, 58, 88 });
//	jump.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	App->lifebar->Enable();
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard.png"); // arcade version
	return ret;
}

bool ModulePlayer::CleanUp()
{
	App->lifebar->Disable();

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	if (health < 0)
		health = 0;

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_L] == 1)
	{
		health -= 10;
	}

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

	if (App->input->keyboard[SDL_SCANCODE_X] == 1)
	{
		App->particles->skill.life = 1000;
		App->particles->skill.speed.x = 1;
		App->particles->AddParticle(App->particles->skill, position.x+50, position.y-75);
	}
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}