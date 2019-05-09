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
#include "ModuleSceneWestSubway.h"


ModuleSceneWestSubway::ModuleSceneWestSubway()
{

	//background
	background.PushBack({ 619, 472, 619, 240 });
	background.PushBack({ 619, 720, 619, 240 });
	background.speed = 0.05f;
}

ModuleSceneWestSubway::~ModuleSceneWestSubway(){}

// Load assets
bool ModuleSceneWestSubway::Start()
{
	LOG("Loading West Subway scene");
	App->audio->Start();
	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/Fatal Fury King of Fighters - The Wild Boy From Downtown (Duck King Theme).ogg");
	App->audio->playMusic(music);

	back_graphics = App->textures->Load("SPRITES FATAL FURY/Stages/4 The West Subway (Duck)/West Subway.png");

	App->fight_manager->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneWestSubway::CleanUp()
{
	LOG("Unloading West Subway scene");
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
update_status ModuleSceneWestSubway::Update()
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
	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 0, -19, &(background.GetCurrentFrame()), false, 0.92f);


	return UPDATE_CONTINUE;
}