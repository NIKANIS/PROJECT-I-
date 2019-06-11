#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFightManager.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"
#include "ModuleRoundDisplay.h"
#include "ModuleFightTimer.h"
#include "ModuleSceneChoosePlayer.h"
#include "ModuleSceneMap.h"
#include "ModuleSlowdown.h"

#include "SDL/include/SDL_timer.h"

ModulePlayer::ModulePlayer(int player)
{
	this->player = player;
	health = 100;
	already_hit = false;
	body_collide = false;
}

ModulePlayer::~ModulePlayer(){}

bool ModulePlayer::Start()
{
	bool ret = true;

	LOG("Loading player textures");
	current_animation = &idle;
	health = 100;
	score = 0;
	already_hit = false;
	body_collide = false;
	stuned = 0;
	
	if (player == 0)
	{
		character = App->scene_chooseplayer->final_player1;
		position = { 200,220 };
		player_col = App->collision->AddCollider({ position.x + 5, position.y - 100, 33, 100 }, COLLIDER_PLAYER, App->player);
		App->lifebar->Enable();
		App->plscore->Enable();
		if (App->scene_chooseplayer->final_player1 == 1)
		{
			graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/3-Joe Higashi/Sprites joe higashi.png");
			LoadJoeAnimations();

			width = 62;
		}

		if (App->scene_chooseplayer->final_player1 == 2)
		{
			graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard.png");
			LoadTerryAnimations();

			width = 60;
		}

		if (App->scene_chooseplayer->final_player1 == 3)
		{
			graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/2-Andy Bogard/Sprites_AndyBogard.png");
			LoadAndyAnimations();

			width = 59;
		}
	}

	if (player == 1)
	{
		character = App->scene_chooseplayer->final_player2;
		position = { 400,220 };
		player_col = App->collision->AddCollider({ position.x + 5, position.y - 100, 33, 100 }, COLLIDER_ENEMY, App->enemy);
		App->lifebar2->Enable();
		App->enscore->Enable();
		if (App->scene_chooseplayer->final_player2 == 1)
		{
			if (App->scene_chooseplayer->final_player1 == 1)
				graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/3-Joe Higashi/Sprites joe higashi2.png");
			else
				graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/3-Joe Higashi/Sprites joe higashi.png");
			LoadJoeAnimations();

			width = 62;
			//draw_pos_x = position.x - (62 - width);
		}

		if (App->scene_chooseplayer->final_player2 == 2)
		{
			if (App->scene_chooseplayer->final_player1 == 2)
			{
				graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard2.png");
			}
			else
				graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/1-Terry Bogard/spritesTerryBogard.png");
			LoadTerryAnimations();

			width = 60;
			//draw_pos_x = position.x - (60 - width);
		}

		if (App->scene_chooseplayer->final_player2 == 3)
		{	
			if (App->scene_chooseplayer->final_player1 == 3)
				graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/2-Andy Bogard/Sprites_AndyBogard2.png");
			else
				graphics = App->textures->Load("SPRITES FATAL FURY/CHARACTERS/2-Andy Bogard/Sprites_AndyBogard.png");
			LoadAndyAnimations();

			width = 59;
			//draw_pos_x = position.x - (59 - width);
		}
	}

		
	return ret;
}

