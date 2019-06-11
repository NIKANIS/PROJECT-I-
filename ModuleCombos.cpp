#include "Globals.h"
#include "Application.h"
#include "ModuleCombos.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"

ModuleCombos::ModuleCombos() : Module()
{}

// Destructor
ModuleCombos::~ModuleCombos()
{}

bool ModuleCombos::Init() {
	LOG("Init ModuleCOMBOS");

	return true;
}

bool ModuleCombos::CleanUp() {

	return true;
}

update_status ModuleCombos::Update() 
{



	return update_status::UPDATE_CONTINUE;
}

bool ModuleCombos::SpecialAttack3(int player) 
{
	App->player->score = SplashFountCount;
		actual_frameP1SF++;
		if (actual_frameP1SF <= 120) 
		{
			switch (SplashFountCount == 0)
				if (App->input->JoystickGetPos(App->input->controller, DOWN) == true)
						SplashFountCount++;
				
			/*if (SplashFountCount == 1)
				if (App->input->JoystickGetPos(App->input->controller, DOWNLEFT) == true) 
						SplashFountCount++;*/
				
			if (SplashFountCount == 1)
				if (App->input->JoystickGetPos(App->input->controller, LEFT) == true) 
						SplashFountCount++;
				
			if (SplashFountCount == 2)
				if (App->input->controll[BUTTON_X] == KEY_DOWN)
				{
					SplashFountCount = 0;
					return true;
				}
		}
		else 
		{
			actual_frameP1SF = 0;
			SplashFountCount = 0;
			return false;
		}
	
	
}

/*bool ModuleCombos::CheckPunchP2() {
	if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
		return true;
	}
	return false;
}

bool ModuleCombos::CheckSplashFountP1() {
	actual_frameP1SF++;
	if (actual_frameP1SF <= SPLASHFOUNT) {
		switch (SplashFountCount)
		{
		case 0:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN)  {
				SplashFountCount++;
			}
			break;
		case 1:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN)  {
				SplashFountCount++;
			}
			break;
		case 2:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN)  {
				SplashFountCount = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP1SF = 0;
		SplashFountCount = 0;
		return false;
	}
}

bool ModuleCombos::CheckSplashFountP2() {
	actual_frameP2SF++;
	if (actual_frameP2SF <= SPLASHFOUNT) {
		switch (SplashFountCount2)
		{
		case 0:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				SplashFountCount2++;
			}
			break;
		case 1:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				SplashFountCount2++;
			}
			break;
		case 2:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				SplashFountCount2 = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP2SF = 0;
		SplashFountCount2 = 0;
		return false;
	}
}

bool ModuleCombos::CheckPowerGraduationP1() {
	actual_frameP1PG++;
	if (actual_frameP1PG <= POWERGRADUATION) {
		switch (PowerGraditionCount)
		{
		case 0:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_IDLE) {
				HoldGP1++;
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_UP) {
				if (HoldGP1 > 10) {
					HoldGP1 = 0;
					PowerGraditionCount++;
				}
			}
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_UP) {
				if (HoldGP1 > 10) {
					HoldGP1 = 0;
					PowerGraditionCount++;
				}
			}
			break;
		case 1:
			if (App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				PowerGraditionCount = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP1PG = 0;
		PowerGraditionCount = 0;
		return false;
	}
}

bool ModuleCombos::CheckPowerGraduationP2() {
	actual_frameP2PG++;
	if (actual_frameP2PG <= POWERGRADUATION) {
		switch (PowerGraditionCount2)
		{
		case 0:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_IDLE) {
				HoldGP2++;
			}
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_UP) {
				if (HoldGP2 > 10) {
					HoldGP2 = 0;
					PowerGraditionCount2++;
				}
			}
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_UP) {
				if (HoldGP2 > 10) {
					HoldGP2 = 0;
					PowerGraditionCount2++;
				}
			}
			break;
		case 1:
			if (App->input->Pad2.button_state[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Pad1.button_state[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == KEY_DOWN) {
				PowerGraditionCount2 = 0;
				return true;
			}
			break;
		}
	}
	else {
		actual_frameP2PG = 0;
		PowerGraditionCount2 = 0;
		return false;
	}
}*/