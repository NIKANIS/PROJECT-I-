#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleLifeBar.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleLifeBar::ModuleLifeBar()
{
	position.x = HUD_X;
	position.y = HUD_Y;

	P1photo = {1,144,15,15};

	health = { 1,72,100,7 };

	healthy.PushBack({1,0,113,17});

	lowhealth.PushBack({ 1,0,113,17 });
	lowhealth.PushBack({ 1,36,113,17 });
	lowhealth.speed = 0.2f;
	lowhealth.loop = true;

}

ModuleLifeBar::~ModuleLifeBar()
{}

// Load assets
bool ModuleLifeBar::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/UI sprites.png"); 
	return ret;
}

update_status ModuleLifeBar::Update()
{
	Animation* current_animation = &healthy;

	health = { 1,72,App->player->Health(),7 };

	if (App->player->Health() <= 20)
	{
		current_animation = &lowhealth;
	}

	int speed = 1;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r,0.0f);
	App->render->Blit(graphics, position.x +1, position.y - r.h+1, &P1photo, 0.0f);
	App->render->Blit(graphics, position.x + 17, position.y - r.h + 9, &health, 0.0f);

	return UPDATE_CONTINUE;
}