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
#include "SDL/include/SDL_timer.h"


ModuleSceneMap::ModuleSceneMap()
{
	background	 =	{ 8, 5, 308, 240 };

	pao_pao		 =	{ 299, 523, 96, 64};
	sound_beach  =	{399, 523, 96, 64};
	west_sub	 =	{499, 523,96, 64};
	howard_arena =	{599, 523, 96, 64};

	map_select_tittle = { 598, 167, 120, 16 };

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
	App->audio->Start();

	back_graphics = App->textures->Load("SPRITES FATAL FURY/GENERAL MENUS/Neo Geo NGCD - Fatal Fury King of Fighters - Select & Map Screens.png");
	select = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/FX/FX_SelectHover.wav");
	selected = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/FX/FX_ChooseSelection.wav");
	map = 1;

	return true;
}

// UnLoad assets
bool ModuleSceneMap::CleanUp()
{
	LOG("Unloading Map scene");
	App->audio->Disable();
	App->textures->Unload(back_graphics);
	map_chosen = false;
	return true;
}

// Update: draw background
update_status ModuleSceneMap::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 0, 0, &background, false, 0.92f);
	App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - map_select_tittle.w/2, 60, &map_select_tittle, false, 0.92f);

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN && map != 4) {
		App->audio->playFx(select);
		map++;
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN && map != 1) {
		App->audio->playFx(select);
		map--;
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN && map != 3 && map != 4) {
		App->audio->playFx(select);
		map+= 2;
	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN && map != 1 && map != 2) {
		App->audio->playFx(select);
		map-= 2;
	}

	switch (map)
	{
	case 1:
	{
		if(map_chosen == true)
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80, &pao_pao_selected, false, 0.92f);
		else
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80, &(map_1.GetCurrentFrame()), false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80, &sound_beach, false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80 + 64, &west_sub, false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80 + 64, &howard_arena, false, 0.92f);
	
	}	break;
	
	case 2:
	{
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80, &pao_pao, false, 0.92f);
		if(map_chosen == true)
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80, &sound_beach_selected, false, 0.92f);
		else
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80, &(map_2.GetCurrentFrame()), false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80 + 64, &west_sub, false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80 + 64, &howard_arena, false, 0.92f);
	
	}	break;
	
	case 3:
	{
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80, &pao_pao, false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80, &sound_beach, false, 0.92f);
		if(map_chosen == true)
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80 + 64, &west_sub_selected, false, 0.92f);
		else
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80 + 64, &(map_3.GetCurrentFrame()), false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80 + 64, &howard_arena, false, 0.92f);
	
	}	break;
	
	case 4:
	{
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80, &pao_pao, false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80, &sound_beach, false, 0.92f);
		App->render->Blit(back_graphics, SCREEN_WIDTH / 2 - 96, 80 + 64, &west_sub, false, 0.92f);
		if(map_chosen == true)
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80 + 64, &howard_arena_selected, false, 0.92f);
		else
			App->render->Blit(back_graphics, SCREEN_WIDTH / 2, 80 + 64, &(map_4.GetCurrentFrame()), false, 0.92f);
	
	}	break;
	}
	
	


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		switch (map) 
		{
		case 1:
		{
			map_chosen = true;
			App->audio->playFx(selected);
			App->fade->FadeToBlack(App->scene_map, (Module*)App->scene_paopao);
		}	break;

		case 2:
		{
			map_chosen = true;
			App->audio->playFx(selected);
			App->fade->FadeToBlack(App->scene_map, (Module*)App->scene_paopao);
		}break;

		case 3:
		{
			map_chosen = true;
			App->audio->playFx(selected);
			App->fade->FadeToBlack(App->scene_map, (Module*)App->scene_westsubway);
		}	break;

		case 4:
		{
			map_chosen = true;
			App->audio->playFx(selected);
			App->fade->FadeToBlack(App->scene_map, (Module*)App->scene_howardarena);
		} break;
		}		
	}

	return UPDATE_CONTINUE;
}