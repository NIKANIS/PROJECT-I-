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
#include "SDL/include/SDL_timer.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneChoosePlayer::ModuleSceneChoosePlayer()
{
	background = { 8, 5, 308, 240 };

	grey_joehigashi = { 265, 248, 76, 133 };
	grey_terrybogard = { 356, 253, 69, 128 };
	grey_andybogard = { 439, 258, 50, 123 };

	purple_joehigashi = { 504, 384, 76, 133 };
	purple_terrybogard = { 595, 389, 70, 128 };
	purple_andybogard = { 678, 394, 50, 123 };

	player_select_tittle = { 598, 147, 120, 17 };
	p1 = {603, 187, 48, 15};
	p2 = {662, 187,48,15};

	selected_joehigashi.PushBack({ 504, 248, 76, 133 });
	selected_joehigashi.PushBack({ 26, 385, 76, 133 });
	selected_joehigashi.speed = 0.2f;
	selected_joehigashi.loop = true;

	selected_terrybogard.PushBack({ 595, 253, 69, 128 });
	selected_terrybogard.PushBack({ 117, 390, 69, 128 });
	selected_terrybogard.speed = 0.2f;;
	selected_terrybogard.loop = true;

	selected_andybogard.PushBack({ 678, 258, 50, 123 });
	selected_andybogard.PushBack({ 200, 395, 50, 123 });
	selected_andybogard.speed = 0.2f;;
	selected_andybogard.loop = true;

	timer = { 39, 715, 88, 16 };
}

ModuleSceneChoosePlayer::~ModuleSceneChoosePlayer()
{}

// Load assets
bool ModuleSceneChoosePlayer::Start()
{
	LOG("Loading choose player assets");
	bool ret = true;
	graphicschooseplayer = App->textures->Load("SPRITES FATAL FURY/GENERAL MENUS/Neo Geo NGCD - Fatal Fury King of Fighters - Select & Map Screens.png");
	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/Fatal Fury King of Fighters-Character Selection.ogg");
	select = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/FX/FX_SelectHover.wav");
	selected = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/FX/FX_ChooseSelection.wav");

	current_animation = &selected_terrybogard;
	player_selected = 2;

	App->audio->playMusic(music);

	return ret;
}

// Load assets
bool ModuleSceneChoosePlayer::CleanUp()
{
	LOG("Unloading ChoosePlayer");
	App->audio->Disable();
	App->textures->Unload(graphicschooseplayer);

	player_selected = 2;
	numberofplayers = 0;

	return true;
}

void ModuleSceneChoosePlayer::ResetTimer()
{
	frames_timer = 0;
	timer = { 39, 715, 88, 16 };
}

void ModuleSceneChoosePlayer::SelectPlayer()
{
	switch (numberofplayers)
	{
	case 0:
	{
		if (player_selected == 1)
		{
			joehigashi_chosen = true;
			App->render->Blit(graphicschooseplayer, 25, 83 + 3, &purple_joehigashi, 0.0f);
			numberofplayers++;
			App->render->Blit(graphicschooseplayer, 50, 80 + 3, &p1, 0.0f);
			final_player1 = 1;
			
		}

		if (player_selected == 2)
		{
			terrybogard_chosen = true;
			App->render->Blit(graphicschooseplayer, 115, 88 + 3, &purple_terrybogard, 0.0f);
			numberofplayers++;
			App->render->Blit(graphicschooseplayer, 125, 80 + 3, &p1, 0.0f);
			final_player1 = 2;
			
		}

		if (player_selected == 3)
		{
			andybogard_chosen = true;
			App->render->Blit(graphicschooseplayer, 205, 92 + 3, &purple_andybogard, 0.0f);
			numberofplayers++;
			App->render->Blit(graphicschooseplayer, 195, 80 + 3, &p1, 0.0f);
			final_player1 = 3;
			
		}

	}	break;

	case 1:
	{
		if (player_selected == 1)
		{
			joehigashi_chosen = true;
			App->render->Blit(graphicschooseplayer, 25, 83 + 3, &purple_joehigashi, 0.0f);
			numberofplayers++;
			App->render->Blit(graphicschooseplayer, 50, 80 + 3, &p2, 0.0f);
			final_player2 = 1;
			
		}

		if (player_selected == 2)
		{
			terrybogard_chosen = true;
			App->render->Blit(graphicschooseplayer, 115, 88 + 3, &purple_terrybogard, 0.0f);
			numberofplayers++;
			App->render->Blit(graphicschooseplayer, 125, 80 + 3, &p2, 0.0f);
			final_player2 = 2;
			
		}

		if (player_selected == 3)
		{
			andybogard_chosen = true;
			App->render->Blit(graphicschooseplayer, 205, 92 + 3, &purple_andybogard, 0.0f);
			numberofplayers++;
			App->render->Blit(graphicschooseplayer, 195, 80 + 3, &p2, 0.0f);
			final_player2 = 3;
			
		}

	}	break;
	}
}

