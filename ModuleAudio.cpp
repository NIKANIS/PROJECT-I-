#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module()
{
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	int Audioflags = MIX_INIT_OGG | MIX_INIT_MOD;
	int initted2 = Mix_Init(Audioflags);
	if (initted2&Audioflags != Audioflags) {
		LOG("Mix_Init: Failed to init required ogg and mod support!\n");
		LOG("Mix_Init: %s\n", Mix_GetError());
		ret = false;
		// handle error
	}

	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		LOG("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	// open 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		LOG("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}

	return ret;
}

// Called every draw update
update_status ModuleAudio::Update()
{

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Quitting SDL mixer");
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	Mix_CloseAudio();
	Mix_Quit();
	return true;
}