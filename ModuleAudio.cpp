#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL_Mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_Mixer/libx86/SDL2_Mixer.lib" )

ModuleAudio::ModuleAudio() : Module()
{
	for (int i = 0; i < MAX_CHUNKS; i++) {
		chunks[i] = nullptr;
	}
}

ModuleAudio::~ModuleAudio()
{}

// Called before audio is available
bool ModuleAudio::Init()
{
	LOG("Init SDL Audio event system");
	bool ret = true;
	SDL_Init(0);

	if (Mix_Init(MIX_INIT_OGG) < 0)
	{
		LOG("Mix_Init Error: %s\n", SDL_GetError());
		ret = false;
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1048) < 0)
	{
		LOG("Mix_Init Error: %s\n", SDL_GetError());
		ret = false;
	}

	Mix_VolumeMusic(DEFAULT_VOLUME);
	chunks[0] = LoadChunk("AUDIO FATAL FURY/FX[WAV]/Voice/Special Attacks/FX_BurnKnuckleAttackTerryBogardVoice.wav");

	return ret;
}

update_status ModuleAudio::Update() {
	update_status update = UPDATE_CONTINUE;
	return update;
}

bool ModuleAudio::CleanUp()
{
	bool ret = true;


	Mix_CloseAudio();
	Mix_Quit();

	return ret;
}

void ModuleAudio::StopMusic() {
	while (!Mix_FadeOutMusic(2000) && Mix_PlayingMusic()) {
		SDL_Delay(80);
	}
	Mix_FadeOutMusic(2000);
}

Mix_Chunk * ModuleAudio::LoadChunk(const char* path)
{
	Mix_Chunk* chunk = nullptr;
	chunk = Mix_LoadWAV(path);
	if (chunk == NULL) {
		LOG("Mix_LoadWAV: %s\n", Mix_GetError());

	};
	chunks[chunk_number] = chunk;
	chunk_number++;
	if (chunk_number == MAX_CHUNKS) chunk_number %= MAX_CHUNKS;
	return chunk;
}

bool ModuleAudio::PlayChunk(Mix_Chunk * sound)
{
	Mix_PlayChannel(-1, sound, 0);
	return true;
}

bool ModuleAudio::PlayMusic(const char* path, int loops)
{
	bool ret = true;

	//Mix_VolumeMusic(0);

	music = Mix_LoadMUS(path);

	if (!music) {
		LOG("Mix_LoadMUS: %s\n", Mix_GetError());
		ret = false;
	};

	if (Mix_FadeInMusic(music, loops, 2000) < 0) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());
		ret = false;
	}
	return ret;
}