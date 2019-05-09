#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFightManager.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"
#include "ModuleRoundDisplay.h"
#include "ModuleFightTimer.h"
#include "ModuleJoeHigashiPlayer.h"

#include "SDL/include/SDL_timer.h"



void ModuleJoeHigashiPlayer::Jump() {
	if (jumping) {
		t++;
		position.y = 220 - 7 * t + 0.12 * (t * t);
		vy = -7 + 0.24 * t;
		if (position.y >= 220) {
			jumping = false;
			position.y = 220;
		}
		if (vy > 0) {
			if (current_animation != &jumpidown)
			{
				jumpidown.Reset();
				current_animation = &jumpidown;
			}
		}
	}
}

int ModuleJoeHigashiPlayer::Health()
{
	return health;
}

int ModuleJoeHigashiPlayer::Score()
{
	return score;
}

ModuleJoeHigashiPlayer::ModuleJoeHigashiPlayer()
{
	health = 100;
	already_hit = false;
	body_collide = false;

	// idle animation done 
	idle.PushBack({ 195, 20, 62, 104 });
	idle.PushBack({ 274, 18, 61, 106 });
	idle.PushBack({ 354, 16, 63, 108 });
	idle.PushBack({ 434, 18, 61, 106 });
	idle.PushBack({ 518, 20, 62, 104 });
	idle.loop = true;
	idle.speed = 0.14f;

	// jump idle up done
	jumpiup.PushBack({ 88, 367, 39, 126 });

	// jump idle down 
	jumpidown.PushBack({ 145, 367, 49, 81 });

	//jump while moving done
	jump.PushBack({ 204, 367, 56, 121 });
	
	//go forward done	
	forward.PushBack({ 597, 19, 75, 105 });
	forward.PushBack({ 686, 11, 65, 113 });
	forward.PushBack({ 758, 5, 62, 119 });
	forward.PushBack({ 825, 16, 63, 108 });
	forward.speed = 0.13f;
	forward.loop = true;

	//go backwards done
	backward.PushBack({ 33, 144, 60, 102 });
	backward.PushBack({ 111, 141, 55, 105 });
	backward.PushBack({ 176, 136, 55, 110 });
	backward.PushBack({ 241, 140, 56, 106 });
	backward.speed = 0.13f;
	backward.loop = true;

	// crowch done
	crowch.PushBack({ 761, 888, 59, 69 });

	// crowch while going backwards and viceversa
	crowchprotecc.PushBack({ 830,881,51,74 });

	//punch while standing done	
	punchstanding.PushBack({ 481, 610, 64, 102 });
	punchstanding.PushBack({ 553, 616, 63, 96 });
	punchstanding.PushBack({ 627, 616, 97, 96 });
	punchstanding.PushBack({ 553, 616, 63, 96 });
	punchstanding.PushBack({ 481, 610, 64, 102 });	
	punchstanding.speed = 0.15f;
	punchstanding.loop = false;

	//punch while crowching 
	crowchpunch.PushBack({ 97,286,55,71 });
	crowchpunch.PushBack({ 159,288,76,70 });
	crowchpunch.PushBack({ 97,286,55,71 });
	crowchpunch.speed = 0.12f;
	crowchpunch.loop = false;

	//kick while standing done
	kickingstanding.PushBack({ 417,163,60,84 });
	kickingstanding.PushBack({ 495,185,52,65 });
	kickingstanding.PushBack({ 562,153,44,94 });
	kickingstanding.PushBack({ 631,139,110,106 });
	kickingstanding.PushBack({ 770,156,54,90 });	
	kickingstanding.speed = 0.13f;
	kickingstanding.loop = false;

	//special attack while standing done
	specialattack.PushBack({ 620, 689, 51, 105 });
	specialattack.PushBack({ 547, 682, 54, 112 });
	specialattack.PushBack({ 482, 699, 60, 95 });
	specialattack.PushBack({ 399, 717, 67, 76 });
	specialattack.PushBack({ 399, 717, 67, 76 });
	specialattack.PushBack({ 260, 727, 65, 67 });
	specialattack.PushBack({ 195, 714, 60, 80 });
	specialattack.speed = 0.15f;
	specialattack.loop = false;

	//die
	die.PushBack({ 1929,836,64,155 });
	die.PushBack({ 1851,836,69,155 });
	die.PushBack({ 1756,836,84,155 });
	die.PushBack({ 1644,836,107,155 });
	die.PushBack({ 1542,836,87,155 });
	die.PushBack({ 1425,836,102,155 });
	die.PushBack({ 1303,836,112,155 });
	die.PushBack({ 1178,836,115,155 });
	die.speed = 0.15f;
	die.loop = false;

	//victory
	victory.PushBack({ 699,324,56,136 });
	victory.PushBack({ 772,324,56,136 });
	victory.PushBack({ 839,324,60,136 });
	victory.PushBack({ 908,324,56,136 });
	victory.speed = 0.15f;
	victory.loop = false;

	//hit
	hit.PushBack({ 20, 473, 67, 104 });
	hit.PushBack({ 88, 470, 73, 110 });
	hit.PushBack({ 20, 473, 67, 104 });
	hit.speed = 0.15f;
	hit.loop = false;

	//kickstun
	kickstun.PushBack({ 160,479,64,96 });
	kickstun.PushBack({ 235,479,69,96 });
	kickstun.speed = 0.04f;
	kickstun.loop = false;

	//punchstun
	punchstun.PushBack({ 88,469,68,106 });
	punchstun.PushBack({ 24,475,60,100 });
	punchstun.speed = 0.04f;
	punchstun.loop = false;

}

