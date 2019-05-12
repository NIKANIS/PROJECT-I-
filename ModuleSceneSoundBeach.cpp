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
#include "ModuleSceneSoundBeach.h"


ModuleSceneSoundBeach::ModuleSceneSoundBeach()
{

	//background
	background.PushBack({ 275, 63, 619, 224 });
	background.PushBack({ 940, 63, 619, 224 });
	background.PushBack({ 275, 328, 619, 224 }); 
	background.PushBack({ 940, 328, 619, 224 }); 
	background.PushBack({ 275, 593, 619, 224 });
	background.PushBack({ 940, 593, 619, 224 });
	background.PushBack({ 275, 858, 619, 224 });
	background.PushBack({ 940, 858, 619, 224 });
	background.speed = 0.07f;

	landscape = { 592, 1246, 461, 104 };
}

ModuleSceneSoundBeach::~ModuleSceneSoundBeach() {}

// Load assets
bool ModuleSceneSoundBeach::Start()
{
	LOG("Loading Sound Beach scene");
	App->audio->Start();
	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/Fatal Fury King of Fighters - The Sea Knows (Michael Max Theme).ogg");
	App->audio->playMusic(music);

	back_graphics = App->textures->Load("SPRITES FATAL FURY/Stages/2 Sound Beach (Michael)/Day/soundbeachfinal.png");

	App->fight_manager->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneSoundBeach::CleanUp()
{
	LOG("Unloading Sound Beach scene");
	App->fight_manager->Disable();
	App->audio->Disable();
	App->textures->Unload(back_graphics);
	App->collision->CleanUp();
	App->player->Reset();
	App->render->camera.x = 0;
	App->render->camera.y = -46;


	return true;
}

// Update: draw background
update_status ModuleSceneSoundBeach::Update()
{
	//int speed = 3;
	//if (App->player->position.x >= 30 && App->player->position.x <= 367 && !App->player->lockX && !App->player->punching && !App->player->kicking && !App->player->specialattack_)
	//{
	//	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT)
	//	{
	//		App->render->camera.x += speed;
	//		//App->fight_manager->position.x += speed;
	//		App->round_pl->position.x -= speed / 2;
	//		App->round_en->position.x -= speed / 2;
	//		App->plscore->position.x -= speed / 2;
	//		App->enscore->position.x -= speed / 2;
	//		App->lifebar->position.x -= speed / 2;
	//		App->lifebar2->position.x -= speed / 2;
	//		App->fight_timer->position.x -= speed / 2;
	//	}
	//	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT)
	//	{
	//		App->render->camera.x -= speed;
	//		//App->fight_manager->position.x -= speed;
	//		App->round_pl->position.x += speed / 2;
	//		App->round_en->position.x += speed / 2;
	//		App->plscore->position.x += speed / 2;
	//		App->enscore->position.x += speed / 2;
	//		App->lifebar->position.x += speed / 2;
	//		App->lifebar2->position.x += speed / 2;
	//		App->fight_timer->position.x += speed / 2;
	//	}
	//}
	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 100, 0, &landscape, 0.90f);
	App->render->Blit(back_graphics, 0, 0, &(background.GetCurrentFrame()), false, 0.90f);
	


	return UPDATE_CONTINUE;
}