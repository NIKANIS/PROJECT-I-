

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
	
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/spritesSpecialAttacks.png");

	//Joe skill
	skillJoe.anim.PushBack({ 43, 31, 43, 113 }); 
	skillJoe.anim.PushBack({ 99, 31, 43, 113 }); 
	skillJoe.anim.speed = 0.04f;
	skillJoe.anim.loop = false;
	skillJoe.life = 200;


	skillJoe2.anim.PushBack({ 162, 31, 50, 113 });
	skillJoe2.anim.PushBack({ 228, 31, 50, 113 });
	skillJoe2.anim.speed = 0.04f;
	skillJoe2.life = 3000;


	skillJoe3.anim.PushBack({ 295, 31, 44, 113 }); //5ta
	skillJoe3.anim.PushBack({ 383, 31, 44, 113 }); //6ta
	skillJoe3.anim.speed = 0.04f;
	skillJoe3.anim.loop = false;

	

	////Terry skill
	skill.anim.PushBack({ 61,187,17,96 });
	skill.life = 3000;

	
	skill2.anim.PushBack({ 80,289,17,96 });
	skill2.life = 3000;

	
	skill3.anim.PushBack({ 93,187,17,96});
	skill3.life = 3000;


	//Andy skill
	skillAndy.anim.PushBack({ 42, 750, 23, 97 }); //1ra
	skillAndy.anim.PushBack({ 78, 750, 40, 97 }); //2nda
	skillAndy.anim.PushBack({ 118, 750, 57, 97 }); //3ra
	skillAndy.anim.speed = 0.1f;
	skillAndy.anim.loop = false;
	skillAndy.life = 400;

	skillAndy2.anim.PushBack({ 176, 750, 62, 97 }); //4ta
	skillAndy2.anim.PushBack({ 248, 750, 47, 97 }); //5ta
	skillAndy2.anim.speed = 0.1f;
	skillAndy2.life = 3000;

	skillAndy3.anim.PushBack({ 444, 750, 61, 97 }); //6ta
	skillAndy3.life = 3000;

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

			App->render->Blit(graphics, active[i]->position.x, active[i]->position.y, &active[i]->anim.GetCurrentFrame(), active[i]->fliped);

			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, bool fliped, bool augmented, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			if (augmented && App->scene_chooseplayer->final_player1 == 2 || App->scene_chooseplayer->final_player2 == 2)
				p->hits = 5;
/*			else
				p->hits = 1;*/
			p->position.x = x;
			p->position.y = y;
			p->fliped = fliped;
			if (!fliped)
				p->speed.x = 3.0f;
			else
				p->speed.x = -3.0f;
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

void ModuleParticles::OnCollision(Collider* c1, Collider* c2, bool colliding)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			active[i]->hits--;
			if (active[i]->hits < 0)
				active[i]->hits = 0;
			if (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_ENEMY)
				active[i]->hits = 0;
			if (active[i]->hits == 0)
			{
				active[i]->collider->to_delete = true;
				delete active[i];
			}
			active[i] = nullptr;

			break;
		}
	}

	if (c1->type == COLLIDER_PLAYER_SKILL && c2->type == COLLIDER_ENEMY )
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
		App->enemy->score += 100;
		
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
