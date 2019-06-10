#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFightManager.h"
#include "ModulePlayer.h"
#include "ModuleFightTimer.h"
#include "ModuleInput.h"
#include "ModuleRoundDisplay.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMap.h"
#include "ModuleAudio.h"
#include "ModuleSceneChoosePlayer.h"



ModuleFightManager::ModuleFightManager()
{
	win = { 155,1,123,16 };
	lose = { 155,18,126,16 };
	draw = { 155,35,142,16 };
	round = { 155,52,78,16};
	bonus = { 155, 69, 78 ,16};
	total = { 155, 120, 78, 16};
	life = { 155, 86, 62, 16};
	time = { 155, 103, 62, 16 };
	int a = 155;
	int b = 171;
	for (int u = 0; u < 10; u++)
	{
		score_numbers[u] = { a, b , 14,16 };
		a += 15;
		if (u == 4)
		{
			a = 155;
			b += 17;
		}
	}
	
	for (int i = 0; i < 5 ;i++)
	{
		if (i < 4)
		{
			for (int j = 0; j < 13; j++)
			{
				fightAnimX.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
		else
		{
			for (int j = 0; j < 5; j++)
			{
				fightAnimX.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}		
	}
	fightAnimX.loop = false;

	for (int i = 0; i < 8; i++)
	{
		if (i < 7)
		{
			for (int j = 0; j < 13; j++)
			{
				round1Anim.PushBack({ (304 * j), (224 * i), 304, 224 });
				round2Anim.PushBack({ (304 * j), (224 * i), 304, 224 });
				round3Anim.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
		else
		{
			for (int j = 0; j < 9; j++)
			{
				round1Anim.PushBack({ (304 * j), (224 * i), 304, 224 });
				round2Anim.PushBack({ (304 * j), (224 * i), 304, 224 });
				round3Anim.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
	}
	round1Anim.loop = false;
	round2Anim.loop = false;
	round3Anim.loop = false;

	for (int i = 0; i < 15; i++)
	{
		if (i < 14)
		{
			for (int j = 0; j < 13; j++)
			{
				youWinAnim.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
		else
		{
			for (int j = 0; j < 12; j++)
			{
				youWinAnim.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
	}
	youWinAnim.loop = false;

	for (int i = 0; i < 9; i++)
	{
		if (i < 8)
		{
			for (int j = 0; j < 13; j++)
			{
				youLoseAnim.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
		else
		{
			for (int j = 0; j < 5; j++)
			{
				youLoseAnim.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
	}
	youLoseAnim.loop = false;

	for (int i = 0; i < 14; i++)
	{
		if (i < 13)
		{
			for (int j = 0; j < 13; j++)
			{
				DrawAnim.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
		else
		{
			for (int j = 0; j < 1; j++)
			{
				DrawAnim.PushBack({ (304 * j), (224 * i), 304, 224 });
			}
		}
	}
	DrawAnim.loop = false;

	PixelFadeOut.PushBack({ 0,0,304,224  });
	PixelFadeOut.PushBack({ 304,0,304,224  });
	PixelFadeOut.PushBack({ 608,0,304,224  });
	PixelFadeOut.PushBack({ 0,224,304,224  });
	PixelFadeOut.PushBack({ 304,224,304,224 });
	PixelFadeOut.PushBack({ 608,224,304,224  });
	PixelFadeOut.PushBack({ 0,448,304,224 });
			 
	PixelFadeOut.speed = 0.2f;
	PixelFadeOut.loop = false;

	PixelFadeIn.PushBack({ 0,448,304,224 });
	PixelFadeIn.PushBack({ 608,224,304,224 });
	PixelFadeIn.PushBack({ 304,224,304,224 });
	PixelFadeIn.PushBack({ 0,224,304,224 });
	PixelFadeIn.PushBack({ 608,0,304,224 });
	PixelFadeIn.PushBack({ 304,0,304,224 });
	PixelFadeIn.PushBack({ 0,0,304,224 });	
			 
	PixelFadeIn.speed = 0.2f;
	PixelFadeIn.loop = false;	
}

ModuleFightManager::~ModuleFightManager(){}

bool ModuleFightManager::Start() 
{
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/UI sprites.png");
	graphicsFight = App->textures->Load("SPRITES FATAL FURY/UI/Fight57.png");
	graphicsRound1 = App->textures->Load("SPRITES FATAL FURY/UI/RoundOne87.png");
	graphicsRound2 = App->textures->Load("SPRITES FATAL FURY/UI/RoundTwo85.png");
	graphicsRound3 = App->textures->Load("SPRITES FATAL FURY/UI/RoundThree85.png");
	graphicsYouWin = App->textures->Load("SPRITES FATAL FURY/UI/Youwin194.png");
	graphicsYouLose = App->textures->Load("SPRITES FATAL FURY/UI/Youlose96.png");
	graphicsDrawGame = App->textures->Load("SPRITES FATAL FURY/UI/DrawGame170.png");
	graphicsPixelFade = App->textures->Load("SPRITES FATAL FURY/UI/Introductiontotheround7.png");
	fightFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/FX_FightVoice.wav");
	roundFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/FX_ReadyVoice.wav");

	position.x = 151;
	position.y = 103;

	pl_won_rounds = 0;
	en_won_rounds = 0;
	current_round = 1;
	winner = 3;
	timer_num = 93;
	timer_counter = 0;
	time_stop = false;
	SDL_Rect none = { 0,0,0,0 };
	f = none;
	
	App->player->Enable();
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
	App->enemy->Disable();
	App->fight_timer->Disable();
	App->round_pl->Disable();
	App->round_en->Disable();
	return true;
}

void ModuleFightManager::Reset()
{
	App->player->Reset();
	App->enemy->Reset();
	App->particles->DeleteAll();
	timer_num = 93;
	timer_counter = 0;
	time_stop = false;
	blockpoints = false;
	round_start = true;
	youWinAnim.Reset();
	youLoseAnim.Reset();
	DrawAnim.Reset();
	fightAnimX.Reset();
	PixelFadeOut.Reset();
	ft = 0;
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
	if (round_start)
	{
		ft++;
		App->render->Blit(graphicsPixelFade, 0, -30, &(PixelFadeIn.GetCurrentFrame()), false, 0.0f);
		if (ft == 40)
		{
			round_start = false;
			PixelFadeIn.Reset();
			ft = 0;
		}
	}
	if (time_stop)
	{
		ft++;
		if (App->enemy->Health() == 0)
			App->render->Blit(graphicsYouWin, 0, -30, &(youWinAnim.GetCurrentFrame()), false, 0.0f);
		if (timer_num == 0 && App->player->Health() > App->enemy->Health())
			App->render->Blit(graphicsYouWin, 0, -30, &(youWinAnim.GetCurrentFrame()), false, 0.0f);

		if (App->player->Health() == 0)
			App->render->Blit(graphicsYouLose, 0, -30, &(youLoseAnim.GetCurrentFrame()), false, 0.0f);
		if (timer_num == 0 && App->enemy->Health() > App->player->Health())
			App->render->Blit(graphicsYouLose, 0, -30, &(youLoseAnim.GetCurrentFrame()), false, 0.0f);

		if (timer_num == 0 && App->enemy->Health() == App->player->Health())
			App->render->Blit(graphicsDrawGame, 0, -30, &(DrawAnim.GetCurrentFrame()), false, 0.0f);

		if (ft > 120)
		{
			App->render->Blit(graphicsPixelFade, 0, -30, &(PixelFadeOut.GetCurrentFrame()), false, 0.0f);
			if (pl_won_rounds >= 2 && pl_won_rounds > en_won_rounds)
				winner = 0;
			if (en_won_rounds >= 2 && pl_won_rounds < en_won_rounds)
				winner = 1;

			if (winner == 0)
			{
				if (App->scene_map->map == 1)
					App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_congrats);
				if (App->scene_map->map == 2)
					App->fade->FadeToBlack((Module*)App->scene_soundbeach, (Module*)App->scene_congrats);
				if (App->scene_map->map == 3)
					App->fade->FadeToBlack((Module*)App->scene_westsubway, (Module*)App->scene_congrats);
				if (App->scene_map->map == 4)
					App->fade->FadeToBlack((Module*)App->scene_howardarena, (Module*)App->scene_congrats);
			}

			if (winner == 1)
			{
				if (App->scene_map->map == 1)
					App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_gameover);
				if (App->scene_map->map == 2)
					App->fade->FadeToBlack((Module*)App->scene_soundbeach, (Module*)App->scene_gameover);
				if (App->scene_map->map == 3)
					App->fade->FadeToBlack((Module*)App->scene_westsubway, (Module*)App->scene_gameover);
				if (App->scene_map->map == 4)
					App->fade->FadeToBlack((Module*)App->scene_howardarena, (Module*)App->scene_gameover);
			}
		}
		if (ft == 160 && winner != 0 && winner != 1)
			Reset();
	}


	if (timer_num != 0 && !time_stop)
	{
		timer_counter++;
		if (timer_counter == 60)
		{
			timer_num--;
			timer_counter = 0;
		}
	}
	if (timer_num >91)
	{
		if(current_round == 1)
			App->render->Blit(graphicsRound1, 0, -30, &(round1Anim.GetCurrentFrame()), false, 0.0f);
		if (current_round == 2)
			App->render->Blit(graphicsRound2, 0, -30, &(round2Anim.GetCurrentFrame()), false, 0.0f);
		if (current_round == 3)
			App->render->Blit(graphicsRound3, 0, -30, &(round3Anim.GetCurrentFrame()), false, 0.0f);
	}
	
	if (timer_num == 91)
	{
		App->render->Blit(graphicsFight, 0, -30, &(fightAnimX.GetCurrentFrame()), false, 0.0f);
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
		current_round++;
		time_stop = true;		
		timer_counter = 0;
	}
	else if (App->enemy->Health() == 0 && !blockpoints)
	{
		blockpoints = true;
		pl_won_rounds++;
		current_round++;
		time_stop = true;
		timer_counter = 0;
	}

	if (timer_num == 0 && !blockpoints)
	{
		blockpoints = true;
		if (App->player->Health() > App->enemy->Health())
		{
			pl_won_rounds++;
			current_round++;
			time_stop = true;
			timer_counter = 0;
		}
		if (App->player->Health() < App->enemy->Health())
		{
			en_won_rounds++;
			current_round++;
			time_stop = true;
			timer_counter = 0;
		}
		if (App->player->Health() == App->enemy->Health())
		{
			current_round++;
			time_stop = true;
			timer_counter = 0;
		}		
	}

	App->render->Blit(graphics, position.x - (f.w / 2) , position.y - (f.h / 2) - 48, &f,false, 0.0f);	

	return update_status::UPDATE_CONTINUE;
	
}