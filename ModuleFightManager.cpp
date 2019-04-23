#include "Application.h"
#include "ModuleFightManager.h"
#include "ModulePlayer.h"
#include "ModuleFightTimer.h"
#include "ModuleInput.h"


ModuleFightManager::ModuleFightManager()
{
	pl_won_rounds = 0;
	en_won_rounds = 0;
	timer_num = 93;
	timer_counter = 0;
	time_stop = false;
}

ModuleFightManager::~ModuleFightManager(){}

bool ModuleFightManager::Start() 
{
	App->player->Enable();
	App->enemy->Enable();
	App->fight_timer->Enable();
	return true;
}

bool ModuleFightManager::CleanUp()
{
	App->player->Disable();
	App->enemy->Disable();
	App->fight_timer->Disable();
	return true;
}

int ModuleFightManager::Time()
{
	return timer_num;
}

void ModuleFightManager::Reset()
{
	App->player->Reset();
	App->enemy->Reset();
	timer_num = 93;
	timer_counter = 0;
	time_stop = false;
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
		pl_won_rounds++;
		en_won_rounds++;
		time_stop = true;
	}

	if (timer_num == 0)
	{
		if (App->player->Health() > App->enemy->Health())
			pl_won_rounds++;
		if (App->player->Health() < App->enemy->Health())
			en_won_rounds++;
		if (App->player->Health() == App->enemy->Health())
		{
			pl_won_rounds++;
			en_won_rounds++;
		}
		time_stop = true;
	}

	
	if (pl_won_rounds >= 2 && pl_won_rounds > en_won_rounds)
		winner = 0;
	if (en_won_rounds >= 2 && pl_won_rounds < en_won_rounds)
		winner = 1;

	if (time_stop == true && winner != 0 && winner != 1)
		Reset();

	if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
		Reset();

	return update_status::UPDATE_CONTINUE;
}