void ModulePlayer::LoadJoeAnimations()
{
	skillFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Special Attacks/FX_HurricaneUpAttackJoeHigashiVoice.wav");
	punchFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack2.wav");
	kickFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack2.wav");

	// idle animation done 
	idle.PushBack({ 190, 20, 62, 104 }); idle.PushBack({ 269, 18, 61, 106 }); idle.PushBack({ 349, 16, 63, 108 });
	idle.PushBack({ 429, 18, 61, 106 }); idle.PushBack({ 513, 20, 62, 104 });
	idle.loop = true; idle.speed = 0.14f;

	// jump idle up done
	jumpiup.PushBack({ 83, 367, 39, 126 });

	// jump forward up
	jumpfup.PushBack({ 952,612,64,103 });
	jumpfup.PushBack({152,495,73,80});	
	jumpfup.PushBack({ 237,495,65,80 });
	jumpfup.PushBack({ 318,495,73,80 });
	jumpfup.PushBack({ 83,495,65,80 });
	jumpfup.loop = true;
	jumpfup.speed = 0.13f;

	//jump backwards up

	jumpbup.PushBack({ 412,476,50,124 });
	jumpbup.PushBack({ 318,495,73,80 });
	jumpbup.PushBack({ 237,495,65,80 });
	jumpbup.PushBack({ 152,495,73,80 });
	jumpbup.PushBack({ 83,495,65,80});
	jumpbup.loop = true;
	jumpbup.speed = 0.13f;

	//jump forward and backwards down

	jumpfbdown.PushBack({ 411,475,51,125 });

	// jump idle down 
	jumpidown.PushBack({ 140, 367, 49, 81 });

	//go forward done	
	forward.PushBack({ 592, 19, 75, 105 }); forward.PushBack({ 681, 11, 65, 113 }); forward.PushBack({ 753, 5, 62, 119 }); forward.PushBack({ 820, 16, 63, 108 });
	forward.speed = 0.13f; forward.loop = true;

	//go backwards done
	backward.PushBack({ 28, 144, 60, 102 }); backward.PushBack({ 106, 141, 55, 105 }); backward.PushBack({ 171, 136, 55, 110 }); backward.PushBack({ 236, 140, 56, 106 });
	backward.speed = 0.13f; backward.loop = true;

	// crowch done
	crowch.PushBack({ 756, 888, 59, 69 });

	// crowch while going backwards and viceversa
	crowchprotecc.PushBack({ 825,881,51,74 });

	//punch while standing done	
	punchstanding.PushBack({ 476, 610, 64, 102 }); punchstanding.PushBack({ 548, 616, 63, 96 }); punchstanding.PushBack({ 622, 616, 97, 96 });
	punchstanding.PushBack({ 548, 616, 63, 96 }); punchstanding.PushBack({ 476, 610, 64, 102 });
	punchstanding.speed = 0.15f; punchstanding.loop = false;

	//punch while crowching 
	crowchpunch.PushBack({ 92,286,55,71 });
	crowchpunch.PushBack({ 154,288,76,70 });
	crowchpunch.PushBack({ 92,286,55,71 });
	crowchpunch.speed = 0.14f;
	crowchpunch.loop = false;

	//kick while standing done
	kickingstanding.PushBack({ 412,163,60,84 });
	kickingstanding.PushBack({ 490,185,52,65 });
	kickingstanding.PushBack({ 557,153,44,94 });
	kickingstanding.PushBack({ 626,139,110,106 });
	kickingstanding.PushBack({ 765,156,54,90 });
	kickingstanding.speed = 0.13f;
	kickingstanding.loop = false;

	//special attack while standing done
	specialattack.PushBack({ 1053, 44, 54, 102 });
	specialattack.PushBack({ 1132, 83, 80, 63 });
	specialattack.PushBack({ 1238, 60, 50, 84 });
	specialattack.PushBack({ 1313, 5, 47, 141 });
	specialattack.speed = 0.1f;
	specialattack.loop = false;

	//die
	die.PushBack({ 856, 495, 75, 101 });
	die.PushBack({ 103,751,61,94 });
	die.PushBack({ 177,743,70,87 });
	die.PushBack({ 432,736,79,65 });
	die.PushBack({ 554,780,115,36 });
	die.PushBack({ 2,884,120,24 });
	die.speed = 0.11f;
	die.loop = false;

	//victory
	victory.PushBack({ 573,943,73,62 });
	victory.PushBack({ 497,923,76,64 });
	victory.PushBack({ 504,821,94,87 });
	victory.PushBack({ 504,821,94,87 });
	victory.speed = 0.08f;
	victory.loop = false;

	//hit
	hit.PushBack({ 856, 495, 75, 101 });
	hit.PushBack({ 782, 510, 67, 86 });
	hit.PushBack({ 856, 495, 75, 101 });
	hit.speed = 0.15f;
	hit.loop = false;

	//kickstun
	//kickstun.PushBack({ 557, 495, 62, 105 }); 
	kickstun.PushBack({ 626, 495, 70, 103 });
	kickstun.PushBack({ 709, 495, 66, 103 });
	kickstun.PushBack({ 856, 495, 75, 103 });
	//kickstun.PushBack({ 782, 495, 67, 103 });
	kickstun.speed = 0.2f;
	kickstun.loop = false;

	//punchstun
	//punchstun.PushBack({ 557, 495, 62, 105 });
	punchstun.PushBack({ 626, 495, 70, 103 });
	punchstun.PushBack({ 709, 495, 66, 103 });
	punchstun.PushBack({ 856, 495, 75, 103 });
	//punchstun.PushBack({ 782, 495, 67, 103 });
	punchstun.speed = 0.2f;
	punchstun.loop = false;

	//low kick
	lowkick.PushBack({ 688,724,59,69 });
	lowkick.PushBack({ 758,737,57,56 });
	lowkick.PushBack({ 821,744,81,49 });
	lowkick.PushBack({ 758,737,57,56 });
	lowkick.PushBack({ 688,724,59,69 });
	lowkick.speed = 0.15f;
	lowkick.loop = false;

	//takedown done
	takedown_done.PushBack({ 476, 610, 64, 102 });
	takedown_done.PushBack({ 1257 - 25, 540, 57 + 25, 102 });
	takedown_done.PushBack({ 1415 - 25, 540, 59 + 25, 101 });
	takedown_done.PushBack({ 1107 - 25, 669, 72 + 25, 71 });
	takedown_done.PushBack({ 1235 - 25, 673, 90 + 25, 63 });
	takedown_done.speed = 0.13f;
	takedown_done.loop = false;

	//takedown fail
	takedown_fail.PushBack({ 476, 610, 64, 102 });
	takedown_fail.PushBack({ 1257 - 25, 540, 57 + 25, 102 });
	takedown_fail.PushBack({ 476, 610, 64, 102 });
	takedown_fail.speed = 0.11f;
	takedown_fail.loop = false;

	//takedown recieved
	takedown_recieved.PushBack({ 1692,593,74,100 });
	takedown_recieved.PushBack({ 1784,599,61,94 });
	takedown_recieved.PushBack({ 1854,606,70,87 });
	takedown_recieved.PushBack({ 1868,731,80,65 });
	takedown_recieved.PushBack({ 1784,706,74,98 });
	takedown_recieved.PushBack({ 1877,721,79,65 });
	takedown_recieved.PushBack({ 1659,822,115,36 });
	takedown_recieved.PushBack({ 1798,828,120,24 });
	takedown_recieved.speed = 0.15f;
	takedown_recieved.loop = false;

	takedown_recieved2.PushBack({ 1672,884,59,52 });
	takedown_recieved2.PushBack({ 1774,874,60,62 });
	takedown_recieved2.PushBack({ 1868,874,56,84 });
	takedown_recieved2.speed = 0.15f;
	takedown_recieved2.loop = false;

	//air punch diagonal (hacia delante y hacia atrás)
	airpunchdiagonal.PushBack({ 1118,899,70,98 });
	airpunchdiagonal.PushBack({ 1203,912,42,85 });
	airpunchdiagonal.PushBack({ 1442,798,54,90 });
	airpunchdiagonal.speed = 0.15f;
	airpunchdiagonal.loop = false;

	//air punch saltando recto
	airpunchstraight.PushBack({ 1105,773,59,106 });
	airpunchstraight.PushBack({ 1188,770,71,112 });
	airpunchstraight.PushBack({ 1105,773,59,106 });
	/*airpunchstraight.PushBack({ 1359,758,56,121 });
	airpunchstraight.PushBack({ 1442,798,54,90 });*/
	airpunchstraight.speed = 0.15f;
	airpunchstraight.loop = false;

	//air kick saltando recto
	airkickstraight.PushBack({ 1559,412,59,100 });
	airkickstraight.PushBack({ 1632,413,81,99 });
	airkickstraight.PushBack({ 1559,412,59,100 });
	/*airkickstraight.PushBack({ 199,367,56,121 });
	airkickstraight.PushBack({ 945,393,54,90 });*/
	airkickstraight.speed = 0.15f;
	airkickstraight.loop = false;

	//air kick saltando diagonal (hacia delante y hacia atrás)
	airkickdiagonal.PushBack({ 338,364,50,124 });
	airkickdiagonal.PushBack({ 394,379,84,95 });
	//airkickdiagonal.PushBack({ 945,393,54,90 });
	airkickdiagonal.speed = 0.15f;
	airkickdiagonal.loop = false;

	//Joe skill
	skillJoe.anim.PushBack({ 1419, 85, 40, 60 }); //1ra
	skillJoe.anim.PushBack({ 1475, 56,50, 89 }); //2nda
	skillJoe.life = 1000;
	skillJoe.speed.x = 3.0f;
	skillJoe.anim.speed = 0.04f;
	skillJoe.anim.loop = false;


	skillJoe2.anim.PushBack({ 1538, 33, 61, 112 }); //3ra
	skillJoe2.anim.PushBack({ 1671, 33, 63, 112 }); //4ta
	skillJoe2.anim.PushBack({ 1604, 33, 58, 112 }); //5ta
	skillJoe2.life = 6000;
	skillJoe2.speed.x = 3.0f;
	skillJoe2.anim.speed = 0.1f;

	//Joe skill
	skillJoe_.anim.PushBack({ 1419, 85, 40, 60 }); //1ra
	skillJoe_.anim.PushBack({ 1475, 56,50, 89 }); //2nda
	skillJoe_.life = 1000;
	skillJoe_.speed.x = 3.0f;
	skillJoe_.anim.speed = 0.04f;
	skillJoe_.anim.loop = false;


	skillJoe2_.anim.PushBack({ 1538, 33, 61, 112 }); //3ra
	skillJoe2_.anim.PushBack({ 1671, 33, 63, 112 }); //4ta
	skillJoe2_.anim.PushBack({ 1604, 33, 58, 112 }); //5ta
	skillJoe2_.life = 6000;
	skillJoe2_.speed.x = 3.0f;
	skillJoe2_.anim.speed = 0.1f;

	//JoeSpecial Kick
	JoeSpecialKick.PushBack({ 1053, 183, 60, 85 });
	JoeSpecialKick.PushBack({ 1113, 206, 52, 62 }); 
	JoeSpecialKick.PushBack({ 1179, 173, 44, 94 });
	JoeSpecialKick.speed = 0.15f;
	JoeSpecialKick.loop = false;

	JoeSpecialKick2.PushBack({ 1246, 162, 112, 106 });
	JoeSpecialKick2.PushBack({ 1383, 162, 110, 106 });
	JoeSpecialKick2.PushBack({ 1526, 162, 114, 106 });
	JoeSpecialKick2.speed = 0.15f;
	JoeSpecialKick2.loop = false;

	//JoeSpecial Knee
	JoeSpecialKnee.PushBack({ 1046, 405, 49, 89 });
	JoeSpecialKnee.PushBack({ 1104, 408, 50, 80 });
	JoeSpecialKnee.PushBack({ 1166, 401, 72, 93 });
	JoeSpecialKnee.PushBack({ 1245, 399, 92, 93 });
	JoeSpecialKnee.PushBack({ 1346, 395, 107, 93 });
	JoeSpecialKnee.speed = 0.15f;
	JoeSpecialKnee.loop = false;

	//Joe Multiple Punch
	JoeMultiplePunch.PushBack({ 1049, 281, 53, 102 });
	JoeMultiplePunch.PushBack({ 1115, 281, 85, 102 });
	JoeMultiplePunch.PushBack({ 1200, 281, 82, 102 });
	JoeMultiplePunch.PushBack({ 1294, 281, 83, 102 });
	JoeMultiplePunch.PushBack({ 1049, 281, 53, 102 });
	JoeMultiplePunch.PushBack({ 1460, 275, 82, 108 });
	JoeMultiplePunch.speed = 0.15f;
	JoeMultiplePunch.loop = false;

	//Joe Yellow Punch
	JoeYellowPunch.PushBack({ 1049, 281, 53, 102 });
	JoeYellowPunch.PushBack({ 1622, 287, 63, 96 });
	JoeYellowPunch.PushBack({ 1697, 287, 100, 96 });
	JoeYellowPunch.PushBack({ 1804, 287, 97, 96 });
	JoeYellowPunch.PushBack({ 1889, 175, 97, 96 });
	JoeYellowPunch.PushBack({ 1863, 395, 97, 96 });
	JoeYellowPunch.speed = 0.15f;
	JoeYellowPunch.loop = false;

}
void ModulePlayer::LoadTerryAnimations()
{
	skillFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Special Attacks/FX_PowerWaveAttackTerryBogardVoice.wav");
	punchFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack3.wav");
	kickFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack3.wav");

	// idle animation done 
	idle.PushBack({ 27, 913, 60, 105 });
	idle.PushBack({ 95, 915, 61, 104 });
	idle.PushBack({ 164, 914, 60, 104 });
	idle.PushBack({ 95, 915, 61, 104 });
	idle.loop = true;
	idle.speed = 0.13f;

	// jump idle up done
	jumpiup.PushBack({ 907, 471, 61, 128 });

	// jump forward up
	jumpfup.PushBack({ 841,919,88,103 });
	jumpfup.PushBack({ 937 + 233,919 - 163,54,103 });
	jumpfup.PushBack({ 999 + 233,919 - 163,88,103 });
	jumpfup.PushBack({ 1098 + 233,919 - 163,54,103 });
	jumpfup.loop = true;
	jumpfup.speed = 0.13f;

	//jump backwards up

	jumpbup.PushBack({ 999 + 233,919 - 163,88,103 });
	jumpbup.PushBack({ 937 + 233,919 - 163,54,103 });
	jumpbup.PushBack({ 841,919,88,103 });
	jumpbup.PushBack({ 1098 + 233,919 - 163,54,103 });
	jumpbup.loop = true;
	jumpbup.speed = 0.13f;

	//jump forward and backwards down

	jumpfbdown.PushBack({ 783,919,57,103 });

	// jump idle down 
	jumpidown.PushBack({ 908, 655, 60, 96 });

	//go forward done
	forward.PushBack({ 1111, 270, 69, 105 });
	forward.PushBack({ 1193, 271, 59, 104 });
	forward.PushBack({ 1267, 274, 59, 101 });
	forward.PushBack({ 1036, 273, 59, 102 });
	forward.speed = 0.13f;
	forward.loop = true;

	//go backwards done
	backward.PushBack({ 1465, 446, 59, 102 });
	backward.PushBack({ 1396, 445, 55, 104 });
	backward.PushBack({ 1327, 442, 56, 106 });
	backward.PushBack({ 1258, 444, 57, 104 });
	backward.speed = 0.13f;
	backward.loop = true;

	// crowch done
	crowch.PushBack({ 440, 606, 52, 63 });

	// crowch while going backwards and viceversa
	crowchprotecc.PushBack({ 380,607,52,62 });

	//punch while standing
	punchstanding.PushBack({ 434, 919, 71, 99 });
	punchstanding.PushBack({ 507, 919, 61, 100 });
	punchstanding.PushBack({ 575, 917, 95, 102 });
	punchstanding.PushBack({ 507, 919, 61, 100 });
	punchstanding.PushBack({ 434, 919, 71, 99 });
	punchstanding.speed = 0.15f;
	punchstanding.loop = false;

	//punch while crowching 
	crowchpunch.PushBack({ 239,832,57,66 });
	crowchpunch.PushBack({ 302,835,50,65 });
	crowchpunch.PushBack({ 359,834,82,64 });
	crowchpunch.PushBack({ 302,835,50,65 });
	crowchpunch.PushBack({ 239,832,57,66 });
	crowchpunch.speed = 0.15f;
	crowchpunch.loop = false;

	//kick while standing done
	kickingstanding.PushBack({ 1119,631,59,103 });
	kickingstanding.PushBack({ 1196,628,47,106 });
	kickingstanding.PushBack({ 1261,642,47,93 });
	kickingstanding.PushBack({ 1314,617,57,120 });
	kickingstanding.PushBack({ 1379,617,42,120 });
	kickingstanding.PushBack({ 1441,612,116,125 });
	kickingstanding.PushBack({ 1572,628,62,117 });
	kickingstanding.PushBack({ 1653,625,57,91 });
	kickingstanding.speed = 0.20f;
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

	//low kick
	lowkick.PushBack({ 1132,154,58,63 });
	lowkick.PushBack({ 1205,154,92,60 });
	lowkick.PushBack({ 1132,154,58,63 });
	lowkick.speed = 0.12f;
	lowkick.loop = false;

	//takedown done
	takedown_done.PushBack({ 331,927,52,90 });
	takedown_done.PushBack({ 760,817,62,94 });
	takedown_done.PushBack({ 827,831,77,87 });
	takedown_done.PushBack({ 907,830,93,80 });
	takedown_done.PushBack({ 907,830,93,80 });
	takedown_done.PushBack({ 907,830,93,80 });
	takedown_done.PushBack({ 907,830,93,80 });
	takedown_done.PushBack({ 907,830,93,80 });
	takedown_done.PushBack({ 907,830,93,80 });
	takedown_done.PushBack({ 978,918,52,90 });
	takedown_done.speed = 0.13f;
	takedown_done.loop = false;

	//takedown fail
	takedown_fail.PushBack({ 331 - 25 ,927, 52 + 25, 90 });
	takedown_fail.PushBack({ 760 - 25, 817, 62 + 25, 94 });
	takedown_fail.PushBack({ 978 - 25, 918, 52 + 25, 90 });
	takedown_fail.speed = 0.11f;
	takedown_fail.loop = false;

	//takedown recieved
	takedown_recieved.PushBack({ 1919,188,67,105 });
	takedown_recieved.PushBack({ 1828,198,63,95 });
	takedown_recieved.PushBack({ 1919,303,63,95 });
	takedown_recieved.PushBack({ 1809,319,101,63 });
	takedown_recieved.PushBack({ 1682,339,111,43 });
	takedown_recieved.PushBack({ 1868,445,114,30 });
	takedown_recieved.speed = 0.15f;
	takedown_recieved.loop = false;

	takedown_recieved2.PushBack({ 1761,430,95,45 });
	takedown_recieved2.PushBack({ 1658,407,79,68 });
	takedown_recieved2.PushBack({ 1919,505,56,70 });
	takedown_recieved2.PushBack({ 1835,505,56,79 });
	takedown_recieved2.speed = 0.15f;
	takedown_recieved2.loop = false;

	airpunchdiagonal.PushBack({ 1813,8,78,88 });
	airpunchdiagonal.PushBack({ 1903,8,57,89 });
	airpunchdiagonal.PushBack({ 1971,3,57,94 });	
	airpunchdiagonal.speed = 0.15f;
	airpunchdiagonal.loop = false;

	airpunchstraight.PushBack({ 1802,616,51,103 });
	airpunchstraight.PushBack({ 1877,618,83,99 });
	airpunchstraight.PushBack({ 1802,616,51,103 });
	airpunchstraight.speed = 0.15f;
	airpunchstraight.loop = false;

	//air kick saltando recto
	airkickstraight.PushBack({ 1486,169,57,103 });
	airkickstraight.PushBack({ 1556,169,72,93 });
	airkickstraight.speed = 0.15f;
	airkickstraight.loop = false;

	//air kick saltando diagonal (hacia delante y hacia atrás)
	airkickdiagonal.PushBack({ 1903,8,57,89 });
	airkickdiagonal.PushBack({ 1458,295,113,69 });
	airkickdiagonal.speed = 0.15f;
	airkickdiagonal.loop = false;

	//TerrySpecialKick
	TerrySpecialKick.PushBack({ 12, 225, 57, 107 });
	TerrySpecialKick.PushBack({ 76, 237, 80, 95});
	TerrySpecialKick.PushBack({ 157, 247, 81, 85});
	TerrySpecialKick.PushBack({ 241, 242, 102, 90});
	TerrySpecialKick.PushBack({ 343, 237, 82, 96});
	TerrySpecialKick.PushBack({ 439, 226, 103, 121});
	TerrySpecialKick.PushBack({ 578, 336, 57, 94 });
	TerrySpecialKick.speed = 0.15f;
	TerrySpecialKick.loop = false;

	//TerrySpecialPunch1
	TerrySpecialPunch1.PushBack({ 10, 356, 88, 110 });
	TerrySpecialPunch1.PushBack({ 112, 366, 58, 98 });
	TerrySpecialPunch1.PushBack({ 188, 381, 62, 83 });
	TerrySpecialPunch1.speed = 0.15f;
	TerrySpecialPunch1.loop = false;

	//TerrySpecialPunch2
	TerrySpecialPunch2.PushBack({ 257, 373, 116, 93 });
	TerrySpecialPunch2.PushBack({ 375, 353, 110, 94 });	
	TerrySpecialPunch2.speed = 0.15f;
	TerrySpecialPunch2.loop = true;
}
void ModulePlayer::LoadAndyAnimations()
{
	skillFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Special Attacks/FX_HishokenAttackAndyBogardVoice.wav");
	punchFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack.wav");
	kickFX = App->audio->loadWAV("AUDIO FATAL FURY/FX[WAV]/Voice/Attacks/FX_Attack.wav");

	// idle animation done
	idle.PushBack({ 428, 810, 59, 98 });
	idle.PushBack({ 497, 808, 59, 100 });
	idle.PushBack({ 428, 810, 59, 98 });
	idle.PushBack({ 635, 811, 60, 95 });
	idle.loop = true;
	idle.speed = 0.13f;

	// jump idle up 
	jumpiup.PushBack({ 515, 119, 42, 104 });

	// jump forward up
	jumpfup.PushBack({932,822,68,94});
	jumpfup.PushBack({ 1003,822,56,94 });	
	jumpfup.PushBack({ 802,822,68,94 });
	jumpfup.PushBack({ 872,822,56,94 });
	jumpfup.loop = true;
	jumpfup.speed = 0.13f;

	//jump backwards up

	jumpbup.PushBack({ 802,822,68,94 });
	jumpbup.PushBack({ 1003,822,56,94 });
	jumpbup.PushBack({ 932,822,68,94 });
	jumpbup.PushBack({ 872,822,56,94 });
	jumpbup.loop = true;
	jumpbup.speed = 0.13f;

	//jump forward and backwards down

	jumpfbdown.PushBack({729,822,56,94});


	// jump idle 
	jumpidown.PushBack({ 577, 119, 51, 92 });

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
	backward.speed = 0.13f;
	backward.loop = true;

	// crowch done
	crowch.PushBack({ 947, 162, 48, 60 });

	// crowch while going backwards and viceversa done
	crowchprotecc.PushBack({ 944,81,44,64 });

	//punch while standing done
	punchstanding.PushBack({ 89, 132, 49, 90 });
	punchstanding.PushBack({ 155, 128, 48, 95 });
	punchstanding.PushBack({ 220, 127, 93, 95 });
	punchstanding.PushBack({ 220, 127, 93, 95 });
	punchstanding.PushBack({ 155, 128, 48, 95 });
	punchstanding.speed = 0.15f;
	punchstanding.loop = false;

	//punch while crowching done
	crowchpunch.PushBack({ 881, 735, 49, 63 });
	crowchpunch.PushBack({ 942, 736, 78, 62 });
	crowchpunch.speed = 0.12f;
	crowchpunch.loop = false;

	//kick while standing DONE
	kickingstanding.PushBack({ 312,14,44,98 });
	kickingstanding.PushBack({ 379,25,57,87 });
	kickingstanding.PushBack({ 449,22,52,90 });
	kickingstanding.PushBack({ 515,25,113,94 }); //instead of 94, put 75 as normal sprite
	kickingstanding.PushBack({ 642,12,83,94 });
	kickingstanding.PushBack({ 748,28,53,79 });
	kickingstanding.speed = 0.15f;
	kickingstanding.loop = false;

	//special attack while standing done
	specialattack.PushBack({ 24, 360, 65, 94 });
	specialattack.PushBack({ 94, 363, 48, 91 });
	specialattack.PushBack({ 155, 367, 48, 88 });
	specialattack.PushBack({ 217, 366, 98, 88 });
	specialattack.speed = 0.15f;
	specialattack.loop = false;

	//die done
	die.PushBack({ 28, 938, 92, 78 });
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

	//low kick
	lowkick.PushBack({ 24,740,53,60 });
	lowkick.PushBack({ 94,745,66,55 });
	lowkick.PushBack({ 166,765,119,35 });
	lowkick.PushBack({ 94,745,66,55 });
	lowkick.PushBack({ 24,740,53,60 });
	lowkick.speed = 0.19f;
	lowkick.loop = false;

	//Andy skill
	skillAndy.anim.PushBack({ 328, 378, 22, 22 }); //1ra
	skillAndy.anim.PushBack({ 364, 357, 35, 64 }); //2nda
	skillAndy.anim.PushBack({ 404, 358, 48, 62 }); //3ra
	skillAndy.life = 1000;
	skillAndy.speed.x = 2.0f;
	skillAndy.anim.speed = 0.06f;
	skillAndy.anim.loop = false;

	skillAndy2.anim.PushBack({ 462, 345, 61, 87 }); //4ta
	skillAndy2.anim.PushBack({ 534, 346, 46, 85 }); //5ta
	skillAndy2.life = 6000;
	skillAndy2.speed.x = 3.0f;
	skillAndy2.anim.speed = 0.1f;

	//Andy skill
	skillAndy_.anim.PushBack({ 328, 378, 22, 22 }); //1ra
	skillAndy_.anim.PushBack({ 364, 357, 35, 64 }); //2nda
	skillAndy_.anim.PushBack({ 404, 358, 48, 62 }); //3ra
	skillAndy_.life = 1000;
	skillAndy_.speed.x = 2.0f;
	skillAndy_.anim.speed = 0.06f;
	skillAndy_.anim.loop = false;


	skillAndy2_.anim.PushBack({ 462, 345, 61, 87 }); //4ta
	skillAndy2_.anim.PushBack({ 534, 346, 46, 85 }); //5ta
	skillAndy2_.life = 6000;
	skillAndy2_.speed.x = 3.0f;
	skillAndy2_.anim.speed = 0.1f;
}