ModuleJoeHigashiPlayer::~ModuleJoeHigashiPlayer()
{}

// Load assets
bool ModuleJoeHigashiPlayer::Start()
{
	LOG("Loading joe higashi textures");
	current_animation = &idle;
	health = 100;
	score = 0;
	already_hit = false;
	body_collide = false;
	stuned = 0;

	position.x = 200;
	position.y = 220;
	App->lifebar->Enable();
	App->plscore->Enable();
	player_col = App->collision->AddCollider({ position.x + 10, position.y - 90, 33, 104 }, COLLIDER_PLAYER, App->JoeHigashiPlayer);


	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/3-Joe Higashi/Sprites joe higashi.png"); // arcade version

	skillFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Special Attacks/FX_PowerWaveAttackTerryBogardVoice.wav");
	punchFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack3.wav");
	kickFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack2.wav");

	return ret;
}

bool ModuleJoeHigashiPlayer::CleanUp()
{
	App->lifebar->Disable();
	App->plscore->Disable();
	App->textures->Unload(graphics);

	return true;
}

void ModuleJoeHigashiPlayer::Reset()
{
	health = 100;
	position.x = 200;
	position.y = 220;
	body_collide = false;
	already_hit = false;
	stuned = 0;

	current_animation = &idle;
	lockX = false;
	jumping = false;
	punching = false;
	kicking = false;
	crowchaction = false;
	specialattack_ = false;
	sp = false;
	t = 0;
	at = 0;
	st = 0;
	vy = 0;
}

int ModuleJoeHigashiPlayer::Pos_X()
{
	if (punching == true && fliped && at >= 13 && at <= 18)
		return (position.x + 34);

	if (kicking == true && fliped && at >= 25 && at <= 29)
		return (position.x + 44);

	return position.x;
}

