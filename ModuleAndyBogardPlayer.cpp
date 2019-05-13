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
#include "ModuleAndyBogardPlayer.h"

#include "SDL/include/SDL_timer.h"



void ModuleAndyBogardPlayer::Jump() {
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

int ModuleAndyBogardPlayer::Health()
{
	return health;
}

int ModuleAndyBogardPlayer::Score()
{
	return score;
}

ModuleAndyBogardPlayer::ModuleAndyBogardPlayer()
{
	health = 100;
	already_hit = false;
	body_collide = false;

	// idle animation 
	idle.PushBack({ 195, 20, 62, 104 });
	idle.PushBack({ 274, 18, 61, 106 });
	idle.PushBack({ 354, 16, 63, 108 });
	idle.PushBack({ 434, 18, 61, 106 });
	idle.PushBack({ 518, 20, 62, 104 });
	idle.loop = true;
	idle.speed = 0.14f;

	// jump idle up 
	jumpiup.PushBack({ 88, 367, 39, 126 });

	// jump idle 
	jumpidown.PushBack({ 145, 367, 49, 81 });

	//jump while moving 
	jump.PushBack({ 204, 367, 56, 121 });

	//go forward done
	forward.PushBack({ 746, 602, 63, 98 });
	forward.PushBack({ 821, 601, 53, 98 });
	forward.PushBack({ 878, 602, 62, 98 });
	forward.PushBack({ 944, 599, 59, 101 });
	forward.speed = 0.13f;
	forward.loop = true;

	//go backwards done
	backward.PushBack({ 744, 473, 50, 100 });
	backward.PushBack({ 801, 471, 49, 100 });
	backward.PushBack({ 866, 475, 54, 98 });
	backward.PushBack({ 947, 476, 53, 96 });
	backward.speed = 0.13f;
	backward.loop = true;

	// crowch done
	crowch.PushBack({ 947, 162, 48, 60 });

	// crowch while going backwards and viceversa
	crowchprotecc.PushBack({ 830,881,51,74 });

	//punch while standing done
	punchstanding.PushBack({ 15, 121, 60, 101 });
	punchstanding.PushBack({ 553, 616, 50, 90 });
	punchstanding.PushBack({ 627, 616, 48, 96 });
	punchstanding.PushBack({ 220, 127, 93, 95 });
	punchstanding.speed = 0.15f;
	punchstanding.loop = false;

	//punch while crowching done
	crowchpunch.PushBack({ 881, 735, 49, 63 });
	crowchpunch.PushBack({ 942, 736, 78, 62 });
	crowchpunch.speed = 0.12f;
	crowchpunch.loop = false;

	//kick while standing 
	kickingstanding.PushBack({ 417,163,60,84 });
	kickingstanding.PushBack({ 495,185,52,65 });
	kickingstanding.PushBack({ 562,153,44,94 });
	kickingstanding.PushBack({ 631,139,110,106 });
	kickingstanding.PushBack({ 770,156,54,90 });
	kickingstanding.speed = 0.13f;
	kickingstanding.loop = false;

	//special attack while standing done
	specialattack.PushBack({ 24, 360, 65, 94 });
	specialattack.PushBack({ 94, 363, 48, 91 });
	specialattack.PushBack({ 155, 367, 48, 88 });
	specialattack.PushBack({ 217, 366, 98, 88 });
	specialattack.speed = 0.15f;
	specialattack.loop = false;

	//die done
	die.PushBack({ 28, 938, 92, 78});
	die.PushBack({ 127, 941, 98, 59 });
	die.PushBack({ 231, 942 ,89, 55 });
	die.PushBack({ 317, 950, 98, 42 });
	die.PushBack({ 422, 954, 111, 37 });
	die.PushBack({ 520, 917, 109, 32 });
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

	//kickstun doone
	kickstun.PushBack({ 843, 921, 54, 92 });
	kickstun.PushBack({ 908, 932, 64, 79 });
	kickstun.speed = 0.04f;
	kickstun.loop = false;

	//punchstun done
	punchstun.PushBack({ 721, 929, 62, 95 });
	punchstun.PushBack({ 780, 932 ,65, 82 });
	punchstun.speed = 0.04f;
	punchstun.loop = false;

}

ModuleAndyBogardPlayer::~ModuleAndyBogardPlayer()
{}

// Load assets
bool ModuleAndyBogardPlayer::Start()
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
	player_col = App->collision->AddCollider({ position.x + 10, position.y - 90, 33, 104 }, COLLIDER_PLAYER, App->player);


	bool ret = true;
	graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/2-Andy Bogard/Sprites_AndyBogard.png"); // arcade version

	skillFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Special Attacks/FX_PowerWaveAttackTerryBogardVoice.wav");
	punchFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack3.wav");
	kickFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack2.wav");

	return ret;
}

bool ModuleAndyBogardPlayer::CleanUp()
{
	App->lifebar->Disable();
	App->plscore->Disable();
	App->textures->Unload(graphics);

	return true;
}

void ModuleAndyBogardPlayer::Reset()
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

int ModuleAndyBogardPlayer::Pos_X()
{
	if (punching == true && fliped && at >= 13 && at <= 18)
		return (position.x + 34);

	if (kicking == true && fliped && at >= 25 && at <= 29)
		return (position.x + 44);

	return position.x;
}

update_status ModuleAndyBogardPlayer::Update()
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

	//if (sp == true) {
	//	st++;
	//	int n;
	//	if (!fliped)
	//	{
	//		n = 20;
	//		App->particles->skill.speed.x = 3.0f;
	//		App->particles->skill2.speed.x = 3.0f;
	//		App->particles->skill3.speed.x = 3.0f;
	//	}
	//	else
	//	{
	//		n = 0;
	//		App->particles->skill.speed.x = -3.0f;
	//		App->particles->skill2.speed.x = -3.0f;
	//		App->particles->skill3.speed.x = -3.0f;
	//	}
	//	if (st == 25)
	//	{
	//		App->particles->AddParticle(App->particles->skill, position.x + n, position.y - 40, COLLIDER_PLAYER_ATTACK);
	//	}
	//	if (st == 30)
	//	{
	//		App->particles->AddParticle(App->particles->skill2, position.x + n, position.y - 67, COLLIDER_PLAYER_ATTACK);
	//	}
	//	if (st == 35)
	//	{
	//		App->particles->AddParticle(App->particles->skill3, position.x + n, position.y - 95, COLLIDER_PLAYER_ATTACK);
	//		specialattack_ = false;
	//	}
	//	if (st == 40)
	//	{
	//		App->particles->AddParticle(App->particles->skill2, position.x + n, position.y - 67, COLLIDER_PLAYER_ATTACK);
	//	}
	//	if (st == 45)
	//	{
	//		App->particles->AddParticle(App->particles->skill, position.x + n, position.y - 40, COLLIDER_PLAYER_ATTACK);
	//	}
	//	if (st == 1000)
	//		sp = false;
	//}
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

void ModuleAndyBogardPlayer::Damage(const int damage, const int type)
{
	if (current_animation == &backward || current_animation == &crowchprotecc)
		health -= damage / 2;
	else
		health -= damage;
	stuned = type;
}

void ModuleAndyBogardPlayer::godMode()
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

void ModuleAndyBogardPlayer::OnCollision(Collider * a, Collider * b, bool colliding)
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