bool ModulePlayer::CleanUp()
{
	App->textures->Unload(graphics);
	if (player == 0)
	{
		App->lifebar->Disable();
		App->plscore->Disable();
	}
	else
	{
		App->lifebar2->Disable();
		App->enscore->Disable();
	}

	return true;
}

void ModulePlayer::Reset()
{	
	health = 100;

	if (player == 0)
		position = { 200,220 };
	else
		position = { 400,220 };

	body_collide = false;
	already_hit = false;
	stuned = 0;
	if (player_punch_col != nullptr)
		player_punch_col->to_delete = true;
	if (player_kick_col != nullptr)
		player_kick_col->to_delete = true;
	if (player_skill_col != nullptr)
		player_skill_col->to_delete = true;

	current_animation = &idle;
	lockX = false;
	jumping = false;
	punching = false;
	kicking = false;
	lowkicking = false;
	crowchaction = false;
	specialattack_ = false;
	sp = false;
	takingdown = false;
	t = 0; 
	at = 0; 
	st = 0;
	vy = 0;
	tktempo = 0;
}

int ModulePlayer::Health()
{
	return health;
}

int ModulePlayer::Score()
{
	return score;
}

int ModulePlayer::Pos_X()
{
	if (punching == true && fliped && at >= 13 && at <= 18) 
		return (position.x);

	if (kicking == true && fliped && at >= 25 && at <= 29) 
		return (position.x);

	return position.x;
}

