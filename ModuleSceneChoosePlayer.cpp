#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleScenePaoPao.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleSceneChoosePlayer.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneChoosePlayer::ModuleSceneChoosePlayer()
{
	background = { 8, 5, 308, 240 };
	grey_joehigashi = { 265, 248, 76, 133 };
	grey_terrybogard = { 356, 253, 69, 128 };
	grey_andybogard = { 439, 258, 50, 123 };
	player_select_tittle = { 598, 147, 120, 17 };

	selected_joehigashi.PushBack({ 504, 248, 76, 133 });
	selected_joehigashi.PushBack({ 26, 385, 76, 133 });
	selected_joehigashi.speed = 0.1f;
	selected_joehigashi.loop = true;

	selected_terrybogard.PushBack({ 595, 253, 69, 128 });
	selected_terrybogard.PushBack({ 117, 390, 69, 128 });
	selected_terrybogard.speed = 0.1f;;
	selected_terrybogard.loop = true;

	selected_andybogard.PushBack({ 678, 258, 50, 123 });
	selected_andybogard.PushBack({ 200, 395, 50, 123 });
	selected_andybogard.speed = 0.1f;;
	selected_andybogard.loop = true;
}

ModuleSceneChoosePlayer::~ModuleSceneChoosePlayer()
{}

// Load assets
bool ModuleSceneChoosePlayer::Start()
{
	LOG("Loading choose player assets");
	bool ret = true;
	graphicschooseplayer = App->textures->Load("SPRITES FATAL FURY/GENERAL MENUS/Neo Geo NGCD - Fatal Fury King of Fighters - Select & Map Screens.png");

	current_animation = &selected_terrybogard;
	player_selected = 1;

	return ret;
}

// Load assets
bool ModuleSceneChoosePlayer::CleanUp()
{
	LOG("Unloading ChoosePlayer");
	App->audio->Disable();
	App->textures->Unload(graphicschooseplayer);

	return true;
}

// Update: draw background
update_status ModuleSceneChoosePlayer::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphicschooseplayer, 0, 0, &background, 0.0f);
	App->render->Blit(graphicschooseplayer, 90, 57, &player_select_tittle, 0.0f);

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN && player_selected != 2) {
		player_selected++;
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN && player_selected != 0) {
		player_selected--;
	}

	switch (player_selected)
	{
		case 0:
		{
			current_animation = &selected_joehigashi;
			App->render->Blit(graphicschooseplayer, 25, 63, &(selected_joehigashi.GetCurrentFrame()), false, 0.0f);
			App->render->Blit(graphicschooseplayer, 115, 83, &grey_terrybogard, 0.0f);
			App->render->Blit(graphicschooseplayer, 205, 87, &grey_andybogard, 0.0f);
		}	break;

		case 1:
		{
			current_animation = &selected_terrybogard;
			App->render->Blit(graphicschooseplayer, 115, 68, &(selected_terrybogard.GetCurrentFrame()), false, 0.0f);
			App->render->Blit(graphicschooseplayer, 25, 78, &grey_joehigashi, 0.0f);
			App->render->Blit(graphicschooseplayer, 205, 87, &grey_andybogard, 0.0f);
		}	break;

		case 2:
		{
			current_animation = &selected_andybogard;
			App->render->Blit(graphicschooseplayer, 205, 71, &(selected_andybogard.GetCurrentFrame()), false, 0.0f);
			App->render->Blit(graphicschooseplayer, 25, 78, &grey_joehigashi, 0.0f);
			App->render->Blit(graphicschooseplayer, 115, 83, &grey_terrybogard, 0.0f);
		}	break;
	}		

	
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_chooseplayer,(Module*) App->scene_map);
	}

	return UPDATE_CONTINUE;
}