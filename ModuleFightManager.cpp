#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFightManager.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleFightTimer.h"
#include "ModuleInput.h"
#include "ModuleRoundDisplay.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMap.h"
#include "ModuleJoeHigashiPlayer.h"
#include "ModuleAudio.h"


ModuleFightManager::ModuleFightManager()
{
	win = { 155,1,123,16 };
	lose = { 155,18,126,16 };
	draw = { 155,35,142,16 };
	round = {155,52,78,16};
	fight = {99,205,173,40};

}

ModuleFightManager::~ModuleFightManager(){}

bool ModuleFightManager::Start() 
{
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/UI sprites.png");
	fightFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/FX_FightVoice.wav");
	roundFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/FX_ReadyVoice.wav");

	position.x = 151;
	position.y = 103;

	pl_won_rounds = 0;
	en_won_rounds = 0;
	winner = 3;
	timer_num = 93;
	timer_counter = 0;
	time_stop = false;
	SDL_Rect none = { 0,0,0,0 };
	f = none;

	App->player->Enable();
	//App->JoeHigashiPlayer->Enable();
	App->enemy->Enable();
	App->fight_timer->Enable();
	App->round_pl->Enable();
	App->round_en->Enable();
	return true;
}

bool ModuleFightManager::CleanUp()
{
	App->textures->Unload(graphics);
	App->player->Disable();
	//App->JoeHigashiPlayer->Disable();
	App->enemy->Disable();
	App->fight_timer->Disable();
	App->round_pl->Disable();
	App->round_en->Disable();
	return true;
}

void ModuleFightManager::Reset()
{
	App->player->Reset();
	//App->JoeHigashiPlayer->Reset();
	App->enemy->Reset();
	timer_num = 93;
	timer_counter = 0;
	time_stop = false;
	blockpoints = false;
	SDL_Rect none = { 0,0,0,0 };
	f = none;
}

update_status ModuleFightManager::Update()
{
	App->render->camera.x = -SCREEN_SIZE * ((App->player->Pos_X() + App->enemy->Pos_X() + 60) / 2 - SCREEN_WIDTH / 2);
	if (App->render->camera.x >= 0)
		App->render->camera.x = 0;
	if (App->render->camera.x <= -(640 - SCREEN_WIDTH)*SCREEN_SIZE)
		App->render->camera.x = -(640 - SCREEN_WIDTH)*SCREEN_SIZE;
	if (timer_num != 0 && !time_stop)
	{
		timer_counter++;
		if (timer_counter == 60)
		{
			timer_num--;
			timer_counter = 0;
		}
	}
	if (timer_num == 93)
	{
		f = round;
		//App->audio->playFx(roundFX);
	}

	if (timer_num == 92)
	{
		f = fight;
		//App->audio->playFx(fightFX);
	}

	if (timer_num == 90)
	{
		SDL_Rect none = { 0,0,0,0 };
		f = none;
	}


	if (App->player->Health() == 0 && !blockpoints)
	{
		blockpoints = true;
		en_won_rounds++;
		time_stop = true;
		f = lose;
		timer_counter = 0;
	}
	else if (App->enemy->Health() == 0 && !blockpoints)
	{
		blockpoints = true;
		pl_won_rounds++;
		time_stop = true;
		f = win;
		timer_counter = 0;
	}

	if (App->player->Health() == 0 && App->enemy->Health() == 0 && !blockpoints)
	{
		blockpoints = true;
		time_stop = true;
		f = draw;
		timer_counter = 0;
	}

	if (timer_num == 0 && !blockpoints)
	{
		blockpoints = true;
		if (App->player->Health() > App->enemy->Health())
		{
			pl_won_rounds++;
			f = win;
			timer_counter = 0;
		}
		if (App->player->Health() < App->enemy->Health())
		{
			en_won_rounds++;
			f = lose;
			timer_counter = 0;
		}
		if (App->player->Health() == App->enemy->Health())
		{
			f = draw;
			timer_counter = 0;
		}
	}

	if (blockpoints)
	{
		timer_counter++;
		if (timer_counter >= 90/* && winner != 0 && winner != 1*/)
		{
			Reset();
			if (winner == 0)
				App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_congrats);

			if (winner == 1)
				App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_gameover);
		}
	}
		if (pl_won_rounds >= 2 && pl_won_rounds > en_won_rounds)
			winner = 0;
		if (en_won_rounds >= 2 && pl_won_rounds < en_won_rounds)
			winner = 1;

		if (winner == 0)
		{
			if(App->scene_map->map == 1)
				App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_congrats);
			//if (App->scene_map->map == 2)
			//	App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_congrats);
			if (App->scene_map->map == 3)
				App->fade->FadeToBlack((Module*)App->scene_westsubway, (Module*)App->scene_congrats);
			//if (App->scene_map->map == 4)
			//	App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_congrats);
		}	
			

		if (winner == 1)
		{
			if (App->scene_map->map == 1)
				App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_gameover);
			//if (App->scene_map->map == 2)
			//	App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_gameover);
			if (App->scene_map->map == 3)
				App->fade->FadeToBlack((Module*)App->scene_westsubway, (Module*)App->scene_gameover);
			//if (App->scene_map->map == 4)
			//	App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_gameover);
		}
			

		App->render->Blit(graphics, position.x - (f.w / 2) , position.y - (f.h / 2) - 48, &f,false, 0.0f);

		return update_status::UPDATE_CONTINUE;
	
}