void ModulePlayer::Jump() {
	if (jumping) {
		lockX = true;
		if ((position.x*(-SCREEN_SIZE)) < App->render->camera.x || (-SCREEN_SIZE * (position.x + 60)) > (App->render->camera.x - SCREEN_SIZE * SCREEN_WIDTH))
			position.x += jumpspeed;
		t++;
		position.y = 220 - 7 * t + 0.12*(t*t);
		vy = -7 + 0.24*t;
		if (position.y >= 220)
		{
			if (player_kick_col != nullptr)
				player_kick_col->to_delete = true;
			if (player_punch_col != nullptr)
				player_punch_col->to_delete = true;
			jumping = false;
			airkicking = false;
			airpunching = false;
			punching = false;
			jt = 0;
			at = 0;
			already_hit = false;
			position.y = 220;
		}
		if (airkicking || airpunching)
		{
			jt++;
			if (player_kick_col != nullptr && airkicking)
			{
				player_kick_col->rect.x += jumpspeed;
				player_kick_col->rect.y = 220 - 7 * t + 0.12*(t*t);
			}
		}

		if (vy > 0 && !airkicking && !airpunching)
			if (current_animation != &jumpidown && current_animation != &die && current_animation != &takedown_fail)
				if (jumptype == 0)
				{
					jumpidown.Reset();
					current_animation = &jumpidown;
				}
				else
				{
					jumpfbdown.Reset();
					current_animation = &jumpfbdown;
				}
		if (jt == 20)
		{
			if (player_kick_col != nullptr)
				player_kick_col->to_delete = true;
			if (player_punch_col != nullptr)
				player_punch_col->to_delete = true;
			if (current_animation != &jumpidown && current_animation != &die && current_animation != &takedown_fail)
				if (jumptype == 0)
				{
					jumpidown.Reset();
					current_animation = &jumpidown;
				}
				else
				{
					jumpfbdown.Reset();
					current_animation = &jumpfbdown;
				}
			jt = 0;
		}

		if (fliped)
			player_col->SetPos(position.x, position.y - 90);
	}
}

void ModulePlayer::Punch()
{
	if (punching == true) {
		at++;
		if (already_hit && !crowchaction && !airpunching)
		{ 
			if (!fliped)
				position.x--;
			else
				position.x++;
		}

		if (at == 1 && current_animation == &crowchpunch)
		{
				player_col->rect.h = 65;
				player_col->rect.w = 41;
				player_col->SetPos(position.x + 5, position.y - 67);
		}
		if (current_animation == &airpunchstraight && jumping)
		{
			player_col->rect.h = 65;
			player_col->rect.w = 41;
			player_col->SetPos(position.x + 5, position.y - 67);
		}
		if (at == 12)
		{
			COLLIDER_TYPE COLLIDER_ = COLLIDER_NONE;
			ModulePlayer *source = nullptr;
			if (player == 0)
			{
				COLLIDER_ = COLLIDER_PLAYER_ATTACK;
				source = App->player;
			}
			else
			{
				COLLIDER_ = COLLIDER_ENEMY_ATTACK;
				source = App->enemy;
			}

			if (character == 1)
			{
				if (fliped == false)
				{
					if (current_animation == &airpunchstraight)
					{
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 90, 35, 12 }, COLLIDER_, source);
					}	
					if (current_animation == &airpunchdiagonal)
					{
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 90, 35, 12 }, COLLIDER_, source);
					}
					if (current_animation == &crowchpunch)																		
						player_punch_col = App->collision->AddCollider({ position.x + 40, position.y - 60, 35, 12 }, COLLIDER_, source);
					if(current_animation == &punchstanding)																		
					{																											
						player_punch_col = App->collision->AddCollider({ position.x + 50, position.y - 87, 45, 12 }, COLLIDER_, source);
						player_col->SetPos(position.x + 17, position.y - 100);
					}
				}
				else
				{
					if (current_animation == &airpunchstraight)
						player_punch_col = App->collision->AddCollider({ position.x + 40, position.y - 90, 35, 12 }, COLLIDER_, source);

					if (current_animation == &airpunchdiagonal)
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 90, 35, 12 }, COLLIDER_, source);
				
					if (current_animation == &crowchpunch)
						player_punch_col = App->collision->AddCollider({ position.x - 24, position.y - 60, 35, 12 }, COLLIDER_, source);
					
					if (current_animation == &punchstanding)																	
					{																											
						player_punch_col = App->collision->AddCollider({ position.x - 30, position.y - 87, 45, 12 }, COLLIDER_, source);
						player_col->SetPos(position.x + 15, position.y - 100);
					}
				}

			}
			if (character == 2)
			{
				if (fliped == false)
				{
					if (current_animation == &airpunchstraight)
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 90, 35, 12 }, COLLIDER_, source);	

					if (current_animation == &airpunchdiagonal)
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 60, 35, 16 }, COLLIDER_, source);

					if (current_animation == &crowchpunch)																	
						player_punch_col = App->collision->AddCollider({ position.x + 46, position.y - 52, 35, 12 }, COLLIDER_, source);

					if (current_animation == &punchstanding)																
						player_punch_col = App->collision->AddCollider({ position.x + 50, position.y - 90, 41, 12 }, COLLIDER_, source);

				}
				else
				{
					if (current_animation == &airpunchstraight)
					{
						player_punch_col = App->collision->AddCollider({ position.x - 18, position.y - 90, 35, 12 }, COLLIDER_, source);
					}		
					if (current_animation == &airpunchdiagonal)
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 90, 35, 12 }, COLLIDER_, source);

					if (current_animation == &crowchpunch)																		
						player_punch_col = App->collision->AddCollider({ position.x - 30, position.y - 52, 35, 12 }, COLLIDER_, source);
					if (current_animation == &punchstanding)																	
						player_punch_col = App->collision->AddCollider({ position.x - 30, position.y - 90, 41, 12 }, COLLIDER_, source);
				}
			}
			if (character == 3)
			{
				if (fliped == false)
				{
					if (current_animation == &airpunchstraight)
					{
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 90, 35, 12 }, COLLIDER_, source);
					}
					if (current_animation == &airpunchdiagonal)
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 90, 35, 12 }, COLLIDER_, source);

					if (current_animation == &crowchpunch)
						player_punch_col = App->collision->AddCollider({ position.x + 46, position.y - 52, 32, 16 }, COLLIDER_, source);
					if (current_animation == &punchstanding)													
						player_punch_col = App->collision->AddCollider({ position.x + 42, position.y - 82, 48, 12 }, COLLIDER_, source);
				}																												
																																
				else																											
				{		
					if (current_animation == &airpunchstraight)
					{
						player_punch_col = App->collision->AddCollider({ position.x - 18, position.y - 90, 35, 12 }, COLLIDER_, source);
					}
					if (current_animation == &airpunchdiagonal)
						player_punch_col = App->collision->AddCollider({ position.x + 43, position.y - 90, 35, 12 }, COLLIDER_, source);

					if (current_animation == &crowchpunch)																		
						player_punch_col = App->collision->AddCollider({ position.x - 28, position.y - 52, 32, 16 }, COLLIDER_, source);
					if (current_animation == &punchstanding)																	
						player_punch_col = App->collision->AddCollider({ position.x - 31, position.y - 82, 48, 12 }, COLLIDER_, source);
				}
			}
		}
		if (at == 20)
		{
			if (player_punch_col != nullptr)
				player_punch_col->to_delete = true;
		}
	/*	if (at == 13 && fliped)
		{
			position.x -= 34;
		}
		if (at == 19 && fliped)
		{
			position.x += 34;
		}*/
		if (at == 30)
		{
			punching = false;
			crowchaction = false;
			airpunching = false;
			already_hit = false;
		}
	}
	else
	{
	if (player_punch_col != nullptr)
		player_punch_col->to_delete = true;
	}
}

