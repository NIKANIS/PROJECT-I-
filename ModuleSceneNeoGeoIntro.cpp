#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNeoGeoIntro.h"
#include "ModuleSceneIntro.h"
#include "ModuleScenePaoPao.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleSceneChoosePlayer.h"

ModuleSceneNeoGeoIntro::ModuleSceneNeoGeoIntro()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			backgroundanim.PushBack({ (320 * j), (224 * i), 320, 224 });
		}
	}

	backgroundanim.speed = 0.20f;
	backgroundanim.loop = false;
}

ModuleSceneNeoGeoIntro::~ModuleSceneNeoGeoIntro()
{}

// Load assets
bool ModuleSceneNeoGeoIntro::Start()
{
	LOG("Loading Neo Geo screen");
	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/1.Intro_NEO_GEO/neo_geo_introo.png");
	music = App->audio->loadMusic("AUDIO FATAL FURY/MUSIC[OGG]/NeoGeo - Intro.ogg");
	App->audio->playMusic(music);
	return ret;
}

// Load assets
bool ModuleSceneNeoGeoIntro::CleanUp()
{
	LOG("Unloading NeoGeo screen");
	App->audio->Disable();
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneNeoGeoIntro::Update()
{
	App->render->Blit(graphics, 0, 0, &(backgroundanim.GetCurrentFrame()), 0.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN )
	{
		App->fade->FadeToBlack(App->scene_neogeo, App->scene_intro);
	}

	if (backgroundanim.Finished() == true)
	{
		App->fade->FadeToBlack(App->scene_neogeo, App->scene_intro);
	}

	return UPDATE_CONTINUE;
}