update_status ModuleJoeHigashiPlayer::Update()
{
	godMode();
	if (App->enemy->position.x <= position.x)
	{
		fliped = true;
	}
	else
	{
		fliped = false;
	}

	if (punching == true) {
		at++;
		if (at == 1 && current_animation == &crowchpunch)
		{
			player_col->rect.h = 65;
			player_col->rect.w = 41;
			player_col->SetPos(position.x + 5, position.y - 67);
		}
		if (at == 12)
		{
			if (fliped == false)
				if (current_animation == &crowchpunch)
					player_punch_col = App->collision->AddCollider({ position.x + 46, position.y - 52, 35, 12 }, COLLIDER_PLAYER_ATTACK, App->player);
				else
					player_punch_col = App->collision->AddCollider({ position.x + 50, position.y - 90, 41, 12 }, COLLIDER_PLAYER_ATTACK, App->player);
			else
				if (current_animation == &crowchpunch)
					player_punch_col = App->collision->AddCollider({ position.x - 30, position.y - 52, 35, 12 }, COLLIDER_PLAYER_ATTACK, App->player);
				else
					player_punch_col = App->collision->AddCollider({ position.x - 30, position.y - 90, 41, 12 }, COLLIDER_PLAYER_ATTACK, App->player);

		}
		if (at == 19)
		{
			player_punch_col->to_delete = true;
			already_hit = false;
		}
		if (at == 13 && fliped)
		{
			position.x -= 34;
		}
		if (at == 19 && fliped)
		{
			position.x += 34;
		}
		if (at == 33)
		{
			punching = false;
			crowchaction = false;
		}
	}

	if (health < 0)
		health = 0;

	int speed = 2;

	if (kicking == true) {
		at++;
		if (at == 24)
		{
			if (fliped == false)
			{
				player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 85, 49, 17 }, COLLIDER_PLAYER_ATTACK, App->player);
				player_col->SetPos(position.x, position.y - 121);
				player_col->rect.h = 110;
				player_col->rect.w = 50;

			}
			else
			{
				player_kick_col = App->collision->AddCollider({ position.x - 25, position.y - 85, 49, 17 }, COLLIDER_PLAYER_ATTACK, App->player);
				player_col->SetPos(position.x + 20, position.y - 121);
				player_col->rect.h = 110;
				player_col->rect.w = 50;
			}
		}
		if (at == 25 && fliped)
		{
			position.x -= 44;
		}
		if (at == 30)
		{
			if (fliped)
			{
				position.x += 44;
			}
			player_kick_col->to_delete = true;
			already_hit = false;
		}
		if (at == 40)
		{
			kicking = false;
		}
	}

	if (sp == true) {
		st++;
		int n;
		if (!fliped)
		{
			n = 20;
			App->particles->skill.speed.x = 3.0f;
			App->particles->skill2.speed.x = 3.0f;
			App->particles->skill3.speed.x = 3.0f;
		}
		else
		{
			n = 0;
			App->particles->skill.speed.x = -3.0f;
			App->particles->skill2.speed.x = -3.0f;
			App->particles->skill3.speed.x = -3.0f;
		}
		if (st == 25)
		{
			App->particles->AddParticle(App->particles->skill, position.x + n, position.y - 40, COLLIDER_PLAYER_ATTACK);
		}
		if (st == 30)
		{
			App->particles->AddParticle(App->particles->skill2, position.x + n, position.y - 67, COLLIDER_PLAYER_ATTACK);
		}
		if (st == 35)
		{
			App->particles->AddParticle(App->particles->skill3, position.x + n, position.y - 95, COLLIDER_PLAYER_ATTACK);
			specialattack_ = false;
		}
		if (st == 40)
		{
			App->particles->AddParticle(App->particles->skill2, position.x + n, position.y - 67, COLLIDER_PLAYER_ATTACK);
		}
		if (st == 45)
		{
			App->particles->AddParticle(App->particles->skill, position.x + n, position.y - 40, COLLIDER_PLAYER_ATTACK);
		}
		if (st == 90)
			sp = false;
	}
	Jump();
	if (health == 0)
	{
		if (current_animation != &die)
		{
			die.Reset();
			current_animation = &die;
		}
	}
	else
	{
		if (App->enemy->Health() != 0)
		{
			if (stuned != 0 || App->fight_manager->Time() > 90)
			{
				if (stuned != 0)
				{
					at++;
					if (at < 30)
					{
						if (!fliped)
							position.x -= 2;
						else
							position.x += 2;
					}
					if (current_animation != &kickstun && stuned == 2)
					{
						kickstun.Reset();
						current_animation = &kickstun;
						at = 0;
					}
					if (current_animation != &punchstun && stuned == 1)
					{
						punchstun.Reset();
						current_animation = &punchstun;
						at = 0;
					}
					if (at == 60)
					{
						stuned = 0;
					}
					player_col->SetPos(position.x + 17, position.y - 91);
					if (position.x < 0)
						position.x = 0;
					if (position.x > 600)
						position.x = 600;
				}
			}
			else
			{
				if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_ && current_animation != &crowch)
				{
					if (body_collide && !fliped)
						body_collide = false;
					if (position.x != 0 && !body_collide && position.x * (-SCREEN_SIZE) < App->render->camera.x)
						position.x -= speed;
					if (fliped == true) {
						if (current_animation != &forward && !jumping && current_animation != &crowch)
						{
							forward.Reset();
							current_animation = &forward;
						}
					}
					else
					{
						if (current_animation != &backward && !jumping && current_animation != &crowch)
						{
							backward.Reset();
							current_animation = &backward;
						}
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_ && current_animation != &crowch)
				{
					if (body_collide && fliped)
						body_collide = false;
					if (position.x != 610 && !body_collide && (-SCREEN_SIZE * (position.x + 60)) > (App->render->camera.x - SCREEN_SIZE * SCREEN_WIDTH))
						position.x += speed;
					if (fliped == true)
					{
						if (current_animation != &backward && !jumping && current_animation != &crowch)
						{
							backward.Reset();
							current_animation = &backward;
						}
					}
					else
					{
						if (current_animation != &forward && !jumping && current_animation != &crowch)
						{
							forward.Reset();
							current_animation = &forward;
						}
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !jumping && !punching && !kicking && !specialattack_)
				{
					if (current_animation != &crowch)
					{
						lockX = true;
						crowchaction = true;
						crowch.Reset();
						current_animation = &crowch;
					}
					if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN && !punching && !kicking && !specialattack_) {
						if (current_animation != &crowchpunch && !jumping)
						{
							punching = true;
							at = 0;
							crowchpunch.Reset();
							current_animation = &crowchpunch;
							App->audio->playFx(punchFX);
						}
					}
					if (fliped == true)
					{
						if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !punching && !kicking && !specialattack_)
						{
							if (current_animation != &crowchprotecc)
							{
								crowchprotecc.Reset();
								current_animation = &crowchprotecc;
							}
						}
					}
					else {
						if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !punching && !kicking && !specialattack_)
						{
							if (current_animation != &crowchprotecc)
							{
								crowchprotecc.Reset();
								current_animation = &crowchprotecc;
							}
						}
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT && current_animation != &crowchpunch) {
					lockX = false;
					crowchaction = false;
				}

				if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP && current_animation != &crowchpunch)
				{
					current_animation = &idle;
				}

				if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && !jumping && !punching && !kicking && !specialattack_)
				{
					if (current_animation != &jumpiup)
					{
						jumping = true;
						t = 0;
						jumpiup.Reset();
						current_animation = &jumpiup;
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN && !punching && !kicking && !crowchaction && !specialattack_) {
					if (current_animation != &punchstanding && !jumping)
					{
						punching = true;
						at = 0;
						punchstanding.Reset();
						current_animation = &punchstanding;
						App->audio->playFx(punchFX);
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_T] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction && !specialattack_) {
					if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_)
					{
						kicking = true;
						at = 0;
						kickingstanding.Reset();
						current_animation = &kickingstanding;
						App->audio->playFx(kickFX);
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction && !sp) {
					if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_)
					{
						specialattack_ = true;
						sp = true;
						st = 0;
						specialattack.Reset();
						current_animation = &specialattack;
						App->audio->playFx(skillFX);
					}
				}

				if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
					&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
					&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
					&& !jumping && !punching && !kicking && !specialattack_)
					current_animation = &idle;

				if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
					&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
					&& App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
					&& !jumping && !punching && !kicking && !specialattack_)
					current_animation = &idle;

				if (current_animation != &punchstanding && current_animation != &kickingstanding && current_animation != &crowchpunch)
				{
					if (current_animation == &crowch || current_animation == &crowchprotecc && crowchaction)
					{
						player_col->rect.h = 65;
						player_col->rect.w = 41;
						player_col->SetPos(position.x + 5, position.y - 67);
					}
					else
					{
						if (!fliped)
						{
							player_col->SetPos(position.x + 10, position.y - 91);
							player_col->rect.h = 90;
							player_col->rect.w = 33;
						}
						else
						{
							player_col->SetPos(position.x + 17, position.y - 91);
							player_col->rect.h = 90;
							player_col->rect.w = 33;
						}
					}
				}
			}

		}
		else
		{
			if (current_animation != &victory)
			{
				victory.Reset();
				current_animation = &victory;
			}
		}
	}

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r, fliped);

	return UPDATE_CONTINUE;
}

