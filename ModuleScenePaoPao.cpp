#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleScenePaoPao.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFightTimer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScenePaoPao::ModuleScenePaoPao()
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 512;
	ground.h = 224;
}

ModuleScenePaoPao::~ModuleScenePaoPao()
{}

// Load assets
bool ModuleScenePaoPao::Start()
{
	LOG("Loading ken scene");
	
	back_graphics = App->textures->Load("SPRITES FATAL FURY/Stages/1 Pao Pao Cafe(Richard)/frame_0.png");
	back_graphics1 = App->textures->Load("SPRITES FATAL FURY/Stages/1 Pao Pao Cafe(Richard)/frame_1.png");

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemy->Enable();
	App->fight_timer->Enable();

	return true;
}

// UnLoad assets
bool ModuleScenePaoPao::CleanUp()
{
	LOG("Unloading ken scene");
	App->player->Disable();
	App->enemy->Disable();
	App->fight_timer->Disable();

	return true;
}

// Update: draw background
update_status ModuleScenePaoPao::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 0, 0, &ground, 0.75f); // background

	// pressing O game is restarted
	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_paopao, App->scene_intro);
	}

	return UPDATE_CONTINUE;
}