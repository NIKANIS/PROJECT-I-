#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleSlowdown.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

ModuleSlowdown::ModuleSlowdown()
{
}

ModuleSlowdown::~ModuleSlowdown()
{}

// Load assets
bool ModuleSlowdown::Start()
{
	return true;
}

// Update: draw background
update_status ModuleSlowdown::PostUpdate()
{
	if (slowing_down)
	{
		UpdateSlowdown();
	}

	return UPDATE_CONTINUE;
}
void ModuleSlowdown::StartSlowdown(int duration, int magnitude)
{
	slowing_down = true;

	slowdown_duration = duration;
	slowdown_magnitude = magnitude;
	slowdown_timer = 0.0f;
}

void ModuleSlowdown::UpdateSlowdown()
{
	if (slowdown_timer < slowdown_duration)
	{
		slowdown_timer++;
		SDL_Delay(slowdown_magnitude);
	}

	if (slowdown_timer == slowdown_duration)
	{
		slowing_down = false;

	}
}
