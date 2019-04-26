#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneCongrats.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

ModuleSceneCongrats::ModuleSceneCongrats()
{

	background = {0, 0, 304, 224};

}

ModuleSceneCongrats::~ModuleSceneCongrats()
{}

// Load assets
bool ModuleSceneCongrats::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/35.Fatal_Fury_End_Fade_Out/fatfury1666.png");

	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/Fatal Fury King of Fighters - Winner Screen.ogg");
	App->audio->playMusic(music);


	return ret;
}

// Load assets
bool ModuleSceneCongrats::CleanUp()
{
	LOG("Unloading honda stage");
	App->player->Disable();
	App->textures->Unload(graphics);
	App->audio->Disable();
	App->textures->Unload(graphics);

	return true;
}

	// Draw everything --------------------------------------	
update_status ModuleSceneCongrats::Update()
{
	App->render->Blit(graphics, 0, 0, &background, 0.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_congrats, App->scene_intro);
	}

	return UPDATE_CONTINUE;
}