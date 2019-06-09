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
#include "ModuleJoeHigashiPlayer.h"



ModuleScenePaoPao::ModuleScenePaoPao()
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 512;
	ground.h = 224;

	//background
	background.PushBack({ 49, 134, 619, 234 });
	background.PushBack({ 772, 134, 619, 234 });
	background.speed = 0.05f;

	shadowp1 = shadowp2 = { 290,70,64,12 };
}

ModuleScenePaoPao::~ModuleScenePaoPao()
{}

// Load assets
bool ModuleScenePaoPao::Start()
{
	LOG("Loading Pao Pao scene");
	App->audio->Start();
	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/Fatal Fury King of Fighters - Halema School of Capoeira Fight Song (Richard Meyer Theme).ogg");
	App->audio->playMusic(music);

	back_graphics = App->textures->Load("SPRITES FATAL FURY/Stages/1 Pao Pao Cafe(Richard)/sprites paopao.png");

	App->fight_manager->Enable();

	return true;
}

// UnLoad assets
bool ModuleScenePaoPao::CleanUp()
{
	LOG("Unloading Pao Pao scene");
	App->fight_manager->Disable();
	App->audio->Disable();
	App->textures->Unload(back_graphics);
	App->collision->CleanUp();
	App->player->Reset();
	App->render->camera.x = 0;
	App->render->camera.y = -46;


	return true;
}

update_status ModuleScenePaoPao::Update()
{
	App->render->DrawQuad({ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 0, 0, 80);
	// Draw everything --------------------------------------
	App->render->Blit(back_graphics, 0, 0, &(background.GetCurrentFrame()), false, 0.92f);
	App->render->Blit(back_graphics, App->player->Pos_X() - 5, 210, &shadowp1, 0.0f);
	App->render->Blit(back_graphics, App->enemy->Pos_X() - 2, 210, &shadowp2, 0.0f);


	return UPDATE_CONTINUE;
}