void ModuleSceneChoosePlayer::Timer()
{
	frames_timer++;
	
	if (frames_timer >= 0 && frames_timer < 120)
	{
		App->render->Blit(graphicschooseplayer, 102, 71 - 4, &timer, 0.0f);
	}
	else if (frames_timer >= 120 && frames_timer < 180)
	{
		timer = { 39, 755, 88, 16 };
		App->render->Blit(graphicschooseplayer, 102, 71 - 4, &timer, 0.0f);
	}
	else if (frames_timer >= 180 && frames_timer < 240)
	{
		timer = { 39, 795, 88, 16 };
		App->render->Blit(graphicschooseplayer, 102, 71 - 4, &timer, 0.0f);
	}
	else if (frames_timer >= 240 && frames_timer < 300)
	{
		timer = { 142, 715, 88, 16 };
		App->render->Blit(graphicschooseplayer, 102, 71 - 4, &timer, 0.0f);
	}
	else if (frames_timer >= 300 && frames_timer < 360)
	{
		timer = { 142, 755, 88, 16 };
		App->render->Blit(graphicschooseplayer, 102, 71 - 4, &timer, 0.0f);
	}
	else if (frames_timer >= 360/* && frames_timer < 420*/)
	{
		timer = { 142, 786, 88, 16 };
		App->render->Blit(graphicschooseplayer, 102, 71 - 4, &timer, 0.0f);
	}
	
	if (frames_timer == 380)
	{
		SelectPlayer();
	}	
}

// Update: draw background
update_status ModuleSceneChoosePlayer::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphicschooseplayer, 0, -4, &background, 0.0f);
	App->render->Blit(graphicschooseplayer, SCREEN_WIDTH/2 - player_select_tittle.w/2, 55 - 4, &player_select_tittle, 0.0f);

	if (joehigashi_chosen == true)
	{
		App->audio->playFx(selected);
		SDL_Delay(1000);
		ResetTimer();
		joehigashi_chosen = false;
	}

	if (terrybogard_chosen == true)
	{
		App->audio->playFx(selected);
		SDL_Delay(1000);
		ResetTimer();
		terrybogard_chosen = false;
	}

	if (andybogard_chosen == true)
	{
		App->audio->playFx(selected);
		SDL_Delay(1000);
		ResetTimer();
		andybogard_chosen = false;
	}


	if (numberofplayers == 0)
	{
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN && player_selected != 3) {
			player_selected++;
			App->audio->playFx(select);
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN && player_selected != 1) {
			player_selected--;
			App->audio->playFx(select);
		}
	}

	if (numberofplayers == 1)
	{
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN && player_selected != 3) {
			player_selected++;
			App->audio->playFx(select);
		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN && player_selected != 1) {
			player_selected--;
			App->audio->playFx(select);
		}
	}	

	switch (player_selected)
	{
		case 1:
		{
			if (joehigashi_chosen != true)
			{
				current_animation = &selected_joehigashi;
				App->render->Blit(graphicschooseplayer, 25, 37 + 3, &(selected_joehigashi.GetCurrentFrame()), false, 0.0f);
			}

			App->render->Blit(graphicschooseplayer, 115, 88 + 3, &grey_terrybogard, 0.0f);
			App->render->Blit(graphicschooseplayer, 205, 92 + 3, &grey_andybogard, 0.0f);

			if (numberofplayers == 0)
			{
				App->render->Blit(graphicschooseplayer, 50, 80 + 3, &p1, 0.0f);
			}
			else if (numberofplayers == 1)
			{
				App->render->Blit(graphicschooseplayer, 50, 80 + 3, &p2, 0.0f);
			}
			
		}	break;

		case 2:
		{
			if (terrybogard_chosen != true)
			{
				current_animation = &selected_terrybogard;
				App->render->Blit(graphicschooseplayer, 115, 42 + 3, &(selected_terrybogard.GetCurrentFrame()), false, 0.0f);
			}			
			
			App->render->Blit(graphicschooseplayer, 25, 83 + 3, &grey_joehigashi, 0.0f);
			App->render->Blit(graphicschooseplayer, 205, 92 + 3, &grey_andybogard, 0.0f);

			if (numberofplayers == 0)
			{
				App->render->Blit(graphicschooseplayer, 125, 80 + 3, &p1, 0.0f);
			}
			else if (numberofplayers == 1)
			{
				App->render->Blit(graphicschooseplayer, 125, 80 + 3, &p2, 0.0f);
			}
			
		}	break;

		case 3:
		{
			if (andybogard_chosen != true)
			{
				current_animation = &selected_andybogard;
				App->render->Blit(graphicschooseplayer, 205, 46 + 3, &(selected_andybogard.GetCurrentFrame()), false, 0.0f);
			}			
			
			App->render->Blit(graphicschooseplayer, 25, 83 + 3, &grey_joehigashi, 0.0f);
			App->render->Blit(graphicschooseplayer, 115, 88 + 3, &grey_terrybogard, 0.0f);

			if (numberofplayers == 0)
			{
				App->render->Blit(graphicschooseplayer, 195, 80 + 3, &p1, 0.0f);
			}
			else if (numberofplayers == 1)
			{
				App->render->Blit(graphicschooseplayer, 195, 80 + 3, &p2, 0.0f);
			}
			
		}	break;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		SelectPlayer();
	}	

	Timer();
		
	if (numberofplayers == 2)
	{
		App->fade->FadeToBlack(App->scene_chooseplayer,(Module*) App->scene_map, 0.5f);
	}

	return UPDATE_CONTINUE;
}