#include "Globals.h"
#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleSceneHowardArena.h"
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
#include "ModuleJoeHigashiPlayer.h"


ModuleSceneHowardArena::ModuleSceneHowardArena()
{

	//background
	background.PushBack({ 156,118, 619, 236 });
	background.PushBack({ 156,398, 619, 236 });
	background.PushBack({ 156,669, 619, 236 });
	background.PushBack({ 156,940, 619, 236 });
								   
	background.PushBack({ 828, 118, 619, 236 });
	background.PushBack({ 828,398, 619, 236 });
	background.PushBack({ 828, 669, 619, 236 });
	background.PushBack({ 828,940, 619, 236 });
								   
	background.PushBack({ 1500, 118, 619, 236 });
	background.PushBack({ 1500,398, 619, 236 });
	background.PushBack({ 1500, 669, 619, 236 });
	background.PushBack({ 1500,940, 619, 236 });
								   
	background.PushBack({ 1500, 118, 619, 236 });
	background.PushBack({ 1500,398, 619, 236 });
	background.PushBack({ 1500, 669, 619, 236 });
	background.PushBack({ 1500,940, 619, 236 });
	background.speed = 0.05f;
}

ModuleSceneHowardArena::~ModuleSceneHowardArena()
{}

// Load assets
bool ModuleSceneHowardArena::Start()
{
	LOG("Loading Pao Pao scene");
	App->audio->Start();
	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/Fatal Fury King of Fighters - Four Thousand Years of Chinese History (Tung Fu Rue Theme).ogg");
	App->audio->playMusic(music);

	back_graphics = App->textures->Load("SPRITES FATAL FURY/Stages/3 Howard Arena (Tung)/HowardArena.png");

	App->fight_manager->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneHowardArena::CleanUp()
{
	LOG("Unloading Pao Pao scene");
	App->fight_manager->Disable();
	App->audio->Disable();
	App->textures->Unload(back_graphics);
	App->collision->CleanUp();
	App->player->Reset();
	//App->JoeHigashiPlayer->Reset();
	App->render->camera.x = 0;
	App->render->camera.y = -46;


	return true;
}

// Update: draw background
update_status ModuleSceneHowardArena::Update()
{
	int speed = 3;
	if (App->player->position.x >= 30 && App->player->position.x <= 367 && !App->player->lockX && !App->player->punching && !App->player->kicking && !App->player->specialattack_)
	{
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT)
		{
			App->render->camera.x += speed;
			//App->fight_manager->position.x += speed;
			App->round_pl->position.x -= speed / 2;
			App->round_en->position.x -= speed / 2;
			App->plscore->position.x -= speed / 2;
			App->enscore->position.x -= speed / 2;
			App->lifebar->position.x -= speed / 2;
			App->lifebar2->position.x -= speed / 2;
			App->fight_timer->position.x -= speed / 2;
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT)
		{
			App->render->camera.x -= speed;
			//App->fight_manager->position.x -= speed;
			App->round_pl->position.x += speed / 2;
			App->round_en->position.x += speed / 2;
			App->plscore->position.x += speed / 2;
			App->enscore->position.x += speed / 2;
			App->lifebar->position.x += speed / 2;
			App->lifebar2->position.x += speed / 2;
			App->fight_timer->position.x += speed / 2;
		}
	}

	App->render->DrawQuad({ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 0, 0, 80);
	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 0, -15, &(background.GetCurrentFrame()), false, 0.92f);


	return UPDATE_CONTINUE;
}