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

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_chooseplayer,(Module*) App->scene_map);
	}

	return UPDATE_CONTINUE;
}