void ModulePlayer::LowKick()
{
	if (lowkicking == true && current_animation == &lowkick)
	{
		at++;
		if (character == 1 && at < 12)
		{
			if (!fliped)
				position.x += 3.0f;
			else
				position.x -= 3.0f;
			player_col->SetPos(position.x, position.y);
		}
		if (at == 12)
		{
			if (character == 1)
				{
					if (fliped == false)
						player_kick_col = App->collision->AddCollider({ position.x + 40, position.y - 20, 35, 12 }, COLLIDER_PLAYER_ATTACK, App->player);
							   
					else	   
						player_kick_col = App->collision->AddCollider({ position.x - 24, position.y - 20, 35, 12 }, COLLIDER_PLAYER_ATTACK, App->player);
				}	
			if (character == 2)
				{
					if (fliped == false)
						player_kick_col = App->collision->AddCollider({ position.x + 46, position.y - 28, 40, 26 }, COLLIDER_PLAYER_ATTACK, App->player);
																									 
					else																			 
						player_kick_col = App->collision->AddCollider({ position.x - 35, position.y - 28, 40, 26 }, COLLIDER_PLAYER_ATTACK, App->player);
					

				}
			if (character == 3)
				{
					if (fliped == false)
						player_kick_col = App->collision->AddCollider({ position.x + 46, position.y - 20, 32, 16 }, COLLIDER_PLAYER_ATTACK, App->player);
					else																			  
						player_kick_col = App->collision->AddCollider({ position.x - 28, position.y - 20, 32, 16 }, COLLIDER_PLAYER_ATTACK, App->player);
				}
		}
		if (at == 19)
		{
			player_kick_col->to_delete = true;
		}
		if (at == 33)
		{
			lowkicking = false;
			crowchaction = false;
			already_hit = false;
		}
	}
}

void ModulePlayer::Kick()
{
	if (kicking == true) {
		at++;
		if (already_hit && !crowchaction)
		{
			if (!fliped)
				position.x--;
			else
				position.x++;
		}
		if (at == 24)
		{
			COLLIDER_TYPE COLLIDER_ = COLLIDER_NONE;
			ModulePlayer* source = nullptr;
			if (player == 0)
			{
				COLLIDER_ = COLLIDER_PLAYER_ATTACK;
				source = App->player;
			}
			else
			{
				COLLIDER_ = COLLIDER_ENEMY_ATTACK;
				source = App->enemy;
			}
			player_col->rect.h = 110;
			player_col->rect.w = 50;

			if (character == 1)
			{

				if (fliped == false)
				{
					player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 85, 55, 17 }, COLLIDER_, source);
					player_col->SetPos(position.x, position.y - 100);
				}
				else
				{
					player_kick_col = App->collision->AddCollider({ position.x - 25, position.y - 85, 55, 17 }, COLLIDER_, source);
					player_col->SetPos(position.x + 20, position.y - 100);
				}
				

			}
			if (character == 2)
			{
				if (fliped == false)
				{
					player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 85, 49, 17 }, COLLIDER_, source);
					player_col->SetPos(position.x, position.y - 121);
				}
				else
				{
					player_kick_col = App->collision->AddCollider({ position.x - 25, position.y - 85, 49, 17 }, COLLIDER_, source);
					player_col->SetPos(position.x + 20, position.y - 121);
				}
				
			}
			if (character == 3)
			{

				if (fliped == false)
				{

					player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 85, 49, 17 }, COLLIDER_, source);
					player_col->SetPos(position.x, position.y - 121);
				}
				else
				{
					player_kick_col = App->collision->AddCollider({ position.x - 25, position.y - 85, 49, 17 }, COLLIDER_, source);
					player_col->SetPos(position.x + 20, position.y - 121);
				}
		
			}
		}
		/*if (at == 25 && fliped)
		{
			position.x -= 44;
		}*/
		if (at == 30)
		{
			/*if (fliped)
			{
				position.x += 44;
			}*/
			if(player_kick_col != nullptr)
				player_kick_col->to_delete = true;
		}
		if (at == 40)
		{
			kicking = false;
			already_hit = false;
		}		
	}
}

void ModulePlayer::AirKick()
{
	if (airkicking == true && jumping) {
		at++;
		if (at == 8)
		{
			COLLIDER_TYPE COLLIDER_ = COLLIDER_NONE;
			ModulePlayer* source = nullptr;
			if (player == 0)
			{
				COLLIDER_ = COLLIDER_PLAYER_ATTACK;
				source = App->player;
			}
			else
			{
				COLLIDER_ = COLLIDER_ENEMY_ATTACK;
				source = App->enemy;
			}
			player_col->rect.h = 110;
			player_col->rect.w = 50;

			if (character == 1)
				{
					if (fliped == false)
					{
						if (current_animation == &airkickstraight)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 44, position.y - 70, 35, 20 }, COLLIDER_, source);
						}
						if (current_animation == &airkickdiagonal)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 40, 49, 17 }, COLLIDER_, source);
						}
					}
					else
					{
						if (current_animation == &airkickstraight)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 44, position.y - 70, 35, 20 }, COLLIDER_, source);
						}
						if (current_animation == &airkickdiagonal)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 40, 49, 17 }, COLLIDER_, source);
						}
					}
				}
			if (character == 2)
				{
					if (fliped == false)
					{
						if (current_animation == &airkickstraight)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 44, position.y - 70, 35, 20 }, COLLIDER_, source);
						}
						if (current_animation == &airkickdiagonal)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 40, 49, 17 }, COLLIDER_, source);
						}
					}
					else
					{
						if (current_animation == &airkickstraight)
						{
							player_kick_col = App->collision->AddCollider({ position.x - 18, position.y - 70, 35, 20 }, COLLIDER_, source);
						}
						if (current_animation == &airkickdiagonal)
						{
							player_kick_col = App->collision->AddCollider({ position.x - 49, position.y - 40, 49, 17 }, COLLIDER_, source);
						}
					}
				}
			if (character == 3)
				{
					if (fliped == false)
					{
						if (current_animation == &airkickstraight)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 44, position.y - 70, 35, 20 }, COLLIDER_, source);
						}
						if (current_animation == &airkickdiagonal)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 40, 49, 17 }, COLLIDER_, source);
						}
					}
					else
					{
						if (current_animation == &airkickstraight)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 44, position.y - 70, 35, 20 }, COLLIDER_, source);
						}
						if (current_animation == &airkickdiagonal)
						{
							player_kick_col = App->collision->AddCollider({ position.x + 50, position.y - 40, 49, 17 }, COLLIDER_, source);
						}
					}
				}

		}
		if (at == 80)
		{
			airkicking = false;
			already_hit = false;
			if (player_kick_col != nullptr)
				player_kick_col->to_delete = true;
		}
	}
}

