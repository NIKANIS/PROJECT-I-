#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModulePlayerScore.h"

#define MAX_SCORE_D 5

ModulePlayerScore::ModulePlayerScore(const int player)
{
	position.x = HUD_X + 72;
	position.y = HUD_Y - 17;

	if (player == 0)
		this->player = 0;
	
	if (player != 0)
		this->player = 1;

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

bool ModulePlayerScore::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}

update_status ModulePlayerScore::Update()
{
	int s;
	if (player == 0)
		s = App->player->Score();

	if (player == 1)
		s = App->enemy->Score();

	if (s > 99999)
	{
		s = 99999;
	}
		
	if (pastscore != s) {
		n[4] = (int)s / 10000;
		n[3] = (int)(s - n[4] * 10000) / 1000;
		n[2] = (int)(s - n[4] * 10000 - n[3] * 1000) / 100;
		n[1] = (int)(s - n[4] * 10000 - n[3] * 1000 - n[2] * 100) / 10;
		n[0] = s - n[4] * 10000 - n[3] * 1000 - n[2] * 100 - n[1] * 10;

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
	pastscore = s;

	App->render->Blit(graphics, position.x + (88*player), position.y, &r[4], 0.0f);
	App->render->Blit(graphics, position.x + 8 + (88 * player), position.y, &r[3], 0.0f);
	App->render->Blit(graphics, position.x + 8*2 + (88 * player), position.y, &r[2], 0.0f);
	App->render->Blit(graphics, position.x + 8*3 + (88 * player), position.y, &r[1], 0.0f);
	App->render->Blit(graphics, position.x + 8*4 + (88 * player), position.y, &r[0], 0.0f);

	return UPDATE_CONTINUE;
}