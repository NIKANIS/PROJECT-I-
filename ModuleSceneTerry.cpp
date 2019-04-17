#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleSceneTerry.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneTerry::ModuleSceneTerry()
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 512;
	ground.h = 224;
}

ModuleSceneTerry::~ModuleSceneTerry()
{}

// Load assets
bool ModuleSceneTerry::Start()
{
	LOG("Loading ken scene");
	
	back_graphics = App->textures->Load("SPRITES FATAL FURY/Stages/1 Pao Pao Cafe(Richard)/frame_0.png");

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneTerry::CleanUp()
{
	LOG("Unloading ken scene");
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneTerry::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 0, 0, &ground, 0.75f); // sea and sky
	// TODO 3: make so pressing O the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_terry, App->scene_honda);
	}

	return UPDATE_CONTINUE;
}