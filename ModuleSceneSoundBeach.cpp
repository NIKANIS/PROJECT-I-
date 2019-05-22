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

	landscape = { 592, 1246, 665, 104 };

	shadowp1 = { 333,1163,64,12 };
	shadowp2 = { 333,1163,64,12 };
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

	// Draw everything --------------------------------------
	App->render->DrawQuad({ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 0, 0, 80);
	App->render->Blit(back_graphics, 0, -10, &landscape, true, 0.75f);
	App->render->Blit(back_graphics, 0, 0, &(background.GetCurrentFrame()), false, 0.9f);
	App->render->Blit(back_graphics, App->player->Pos_X() - 5, 210, &shadowp1, 0.0f);
	App->render->Blit(back_graphics, App->enemy->Pos_X() - 2, 210, &shadowp2, 0.0f);


	return UPDATE_CONTINUE;
}