#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleLifeBar.h"

ModuleLifeBar::ModuleLifeBar(const int player)
{
	position.x = HUD_X;
	position.y = HUD_Y;

	P1photo = { 1,144,15,15 };
	health = { 1,72,100,7 };
	lowhealth.speed = 0.2f;
	lowhealth.loop = true;

	if (player == 0)
	{
		this->player = 0;
		healthy.PushBack({ 1,0,113,17 });

		lowhealth.PushBack({ 1,0,113,17 });
		lowhealth.PushBack({ 1,36,113,17 });

		dead.PushBack({ 1,36,113,17 });
		
	}
	if (player == 1)
	{
		this->player = 1;
		healthy.PushBack({ 1,18,113,17 });

		lowhealth.PushBack({ 1,18,113,17 });
		lowhealth.PushBack({ 1,54,113,17 });

		dead.PushBack({ 1,54,113,17 });
	}
}

ModuleLifeBar::~ModuleLifeBar()
{}

bool ModuleLifeBar::Start()
{
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/UI sprites.png"); 
	return true;
}

bool ModuleLifeBar::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}

update_status ModuleLifeBar::Update()
{
	Animation* current_animation = &healthy;

	if (player == 0)
	{
		position.x = -App->render->camera.x / SCREEN_SIZE;
		health = { 1,72,App->player->Health(),7 };
		if (App->player->Health() <= 20)
		{
			current_animation = &lowhealth;
		}

		if (App->player->Health() <= 0)
		{
			current_animation = &dead;
		}
	}

	if (player == 1)
	{
		position.x = -App->render->camera.x / SCREEN_SIZE;
		health = { 1 + (100 - App->enemy->Health()),72,App->enemy->Health(),7 };
		if (App->enemy->Health() <= 20)
		{
			current_animation = &lowhealth;
		}

		if (App->enemy->Health() <= 0)
		{
			current_animation = &dead;
		}
	}

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x + (160)*player + HUD_X, position.y - r.h, &r, 0.0f);
	App->render->Blit(graphics, position.x + 1 + (256)*player + HUD_X, position.y - r.h + 1, &P1photo, 0.0f);
	App->render->Blit(graphics, (100 - App->enemy->Health())*player + position.x + 17 + (144)*player + HUD_X, position.y - r.h + 9, &health, 0.0f);

	return UPDATE_CONTINUE;
}