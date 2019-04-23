#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFightTimer.h"
#include "ModuleFightManager.h"

ModuleFightTimer::ModuleFightTimer()
{
	position.x = HUD_X;
	position.y = HUD_Y;
	timer = { 1,80,33,33 };
	zero = {35,80,15,22};
	one = { 51,80,15,22 };
	two = { 67,80,15,22 };
	three = { 83,80,15,22 };
	four = { 99,80,15,22 };
	five = { 35,103,15,22 };
	six = { 51,103,15,22 };
	seven = { 67,103,15,22 };
	eight = { 83,103,15,22 };
	nine = { 99,103,15,22 };
	
}

ModuleFightTimer::~ModuleFightTimer()
{
}

bool ModuleFightTimer::Start()
{
	graphics = App->textures->Load("SPRITES FATAL FURY/UI/UI sprites.png");
	return true;
}

update_status ModuleFightTimer::Update()
{


	int time = App->fight_manager->Time();
	if (time > 90)
		time = 90;

	n[1] = (int)(time) / 10;
	n[0] = time - n[1] * 10;

	for (int i = 0; i < 2; i++)
	{
		switch (n[i])
		{
		case 0:
			r[i] = zero;
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

	App->render->Blit(graphics, position.x+ 120, position.y - 25, &timer, 0.0f);
	App->render->Blit(graphics, position.x + 121, position.y - 15, &r[1], 0.0f);
	App->render->Blit(graphics, position.x + 137, position.y - 15, &r[0], 0.0f);
	return update_status::UPDATE_CONTINUE;
}