#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFightManager.h"
#include "ModuleRoundDisplay.h"

ModuleRoundDisplay::ModuleRoundDisplay(const int player)
{
	position.x = HUD_X;
	position.y = HUD_Y + 20;

	off.PushBack({ 1,127,17,16 });

	on.PushBack({ 19,127,18,16 });
	on.PushBack({ 19,127,18,16 });
	on.PushBack({ 19,127,18,16 });
	on.PushBack({ 37,127,17,16 });
	on.speed = 0.1f;
	on.loop = true;

	if (player == 0)
		this->player = 0;
	if (player != 0)
		this->player = 1;
}

ModuleRoundDisplay::~ModuleRoundDisplay()
{
}

bool ModuleRoundDisplay::Start()
{
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/UI sprites.png");
	return true;
}

bool ModuleRoundDisplay::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}

update_status ModuleRoundDisplay::Update()
{
	Animation* current_animation = nullptr;

	if (player == 0)
	{

		if (App->fight_manager->Player() >= 1)
		{
			current_animation = &on;
			App->render->Blit(graphics, position.x, position.y, &current_animation->GetCurrentFrame(), 0.0f);
		}else
		{
			current_animation = &off;
			App->render->Blit(graphics, position.x, position.y, &current_animation->GetCurrentFrame(), 0.0f);
		}

		if (App->fight_manager->Player() >= 2)
		{
			current_animation = &on;
			App->render->Blit(graphics, position.x + 18, position.y, &current_animation->GetCurrentFrame(), 0.0f);
		}
		else
		{
			current_animation = &off;
			App->render->Blit(graphics, position.x + 18, position.y, &current_animation->GetCurrentFrame(), 0.0f);
		}
		
	}

	if (player == 1)
	{
		if (App->fight_manager->Enemy() >= 1)
		{
			current_animation = &on;
			App->render->Blit(graphics, position.x + 257, position.y, &current_animation->GetCurrentFrame(), 0.0f);
		}
		else
		{
			current_animation = &off;
			App->render->Blit(graphics, position.x + 257, position.y, &current_animation->GetCurrentFrame(), 0.0f);
		}

		if (App->fight_manager->Enemy() >= 2)
		{
			current_animation = &on;
			App->render->Blit(graphics, position.x + 239, position.y, &current_animation->GetCurrentFrame(), 0.0f);
		}
		else
		{
			current_animation = &off;
			App->render->Blit(graphics, position.x + 239, position.y, &current_animation->GetCurrentFrame(), 0.0f);
		}
	}

	return update_status::UPDATE_CONTINUE;
}