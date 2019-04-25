#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard.png");

	// Terry skill
	skillsmall.anim.PushBack({ 611, 274, 18, 42 });
	skillsmall.life = 6000; //el tiempo que va a estar en pantalla (si pones 1000, apenas recorrerá uns metros
	skillsmall.speed.x = 20; //la velocidad
	
	skillmedium.anim.PushBack({ 577, 247, 18, 69 });
	skillmedium.life = 6000;
	skillmedium.speed.x = 20;

	skillbig.anim.PushBack({ 645, 219, 18, 97 });
	skillbig.life = 6000;
	skillbig.speed.x = 20;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here

			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay; //born "guarda" los milisegundos justos cuando se crea la particula.
			p->position.x = x;
			p->position.y = y;
			active[i] = p;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0) //este if hace que mientras si la particula lleva mas tiempo en pantalla que la vida que tiene, deje de updatear y elimine la particula
	{
		if((SDL_GetTicks() - born) > life) 
			ret = false;
	}

	//this code below is only for the special attack. Other particles would not work correctly with this function.

	if (((SDL_GetTicks() - born) % 500) == 0) //este lo he puesto yo, y hace que cada 500 milisegundos avance 20 posiciones. Deberia estar bien pero parece que no.
	{
		position.x += speed.x;
		position.y += speed.y;
	}	

	return ret;
}