void ModulePlayer::SpecialAttack()
{
	if (sp == true) {
		st++;
		int n;
		COLLIDER_TYPE COLLIDER_ = COLLIDER_NONE;
		ModulePlayer* source = nullptr;
		if (player == 0)
		{
			COLLIDER_ = COLLIDER_PLAYER_SKILL;
			source = App->player;
		}
		else
		{
			COLLIDER_ = COLLIDER_ENEMY_SKILL;
			source = App->enemy;
		}
		if (character == 1)
		{
			if (st == 1)
			{
				if (!fliped)
				{
					skillJoe.speed.x = 3.0f;
					skillJoe2.speed.x = 3.0f;
				}
				else
				{
					skillJoe.speed.x = -3.0f;
					skillJoe2.speed.x = -3.0f;
				}
			}

			if (st == 25)
			{
				skillJoe.position.x = position.x + 25;
				skillJoe.position.y = position.y - 112;
				if (fliped)
				{
					skillJoe.position.x = position.x;
				}
				App->particles->AddParticle(skillJoe, position.x, position.y - 112, COLLIDER_NONE);
				player_skill_col = App->collision->AddCollider({ skillJoe.position.x, position.y - 52, 45, 60 }, COLLIDER_, source);


			}
			if (st >= 25 && st < 35)
			{
				if (st < 26)
					App->render->Blit(graphics, skillJoe.position.x, skillJoe.position.y + 60, &(skillJoe.anim.GetCurrentFrame()), fliped);
				else
					App->render->Blit(graphics, skillJoe.position.x, skillJoe.position.y + 23, &(skillJoe.anim.GetCurrentFrame()), fliped);
				skillJoe.Update();
				skillJoe2.position.x = skillJoe.position.x;
				skillJoe2.position.y = skillJoe.position.y;
				player_skill_col->SetPos(skillJoe.position.x, skillJoe.position.y + 52);
			}

			if (st >= 35)
			{
				App->render->Blit(graphics, skillJoe2.position.x, skillJoe2.position.y, &(skillJoe2.anim.GetCurrentFrame()), fliped);
				skillJoe2.Update();
				player_skill_col->rect.h = 90;
				player_skill_col->rect.w = 35;
				player_skill_col->SetPos(skillJoe2.position.x + 10, skillJoe2.position.y + 20);
			}
			if (st == 35)
			{

				specialattack_ = false;
			}
			if (st == 100)
			{
				player_skill_col->to_delete = true;
				already_hit = false;
			}

			if (st == 500)
				sp = false;

		}
		if (character == 2)
		{
			if (!fliped)
				n = 55;
			else
				n = -10;

			if (st == 1)
			{
				spatckpos.x = position.x;
				spatckpos.y = position.y;
				if (!fliped)
				{
					App->particles->skill.speed.x = 3.0f;
					App->particles->skill2.speed.x = 3.0f;
					App->particles->skill3.speed.x = 3.0f;
				}
				else
				{
					App->particles->skill.speed.x = -3.0f;
					App->particles->skill2.speed.x = -3.0f;
					App->particles->skill3.speed.x = -3.0f;
				}
			}

			if (st == 25)
			{
				App->particles->AddParticle(App->particles->skill, spatckpos.x + n, spatckpos.y - 40, COLLIDER_);
			}
			if (st == 30)
			{
				App->particles->AddParticle(App->particles->skill2, spatckpos.x + n, spatckpos.y - 67, COLLIDER_);
			}
			if (st == 35)
			{
				App->particles->AddParticle(App->particles->skill3, spatckpos.x + n, spatckpos.y - 95, COLLIDER_);
				specialattack_ = false;
			}
			if (st == 40)
			{
				App->particles->AddParticle(App->particles->skill2, spatckpos.x + n, spatckpos.y - 67, COLLIDER_);
			}
			if (st == 45)
			{
				App->particles->AddParticle(App->particles->skill, spatckpos.x + n, spatckpos.y - 40, COLLIDER_);
			}
			if (st == 1000)
				sp = false;
		}
		if (character == 3)
		{
			if (st == 1)
			{
				if (!fliped)
				{
					skillAndy.speed.x = 3.0f;
					skillAndy2.speed.x = 3.0f;
				}
				else
				{
					skillAndy.speed.x = -3.0f;
					skillAndy2.speed.x = -3.0f;
				}
			}

			if (st == 25)
			{
				skillAndy.position.x = position.x + 80;
				skillAndy.position.y = position.y - 112;
				if (fliped)
				{
					skillAndy.position.x = position.x;
				}
				App->particles->AddParticle(skillAndy, position.x, position.y - 112, COLLIDER_NONE);
				player_skill_col = App->collision->AddCollider({ skillAndy.position.x, position.y - 50, 30, 30 }, COLLIDER_, source);


			}
			if (st >= 25 && st < 35)
			{
				if (st < 26)
					App->render->Blit(graphics, skillAndy.position.x, skillAndy.position.y + 60, &(skillAndy.anim.GetCurrentFrame()), fliped);
				else
					App->render->Blit(graphics, skillAndy.position.x, skillAndy.position.y + 23, &(skillAndy.anim.GetCurrentFrame()), fliped);
				skillAndy.Update();
				skillAndy2.position.x = skillAndy.position.x;
				skillAndy2.position.y = skillAndy.position.y;
				player_skill_col->SetPos(skillAndy.position.x, skillAndy.position.y + 20);
			}

			if (st >= 35)
			{
				App->render->Blit(graphics, skillAndy2.position.x, skillAndy2.position.y, &(skillAndy2.anim.GetCurrentFrame()), fliped);
				skillAndy2.Update();
				player_skill_col->rect.h = 60;
				player_skill_col->rect.w = 25;
				player_skill_col->SetPos(skillAndy2.position.x + 10, skillAndy2.position.y + 20);
			}
			if (st == 35)
			{

				specialattack_ = false;
			}
			if (st == 200)
			{
				player_skill_col->to_delete = true;
				already_hit = false;
			}

			if (st == 500)
				sp = false;
		}
	}
}

void ModulePlayer::SpecialAttack2()
{
	if (sp2 == true)
	{
		st++;
		if (current_animation != &TerrySpecialKick)
		{
			TerrySpecialKick.Reset();
			current_animation = &TerrySpecialKick;
		}
		if (st == 120)
		{
			sp2 = false;
			specialattack_ = false;
			st = 0;
		}
	}
}

void ModulePlayer::TakeDown() 
{
	if (takingdown == true && current_animation == &takedown_fail)
	{
		tktempo++;
		if (tktempo == 20)
		{
			takingdown = false;
		}
	}
	else if (takingdown == true && current_animation == &takedown_done)
	{
		tktempo++;
		if (tktempo == 1)
			if (player == 0)
				App->enemy->Damage(30, 3);
			else
				App->player->Damage(30, 3);
		if (tktempo == 40)
		{
			App->render->StartCameraShake(20.0f, 5.0f);
		}
		if (tktempo == 80)
		{
			takingdown = false;
		}
	}
}

