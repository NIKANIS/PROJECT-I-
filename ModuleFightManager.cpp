#include "Application.h"
#include "ModuleFightManager.h"
#include "ModulePlayer.h"
#include "ModuleFightTimer.h"

ModuleFightManager::ModuleFightManager()
{
	pl_won_rounds = 0;
	en_won_rounds = 0;
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

update_status ModuleFightManager::Update()
{

	return update_status::UPDATE_CONTINUE;
}