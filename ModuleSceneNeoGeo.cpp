#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNeoGeo.h"
#include "ModuleSceneIntro.h"
#include "ModuleScenePaoPao.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleSceneChoosePlayer.h"

ModuleSceneNeoGeo::ModuleSceneNeoGeo()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			backgroundanim.PushBack({ (320 * j), (224 * i), 320, 224 });
			LOG("j++")
		}

		LOG("i++")
	}	

	backgroundanim.speed = 0.10f;
	backgroundanim.loop = false;
}

ModuleSceneNeoGeo::~ModuleSceneNeoGeo()
{}

// Load assets
bool ModuleSceneNeoGeo::Start()
{
	LOG("Loading Neo Geo screen");
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/1.Intro_NEO_GEO/neo_geo_introo.png");
	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/NeoGeo - Intro.ogg");
	App->audio->playMusic(music);
	return ret;
}

// Load assets
bool ModuleSceneNeoGeo::CleanUp()
{
	LOG("Unloading NeoGeo screen");
	App->audio->Disable();
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneNeoGeo::Update()
{
	App->render->Blit(graphics, 0, 0, &(backgroundanim.GetCurrentFrame()), 0.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_neogeo, App->scene_intro);
	}

	if (backgroundanim.Finished() == true)
	{
		App->fade->FadeToBlack(App->scene_neogeo, App->scene_intro);
	}

	return UPDATE_CONTINUE;
}