#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleScenePaoPao.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFightManager.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScenePaoPao::ModuleScenePaoPao()
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 512;
	ground.h = 224;

	//background
	background.PushBack({ 36, 72, 512, 224 });
	background.PushBack({ 487, 318, 512, 224 });
	background.speed = 0.05f;
}

ModuleScenePaoPao::~ModuleScenePaoPao()
{}

// Load assets
bool ModuleScenePaoPao::Start()
{
	LOG("Loading Pao Pao scene");

	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/Fatal Fury King of Fighters - Halema School of Capoeira Fight Song (Richard Meyer Theme).ogg");
	App->audio->playMusic(music);

	back_graphics = App->textures->Load("SPRITES FATAL FURY/Stages/1 Pao Pao Cafe(Richard)/sprites paopao.png");

	App->fight_manager->Enable();

	return true;
}

// UnLoad assets
bool ModuleScenePaoPao::CleanUp()
{
	LOG("Unloading Pao Pao scene");
	App->fight_manager->Disable();
	App->audio->Disable();
	App->textures->Unload(back_graphics);

	return true;
}

// Update: draw background
update_status ModuleScenePaoPao::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 0, 0, &(background.GetCurrentFrame()), 0.92f);

	// pressing O game is restarted
	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_paopao, App->scene_intro);
	}

	return UPDATE_CONTINUE;
}