#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneCongrats.h"
#include "ModuleSceneGameOver.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneGameOver::ModuleSceneGameOver()
{

	background = { 0, 0, 304, 224 };

}

ModuleSceneGameOver::~ModuleSceneGameOver()
{}

// Load assets
bool ModuleSceneGameOver::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/37.Game_Over/fatfury1672.png");

	return ret;
}

// Load assets
bool ModuleSceneGameOver::CleanUp()
{
	LOG("Unloading honda stage");
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneGameOver::Update()
{
	// Draw everything --------------------------------------	

	App->render->Blit(graphics, 0, 0, &background, 0.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_intro, App->scene_paopao);
	}

	return UPDATE_CONTINUE;
}