update_status ModulePlayer::Update()
{
	godMode();
	Jump();

	if (health < 0)
		health = 0;

	int speed = 2;
	if (!jumping)
	{
		if (player == 0)
		{
			if (!takingdown)
				if (App->enemy->Pos_X() <= Pos_X())
				{
					fliped = true;
				}
				else
				{
					fliped = false;
				}
		}

		if (player == 1)
		{
			if (!takingdown)
				if (App->player->Pos_X() <= Pos_X())
				{
					fliped = true;
				}
				else
				{
					fliped = false;
				}
		}

	}

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
		if (player == 0) 
		{
			if (App->enemy->Health() != 0)
			{
				if (stuned != 0 || App->fight_manager->Time() > 90)
				{
					if (stuned != 0)
					{
						sp = false;
						st = 0;
						specialattack_ = false;
						punching = false;
						kicking = false;
						lowkicking = false;
						takingdown = false;
						at++;
						if (stuned != 3)
						{
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
								at = 0;
							}
							if (App->scene_chooseplayer->final_player1 == 1)
							{
								player_col->SetPos(position.x + 17, position.y - 100);
							}
							if (App->scene_chooseplayer->final_player1 == 2)
							{
								player_col->SetPos(position.x + 17, position.y - 91);
							}
							if (App->scene_chooseplayer->final_player1 == 3)
							{
								player_col->SetPos(position.x + 17, position.y - 91);
							}

							if (position.x < 0)
								position.x = 0;
							if (position.x > 600)
								position.x = 600;
						}
						else
						{
							t++;
							if (at == 1)
							{
								vy = 5;
								takedown_recieved.Reset();
								current_animation = &takedown_recieved;

								if (fliped)
									jumpspeed = 2;
								else
									jumpspeed = -2;
							}
							if (at < 120)
							{
								if (vy != 2)
								{
									position.y = 220 - vy * t + 0.12*(t*t);
									position.x -= jumpspeed;
									if (position.y >= 220 && at < 120)
									{
										t = 0;
										vy--;
									}
								}
								else
								{
									position.y = 220;
								}
							}
							if (at >= 120 && position.y == 220)
							{
								position.y = 220;
								jumpspeed = 0;
								if (current_animation == &takedown_recieved)
								{
									takedown_recieved2.Reset();
									current_animation = &takedown_recieved2;
								}
							}
							if (at == 150)
							{
								stuned = 0;
								at = 0;
								t = 0;
							}
						}
					}
				}
				else
				{
					Punch();
					Kick();
					SpecialAttack();
					LowKick();
					AirKick();
					TakeDown();
					SpecialAttack2();

					if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_ && current_animation != &crowch && !lowkicking && !takingdown)
					{
						if (body_collide && !fliped)
							body_collide = false;
						if (position.x != 0 && !body_collide && position.x*(-SCREEN_SIZE) < App->render->camera.x)
							position.x -= speed;
						if (fliped == true) {
							if (current_animation != &forward && !jumping && current_animation != &crowch && !lowkicking && !takingdown)
							{
								forward.Reset();
								current_animation = &forward;
							}
						}
						else
						{
							if (current_animation != &backward && !jumping && current_animation != &crowch && !lowkicking && !takingdown)
							{
								backward.Reset();
								current_animation = &backward;
							}
						}


					}

					if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_ && current_animation != &crowch && !lowkicking && !takingdown)
					{
						if (body_collide && fliped)
							body_collide = false;
						if (position.x != 610 && !body_collide && (-SCREEN_SIZE * (position.x + 60)) > (App->render->camera.x - SCREEN_SIZE * SCREEN_WIDTH))
							position.x += speed;
						if (fliped == true)
						{
							if (current_animation != &backward && !jumping && current_animation != &crowch && !lowkicking && !takingdown)
							{
								backward.Reset();
								current_animation = &backward;
							}
						}
						else
						{
							if (current_animation != &forward && !jumping && current_animation != &crowch && !lowkicking && !takingdown)
							{
								forward.Reset();
								current_animation = &forward;
							}
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !jumping && !punching && !kicking && !specialattack_ && !lowkicking && !takingdown)
					{
						if (current_animation != &crowch)
						{
							lockX = true;
							crowchaction = true;
							crowch.Reset();
							current_animation = &crowch;
						}
						if (App->input->keyboard[SDL_SCANCODE_T] == KEY_STATE::KEY_DOWN && !punching && !kicking && !specialattack_ && !lowkicking && !takingdown) {
							if (current_animation != &crowchpunch && !jumping)
							{
								lowkicking = true;
								at = 0;
								lowkick.Reset();
								current_animation = &lowkick;
								////App->audio->playFx(punchFX);
							}
						}
						else if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN && !punching && !kicking && !specialattack_ && !lowkicking && !takingdown)
						{
							if (current_animation != &lowkick && !jumping)
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
							if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !punching && !kicking && !specialattack_ && !lowkicking && !takingdown)
							{
								if (current_animation != &crowchprotecc)
								{
									crowchprotecc.Reset();
									current_animation = &crowchprotecc;
								}
							}
						}
						else {
							if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !punching && !kicking && !specialattack_ && !lowkicking && !takingdown)
							{
								if (current_animation != &crowchprotecc)
								{
									crowchprotecc.Reset();
									current_animation = &crowchprotecc;
								}
							}
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT && current_animation != &crowchpunch && !lowkicking && !takingdown) {
						lockX = false;
						crowchaction = false;
					}

					if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP && current_animation != &crowchpunch && !lowkicking && !takingdown)
					{
						current_animation = &idle;
					}

					if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && !jumping && !punching && !kicking && !specialattack_ && !lowkicking && !takingdown)
					{
						jumping = true;
						t = 0;
							if (current_animation == &forward)
							{
								jumptype = 1;
								if (!fliped)
									jumpspeed = 2;
								else
									jumpspeed = -2;

								jumpfup.Reset();
								current_animation = &jumpfup;
							}
							else if (current_animation == &backward)
							{		
								jumptype = 2;
								if (!fliped)
									jumpspeed = -2;
								else
									jumpspeed = 2;

								jumpbup.Reset();
								current_animation = &jumpbup;
							}
							else
							{
								jumptype = 0;
								jumpspeed = 0;
							
								jumpiup.Reset();
								current_animation = &jumpiup;
							}
					}

					if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN && !punching && !kicking && !crowchaction && !specialattack_ && !lowkicking && !takingdown && !airkicking && !airpunching)
					{
						if (current_animation != &punchstanding && !jumping && !takingdown)
						{
							punching = true;
							at = 0;
							punchstanding.Reset();
							current_animation = &punchstanding;
							App->audio->playFx(punchFX);
						}
						if (current_animation != &airpunchstraight && jumping && jumptype == 0)
						{
							punching = true;
							airpunching = true;
							at = 0;
							airpunchstraight.Reset();
							current_animation = &airpunchstraight;
							App->audio->playFx(punchFX);
						}

						if (current_animation != &airpunchdiagonal && jumping && jumptype == 1 || jumptype == 2)
						{
							punching = true;
							airpunching = true;
							at = 0;
							airpunchdiagonal.Reset();
							current_animation = &airpunchdiagonal;
							App->audio->playFx(punchFX);
						}
						
					}

					if (App->input->keyboard[SDL_SCANCODE_T] == KEY_STATE::KEY_DOWN && !punching  && !crowchaction && !specialattack_ && !lowkicking && !takingdown && !airkicking && !airpunching)
					{
						if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_ && !takingdown)
						{
							kicking = true;
							at = 0;
							kickingstanding.Reset();
							current_animation = &kickingstanding;
							App->audio->playFx(kickFX);
						}
						if (current_animation != &airkickstraight && jumping && jumptype == 0)
						{
							airkicking = true;
							at = 0;
							airkickstraight.Reset();
							current_animation = &airkickstraight;
							App->audio->playFx(kickFX);
						}

						if (current_animation != &airkickdiagonal && jumping && jumptype == 1 || jumptype == 2)
						{
							airkicking = true;
							at = 0;
							airkickdiagonal.Reset();
							current_animation = &airkickdiagonal;
							App->audio->playFx(kickFX);
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction && !sp2/*<--CHANGE*/ && !lowkicking && !takingdown && !kicking) {
						/*specialattack_ = true;
						sp = true;
						st = 0;
						specialattack.Reset();
						current_animation = &specialattack;
						App->audio->playFx(skillFX);*/
						sp2 = true;
						specialattack_ = true;
						st = 0;
					}
					if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction && !sp && !lowkicking && !takingdown)
					{
						if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_ && current_animation != &takedown_fail && current_animation != &takedown_done && body_collide == true)
						{
							takingdown = true;
							tktempo = 0;
							current_animation = &takedown_done;
							takedown_done.Reset();
						}
						else if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_ && body_collide == false)
						{
							takingdown = true;
							tktempo = 0;
							current_animation = &takedown_fail;
							takedown_fail.Reset();
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN && App->scene_chooseplayer->final_player1 == 1)
					{
						if (current_animation != &JoeSpecialKick)
						{
							specialattack2_ = true;
							st = 0;
							current_animation = &JoeSpecialKick;
							JoeSpecialKick.Reset();
							App->audio->playFx(skillFX);
						}

					}

					if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
						&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
						&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
						&& !jumping && !punching && !kicking && !specialattack_ && !lowkicking && !takingdown)
						current_animation = &idle;

					if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
						&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
						&& App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
						&& !jumping && !punching && !kicking && !specialattack_ && !lowkicking && !takingdown)
						current_animation = &idle;

					if (current_animation != &punchstanding && current_animation != &kickingstanding && current_animation != &crowchpunch && !lowkicking && !takingdown)
					{
						if (character == 1)
						{
							if (current_animation == &crowch || current_animation == &crowchprotecc && crowchaction)
							{
								player_col->rect.h = 65;
								player_col->rect.w = 41;
								if (!fliped)
								{
									player_col->SetPos(position.x + 5, position.y - 67);
								}
								else
								{
									player_col->SetPos(position.x + 14, position.y - 67);
								}
							}
							else
							{
								if (!fliped)
								{
									player_col->SetPos(position.x + 5, position.y - 100);
									player_col->rect.h = 100;
									player_col->rect.w = 33;
								}
								else
								{
									player_col->SetPos(position.x + 27, position.y - 100);
									player_col->rect.h = 100;
									player_col->rect.w = 33;
								}
							}
						}
						if (character == 2)
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
						if (character == 3)
						{
							if (current_animation == &crowch || current_animation == &crowchprotecc && crowchaction)
							{
								player_col->rect.h = 55;
								player_col->rect.w = 41;
								player_col->SetPos(position.x + 5, position.y - 55);
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
									if (!jumping)
										player_col->SetPos(position.x + 17, position.y - 91);
									else
										player_col->SetPos(position.x + 7, position.y - 91);
									player_col->rect.h = 90;
									player_col->rect.w = 33;
								}
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
		if (player == 1)
		{
			if (App->player->Health() != 0)
			{
				if (stuned != 0 || App->fight_manager->Time() > 90)
				{
					if (stuned != 0)
					{
						sp = false;
						st = 0;
						specialattack_ = false;
						punching = false;
						kicking = false;
						lowkicking = false;
						takingdown = false;
						at++;
						if (stuned != 3)
						{
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
								at = 0;
							}
							if (App->scene_chooseplayer->final_player1 == 1)
							{
								player_col->SetPos(position.x + 17, position.y - 100);
							}
							if (App->scene_chooseplayer->final_player1 == 2)
							{
								player_col->SetPos(position.x + 17, position.y - 91);
							}
							if (App->scene_chooseplayer->final_player1 == 3)
							{
								player_col->SetPos(position.x + 17, position.y - 91);
							}

							if (position.x < 0)
								position.x = 0;
							if (position.x > 600)
								position.x = 600;
						}
						else
						{
							t++;
							if (at == 1)
							{
								vy = 5;
								takedown_recieved.Reset();
								current_animation = &takedown_recieved;

								if (fliped)
									jumpspeed = 2;
								else
									jumpspeed = -2;
							}
							if (at < 120)
							{
								if (vy != 2)
								{
									position.y = 220 - vy * t + 0.12*(t*t);
									position.x -= jumpspeed;
									if (position.y >= 220 && at < 120)
									{
										t = 0;
										vy--;
									}
								}
								else
								{
									position.y = 220;
								}
							}
							if (at >= 120 && position.y == 220)
							{
								position.y = 220;
								jumpspeed = 0;
								if (current_animation == &takedown_recieved)
								{
									takedown_recieved2.Reset();
									current_animation = &takedown_recieved2;
								}
							}
							if (at == 150)
							{
								stuned = 0;
								at = 0;
								t = 0;
							}
						}
					}
				}
				else
				{
					Punch();
					Kick();
					SpecialAttack();
					LowKick();
					AirKick();
					TakeDown();

					if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_ && current_animation != &crowch && !lowkicking)
					{
						if (body_collide && !fliped)
							body_collide = false;
						if (position.x != 0 && !body_collide && position.x*(-SCREEN_SIZE) < App->render->camera.x)
							position.x -= speed;
						if (fliped == true) {
							if (current_animation != &forward && !jumping && current_animation != &crowch && !lowkicking)
							{
								forward.Reset();
								current_animation = &forward;
							}
						}
						else
						{
							if (current_animation != &backward && !jumping && current_animation != &crowch && !lowkicking)
							{
								backward.Reset();
								current_animation = &backward;
							}
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && !lockX && !punching && !kicking && !specialattack_ && current_animation != &crowch && !lowkicking)
					{
						if (body_collide && fliped)
							body_collide = false;
						if (position.x != 610 && !body_collide && (-SCREEN_SIZE * (position.x + 60)) > (App->render->camera.x - SCREEN_SIZE * SCREEN_WIDTH))
							position.x += speed;
						if (fliped == true)
						{
							if (current_animation != &backward && !jumping && current_animation != &crowch && !lowkicking)
							{
								backward.Reset();
								current_animation = &backward;
							}
						}
						else
						{
							if (current_animation != &forward && !jumping && current_animation != &crowch && !lowkicking)
							{
								forward.Reset();
								current_animation = &forward;
							}
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && !jumping && !punching && !kicking && !specialattack_ && !lowkicking)
					{
						if (current_animation != &crowch)
						{
							lockX = true;
							crowchaction = true;
							crowch.Reset();
							current_animation = &crowch;
						}
						if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN && !punching && !kicking && !specialattack_ && !lowkicking) {
							if (current_animation != &crowchpunch && !jumping)
							{
								lowkicking = true;
								at = 0;
								lowkick.Reset();
								current_animation = &lowkick;
								//App->audio->playFx(punchFX);
							}
						}
						else if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN && !punching && !kicking && !specialattack_ && !lowkicking)
						{
							if (current_animation != &lowkick && !jumping)
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
							if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && !punching && !kicking && !specialattack_ && !lowkicking)
							{
								if (current_animation != &crowchprotecc)
								{
									crowchprotecc.Reset();
									current_animation = &crowchprotecc;
								}
							}
						}
						else {
							if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && !punching && !kicking && !specialattack_ && !lowkicking)
							{
								if (current_animation != &crowchprotecc)
								{
									crowchprotecc.Reset();
									current_animation = &crowchprotecc;
								}
							}
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_DOWN] != KEY_STATE::KEY_REPEAT && current_animation != &crowchpunch && !lowkicking) {
						lockX = false;
						crowchaction = false;
					}

					if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_UP && current_animation != &crowchpunch && !lowkicking)
					{
						current_animation = &idle;
					}

					if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN && !jumping && !punching && !kicking && !specialattack_ && !lowkicking)
					{
						jumping = true;
						t = 0;
						if (current_animation == &forward)
						{
							jumptype = 1;
							if (!fliped)
								jumpspeed = 2;
							else
								jumpspeed = -2;

							jumpfup.Reset();
							current_animation = &jumpfup;
						}
						else if (current_animation == &backward)
						{
							jumptype = 2;
							if (!fliped)
								jumpspeed = -2;
							else
								jumpspeed = 2;

							jumpbup.Reset();
							current_animation = &jumpbup;
						}
						else
						{
							jumptype = 0;
							jumpspeed = 0;

							jumpiup.Reset();
							current_animation = &jumpiup;
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN && !punching && !kicking && !crowchaction && !specialattack_ && !lowkicking && !airkicking && !airpunching) {
						if (current_animation != &punchstanding && !jumping && !takingdown)
						{
							punching = true;
							at = 0;
							punchstanding.Reset();
							current_animation = &punchstanding;
							App->audio->playFx(punchFX);
						}
						if (current_animation != &airpunchstraight && jumping && jumptype == 0)
						{
							punching = true;
							airpunching = true;
							at = 0;
							airpunchstraight.Reset();
							current_animation = &airpunchstraight;
							App->audio->playFx(punchFX);
						}

						if (current_animation != &airpunchdiagonal && jumping && jumptype == 1 || jumptype == 2)
						{
							punching = true;
							airpunching = true;
							at = 0;
							airpunchdiagonal.Reset();
							current_animation = &airpunchdiagonal;
							App->audio->playFx(punchFX);
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN && !punching && !crowchaction && !specialattack_ && !lowkicking && !airpunching && !airkicking && !airpunching)
					{
						if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_ && !takingdown)
						{
							kicking = true;
							at = 0;
							kickingstanding.Reset();
							current_animation = &kickingstanding;
							App->audio->playFx(kickFX);
						}
						if (current_animation != &airkickstraight && jumping && jumptype == 0)
						{
							kicking = true;
							at = 0;
							airkickstraight.Reset();
							current_animation = &airkickstraight;
							App->audio->playFx(kickFX);
						}

						if (current_animation != &airkickdiagonal && jumping && jumptype == 1 || jumptype == 2)
						{
							kicking = true;
							at = 0;
							airkickdiagonal.Reset();
							current_animation = &airkickdiagonal;
							App->audio->playFx(kickFX);
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction && !sp && !lowkicking) {
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

					if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN && !punching && !jumping && !crowchaction && !sp && !lowkicking && !takingdown)
					{
						if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_ && current_animation != &takedown_fail && current_animation != &takedown_done && body_collide == true)
						{
							takingdown = true;
							tktempo = 0;
							takedown_done.Reset();
							current_animation = &takedown_done;
						}
						else if (current_animation != &kickingstanding && !jumping && !crowchaction && !specialattack_ && body_collide == false)
						{
							takingdown = true;
							tktempo = 0;
							takedown_fail.Reset();
							current_animation = &takedown_fail;
						}
					}

					if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
						&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
						&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
						&& !jumping && !punching && !kicking && !specialattack_ && !lowkicking)
						current_animation = &idle;

					if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT
						&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT
						&& App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
						&& !jumping && !punching && !kicking && !specialattack_ && !lowkicking)
						current_animation = &idle;

					if (current_animation != &punchstanding && current_animation != &kickingstanding && current_animation != &crowchpunch && !lowkicking)
					{
						if (character == 1)
						{
							if (current_animation == &crowch || current_animation == &crowchprotecc && crowchaction)
							{
								player_col->rect.h = 65;
								player_col->rect.w = 41;
								if (!fliped)
								{
									player_col->SetPos(position.x + 5, position.y - 67);
								}
								else
								{
									player_col->SetPos(position.x + 14, position.y - 67);
								}

							}
							else
							{
								if (!fliped)
								{
									player_col->SetPos(position.x + 5, position.y - 100);
									player_col->rect.h = 100;
									player_col->rect.w = 33;
								}
								else
								{
									player_col->SetPos(position.x + 27, position.y - 100);
									player_col->rect.h = 100;
									player_col->rect.w = 33;
								}
							}
						}
						if (character == 2)
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
						if (character == 3)
						{
							if (current_animation == &crowch || current_animation == &crowchprotecc && crowchaction)
							{
								player_col->rect.h = 55;
								player_col->rect.w = 41;
								player_col->SetPos(position.x + 5, position.y - 55);
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
									if (!jumping)
										player_col->SetPos(position.x + 17, position.y - 91);
									else
										player_col->SetPos(position.x + 7, position.y - 91);
									player_col->rect.h = 90;
									player_col->rect.w = 33;
								}
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
	}

	SDL_Rect r = current_animation->GetCurrentFrame();
	
	if (fliped)
	{
		App->render->Blit(graphics, position.x + width, position.y - r.h, &r, fliped);
	}
	else 
	{
		App->render->Blit(graphics, position.x, position.y - r.h, &r, fliped);
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::Damage(const int damage, const int type)
{
	if (current_animation == &backward || current_animation == &crowchprotecc)
	{
		health -= damage / 2;
	}		
	else
	{
		if (damage > health)
		{		
			App->slowdown->StartSlowdown(60, 60);
		}
		health -= damage;
	}
		
	stuned = type;
}

void ModulePlayer::godMode()
{
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
		godMode_ = !godMode_;

	if (godMode_ == false)
		return;

	App->player->health = 100;
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN)
	{
		App->player->health = 0;
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		App->enemy->health = 0;
	}
	// pressing F10 game is restarted
	if (App->input->keyboard[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_intro);
		switch (App->scene_map->map)
		{
		case 1:
		{
			App->fade->FadeToBlack((Module*)App->scene_paopao, (Module*)App->scene_intro);
		}	break;

		case 2:
		{
			App->fade->FadeToBlack((Module*)App->scene_soundbeach, (Module*)App->scene_intro);
		}break;

		case 3:
		{
			App->fade->FadeToBlack((Module*)App->scene_westsubway, (Module*)App->scene_intro);
		}	break;

		case 4:
		{
			App->fade->FadeToBlack((Module*)App->scene_howardarena, (Module*)App->scene_intro);
		} break;
		}
		App->Restart();
	}

}

void ModulePlayer::OnCollision(Collider* a, Collider* b, bool colliding)
{
	if (player == 0) 
	{
		if (colliding)
		{
			if (a->type == COLLIDER_PLAYER_ATTACK && b->type == COLLIDER_ENEMY && !already_hit)
			{
				already_hit = true;
				if (kicking || lowkicking || airkicking)
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
			if (a->type == COLLIDER_PLAYER_SKILL && b->type == COLLIDER_ENEMY && !already_hit)
			{
				already_hit = true;
				if (sp)
				{
					App->enemy->Damage(50, 1);
					score += 500;
				}
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

	if (player == 1)
	{
		if (colliding)
		{
			if (a->type == COLLIDER_ENEMY_ATTACK && b->type == COLLIDER_PLAYER && !already_hit)
			{
				already_hit = true;
				if (kicking || lowkicking || airkicking)
				{
					App->player->Damage(30, 2);
					score += 200;
				}
				if (punching)
				{
					App->player->Damage(20, 1);
					score += 100;
				}

			}
			if (b->type == COLLIDER_PLAYER && a->type == COLLIDER_ENEMY)
			{
				body_collide = true;
			}
			if (a->type == COLLIDER_ENEMY_SKILL && b->type == COLLIDER_PLAYER && !already_hit)
			{
				already_hit = true;
				if (sp)
				{
					App->player->Damage(50, 1);
					score += 500;
				}
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
}