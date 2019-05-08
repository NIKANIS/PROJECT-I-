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
	background	 =	{ 8, 5, 308, 240 };

	pao_pao		 =	{ 299, 523, 96, 64};
	sound_beach  =	{399, 523, 96, 64};
	west_sub	 =	{499, 523,96, 64};
	howard_arena =	{599, 523, 96, 64};

	pao_pao_selected = { 299, 727, 96, 64 };
	sound_beach_selected = { 399, 727, 96, 64 };
	west_sub_selected = { 499, 727,96, 64 };
	howard_arena_selected = { 599, 727, 96, 64 };


	map_1.PushBack({ 299, 591, 96, 64});
	map_1.PushBack({ 299, 659, 96, 64 });
	map_1.speed = 0.1f;
	map_1.loop = true;
	   
	map_2.PushBack({ 399, 591, 96, 64 });
	map_2.PushBack({ 399, 659, 96, 64 });
	map_2.speed = 0.1f;;
	map_2.loop = true;
	   
	map_3.PushBack({ 499, 591, 96, 64 });
	map_3.PushBack({ 499, 659, 96, 64 });
	map_3.speed = 0.1f;;	   	
	map_3.loop = true;		   	
	   						   	
	map_4.PushBack({ 599, 591, 96, 64 });
	map_4.PushBack({ 599, 659, 96, 64 });
	map_4.speed = 0.1f;;
	map_4.loop = true;
}

ModuleSceneMap::~ModuleSceneMap()
{}

// Load assets
bool ModuleSceneMap::Start()
{
	LOG("Loading Map scene");
	back_graphics = App->textures->Load("SPRITES FATAL FURY/GENERAL MENUS/Neo Geo NGCD - Fatal Fury King of Fighters - Select & Map Screens.png");

	map = 1;

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

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN && map != 4) {
		map++;
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN && map != 1) {
		map--;
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN && map != 3 && map != 4) {
		map+= 2;
	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN && map != 1 && map != 2) {
		map-= 2;
	}


	switch (map)
	{
		case 1:
		{
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75, &(map_1.GetCurrentFrame()), false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 75, &sound_beach, false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75 + 64, &west_sub, false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 75 + 64, &howard_arena, false, 0.92f);

		}	break;

		case 2:
		{
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75, &pao_pao, false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 75, &(map_2.GetCurrentFrame()), false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75 + 64, &west_sub, false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 75 + 64, &howard_arena, false, 0.92f);

		}	break;

		case 3:
		{
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75, &pao_pao, false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 75, &sound_beach, false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75 + 64, &(map_3.GetCurrentFrame()), false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 75 + 64, &howard_arena, false, 0.92f);

		}	break;

		case 4:
		{
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75,&pao_pao , false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 75, &sound_beach, false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75 + 64, &west_sub, false, 0.92f);
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 75 + 64, &(map_4.GetCurrentFrame()), false, 0.92f);

		}	break;
	}


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		if (map == 1)
		{
			map_1.speed = 0;
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 75, &pao_pao_selected, false, 0.92f);
			App->fade->FadeToBlack(App->scene_map, (Module*)App->scene_paopao);
		}
			
	}

	return UPDATE_CONTINUE;
}