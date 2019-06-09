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
	shadowp1 = { 600,406,64,12 };
	shadowp2 = { 600,406,64,12 };
}

ModuleSceneWestSubway::~ModuleSceneWestSubway() {}

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
	App->enemy->Reset();
	App->render->camera.x = 0;
	App->render->camera.y = -46;


	return true;
}

// Update: draw background
update_status ModuleSceneWestSubway::Update()
{
	// Draw everything --------------------------------------
	App->render->DrawQuad({ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 0, 0, 80);
	App->render->Blit(back_graphics, 0, -19, &(background.GetCurrentFrame()), false, 0.92f);
	App->render->Blit(back_graphics, App->player->Pos_X() - 5, 210, &shadowp1, 0.0f);
	App->render->Blit(back_graphics, App->enemy->Pos_X() - 2, 210, &shadowp2, 0.0f);

	return UPDATE_CONTINUE;
}