#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"
#include "ModuleRoundDisplay.h"
#include "ModuleFightTimer.h"
#include "SDL/include/SDL.h"
#include <cstdlib>
#include <time.h>

ModuleRender::ModuleRender() : Module()
{
	camera.x = 0;
	camera.y = -46;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	camera_offset.x = camera_offset.y = 0;

	srand(time(NULL));
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	SDL_RenderSetLogicalSize(renderer, 303, 207); // Comenta este codigo y pon en el archivo globals.h SCREEN SIZE 3 y WIN_FULLSCREEN_DESKTOP 0  para ver el juego en ventana

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{ 
	SDL_RenderClear(renderer);

	if (shaking)
		UpdateCameraShake();
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section,bool flip, float speed)
{
	bool ret = true;
	SDL_Rect rect;

	rect.x = (int)((camera.x + camera_offset.x) * speed) + x * SCREEN_SIZE;
	rect.y = (int)((camera.y + camera_offset.y) * speed) + y * SCREEN_SIZE + 28;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	if (!flip) {
		rect.w *= SCREEN_SIZE;
		rect.h *= SCREEN_SIZE;
	}
	else {
		rect.w *= -SCREEN_SIZE;
		rect.h *= SCREEN_SIZE;
	}


	SDL_Point p = { App->enemy->position.x / 2,  App->enemy->position.y / 2 };
	SDL_Point* pivot = &p;

	if (flip == false)
	{
		if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	if (flip == true)
	{
		if (SDL_RenderCopyEx(renderer, texture, section, &rect, NULL, NULL, SDL_FLIP_NONE) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (App->player->godMode_)
	{
		rec.x = (int)((camera.x + camera_offset.x) + rect.x * SCREEN_SIZE);
		rec.y = (int)((camera.y + camera_offset.y) + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}


void ModuleRender::StartCameraShake(int duration, float magnitude)
{
	shaking = true;
	shake_duration = duration;
	shake_magnitude = magnitude;
	shake_timer = 0.0f;
}

void ModuleRender::UpdateCameraShake()
{
	if (shake_timer < shake_duration)
	{
		shake_timer++;
		camera_offset.x = ((rand() % 2) - 1) * shake_magnitude;
		camera_offset.y = ((rand() % 2) - 1) * shake_magnitude;
	}

	if (shake_timer == shake_duration)
	{
		shaking = false;
		camera_offset.x = 0;
		camera_offset.y = 0;
	}
}