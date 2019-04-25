#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFightManager.h"
#include "ModulePlayer.h"
#include "ModuleFightTimer.h"
#include "ModuleInput.h"
#include "ModuleRoundDisplay.h"


ModuleFightManager::ModuleFightManager()
{
	position.x = 151;
	position.y = 103;

	pl_won_rounds = 0;
	en_won_rounds = 0;
	timer_num = 93;
	timer_counter = 0;
	time_stop = false;

	win = { 155,1,123,16 };
	lose = { 155,18,126,16 };
	draw = { 155,35,142,16 };
}

ModuleFightManager::~ModuleFightManager(){}

bool ModuleFightManager::Start() 
{
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/UI sprites.png");

	App->player->Enable();
	App->enemy->Enable();
	App->fight_timer->Enable();
	App->round_pl->Enable();
	App->round_en->Enable();
	return true;
}

bool ModuleFightManager::CleanUp()
{
	App->textures->Unload(graphics);

	App->player->Disable();
	App->enemy->Disable();
	App->fight_timer->Disable();
	App->round_pl->Disable();
	App->round_en->Disable();
	return true;
}

void ModuleFightManager::Reset()
{
	App->player->Reset();
	App->enemy->Reset();
	timer_num = 93;
	timer_counter = 0;
	time_stop = false;
}

void ModuleFightManager::EndTimer()
{
	timer_counter++;
	if (timer_counter == 90 && winner != 0 && winner != 1)
	{
		Reset();
	}
}

update_status ModuleFightManager::Update()
{
	if (timer_num != 0 && !time_stop)
	{
		timer_counter++;
		if (timer_counter == 60)
		{
			timer_num--;
			timer_counter = 0;
		}
	}

	if (App->player->Health() == 0)
	{
		en_won_rounds++;
		time_stop = true;
	}
	else if (App->enemy->Health() == 0)
	{
		pl_won_rounds++;
		time_stop = true;
	}

	if (App->player->Health() == 0 && App->enemy->Health() == 0)
	{
		time_stop = true;
	}

	if (timer_num == 0 && !blockpoints)
	{
		if (App->player->Health() > App->enemy->Health())
		{
			pl_won_rounds++;
			App->render->Blit(graphics, position.x, position.y, &win, 0.0f);
			EndTimer();
		}
		if (App->player->Health() < App->enemy->Health())
		{
			en_won_rounds++;
			App->render->Blit(graphics, position.x, position.y, &lose, 0.0f);
			EndTimer();
		}
		if (App->player->Health() == App->enemy->Health())
		{
			App->render->Blit(graphics, position.x, position.y, &draw, 0.0f);
			EndTimer();
		}
	}

	
	if (pl_won_rounds >= 2 && pl_won_rounds > en_won_rounds)
		winner = 0;
	if (en_won_rounds >= 2 && pl_won_rounds < en_won_rounds)
		winner = 1;

	if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
		Reset();

	return update_status::UPDATE_CONTINUE;
}