void ModuleJoeHigashiPlayer::Damage(const int damage, const int type)
{
	if (current_animation == &backward || current_animation == &crowchprotecc)
		health -= damage / 2;
	else
		health -= damage;
	stuned = type;
}

void ModuleJoeHigashiPlayer::godMode()
{
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
		godMode_ = !godMode_;

	if (godMode_ == false)
		return;

	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
	{
		health = 0;
	}
	if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN)
	{
		App->enemy->health = 0;
	}
	// pressing O game is restarted
	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_intro);
	}

}

void ModuleJoeHigashiPlayer::OnCollision(Collider * a, Collider * b, bool colliding)
{
	if (colliding)
	{
		if (a->type == COLLIDER_PLAYER_ATTACK && b->type == COLLIDER_ENEMY && !already_hit)
		{
			already_hit = true;
			if (kicking)
			{
				App->enemy->Damage(30, 2);
				score += 200;
			}
			if (punching)
			{
				App->enemy->Damage(20, 1);
				score += 100;
			}
		}
		if (a->type == COLLIDER_PLAYER && b->type == COLLIDER_ENEMY)
		{
			body_collide = true;
		}
	}
	else
	{
		if (a->type == COLLIDER_PLAYER && b->type == COLLIDER_ENEMY)
		{
			body_collide = false;
		}
	}
}