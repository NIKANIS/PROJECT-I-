#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModulePlayerScore.h"

#define MAX_SCORE_D 5

ModulePlayerScore::ModulePlayerScore()
{
	position.x = HUD_X + 72;
	position.y = HUD_Y - 17;

	zero = {1,286,9,9};
	one = {11,286,7,9};
	two = {19,286,9,9};
	three = {29,286,9,9};
	four = {39,286,9,9};
	five = {1,296,9,9};
	six = { 11,296,9,9 };
	seven = { 21,296,9,9 };
	eight = { 31,296,9,9 };
	nine = { 41,296,9,9 };

	score = 0;
	pastscore = 1;
}

ModulePlayerScore::~ModulePlayerScore()
{
}

bool ModulePlayerScore::Start()
{
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/UI sprites.png");
	return true;
}

/*bool ModulePlayerScore::CleanUp()
{

}*/

update_status ModulePlayerScore::Update()
{
	/*if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN)
	{
		score++;
	}
	if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN)
	{
		score+= 10;
	}
	if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN)
	{
		score += 100;
	}
	if (App->input->keyboard[SDL_SCANCODE_T] == KEY_STATE::KEY_DOWN)
	{
		score += 1000;
	}
	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN)
	{
		score += 10000;
	}*/

	if (score > 99999)
	{
		score = 99999;
	}
		
	if (pastscore != score) {
		n[4] = (int)score / 10000;
		n[3] = (int)(score - n[4] * 10000) / 1000;
		n[2] = (int)(score - n[4] * 10000 - n[3] * 1000) / 100;
		n[1] = (int)(score - n[4] * 10000 - n[3] * 1000 - n[2] * 100) / 10;
		n[0] = score - n[4] * 10000 - n[3] * 1000 - n[2] * 100 - n[1] * 10;

		for (int i = 0; i < MAX_SCORE_D; i++)
		{
			switch (n[i])
			{
			case 0:
				if (i == 0)
					r[i] = zero;
				else
				{
					for (int y = i + 1; y < MAX_SCORE_D; y++)
					{
						if (n[y] != 0)
						{
							r[i] = zero;
							break;
						}
					}
				}
				break;
			case 1:
				r[i] = one;
				break;
			case 2:
				r[i] = two;
				break;
			case 3:
				r[i] = three;
				break;
			case 4:
				r[i] = four;
				break;
			case 5:
				r[i] = five;
				break;
			case 6:
				r[i] = six;
				break;
			case 7:
				r[i] = seven;
				break;
			case 8:
				r[i] = eight;
				break;
			case 9:
				r[i] = nine;
				break;
			}
		}
	}
	pastscore = score;

	App->render->Blit(graphics, position.x, position.y, &r[4], 0.0f);
	App->render->Blit(graphics, position.x + 8, position.y, &r[3], 0.0f);
	App->render->Blit(graphics, position.x + 8*2, position.y, &r[2], 0.0f);
	App->render->Blit(graphics, position.x + 8*3, position.y, &r[1], 0.0f);
	App->render->Blit(graphics, position.x + 8*4, position.y, &r[0], 0.0f);

	return UPDATE_CONTINUE;
}