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
	
}

ModuleSceneChoosePlayer::~ModuleSceneChoosePlayer()
{}

// Load assets
bool ModuleSceneChoosePlayer::Start()
{
	LOG("Loading choose player assets");
	bool ret = true;
	graphicschooseplayer = App->textures->Load("SPRITES FATAL FURY/GENERAL MENUS/Neo Geo NGCD - Fatal Fury King of Fighters - Select & Map Screens.png");
	//music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/Fatal Fury King of Fighters-(Opening Arcade-Console).ogg");
	//App->audio->playMusic(music);
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
	App->render->Blit(graphicschooseplayer, 25, 65, &grey_joehigashi, 0.0f);
	App->render->Blit(graphicschooseplayer, 115, 70, &grey_terrybogard, 0.0f);
	App->render->Blit(graphicschooseplayer, 205, 74, &grey_andybogard, 0.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_chooseplayer, App->scene_paopao);
	}

	return UPDATE_CONTINUE;
}