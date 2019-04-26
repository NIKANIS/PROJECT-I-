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
	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		LOG("SDL_Init: %s\n", SDL_GetError());
		ret = false;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		LOG("Mix_OpenAudio: %s\n", Mix_GetError());
		ret = false;
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

Mix_Chunk* const ModuleAudio::loadWAV(const char* path)
{
	return Mix_LoadWAV(path);
}

Mix_Music* const ModuleAudio::loadMusic(const char* path)
{
	return  Mix_LoadMUS(path);
}

bool ModuleAudio::playMusic(Mix_Music *music)
{ 
	bool ret = true; 
	Mix_PlayMusic(music, -1); 
	return ret;
}

bool ModuleAudio::playFx(Mix_Chunk *chunk)
{
	bool ret = true;
	Mix_PlayChannel(-1, chunk, 0); 
	return ret;
}