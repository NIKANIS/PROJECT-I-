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
}

update_status ModuleFightManager::Update()
{
	if (timer_num != 0)
	{
		timer_counter++;
		if (timer_counter == 60)
		{
			timer_num--;
			timer_counter = 0;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
		Reset();

	return update_status::UPDATE_CONTINUE;
}