#include "Globals.h"
#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneCongrats.h"
#include "ModuleSceneGameOver.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"
#include "ModuleFightTimer.h"
#include "ModuleFightManager.h"
#include "ModuleCollision.h"
#include "ModuleRoundDisplay.h"
#include "ModuleSceneChoosePlayer.h"
#include "ModuleSceneMap.h"


ModuleSceneMap::ModuleSceneMap()
{
	background = { 8, 5, 308, 240 };

	pao_pao ={ 299, 523, 96, 64 };
	sound_beach = {399, 523, 96, 64};
	west_sub = {499, 523,96, 64};
	howard_arena = {599, 523, 96, 64};
}

ModuleSceneMap::~ModuleSceneMap()
{}

// Load assets
bool ModuleSceneMap::Start()
{
	LOG("Loading Map scene");
	back_graphics = App->textures->Load("SPRITES FATAL FURY/GENERAL MENUS/Neo Geo NGCD - Fatal Fury King of Fighters - Select & Map Screens.png");

	return true;
}

// UnLoad assets
bool ModuleSceneMap::CleanUp()
{
	LOG("Unloading Map scene");
;
	App->textures->Unload(back_graphics);
	return true;
}

// Update: draw background
update_status ModuleSceneMap::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 0, 0, &background, false, 0.92f);
	App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75, &pao_pao, false, 0.92f);
	App->render->Blit(back_graphics, SCREEN_WIDTH / 2 , 75, &sound_beach, false, 0.92f);
	App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75 + 64, &west_sub, false, 0.92f);
	App->render->Blit(back_graphics, SCREEN_WIDTH / 2 , 75 + 64, &howard_arena, false, 0.92f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_map, (Module*)App->scene_paopao);
	}

	return UPDATE_CONTINUE;
}