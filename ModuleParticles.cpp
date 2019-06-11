#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneChoosePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard.png");
	graphics1 = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard2.png");
	graphics2 = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/3-Joe Higashi/Sprites joe higashi.png");

	////Terry skill
	skill.anim.PushBack({ 1022,751,17,41 });
	skill.life = 3000;
	skill.speed.x = 3.0f;


	skill2.anim.PushBack({ 1038,625,17,68 });
	skill2.life = 3000;
	skill2.speed.x = 3.0f;

	skill3.anim.PushBack({ 1054,496,17,96 });
	skill3.life = 3000;
	skill3.speed.x = 3.0f;


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
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
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{

			if (App->scene_chooseplayer->final_player1 == App->scene_chooseplayer->final_player2)
			{
				if (App->player->sp == true)
				{
					if (App->scene_chooseplayer->final_player1 == 2)
						App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				}

				if (App->enemy->sp == true)
				{
					if (App->scene_chooseplayer->final_player2 == 2)
						App->render->Blit(graphics1, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				}
			}

			else
			{
				App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			}

			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle & particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::DeleteAll()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		delete active[i];
		active[i] = nullptr;
	}
}

void ModuleParticles::OnCollision(Collider * c1, Collider * c2, bool colliding)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}

	if (c1->type == COLLIDER_PLAYER_SKILL && c2->type == COLLIDER_ENEMY)
	{
		if (App->player->sp)
		{
			App->enemy->Damage(10, 2);
			App->player->score += 100;
		}
	}

	if (c1->type == COLLIDER_ENEMY_SKILL && c2->type == COLLIDER_PLAYER)
	{

		App->player->Damage(10, 2);
		App->player->score += 100;

	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle & p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
